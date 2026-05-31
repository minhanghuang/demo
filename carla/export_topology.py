#!/usr/bin/env python3
"""Export CARLA map topology to JSON.

Saves a JSON file with structure:
{
  "meta": { ... },
  "lanes": [
    { "road_id": int, "section_id": int, "lane_id": int,
      "lane_type": str, "lane_change": str,
      "length_m": float,
      "waypoints": [ {x,y,z,yaw,pitch,roll}, ... ]
    }, ...
  ]
}

Usage: python3 export_topology.py --out topology.json --spacing 2.0
"""

import argparse
import json
import math
import time

try:
    import carla
except Exception as e:
    raise SystemExit("This script must be run where the CARLA Python API is available: {}".format(e))


def parse_args():
    p = argparse.ArgumentParser(description="Export CARLA map topology to JSON")
    p.add_argument('--host', default='127.0.0.1', help='CARLA host')
    p.add_argument('--port', default=2000, type=int, help='CARLA port')
    p.add_argument('--out', default=None, help='Output JSON path (default: topology_<map>.json)')
    p.add_argument('--spacing', default=2.0, type=float, help='Waypoint spacing for next_until_lane_end')
    p.add_argument('--only-driving', action='store_true', help='Export only driving lanes')
    return p.parse_args()


def wp_to_dict(wp):
    t = wp.transform
    loc = t.location
    rot = t.rotation
    return {
        'x': float(loc.x), 'y': float(loc.y), 'z': float(loc.z),
        'yaw': float(rot.yaw), 'pitch': float(rot.pitch), 'roll': float(rot.roll)
    }


def euclid(a, b):
    dx = a['x'] - b['x']
    dy = a['y'] - b['y']
    dz = a['z'] - b['z']
    return math.hypot(math.hypot(dx, dy), dz)


def main():
    args = parse_args()
    client = carla.Client(args.host, args.port)
    client.set_timeout(10.0)
    world = client.get_world()
    carla_map = world.get_map()
    map_name = carla_map.name.split('/')[-1]  # e.g. "Town01"

    out_path = args.out if args.out else 'topology_{}.json'.format(map_name)
    print('Map: {}  ->  {}'.format(map_name, out_path))

    topology = carla_map.get_topology()
    lanes = []

    for entry_wp, _ in topology:
        if args.only_driving and entry_wp.lane_type != carla.LaneType.Driving:
            continue
        try:
            path_wps = [entry_wp] + entry_wp.next_until_lane_end(args.spacing)
        except Exception as e:
            # if expansion fails, skip this lane
            print('Warning: failed to expand lane starting at {}: {}'.format(entry_wp.transform.location, e))
            continue

        waypoints = [wp_to_dict(wp) for wp in path_wps]
        length = 0.0
        for i in range(1, len(waypoints)):
            length += euclid(waypoints[i - 1], waypoints[i])

        lanes.append({
            'road_id': int(entry_wp.road_id),
            'section_id': int(entry_wp.section_id),
            'lane_id': int(entry_wp.lane_id),
            'lane_type': str(entry_wp.lane_type),
            'lane_change': str(entry_wp.lane_change),
            'length_m': float(length),
            'waypoints': waypoints
        })

    out = {
        'meta': {
            'map': map_name,
            'exported_at': time.time(),
            'num_lanes': len(lanes)
        },
        'lanes': lanes
    }

    with open(out_path, 'w') as f:
        json.dump(out, f, indent=2)

    print('Exported {} lanes to {}'.format(len(lanes), out_path))


if __name__ == '__main__':
    main()
