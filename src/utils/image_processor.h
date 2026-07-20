#pragma once

#include <QString>
#include <QPixmap>
#include <QImage>

namespace LabelDesigner {

/**
 * @brief Image processing utility
 * Handles image loading, scaling, and manipulation
 */
class ImageProcessor {
public:
    ImageProcessor();
    ~ImageProcessor();

    /**
     * @brief Load image from file
     */
    QPixmap loadImage(const QString& filePath);

    /**
     * @brief Scale image to fit dimensions while maintaining aspect ratio
     */
    QPixmap scaleImage(const QPixmap& pixmap,
                      int maxWidth,
                      int maxHeight,
                      bool maintainAspectRatio = true);

    /**
     * @brief Apply opacity to image
     */
    QPixmap applyOpacity(const QPixmap& pixmap, int opacity);

    /**
     * @brief Rotate image
     */
    QPixmap rotateImage(const QPixmap& pixmap, int degrees);

    /**
     * @brief Convert image to grayscale
     */
    QPixmap toGrayscale(const QPixmap& pixmap);

    /**
     * @brief Save image to file
     */
    bool saveImage(const QPixmap& pixmap, const QString& filePath);

    /**
     * @brief Get last error message
     */
    const QString& getLastError() const { return m_lastError; }

private:
    QString m_lastError;
};

} // namespace LabelDesigner
