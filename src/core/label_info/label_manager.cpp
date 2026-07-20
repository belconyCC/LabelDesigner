#include "label_manager.h"
#include "src/models/fixed_info_element.h"
#include "src/models/binding_info_element.h"
#include "src/models/time_info_element.h"
#include "src/models/barcode_element.h"
#include "src/models/qrcode_element.h"
#include "src/models/image_element.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

namespace LabelDesigner {

LabelManager::LabelManager() {
}

LabelManager::~LabelManager() {
    clear();
}

void LabelManager::addElement(LabelElementPtr element) {
    if (element) {
        m_elements.push_back(element);
        m_elementIndex[element->getId()] = m_elements.size() - 1;
    }
}

bool LabelManager::removeElement(const QString& elementId) {
    auto it = std::find_if(m_elements.begin(), m_elements.end(),
        [&elementId](const LabelElementPtr& elem) {
            return elem->getId() == elementId;
        });
    
    if (it != m_elements.end()) {
        m_elementIndex.erase(elementId);
        m_elements.erase(it);
        return true;
    }
    return false;
}

LabelElementPtr LabelManager::getElement(const QString& elementId) const {
    auto it = std::find_if(m_elements.begin(), m_elements.end(),
        [&elementId](const LabelElementPtr& elem) {
            return elem->getId() == elementId;
        });
    
    if (it != m_elements.end()) {
        return *it;
    }
    return nullptr;
}

std::vector<LabelElementPtr> LabelManager::getElementsByType(LabelElement::ElementType type) const {
    std::vector<LabelElementPtr> result;
    for (const auto& element : m_elements) {
        if (element->getType() == type) {
            result.push_back(element);
        }
    }
    return result;
}

void LabelManager::clear() {
    m_elements.clear();
    m_elementIndex.clear();
}

QString LabelManager::toJson() const {
    QJsonObject root;
    root["version"] = "1.0";
    root["element_count"] = static_cast<int>(m_elements.size());
    
    QJsonArray elementsArray;
    for (const auto& element : m_elements) {
        QJsonDocument doc = QJsonDocument::fromJson(element->toJson().toUtf8());
        if (doc.isObject()) {
            elementsArray.append(doc.object());
        }
    }
    root["elements"] = elementsArray;

    QJsonDocument doc(root);
    return QString::fromUtf8(doc.toJson());
}

void LabelManager::fromJson(const QString& json) {
    clear();
    
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject root = doc.object();
    QJsonArray elementsArray = root["elements"].toArray();
    
    for (const auto& elemValue : elementsArray) {
        QJsonObject elemObj = elemValue.toObject();
        QString type = elemObj["type"].toString();
        
        LabelElementPtr element;
        if (type == "FixedInfo") {
            element = std::make_shared<FixedInfoElement>();
        } else if (type == "BindingInfo") {
            element = std::make_shared<BindingInfoElement>();
        } else if (type == "TimeInfo") {
            element = std::make_shared<TimeInfoElement>();
        } else if (type == "Barcode") {
            element = std::make_shared<BarcodeElement>();
        } else if (type == "QRCode") {
            element = std::make_shared<QRCodeElement>();
        } else if (type == "Image") {
            element = std::make_shared<ImageElement>();
        }
        
        if (element) {
            element->fromJson(QString::fromUtf8(QJsonDocument(elemObj).toJson()));
            addElement(element);
        }
    }
}

} // namespace LabelDesigner
