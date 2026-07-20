*** Begin Patch
*** Update File: src/ui/widgets/label_editor_widget.cpp
@@
 #include "../../models/binding_info_element.h"
+#include "../dialogs/element_properties_dialog.h"
@@
 void LabelEditorWidget::onEditElement() {
     int row = m_elementList->currentRow();
     if (row < 0) return;
     const auto& elems = m_labelManager->getElements();
     if (row >= static_cast<int>(elems.size())) return;
-    auto e = elems[row];
+    auto e = elems[row];
     // For demo, only allow editing FixedInfo text and BindingInfo path
-    if (e->getType() == LabelElement::ElementType::FixedInfo) {
-        FixedInfoElement* f = dynamic_cast<FixedInfoElement*>(e.get());
-        if (!f) return;
-        bool ok;
-        QString text = QInputDialog::getText(this, "Edit Fixed Text", "Text:", QLineEdit::Normal, f->getText(), &ok);
-        if (ok) {
-            f->setText(text);
-            refreshElementList();
-        }
-    } else if (e->getType() == LabelElement::ElementType::BindingInfo) {
-        BindingInfoElement* b = dynamic_cast<BindingInfoElement*>(e.get());
-        if (!b) return;
-        AddElementDialog dlg(m_jsonParser, this);
-        // Pre-fill name and selection
-        dlg.exec();
-        QString path = dlg.bindingJsonPath();
-        if (!path.isEmpty()) {
-            b->setJsonPath(path);
-            refreshElementList();
-        }
-    } else {
-        QMessageBox::information(this, "Edit", "Edit not implemented for this element type yet.");
-    }
+    // Open generic properties dialog for element
+    ElementPropertiesDialog dlg(e, m_jsonParser, this);
+    if (dlg.exec() == QDialog::Accepted) {
+        refreshElementList();
+        emit elementsChanged();
+    }
 }
*** End Patch
