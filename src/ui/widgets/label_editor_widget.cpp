*** Begin Patch
*** Update File: src/ui/widgets/label_editor_widget.cpp
@@
 void LabelEditorWidget::onAddElement() {
-    AddElementDialog dlg(m_jsonParser, this);
+    AddElementDialog dlg(m_jsonParser, this);
+    // If the dialog loads JSON into the shared parser, we want to refresh preview
+    connect(&dlg, &AddElementDialog::jsonLoaded, [this]() {
+        emit elementsChanged();
+    });
     if (dlg.exec() != QDialog::Accepted) return;
@@
     }
     refreshElementList();
+    emit elementsChanged();
 }
@@
 void LabelEditorWidget::onDeleteElement() {
@@
             m_labelManager->removeElement(id);
             refreshElementList();
+            emit elementsChanged();
         }
     }
 }
*** End Patch
