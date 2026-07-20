#pragma once

#include "label_element.h"
#include <QString>

namespace LabelDesigner {

enum class BarcodeFormat {
    Code128,
    Code39,
    Code93,
    EAN13,
    EAN8,
    UPCA,
    UPCE,
    Interleaved2of5,
    Codabar,
    MSI
};

/**
 * @brief Barcode element
 * Represents barcode information with various formats
 */
class BarcodeElement : public LabelElement {
public:
    BarcodeElement();
    explicit BarcodeElement(const QString& name);

    ElementType getType() const override {
        return ElementType::Barcode;
    }

    /**
     * @brief Get barcode format
     */
    BarcodeFormat getFormat() const { return m_format; }

    /**
     * @brief Set barcode format
     */
    void setFormat(BarcodeFormat format) { m_format = format; }

    /**
     * @brief Get barcode content/encoding data
     */
    const QString& getContent() const { return m_content; }

    /**
     * @brief Set barcode content
     */
    void setContent(const QString& content) { m_content = content; }

    /**
     * @brief Get barcode width in pixels
     */
    int getBarWidth() const { return m_barWidth; }

    /**
     * @brief Set barcode width
     */
    void setBarWidth(int width) { m_barWidth = width; }

    /**
     * @brief Get barcode height in pixels
     */
    int getBarHeight() const { return m_barHeight; }

    /**
     * @brief Set barcode height
     */
    void setBarHeight(int height) { m_barHeight = height; }

    /**
     * @brief Check if text label should be displayed
     */
    bool isShowText() const { return m_showText; }

    /**
     * @brief Set whether to show text label
     */
    void setShowText(bool show) { m_showText = show; }

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    BarcodeFormat m_format;
    QString m_content;
    int m_barWidth;
    int m_barHeight;
    bool m_showText;
};

} // namespace LabelDesigner
