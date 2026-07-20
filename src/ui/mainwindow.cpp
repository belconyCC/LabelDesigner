*** Begin Patch
*** Update File: src/ui/mainwindow.cpp
@@
 #include "widgets/label_editor_widget.h"
 #include "widgets/layout_designer_widget.h"
 #include "widgets/package_code_designer_widget.h"
 #include "widgets/preview_widget.h"
+#include "src/utils/json_parser.h"
@@
 MainWindow::MainWindow(QWidget* parent)
     : QMainWindow(parent),
       m_labelManager(std::make_unique<LabelManager>()),
       m_layoutEngine(std::make_unique<LayoutEngine>()),
       m_counterManager(std::make_unique<CounterManager>()),
       m_fileManager(std::make_unique<FileManager>()),
-      m_isModified(false) {
+      m_isModified(false) {
+    m_jsonParser = std::make_unique<JsonParser>();
@@
-    m_labelEditorWidget = new LabelEditorWidget();
-    m_layoutDesignerWidget = new LayoutDesignerWidget();
+    m_labelEditorWidget = new LabelEditorWidget(m_labelManager.get(), m_jsonParser.get());
+    m_layoutDesignerWidget = new LayoutDesignerWidget();
@@
-    m_packageCodeDesignerWidget = new PackageCodeDesignerWidget();
-    m_previewWidget = new PreviewWidget();
+    m_packageCodeDesignerWidget = new PackageCodeDesignerWidget();
+    m_previewWidget = new PreviewWidget(m_labelManager.get(), m_jsonParser.get());
*** End Patch
