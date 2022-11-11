import math
import numpy as np
from math import cos, sin, pi, radians, sqrt
from scipy.special import fresnel
from scipy.integrate import quad
import matplotlib.pyplot as plt
import itertools
from pynverse import inversefunc


def line(distance, x, y, hdg):
    xcoord = x + distance * cos(hdg)
    ycoord = y + distance * sin(hdg)
    return xcoord, ycoord


def arc(distance, x, y, hdg, length, curvature):
    hdg = hdg - math.pi / 2.0
    a = 2.0 / curvature * sin(distance * curvature / 2.0)
    alpha = (math.pi - distance * curvature) / 2.0 - hdg
    xcoord = -1 * a * cos(alpha) + x
    ycoord = a * sin(alpha) + y
    return xcoord, ycoord


def spiral(distance, x, y, hdg, length, curvEnd):
    '''Interpolate for a spiral centred on the origin'''

    # s doesn't seem to be needed...
    theta = hdg                    # Angle of the start of the curve
    Ltot = length                  # Length of curve
    Rend = 1 / curvEnd             # Radius of curvature at end of spiral

    # Rescale, compute and unscale
    a = 1 / sqrt(2 * Ltot * Rend)  # Scale factor
    distance_scaled = distance * a  # Distance along normalised spiral
    deltay_scaled, deltax_scaled = fresnel(distance_scaled)
    deltax = deltax_scaled / a
    deltay = deltay_scaled / a

    # deltax and deltay give coordinates for theta=0
    deltax_rot = deltax * cos(theta) - deltay * sin(theta)
    deltay_rot = deltax * sin(theta) + deltay * cos(theta)

    # Spiral is relative to the starting coordinates
    xcoord = x + deltax_rot
    ycoord = y + deltay_rot

    return xcoord, ycoord


class Poly3:
    '''Cubic polynomial.'''

    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def eval_at(self, x):
        return self.a + self.b * x + self.c * x ** 2 + self.d * x ** 3

    def grad_at(self, x):
        return self.b + 2 * self.c * x + 3 * self.d * x ** 2


class Curve:
    ''' Geometric elements which compose road reference lines.
    See the OpenDRIVE Format Specification for coordinate system details.'''

    def __init__(self, x0, y0, hdg, length):
        self.x0 = x0
        self.y0 = y0
        self.hdg = hdg    # In radians counterclockwise, 0 at positive x-axis.
        self.cos_hdg, self.sin_hdg = math.cos(hdg), math.sin(hdg)
        self.length = length

    def to_points(self, num, extra_points=[]):
        '''Sample NUM evenly-spaced points from curve.

        Points are tuples of (x, y, s) with (x, y) absolute coordinates
        and s the arc length along the curve. Additional points at s values in
        extra_points are included if they are contained in the curve (unless
        they are extremely close to one of the equally-spaced points).
        '''
        s_vals = []
        extras = itertools.chain(extra_points, itertools.repeat(float('inf')))
        next_extra = next(extras)
        last_s = 0
        for s in np.linspace(0, self.length, num=num):
            while next_extra <= s:
                if last_s + 1e-6 < next_extra < s - 1e-6:
                    s_vals.append(next_extra)
                next_extra = next(extras)
            s_vals.append(s)
            last_s = s
        return [self.point_at(s) for s in s_vals]

    def point_at(self, s):
        '''Get an (x, y, s) point along the curve at the given s coordinate.'''
        return

    def rel_to_abs(self, point):
        '''Convert from relative coordinates of curve to absolute coordinates.
        I.e. rotate counterclockwise by self.hdg and translate by (x0, x1).'''
        x, y, s = point
        return (self.x0 + self.cos_hdg * x - self.sin_hdg * y,
                self.y0 + self.sin_hdg * x + self.cos_hdg * y,
                s)


class Cubic(Curve):
    '''A curve defined by the cubic polynomial a + bu + cu^2 + du^3.
    The curve starts at (X0, Y0) in direction HDG, with length LENGTH.'''

    def __init__(self, x0, y0, hdg, length, a, b, c, d):
        super().__init__(x0, y0, hdg, length)
        self.poly = Poly3(a, b, c, d)

    def arclength(self, u):
        def d_arc(x): return np.sqrt(1 + self.poly.grad_at(x) ** 2)
        return quad(d_arc, 0, u)[0]

    def point_at(self, s):
        u = float(inversefunc(self.arclength, s))
        pt = (s, self.poly.eval_at(u), s)
        return self.rel_to_abs(pt)

class ParamCubic(Curve):
    ''' A curve defined by the parametric equations
    u = a_u + b_up + c_up^2 + d_up^3,
    v = a_v + b_vp + c_vp^2 + d_up^3,
    with p in [0, p_range].
    The curve starts at (X0, Y0) in direction HDG, with length LENGTH.'''
    def __init__(self, x0, y0, hdg, length,
                 au, bu, cu, du, av, bv, cv, dv, p_range=1):
        super().__init__(x0, y0, hdg, length)
        self.u_poly = Poly3(au, bu, cu, du)
        self.v_poly = Poly3(av, bv, cv, dv)
        self.p_range = p_range if p_range else 1

    def arclength(self, p):
        d_arc = lambda x: math.hypot(self.u_poly.grad_at(x),
                                     self.v_poly.grad_at(x))
        return quad(d_arc, 0, p)[0]

    def point_at(self, s):
        p = float(inversefunc(self.arclength, s))
        pt = (self.u_poly.eval_at(p), self.v_poly.eval_at(p), s)
        return self.rel_to_abs(pt)

def main():

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)

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

    poly3 = Cubic(x0=1.3818843120268710e+01,
                  y0=-8.5806245507238330e+00,
                  hdg=-3.8812339311141031e-02,
                  length=3.0383609851696789e+01,
                  a=0,
                  b=0,
                  c=7.8270095403552599e-03,
                  d=-1.2981379520556725e-04
                  )
    param_poly3 = ParamCubic(x0=1.3818843120268710e+01,
                  y0=-8.5806245507238330e+00,
                  hdg=5.6427043078325168e-01,
                  length=1.0005839175793547e+00,
                  au=0.0000000000000000e+00,
                  bu=1.0000000000000000e+00,
                  cu=-2.1071808121856253e-03,
                  du=2.4773524493628996e-04,
                  av=0.0000000000000000e+00,
                  bv=0.0000000000000000e+00,
                  cv=1.6676606691028689e-01,
                  dv=-1.6666874609951038e-01
                  )

    for n in range(100):
        x, y = line(
            n/10,
            2.4122510649679477e+01,
            -7.0000000000000000e+00,
            3.1415926535897931e+00
        )
        line_x_list.append(x)
        line_y_list.append(y)

        x, y = arc(
            distance=n/10,
            x=1.3818843120268710e+01,
            y=-8.5806245507238330e+00,
            hdg=-2.6841257348764787e+00,
            length=7.5424186276494236e+00,
            curvature=8.6956521739130432e-02
        )
        arc_x_list.append(x)
        arc_y_list.append(y)

        x, y = spiral(
            n/10,
            2.4122510649679477e+01,
            -7.0000000000000000e+00,
            3.1415926535897931e+00,
            1.0521739130434783e+01,
            8.6956521739130432e-02
        )
        spiral_x_list.append(x)
        spiral_y_list.append(y)

        x, y , _ = poly3.point_at(n/10)
        poly3_x_list.append(x)
        poly3_y_list.append(y)

        x, y , _ = param_poly3.point_at(n/10)
        param_poly3_x_list.append(x)
        param_poly3_y_list.append(y)

    ax.plot(line_x_list, line_y_list)
    ax.plot(arc_x_list, arc_y_list)
    ax.plot(spiral_x_list, spiral_y_list)
    ax.plot(poly3_x_list, poly3_y_list)
    ax.plot(param_poly3_x_list, param_poly3_y_list)
    ax.legend(['line', 'arc', 'spiral', 'poloy3', 'param_poly3'])
    plt.show()


if __name__ == "__main__":
    main()
