from numpy import arange, array
import pylab

class car:
    '''Basic class to compute positions of a vehicle braking.  Useful to see if two cars will crash.  Need to fix units and do conversions.  Probably seconds for time, mph for speed, and...mph per second for braking?  Whatever is typical.'''
    def __init__(self, pos_init, v_init, brake, time_react = 0):
        #starting position
        self.x0 = pos_init
        #current position
        self.x = self.x0
        #initial velocity
        assert v_init >= 0 #no one going backwards...for now
        self.v0 = v_init
        #current velocity
        self.v = self.v0
        #braking constant (x'' = -k)
        self.k = brake
        #reaction time (0 for lead car), must be > 0, although networked cars could communicate prior to actual braking...
        assert time_react >= 0
        self.tr = time_react
        self.t_stop = self.tr + self.v0 / float(self.k)
    def get_accel(self, time = 0):
        if time < self.tr or time > self.t_stop:
            accel = 0
        else:
            accel = -self.k
        return accel
    def get_velocity(self, time = 0):
        if time < self.tr:
            velocity = self.v0
        elif time <= self.t_stop:
            velocity = self.v0 - self.k * (time - self.tr)
        else:
            velocity = 0
        return velocity
    def get_position(self, time = 0):
        '''Compute position of the vehicle at given time.  This would be a good function to memoize.  I know boiserm does this.'''
        if time < self.tr:
            pos = self.v0 * time
        elif time <= self.t_stop:
            pos = self.v0 * time + self.x0 - 0.5 * self.k * (time - self.tr)**2
        else:
            pos = self.get_position(time = self.t_stop)
        return pos
    def plot(self, start = 0, stop = 10, resolution = .25, new_fig = False):
        '''Make a plot of the position of the vehicle over time.  But don't make a new figure so successive plots should be on top.  Or specify a new_fig'''
        points = array([(t,self.get_position(t)) for t in arange(start,stop,resolution)])
        if new_fig:
            pylab.figure()
        pylab.plot(points[:,0],points[:,1])

def test(pos_init = 3, v_init = 10, brake = 1, time_react = 0, start_time = 0, end_time = 20):
    lead = car(pos_init, v_init, brake, time_react) 
    lead.plot(start_time, end_time)

def crash(pos_init_lead = 3, v_init_lead = 10, brake_lead = 1, time_react_lead = 0, pos_init_back = 0, v_init_back = 10, brake_back = 1, time_react_back = 1, start_time = 0, end_time = 20):
    test(pos_init_lead, v_init_lead, brake_lead, time_react_lead, start_time, end_time)
    test(pos_init_back, v_init_back, brake_back, time_react_back, start_time, end_time)


if __name__ == '__main__':
    crash()
