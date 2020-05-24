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

    void setSelectedTileName(QString name) {
        m_selectedTileName = name;
    }

private:
    TileMap& m_tilemap;
    QString m_selectedTileName;
};

#endif // EDITORSCENE_H
