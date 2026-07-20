cmake_minimum_required(VERSION 3.16)
project(LabelDesigner LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt5 COMPONENTS Core Gui Widgets Svg REQUIRED)

# Enable Qt automoc, uic, rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add source files
set(SOURCES
    # Main
    src/main.cpp
    
    # UI Layer
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/widgets/label_editor_widget.cpp
    src/ui/widgets/label_editor_widget.h
    src/ui/widgets/layout_designer_widget.cpp
    src/ui/widgets/layout_designer_widget.h
    src/ui/widgets/package_code_designer_widget.cpp
    src/ui/widgets/package_code_designer_widget.h
    src/ui/widgets/preview_widget.cpp
    src/ui/widgets/preview_widget.h
    src/ui/widgets/property_panel.cpp
    src/ui/widgets/property_panel.h
    
    # Models Layer
    src/models/label_element.cpp
    src/models/label_element.h
    src/models/fixed_info_element.cpp
    src/models/fixed_info_element.h
    src/models/binding_info_element.cpp
    src/models/binding_info_element.h
    src/models/time_info_element.cpp
    src/models/time_info_element.h
    src/models/barcode_element.cpp
    src/models/barcode_element.h
    src/models/qrcode_element.cpp
    src/models/qrcode_element.h
    src/models/image_element.cpp
    src/models/image_element.h
    src/models/layout_cell.cpp
    src/models/layout_cell.h
    
    # Core Business Logic
    src/core/label_info/label_manager.cpp
    src/core/label_info/label_manager.h
    src/core/label_info/element_factory.cpp
    src/core/label_info/element_factory.h
    
    src/core/layout/layout_engine.cpp
    src/core/layout/layout_engine.h
    src/core/layout/grid_layout.cpp
    src/core/layout/grid_layout.h
    
    src/core/package_code/package_code_engine.cpp
    src/core/package_code/package_code_engine.h
    src/core/package_code/counter_manager.cpp
    src/core/package_code/counter_manager.h
    
    src/core/file_manager/file_manager.cpp
    src/core/file_manager/file_manager.h
    src/core/file_manager/project_serializer.cpp
    src/core/file_manager/project_serializer.h
    
    # Utils
    src/utils/json_parser.cpp
    src/utils/json_parser.h
    src/utils/barcode_generator.cpp
    src/utils/barcode_generator.h
    src/utils/qrcode_generator.cpp
    src/utils/qrcode_generator.h
    src/utils/image_processor.cpp
    src/utils/image_processor.h
    
    # Plugin System
    src/plugins/plugin_interface.h
    src/plugins/plugin_manager.cpp
    src/plugins/plugin_manager.h
)

# Add resources
set(RESOURCES
    resources/resources.qrc
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets 
    Qt5::Svg
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugins
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Compiler-specific settings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Enable testing
enable_testing()

# Add subdirectories for tests
add_subdirectory(tests)
