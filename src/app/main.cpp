#include <QApplication>
#include "mainwindow.h"

#include "pluginmanager.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    PluginManager pluginManager;
//    QTreeView tv;
//    tv.setModel(pluginManager.model());
//    tv.expandAll();
//    tv.setHeaderHidden(true);
//    tv.setRootIsDecorated(false);
//    tv.setExpandsOnDoubleClick(false);
//    tv.setItemsExpandable(false);
//    tv.setAlternatingRowColors(true);
//    QModelIndex root = pluginManager.model()->findItems("org.nzbri.elapse.DataSourceInterface").at(0)->index();
//    tv.setRootIndex(root);
//    tv.selectionModel()->select(root.child(0,0).child(0,0), QItemSelectionModel::SelectCurrent);
//    QObject::connect(tv.selectionModel(), &QItemSelectionModel::selectionChanged,
//        [&](QItemSelection current, QItemSelection prev) {
//            if (current.indexes().isEmpty())
//                tv.selectionModel()->select(prev, QItemSelectionModel::SelectCurrent);
//        });
//    tv.setSelectionMode(QAbstractItemView::SingleSelection);
//    tv.show();
    pluginManager.show();

    return a.exec();
}
