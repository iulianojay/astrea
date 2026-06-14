#!/usr/bin/env python3
"""
Propagation Benchmark Report Generator

Parses Google Benchmark JSON results and produces:
  - A Markdown report saved to docs/design/benchmarks/propagation.md
  - An ASCII summary table printed to the console

Usage:
    python3 scripts/print_benchmark_results.py [options]

Options:
    --results-dir PATH   Root directory to search for benchmark JSON files
                         (default: ./install)
    --output PATH        Output Markdown file
                         (default: docs/design/benchmarks/propagation.md)
    --notes-file PATH    JSON file mapping propagator names to notes
                         (default: scripts/benchmark_notes.json)
    --introduction TEXT  Override the default introduction paragraph
    --no-markdown        Skip writing the Markdown report to disk
    --no-console         Suppress the console ASCII table
    --stdout             Write Markdown to stdout instead of a file
"""

import json
import glob
import sys
import re
import argparse
from pathlib import Path
from datetime import datetime
from itertools import groupby
from typing import Dict, List, Optional

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

_SCRIPT_DIR       = Path(__file__).parent
_REPO_ROOT        = _SCRIPT_DIR.parent
DEFAULT_RESULTS_DIR = _REPO_ROOT
DEFAULT_OUTPUT      = _REPO_ROOT / "docs" / "design" / "benchmarks" / "propagation.md"
DEFAULT_NOTES_FILE  = _SCRIPT_DIR / "benchmark_notes.json"

# ---------------------------------------------------------------------------
# Domain constants
# ---------------------------------------------------------------------------

EOM_ORDER = ["TwoBody", "J2MeanVop", "KeplerianVop", "EquinoctialVop", "CowellsMethod"]

GCOLS = [2, 20, 70]
PCOLS = [("Drag", 1), ("N-Body", 2), ("SRP", 4), ("All", 7)]
TCOLS = [97, 1440, 10080]

DEFAULT_INTRODUCTION = """\
This report presents the propagation benchmark results for Astrea's orbital propagation suite.
Benchmarks are run using [Google Benchmark](https://github.com/google/benchmark) and cover all
supported equations of motion (EOM) types across a range of force model configurations and
propagation durations. Results are generated automatically by `scripts/run_benchmarks.sh`.

Propagation times benchmarked: **97 min** (~1 orbit), **1440 min** (1 day), **10080 min** (1 week).
"""

# ---------------------------------------------------------------------------
# Data loading
# ---------------------------------------------------------------------------

def _parse_name_params(name: str) -> Dict[str, int]:
    """Extract key:value integer pairs from a benchmark name string."""
    params = {}
    for part in name.split("/")[1:]:
        m = re.match(r"(\w+):(-?\d+)", part)
        if m:
            params[m.group(1)] = int(m.group(2))
    return params


def _perturb_label(pf: int) -> str:
    flags = [name for name, bit in [("Drag", 1), ("N-Body", 2), ("SRP", 4)] if pf & bit]
    return ", ".join(flags) if flags else "None"


def load_records(results_dir: Path) -> List[Dict]:
    """Discover and parse all BenchmarkPropagation entries from benchmark JSON files."""
    pattern = str(results_dir / "**" / "benchmarks" / "benchmark_results" / "*.json")
    records = []
    for fpath in sorted(glob.glob(pattern, recursive=True)):
        try:
            with open(fpath) as f:
                data = json.load(f)
        except Exception as e:
            print(f"Warning: could not read {fpath}: {e}", file=sys.stderr)
            continue

        ctx = data.get("context", {})
        for bm in data.get("benchmarks", []):
            if bm.get("run_type") == "aggregate":
                continue
            if "BenchmarkPropagation" not in bm.get("name", ""):
                continue
            p = _parse_name_params(bm["name"])
            records.append(dict(
                eom      = p.get("eom", 0),
                name     = bm.get("label", "?"),
                t        = p.get("prop_time_min", 0),
                g        = p.get("gravity", 0),
                pf       = p.get("perturb", 0),
                real     = bm.get("real_time", 0.0),
                cpu      = bm.get("cpu_time", 0.0),
                iters    = bm.get("iterations", 0),
                date     = ctx.get("date", ""),
                host     = ctx.get("host_name", ""),
                num_cpus = ctx.get("num_cpus", 0),
                mhz      = ctx.get("mhz_per_cpu", 0),
            ))
    records.sort(key=lambda r: (r["eom"], r["t"], r["g"], r["pf"]))
    return records

# ---------------------------------------------------------------------------
# Report generator
# ---------------------------------------------------------------------------

class BenchmarkReportGenerator:
    """
    Generates a Markdown benchmark report from Google Benchmark JSON results.

    Parameters
    ----------
    results_dir  : Root directory to search for benchmark result JSON files.
    notes_file   : Optional JSON file mapping propagator names to annotation strings.
    introduction : Optional override for the default introduction paragraph.
    """

    def __init__(
        self,
        results_dir: Path = DEFAULT_RESULTS_DIR,
        notes_file: Optional[Path] = DEFAULT_NOTES_FILE,
        introduction: Optional[str] = None,
    ):
        self.results_dir  = Path(results_dir)
        self.introduction = introduction or DEFAULT_INTRODUCTION
        self.notes: Dict[str, str] = {}

        if notes_file:
            nf = Path(notes_file)
            if nf.exists():
                try:
                    with open(nf) as f:
                        self.notes = json.load(f)
                except Exception as e:
                    print(f"Warning: could not load notes file {nf}: {e}", file=sys.stderr)

        self.records = load_records(self.results_dir)

    # ------------------------------------------------------------------
    # Markdown helpers
    # ------------------------------------------------------------------

    def _md_header(self) -> str:
        generated = datetime.now().strftime("%B %d, %Y at %H:%M:%S")
        ctx_line = ""
        if self.records:
            r = self.records[0]
            if r["host"]:
                ctx_line = (
                    f"\n*Run on **{r['host']}** — "
                    f"{r['num_cpus']} CPUs @ {r['mhz']} MHz — {r['date']}*\n"
                )
        return (
            '---\n'
            'title: "Propagation Benchmarks"\n'
            'description: "Runtime benchmarks for the Astrea propagation suite"\n'
            '---\n\n'
            '# Propagation Benchmarks\n\n'
            f'*Report generated on {generated}*\n'
            f'{ctx_line}\n'
        )

    def _md_introduction(self) -> str:
        return f'{self.introduction.strip()}\n\n'

    def _md_summary(self) -> str:
        if not self.records:
            return ""
        by_name: Dict[str, List] = {}
        for r in self.records:
            by_name.setdefault(r["name"], []).append(r)

        md  = "## Summary\n\n"
        md += "| Propagator | Configurations | Fastest (ms) | Slowest (ms) |\n"
        md += "|---|---|---|---|\n"
        for name in EOM_ORDER:
            if name not in by_name:
                continue
            grp     = by_name[name]
            fastest = min(r["real"] for r in grp)
            slowest = max(r["real"] for r in grp)
            md += f"| {name} | {len(grp)} | {fastest:.4f} | {slowest:.4f} |\n"
        md += "\n"
        return md

    def _md_propagator_section(self, name: str, records: List[Dict]) -> str:
        md   = f"### {name}\n\n"
        note = self.notes.get(name)
        if note:
            md += f'!!! info "Notes"\n    {note}\n\n'

        is_analytic = records[0]["eom"] < 2
        if is_analytic:
            md += "| Prop Time (min) | Real Time (ms) | CPU Time (ms) | Iterations |\n"
            md += "|---|---|---|---|\n"
            for r in sorted(records, key=lambda r: r["t"]):
                md += f"| {r['t']} | {r['real']:.4f} | {r['cpu']:.4f} | {r['iters']:,} |\n"
        else:
            md += "| Prop Time (min) | Gravity | Perturbations | Real Time (ms) | CPU Time (ms) | Iterations |\n"
            md += "|---|---|---|---|---|---|\n"
            for r in records:
                md += (
                    f"| {r['t']} | {r['g']} | {_perturb_label(r['pf'])} "
                    f"| {r['real']:.4f} | {r['cpu']:.4f} | {r['iters']:,} |\n"
                )
        md += "\n"
        return md

    def _md_results(self) -> str:
        if not self.records:
            return "*No benchmark results found.*\n"
        by_name: Dict[str, List] = {}
        for r in self.records:
            by_name.setdefault(r["name"], []).append(r)

        md = "## Results\n\n"
        for name in EOM_ORDER:
            if name not in by_name:
                continue
            md += self._md_propagator_section(name, by_name[name])
        return md

    def generate_report(self) -> str:
        """Return the full Markdown report as a string."""
        return (
            self._md_header()
            + self._md_introduction()
            + self._md_summary()
            + self._md_results()
        )

    def save_report(self, output_path: Path) -> None:
        """Write the Markdown report to *output_path*, creating directories as needed."""
        output_path = Path(output_path)
        output_path.parent.mkdir(parents=True, exist_ok=True)
        content = self.generate_report()
        with open(output_path, "w") as f:
            f.write(content)
        print(f"Report saved to: {output_path.absolute()}")

    # ------------------------------------------------------------------
    # Console ASCII table
    # ------------------------------------------------------------------

    def print_console_table(self) -> None:
        """Print a compact ASCII table of all results to stdout."""
        if not self.records:
            print("No propagation benchmark results found.")
            return

        WN = 16; WG = 4; WP = 6; WTS = [5, 6, 7]; WR = 14; WC = 13; WI = 11
        all_widths = [WN] + [WG] * 3 + [WP] * 4 + WTS + [WR, WC, WI]
        g_span = 3 * WG + 2
        p_span = 4 * WP + 3
        t_span = sum(WTS) + 2

        sep   = "+" + "+".join("-" * w for w in all_widths) + "+"
        thick = "+" + "+".join("=" * w for w in all_widths) + "+"

        def row_str(cells):
            return "|" + "|".join(cells) + "|"

        def header1():
            s  = f'|{"Options":>{WN}}'
            s += f'|{" Gravity ":^{g_span}}'
            s += f'|{" Perturbations ":^{p_span}}'
            s += f'|{" Prop Time (min) ":^{t_span}}'
            s += f'|{" Real Time (ms)":^{WR}}'
            s += f'|{" CPU Time (ms)":^{WC}}'
            s += f'|{" Iterations":^{WI}}|'
            return s

        def header2():
            c = [f'{"Propagator":>{WN}}']
            for gv in GCOLS:
                c.append(f"{gv:^{WG}}")
            for pn, _ in PCOLS:
                c.append(f"{pn:^{WP}}")
            for tv, w in zip(TCOLS, WTS):
                c.append(f"{tv:^{w}}")
            c.append(f'{"(ms)":>{WR}}')
            c.append(f'{"(ms)":>{WC}}')
            c.append(f'{"count":>{WI}}')
            return row_str(c)

        def data_row(rec, label):
            eom = rec["eom"]
            c = [f" {label:<{WN - 1}}"]
            for gv in GCOLS:
                c.append(("-" if eom < 2 else "x" if rec["g"] == gv else "").center(WG))
            for _, pf in PCOLS:
                c.append(("-" if eom < 2 else "x" if rec["pf"] == pf else "").center(WP))
            for tv, w in zip(TCOLS, WTS):
                c.append(("x" if rec["t"] == tv else "").center(w))
            c.append(f' {rec["real"]:>{WR - 2}.3f} ')
            c.append(f' {rec["cpu"]:>{WC - 2}.3f} ')
            c.append(f' {rec["iters"]:>{WI - 2}d} ')
            return row_str(c)

        print(thick)
        print(header1())
        print(sep)
        print(header2())
        print(thick)
        for _, grp in groupby(self.records, key=lambda r: r["eom"]):
            grp = list(grp)
            name = grp[0]["name"]
            for i, rec in enumerate(grp):
                print(data_row(rec, name if i == 0 else ""))
            print(sep)

# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Generate a Markdown benchmark report from Google Benchmark JSON results."
    )
    parser.add_argument(
        "--results-dir", type=Path, default=DEFAULT_RESULTS_DIR,
        help=f"Root directory to search for benchmark JSON files (default: {DEFAULT_RESULTS_DIR})",
    )
    parser.add_argument(
        "--output", type=Path, default=DEFAULT_OUTPUT,
        help=f"Output Markdown file path (default: {DEFAULT_OUTPUT})",
    )
    parser.add_argument(
        "--notes-file", type=Path, default=DEFAULT_NOTES_FILE,
        help=f"JSON file mapping propagator names to notes (default: {DEFAULT_NOTES_FILE})",
    )
    parser.add_argument(
        "--introduction", type=str, default=None,
        help="Override the default introduction paragraph",
    )
    parser.add_argument(
        "--no-markdown", action="store_true",
        help="Skip writing the Markdown report to disk",
    )
    parser.add_argument(
        "--no-console", action="store_true",
        help="Suppress the console ASCII table",
    )
    parser.add_argument(
        "--stdout", action="store_true",
        help="Write Markdown to stdout instead of a file",
    )
    args = parser.parse_args()

    generator = BenchmarkReportGenerator(
        results_dir  = args.results_dir,
        notes_file   = args.notes_file,
        introduction = args.introduction,
    )

    if not generator.records:
        print("No propagation benchmark results found.", file=sys.stderr)
        sys.exit(0)

    if args.stdout:
        print(generator.generate_report())
    elif not args.no_markdown:
        generator.save_report(args.output)

    if not args.no_console:
        generator.print_console_table()


if __name__ == "__main__":
    main()
