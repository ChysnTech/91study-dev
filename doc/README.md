# 91学习

Copyright (C) 2026 DebArch91工作室

## 学习内容

### [硬件学习](Hardware/README.md)
- [内存和储存](Hardware/memory.md)
- [CPU和GPU](Hardware/cpu-and-gpu.md)

### [软件学习](Software/README.md)
- 待扩展...

## 构建指南

```bash
cd /works/CPP/91study-dev
rm -rf build && mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/works/Qt/6.11.1/gcc_64 ..
make -j$(nproc)
./91study
