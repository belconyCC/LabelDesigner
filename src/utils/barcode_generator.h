#pragma once

#include <QString>
#include <QPixmap>

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
 * @brief Barcode image generator
 * Generates barcode images from data
 */
class BarcodeGenerator {
public:
    BarcodeGenerator();
    ~BarcodeGenerator();

    /**
     * @brief Generate barcode image
     * @param data Data to encode
     * @param format Barcode format
     * @param width Image width in pixels
     * @param height Image height in pixels
     * @param showText Whether to display text below barcode
     * @return Generated pixmap, empty if failed
     */
    QPixmap generateBarcode(const QString& data,
                           BarcodeFormat format,
                           int width,
                           int height,
                           bool showText = true);

    /**
     * @brief Get last error message
     */
    const QString& getLastError() const { return m_lastError; }

private:
    QString m_lastError;

    /**
     * @brief Validate data format for specific barcode type
     */
    bool validateData(const QString& data, BarcodeFormat format);

    /**
     * @brief Encode data using specific format
     * Returns encoded bit string
     */
    QString encodeData(const QString& data, BarcodeFormat format);
};

} // namespace LabelDesigner
