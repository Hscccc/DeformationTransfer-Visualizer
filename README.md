# Deformation Transfer Visualizer

## 项目简介
Deformation Transfer Visualizer 是一个基于 OpenGL 的 3D 可视化工具，用于加载和渲染 3D 模型，并支持光照效果的实时切换（Gouraud 和 Phong 着色）。该项目使用 OpenMesh 进行模型加载，支持用户交互以调整光源位置、模型缩放和旋转。

---

## 功能特性
- **模型加载**：支持 `.obj` 格式的 3D 模型加载。
- **实时光照**：支持 Gouraud 和 Phong 两种光照模式的切换。
- **用户交互**：
  - 调整光源位置（W/S/A/D/Q/E 键）。
  - 调整模型缩放（方向键 UP/DOWN）。
  - 调整模型旋转（方向键 LEFT/RIGHT）。
  - 切换光照模式（G 键切换到 Gouraud，P 键切换到 Phong）。
- **光源可视化**：通过颜色高亮显示光源位置。

---

## 环境依赖
- **操作系统**：macOS
- **开发工具**：C++17
- **依赖库**：
  - [OpenGL](https://www.opengl.org/)
  - [GLEW](http://glew.sourceforge.net/)
  - [GLFW](https://www.glfw.org/)
  - [OpenMesh](https://www.openmesh.org/)
  - [GLM](https://github.com/g-truc/glm)

---

## 编译与运行
### 1. 配置依赖
确保已安装以下依赖库：
- GLEW
- GLFW
- OpenMesh
- GLM

### 2. 编译项目
使用 `CMake` 进行编译：
```bash
./build.sh
```

### 3. 运行程序
```bash
./build/DeformationTransferVisualizer 
```

---

## 使用说明
### 键盘交互
| 按键       | 功能                     |
|------------|--------------------------|
| `W/S`      | 上/下移动光源            |
| `A/D`      | 左/右移动光源            |
| `Q/E`      | 前/后移动光源            |
| `UP/DOWN`  | 放大/缩小模型            |
| `LEFT/RIGHT` | 旋转模型               |
| `G`        | 切换到 Gouraud 着色模式  |
| `P`        | 切换到 Phong 着色模式    |

---

## 文件结构
```
DeformationTransfer-Visualizer/
├── ModelLoader.cpp       # 模型加载与渲染逻辑
├── ModelLoader.h         # 模型加载类定义
├── main.cpp              # 主程序入口
├── shaders/              # 着色器文件
│   ├── vertex_shader.glsl   # 顶点着色器
│   ├── fragment_shader.glsl # 片段着色器
├── README.md             # 项目文档
```

---

## 注意事项
1. 确保模型文件路径正确，例如 `t1.obj`。
2. 如果模型不可见，请检查光源位置和模型的缩放比例。
3. 如果出现 OpenGL 错误，请确保显卡驱动已更新并支持 OpenGL 3.3 或更高版本。


