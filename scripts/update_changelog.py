#!/usr/bin/env python3
"""
Update CHANGELOG.md with a new entry when a PR is merged.

Reads PR_NUMBER, PR_TITLE, and PR_LABELS from environment variables and
inserts an entry under the appropriate ### section inside ## [Unreleased].

Label-to-section mapping:
  Added      : feature, enhancement, added
  Changed    : changed, refactor, improvement
  Deprecated : deprecated
  Removed    : removed, breaking
  Fixed      : bug, fix, bugfix, hotfix
  Security   : security, vulnerability
"""

import os
import re
import sys

PR_NUMBER = os.environ.get("PR_NUMBER", "")
PR_TITLE = os.environ.get("PR_TITLE", "").strip()
PR_LABELS_RAW = os.environ.get("PR_LABELS", "")
PR_LABELS = [label.strip().lower() for label in PR_LABELS_RAW.split(",") if label.strip()]

if not PR_NUMBER or not PR_TITLE:
    print("Error: PR_NUMBER and PR_TITLE must be set.", file=sys.stderr)
    sys.exit(1)

SECTION_MAP = {
    "Added":      ["feature", "enhancement", "added"],
    "Changed":    ["changed", "refactor", "improvement"],
    "Deprecated": ["deprecated"],
    "Removed":    ["removed", "breaking"],
    "Fixed":      ["bug", "fix", "bugfix", "hotfix"],
    "Security":   ["security", "vulnerability"],
}


def get_section_title(labels: list[str]) -> str:
    for title, keywords in SECTION_MAP.items():
        for label in labels:
            if any(kw in label for kw in keywords):
                return title
    return "Changed"


section_title = get_section_title(PR_LABELS)
section_header = f"### {section_title}"
new_entry = f"- {PR_TITLE} ([#{PR_NUMBER}](../../pull/{PR_NUMBER}))\n"

changelog_path = os.path.join(os.path.dirname(__file__), "..", "CHANGELOG.md")
changelog_path = os.path.normpath(changelog_path)

with open(changelog_path, "r") as f:
    lines = f.readlines()

# Locate ## [Unreleased]
unreleased_idx = None
for i, line in enumerate(lines):
    if re.match(r"^## \[Unreleased\]", line.strip()):
        unreleased_idx = i
        break

# Find where [Unreleased] block ends (next ## heading or EOF)
end_idx = len(lines)
if unreleased_idx is not None:
    for i in range(unreleased_idx + 1, len(lines)):
        if re.match(r"^## ", lines[i]):
            end_idx = i
            break

if unreleased_idx is None:
    # No [Unreleased] section — insert one after the first line
    insert_block = [
        "\n",
        "## [Unreleased]\n",
        "\n",
        f"{section_header}\n",
        new_entry,
    ]
    lines = lines[:1] + insert_block + lines[1:]
else:
    # Look for the target ### section inside [Unreleased]
    section_idx = None
    for i in range(unreleased_idx + 1, end_idx):
        if lines[i].strip() == section_header:
            section_idx = i
            break

    if section_idx is not None:
        # Insert entry immediately after the section header
        lines.insert(section_idx + 1, new_entry)
    else:
        # Append a new section before end_idx, skipping trailing blank lines
        insert_pos = end_idx
        while insert_pos > unreleased_idx + 1 and lines[insert_pos - 1].strip() == "":
            insert_pos -= 1
        insert_block = [f"\n{section_header}\n", new_entry]
        lines = lines[:insert_pos] + insert_block + lines[insert_pos:]

with open(changelog_path, "w") as f:
    f.writelines(lines)

print(f"Updated CHANGELOG.md: [{section_title}] {PR_TITLE} (#{PR_NUMBER})")
