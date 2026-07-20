#pragma once

#include "label_element.h"
#include <QString>

namespace LabelDesigner {

enum class QRCodeErrorCorrection {
    L,  // ~7% correction
    M,  // ~15% correction
    Q,  // ~25% correction
    H   // ~30% correction
};

/**
 * @brief QR Code element
 * Represents QR code information
 */
class QRCodeElement : public LabelElement {
public:
    QRCodeElement();
    explicit QRCodeElement(const QString& name);

    ElementType getType() const override {
        return ElementType::QRCode;
    }

    /**
     * @brief Get QR code content
     */
    const QString& getContent() const { return m_content; }

    /**
     * @brief Set QR code content
     */
    void setContent(const QString& content) { m_content = content; }

    /**
     * @brief Get QR code size (width and height in pixels)
     */
    int getSize() const { return m_size; }

    /**
     * @brief Set QR code size
     */
    void setSize(int size) { m_size = size; }

    /**
     * @brief Get error correction level
     */
    QRCodeErrorCorrection getErrorCorrection() const { return m_errorCorrection; }

    /**
     * @brief Set error correction level
     */
    void setErrorCorrection(QRCodeErrorCorrection level) { m_errorCorrection = level; }

    /**
     * @brief Get border size (quiet zone) in modules
     */
    int getBorderSize() const { return m_borderSize; }

    /**
     * @brief Set border size
     */
    void setBorderSize(int size) { m_borderSize = size; }

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    QString m_content;
    int m_size;
    QRCodeErrorCorrection m_errorCorrection;
    int m_borderSize;
};

} // namespace LabelDesigner
