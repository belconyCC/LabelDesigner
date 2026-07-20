*** Begin Patch
*** Update File: src/core/file_manager/file_manager.h
@@
-    bool saveProject(const QString& filePath, const QString& projectName,
-                     const LabelManager& labelManager);
+    bool saveProject(const QString& filePath, const QString& projectName,
+                     const LabelManager& labelManager,
+                     const QString& bindingJson = QString());
@@
-    bool loadProject(const QString& filePath, QString& projectName,
-                     LabelManager& labelManager);
+    bool loadProject(const QString& filePath, QString& projectName,
+                     LabelManager& labelManager,
+                     QString* outBindingJson = nullptr);
*** End Patch
