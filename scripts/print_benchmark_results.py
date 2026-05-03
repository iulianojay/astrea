import json, glob, sys, re
from itertools import groupby

# --- Column widths ---
WN=16; WG=4; WP=5; WTS=[5,6,7]; WR=14; WC=13; WI=11
GCOLS = [2, 20, 70]
PCOLS = [('Drag',1), ('Nbdy',2), ('SRP',4), ('All',7)]
TCOLS = [97, 1440, 10080]
all_widths = [WN] + [WG]*3 + [WP]*4 + WTS + [WR, WC, WI]

g_span = 3*WG + 2     # gravity group span  (14)
p_span = 4*WP + 3     # pert group span     (23)
t_span = sum(WTS) + 2 # time group span     (20)

sep   = '+' + '+'.join('-'*w for w in all_widths) + '+'
thick = '+' + '+'.join('='*w for w in all_widths) + '+'

def row_str(cells):
    return '|' + '|'.join(cells) + '|'

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
    for gv in GCOLS:             c.append(f'{gv:^{WG}}')
    for pn, _ in PCOLS:          c.append(f'{pn:^{WP}}')
    for tv, w in zip(TCOLS, WTS): c.append(f'{tv:^{w}}')
    c.append(f'{"(ms)":>{WR}}')
    c.append(f'{"(ms)":>{WC}}')
    c.append(f'{"count":>{WI}}')
    return row_str(c)

def data_row(rec, label):
    eom = rec['eom']
    c = [f' {label:<{WN-1}}']
    for gv in GCOLS:
        c.append(('-' if eom < 2 else 'x' if rec['g'] == gv else '').center(WG))
    for _, pf in PCOLS:
        c.append(('-' if eom < 2 else 'x' if rec['pf'] == pf else '').center(WP))
    for tv, w in zip(TCOLS, WTS):
        c.append(('x' if rec['t'] == tv else '').center(w))
    c.append(f' {rec["real"]:>{WR-2}.3f} ')
    c.append(f' {rec["cpu"]:>{WC-2}.3f} ')
    c.append(f' {rec["iters"]:>{WI-2}d} ')
    return row_str(c)

# --- Load results ---
result_files = sorted(glob.glob('./install/**/benchmarks/benchmark_results/*.json', recursive=True))
records = []
for fpath in result_files:
    try:
        with open(fpath) as f:
            data = json.load(f)
    except Exception:
        continue
    for bm in data.get('benchmarks', []):
        if bm.get('run_type') == 'aggregate':
            continue
        if 'BM_Propagation' not in bm.get('name', ''):
            continue
        nm = bm['name']
        p = {}
        for part in nm.split('/')[1:]:
            m = re.match(r'(\w+):(-?\d+)', part)
            if m:
                p[m.group(1)] = int(m.group(2))
        records.append(dict(
            eom=p.get('eom', 0), name=bm.get('label', '?'),
            t=p.get('prop_time_min', 0), g=p.get('gravity', 0), pf=p.get('perturb', 0),
            real=bm.get('real_time', 0), cpu=bm.get('cpu_time', 0), iters=bm.get('iterations', 0),
        ))

if not records:
    print("No propagation benchmark results found.")
    sys.exit(0)

records.sort(key=lambda r: (r['eom'], r['g'], r['pf'], r['t']))

# --- Print table ---
print(thick)
print(header1())
print(sep)
print(header2())
print(thick)
for _, grp in groupby(records, key=lambda r: r['eom']):
    grp = list(grp)
    name = grp[0]['name']
    for i, rec in enumerate(grp):
        print(data_row(rec, name if i == 0 else ''))
    print(sep)
