*** Begin Patch
*** Update File: src/ui/mainwindow.cpp
@@
 void MainWindow::onSaveProject() {
     if (m_currentFilePath.isEmpty()) {
         onSaveProjectAs();
     } else {
         QString projectName = QFileInfo(m_currentFilePath).baseName();
-        if (m_fileManager->saveProject(m_currentFilePath, projectName, *m_labelManager)) {
+        QString bindingJson = m_jsonParser ? m_jsonParser->toJsonString() : QString();
+        if (m_fileManager->saveProject(m_currentFilePath, projectName, *m_labelManager, bindingJson)) {
             m_isModified = false;
             QMessageBox::information(this, "Success", "Project saved successfully!");
         } else {
             QMessageBox::critical(this, "Error",
                 QString("Failed to save project: %1").arg(m_fileManager->getLastError()));
         }
     }
 }
@@
 void MainWindow::onOpenProject() {
     if (!maybeSave()) return;
     
     QString filePath = QFileDialog::getOpenFileName(
         this, "Open Project", "",
         "Label Designer Files (*.ldf);;All Files (*)");
     
     if (filePath.isEmpty()) return;
     
     QString projectName;
-    if (m_fileManager->loadProject(filePath, projectName, *m_labelManager)) {
-        m_currentFilePath = filePath;
-        m_isModified = false;
-        setWindowTitle(QString("Label Designer - %1").arg(projectName));
-    } else {
+    QString bindingJson;
+    if (m_fileManager->loadProject(filePath, projectName, *m_labelManager, &bindingJson)) {
+        // Load binding JSON into shared parser if present
+        if (!bindingJson.isEmpty() && m_jsonParser) {
+            m_jsonParser->loadJson(bindingJson);
+        }
+        m_currentFilePath = filePath;
+        m_isModified = false;
+        setWindowTitle(QString("Label Designer - %1").arg(projectName));
+    } else {
         QMessageBox::critical(this, "Error",
             QString("Failed to load project: %1").arg(m_fileManager->getLastError()));
     }
 }
*** End Patch
