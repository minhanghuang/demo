import math
import numpy as np
from math import cos, sin, pi, radians, sqrt
from scipy.special import fresnel
from scipy.integrate import quad
import matplotlib.pyplot as plt
import itertools
from pynverse import inversefunc


def clamp(a, mi, ma):
    return min(max(a, mi), ma)


def line(x, y, hdg, length, distance):
    distance = clamp(distance, 0, length)
    cx = x + distance * math.cos(hdg)
    cy = y + distance * math.sin(hdg)
    return cx, cy


def arc(x, y, hdg, length, curvature, distance):
    distance = clamp(distance, 0, length)
    radius = 1.0 / curvature
    pi_half = math.pi / 2.0
    cx = x + radius * cos(hdg + pi_half)
    cy = y + radius * sin(hdg + pi_half)
    hdg = hdg + distance * curvature
    cx = cx - radius * cos(hdg + pi_half)
    cy = cy - radius * sin(hdg + pi_half)
    return cx, cy


def spiral(x, y, hdg, length, curve_start, curve_end, distance):

    distance = clamp(distance, 0, length)
    theta = hdg                    # Angle of the start of the curve
    Ltot = length                  # Length of curve
    Rend = 1 / curve_end           # Radius of curvature at end of spiral

    a = 1 / sqrt(2 * Ltot * Rend)  # Scale factor
    distance_scaled = distance * a  # Distance along normalised spiral
    deltay_scaled, deltax_scaled = fresnel(distance_scaled)
    deltax = deltax_scaled / a
    deltay = deltay_scaled / a

    deltax_rot = deltax * cos(theta) - deltay * sin(theta)
    deltay_rot = deltax * sin(theta) + deltay * cos(theta)

    cx = x + deltax_rot
    cy = y + deltay_rot
    return cx, cy


def poly3(s, x, y, hdg, length, a, b, c, d, distance):
    distance = clamp(distance, 0, length)
    u = distance - s
    v = a + b*u + c*u*u + d*u*u*u
    cx = x + u*cos(hdg) + v*(-sin(hdg))
    cy = y + u*sin(hdg) + v*(cos(hdg))
    return cx, cy


def parampoly3(s, x, y, hdg, length, au, bu, cu, du, av, bv, cv, dv, distance):
    distance = clamp(distance, 0, length)
    param = distance - s
    u = au + bu*param + cu*param*param + du*param*param*param
    v = av + bv*param + cv*param*param + dv*param*param*param
    cx = x + u*cos(hdg) + v*(-sin(hdg))
    cy = y + u*sin(hdg) + v*(cos(hdg))
    return cx, cy


def main():

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)

    line_x = 0
    line_y = 0
    line_length = 10

    arc_x = 0
    arc_y = 0
    arc_length = 10
    arc_curvature = 8.6956521739130432e-02

    spiral_x = 0
    spiral_y = 0
    spiral_length = 10
    spiral_start = 0
    spiral_end = 8.6956521739130432e-02

    poly3_x = 0
    poly3_y = 0
    poly3_length = 10
    poly3_s = 0
    poly3_a = 0
    poly3_b = 0
    poly3_c = -1.7226411871382161e-02
    poly3_d = 2.2357975735133454e-04

    param_poly3_x = 0
    param_poly3_y = 0
    param_poly3_length = 10
    param_poly3_s = 0
    param_poly3_au = 0
    param_poly3_bu = 1
    param_poly3_cu =-1.8467144549669900e-05
    param_poly3_du = 1.0724810673786031e-06
    param_poly3_av = 0
    param_poly3_bv = 0
    param_poly3_cv = -1.1349756685716953e-02
    param_poly3_dv = 5.9379781781362532e-03

    line_x_list = []
    line_y_list = []
    arc_x_list = []
    arc_y_list = []
    spiral_x_list = []
    spiral_y_list = []
    poly3_x_list = []
    poly3_y_list = []
    param_poly3_x_list = []
    param_poly3_y_list = []

    for n in range(100):
        x, y = line(
            line_x, line_y,
            3.1415926535897931e+00,
            line_length,
            n/10,
        )
        line_x_list.append(x)
        line_y_list.append(y)

        x, y = arc(
            arc_x, arc_y,
            3.1415926535897931e+00,
            arc_length, arc_curvature,
            n/10,
        )
        arc_x_list.append(x)
        arc_y_list.append(y)

        x, y = spiral(
            spiral_x,
            spiral_y,
            3.1415926535897931e+00,
            spiral_length,
            spiral_start,
            spiral_end,
            n/10,
        )
        spiral_x_list.append(x)
        spiral_y_list.append(y)

        x, y = poly3(
            poly3_s,
            poly3_x,
            poly3_y,
            3.1415926535897931e+00,
            poly3_length,
            poly3_a,
            poly3_b,
            poly3_c,
            poly3_d,
            n/10,
        )
        poly3_x_list.append(x)
        poly3_y_list.append(y)

        x, y = parampoly3(
            param_poly3_s,
            param_poly3_x,
            param_poly3_y,
            3.1415926535897931e+00,
            param_poly3_length,
            param_poly3_au,
            param_poly3_bu,
            param_poly3_cu,
            param_poly3_du,
            param_poly3_av,
            param_poly3_bv,
            param_poly3_cv,
            param_poly3_dv,
            n/10,
        )
        param_poly3_x_list.append(x)
        param_poly3_y_list.append(y)

    ax.plot(line_x_list, line_y_list)
    ax.plot(arc_x_list, arc_y_list)
    ax.plot(spiral_x_list, spiral_y_list)
    ax.plot(poly3_x_list, poly3_y_list)
    ax.plot(param_poly3_x_list, param_poly3_y_list)
    ax.legend(['line', 'arc', 'spiral', 'poloy3', 'parampoly3'])
    plt.show()


if __name__ == "__main__":
    main()
