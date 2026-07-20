*** Begin Patch
*** Update File: src/ui/mainwindow.cpp
@@
 void MainWindow::onSaveProjectAs() {
     QString filePath = QFileDialog::getSaveFileName(
         this, "Save Project As", "",
         "Label Designer Files (*.ldf);;All Files (*)");
     
     if (filePath.isEmpty()) return;
     
     QString projectName = QFileInfo(filePath).baseName();
-    if (m_fileManager->saveProject(filePath, projectName, *m_labelManager)) {
+    QString bindingJson = m_jsonParser ? m_jsonParser->toJsonString() : QString();
+    if (m_fileManager->saveProject(filePath, projectName, *m_labelManager, bindingJson)) {
         m_currentFilePath = filePath;
         m_isModified = false;
         setWindowTitle(QString("Label Designer - %1").arg(projectName));
         QMessageBox::information(this, "Success", "Project saved successfully!");
     } else {
         QMessageBox::critical(this, "Error",
             QString("Failed to save project: %1").arg(m_fileManager->getLastError()));
     }
 }
*** End Patch
