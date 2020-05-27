#include "EditorScene.h"

EditorScene::EditorScene(TileMap &tilemap)
    : m_tilemap(tilemap)
{

}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint tilePos = sceneToTilePosition(event->scenePos());
    m_mousePressPosition = tilePos;

    if (!m_tilemap.tileExists(tilePos)) {
        return;
    }

    if (event->button() == Qt::LeftButton) {
        if (m_selectedTileName != "") {
            m_tilemap.enableTile(tilePos, m_selectedTileName);
        }
    } else if (event->button() == Qt::RightButton) {
        m_tilemap.disableTile(tilePos);
    }
}

void EditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint tilePos = sceneToTilePosition(event->scenePos());

    QPoint startPos;
    QPoint endPos;

    if (tilePos.x() > m_mousePressPosition.x()) {
        startPos.setX(m_mousePressPosition.x());
        endPos.setX(tilePos.x());
    } else {
        endPos.setX(m_mousePressPosition.x());
        startPos.setX(tilePos.x());
    }

    if (tilePos.y() > m_mousePressPosition.y()) {
        startPos.setY(m_mousePressPosition.y());
        endPos.setY(tilePos.y());
    } else {
        endPos.setY(m_mousePressPosition.y());
        startPos.setY(tilePos.y());
    }

    for (int x = startPos.x(); x <= endPos.x(); x++) {
        for (int y = startPos.y(); y <= endPos.y(); y++) {
            QPoint pos {x, y};

            if (!m_tilemap.tileExists(pos)) {
                return;
            }

            if (event->button() == Qt::LeftButton) {
                if (m_selectedTileName != "") {
                    m_tilemap.enableTile(pos, m_selectedTileName);
                }
            } else if (event->button() == Qt::RightButton) {
                m_tilemap.disableTile(pos);
            }
        }
    }
}

QPoint EditorScene::sceneToTilePosition(QPointF scenePos)
{
    int tilePosX = (int) scenePos.x() / m_tilemap.getTileSize().x();
    int tilePosY = (int) scenePos.y() / m_tilemap.getTileSize().y();
    QPoint tilePos {tilePosX, tilePosY};

    return tilePos;
}
