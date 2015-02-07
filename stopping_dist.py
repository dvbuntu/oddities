from sage.all import *

# sage -ipython

# some vars I like
t, x0, v0, dec0, L0, m0, Fa0, Fb0, x1, v1, acc1, dec1, tr1, m1, Fa1, Fb1 = var('t x0 v0 dec0 L0 m0 Fa0 Fb0 x1 v1 acc1 dec1 tr1 m1 Fa1 Fb1')

# back of the lead car
leadx = dec0 * t**2 / 2 + v0*t + x0 - L0

# front of following car before slowing down
follow_accx = acc1 * t**2 / 2 + v1*t + x1

# t < tr1, back car hasn't noticed yet, still accelerating
h0 = leadx - follow_accx 

# front of following car when starting to slow down
follow_tr1_x = follow_accx.substitute(t=tr1) 

# velocity of following car when starting to slow down
follow_tr1_v = (acc1*tr1 + v1)

# front of following car once starting to slow down
follow_decx = dec1 * (t-tr1)**2 / 2 + follow_tr1_v * (t-tr1) + follow_tr1_v

# tb <= t <= t_stopl, both cars slowing down
h1 = leadx - follow_decx

# time of lead car stopping
ts0 = v0 / dec0

# back of lead car after stopping, final stopping position
x0_fin = leadx.substitute(t=ts0)

# following car velocity
v1_dec = follow_tr1_v + dec1 * (t-tr1)

# time when following car stops
ts1 = v1_dec.solve(t)[0].right()

# front of the following car when stopped
x1_fin = follow_decx.substitute(t=ts1)

# may set up two x positions and solve for when they are equal??
# or solve for t, compare to tr1 (and likewise for other)
# if h0 <= 0 before t = tr1, crashed before we had a chance to stop

# if h1 <= 0 with time between tr1 and ts1, crashed before leader stops

# if x1_fin >= x0_fin, crash after leader stops
