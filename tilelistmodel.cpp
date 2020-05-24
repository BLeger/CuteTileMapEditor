#include "TileListModel.h"

TileListModel::TileListModel(TileSet &tileset) :
    m_tileset(tileset)
{

}

int TileListModel::rowCount(const QModelIndex &parent) const
{
    return m_tileset.getDescriptors().size();
}

QVariant TileListModel::data(const QModelIndex &index, int role) const
{
    const TileSet::TileDescriptor& descriptor = m_tileset.getDescriptors()[index.row()];

    if (role == Qt::DecorationRole) {
        return m_tileset.getImage().copy(m_tileset.getTileRect(descriptor.name));
        //return m_tileset.getImage().copy(QRect(0, 0, 16, 16));
    }

    if (role == Qt::DisplayRole) {
        return descriptor.name;
    }

    return QVariant();
}

QVariant TileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Orientation::Horizontal) {
        return "ah";
    }

    return QVariant();
}
