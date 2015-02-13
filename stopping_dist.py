from sage.all import *

# sage -ipython

# some vars I like
t, x0, v0, dec0, L0, m0, Fa0, Fb0, x1, v1, acc1, dec1, tr1, m1, Fa1, Fb1 = var('t x0 v0 dec0 L0 m0 Fa0 Fb0 x1 v1 acc1 dec1 tr1 m1 Fa1 Fb1')

# initial headway
h_init = x0 - L0 - x1

# back of the lead car
leadx = dec0 * t**2 / 2 + v0*t + x0 - L0

# front of following car before slowing down
follow_accx = acc1 * t**2 / 2 + v1*t + x1

# t < tr1, back car hasn't noticed yet, still accelerating
h0 = leadx - follow_accx

# solve h0 for h_init
solve0 = h0 - h_init

dhdt0 = solve0.differentiate(t)
# t_max0 must occur between 0 and tr1
t_max0 = dhdt0.solve(t)[0].right()

h_max0 = [-1*solve0.substitute(t=0), -1*solve0.substitute(t=t_max0), -1*solve0.substitute(t=tr1)]

# front of following car when starting to slow down
follow_tr1_x = follow_accx.substitute(t=tr1) 

# velocity of following car when starting to slow down
follow_tr1_v = (acc1*tr1 + v1)

# front of following car once starting to slow down
follow_decx = dec1 * (t-tr1)**2 / 2 + follow_tr1_v * (t-tr1) + follow_tr1_x 

# tb <= t <= t_stopl, both cars slowing down
h1 = leadx - follow_decx

# time of lead car stopping
ts0 = v0 / dec0

# solve h0 for h_init
solve1 = h1 - h_init

dhdt1 = solve1.differentiate(t)
# t_max1 must occur between tr1 and ts0 (careful about divide by zero, that means huge scale t, so throw out
t_max1 = dhdt1.solve(t)[0].right()

# don't need to compute at lower bound, that's already done
h_max1 = [-1*solve1.substitute(t=t_max1), -1*solve1.substitute(t=ts0)]

# following car velocity
v1_dec = follow_tr1_v + dec1 * (t-tr1)

# time when following car stops
ts1 = v1_dec.solve(t)[0].right()
# ts1 = -((acc1 - dec1)*tr1 + v1)/dec1

# t_stopl <= t <= t_stopf
h2 = leadx.substitute(t=ts0) - follow_decx

# solve h0 for h_init
solve2 = h2 - h_init

dhdt2 = solve2.differentiate(t)
# t_max1 must occur between t
t_max2 = dhdt2.solve(t)[0].right()

# don't need to compute at lower bound, that's already done
h_max2 = [-1*solve2.substitute(t=t_max2), -1*solve2.substitute(t=ts1)]

# back of lead car after stopping, final stopping position
x0_fin = leadx.substitute(t=ts0)
# x0_fin = -L0 + 3/2*v0^2/dec0 + x0

# front of the following car when stopped
x1_fin = follow_decx.substitute(t=ts1)
# x1_fin = 1/2*dec1*(tr1 + ((acc1 - dec1)*tr1 + v1)/dec1)^2 - (acc1*tr1 + v1)*(tr1 + ((acc1 - dec1)*tr1 + v1)/dec1) + acc1*tr1 + v1

# may set up two x positions and solve for when they are equal??
# or solve for t, compare to tr1 (and likewise for other)
# if h0 <= 0 before t = tr1, crashed before we had a chance to stop
h0_crash = h0.solve(t)
# two possibilities
# if speeds are equal or follower is faster, clearly the first is false
# t == (v0 - v1 - sqrt(-2*L0*(acc1 - dec0) + v0^2 - 2*v0*v1 + v1^2 + 2*(acc1 - dec0)*x0 - 2*(acc1 - dec0)*x1))/(acc1 - dec0)
# if leader is much faster, obviously follower has plenty of time to react
# t == (v0 - v1 + sqrt(-2*L0*(acc1 - dec0) + v0^2 - 2*v0*v1 + v1^2 + 2*(acc1 - dec0)*x0 - 2*(acc1 - dec0)*x1))/(acc1 - dec0)

# if h1 <= 0 with time between tr1 and ts1, crashed before leader stops
h1_crash = h1.solve(t)
# t == ((acc1 - dec1)*tr1 - v0 + v1 - sqrt((acc1^2 - 2*acc1*dec0 + dec0*dec1)*tr1^2 - 2*(acc1 - dec1)*tr1*v0 + 2*L0*(dec0 - dec1) + 2*(acc1*dec0 - acc1*dec1)*tr1 + v0^2 + 2*((acc1 - dec0)*tr1 + dec0 - dec1 - v0)*v1 + v1^2 - 2*(dec0 - dec1)*x0))/(dec0 - dec1)
# t == ((acc1 - dec1)*tr1 - v0 + v1 + sqrt((acc1^2 - 2*acc1*dec0 + dec0*dec1)*tr1^2 - 2*(acc1 - dec1)*tr1*v0 + 2*L0*(dec0 - dec1) + 2*(acc1*dec0 - acc1*dec1)*tr1 + v0^2 + 2*((acc1 - dec0)*tr1 + dec0 - dec1 - v0)*v1 + v1^2 - 2*(dec0 - dec1)*x0))/(dec0 - dec1)

# if x1_fin >= x0_fin, crash after leader stops
