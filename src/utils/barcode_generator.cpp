#include "barcode_generator.h"
#include <QPainter>
#include <QRegularExpression>

namespace LabelDesigner {

BarcodeGenerator::BarcodeGenerator() {
}

BarcodeGenerator::~BarcodeGenerator() {
}

bool BarcodeGenerator::validateData(const QString& data, BarcodeFormat format) {
    if (data.isEmpty()) {
        m_lastError = "Data cannot be empty";
        return false;
    }
    
    switch (format) {
    case BarcodeFormat::Code128:
        return true;  // Code128 can encode most characters
    
    case BarcodeFormat::Code39:
        // Code39 allows uppercase, digits, and some special characters
        if (!QRegularExpression("^[A-Z0-9\\-. $%*/+]+$").match(data).hasMatch()) {
            m_lastError = "Code39 only allows uppercase, digits, and -. $%*/+";
            return false;
        }
        return true;
    
    case BarcodeFormat::EAN13:
        if (data.length() != 13 || !QRegularExpression("^[0-9]+$").match(data).hasMatch()) {
            m_lastError = "EAN13 requires exactly 13 digits";
            return false;
        }
        return true;
    
    case BarcodeFormat::EAN8:
        if (data.length() != 8 || !QRegularExpression("^[0-9]+$").match(data).hasMatch()) {
            m_lastError = "EAN8 requires exactly 8 digits";
            return false;
        }
        return true;
    
    default:
        return true;
    }
}

QString BarcodeGenerator::encodeData(const QString& data, BarcodeFormat format) {
    // Simplified encoding - in production, use a proper barcode library
    // This is a placeholder for demonstration
    switch (format) {
    case BarcodeFormat::Code128:
        return data;  // Code128 encoding would happen here
    case BarcodeFormat::Code39:
        return data.toUpper();
    case BarcodeFormat::EAN13:
    case BarcodeFormat::EAN8:
        return data;
    default:
        return data;
    }
}

QPixmap BarcodeGenerator::generateBarcode(const QString& data,
                                         BarcodeFormat format,
                                         int width,
                                         int height,
                                         bool showText) {
    if (!validateData(data, format)) {
        return QPixmap();
    }
    
    QString encoded = encodeData(data, format);
    
    // Create pixmap
    int textHeight = showText ? 20 : 0;
    QPixmap pixmap(width, height + textHeight);
    pixmap.fill(Qt::white);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw barcode bars (simplified representation)
    int barWidth = width / (encoded.length() * 2 + 1);
    int xPos = barWidth;
    
    for (int i = 0; i < encoded.length(); ++i) {
        if (encoded[i] == '1') {
            painter.fillRect(xPos, 0, barWidth, height, Qt::black);
        }
        xPos += barWidth * 2;
    }
    
    // Draw text if needed
    if (showText) {
        painter.drawText(0, height, width, textHeight, Qt::AlignCenter, data);
    }
    
    painter.end();
    return pixmap;
}

} // namespace LabelDesigner
