import elapse

@elapse.export
class BazImuFeatEx(elapse.elements.BaseFeatureExtractor):
    signalType = elapse.data.Signal.IMU

    def analyseSample(self, sample):
        pass

    def features(self):
        return None

    def removeDataBefore(self, time):
        pass

