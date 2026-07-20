#include "image_element.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

namespace LabelDesigner {

ImageElement::ImageElement()
    : m_maintainAspectRatio(true),
      m_opacity(255) {
    generateId();
    setName("Image");
}

ImageElement::ImageElement(const QString& name)
    : m_maintainAspectRatio(true),
      m_opacity(255) {
    generateId();
    setName(name);
}

bool ImageElement::loadImage(const QString& path) {
    m_imagePath = path;
    return m_pixmap.load(path);
}

std::map<QString, QVariant> ImageElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["image_path"] = m_imagePath;
    props["maintain_aspect_ratio"] = m_maintainAspectRatio;
    props["opacity"] = m_opacity;
    return props;
}

void ImageElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "image_path") {
        loadImage(value.toString());
    } else if (key == "maintain_aspect_ratio") {
        m_maintainAspectRatio = value.toBool();
    } else if (key == "opacity") {
        m_opacity = value.toInt();
    }
}

QString ImageElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "Image";
    obj["image_path"] = m_imagePath;
    obj["maintain_aspect_ratio"] = m_maintainAspectRatio;
    obj["opacity"] = m_opacity;
    obj["rect_x"] = m_rect.x();
    obj["rect_y"] = m_rect.y();
    obj["rect_width"] = m_rect.width();
    obj["rect_height"] = m_rect.height();

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void ImageElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_imagePath = obj["image_path"].toString();
    m_maintainAspectRatio = obj["maintain_aspect_ratio"].toBool();
    m_opacity = obj["opacity"].toInt();
    
    m_rect = QRect(
        obj["rect_x"].toInt(),
        obj["rect_y"].toInt(),
        obj["rect_width"].toInt(),
        obj["rect_height"].toInt()
    );
    
    // Try to load image if path is valid
    if (!m_imagePath.isEmpty()) {
        m_pixmap.load(m_imagePath);
    }
}

std::unique_ptr<LabelElement> ImageElement::clone() const {
    auto clone = std::make_unique<ImageElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_imagePath = m_imagePath;
    clone->m_pixmap = m_pixmap;
    clone->m_rect = m_rect;
    clone->m_maintainAspectRatio = m_maintainAspectRatio;
    clone->m_opacity = m_opacity;
    return clone;
}

} // namespace LabelDesigner
