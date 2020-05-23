from statistics import mean

class PID:
    def __init__(self, data, time, setpoint=0):
        self.data = data
        self.time = time
        self.setpoint = setpoint
        self.err = 0
        self.correction = 0
        self.prop_gain = 0
        self.buffer = 10
        self.ID_gain = 0

    def set_target(self, setpoint):
        self.setpoint = setpoint
    
    def set_buffer(self, buffer):
        self.buffer = buffer
    
    def set_Pgain(self, gain):
        self.prop_gain = gain

    def update(data, time):
        data_size = len(data)
        time_size = len(time)
        
        if (data_size != self.buffer) or (time_size != self.buffer):
            raise Exception("Error: Data or Time arrag size does not match buffer size.")
        '''
        if data_size > buffer:
            data = data[data_size-buffer:]

        if time_size > buffer:
            time = time[time_size-buffer]
        '''
        self.data = data
        self.time = time

        self.err = self.setpoint-mean(data)
        self.ID_gain = self.Integrate() + self.Derivative()
        self.correction = self.prop_gain*(err+ID_gain*err)
        
        return self.correction

    def Integrate(self):
        val, num = 0,0

        for i in range(0,buffer-1):
            num = (self.time[i+1]-self.time[i])*(self.data[i+1]+self.data[i])
            val += num
        val *= 0.5
        return val

    def Derivative(self):
        der = []
        diff, avg = 0,0

        for i in range(0, buffer-1):
            diff = (self.data[i+1]-self.data[i])/(self.time[i+1]-self.time[i])
            der.append(diff)
        
        avg = mean(der)
        return avg
     