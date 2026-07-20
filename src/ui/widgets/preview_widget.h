#pragma once

#include <QWidget>

class QLabel;

namespace LabelDesigner {

/**
 * @brief Preview widget
 * Displays real-time preview of the label design
 */
class PreviewWidget : public QWidget {
    Q_OBJECT

public:
    explicit PreviewWidget(QWidget* parent = nullptr);
    ~PreviewWidget();

    /**
     * @brief Update preview with new label data
     */
    void updatePreview();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void createUI();

    QLabel* m_previewLabel;
};

} // namespace LabelDesigner
