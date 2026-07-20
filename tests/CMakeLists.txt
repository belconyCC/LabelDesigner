*** Begin Patch
*** Update File: tests/CMakeLists.txt
@@
 add_test(NAME TestJsonParser COMMAND TestJsonParser)
 
 add_executable(TestLabelManager tests/test_labelmanager.cpp src/core/label_info/label_manager.cpp src/models/label_element.cpp src/models/fixed_info_element.cpp src/models/binding_info_element.cpp)
 target_include_directories(TestLabelManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
 target_link_libraries(TestLabelManager PRIVATE Qt5::Test Qt5::Core)
 add_test(NAME TestLabelManager COMMAND TestLabelManager)
+
+add_executable(TestCounterManager tests/test_countermanager.cpp src/core/package_code/counter_manager.cpp)
+target_include_directories(TestCounterManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
+target_link_libraries(TestCounterManager PRIVATE Qt5::Test Qt5::Core)
+add_test(NAME TestCounterManager COMMAND TestCounterManager)
+
+add_executable(TestFileManager tests/test_filemanager.cpp src/core/file_manager/file_manager.cpp src/core/label_info/label_manager.cpp src/models/label_element.cpp src/models/fixed_info_element.cpp)
+target_include_directories(TestFileManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
+target_link_libraries(TestFileManager PRIVATE Qt5::Test Qt5::Core)
+add_test(NAME TestFileManager COMMAND TestFileManager)
*** End Patch
