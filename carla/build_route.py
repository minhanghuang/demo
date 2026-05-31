#!/usr/bin/env python3
"""Build a long loop route from an exported topology JSON.

This script reads topology.json (created by export_topology.py) and greedily stitches
lane segments into a single ordered list of waypoints. The result is saved as route.json.

Usage:
  python3 build_route.py --in topology.json --out route.json --max-gap 80.0 --close-loop
"""

import argparse
import json
import math
import time


def parse_args():
    p = argparse.ArgumentParser(description='Build route from exported topology')
    p.add_argument('--in', dest='infile', default=None, help='Input topology JSON (default: topology_<map>.json, auto-detected)')
    p.add_argument('--out', default=None, help='Output route JSON (default: route_<map>.json, auto-detected)')
    p.add_argument('--map', default=None, help='Map name override (used when auto-detecting filenames)')
    p.add_argument('--max-gap', default=80.0, type=float, help='Max distance (m) considered "close" when stitching')
    p.add_argument('--close-loop', action='store_true', help='Try to append start to close the loop')
    return p.parse_args()


def dist(a, b):
    dx = a['x'] - b['x']
    dy = a['y'] - b['y']
    dz = a['z'] - b['z']
    return math.hypot(math.hypot(dx, dy), dz)


def reverse_waypoints(wps):
    # reverse order and flip yaw by 180 degrees
    rev = []
    for wp in reversed(wps):
        yaw = wp.get('yaw', 0.0) + 180.0
        if yaw > 180.0:
            yaw -= 360.0
        rev.append({
            'x': wp['x'], 'y': wp['y'], 'z': wp['z'],
            'yaw': yaw, 'pitch': wp.get('pitch', 0.0), 'roll': wp.get('roll', 0.0)
        })
    return rev


def main():
    args = parse_args()

    # resolve input file
    import glob as _glob
    infile = args.infile
    if infile is None:
        if args.map:
            infile = 'topology_{}.json'.format(args.map)
        else:
            candidates = sorted(_glob.glob('topology_*.json'))
            if candidates:
                infile = candidates[0]
                print('Auto-detected input: {}'.format(infile))
            else:
                raise SystemExit('No topology JSON found. Run export_topology.py first, or pass --in.')

    with open(infile, 'r') as f:
        data = json.load(f)

    # resolve map name for output filename
    map_name = args.map or data.get('meta', {}).get('map') or 'unknown'
    out_path = args.out if args.out else 'route_{}.json'.format(map_name)

    lanes = data.get('lanes', [])
    if not lanes:
        raise SystemExit('No lanes found in {}'.format(infile))

    # prepare lane summary with start/end
    summary = []
    for i, lane in enumerate(lanes):
        wps = lane.get('waypoints', [])
        if not wps:
            continue
        start = wps[0]
        end = wps[-1]
        summary.append({
            'index': i,
            'start': start,
            'end': end,
            'length': float(lane.get('length_m', 0.0)),
            'waypoints': wps
        })

    if not summary:
        raise SystemExit('No usable lane waypoints')

    # start from the longest lane (heuristic)
    start_idx = max(range(len(summary)), key=lambda i: summary[i]['length'])
    visited = set()
    route_wps = []

    cur = summary[start_idx]
    route_wps.extend(cur['waypoints'])
    visited.add(cur['index'])
    cur_end = route_wps[-1]

    total = len(summary)
    while len(visited) < total:
        best = None
        best_cost = float('inf')
        best_rev = False
        for s in summary:
            if s['index'] in visited:
                continue
            d_start = dist(cur_end, s['start'])
            d_end = dist(cur_end, s['end'])
            if d_start < best_cost:
                best_cost = d_start
                best = s
                best_rev = False
            if d_end < best_cost:
                best_cost = d_end
                best = s
                best_rev = True

        if best is None:
            break

        if best_rev:
            next_wps = reverse_waypoints(best['waypoints'])
        else:
            # ensure canonical dict entries
            next_wps = [ { 'x': float(w['x']), 'y': float(w['y']), 'z': float(w['z']),
                           'yaw': float(w.get('yaw', 0.0)), 'pitch': float(w.get('pitch', 0.0)), 'roll': float(w.get('roll', 0.0)) }
                        for w in best['waypoints'] ]

        # if the first waypoint is essentially the same as last, skip duplicate
        if dist(route_wps[-1], next_wps[0]) < 0.05:
            route_wps.extend(next_wps[1:])
        else:
            # allow a gap; route consumer can choose to teleport or drive there
            route_wps.extend(next_wps)

        visited.add(best['index'])
        cur_end = route_wps[-1]

    # attempt to close loop if requested
    if args.close_loop and len(route_wps) > 1:
        gap = dist(route_wps[-1], route_wps[0])
        print('Closing loop: gap from end to start = {:.2f} m'.format(gap))
        # simply append the start waypoint to close; consumer may choose to teleport or drive
        if gap > 0.05:
            route_wps.append(route_wps[0])

    out = {
        'meta': {
            'map': map_name,
            'generated_at': time.time(),
            'lanes_covered': len(visited),
            'total_lanes': total
        },
        'waypoints': route_wps
    }

    with open(out_path, 'w') as f:
        json.dump(out, f, indent=2)

    print('Route written to {} (waypoints: {}, lanes_covered: {}/{})'.format(out_path, len(route_wps), len(visited), total))


if __name__ == '__main__':
    main()
