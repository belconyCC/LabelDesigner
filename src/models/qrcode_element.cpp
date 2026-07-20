#include "qrcode_element.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace LabelDesigner {

QRCodeElement::QRCodeElement()
    : m_size(200),
      m_errorCorrection(QRCodeErrorCorrection::M),
      m_borderSize(4) {
    generateId();
    setName("QRCode");
}

QRCodeElement::QRCodeElement(const QString& name)
    : m_size(200),
      m_errorCorrection(QRCodeErrorCorrection::M),
      m_borderSize(4) {
    generateId();
    setName(name);
}

std::map<QString, QVariant> QRCodeElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["content"] = m_content;
    props["size"] = m_size;
    props["error_correction"] = static_cast<int>(m_errorCorrection);
    props["border_size"] = m_borderSize;
    return props;
}

void QRCodeElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "content") {
        m_content = value.toString();
    } else if (key == "size") {
        m_size = value.toInt();
    } else if (key == "error_correction") {
        m_errorCorrection = static_cast<QRCodeErrorCorrection>(value.toInt());
    } else if (key == "border_size") {
        m_borderSize = value.toInt();
    }
}

QString QRCodeElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "QRCode";
    obj["content"] = m_content;
    obj["size"] = m_size;
    obj["error_correction"] = static_cast<int>(m_errorCorrection);
    obj["border_size"] = m_borderSize;
    obj["rect_x"] = m_rect.x();
    obj["rect_y"] = m_rect.y();
    obj["rect_width"] = m_rect.width();
    obj["rect_height"] = m_rect.height();

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void QRCodeElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_content = obj["content"].toString();
    m_size = obj["size"].toInt();
    m_errorCorrection = static_cast<QRCodeErrorCorrection>(obj["error_correction"].toInt());
    m_borderSize = obj["border_size"].toInt();
    
    m_rect = QRect(
        obj["rect_x"].toInt(),
        obj["rect_y"].toInt(),
        obj["rect_width"].toInt(),
        obj["rect_height"].toInt()
    );
}

std::unique_ptr<LabelElement> QRCodeElement::clone() const {
    auto clone = std::make_unique<QRCodeElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_content = m_content;
    clone->m_size = m_size;
    clone->m_errorCorrection = m_errorCorrection;
    clone->m_borderSize = m_borderSize;
    clone->m_rect = m_rect;
    return clone;
}

} // namespace LabelDesigner
