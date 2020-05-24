#include "TileMap.h"

TileMap::TileMap(QPoint size, TileSet& tileset) :
    m_size(size), m_tileSize(tileset.getTileSize()), m_tileset(tileset)
{
    for (float y = 0.f; y < size.y(); y++) {
        for (float x = 0.f; x < size.x(); x++) {
            m_tiles.push_back(new Tile {QPointF{x * m_tileSize.x(), y * m_tileSize.y()}, m_tileset});
        }
    }
}

TileMap::TileMap(TileSet &tileset, QString mapDescriptorPath) :
    m_tileSize(tileset.getTileSize()), m_tileset(tileset)
{
    // Read json file
    QFile file;
    file.setFileName(mapDescriptorPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject mainObject = document.object();

    // Read map size
    QJsonObject size = mainObject["size"].toObject();
    m_size = {size["x"].toInt(), size["y"].toInt()};

    for (float y = 0.f; y < m_size.y(); y++) {
        for (float x = 0.f; x < m_size.x(); x++) {
            m_tiles.push_back(new Tile {QPointF{x * m_tileSize.x(), y * m_tileSize.y()}, m_tileset});
        }
    }

    // Read tiles
    QJsonArray tiles = mainObject["map"].toArray();

    for (auto tileInfoRef : tiles) {
        QJsonObject tileInfo = tileInfoRef.toObject();
        QJsonObject positionObject = tileInfo["position"].toObject();
        QPoint position {positionObject["x"].toInt(), positionObject["y"].toInt()};
        QString tileName = tileInfo["tile"].toString();
        enableTile(position, tileName);
    }
}

void TileMap::updatePosition()
{
    return;
    static int counter = 0;
    if (childItems().size() > 0) {
        qDebug() << childItems()[0];
        ((Tile*) childItems()[0])->disable();
        removeFromGroup(childItems()[0]);
        //qDebug() << childItems()[0];

        counter++;
    }
}

bool TileMap::tileExists(QPointF position)
{
    return position.x() >= 0 && position.y() >= 0 && position.x() < m_size.x() && position.y() < m_size.y();
}

Tile &TileMap::getTile(QPointF position)
{
    assert(tileExists(position));
    return *m_tiles[position.x() + m_size.x() * position.y()];
}

void TileMap::enableTile(QPointF position)
{
    Tile& tile = getTile(position);

    if (!tile.isEnabled()) {
        addToGroup(&tile);
        tile.enable();
    }
}

void TileMap::enableTile(QPointF position, QString descriptorName)
{
    Tile& tile = getTile(position);

    if (!tile.isEnabled()) {
        addToGroup(&tile);
        tile.enable(descriptorName);
    } else {
        tile.setDescriptorName(descriptorName);
        update();
    }
}

void TileMap::disableTile(QPointF position)
{
    Tile& tile = getTile(position);

    if (tile.isEnabled()) {
        removeFromGroup(&tile);
        tile.disable();
    }
}

void TileMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos();
    }
}

void TileMap::reset(QPoint size)
{
    m_size = size;
    m_tiles.clear();

    for (float y = 0.f; y < size.y(); y++) {
        for (float x = 0.f; x < size.x(); x++) {
            m_tiles.push_back(new Tile {QPointF{x * m_tileSize.x(), y * m_tileSize.y()}, m_tileset});
        }
    }
}

QJsonObject TileMap::toJson()
{
    QJsonObject tilemap;
    QJsonObject sizeObject;
    sizeObject["x"] = m_size.x();
    sizeObject["y"] = m_size.y();

    tilemap["size"] = sizeObject;

    QJsonArray tileArray;

    for (float y = 0.f; y < m_size.y(); y++) {
        for (float x = 0.f; x < m_size.x(); x++) {
            auto &tile = getTile({x, y});
            if (!tile.isEnabled()) continue;

            QJsonObject tileObject;

            QJsonObject positionObject;
            positionObject["x"] = x;
            positionObject["y"] = y;
            tileObject["position"] = positionObject;

            tileObject["tile"] = tile.getDesctiptorName();
            tileArray.push_back(tileObject);
        }
    }


    tilemap["map"] = tileArray;

    return tilemap;
}
