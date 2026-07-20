*** Begin Patch
*** Update File: src/ui/dialogs/add_element_dialog.cpp
@@
 void AddElementDialog::onLoadJsonClicked() {
@@
-    // Populate binding paths (recursively)
-    m->m_bindingPaths->clear();
-    auto paths = parser->getAllPaths(3);
-    for (const auto& p : paths) {
-        m->m_bindingPaths->addItem(p);
-    }
+    // Populate binding paths (recursively)
+    m->m_bindingPaths->clear();
+    auto paths = parser->getAllPaths(3);
+    for (const auto& p : paths) {
+        m->m_bindingPaths->addItem(p);
+    }
+
+    // Notify that a JSON was loaded into the parser
+    emit jsonLoaded();
 }
*** End Patch
