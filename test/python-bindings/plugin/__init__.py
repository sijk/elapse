import elapse
try:
    from flexmock import flexmock, flexmock_teardown
except ImportError:
    def flexmock(*args, **kwargs):
        raise ImportError, 'You need to install the "flexmock" package to run this test'
    def flexmock_teardown(): pass


def test(fn):
    '''
    A decorator which creates an elapse element class whose constructor
    will call the given function. To create a test, use this decorator on
    a function which raises an exception if it fails:

        >>> @test
        ... def TwoPlusTwo():
        ...     x = 2 + 2
        ...     assert x == 4, "Python can't add"
    '''
    class Test(elapse.elements.FeatureExtractor):
        testname = fn.__name__

        def __init__(self):
            super(Test, self).__init__()
            print '[ RUN      ]', self.testname
            try:
                fn()
                flexmock_teardown()
            except Exception, e:
                print '[  FAILED  ]', e
                raise
            else:
                print '[       OK ]'

    # Name the class according to the name of the function
    testClass = type('test_' + fn.__name__, (Test,), {})
    elapse.export(testClass)
    return testClass


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

from elapse.data import Signal

@test
def SignalTypes():
    assert Signal.toString(Signal.EEG) == 'EEG'
    assert Signal.toString(Signal.VIDEO) == 'VIDEO'
    assert Signal.toString(Signal.IMU) == 'IMU'

    assert Signal.fromString('EEG') == Signal.EEG
    assert Signal.fromString('VIDEO') == Signal.VIDEO
    assert Signal.fromString('IMU') == Signal.IMU

    assert Signal.toString(Signal.INVALID) == 'INVALID'
    assert Signal.fromString('INVALID') == Signal.INVALID

    assert Signal.toString(Signal.Type(42)) == None
    assert Signal.fromString('foobar') == Signal.INVALID

    assert Signal.count() == 3

def assertNotDefaultConstructible(cls):
    try:
        instance = cls()
    except:
        pass
    else:
        raise TypeError, str(cls) + " should not be default-constructible"

@test
def CreateSample():
    assertNotDefaultConstructible(elapse.data.Sample)

@test
def CreateEegSample():
    s = elapse.data.EegSample()
    assert isinstance(s, elapse.data.Sample)
    assert s.timestamp == 0
    assert s.seqnum == 0
    assert s.leadOff == 0
    assert len(s.values) == 0

@test
def CreateVideoSample():
    s = elapse.data.VideoSample()
    assert isinstance(s, elapse.data.Sample)
    assert s.timestamp == 0
    assert s.w == 0
    assert s.h == 0
    assert len(s.data) == 0

@test
def CreateImuSample():
    s = elapse.data.ImuSample()
    assert isinstance(s, elapse.data.Sample)
    assert s.timestamp == 0
    assert s.acc == (0,0,0)
    assert s.gyr == (0,0,0)

@test
def CreateFeatureVector():
    assertNotDefaultConstructible(elapse.data.FeatureVector)

    v = elapse.data.FeatureVector(Signal.EEG, 42)
    assert v.signalType == Signal.EEG
    assert v.startTime == 42
    assert len(v.features) == 0

    # TODO: v.features should be writable
#    v.features = []

@test
def CreateCogState():
    assertNotDefaultConstructible(elapse.data.CognitiveState)

    c = elapse.data.CognitiveState(42)
    assert c.startTime == 42
    assert len(c.state) == 0

    # TODO: c.state should be writable
#    c.state = []

@test
def CreateFeatureExtractor():
    class FX(elapse.elements.FeatureExtractor):
        pass

    fx = FX()

    try:
        fx.onSample(elapse.data.EegSample())
    except:
        pass
    else:
        raise TypeError, 'FeatureExtractor.onSample() should be pure virtual'

@test
def BaseFeatExMethods():
    class BFX(elapse.elements.BaseFeatureExtractor):
        signalType = Signal.EEG
    fx = flexmock(BFX())

    # Necessary configuration before calling onSample
    fx.should_receive('removeDataBefore').once()
    fx.setStartTime(1)

    fx.should_call('onSample').once()
    fx.should_receive('analyseSample').once()

    sample = elapse.data.EegSample()
    sample.timestamp = 2
    fx.onSample(sample)
