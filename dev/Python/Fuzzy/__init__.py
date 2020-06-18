class Fuzzy:
    def __init__(self, bounds=[0,0], setpoint=0, invert=False):
        self.range = bounds
        self.SP = setpoint
        self.inverse = invert
        self.tot_range = abs(self.range[1]-self.range[0])
            
    def set_setpoint(self,setpoint):
        self.SP = setpoint
    
    def set_bounds(self, bounds):
        self.range = bounds
        self.tot_range = abs(self.range[1]-self.range[0])
    
    def get_correction(self, value):
        value = abs(value/self.tot_range)
        if inverse is True:
            return 1 - value
        else:
            return value