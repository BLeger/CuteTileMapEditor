#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QResizeEvent>
#include <QItemSelection>
#include <QFileDialog>

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

#include "TileListModel.h"
#include "TileSet.h"
#include "TileMap.h"
#include "EditorScene.h"

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private slots:
    void openMapMenuClicked();
    void closeMapMenuClicked();
    void saveMapMenuClicked();
    void changeSelectedTile(QItemSelection selected, QItemSelection deselected);

private:
    Ui::EditorWindow *ui;

    QGraphicsView * m_view;
    EditorScene * m_scene;

    TileListModel m_tileModel;
    TileSet m_tileset;
    TileMap m_tilemap;

    QString openedMap = "";

    void resizeEvent(QResizeEvent* event);
};

#endif // EDITORWINDOW_H
