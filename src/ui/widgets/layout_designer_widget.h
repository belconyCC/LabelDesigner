#pragma once

#include <QWidget>

class QSpinBox;
class QComboBox;
class QSlider;

namespace LabelDesigner {

/**
 * @brief Layout designer widget
 * Provides UI for designing label layout
 */
class LayoutDesignerWidget : public QWidget {
    Q_OBJECT

public:
    explicit LayoutDesignerWidget(QWidget* parent = nullptr);
    ~LayoutDesignerWidget();

private slots:
    void onRowsChanged(int rows);
    void onColumnsChanged(int cols);
    void onCellWidthChanged(int width);
    void onCellHeightChanged(int height);

private:
    void createUI();
    void setupConnections();

    QSpinBox* m_rowsSpinBox;
    QSpinBox* m_columnsSpinBox;
    QSpinBox* m_cellWidthSpinBox;
    QSpinBox* m_cellHeightSpinBox;
};

} // namespace LabelDesigner
