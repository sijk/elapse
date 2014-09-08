#ifndef SIMPLERAWDATASOURCE_H
#define SIMPLERAWDATASOURCE_H

#include <elapse/elements/datasource.h>
#include <elapse/displayable.h>

namespace elapse { namespace coreplugin {

class SimpleRawDataSourcePrivate;


/*!
 * \brief The SimpleRawDataSource class loads data saved by a
 * SimpleRawDataSink.
 *
 * \ingroup core-plugin
 */

class SimpleRawDataSource : public elapse::elements::OfflineDataSource,
                            public elapse::Displayable
{
    Q_OBJECT
public:
    Q_INVOKABLE SimpleRawDataSource();
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

}} // namespace elapse::coreplugin

#endif // SIMPLERAWDATASOURCE_H
