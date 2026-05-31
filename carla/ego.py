import carla
import random
import time
import os
import sys
import json
import math

# try to find CARLA agents module
_api_candidates = [
    '/opt/carla-simulator/PythonAPI/carla',
    os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'PythonAPI', 'carla'),
    os.path.join(os.path.dirname(os.path.abspath(__file__)), 'agents', '..'),
]
for _p in _api_candidates:
    _p = os.path.normpath(_p)
    if os.path.isdir(_p) and _p not in sys.path:
        sys.path.insert(0, _p)

try:
    from agents.navigation.behavior_agent import BehaviorAgent
    _has_behavior_agent = True
    print('BehaviorAgent loaded successfully')
except ImportError:
    _has_behavior_agent = False
    print('BehaviorAgent not available, will use Traffic Manager autopilot')

client = carla.Client("127.0.0.1", 2000)
client.set_timeout(10.0)

world = client.get_world()
carla_map = world.get_map()
bp_lib = world.get_blueprint_library()

vehicle_bps = list(bp_lib.filter("vehicle.*"))
if not vehicle_bps:
    raise RuntimeError("No vehicle blueprints found")

for bp in vehicle_bps:
    if "vehicle.mini.cooper_s" in bp.id:
        vehicle_bp = bp
        break
else:
    vehicle_bp = vehicle_bps[0]

print('Using blueprint:', vehicle_bp.id)

topology = carla_map.get_topology()

visited_lanes = set()
lane_paths = []

for entry_wp, _ in topology:
    if entry_wp.lane_type != carla.LaneType.Driving:
        continue

    lane_key = (entry_wp.road_id, entry_wp.section_id, entry_wp.lane_id)
    if lane_key in visited_lanes:
        continue

    visited_lanes.add(lane_key)
    path = [entry_wp] + entry_wp.next_until_lane_end(2.0)
    lane_paths.append((lane_key, path))

if not lane_paths:
    raise RuntimeError("No driving lanes found")

vehicle = None
# attempt safe spawn to avoid collision
try:
    vehicle_bp.set_attribute('role_name', 'autopilot')
except Exception:
    pass

spawn_tf = lane_paths[0][1][0].transform
vehicle = world.try_spawn_actor(vehicle_bp, spawn_tf)
if vehicle is None:
    forward = spawn_tf.get_forward_vector()
    found = False
    for dz in (0.5, 1.0):
        for dist in (0.0, 2.0, -2.0, 4.0, -4.0, 6.0, -6.0):
            test_loc = carla.Location(
                x=spawn_tf.location.x - forward.x * dist,
                y=spawn_tf.location.y - forward.y * dist,
                z=spawn_tf.location.z + dz
            )
            test_tf = carla.Transform(test_loc, spawn_tf.rotation)
            vehicle = world.try_spawn_actor(vehicle_bp, test_tf)
            if vehicle:
                found = True
                break
        if found:
            break

if vehicle is None:
    spawn_points = carla_map.get_spawn_points()
    random.shuffle(spawn_points)
    for sp in spawn_points:
        vehicle = world.try_spawn_actor(vehicle_bp, sp)
        if vehicle:
            break

if vehicle is None:
    raise RuntimeError("Failed to spawn vehicle without collision")

vehicle.set_simulate_physics(True)

spectator = world.get_spectator()

try:
    # try to load a precomputed route (route_<map>.json) exported by build_route.py
    map_name = carla_map.name.split('/')[-1]
    route_path = 'route_{}.json'.format(map_name)
    if not os.path.exists(route_path) and os.path.exists('route.json'):
        route_path = 'route.json'  # fallback for old filename
    route = None
    if os.path.exists(route_path):
        try:
            with open(route_path, 'r') as f:
                route = json.load(f)
            if not route.get('waypoints'):
                print('{} found but contains no waypoints, ignoring'.format(route_path))
                route = None
            else:
                print('Loaded {} with {} waypoints'.format(route_path, len(route['waypoints'])))
        except Exception as e:
            print('Failed to read {}: {}'.format(route_path, e))
            route = None

    tm_port = 8000
    traffic_manager = client.get_trafficmanager(tm_port)

    # smoothing parameters for spectator camera
    pos_alpha = 0.12
    yaw_alpha = 0.20
    chase_distance = 6.0
    height_offset = 2.0
    prev_spec_tf = [spectator.get_transform()]

    def update_spectator():
        tf = vehicle.get_transform()
        fwd = tf.get_forward_vector()
        desired_loc = carla.Location(
            x=tf.location.x - fwd.x * chase_distance,
            y=tf.location.y - fwd.y * chase_distance,
            z=tf.location.z + height_offset,
        )
        pl = prev_spec_tf[0].location
        new_loc = carla.Location(
            x=pl.x + (desired_loc.x - pl.x) * pos_alpha,
            y=pl.y + (desired_loc.y - pl.y) * pos_alpha,
            z=pl.z + (desired_loc.z - pl.z) * pos_alpha,
        )
        py = prev_spec_tf[0].rotation.yaw
        dy = tf.rotation.yaw - py
        if dy > 180.0: dy -= 360.0
        if dy < -180.0: dy += 360.0
        new_yaw = py + dy * yaw_alpha
        prev_spec_tf[0] = carla.Transform(new_loc, carla.Rotation(pitch=-10.0, yaw=new_yaw, roll=0.0))
        spectator.set_transform(prev_spec_tf[0])

    if route and _has_behavior_agent:
        # ---- BehaviorAgent route following ----
        agent = BehaviorAgent(vehicle, behavior='normal')

        raw_wps = route['waypoints']

        # sample sparse targets every ~60 m so BehaviorAgent can plan between them
        targets = [raw_wps[0]]
        acc = 0.0
        for i in range(1, len(raw_wps)):
            dx = raw_wps[i]['x'] - raw_wps[i - 1]['x']
            dy = raw_wps[i]['y'] - raw_wps[i - 1]['y']
            acc += math.hypot(dx, dy)
            if acc >= 60.0:
                targets.append(raw_wps[i])
                acc = 0.0
        if targets[-1] is not raw_wps[-1]:
            targets.append(raw_wps[-1])

        print('Navigating through {} sparse waypoints via BehaviorAgent'.format(len(targets)))

        for t_idx, twp in enumerate(targets):
            dest = carla.Location(x=float(twp['x']), y=float(twp['y']), z=float(twp.get('z', 0.0)))
            agent.set_destination(dest)
            print('Target {}/{} -> ({:.1f}, {:.1f})'.format(t_idx + 1, len(targets), dest.x, dest.y))

            while not agent.done():
                world.wait_for_tick(0.5)
                control = agent.run_step()
                vehicle.apply_control(control)
                update_spectator()

        print('Completed BehaviorAgent route following')

        # loop back continuously with autopilot after coverage
        vehicle.set_autopilot(True, tm_port)

    else:
        # ---- fallback: Traffic Manager autopilot (no route.json or no BehaviorAgent) ----
        if route and not _has_behavior_agent:
            print('BehaviorAgent unavailable; using Traffic Manager autopilot (no route enforcement)')
        vehicle.set_autopilot(True, tm_port)
        print('Autopilot enabled (Traffic Manager port {})'.format(tm_port))

    # keep spectator following in all cases
    while True:
        world.wait_for_tick(0.5)
        update_spectator()

except KeyboardInterrupt:
    print("Interrupted by user")

finally:
    vehicle.destroy()
