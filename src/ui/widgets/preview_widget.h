#pragma once

#include <QWidget>

namespace LabelDesigner {
class LabelManager;

class PreviewWidget : public QWidget {
    Q_OBJECT

public:
    explicit PreviewWidget(LabelManager* manager, QWidget* parent = nullptr);
    ~PreviewWidget();

    void updatePreview();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void createUI();
    LabelManager* m_labelManager;
    QLabel* m_previewLabel;
};

} // namespace LabelDesigner
