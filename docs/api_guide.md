# API Guide

This document provides a quick reference for key public APIs and usage examples.

JsonParser

- bool loadJson(const QString& jsonStr);
- bool loadJsonFile(const QString& filePath);
- QVariant getValue(const QString& jsonPath, const QVariant& defaultValue = QVariant());
- QString getString(const QString& jsonPath, const QString& defaultValue = "");
- std::vector<QString> getAllPaths(int arrayIndexLimit = 3) const;
- QString toJsonString() const;

Example: load JSON and list binding paths

```cpp
LabelDesigner::JsonParser parser;
parser.loadJsonFile("examples/sample_label.json");
auto paths = parser.getAllPaths(5);
for (const auto &p : paths) qDebug() << p;
```

LabelManager

- void addElement(LabelElementPtr element);
- bool removeElement(const QString& elementId);
- LabelElementPtr getElement(const QString& elementId) const;
- const std::vector<LabelElementPtr>& getElements() const;
- QString toJson() const; // Serialize all elements
- void fromJson(const QString& json); // Deserialize elements

Example: create a fixed element and add it

```cpp
auto e = std::make_shared<FixedInfoElement>("Title");
e->setText("Hello World");
labelManager.addElement(e);
```

BindingInfoElement

- Holds a JSON path string (e.g., "$.product.name" or "$.serial[0]") which is resolved at render time by PreviewWidget using the shared JsonParser.
- Use AddElementDialog to create or edit binding paths (UI enumerates available paths).

FileManager

- bool saveProject(const QString& filePath, const QString& projectName, const LabelManager& labelManager, const QString& bindingJson = QString());
- bool loadProject(const QString& filePath, QString& projectName, LabelManager& labelManager, QString* outBindingJson = nullptr);

- When saving a project, pass the current binding JSON text (JsonParser::toJsonString()) to persist it as "binding_data" in the project file. On load, the binding JSON will be returned to the caller so it can be loaded into the shared JsonParser.

PreviewWidget

- Constructed with LabelManager* and JsonParser* to read elements and resolve bindings.
- Call updatePreview() to force re-render; the preview auto-updates when elements are added/edited or when the dialog loads new JSON into the shared parser.

Barcode/QRCode Generators

- BarcodeGenerator and QRCodeGenerator provide APIs to produce QPixmap images. Current implementations are placeholders. For production quality barcodes, integrate zint/qrencode on Windows via vcpkg and update the generator implementations to call library APIs and convert output to QImage/QPixmap.

