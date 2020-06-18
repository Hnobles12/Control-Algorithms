class On_Off:
    def __init__(self, SP=0, TOL=10e-3):
        self.SP = SP
        self.TOL = TOL
    
    def set_setpoint(self, SP):
        self.SP = SP

    def set_tolerance(self, TOL):
        self.TOL = TOL
    
    def get_correction(value):
        err = abs(self.SP - value)
        if err > self.TOL:
            return True
        else:
            return False