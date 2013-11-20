#ifndef PLUGINFILTERPROXYMODEL_H
#define PLUGINFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class PluginFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    PluginFilterProxyModel(const QString &elementType,
                           const QString &sampleType,
                           QObject *parent = nullptr);
protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const;

private:
    QString desiredElementType;
    QString desiredSampleType;
};

#endif // PLUGINFILTERPROXYMODEL_H
