# Architecture

This document gives an overview of the LabelDesigner project's architecture and major components.

Layers

- UI Layer
  - MainWindow: application entry window, menu, toolbars and central widget management.
  - Widgets: LabelEditorWidget, LayoutDesignerWidget, PackageCodeDesignerWidget, PreviewWidget and dialogs for editing/adding elements.
  - Responsibilities: user interactions, element editing, layout configuration, preview rendering.

- Models Layer
  - LabelElement base class and derived element types: FixedInfoElement, BindingInfoElement, TimeInfoElement, BarcodeElement, QRCodeElement, ImageElement.
  - Each element stores geometry, style, content and binding metadata.

- Core Business Logic
  - LabelManager: manages element lifecycle (add/remove/edit), serialization (toJson/fromJson).
  - LayoutEngine: arranges elements into grid/cells and computes layout cells.
  - CounterManager / Package Code Engine: handles package-code counters and sequences.
  - FileManager: project persistence (save/load .ldf, import/export JSON). Recently extended to persist binding data (binding_data) so JSON binding sources are saved with the project.

- Utils
  - JsonParser: JSON loading, recursive path enumeration (getAllPaths), and value extraction by JSONPath-like string (getValue).
  - BarcodeGenerator / QRCodeGenerator: barcode/QR image generation interfaces (placeholder implementations; integration with zint/qrencode planned).
  - ImageProcessor: image loading and manipulation utilities.

- Plugins
  - PluginInterface / PluginManager: runtime extension points for adding features without modifying core code.

Data Flow

- User creates/edits elements in the LabelEditor. Elements are stored in LabelManager.
- When the user loads a JSON file (via Add/Edit dialogs), JsonParser enumerates binding paths and stores the loaded JSON in a shared parser that the UI can access.
- BindingInfo elements store a JSONPath-like string (e.g. $.product.name or $.serial[0] or $.serial[]). PreviewWidget resolves those paths against the shared JsonParser at render time and displays the resolved values.
- FileManager can save the current project including label elements and the loaded binding JSON (binding_data) so that reopening the project restores the binding context.

Extension Points

- To add new element types: create a new LabelElement-derived class, implement serialization/deserialization, and add UI editor and preview rendering code.
- To extend rendering or barcode support: implement proper generators and replace placeholder modules (BarcodeGenerator/QRCodeGenerator) with libraries (zint, qrencode) for production output.

Performance and Safety Notes

- JsonParser.getAllPaths provides array index enumeration limited by a default limit (3) to avoid explosion of enumerated paths. This is configurable in the API.
- Preview rendering resolves binding paths on demand; for very large datasets or extremely large arrays, consider lazy evaluation, pagination, or limiting index enumeration.

