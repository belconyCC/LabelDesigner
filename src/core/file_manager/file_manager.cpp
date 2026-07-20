*** Begin Patch
*** Update File: src/core/file_manager/file_manager.cpp
@@
 bool FileManager::saveProject(const QString& filePath, const QString& projectName,
                               const LabelManager& labelManager) {
-    QJsonObject root;
+bool FileManager::saveProject(const QString& filePath, const QString& projectName,
+                              const LabelManager& labelManager,
+                              const QString& bindingJson) {
+    QJsonObject root;
     root["project_name"] = projectName;
@@
-    QJsonDocument elementsDoc = QJsonDocument::fromJson(labelManager.toJson().toUtf8());
-    if (elementsDoc.isObject()) {
-        root["label_data"] = elementsDoc.object();
-    }
+    QJsonDocument elementsDoc = QJsonDocument::fromJson(labelManager.toJson().toUtf8());
+    if (elementsDoc.isObject()) {
+        root["label_data"] = elementsDoc.object();
+    }
+    // Save binding JSON if provided
+    if (!bindingJson.isEmpty()) {
+        QJsonDocument bindDoc = QJsonDocument::fromJson(bindingJson.toUtf8());
+        if (bindDoc.isObject() || bindDoc.isArray()) {
+            root["binding_data"] = bindDoc.object().isEmpty() ? QJsonValue(bindDoc.array()) : QJsonValue(bindDoc.object());
+        }
+    }
@@
 bool FileManager::loadProject(const QString& filePath, QString& projectName,
-                              LabelManager& labelManager) {
+                              LabelManager& labelManager,
+                              QString* outBindingJson) {
     QFile file(filePath);
     if (!file.open(QIODevice::ReadOnly)) {
         m_lastError = QString("Cannot open file for reading: %1").arg(filePath);
         return false;
     }
@@
     QJsonObject root = doc.object();
     projectName = root["project_name"].toString();
     
     // Load elements
     QJsonObject labelData = root["label_data"].toObject();
     QString labelDataJson = QString::fromUtf8(QJsonDocument(labelData).toJson());
     labelManager.fromJson(labelDataJson);
+    
+    // Load binding data if exists
+    if (outBindingJson) {
+        if (root.contains("binding_data")) {
+            QJsonValue bd = root["binding_data"];
+            QJsonDocument bdDoc;
+            if (bd.isObject()) bdDoc.setObject(bd.toObject());
+            else if (bd.isArray()) bdDoc.setArray(bd.toArray());
+            *outBindingJson = QString::fromUtf8(bdDoc.toJson(QJsonDocument::Compact));
+        } else {
+            *outBindingJson = QString();
+        }
+    }
     
     return true;
 }
*** End Patch
