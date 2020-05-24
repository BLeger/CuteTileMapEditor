#ifndef TILEMAP_H
#define TILEMAP_H

#include <QVector>
#include <QGraphicsItemGroup>
#include <QDebug>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QGraphicsSceneMouseEvent>

#include "TileSet.h"
#include "Tile.h"

class TileMap : public QGraphicsItemGroup {

public:
    TileMap(QPoint size, TileSet& tileset);
    TileMap(TileSet& tileset, QString mapDescriptorPath);

    void updatePosition();

    void enableTile(QPointF position);
    void enableTile(QPointF position, QString descriptorName);
    void disableTile(QPointF position);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QPointF getTileSize() {return m_tileSize;}

    void reset(QPoint size);
    const QVector<Tile*>& getTiles() {return m_tiles;}
    QJsonObject toJson();

private:
    QPoint m_size;
    QPointF m_tileSize;
    QVector<Tile*> m_tiles;
    TileSet& m_tileset;

    bool tileExists(QPointF position);
    Tile& getTile(QPointF position);
    bool tileEnabled(QPointF position);
};

#endif // TILEMAP_H
