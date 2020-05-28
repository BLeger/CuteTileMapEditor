#include "EditorScene.h"

EditorScene::EditorScene(TileMap &tilemap, QStatusBar* statusBar)
    : m_tilemap(tilemap), m_statusBar(statusBar)
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


    qDebug() << endPos;

    for (int x = startPos.x(); x <= endPos.x(); x++) {
        for (int y = startPos.y(); y <= endPos.y(); y++) {
            QPoint pos {x, y};
            qDebug() << "actual pos : ";
            qDebug() << pos;
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

void EditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_statusBar == nullptr) return;

    QPoint tilePos = sceneToTilePosition(event->scenePos());

    std::string message = "Taille tilemap : " + std::to_string(m_tilemap.getSize().x()) + "x" + std::to_string(m_tilemap.getSize().y());
    message += " | Position souris : " + std::to_string(tilePos.x()) + "x" + std::to_string(tilePos.y());
    message += " | Décallage affichage map : " + std::to_string(mapXOffset);

    QString str = QString::fromUtf8(message.c_str());
    m_statusBar->showMessage(str);
}

void EditorScene::moveMapLeft()
{
    mapXOffset -= 100;
    updateMapPosition();
}

void EditorScene::moveMapRight()
{
    mapXOffset += 100;
    updateMapPosition();
}

void EditorScene::resetOffset()
{
    mapXOffset = 0;
    updateMapPosition();
}

QPoint EditorScene::sceneToTilePosition(QPointF scenePos)
{
    int tilePosX = (int) (scenePos.x() - mapXOffset) / m_tilemap.getTileSize().x();
    int tilePosY = (int) scenePos.y() / m_tilemap.getTileSize().y();
    QPoint tilePos {tilePosX, tilePosY};

    return tilePos;
}

void EditorScene::updateMapPosition()
{
    m_tilemap.setPos(mapXOffset, m_tilemap.pos().y());
}
