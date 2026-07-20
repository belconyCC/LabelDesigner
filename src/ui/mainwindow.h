*** Begin Patch
*** Update File: src/ui/mainwindow.h
@@
     std::unique_ptr<LabelManager> m_labelManager;
     std::unique_ptr<LayoutEngine> m_layoutEngine;
     std::unique_ptr<CounterManager> m_counterManager;
     std::unique_ptr<FileManager> m_fileManager;
+    // Shared JSON parser for binding data
+    std::unique_ptr<JsonParser> m_jsonParser;
@@
-    // UI Components
-    LabelEditorWidget* m_labelEditorWidget;
-    LayoutDesignerWidget* m_layoutDesignerWidget;
-    PackageCodeDesignerWidget* m_packageCodeDesignerWidget;
-    PreviewWidget* m_previewWidget;
+    // UI Components
+    LabelEditorWidget* m_labelEditorWidget;
+    LayoutDesignerWidget* m_layoutDesignerWidget;
+    PackageCodeDesignerWidget* m_packageCodeDesignerWidget;
+    PreviewWidget* m_previewWidget;
*** End Patch
