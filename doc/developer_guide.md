# Genius TCAD Open 开发资料文档

> **版本**：1.9.0  
> **作者**：Cogenda Pte Ltd / 开源社区  
> **语言**：C++17 + Fortran  

---

## 目录

1. [项目概述](#1-项目概述)
2. [目录结构](#2-目录结构)
3. [整体架构](#3-整体架构)
4. [核心模块详解](#4-核心模块详解)
   - 4.1 [主程序入口](#41-主程序入口)
   - 4.2 [网格系统](#42-网格系统)
   - 4.3 [仿真区域与数据存储](#43-仿真区域与数据存储)
   - 4.4 [边界条件系统](#44-边界条件系统)
   - 4.5 [材料模型接口（PMI）](#45-材料模型接口pmi)
   - 4.6 [求解器框架](#46-求解器框架)
   - 4.7 [输入文件解析器](#47-输入文件解析器)
   - 4.8 [Hook 插件系统](#48-hook-插件系统)
5. [模块依赖关系](#5-模块依赖关系)
6. [关键算法实现](#6-关键算法实现)
   - 6.1 [泊松方程求解](#61-泊松方程求解)
   - 6.2 [漂移扩散模型（DDM）](#62-漂移扩散模型ddm)
   - 6.3 [能量平衡模型（EBM）](#63-能量平衡模型ebm)
   - 6.4 [有限体积离散化](#64-有限体积离散化)
   - 6.5 [非线性求解流程](#65-非线性求解流程)
   - 6.6 [交流小信号分析](#66-交流小信号分析)
   - 6.7 [瞬态分析](#67-瞬态分析)
   - 6.8 [器件-电路混合仿真](#68-器件-电路混合仿真)
   - 6.9 [光学模型](#69-光学模型)
7. [求解器类型与选择](#7-求解器类型与选择)
8. [算例说明](#8-算例说明)
   - 8.1 [PN 结二极管](#81-pn-结二极管)
   - 8.2 [NPN 双极晶体管（BJT）](#82-npn-双极晶体管bjt)
   - 8.3 [NMOS/PMOS 晶体管](#83-nmospmos-晶体管)
   - 8.4 [肖特基二极管（混合仿真）](#84-肖特基二极管混合仿真)
   - 8.5 [EEPROM 浮栅器件](#85-eeprom-浮栅器件)
   - 8.6 [闸流管（含外部电路）](#86-闸流管含外部电路)
   - 8.7 [陷阱仿真](#87-陷阱仿真)
   - 8.8 [霍尔效应器件](#88-霍尔效应器件)
   - 8.9 [25 nm 纳米 MOSFET](#89-25-nm-纳米-mosfet)
9. [输入文件格式参考](#9-输入文件格式参考)
10. [扩展开发指南](#10-扩展开发指南)
    - 10.1 [自定义材料模型（PMI）](#101-自定义材料模型pmi)
    - 10.2 [自定义 Hook 模块](#102-自定义-hook-模块)
11. [构建与安装](#11-构建与安装)
12. [常见问题](#12-常见问题)

---

## 1. 项目概述

**Genius**（General Purpose Semiconductor Device Simulator）是一款面向半导体器件的二维 TCAD（Technology Computer-Aided Design）仿真工具，原由新加坡 Cogenda Pte Ltd 商业开发，此版本为其开源版本（v1.9.0）。

### 主要功能

| 功能类别 | 具体能力 |
|---------|---------|
| **物理模型** | 漂移扩散、能量平衡、晶格加热 |
| **电学分析** | DC 直流扫描、AC 小信号、瞬态仿真 |
| **高场效应** | 碰撞电离、带间隧穿、热载流子注入 |
| **光学模型** | 二维有限元光学（EM-FEM）、光线追踪 |
| **特殊效应** | 载流子陷阱、霍尔效应、应力效应 |
| **混合仿真** | 器件与 SPICE 电路协同仿真 |
| **文件格式** | 导入/导出 CGNS、VTK、TIF、Silvaco、DF-ISE |

### 开源版本限制

与商业版相比，开源版做了如下裁剪：

- 移除了并行计算功能
- 仅支持二维器件结构
- 使用 Triangle 开源网格生成器（取代专有网格器）
- 仅包含基础材料模型集合

---

## 2. 目录结构

```
Genius-TCAD-Open/
├── src/                        # C++ 源代码（约 504 个 .cc 文件）
│   ├── main.cc                 # 程序入口
│   ├── base/                   # 基础类（自由度对象、内存日志等）
│   ├── bc/                     # 边界条件实现
│   ├── fe/                     # 有限元实现
│   ├── geom/                   # 几何原语（节点、单元、点）
│   ├── hook/                   # 监控与输出插件
│   ├── interpolation/          # 插值工具
│   ├── material/               # 材料属性定义
│   ├── math/                   # 数学工具
│   ├── mesh/                   # 网格数据结构与操作
│   ├── meshgen/                # 网格生成（调用 Triangle）
│   ├── parser/                 # 输入文件解析（FLEX/BISON 生成）
│   ├── partition/              # 域分解（并行预留）
│   ├── quadrature/             # 数值积分规则
│   ├── solution/               # 仿真区域与数据结构
│   ├── solver/                 # 核心求解器
│   │   ├── poisson/            # 非线性泊松求解器
│   │   ├── ddm1/               # 漂移扩散模型 Level 1
│   │   ├── ddm2/               # 漂移扩散模型 Level 2（含载流子温度）
│   │   ├── ebm3/               # 能量平衡模型 Level 3
│   │   ├── ddm_ac/             # 交流小信号求解器
│   │   ├── hall/               # 霍尔效应求解器
│   │   ├── mix1/               # 器件/电路混合仿真（DDM1）
│   │   ├── mixA1/              # 高级混合仿真
│   │   ├── emfem2d/            # 二维 EM-FEM 光学求解器
│   │   ├── ray_tracing/        # 光线追踪光学求解器
│   │   ├── stress_solver/      # 应力/应变求解器
│   │   └── doping_analytic/    # 掺杂分布求解器
│   ├── source/                 # 外部激励源定义
│   ├── utils/                  # 通用工具函数
│   └── contrib/                # 第三方库（Triangle、BLAS/LAPACK Fortran）
│
├── include/                    # 公共头文件（约 335 个 .h 文件）
│   ├── base/                   # 基础类接口
│   ├── bc/                     # 边界条件接口
│   ├── enums/                  # 枚举定义（求解器类型、区域类型等）
│   ├── fe/                     # 有限元类型定义
│   ├── geom/                   # 几何元素定义
│   ├── hook/                   # Hook 接口
│   ├── material/               # 材料属性接口
│   ├── mesh/                   # 网格基础类
│   ├── meshgen/                # 网格生成接口
│   ├── parser/                 # 解析器接口
│   ├── quadrature/             # 积分规则定义
│   ├── solution/               # 仿真区域类
│   ├── solver/                 # 求解器基础类与接口
│   └── utils/                  # 工具接口
│
├── examples/                   # 算例（19 种器件类型）
│   ├── PN_Diode/               # PN 结二极管
│   ├── Schottky_Diode/         # 肖特基接触二极管
│   ├── BJT/                    # 双极晶体管
│   ├── HBJT/                   # 异质结双极晶体管
│   ├── MOS/                    # MOS 器件
│   ├── MOSCAP/                 # MOS 电容
│   ├── MESFET/                 # 金属-半导体 FET
│   ├── HEMT/                   # 高电子迁移率晶体管
│   ├── EEPROM/                 # 浮栅 EEPROM 存储器
│   ├── Thyristor/              # 闸流管
│   ├── CAP/                    # 电容器件
│   ├── Trap/                   # 陷阱/缺陷态仿真
│   ├── Well_Tempered/          # 温度相关效应（含 25nm/90nm MOSFET）
│   ├── TID/                    # 总剂量辐射效应
│   ├── HALL/                   # 霍尔效应
│   ├── SOI/                    # SOI 器件
│   ├── Material/               # 材料属性演示
│   ├── Inject/                 # 载流子注入
│   └── IDC_Run/                # 直流运行演示
│
├── lib/                        # 材料属性库与配置文件（XML）
├── doc/                        # Doxygen 配置与开发文档
├── cmake/                      # CMake 构建模块
├── CMakeLists.txt              # 主 CMake 构建文件
├── README                      # 项目简介
├── INSTALL                     # 安装说明
└── COPYRIGHT                   # 版权与许可证信息
```

---

## 3. 整体架构

Genius 采用**分层架构**，从底层几何数据结构到顶层仿真控制逐层构建，核心设计思想是将物理模型、数值方法和数据存储解耦。

### 3.1 架构分层图

```
┌─────────────────────────────────────────────────────────┐
│                    用户输入文件 (.inp)                    │
└─────────────────────────┬───────────────────────────────┘
                          │ FLEX/BISON 解析
┌─────────────────────────▼───────────────────────────────┐
│              SolverControl（仿真控制层）                  │
│         读取指令 → 创建求解器 → 执行求解序列              │
└──────────┬──────────────┬──────────────┬────────────────┘
           │              │              │
┌──────────▼──────┐ ┌─────▼──────┐ ┌────▼──────────────┐
│  SimulationSystem│ │  Solvers   │ │    Hooks/Output    │
│  （系统容器）    │ │  （求解器）│ │   （插件/输出）    │
│ - Mesh           │ │ - DDM1     │ │ - VTKHook          │
│ - Regions        │ │ - DDM2     │ │ - CGNSHook         │
│ - BoundaryConds  │ │ - EBM3     │ │ - MonitorHook      │
│ - Sources        │ │ - DDMAC    │ │ - ProbeHook        │
│ - Circuit        │ │ - MIX      │ └────────────────────┘
└──────────┬───────┘ └─────┬──────┘
           │               │ 装配方程
┌──────────▼───────────────▼──────────────────────────────┐
│                PETSc 数值求解层                           │
│    SNES（非线性）→ KSP（线性）→ 预条件器/直接求解器       │
└─────────────────────────────────────────────────────────┘
           │
┌──────────▼───────────────────────────────────────────────┐
│                     底层数据结构                           │
│  Mesh → Elem/Node → FVM_Node → DataStorage → PMI         │
└──────────────────────────────────────────────────────────┘
```

### 3.2 程序主流程

```
main()
 ├─ 初始化 MPI / PETSc
 ├─ 预处理输入文件（处理 #include 语句）
 ├─ 解析 GeniusSyntax.xml（语法定义）
 ├─ 加载材料库
 ├─ 创建 SolverControl
 └─ SolverControl::run()
      ├─ Parser 解析 .inp → 生成指令序列
      ├─ 执行 MESH 指令 → 生成/导入网格
      ├─ 执行 REGION 指令 → 创建仿真区域
      ├─ 执行 DOPING 指令 → 设置掺杂
      ├─ 执行 BOUNDARY 指令 → 设置边界条件
      ├─ 执行 METHOD 指令 → 选择求解器
      ├─ 执行 SOLVE 指令 → 运行仿真
      └─ 执行 EXPORT 指令 → 导出结果
```

---

## 4. 核心模块详解

### 4.1 主程序入口

**文件**：`src/main.cc`

程序入口负责：
1. 初始化 MPI 并行环境（兼容 PETSc 3.1~3.6 各版本 API）
2. 验证运行环境（`GENIUS_DIR` 环境变量、输入文件可访问性）
3. 调用 `FilePreProcess` 展开 `#include` 预处理指令
4. 从 `$GENIUS_DIR/lib/GeniusSyntax.xml` 加载语法定义
5. 从材料库加载材料定义
6. 实例化 `SolverControl` 并调用 `run()` 执行主循环
7. 记录性能日志（`PerfLog`）与内存日志（`MemoryLog`）

**关键头文件依赖**：
```cpp
#include "genius_common.h"    // 全局宏定义、版本信息
#include "genius_env.h"       // 运行时环境变量管理
#include "material_define.h"  // 材料库初始化
#include "control.h"          // SolverControl 声明
#include "parser.h"           // 输入文件解析器
```

---

### 4.2 网格系统

**头文件路径**：`include/mesh/`  
**实现路径**：`src/mesh/`

#### 核心类层次

```
MeshBase（抽象基类）
 ├─ SerialMesh         # 单处理器网格，主要使用
 └─ Mesh               # 包装接口
```

#### 主要数据结构

| 类名 | 头文件 | 作用 |
|-----|--------|------|
| `MeshBase` | `mesh_base.h` | 所有网格的抽象基类 |
| `SerialMesh` | `serial_mesh.h` | 单核串行网格，存储所有节点和单元 |
| `BoundaryInfo` | `boundary_info.h` | 管理边界单元及 ID 映射 |
| `MeshRefinement` | `mesh_refinement.h` | 自适应网格细化（AMR） |
| `MeshTools` | `mesh_tools.h` | 网格操作工具函数集合 |
| `Node` | `node.h` | 网格顶点，继承自 `Point` |
| `Elem` | `elem.h` | 网格单元基类（支持 Tri3/Quad4/Tet4/Hex8 等） |
| `Point` | `point.h` | 三维坐标点 |

#### FVM 节点

Genius 在标准网格基础上叠加了有限体积法（FVM）专用的节点对象：

| 类名 | 头文件 | 作用 |
|-----|--------|------|
| `FVM_Node` | `fvm_node.h` | FVM 节点，关联控制体、邻居信息 |
| `FVM_NodeData` | `fvm_node_data.h` | 节点关联的物理量存储（电势、载流子浓度等） |
| `FVM_CellData` | `fvm_cell_data.h` | 单元中心物理量存储 |

#### 网格生成

`src/meshgen/` 封装了 Triangle 网格生成器，通过 `MESH` 指令触发。支持多种初始网格类型：

| 关键字 | 说明 |
|-------|------|
| `S_Tri3` | 非结构化三角形网格 |
| `S_Quad4` | 结构化四边形网格 |
| `S_Hex8` | 结构化六面体网格（三维） |
| `S_Tet4` | 非结构化四面体网格（三维） |
| `S_Prism6` | 棱柱网格 |

---

### 4.3 仿真区域与数据存储

**头文件路径**：`include/solution/`  
**实现路径**：`src/solution/`

#### SimulationSystem

`SimulationSystem` 是整个仿真系统的中央容器，其主要成员包括：

```cpp
class SimulationSystem {
  MeshBase &          _mesh;               // 几何网格
  vector<SimulationRegion*> _simulation_regions; // 仿真区域列表
  BoundaryConditionCollector _bcs;         // 边界条件集合
  ElectricalSource *  _electrical_source;  // 电压/电流源
  FieldSource *       _field_source;       // 光源/粒子源
  SpiceCircuit *      _spice_ckt;          // SPICE 外部电路
  Point               _magnetic_field;     // 静态磁场
  double              _T_external;         // 环境温度
};
```

**关键方法**：

| 方法 | 说明 |
|------|------|
| `build_simulation_system()` | 从网格构建仿真区域 |
| `init_region()` | 掺杂/摩尔分数设置后初始化区域数据 |
| `build_boundary_conditions()` | 构建边界条件数组 |
| `import_cgns() / export_cgns()` | CGNS 格式读写（主要存档格式） |
| `import_tif() / export_tif()` | TIF 格式（Medici/Tsuprem 兼容） |
| `import_silvaco()` | Silvaco ATLAS 格式导入 |
| `export_vtk()` | VTK 可视化输出 |
| `self_consistent()` | 检查解是否满足泊松方程 |
| `estimate_error()` | 计算每个网格单元的误差（用于 AMR） |

#### SimulationRegion（仿真区域）

每个物理区域（硅、氧化层、金属等）对应一个 `SimulationRegion` 对象：

```
SimulationRegion（抽象基类）
 ├─ SemiconductorSimulationRegion  # 半导体（Si、Ge、GaAs 等）
 ├─ InsulatorSimulationRegion      # 绝缘体（SiO₂、Si₃N₄ 等）
 ├─ ConductorSimulationRegion      # 导体/电极（金属、多晶硅）
 ├─ ResistanceSimulationRegion     # 电阻元件
 ├─ VacuumSimulationRegion         # 真空（光学仿真用）
 └─ PMLSimulationRegion            # 完全匹配层（光学边界吸收）
```

#### DataStorage

`DataStorage` 是类型安全的通用字段容器，支持标量、复数、向量、张量等多种数据类型，通过字符串键访问存储的物理场量。

---

### 4.4 边界条件系统

**头文件路径**：`include/bc/`  
**实现路径**：`src/bc/`

#### BoundaryCondition 基类

所有边界条件继承自 `BoundaryCondition`：

```cpp
class BoundaryCondition {
  SimulationSystem &   _system;
  string               _boundary_name;    // 用户定义标签
  unsigned int         _boundary_id;      // 数字 ID
  vector<const Node*>  _bd_nodes;         // 边界节点列表
  pair<SimulationRegion*, SimulationRegion*> _bc_regions; // 相邻区域
  // 节点到区域/FVM节点的多重映射
  map<const Node*, multimap<...>> _bd_fvm_nodes;
  double               _T_Ext;            // 外部温度
};
```

#### 边界条件类型

| BC 类型 | 类名 | 适用场景 |
|---------|------|---------|
| 理想欧姆接触 | `OhmicContact` | 金属/半导体理想接触 |
| 带串联电阻欧姆接触 | `OhmicContactWithResistance` | 含寄生电阻的接触 |
| 肖特基接触 | `SchottkyContact` | 金属-半导体整流接触 |
| 栅极接触 | `GateContact` | MOS 栅介质下的金属栅 |
| 多晶硅栅接触 | `PolyGateContact` | 多晶硅栅极 |
| 纽曼边界 | `NeumannBC` | 绝热/绝缘边界 |
| 浮空金属 | `FloatMetal` | 浮栅（EEPROM） |
| 绝缘体-半导体界面 | `InsulatorSemiconductorInterface` | SiO₂/Si 界面 |
| 异质结界面 | `HeteroInterface` | III-V 材料异质结 |
| 同质结界面 | `HomoInterface` | 同材料不同区域界面 |

---

### 4.5 材料模型接口（PMI）

**头文件路径**：`include/material/`  
**实现路径**：`src/material/`

PMI（Physical Model Interface）是 Genius 最重要的扩展接口之一，允许用户在不修改求解器源码的情况下替换或添加材料物理模型。

#### PMI 类型

```cpp
enum PMI_Type {
  PMI_Basic,     // 基本参数（带隙、有效质量等）
  PMI_Band,      // 能带结构模型
  PMI_Mobility,  // 迁移率模型
  PMI_Impact,    // 碰撞电离（雪崩倍增）模型
  PMI_Thermal,   // 热学参数模型
  PMI_Optical,   // 光学参数模型（折射率、吸收系数）
  PMI_Trap,      // 陷阱态模型
};
```

#### 材料类型层次

```
MaterialBase（抽象基类）
 ├─ MaterialSemiconductor   # 含 basic/band/mob/gen/thermal/optical/trap
 ├─ MaterialInsulator       # 含 basic/band/thermal/optical
 ├─ MaterialConductor       # 含 basic/thermal/optical
 ├─ MaterialVacuum          # 含 basic/thermal/optical
 └─ MaterialPML             # 含 basic/thermal
```

#### PMI 调用机制

材料模型以动态库（.so/.dll）形式加载，通过函数指针调用：

```cpp
// 在 SemiconductorRegion 中调用迁移率模型示例
material->mob->ElecMobility(p_point, p_node_data, Tl);
```

每次在节点上进行物理量计算前，先调用 `mapping()` 函数更新当前点的上下文：

```cpp
material->mapping(&node, node_data, current_time);
double mu_n = material->mob->ElecMobility(...);
```

#### 内置迁移率模型

| 模型名称 | 说明 |
|---------|------|
| `Lucent` | 适用于 Si 的 Lucent 迁移率模型（含高场效应） |
| `Philips` | Philips 统一迁移率模型 |
| `Masetti` | Masetti 掺杂相关迁移率模型 |
| `Canali` | Canali 高场饱和速度模型 |

---

### 4.6 求解器框架

**头文件路径**：`include/solver/`  
**实现路径**：`src/solver/`

#### 求解器类层次

```
SolverBase（抽象基类）
 │
 ├─ FVM_PDESolver              # FVM 偏微分方程求解器基类
 │   ├─ FVM_NonlinearSolver    # 非线性求解器（封装 PETSc SNES）
 │   │   └─ DDMSolverBase      # 漂移扩散求解器基类
 │   │       ├─ DDM1Solver     # 漂移扩散 Level 1
 │   │       ├─ DDM2Solver     # 漂移扩散 Level 2
 │   │       ├─ EBM3Solver     # 能量平衡 Level 3
 │   │       ├─ HALLSolver     # 霍尔效应求解器
 │   │       └─ DDMACHook      # AC 小信号分析
 │   └─ FVM_LinearSolver       # 线性求解器（封装 PETSc KSP）
 │
 ├─ FEM_PDESolver              # FEM 偏微分方程求解器
 │
 ├─ MixSolverBase              # 器件/电路混合仿真
 │   ├─ MixSolver              # MIX 模式（DDM1 + 电路）
 │   └─ MixASolver             # MIXA 模式（高级混合）
 │
 └─ 专用求解器
     ├─ PoissonSolver          # 纯泊松方程（初始条件）
     ├─ EmFEM2DSolver          # 二维 EM-FEM 光学
     ├─ RayTracingSolver       # 光线追踪光学
     ├─ StressSolver           # 应力/应变
     └─ DopingAnalyticSolver   # 解析掺杂分布
```

#### SolverBase 接口

```cpp
class SolverBase {
public:
  virtual SolverType   solver_type() const = 0;  // 求解器类型标识
  virtual int          set_variables();           // 准备求解变量
  virtual int          create_solver();           // 创建内部求解器结构
  virtual int          pre_solve_process(bool);   // 求解前预处理
  virtual int          solve() = 0;              // 核心求解（纯虚）
  virtual int          post_solve_process();      // 求解后处理
  virtual int          destroy_solver();          // 销毁求解器
  SimulationSystem &   system();                  // 访问仿真系统
  void                 add_hook(HookBase*);       // 添加插件 Hook
};
```

---

### 4.7 输入文件解析器

**路径**：`src/parser/`、`include/parser/`

解析器使用 **FLEX**（词法分析）和 **BISON**（语法分析）生成。输入文件采用基于"卡片"（Card）的格式，每条指令对应一个卡片类型（如 `MESH`、`SOLVE`、`EXPORT` 等）。

#### 解析流程

```
.inp 文件
  │
  ▼ FilePreProcess（展开 #include）
  │
  ▼ Lexer（FLEX 生成）→ Token 流
  │
  ▼ Parser（BISON 生成）→ AST/指令序列
  │
  ▼ SolverControl::interpreter() → 执行各指令
```

#### 支持的预处理指令

```
#include "other_file.inc"    # 包含其他文件
# 注释                       # 行注释
```

---

### 4.8 Hook 插件系统

**路径**：`include/hook/`、`src/hook/`

Hook 系统允许用户在不修改核心代码的情况下挂入监控、输出、自定义处理等逻辑。所有 Hook 继承自 `HookBase`。

#### Hook 生命周期接口

```cpp
class HookBase {
public:
  virtual void on_init()           {}  // 求解器初始化时调用
  virtual void on_close()          {}  // 求解器关闭时调用
  virtual void pre_solve()         {}  // 每次求解前调用
  virtual void post_solve()        {}  // 每次求解后调用
  virtual void pre_iteration()     {}  // 每次非线性迭代前调用
  virtual void post_iteration()    {}  // 每次非线性迭代后调用
  virtual void post_convergence()  {}  // 收敛后调用
};
```

#### 内置 Hook 类型（部分）

| Hook 名称 | 触发时机 | 功能 |
|-----------|---------|------|
| `vtk` | 每个求解步 | 输出 VTK 格式可视化文件 |
| `cgns` | 收敛后 | 输出 CGNS 格式存档文件 |
| `ddm_monitor` | 每次迭代 | 监控非线性残差收敛过程 |
| `probe` | 收敛后 | 提取指定点的物理量 |
| `data` | 可配置 | 自定义数据提取 |

---

## 5. 模块依赖关系

### 5.1 编译依赖层次

```
Level 0（最底层，无依赖）：
  math、utils、base

Level 1（依赖 Level 0）：
  geom（Node、Elem、Point）

Level 2（依赖 Level 1）：
  mesh（MeshBase、SerialMesh、BoundaryInfo）

Level 3（依赖 Level 2）：
  material（MaterialBase、PMI 接口）
  fe（有限元形函数）
  quadrature（数值积分）

Level 4（依赖 Level 3）：
  solution（SimulationRegion、SimulationSystem）
  interpolation

Level 5（依赖 Level 4）：
  bc（BoundaryCondition 各类型）
  meshgen（Triangle 网格生成）
  partition（域分解）

Level 6（依赖 Level 5）：
  solver（各类求解器）

Level 7（顶层）：
  source（激励源）
  hook（插件系统）
  parser（输入解析）
  SolverControl（仿真控制）
```

### 5.2 运行时数据流

```
输入文件
  │
  ▼ Parser
  │
  ▼ SolverControl
  │
  ├───→ MeshGen → Mesh（SerialMesh）
  │
  ├───→ SimulationSystem
  │         ├── Regions（含 MaterialXxx）
  │         ├── BoundaryConditions
  │         └── FVM Nodes（含 DataStorage）
  │
  └───→ Solver（DDM1 等）
            │
            ├── pre_solve_process()
            │     └── 分配 PETSc Vec/Mat
            │
            ├── solve()
            │     ├── 遍历所有 Region → 装配方程
            │     ├── 遍历所有 BC → 装配方程
            │     └── PETSc SNES/KSP → 线性代数求解
            │
            └── post_solve_process()
                  ├── 将解回填到 DataStorage
                  └── 调用 Hook（输出文件等）
```

---

## 6. 关键算法实现

### 6.1 泊松方程求解

泊松方程用于求解设备内部的静电势分布，是所有物理模型的基础：

$$
-\nabla \cdot (\varepsilon \nabla \varphi) = q(p - n + N_D^+ - N_A^-)
$$

**有限体积离散化**（对控制体 $\Omega_i$ 积分）：

$$
\sum_{j \in \mathcal{N}(i)} \varepsilon_{ij} \frac{\varphi_j - \varphi_i}{d_{ij}} |e_{ij}| = -q (p_i - n_i + N_{D,i}^+ - N_{A,i}^-)|\Omega_i|
$$

其中 $d_{ij}$ 为节点 $i$、$j$ 间距，$|e_{ij}|$ 为控制体面积，$|\Omega_i|$ 为控制体体积。

**对应求解器**：`src/solver/poisson/`  
**求解器类型关键字**：`METHOD Type=Poisson`

---

### 6.2 漂移扩散模型（DDM）

#### 控制方程组

DDM 联立求解以下方程：

**1. 泊松方程**（静电势）：

$$
-\nabla \cdot (\varepsilon \nabla \varphi) = q(p - n + N_D^+ - N_A^-)
$$

**2. 电子连续性方程**：

$$
\frac{\partial n}{\partial t} = \frac{1}{q}\nabla \cdot \mathbf{J}_n + G - R
$$

**3. 空穴连续性方程**：

$$
\frac{\partial p}{\partial t} = -\frac{1}{q}\nabla \cdot \mathbf{J}_p + G - R
$$

**电流密度**（漂移扩散）：

$$
\mathbf{J}_n = q\mu_n n \mathbf{E} + qD_n \nabla n = q\mu_n n (-\nabla\varphi) + \frac{qD_n}{kT/q}\nabla(kT/q \cdot n)
$$

#### Scharfetter-Gummel 格式

在 FVM 网格边上，电流密度采用 Scharfetter-Gummel 格式（保证数值稳定性）：

$$
J_{n,ij} = \frac{q D_n}{d_{ij}} \left[ n_i B\!\left(\frac{q(\varphi_i-\varphi_j)}{kT}\right) - n_j B\!\left(\frac{q(\varphi_j-\varphi_i)}{kT}\right) \right]
$$

其中 $B(x) = x/(e^x - 1)$ 为 Bernoulli 函数。

#### DDM Level 1（DDM1）

- **变量**：电势 $\varphi$、电子浓度 $n$、空穴浓度 $p$
- **文件**：`src/solver/ddm1/ddm1_semiconductor.cc`（约 1795 行）
- **关键字**：`METHOD Type=DDML1`

#### DDM Level 2（DDM2）

- **变量**：$\varphi$、$n$、$p$、电子温度 $T_n$、空穴温度 $T_p$
- 在 DDM1 基础上增加载流子温度方程
- **关键字**：`METHOD Type=DDML2`

---

### 6.3 能量平衡模型（EBM）

EBM（Energy Balance Model，Level 3）在 DDM2 基础上进一步增加晶格温度方程：

**晶格热平衡方程**：

$$
\rho c_p \frac{\partial T_L}{\partial t} = \nabla \cdot (\kappa \nabla T_L) + H_{\text{Joule}} + H_{\text{recomb}}
$$

**载流子能量守恒**：

$$
\frac{\partial (n w_n)}{\partial t} = -\nabla \cdot \mathbf{S}_n - \mathbf{J}_n \cdot \mathbf{E} - n \frac{w_n - w_{n0}}{\tau_w}
$$

其中 $w_n$ 为电子平均能量，$\mathbf{S}_n$ 为能流密度，$\tau_w$ 为能量弛豫时间。

- **文件**：`src/solver/ebm3/`
- **关键字**：`METHOD Type=EBM3`

---

### 6.4 有限体积离散化

Genius 采用基于 Delaunay 三角剖分的 **Box Integration（控制体积分）** 方法：

1. 对每个节点 $i$ 构造 Voronoi 控制体 $\Omega_i$
2. 将 PDE 在 $\Omega_i$ 上积分并应用散度定理
3. 通量在相邻节点 $i$、$j$ 之间的连边上近似

**Voronoi 控制体构造**：
- 三角网格：每个三角形的外接圆圆心
- 矩形网格：单元中心

**时间离散**：
- 后向 Euler 法（一阶，无条件稳定）
- Crank-Nicolson 法（二阶）

---

### 6.5 非线性求解流程

Genius 通过 **PETSc SNES**（Scalable Nonlinear Equation Solver）求解方程组 $\mathbf{F}(\mathbf{x}) = 0$：

```
SNES 外循环（Newton 迭代）：
  给定初始猜测 x₀
  loop:
    1. 装配残差向量 F(xₙ)
       - 遍历所有半导体区域（泊松 + 连续性方程贡献）
       - 遍历所有绝缘体区域
       - 遍历所有导体区域
       - 遍历所有边界条件
    2. 装配 Jacobian 矩阵 J = ∂F/∂x
       （同样按区域和边界条件分别贡献）
    3. KSP 线性子系统求解 J·Δx = -F
       - 迭代法：BCGS、GMRES 等
       - 预条件器：ILU、AMG（HYPRE Boomer AMG）
       - 直接法：SuperLU、MUMPS、LU
    4. 更新 xₙ₊₁ = xₙ + α·Δx（α 由线搜索确定）
    5. 检查收敛：||F(xₙ₊₁)|| < ε
  end loop
```

**Gummel 解耦迭代**（`NS=Gummel`）：
依次单独求解泊松、电子、空穴方程，通过外层 Gummel 迭代耦合。适用于初始收敛困难的情况。

**Newton 全耦合**（`NS=Basic` 或 `NS=LineSearch`）：
同时求解所有变量，每步计算量大但收敛更快，适用于已有良好初值的情形。

---

### 6.6 交流小信号分析

AC 分析在直流工作点附近做线性展开：

$$
\mathbf{J} \cdot \delta\mathbf{x} + j\omega \mathbf{C} \cdot \delta\mathbf{x} = \delta\mathbf{b}
$$

其中 $\mathbf{J}$ 为直流工作点处的 Jacobian，$\mathbf{C}$ 为电容矩阵，$\omega$ 为角频率。

1. 先完成直流求解（`SOLVE Type=STEADYSTATE`）
2. 然后在各频率点求解上述复数线性方程组
3. 输出 Y 参数矩阵、阻抗/导纳谱

- **文件**：`src/solver/ddm_ac/`
- **关键字**：`METHOD Type=DDMAC`，`SOLVE Type=ACSWEEP`

---

### 6.7 瞬态分析

时间积分采用**隐式方案**（保证稳定性）：

**后向 Euler（BDF1）**：

$$
\frac{\mathbf{x}^{n+1} - \mathbf{x}^n}{\Delta t} = \mathbf{f}(\mathbf{x}^{n+1})
$$

**BDF2**（二阶，精度更高）：

$$
\frac{3\mathbf{x}^{n+1} - 4\mathbf{x}^n + \mathbf{x}^{n-1}}{2\Delta t} = \mathbf{f}(\mathbf{x}^{n+1})
$$

自适应时间步长：根据收敛情况动态调整 $\Delta t$（参数 `TStep`、`TStepMax`）。

- **关键字**：`SOLVE Type=TRANSIENT TStart=0 TStep=1e-9 TStop=1e-6`

---

### 6.8 器件-电路混合仿真

Genius 支持将 TCAD 器件模型与 SPICE 电路网表联合求解：

**原理**：
- 器件端口作为 SPICE 网表中的电流源（由 TCAD 提供端口电流）
- SPICE 电路节点电压作为器件边界条件
- 两者通过迭代耦合（relaxation）或全耦合方式求解

**使用方式**：
```
CIRCUIT NETLIST=my_circuit.cir   # 加载 SPICE 网表
ATTACH   Electrode=Anode VApp=Vs # 连接器件电极到电路节点
METHOD   Type=DDML1M              # 混合求解模式
SOLVE    Type=TRANSIENT ...
```

- **文件**：`src/solver/mix1/`、`src/solver/mixA1/`
- **关键字**：`METHOD Type=DDML1M`（`M` 表示 Mixed）

---

### 6.9 光学模型

#### 光线追踪（Ray Tracing）

- 适用于几何光学近似（光波长 << 结构尺寸）
- 追踪光子在器件中的传播路径及吸收
- 计算各区域的光生载流子产生率 $G_{\text{opt}}$
- **文件**：`src/solver/ray_tracing/`
- **关键字**：`SOLVE Type=RAY_TRACE`

#### 二维 EM-FEM 光学

- 适用于亚波长结构（光波长 ≈ 结构尺寸）
- 求解麦克斯韦方程（全波计算）
- 输出复振幅分布、坡印廷矢量、吸收分布
- **文件**：`src/solver/emfem2d/`
- **关键字**：`SOLVE Type=EMFEM2D`

---

## 7. 求解器类型与选择

### METHOD 卡片参数

| 参数 | 取值 | 说明 |
|------|------|------|
| `Type` | `Poisson` | 仅泊松方程（用于初始条件） |
| `Type` | `DDML1` | 漂移扩散 Level 1 |
| `Type` | `DDML2` | 漂移扩散 Level 2（含载流子温度） |
| `Type` | `EBM3` | 能量平衡模型（含晶格温度） |
| `Type` | `HALL` | 漂移扩散 + 霍尔效应 |
| `Type` | `DDMAC` | 交流小信号分析 |
| `Type` | `DDML1M` | DDM1 + 外部电路混合 |
| `NS` | `Basic` | Newton 全耦合（默认） |
| `NS` | `LineSearch` | Newton + 线搜索（改善收敛） |
| `NS` | `Gummel` | Gummel 解耦迭代 |
| `LS` | `BCGS` | 双共轭梯度稳定法（稀疏迭代） |
| `LS` | `GMRES` | 广义最小残差法 |
| `LS` | `MUMPS` | MUMPS 并行直接求解器 |
| `LS` | `SuperLU` | SuperLU 直接求解器 |
| `LS` | `LU` | 串行 LU 分解 |
| `PC` | `ILU` | 不完全 LU 预条件 |
| `PC` | `AMG` | 代数多重网格预条件 |

### SOLVE 卡片类型

| `Type` | 说明 |
|--------|------|
| `EQ` / `EQUILIBRIUM` | 热平衡态（零偏置，作为初始条件） |
| `STEADYSTATE` | 直流稳态 |
| `DC` / `DCSWEEP` | 直流扫描（IV 曲线） |
| `TRANSIENT` | 瞬态时域仿真 |
| `ACSWEEP` | 交流频率扫描 |
| `OP` | 工作点（Operating Point） |
| `TRACE` | IV 曲线追踪（含负阻区域） |

---

## 8. 算例说明

### 8.1 PN 结二极管

**路径**：`examples/PN_Diode/2D/pn2d.inp`

**仿真流程**：
1. 生成初始网格（三角形，约 3μm × 3μm）
2. 设置解析掺杂（N 型基底 + P 型阳极区）
3. 按掺杂梯度细化网格
4. 泊松求解 + 按电势细化网格
5. DDM1 计算热平衡态（`SOLVE Type=EQ`）
6. DDM1 正向 IV 扫描（`SOLVE Type=DC Vscan=Anode Vstart=0 Vstep=0.1 Vstop=1.0`）
7. 导出 CGNS（存档）和 VTK（可视化）

**关键配置**：
```
GLOBAL    T=300 DopingScale=1e18  Z.Width=1.0

MESH      Type=S_Tri3 triangle="pzADq30"

PROFILE   Type=Uniform    Ion=Donor     N.PEAK=1E18
PROFILE   Type=Analytic   Ion=Acceptor  N.PEAK=1E19  Y.JUNCTION=0.5

BOUNDARY ID=Anode   Type=Ohmic RES=1000
BOUNDARY ID=Cathode Type=Ohmic

METHOD    Type=DDML1 NS=Basic LS=MUMPS MaxIt=20
SOLVE     Type=DC Vscan=Anode Vstart=0 Vstep=0.1 Vstop=1.0
```

---

### 8.2 NPN 双极晶体管（BJT）

**路径**：`examples/BJT/`（分步骤仿真）

| 步骤文件 | 内容 |
|---------|------|
| `step1.inp` | 建立网格、设置掺杂、计算热平衡态，导出 CGNS |
| `step2.inp` | 导入 step1 的 CGNS，计算 Gummel Plot |
| `step3.inp` | 计算共射极 IC-VCE 输出特性曲线 |
| `step4.inp` | 计算击穿特性 |
| `step5.inp` | 瞬态开关仿真 |

**BJT 掺杂配置示例**（step1.inp 节选）：
```
REGION    Label=Si Material=Si
# 集电区（轻掺杂 N 型）
PROFILE   Ion=Donor    Type=Uniform N.PEAK=5e15
# 基区（P 型）
PROFILE   Ion=Acceptor Type=analytic N.PEAK=6e17 Y.TOP=0 Y.BOTTOM=0.35
# 发射区（重掺杂 N 型）
PROFILE   Ion=Donor    Type=analytic N.PEAK=7e19 Y.TOP=0 Y.JUNCTION=0.3

METHOD    Type=DDML1 NS=LineSearch LS=BCGS PC=ILU Damping=Potential
SOLVE     Type=EQUILIBRIUM
```

---

### 8.3 NMOS/PMOS 晶体管

**路径**：`examples/MOS/2D/`、`examples/Well_Tempered/`

MOS 示例展示了从 TIF 文件导入预建网格并进行电学仿真的工作流：

```
# 导入已建好的 NMOS 网格（来自 Medici/Tsuprem 的 TIF 格式）
IMPORT   TIFFILE="25nm.tif"

# 设置 Lucent 迁移率模型（适合短沟道）
PMI Region=r5 Type=mobility Model=Lucent

METHOD   Type=DDML1 NS=Basic LS=LU
SOLVE    Type=STEADYSTATE

# VGS 扫描（转移特性 IdVg）
SOLVE    Type=DCSWEEP VScan=gate out.prefix=idvg VStart=0 VStep=0.025 VStop=1.0
```

---

### 8.4 肖特基二极管（混合仿真）

**路径**：`examples/Schottky_Diode/mix.inp`

展示器件与 SPICE 电路的联合仿真：

```
# 加载 SPICE 网表
CIRCUIT NETLIST=diode_ckt.cir

# 肖特基接触（功函数 4.9 eV）
BOUNDARY ID=Anode   Type=Schottky WorkFunction=4.9
BOUNDARY ID=Cathode Type=Ohmic

# 混合求解模式（DDM1 + 外部电路）
METHOD   Type=DDML1M NS=Basic LS=GMRES PC=ILU
SOLVE    Type=TRANSIENT tstart=0 tstep=0.001e-6 tstop=5e-6
```

---

### 8.5 EEPROM 浮栅器件

**路径**：`examples/EEPROM/`

展示含浮栅的多材料器件（硅+氧化层+浮栅+控制栅）仿真：

```
# 多材料区域定义
REGION Label=Silicon   Material=Si
REGION Label=Oxide     Material=SiO2
REGION Label=Flt_Gate  Material=NPolySi   # 浮栅（N 型多晶硅）
REGION Label=Gate      Material=Elec      # 控制栅

# 浮栅设置固定电荷（模拟编程态）
CONTACT Type=FloatMetal ID=Flt_Gate QF=-1e-15

# 隧穿效应（F-N 隧穿）在 PMI 中处理
```

各分析文件：
- `model.inp`：建立器件模型
- `write.inp`：写入操作（施加高压，F-N 隧穿注入）
- `erase.inp`：擦除操作
- `read.inp`：读取操作（低压 IV）

---

### 8.6 闸流管（含外部电路）

**路径**：`examples/Thyristor/`

展示闸流管与正弦电压源（通过外部 RC 调相触发）的瞬态仿真：

```
vsource Type=VSIN ID=Vs Tdelay=0 Vamp=5.0 Freq=1e6

# 门极带 RC 移相（控制导通角）
boundary Type=OhmicContact ID=Gate Res=510 Cap=1e-9

ATTACH   Electrode=Anode VApp=Vs
METHOD   Type=DDML1 NS=Basic LS=GMRES Damping=Potential
SOLVE    Type=TRANSIENT TStart=0 TStep=1e-8 TStop=3e-6
```

---

### 8.7 陷阱仿真

**路径**：`examples/Trap/diode_dc.inp`

展示半导体中界面陷阱的定义与对器件特性的影响：

```
# 在 Silicon 区域定义两种陷阱态
PMI region=Silicon type=Trap \
    string<profile>="TrapA" \
    string<chargetype>=Acceptor \
    double<energy>=0.02 \
    double<sigman>=1e-16 \
    double<sigmap>=1e-14

PMI region=Silicon type=Trap \
    string<profile>="TrapA" \
    string<chargetype>=Donor \
    double<energy>=-0.22 \
    double<sigman>=5e-15
```

---

### 8.8 霍尔效应器件

**路径**：`examples/HALL/hall.inp`

```
GLOBAL    T=300 DopingScale=1e18
MagneticField BY=1        # 施加 Y 方向磁场（1 T）

REGION    Label=Silicon  Material=Si
BOUNDARY  ID=Anode   Type=Ohmic
BOUNDARY  ID=Cathode Type=Ohmic

METHOD    Type=HALL NS=Basic LS=LU
SOLVE     Type=EQ
SOLVE     Type=DCSWEEP Vscan=Anode Vstart=0 Vstep=0.05 Vstop=1.0
```

---

### 8.9 25 nm 纳米 MOSFET

**路径**：`examples/Well_Tempered/25nm/25nm_iv.inp`

展示超短沟道 NMOS 的 IdVg 特性，使用 Lucent 迁移率模型：

```
IMPORT   TIFFILE="25nm.tif"

# Lucent 模型适合短沟道 Si MOSFET
PMI Region=r5 Type=mobility Model=Lucent

METHOD   Type=DDML1 NS=Basic LS=LU
SOLVE    Type=DCSWEEP VScan=gate VStart=0 VStep=0.025 VStop=1.0
```

---

## 9. 输入文件格式参考

### 9.1 全局设置

```
GLOBAL    T=300             # 晶格温度（K），默认 300 K
          DopingScale=1e18  # 掺杂浓度归一化参考值（cm⁻³）
          Z.Width=1.0       # 2D 仿真的 Z 方向厚度（μm），默认 1 μm
```

### 9.2 网格定义

```
MESH      Type=S_Tri3       # 网格类型
          triangle="pzADq30" # Triangle 程序参数

X.MESH    WIDTH=1.0  N.SPACES=10   # X 方向，宽 1 μm，10 等分
Y.MESH    DEPTH=0.5  H1=0.05       # Y 方向，深 0.5 μm，从顶端步长 0.05 μm
```

### 9.3 区域定义

```
REGION    Label=Silicon Material=Si           # 整个仿真域为硅
REGION    Label=Oxide    Material=SiO2  \
          Y.TOP=-0.05 Y.BOTTOM=0.0           # 可指定坐标范围
FACE      Label=Gate     Location=TOP  \
          X.MIN=0.2 X.MAX=0.8                # 定义边界面（用于 BC）
```

### 9.4 掺杂设置

```
DOPING    Type=Analytic     # 解析掺杂（另有 Type=File 从文件读取）

# 均匀掺杂
PROFILE   Type=Uniform   Ion=Donor   N.PEAK=1e15  \
          X.MIN=0 X.MAX=3  Y.MIN=0 Y.MAX=3

# 高斯分布掺杂
PROFILE   Type=Analytic  Ion=Acceptor  N.PEAK=1e19  \
          X.MIN=0 X.MAX=1  \
          Y.MIN=0 Y.MAX=0  Y.CHAR=0.2  Y.JUNCTION=0.5
```

### 9.5 边界条件

```
# 欧姆接触（可选串联电阻、电容、电感）
BOUNDARY  ID=Anode   Type=Ohmic   Res=1000  Cap=0  Ind=0

# 肖特基接触
BOUNDARY  ID=Metal   Type=Schottky  WorkFunction=4.7

# 栅接触
CONTACT   Type=GateContact  ID=Gate  WorkFunction=4.8
```

### 9.6 电源与激励

```
# 直流电压源
vsource   Type=VDC   ID=VCC  Vconst=1.0

# 正弦电压源
vsource   Type=VSIN  ID=Vs   Vamp=1.0  Freq=1e6  Tdelay=0

# 将电源连接到电极
ATTACH    Electrode=Anode  VApp=VCC
```

### 9.7 仿真控制

```
# 选择求解器
METHOD    Type=DDML1  NS=Basic  LS=MUMPS  PC=ILU  MaxIt=25

# 热平衡态
SOLVE     Type=EQ

# 直流 IV 扫描
SOLVE     Type=DC  Vscan=Anode  Vstart=0.0  Vstep=0.05  Vstop=2.0 \
          out.prefix=iv_result

# 瞬态仿真
SOLVE     Type=TRANSIENT  TStart=0  TStep=1e-9  TStepMax=1e-7  TStop=1e-6
```

### 9.8 网格细化

```
# 按掺杂梯度细化
REFINE.C  Variable=Doping   Measure=SignedLog  error.fraction=0.7

# 按电势梯度细化
REFINE.C  Variable=Potential  cell.fraction=0.2
```

### 9.9 物理模型设置

```
# 指定迁移率模型
PMI  Region=Silicon  Type=mobility  Model=Lucent

# 启用碰撞电离
MODEL     Region=Silicon  II.Enable=true

# 启用带间隧穿
MODEL     Region=Silicon  BandBandTunneling=true
```

### 9.10 输入输出

```
# 导入已有仿真结果
IMPORT    CGNSFile=device.cgns
IMPORT    TIFFile=device.tif      # Medici/Tsuprem 格式
IMPORT    VTKFile=device.vtu

# 导出结果
EXPORT    CGNSFile=result.cgns    # CGNS 存档
EXPORT    VTKFile=result.vtu      # VTK 可视化

# 加载输出插件
HOOK      Load=vtk                # 每步求解后输出 VTK
```

---

## 10. 扩展开发指南

### 10.1 自定义材料模型（PMI）

PMI 允许以动态库形式为任何材料添加或替换物理模型，无需修改核心代码。

#### 开发步骤

1. **参考已有模型**：查看 `lib/` 目录下已有的材料模型源码
2. **继承 PMI 基类**：以迁移率模型为例：

```cpp
#include "pmi.h"

class MyMobilityModel : public PMIS_Mobility {
public:
  MyMobilityModel(const PMI_Environment &env) : PMIS_Mobility(env) {}

  // 电子迁移率（cm²/V·s）
  PetscScalar ElecMobility(const PetscScalar &Tl) const override {
    const PetscScalar mu0 = 1400;    // 低场迁移率
    const PetscScalar Tref = 300;
    return mu0 * std::pow(Tref / Tl, 2.2);
  }

  // 空穴迁移率
  PetscScalar HoleMobility(const PetscScalar &Tl) const override {
    return 450 * std::pow(300.0 / Tl, 2.2);
  }
};

// 导出函数（动态库入口）
extern "C" PMIS_Mobility* PMIS_Mobility_Factory(const PMI_Environment &env) {
  return new MyMobilityModel(env);
}
```

3. **编译为动态库**：
```bash
g++ -shared -fPIC -o MyMobility.so MyMobility.cc -I$GENIUS_DIR/include
```

4. **在输入文件中加载**：
```
PMI Region=Silicon Type=mobility Model=MyMobility \
    dll=path/to/MyMobility.so
```

---

### 10.2 自定义 Hook 模块

Hook 可以用于自定义监控、数据提取或后处理。参考 `examples/CAP/cap.cc` 中的自定义 Hook 示例：

#### 开发步骤

1. **继承 HookBase**：

```cpp
#include "hook.h"
#include "simulation_system.h"

class MyMonitorHook : public HookBase {
public:
  MyMonitorHook(SolverBase &solver, const std::string &name, void *param)
    : HookBase(solver, name) {}

  // 每次收敛后调用
  void post_convergence() override {
    const SimulationSystem &sys = solver().system();
    // 遍历区域，提取所需物理量...
    for (unsigned int r = 0; r < sys.n_regions(); ++r) {
      const SimulationRegion *region = sys.region(r);
      // ... 自定义处理
    }
  }
};

// 导出函数
extern "C" HookBase* get_hook(SolverBase &solver,
                               const std::string &name,
                               void *param) {
  return new MyMonitorHook(solver, name, param);
}
```

2. **编译为动态库**：
```bash
g++ -shared -fPIC -o MyHook.so MyHook.cc -I$GENIUS_DIR/include
```

3. **在输入文件中加载**：
```
HOOK Load=MyHook  dll=path/to/MyHook.so
```

---

## 11. 构建与安装

### 11.1 依赖项

| 依赖 | 版本 | 必要性 | 用途 |
|------|------|--------|------|
| GCC (g++, gfortran) | ≥ 3.4.6 | **必须** | C++/Fortran 编译器 |
| FLEX | ≥ 2.5.4a | **必须** | 词法分析器生成 |
| BISON | ≥ 2.0 | **必须** | 语法分析器生成 |
| PETSc | 3.1–3.6 | **必须** | 线性/非线性求解器 |
| BLAS/LAPACK | 任意 | **必须**（随 PETSc） | 线性代数 |
| VTK | 5.4–5.8 | 推荐 | 可视化输出 |
| CGNS | 2.5 | 推荐 | CGNS 格式 I/O |
| MPI | (MPICH2 或 OpenMPI) | 推荐 | 并行支持（开源版实际为串行） |

### 11.2 PETSc 配置（推荐）

```bash
# 并行版 PETSc（含 MUMPS、SuperLU 等直接求解器）
./configure --download-mpich=1 \
  --with-debugging=0 --with-shared=0 --with-x=0 --with-pic=1 \
  --download-f-blas-lapack=1 \
  --download-superlu=1 --download-superlu_dist=1 \
  --download-blacs=1 --download-scalapack=1 \
  --download-parmetis=1 --download-mumps=1 \
  --COPTFLAGS="-O2" --CXXOPTFLAGS="-O2" --FOPTFLAGS="-O2"

make PETSC_DIR=$PWD PETSC_ARCH=arch-linux-c-opt all
```

### 11.3 构建 Genius

**方式一：WAF 构建系统（原始方式）**

```bash
export PETSC_DIR=/path/to/petsc
export PETSC_ARCH=arch-linux-c-opt

./waf --prefix=$PWD \
      --with-petsc-dir=$PETSC_DIR \
      --with-petsc-arch=$PETSC_ARCH \
      configure build install
```

**方式二：CMake**

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release \
      -DPETSC_DIR=$PETSC_DIR \
      -DPETSC_ARCH=$PETSC_ARCH \
      -DGENIUS_ENABLE_VTK=ON \
      -DGENIUS_ENABLE_CGNS=ON \
      ..
cmake --build . -j$(nproc)
cmake --install . --prefix=/path/to/install
```

### 11.4 运行

```bash
# 设置环境变量
export GENIUS_DIR=/path/to/genius
export LD_LIBRARY_PATH=$GENIUS_DIR/lib:$PETSC_DIR/$PETSC_ARCH/lib:$LD_LIBRARY_PATH

# 运行 PN 结二极管算例
cd $GENIUS_DIR/examples/PN_Diode/2D
$GENIUS_DIR/bin/genius.LINUX -i pn2d.inp
```

---

## 12. 常见问题

### Q1：运行时报 `cannot open shared object file` 错误

原因：PETSc/VTK 等共享库路径未添加到 `LD_LIBRARY_PATH`。

```bash
export LD_LIBRARY_PATH=\
  $PETSC_DIR/$PETSC_ARCH/lib:\
  /usr/local/vtk-5.8/lib/vtk-5.8:\
  $GENIUS_DIR/lib:\
  $LD_LIBRARY_PATH
```

### Q2：仿真不收敛

**排查步骤**：
1. 检查初始条件——先用 `METHOD Type=Poisson` + `SOLVE` 获得电势初值
2. 使用 Gummel 迭代（`NS=Gummel`）替换 Newton 全耦合（`NS=Basic`）
3. 降低 DC 扫描步长（`Vstep` 参数）
4. 添加 `Damping=Potential` 阻尼选项
5. 切换线性求解器：迭代法效果差时改用直接法（`LS=MUMPS` 或 `LS=LU`）

### Q3：如何检查网格质量

网格生成后可用 VTK 工具（ParaView 等）打开导出的 `.vtu` 文件检查网格，或在输入文件中加入 `PLOT` 命令。

### Q4：如何添加新材料

1. 参考 `lib/` 目录下已有的材料 XML 配置
2. 通过 PMI 接口编写动态库实现各物理模型
3. 在 `lib/material.xml` 或用 `PMI` 指令在输入文件中注册

### Q5：如何进行三维仿真

开源版**不支持三维**仿真。如需三维仿真，需使用 Cogenda 商业版 Genius，或将三维结构沿 Z 方向提取二维截面后用开源版仿真。

---

*文档基于 Genius TCAD Open v1.9.0 源代码整理，如有疑问请参阅源代码中的 Doxygen 注释或联系 Cogenda Pte Ltd（http://www.cogenda.com）。*
