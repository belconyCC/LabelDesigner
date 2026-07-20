*** Begin Patch
*** Update File: src/ui/mainwindow.cpp
@@
 void MainWindow::createCentralWidget() {
@@
-    // Create left panel: Label Editor and Layout Designer
+    // Create left panel: Label Editor and Layout Designer
     QSplitter* leftSplitter = new QSplitter(Qt::Vertical);
-    m_labelEditorWidget = new LabelEditorWidget(m_labelManager.get(), m_jsonParser.get());
+    m_labelEditorWidget = new LabelEditorWidget(m_labelManager.get(), m_jsonParser.get());
     m_layoutDesignerWidget = new LayoutDesignerWidget();
     leftSplitter->addWidget(m_labelEditorWidget);
     leftSplitter->addWidget(m_layoutDesignerWidget);
@@
     QSplitter* rightSplitter = new QSplitter(Qt::Vertical);
     m_packageCodeDesignerWidget = new PackageCodeDesignerWidget();
-    m_previewWidget = new PreviewWidget(m_labelManager.get(), m_jsonParser.get());
+    m_previewWidget = new PreviewWidget(m_labelManager.get(), m_jsonParser.get());
     rightSplitter->addWidget(m_packageCodeDesignerWidget);
     rightSplitter->addWidget(m_previewWidget);
@@
 }
@@
 void MainWindow::setupConnections() {
-    // Connect signals/slots for UI synchronization
+    // Connect signals/slots for UI synchronization
+    if (m_labelEditorWidget && m_previewWidget) {
+        connect(m_labelEditorWidget, &LabelEditorWidget::elementsChanged, m_previewWidget, &PreviewWidget::updatePreview);
+    }
 }
*** End Patch
