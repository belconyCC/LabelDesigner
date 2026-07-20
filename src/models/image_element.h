#pragma once

#include "label_element.h"
#include <QString>
#include <QPixmap>

namespace LabelDesigner {

/**
 * @brief Image element
 * Represents embedded image in the label
 */
class ImageElement : public LabelElement {
public:
    ImageElement();
    explicit ImageElement(const QString& name);

    ElementType getType() const override {
        return ElementType::Image;
    }

    /**
     * @brief Get image file path
     */
    const QString& getImagePath() const { return m_imagePath; }

    /**
     * @brief Set image file path
     */
    void setImagePath(const QString& path) { m_imagePath = path; }

    /**
     * @brief Get cached pixmap
     */
    const QPixmap& getPixmap() const { return m_pixmap; }

    /**
     * @brief Load image from file
     * @return true if image loaded successfully
     */
    bool loadImage(const QString& path);

    /**
     * @brief Check if image should maintain aspect ratio
     */
    bool isMaintainAspectRatio() const { return m_maintainAspectRatio; }

    /**
     * @brief Set whether to maintain aspect ratio
     */
    void setMaintainAspectRatio(bool maintain) { m_maintainAspectRatio = maintain; }

    /**
     * @brief Get image opacity (0-255)
     */
    int getOpacity() const { return m_opacity; }

    /**
     * @brief Set image opacity
     */
    void setOpacity(int opacity) { m_opacity = opacity; }

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    QString m_imagePath;
    QPixmap m_pixmap;
    bool m_maintainAspectRatio;
    int m_opacity;
};

} // namespace LabelDesigner
