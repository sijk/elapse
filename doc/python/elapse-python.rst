This page documents the Python bindings to the Elapse framework.

.. contents::
    :local:

.. default-role:: elapse
.. Use doxylink as the default ReST role.


``elapse``
==========

All of the python bindings to Elapse are contained within the ``elapse``
package. All of the sub-modules are directly accessible from this package,
so you don't need to import them separately — a simple ``import elapse``
will suffice.

The purpose of this page is primarily to show which parts of the Elapse
API are exposed to Python. For detailed documentation on the classes listed
here, follow the links to the documentation of the C++ classes.


``elapse.data``
---------------

.. module:: elapse.data

See `elapse::data`.

.. class:: Signal

    See `elapse::data::Signal`.

    .. attribute:: EEG
    .. attribute:: VIDEO
    .. attribute:: IMU
    .. attribute:: INVALID
    .. staticmethod:: toString(signal) -> str
    .. staticmethod:: fromString(signal) -> Signal.Type
    .. staticmethod:: count() -> int

.. class:: Sample

    See `elapse::data::Sample`.

    .. attribute:: timestamp

.. class:: EegSample

    See `elapse::data::EegSample`.

    .. attribute:: seqnum
    .. attribute:: leadOff
    .. attribute:: values

.. class:: VideoSample

    See `elapse::data::VideoSample`.

    .. attribute:: w
    .. attribute:: h
    .. attribute:: data

.. class:: ImuSample

    See `elapse::data::ImuSample`. Both :attr:`acc` and :attr:`gyr` are
    3-tuples of ``(x,y,z)`` values.

    .. attribute:: acc
    .. attribute:: gyr

.. class:: FeatureVector

    See `elapse::data::FeatureVector`.

    .. .. method:: __init__(signalType, startTime)
    .. attribute:: signalType
    .. attribute:: startTime
    .. attribute:: features

        An iterable sequence of floats.

.. class:: CognitiveState

    See `elapse::data::CognitiveState`.

    .. .. method:: __init__(startTime)
    .. attribute:: startTime
    .. attribute:: state


``elapse.elements``
-------------------

.. module:: elapse.elements

See `elapse::elements`. When implementing any of these classes you must
implement all of the listed methods unless otherwise noted (they are pure
virtual in the C++ base classes).

.. class:: BaseFeatureExtractor

    See `elapse::elements::BaseFeatureExtractor`.

    .. attribute:: signalType

        Each subclass of :class:`BaseFeatureExtractor` must have a class
        attribute called :attr:`signalType` that indicates what type of signal
        it works with. The value must be one of the :class:`elapse.data.Signal`
        tags. ::

            class MyEegFeatureExtractor(elapse.elements.BaseFeatureExtractor):
                signalType = elapse.data.Signal.EEG
                # ...

    .. method:: analyseSample(sample)
    .. method:: features() -> list
    .. method:: removeDataBefore(time)
    .. method:: reset()

        *Optional* — defaults to calling :meth:`removeDataBefore` with the
        maximum possible value.


.. class:: BaseClassifier

    See `elapse::elements::BaseClassifier`.

    .. method:: classify(featureVectors) -> CognitiveState

        :param featureVectors:
            A list of :class:`FeatureVectors <elapse.data.FeatureVector>`
            to classify, one for each signal type.
        :return: The classified :class:`~elapse.data.CognitiveState`.

.. class:: OutputAction

    See `elapse::elements::OutputAction`.

    .. method:: onState(state)

        :param state:
            The :class:`~elapse.data.CognitiveState` to take action on.

.. class:: DataSink

    See `elapse::elements::DataSink`.

    .. method:: startSaving() -> bool
    .. method:: stopSaving()
    .. method:: needsNewCaptureInfo() -> bool
    .. method:: getCaptureInfo() -> bool
    .. method:: saveDeviceConfig(config)
    .. method:: saveData(signalType, data)

        *Optional*

    .. method:: saveSample(signalType, sample)

        *Optional*

    .. method:: saveFeatureVector(features)

        *Optional*

    .. method:: saveCognitiveState(state)

        *Optional*



``elapse.log``
--------------

.. module:: elapse.log

The functions in this module provide access to the same logger that the C++
code uses. Use these functions instead of the ``print`` statement so that
messages appear in the application's log window. ::

    elapse.log.debug('Analysing sample with timestamp', sample.timestamp)

Functions are listed in order of increasing severity.

.. function:: trace(*args)
.. function:: debug(*args)
.. function:: info(*args)
.. function:: warning(*args)
.. function:: error(*args)


``elapse.settings``
-------------------

.. module:: elapse.settings

The functions in this module provide access to the Elapse client application's
settings file. It is strongly recommended that you prefix the names of any
settings that you store with ``'plugins/myplugin'``, where ``myplugin`` is the
name of your plugin, e.g.::

    dataDir = elapse.settings.getStr('plugins/mydatasink/datadir')

.. function:: getBool(key) -> bool
.. function:: setBool(key, value)
.. function:: getInt(key) -> int
.. function:: setInt(key, value)
.. function:: getStr(key) -> str
.. function:: setStr(key, value)
.. function:: getFloat(key) -> float
.. function:: setFloat(key, value)


``elapse.gui``
--------------

.. module:: elapse.gui

The functions in this module provide access to miscellaneous GUI dialogs that
may be useful for, e.g., implementing :meth:`.DataSink.getCaptureInfo`.

.. function:: getInt(title, label, value, min, max, step) -> int

    Show a dialog box to request an integer from the user.

    :param str title: Text to show in the titlebar of the window
    :param str label: Text describing what should be entered
    :param int value: Default value in the spin box
    :param int min:   Minimum valid value
    :param int max:   Maximum valid value
    :param int step:  Amount to increment by when pressing the arrow buttons
    :return:          The entered value, or ``None`` if cancelled
