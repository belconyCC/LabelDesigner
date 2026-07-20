# 工业物料标签设计工具 (Label Designer)

## 项目概述

一个专业的Windows平台工业物料标签设计工具，支持复杂的标签信息编辑、灵活的布局设计、包码生成等功能。

### 核心特性
- 📋 **标签信息编辑** - 支持固定信息、绑定信息、时间、条码、二维码、图片等
- 🎨 **灵活布局设计** - 栅格布局、分栏、框线、字体管理
- 📦 **包码设计工具** - 信息组合、计数管理、批量清零
- 💾 **项目文件管理** - JSON配置、导入导出
- 🔌 **插件系统** - 易于扩展新功能

## 技术栈

| 项目 | 版本 |
|------|------|
| 语言 | C++14 |
| 平台 | Windows |
| UI框架 | Qt 5.15+ |
| 构建系统 | CMake 3.16+ |

## 项目结构

```
LabelDesigner/
├── src/
│   ├── core/                    # 核心业务逻辑
│   │   ├── label_info/          # 标签信息管理
│   │   ├── layout/              # 布局引擎
│   │   ├── package_code/        # 包码引擎
│   │   └── file_manager/        # 文件管理
│   ├── models/                  # 数据模型
│   │   ├── label_element.h      # 标签元素基类
│   │   ├── label_element.cpp
│   │   └── ...
│   ├── ui/                      # UI层
│   │   ├── mainwindow.h
│   │   ├── mainwindow.cpp
│   │   ├── widgets/             # UI组件
│   │   └── dialogs/             # 对话框
│   ├── utils/                   # 工具类
│   │   ├── json_parser.h
│   │   ├── barcode_generator.h
│   │   └── qrcode_generator.h
│   ├── plugins/                 # 插件系统
│   └── main.cpp
├── tests/                       # 单元测试
├── resources/                   # 资源文件
│   └── qml/
├── docs/                        # 文档
│   ├── architecture.md          # 架构设计
│   ├── api_guide.md             # API指南
│   └── plugin_guide.md          # 插件开发指南
├── examples/                    # 示例配置
│   └── sample_label.json
├── CMakeLists.txt
└── .gitignore
```

## 快速开始

### 系统要求
- Windows 7 或更高版本
- Qt 5.15 或更高版本
- Visual Studio 2015 或更高版本（或其他支持C++14的编译器）
- CMake 3.16 或更高版本

### 编译步骤

```bash
# 1. 克隆仓库
git clone https://github.com/belconyCC/LabelDesigner.git
cd LabelDesigner

# 2. 创建构建目录
mkdir build
cd build

# 3. 配置CMake
cmake .. -G "Visual Studio 16 2019" -A x64

# 4. 编译
cmake --build . --config Release

# 5. 运行
.\Release\LabelDesigner.exe
```

## 核心模块说明

### 1. 标签信息编辑 (Label Info Module)
支持多种信息类型的灵活编辑和管理。

#### 支持的信息类型
- **固定信息** - 静态文本内容
- **绑定信息** - 从JSON文件动态解析
- **时间信息** - 年月日时分秒、周数
- **条码** - 支持多种编码格式、尺寸设置
- **二维码** - 可自定义格式、宽高、编码
- **图片** - 嵌入式图片支持
- **可扩展** - 插件系统支持自定义类型

### 2. 布局设计 (Layout Designer Module)
灵活的布局引擎，支持复杂的标签排版需求。

#### 主要特性
- 栅格系统 - 精确的位置控制
- 分栏支持 - 多列布局
- 框线管理 - 可配置的边框
- 字体管理 - 相对大小选择
- 实时预览 - 所见即所得

### 3. 包码设计 (Package Code Module)
用于生成包含多信息的包码。

#### 功能特性
- 固定信息嵌入
- 绑定信息引用
- 时间戳自动生成
- 计数管理
  - 设定最大值/最小值
  - 显示位数配置
  - 自动补零
  - 按绑定信息分类清零
  - 手动清零按钮

### 4. 文件管理 (File Manager Module)
完整的项目文件读写支持。

#### 支持格式
- `.ldf` - Label Designer File（主项目格式）
- `.json` - 标签配置导出/导入
- `.png/.jpg/.bmp` - 图片资源
- `.csv` - 绑定数据导入

## 架构设计原则

### 1. UI与业务分离
- 所有业务逻辑独立于Qt框架
- UI层仅负责展示和用户交互
- 通过信号/槽或观察者模式通信

### 2. 高内聚、低耦合
- 按功能模块划分
- 模块间通过接口通信
- 最小化模块依赖

### 3. 强扩展性
- 插件系统支持功能扩展
- 工厂模式用于对象创建
- 策略模式支持多种实现

### 4. 强复用性
- 基类和接口定义清晰
- 通用工具集中管理
- 组件化UI设计

## 设计模式应用

| 模式 | 应用场景 |
|------|--------|
| **MVC** | UI与业务分离 |
| **策略模式** | 不同信息类型处理 |
| **工厂模式** | 标签元素创建 |
| **观察者模式** | UI更新联动 |
| **模板方法** | 统一的处理流程 |
| **插件模式** | 功能动态加载 |

## 使用示例

### 创建标签项目

```cpp
#include "core/label_info/label_manager.h"

LabelManager manager;

// 添加固定信息
auto fixed_info = manager.addElement<FixedInfoElement>("标题");
fixed_info->setText("物料标签");

// 添加绑定信息
auto binding_info = manager.addElement<BindingInfoElement>("型号");
binding_info->bindToJsonPath("$.model");

// 添加条码
auto barcode = manager.addElement<BarcodeElement>("条码");
barcode->setFormat(BarcodeFormat::Code128);
barcode->setSize(100, 50);

// 保存项目
manager.saveProject("my_label.ldf");
```

## 文档

- [架构设计文档](docs/architecture.md)
- [API参考指南](docs/api_guide.md)
- [插件开发指南](docs/plugin_guide.md)
- [配置文件格式](docs/config_format.md)

## 贡献指南

欢迎提交Issues和Pull Requests！

## 许可证

MIT License - 详见 LICENSE 文件

## 联系方式

- 项目主页: https://github.com/belconyCC/LabelDesigner
- Issue追踪: https://github.com/belconyCC/LabelDesigner/issues
