#ifndef SIMPLERAWDATASOURCE_H
#define SIMPLERAWDATASOURCE_H

#include <elapse/elements/datasource.h>
#include <elapse/displayable.h>

class SimpleRawDataSourcePrivate;


/*!
 * \brief The SimpleRawDataSource class loads data saved by a
 * SimpleRawDataSinkDelegate.
 *
 * \ingroup core-plugin
 */

class SimpleRawDataSource : public elapse::OfflineDataSource,
                            public elapse::Displayable
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleRawDataSource(QObject *parent = nullptr);
    ~SimpleRawDataSource();

    QVariant get(const QString &subSystem, const QString &property);
    QWidget *getWidget();

public slots:
    void start();
    void stop();

private:
    SimpleRawDataSourcePrivate * const d_ptr;
    Q_DECLARE_PRIVATE(SimpleRawDataSource)
};

#endif // SIMPLERAWDATASOURCE_H
