#include "advqsortfilterproxymodel.h"

AdvQSortFilterProxyModel::AdvQSortFilterProxyModel(QObject* parent)
{
    showOffline = true;
    showApproximateViewerCount = true;
}

QVariant AdvQSortFilterProxyModel::data(const QModelIndex &index, int role) const
{
 /**   if (role == Qt::BackgroundRole ) {
        QBrush demonicBackground(QColor(255, 60, 43));
        QBrush evilBackground(QColor(255,123,71));
        QBrush unkownBackground(QColor(102, 191, 255));
        QBrush goodBackground(QColor(110, 255, 96));
        QBrush playlistBackground(QColor(210, 76, 222));

        if (index.column() == 1) {
            if (genericHelper::isOnline(index.data().toString()) ) {
                return QVariant(goodBackground);
            } else {
                if (index.data().toString() == "hosting") {
                    return QVariant(unkownBackground);
                }
                if (index.data().toString() == "playlist") {
                    return QVariant(playlistBackground);
                }
            }
        }
    }

    **/

    if(role == Qt::DisplayRole && (index.column() == 2 || index.column() == 3) && showApproximateViewerCount) {
        const int viewers = QSortFilterProxyModel::data(index, role).toInt();
        if (viewers > 1e6) {
            return QString::number(viewers / 1e6, 'f', 0) + "m";
        } else if (viewers > 1e3) {
            return QString::number(viewers / 1e3, 'f', 0) + "k";
        } else {
            return QSortFilterProxyModel::data( index, role );
        }
    }

    if ( role == Qt::TextAlignmentRole )
    {
        if (index.column() == 1) {
            return Qt::AlignCenter;

        }
        if (index.column() == 2) {
            return Qt::AlignCenter;

        }
    }

    return QSortFilterProxyModel::data( index, role );
}

bool AdvQSortFilterProxyModel::updateCol(int keycol, QVariant key, int updatecol, QVariant updatedata)
{

    bool updateok = false;

    for(int i = 0; i<this->sourceModel()->rowCount(); ++i)
    {
        QModelIndex key_index = this->sourceModel()->index(i,keycol);
        QModelIndex update_index = this->sourceModel()->index(i,updatecol);

        if ( this->sourceModel()->itemData(key_index)[0].toString() == key.toString() )  {
            updateok = this->sourceModel()->setData(update_index,updatedata);
        }
    }

    return updateok;


}

QVariant AdvQSortFilterProxyModel::getColData(int keycol, QVariant key, int updatecol)
{

    QVariant data = "";

    for(int i = 0; i<this->sourceModel()->rowCount(); ++i)
    {
        QModelIndex key_index = this->sourceModel()->index(i,keycol);
        QModelIndex update_index = this->sourceModel()->index(i,updatecol);

        if ( this->sourceModel()->itemData(key_index)[0].toString() == key.toString() )  {

            data = this->sourceModel()->data(update_index,0);
        }
    }

    return data;


}

void AdvQSortFilterProxyModel::setShowOffline(bool showoffline)
{
    this->showOffline = showoffline;
}

void AdvQSortFilterProxyModel::setShowApproximateViewerCount(const bool approxviewercount)
{
    this->showApproximateViewerCount = approxviewercount;
}

bool AdvQSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index0 = sourceModel()->index(source_row, 0, source_parent);
    QModelIndex index1 = sourceModel()->index(source_row, 1, source_parent);
    QModelIndex index2 = sourceModel()->index(source_row, 2, source_parent);
    QModelIndex index3 = sourceModel()->index(source_row, 3, source_parent);
    QModelIndex index4 = sourceModel()->index(source_row, 4, source_parent);

    if (showOffline == true) {
        return (sourceModel()->data(index0).toString().contains(filterRegExp()) ||
                sourceModel()->data(index3).toString().contains(filterRegExp()) ||
                sourceModel()->data(index4).toString().contains(filterRegExp())
                );
    } else {
        return (( sourceModel()->data(index0).toString().contains(filterRegExp()) ||
                  sourceModel()->data(index3).toString().contains(filterRegExp()) ||
                  sourceModel()->data(index4).toString().contains(filterRegExp())
                 ) &&
                sourceModel()->data(index1).toString() != "offline");
    }
}

bool AdvQSortFilterProxyModel::deleteCol(int keycol, QVariant key)
{
    bool updateok = false;

    for(int i = 0; i<this->sourceModel()->rowCount(); ++i)
    {
        QModelIndex key_index = this->sourceModel()->index(i, keycol);

        if ( this->sourceModel()->itemData(key_index)[0].toString() == key.toString() )  {
            updateok = this->sourceModel()->removeRow(i);
        }
    }

    return updateok;
}
