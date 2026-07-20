# CMake tests

find_package(Qt5 COMPONENTS Test Core REQUIRED)

add_executable(TestJsonParser tests/test_jsonparser.cpp src/utils/json_parser.cpp)
target_include_directories(TestJsonParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(TestJsonParser PRIVATE Qt5::Test Qt5::Core)
add_test(NAME TestJsonParser COMMAND TestJsonParser)

add_executable(TestLabelManager tests/test_labelmanager.cpp src/core/label_info/label_manager.cpp src/models/label_element.cpp src/models/fixed_info_element.cpp src/models/binding_info_element.cpp)
target_include_directories(TestLabelManager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(TestLabelManager PRIVATE Qt5::Test Qt5::Core)
add_test(NAME TestLabelManager COMMAND TestLabelManager)
