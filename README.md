# 91study 91学习
### 本软件由 DevArch91 网络工作室（以社区形式）制作。

## ⚠️ 此项目已存档，不再受维护。
- This project has been archived and is no longer maintained.


- 本软件基于 C++ 开发，UI 框架使用 Qt 6.11。
- 此为自由软件，适用 GPL v3 协议（详情见法律文件），如有改编作品必须开源，任何人不得售卖代码。

## 功能

- [x] Linux 端基础 UI 框架
- [x] 深色模式支持
- [x] 菜单栏（文件/帮助）
- [x] 单元选择（硬件）
- [x] 从 doc 目录读取 Markdown 学习内容
- [x] 小四号字体 (12pt)



## 许可证

本软件使用 GNU General Public License v3.0 授权。

详见 [COPYING](COPYING) 文件。

## 构建

```bash
cd /你的项目路径
cmake -DCMAKE_PREFIX_PATH=/你的QT路径/gcc_64 ..
make -j$(nproc)

