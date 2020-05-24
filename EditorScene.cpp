#include "EditorScene.h"

EditorScene::EditorScene(TileMap &tilemap)
    : m_tilemap(tilemap)
{

}

void EditorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF scenePos = event->scenePos();
    int tilePosX = (int) scenePos.x() / m_tilemap.getTileSize().x();
    int tilePosY = (int) scenePos.y() / m_tilemap.getTileSize().y();
    QPoint tilePos {tilePosX, tilePosY};

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
