import elapse

class BazImuFeatEx(elapse.elements.BaseFeatureExtractor):
    signalType = elapse.Signal.IMU

    def analyseSample(self, sample):
        pass

    def features(self):
        return None

    def removeDataBefore(self, time):
        pass

