## 简介

Crank-Nicolson 有限差分方法求解一维含时薛定谔方程，构造线性系统 $Ax = b$，其中 $A$ 为三对角阵，利用三对角阵的 Thomas 追赶法求解该线性系统。

## 使用

使用 CMake 重新组织代码，按以下步骤构建：

```
cd cn-tdse
mkdir build
cd build
cmake ..
make
```

- 以 `build` 目录为中心，以上步骤将生成可执行文件 `bin/tdse` 与 `bin/tise`，分别用于含时与定态薛定谔方程的求解。因此开始计算，只需执行 `./bin/tdse` 或 `./bin/tise`。

- 将于 `res` 目录下存储计算结果 `pot.dat` （势能）、`norm.dat` （波函数）、`time.dat` （时间网格）与 `grid.dat` （空间网格）。

- 获得结果通过执行 `python ../bin/plot.py`， 可生成动画。

- 不同系统的示例位于 `../bin` 中，可修改 `../bin/tise.cpp` 与 `../bin/tdse.cpp` 中引入的头文件，更换示例。比如，可在 `../bin/tise.cpp` 中引入 `tiseSoftCore.hpp` 用于计算软核势体系下的定态薛定谔方程。

- 自定义算例时，需要提供一个描述特定系统的类，该类根据求解定态解或含时解，分别继承自 `TISEComputationScheme` 或 `TDSEComputationScheme`。这里， `../bin` 下的每个示例中，自定义的描述类均命名为 `MyComputationScheme`。随后，通用接口 `IComputationScheme` 的全局指针 `g_pScheme` 将指向该类。内部计算中所有的操作，都是针对该接口实现的。

- 类 `BaseComputationScheme` 是接口 `IComputationScheme` 具体实现的第一层，定义了基本变量，包括 `nx`、`x0`、`dx`、`nt`、`dt`、`print_steps`、`time_step`，以及各种对象指针： `g`、`pot`、`initWave`、`wf`、`files`。

- 类 `TISEComputationScheme` 与 `TDSEComputationScheme` 是具体实现的第二层，针对定态解与含时解分别定义不同的操作。

## 结构

    ├── bin
    │   ├── CMakeLists.txt
    │   ├── plot.py
    │   ├── tdse.cpp
    │   ├── tdse.hpp
    │   ├── tise.cpp
    │   ├── tiseHarmonicOscillator.hpp
    │   └── tiseSoftCore.hpp
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
        │   ├── InitWaveFromFile.hpp
        │   ├── InitWaveGaussian.hpp
        │   └── InitWaveRandom.hpp
        ├── InitWave.hpp
        ├── main.cpp
        ├── potential
        │   ├── PotentialHarmonicOscillator.hpp
        │   └── PotentialSoftCore.hpp
        ├── Potential.hpp
        ├── TDMA.hpp
        ├── TDSEComputationScheme.cpp
        ├── TDSEComputationScheme.hpp
        ├── TISEComputationScheme.cpp
        ├── TISEComputationScheme.hpp
        └── Wavefunc.hpp
