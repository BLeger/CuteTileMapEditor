#include "EditorWindow.h"
#include "ui_editorwindow.h"

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow),
    m_tileset(":/tileset.json"),
    m_tileModel(m_tileset),
    m_tilemap(QPoint{100, 10}, m_tileset)
{
    ui->setupUi(this);

    m_view = new QGraphicsView();
    m_view->setMouseTracking(true);
    m_scene = new EditorScene(m_tilemap, statusBar());
    m_view->setScene(m_scene);

    m_scene->addItem(&m_tilemap);

    ui->tileView->setModel(&m_tileModel);
    ui->tileView->update();

    ui->horizontalLayout_2->addWidget(m_view);

    connect(ui->tileView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(changeSelectedTile(QItemSelection, QItemSelection)));
    connect(ui->openMapAction, SIGNAL(triggered()), this, SLOT(openMapMenuClicked()));
    connect(ui->saveMapAction, SIGNAL(triggered()), this, SLOT(saveMapMenuClicked()));

    connect(ui->moveLeftButton, SIGNAL(clicked()), this, SLOT(moveLeftClicked()));
    connect(ui->moveRightButton, SIGNAL(clicked()), this, SLOT(moveRightClicked()));

    statusBar()->showMessage("test");
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::openMapMenuClicked()
{
    m_scene->resetOffset();
    QString fileName = QFileDialog::getOpenFileName(this, "Open map", "", tr("Json file (*.json)"));

    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject mainObject = document.object();

    // Read map size
    QJsonObject sizeObject = mainObject["size"].toObject();
    QPoint size = {sizeObject["x"].toInt(), sizeObject["y"].toInt()};
    m_tilemap.reset(size);

    // Read tiles
    QJsonArray tiles = mainObject["map"].toArray();

    for (auto tileInfoRef : tiles) {
        QJsonObject tileInfo = tileInfoRef.toObject();
        QJsonObject positionObject = tileInfo["position"].toObject();
        QPoint position {positionObject["x"].toInt(), positionObject["y"].toInt()};
        QString tileName = tileInfo["tile"].toString();
        m_tilemap.enableTile(position, tileName);
    }

    openedMap = fileName;
}

void EditorWindow::saveMapMenuClicked()
{
    QString filename;

    if (openedMap == "") {
        filename = QFileDialog::getSaveFileName(this, "Save file", "", tr("Json file (*.json)"));
    } else {
        filename = openedMap;
    }

    QFile saveFile(filename);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    QJsonObject tilemap = m_tilemap.toJson();

    QJsonDocument saveDoc(tilemap);
    saveFile.write(saveDoc.toJson());

}

void EditorWindow::changeSelectedTile(QItemSelection selected, QItemSelection deselected)
{
    if (!selected.empty()) {
        int index = selected.first().indexes().first().row();
        QString tileName = m_tileset.getDescriptors()[index].name;
        m_scene->setSelectedTileName(tileName);
    }
}

void EditorWindow::moveLeftClicked()
{
    m_scene->moveMapLeft();
}

void EditorWindow::moveRightClicked()
{
    m_scene->moveMapRight();
}

void EditorWindow::resizeEvent(QResizeEvent *event)
{
    QSize viewSize = m_view->size();
    m_scene->setSceneRect(QRectF{0, 0, (float) viewSize.rwidth() - 10, (float) viewSize.rheight() - 10});
}
