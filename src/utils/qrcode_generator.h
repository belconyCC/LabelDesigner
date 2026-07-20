#pragma once

#include <QString>
#include <QPixmap>

namespace LabelDesigner {

enum class QRCodeErrorCorrection {
    L,  // ~7% correction
    M,  // ~15% correction
    Q,  // ~25% correction
    H   // ~30% correction
};

/**
 * @brief QR Code image generator
 * Generates QR code images from data
 */
class QRCodeGenerator {
public:
    QRCodeGenerator();
    ~QRCodeGenerator();

    /**
     * @brief Generate QR code image
     * @param data Data to encode
     * @param size QR code size in pixels
     * @param errorCorrection Error correction level
     * @param borderSize Border size in modules
     * @return Generated pixmap, empty if failed
     */
    QPixmap generateQRCode(const QString& data,
                          int size,
                          QRCodeErrorCorrection errorCorrection = QRCodeErrorCorrection::M,
                          int borderSize = 4);

    /**
     * @brief Get last error message
     */
    const QString& getLastError() const { return m_lastError; }

private:
    QString m_lastError;
};

} // namespace LabelDesigner
