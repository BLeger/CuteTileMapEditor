#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QStatusBar>

#include "TileMap.h"

class EditorScene : public QGraphicsScene {

public:
    EditorScene(TileMap& tilemap, QStatusBar* statusBar);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void setSelectedTileName(QString name) {
        m_selectedTileName = name;
    }

    void moveMapLeft();
    void moveMapRight();
    void resetOffset();

    QPoint sceneToTilePosition(QPointF scenePos);

private:
    TileMap& m_tilemap;
    QString m_selectedTileName;
    QPoint m_mousePressPosition;
    QStatusBar* m_statusBar = nullptr;

    int mapXOffset = 0;

    void updateMapPosition();
};

#endif // EDITORSCENE_H
