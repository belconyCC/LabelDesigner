#include "image_processor.h"
#include <QFile>
#include <QImage>
#include <QTransform>

namespace LabelDesigner {

ImageProcessor::ImageProcessor() {
}

ImageProcessor::~ImageProcessor() {
}

QPixmap ImageProcessor::loadImage(const QString& filePath) {
    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        m_lastError = QString("Failed to load image: %1").arg(filePath);
        return QPixmap();
    }
    return pixmap;
}

QPixmap ImageProcessor::scaleImage(const QPixmap& pixmap,
                                  int maxWidth,
                                  int maxHeight,
                                  bool maintainAspectRatio) {
    if (pixmap.isNull()) {
        m_lastError = "Input pixmap is null";
        return QPixmap();
    }
    
    Qt::AspectRatioMode mode = maintainAspectRatio ?
        Qt::KeepAspectRatio : Qt::IgnoreAspectRatio;
    
    QPixmap scaled = pixmap.scaledToWidth(maxWidth, mode);
    if (scaled.height() > maxHeight) {
        scaled = pixmap.scaledToHeight(maxHeight, mode);
    }
    
    return scaled;
}

QPixmap ImageProcessor::applyOpacity(const QPixmap& pixmap, int opacity) {
    if (pixmap.isNull()) {
        m_lastError = "Input pixmap is null";
        return QPixmap();
    }
    
    if (opacity < 0) opacity = 0;
    if (opacity > 255) opacity = 255;
    
    QImage image = pixmap.toImage();
    
    if (image.format() != QImage::Format_ARGB32 &&
        image.format() != QImage::Format_ARGB32_Premultiplied) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }
    
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color(image.pixel(x, y));
            color.setAlpha(static_cast<int>(color.alpha() * opacity / 255.0));
            image.setPixel(x, y, color.rgba());
        }
    }
    
    return QPixmap::fromImage(image);
}

QPixmap ImageProcessor::rotateImage(const QPixmap& pixmap, int degrees) {
    if (pixmap.isNull()) {
        m_lastError = "Input pixmap is null";
        return QPixmap();
    }
    
    QImage image = pixmap.toImage();
    QTransform transform;
    transform.rotate(degrees);
    QImage rotated = image.transformed(transform, Qt::SmoothTransformation);
    
    return QPixmap::fromImage(rotated);
}

QPixmap ImageProcessor::toGrayscale(const QPixmap& pixmap) {
    if (pixmap.isNull()) {
        m_lastError = "Input pixmap is null";
        return QPixmap();
    }
    
    QImage image = pixmap.toImage();
    
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color(image.pixel(x, y));
            int gray = (color.red() + color.green() + color.blue()) / 3;
            image.setPixel(x, y, qRgb(gray, gray, gray));
        }
    }
    
    return QPixmap::fromImage(image);
}

bool ImageProcessor::saveImage(const QPixmap& pixmap, const QString& filePath) {
    if (pixmap.isNull()) {
        m_lastError = "Input pixmap is null";
        return false;
    }
    
    if (!pixmap.save(filePath)) {
        m_lastError = QString("Failed to save image: %1").arg(filePath);
        return false;
    }
    
    return true;
}

} // namespace LabelDesigner
