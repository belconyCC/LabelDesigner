*** Begin Patch
*** Update File: src/ui/mainwindow.h
@@
 #include <memory>
+#include "src/utils/json_parser.h"
@@
     std::unique_ptr<CounterManager> m_counterManager;
     std::unique_ptr<FileManager> m_fileManager;
     // Shared JSON parser for binding data
     std::unique_ptr<JsonParser> m_jsonParser;
@@
     LabelEditorWidget* m_labelEditorWidget;
@@
 };
*** End Patch
