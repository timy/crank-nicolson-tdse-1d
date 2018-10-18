Crank-Nicolson 有限差分方法求解含时薛定谔方程，利用了三对角矩阵的 Thomas 追赶法。二维及以上则失去了三对角矩阵的优势。
因使用 CMake 重新组织代码，按以下步骤构建：

```
cd cn-tdse
mkdir build
cd build
cmake ..
make
```

以 build 目录为中心，以上步骤将生成两个可执行文件 bin/tdse 与 bin/tise，分别用于含时与定态薛定谔方程的求解。

将于 res 目录下存储计算结果 norm.dat （波函数）, time.dat （时间网格）与 grid.dat （空间网格）

获得结果通过执行 python ../bin/plot.py， 可生成动画

├── bin
│   ├── CMakeLists.txt
│   ├── plot.py
│   ├── tdse.cpp
│   ├── tdse.hpp
│   ├── tise.cpp
│   └── tise.hpp
├── CMakeLists.txt
├── README.md
└── src
    ├── BaseComputationScheme.cpp
    ├── BaseComputationScheme.hpp
    ├── CMakeLists.txt
    ├── Constants.hpp
    ├── Files.hpp
    ├── Grid.hpp
    ├── IComputationScheme.hpp
    ├── initWave
    │   ├── InitWaveGaussian.hpp
    │   └── InitWaveRandom.hpp
    ├── InitWave.hpp
    ├── main.cpp
    ├── potential
    │   └── PotentialHarmonicOscillator.hpp
    ├── Potential.hpp
    ├── TDMA.hpp
    ├── TDSEComputationScheme.cpp
    ├── TDSEComputationScheme.hpp
    ├── TISEComputationScheme.cpp
    ├── TISEComputationScheme.hpp
    └── Wavefunc.hpp