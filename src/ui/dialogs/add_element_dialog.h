#pragma once

#include <QDialog>
#include <QString>

namespace LabelDesigner {

class JsonParser;

class AddElementDialog : public QDialog {
    Q_OBJECT
public:
    enum class ElementType {
        FixedInfo,
        BindingInfo,
        TimeInfo,
        Barcode,
        QRCode,
        Image
    };

    explicit AddElementDialog(QWidget* parent = nullptr);
    explicit AddElementDialog(JsonParser* sharedParser, QWidget* parent = nullptr);
    ~AddElementDialog();

    ElementType selectedType() const;
    QString elementName() const;

    // For FixedInfo
    QString fixedText() const;

    // For BindingInfo
    QString bindingJsonPath() const;

signals:
    void jsonLoaded();

private slots:
    void onTypeChanged(int index);
    void onLoadJsonClicked();

private:
    struct Impl;
    Impl* m;
};

} // namespace LabelDesigner
