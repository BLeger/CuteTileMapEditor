#ifndef EDITORSCENE_H
#define EDITORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "TileMap.h"

class EditorScene : public QGraphicsScene {

public:
    EditorScene(TileMap& tilemap);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void setSelectedTileName(QString name) {
        m_selectedTileName = name;
    }

    QPoint sceneToTilePosition(QPointF scenePos);

private:
    TileMap& m_tilemap;
    QString m_selectedTileName;
    QPoint m_mousePressPosition;
};

#endif // EDITORSCENE_H
