#ifndef TILELISTMODEL_H
#define TILELISTMODEL_H

#include <QAbstractListModel>
#include "TileSet.h"

class TileListModel : public QAbstractListModel {

public:
    TileListModel(TileSet& tileset);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    TileSet& m_tileset;
};

#endif // TILELISTMODEL_H
