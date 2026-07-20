*** Begin Patch
*** Update File: src/ui/widgets/preview_widget.h
@@
 class PreviewWidget : public QWidget {
     Q_OBJECT
@@
 private:
     void createUI();
     LabelManager* m_labelManager;
     JsonParser* m_jsonParser;
     QLabel* m_previewLabel;
 };
*** End Patch
