# README（中文翻译）

> 原项目：**charybdis-wireless-mini-zmk-firmware** – 面向 Charybdis 3x6 的 ZMK 固件（预配置）

---

## 简介（Intro）

这个仓库提供了**预配置的 ZMK 固件**，用于 **无线版 Charybdis 键盘**。它同时支持 **蓝牙/USB** 和 **2.4G 接收器（Dongle）** 两种形态，并使用了最新的 **输入监听器** 与 **输入处理器** 来在轨迹球与系统之间建立桥接。

如果你想自定义配置：本仓库已配置好 **GitHub Actions**（直接 **fork/clone** 并推送即可触发构建）；或者你也可以使用随仓库提供的 **容器化本地构建脚本**，一条命令即可在本地构建所有固件。

---

## 快速开始（Quick Start）

### 刷写固件（Flashing the Firmware）

从 Releases 页面下载你需要的固件组合：先选择**形态**（Bluetooth / Dongle），再选择**布局**（QWERTY 等）。然后按下列步骤把固件刷到键盘：

1. 解压下载的固件压缩包；  
2. 用 USB 把**右手**按键半侧连接到电脑；  
3. **双击**按下重置（reset）键；  
4. 键盘会以 U 盘（可移动存储）挂载到电脑；  
5. 把对应的 **.uf2** 文件**拷贝**到这个 **NICENANO** 盘里（例如：`charybdis_qwerty_dongle.uf2` → 刷入接收器/右手半侧）；  
6. 等待数秒，设备会自动卸载并重启；  
7. 对**所有设备**重复上述步骤（左右手、接收器等）；  
8. 现在你就可以使用键盘了。

> **注意**：如果这是**首次刷写**，或者你在 **Dongle** 与 **蓝牙/USB** 两种配置之间**切换**，请**先**将“reset 固件”刷进**所有设备**，再刷入目标固件。

---

## 概览与使用（Overview & Usage）

（示意图：基础层键位图 – *keymap base*。查看全部图层请参考项目中的“full render”。）

### ⌨️ 键盘图层（Keyboard Layers）

| 层编号       | 用途说明                                                     |
| ------------ | ------------------------------------------------------------ |
| **0 BASE**   | 标准输入层，启用“无时限（timeless）的主行修饰键（Home-Row Mods）”。 |
| **1 NUM**    | 数字 + 功能键的合层（**点按**出数字，**长按**为 F1–F12）。   |
| **2 NAV**    | 方向键、翻页、TMUX 导航、鼠标指针。                          |
| **3 SYM**    | 符号、标点与若干辅助键。                                     |
| **4 GAME**   | 游戏层（只有基础键码，不带修饰/组合）。                      |
| **5 EXTRAS** | 常用快捷、功能与片段（snippets）。                           |
| **6 MOUSE**  | 完整的鼠标键层（指针 + 滚轮）。                              |
| **7 SLOW**   | 低速指针层，便于像素级的精准操作。                           |
| **8 SCROLL** | 垂直/水平滚动层。                                            |

#### 主行修饰键（Home‑Row Mods）

**侧按住 = 修饰键；点按 = 字母/键位**

- 左手：**Gui / Alt / Shift / Ctrl** → `A S D F`  
- 右手：**Ctrl / Shift / Alt / Gui** → `J K L ;`

#### 组合键（Combos）

| 触发按键              | 结果                                  |
| --------------------- | ------------------------------------- |
| `K17 + K18`           | Caps Word（临时进入**单词大写**模式） |
| `K25 + K26`           | 鼠标左键                              |
| `K26 + K27`           | 鼠标中键                              |
| `K27 + K28`           | 鼠标右键                              |
| `K13 + K22`           | 切换到 **MOUSE** 层                   |
| `K38 + K39`（拇指区） | **BASE ⇄ EXTRAS** 图层互换            |

### ⚙️ 其他亮点（Other Highlights）

- **“无时限”主行修饰键（Timeless HRM）**：基于 *urob* 的方案，配置在 BASE 层，两侧均衡；默认 **280 ms** 的触发判定（tapping-term），并配合 **quick‑tap** 与 **prior‑idle** 调优；  
- **拇指滚动模式**：**按住**最左侧拇指键（`K36`）并滚动轨迹球，可将移动转换为**滚动**；  
- **精准光标模式**：**连点两下**再**按住 `K36`**，可**降低指针速度**；松开后恢复；  
- **“鼠标点击 + 符号层”复合键 – `K37`**  
  - 点按：鼠标**左键单击**；  
  - 点按并**按住**：临时进入 **Layer 3（Symbols）**；  
  - **双击并按住**：**按住**左键（拖拽）；  
  - **三击**：**双击**；  
- **“退格 + 数字层”复合键 – `K38`**  
  - 点按：**Backspace**；  
  - 按住：临时进入 **Layer 1（Numbers）**；  
  - **双击并按住**：保持退格处于按下状态；  
- **蓝牙配置快速切换**：进入 **EXTRAS** 层，通过专用 BT 选择键**配对**或在最多 4 个已保存主机之间切换（支持 BT CLR 清空）；  
- **PMW3610 低功耗轨迹球传感器驱动**（来自 *badjeff*）：已**修补**构建警告并修正**唤醒跳标**问题；  
- **左右半侧感知的 hold‑tap 触发**：仅当**相对半侧**处于激活时，主行键才会作为修饰键生效，避免单手使用时的误触；  
- **Quick‑tap / Prior‑idle 调优**：更快地区分“点按”与“按住”；  
- **ZMK Studio 支持**：当前已支持 **蓝牙**构建的**运行时**键位微调（**Dongle** 版本即将支持）。

---

## 自定义键位、图层与轨迹球（Customize Keymaps, Layers, & Trackball）

### 仅构建指定键位图或指定形态（Building Only Specific Keymaps or Shields）

默认情况下，仓库会同时为 **Bluetooth** 与 **Dongle** 两种形态构建以下三套键位图的固件对：**QWERTY**、**Colemak DH**、**Graphite**。  
若你希望加快构建或只构建所需：

- **单一键位图（keymap）**：`config/keymap/` 目录下的任意 `.keymap` 文件都会被自动构建。默认包含 QWERTY 与 Colemak DH；你可以增删任意数量，只要至少保留 1 个 `.keymap` 文件即可。更多样例可见 `extra-keymaps/`。  
- **单一形态（Shield：Dongle 或 Bluetooth）**：删除 `config/boards/shields/` 下对应的目录（`charybdis_dongle` 或 `charybdis_bt`），就只会构建保留的那一种。

### 修改键位映射（Modify Key Mappings）

**ZMK Studio**：`zmk.studio` 可在**运行时**调整功能（目前仅 **蓝牙**构建实现）。

若要修改**按键外观布局**（物理位置），请编辑 `charybdis-layouts.dtsi`（负责**物理按位**）；这不同于 `charybdis.json`（负责**电气矩阵 ↔ 键位映射**）。  
如需便捷修改物理布局或转换矩阵文件，可使用 **caksoylar** 制作的 **ZMK Physical Layouts Converter**。  
更多 ZMK Studio 用法请参考 ZMK 官方文档。

**Keymap GUI 方式**：

1. Fork/Clone 本仓库；  
2. 打开 **nickcoutsos** 的 **Keymap Editor**；  
3. 允许其访问你的仓库；  
4. 选择你要修改的分支；  
5. 在可视化界面更新键位；  
6. 保存；  
7. 等待流水线（Pipeline）运行完成；  
8. 下载并刷写新固件。

**直接编辑 keymap 文件**：  
选择要分配给某键位的 **behavior（行为）** 与 **参数代码**。更详细的流程见 ZMK 的 **Keymaps & Behaviors** 页面，所有 **keycode** 见官方文档。  
编辑 `config/keymap/charybdis.keymap`，增删键位或图层，然后重新构建并刷写到键盘。

### 修改轨迹球行为（Modifying Trackball Behavior）

轨迹球基于 ZMK 的**模块化输入处理器（input processors）**。相关配置集中在 `config/charybdis_pointer.dtsi`：你可以在这里调节**指针速度**、**加速度**、**滚动行为**等；修改后重新构建固件即可生效。

### 构建你的自定义固件（Building Your Customized Firmware）

**本地构建**（推荐：更快调试与日志排错）：

```bash
cd local-build
docker-compose run --rm builder
```

更多细节（包含如何启用 USB 日志）请查看 `local-build/README.md`。

**GitHub Actions 构建**：

- Fork/Clone 本仓库；  
- 将你的更改推送到 GitHub；  
- GitHub Actions 会自动构建固件，并在 **Actions** 标签页的 Artifacts 中提供下载。

---

## 故障排查（Troubleshooting）

- 如果左右半侧无法正常互联：尝试**同时**按下两个半侧的 **reset** 键；若仍不行，请参考 ZMK 文档中的 **Connection Issues** 页面继续排查；  
- 如果遇到 bug 或某些功能异常：欢迎提交 **Issue/PR**。但请理解：作者**并非职业开发者**，这是一个**业余项目**，可能无法立即修复所有问题。

---

## 鸣谢（Credits）

- **badjeff**  
- **eigatech**  
- **nickcoutsos**  
- **caksoylar**  
- **urob**  