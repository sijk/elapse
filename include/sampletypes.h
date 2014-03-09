#ifndef SAMPLETYPES_H
#define SAMPLETYPES_H

#include <QtGlobal>
#include <QVector>
#include <QVector3D>
#include <QByteArray>
#include <QSharedPointer>
#include <QMetaEnum>


/*!
 * \brief The SampleType class is a wrapper which provides introspection
 * of the SampleType::Type enum.
 * \ingroup signal-datatypes
 */
class SampleType
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * \brief The Type enum allows you to refer to a subclass of Sample by name.
     */
    enum Type { EEG, VIDEO, IMU };

    /*! \return the given \a type as a string. */
    static QString toString(Type type)
    { return typeEnum().valueToKey(type); }

    /*! \return the given \a type as a #Type, or -1 if invalid. */
    static Type fromString(const char *type)
    { return Type(typeEnum().keyToValue(type)); }

    /*! \return the number of #Type%s in the enum. */
    static int count()
    { return typeEnum().keyCount(); }

private:
    static QMetaEnum typeEnum()
    {
        int ienum = staticMetaObject.indexOfEnumerator("Type");
        return staticMetaObject.enumerator(ienum);
    }
};


struct Sample
{
    virtual ~Sample() {}

    quint64 timestamp;
};


typedef QSharedPointer<const Sample> SamplePtr;


struct EegSample : Sample
{
    quint32 seqnum;
    quint16 leadOff;
    QVector<double> values;
};


struct VideoSample : Sample
{
    int w, h;
    QByteArray data;
};


struct ImuSample : Sample
{
    QVector3D acc;
    QVector3D gyr;
};


#endif // SAMPLETYPES_H
