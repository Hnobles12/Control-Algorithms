class DataLengthNotMatching(Exception):
    def __init__(self):
        self.message = "Data or Time array size does not match buffer size."
        super().__init__(self.message)
