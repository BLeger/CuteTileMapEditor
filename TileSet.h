#ifndef TILESET_H
#define TILESET_H

#include <algorithm>

#include <QString>
#include <QPointF>
#include <QImage>
#include <QDebug>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class TileSet {

public:

    struct TileDescriptor {
        QString name;
        QPoint position;
        bool collision;
    };

    TileSet(QString imagePath, QPoint tileSize, QPoint size, QPoint tileOffset = {0, 0});
    TileSet(QString jsonDescriptorPath);

    QPointF getTileSize();
    const QImage& getImage();
    QRect getTileRect(QString name);

    const TileDescriptor& getTileDescriptor(QString name);
    const QVector<TileDescriptor>& getDescriptors() {return m_tileDescriptors;}

private:
    QImage m_image;
    QPoint m_tileSize;
    QPoint m_size;
    QPoint m_tileOffset;

    QVector<TileDescriptor> m_tileDescriptors;

    void addTileDescriptor(QJsonObject& descriptor);
};

#endif // TILESET_H
