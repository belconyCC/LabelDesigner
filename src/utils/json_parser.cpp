*** Begin Patch
*** Update File: src/utils/json_parser.cpp
@@
 std::vector<QString> JsonParser::getAllPaths(int arrayIndexLimit) const {
@@
 }
+
+QString JsonParser::toJsonString() const {
+    QJsonDocument doc(m_root);
+    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
+}
*** End Patch
