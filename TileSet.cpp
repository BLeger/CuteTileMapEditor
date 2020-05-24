#include "TileSet.h"

TileSet::TileSet(QString imagePath, QPoint tileSize, QPoint size, QPoint tileOffset) :
    m_tileSize(tileSize), m_size(size), m_tileOffset(tileOffset)
{
    m_image.load(imagePath);
}

TileSet::TileSet(QString jsonDescriptorPath)
{
    // Read json file
    QFile file;
    file.setFileName(jsonDescriptorPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString val = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject mainObject = document.object();

    // Load the image containing all tiles
    QString imagePath = mainObject["image"].toString();
    m_image.load(imagePath);

    // Read sizes
    QJsonObject size = mainObject["size"].toObject();
    m_size = {size["x"].toInt(), size["y"].toInt()};

    QJsonObject tileSize = mainObject["tileSize"].toObject();
    m_tileSize = {tileSize["x"].toInt(), tileSize["y"].toInt()};

    QJsonObject tileOffset = mainObject["tileOffset"].toObject();
    m_tileOffset = {tileOffset["x"].toInt(), tileOffset["y"].toInt()};

    // Read tile descriptors
    QJsonArray tileDescriptors = mainObject["tiles"].toArray();

    for (auto tileDescriptorRef : tileDescriptors) {
        QJsonObject tileDescriptor = tileDescriptorRef.toObject();
        addTileDescriptor(tileDescriptor);
    }
}

QPointF TileSet::getTileSize()
{
    return m_tileSize;
}

const QImage &TileSet::getImage()
{
    return m_image;
}

QRect TileSet::getTileRect(QString name)
{
    auto &descriptor = getTileDescriptor(name);
    const QPoint &position = descriptor.position;

    return QRect{position.x() * (m_tileSize.x() + m_tileOffset.x()),
                 position.y() * (m_tileSize.y() + m_tileOffset.y()),
                 m_tileSize.x(), m_tileSize.y()};
}

const TileSet::TileDescriptor &TileSet::getTileDescriptor(QString name)
{
    auto descriptor = std::find_if(m_tileDescriptors.begin(), m_tileDescriptors.end(), [&name](const TileDescriptor& value) {
       return value.name == name;
    });

    return *descriptor;
}

void TileSet::addTileDescriptor(QJsonObject &descriptor)
{
    QString tileName = descriptor["name"].toString();
    QJsonObject tilePositionObject = descriptor["position"].toObject();
    QPoint tilePosition = {tilePositionObject["x"].toInt(), tilePositionObject["y"].toInt()};

    m_tileDescriptors.push_back({tileName, tilePosition, descriptor["collision"].toBool()});
}

