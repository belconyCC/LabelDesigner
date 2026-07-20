*** Begin Patch
*** Update File: src/ui/widgets/label_editor_widget.h
@@
 class LabelEditorWidget : public QWidget {
     Q_OBJECT
@@
 private:
     LabelManager* m_labelManager;
     JsonParser* m_jsonParser;
@@
 };
+
+signals:
+    void elementsChanged();
*** End Patch
