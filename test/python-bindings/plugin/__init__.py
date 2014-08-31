import elapse


# The list of test classes is automatically populated by the test decorator
classes = []

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
            except Exception, e:
                print '[  FAILED  ]', e
                raise
            else:
                print '[       OK ]'

    # Name the class according to the name of the function
    testClass = type('test_' + fn.__name__, (Test,), {})
    classes.append(testClass)
    return testClass


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #


@test
def SignalTypes():
    assert elapse.Signal.toString(elapse.Signal.EEG) == 'EEG'
    assert elapse.Signal.toString(elapse.Signal.VIDEO) == 'VIDEO'
    assert elapse.Signal.toString(elapse.Signal.IMU) == 'IMU'

    assert elapse.Signal.fromString('EEG') == elapse.Signal.EEG
    assert elapse.Signal.fromString('VIDEO') == elapse.Signal.VIDEO
    assert elapse.Signal.fromString('IMU') == elapse.Signal.IMU

    assert elapse.Signal.toString(elapse.Signal.INVALID) == 'INVALID'
    assert elapse.Signal.fromString('INVALID') == elapse.Signal.INVALID

    assert elapse.Signal.toString(elapse.Signal.Type(42)) == None
    assert elapse.Signal.fromString('foobar') == elapse.Signal.INVALID

    assert elapse.Signal.count() == 3

@test
def CreateSample():
    s = elapse.Sample()
    assert s.timestamp == 0

    try:
        s.timestamp = 42
    except AttributeError, e:
        pass
    else:
        raise AttributeError, "Sample.timestamp should be read-only"

@test
def CreateEegSample():
    s = elapse.EegSample()
    assert isinstance(s, elapse.Sample)
    assert s.timestamp == 0
    assert s.seqnum == 0
    assert s.leadOff == 0
    assert len(s.values) == 0

@test
def CreateVideoSample():
    s = elapse.VideoSample()
    assert isinstance(s, elapse.Sample)
    assert s.timestamp == 0
    assert s.w == 0
    assert s.h == 0
    assert len(s.data) == 0

@test
def CreateImuSample():
    s = elapse.ImuSample()
    assert isinstance(s, elapse.Sample)
    assert s.timestamp == 0
    assert s.acc == (0,0,0)
    assert s.gyr == (0,0,0)

@test
def CreateFeatureVector():
    try:
        v = elapse.FeatureVector()
    except:
        pass
    else:
        raise TypeError, "FeatureVector should not have a default ctor"

    v = elapse.FeatureVector(elapse.Signal.EEG, 42)
    assert v.signalType == elapse.Signal.EEG
    assert v.startTime == 42
    assert len(v.features) == 0

    # TODO: v.features should be writable
#    v.features = []

@test
def CreateCogState():
    try:
        c = elapse.CognitiveState()
    except:
        pass
    else:
        raise TypeError, "CognitiveState should not have a default ctor"

    c = elapse.CognitiveState(42)
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
        fx.onSample(elapse.EegSample())
    except:
        pass
    else:
        raise TypeError, 'FeatureExtractor.onSample() should be pure virtual'
