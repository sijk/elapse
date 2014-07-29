import elapse

class BazEegFeatEx(elapse.elements.BaseFeatureExtractor):
    signalType = elapse.Signal.EEG

    def analyseSample(self, sample):
        pass

    def features(self):
        return None

    def removeDataBefore(self, time):
        pass

