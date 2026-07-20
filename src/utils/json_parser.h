*** Begin Patch
*** Update File: src/utils/json_parser.h
@@
     std::vector<QString> getAllPaths(int arrayIndexLimit = 3) const;
+
+    /**
+     * @brief Serialize currently loaded JSON to string
+     */
+    QString toJsonString() const;
*** End Patch
