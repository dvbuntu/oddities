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
follow_tr1_x = follow_accx 

# velocity of following car when starting to slow down


# front of following car once starting to slow down


# tb <= t <= t_stopl, both cars slowing down
h1 = leadx - (dec1*(t-tr1)^2 /2 +  (acc1 * t^2 / 2 + v1*t + x1))

