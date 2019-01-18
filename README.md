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

- 类 `Files` 用于系统性地生成一组文件名，建立并保存相应的文件指针。在 `dir` 目录下，指定文件名 `filename` 及该文件名下的文件数量 `n_files`，可生成一组全文件名 `{dir}/{filename}_{idx}.dat`，其中 `idx` 将在 `0` 到 `n_files-1` 间遍历。构造时可不指定文件名及打开方式（`"w"`或`"r"`），但需指定该组文件的数量；如不指定，默认只含一个文件。在实际产生文件前（调用 `open` 函数前），可 `set_dir (dir)` 指定目录，不指定时默认为 `res`。调用 `open` 时，传入文件名及打开方式。关闭文件可调用 `close`。文件指针可通过数组下标 `[]` 的方式引用。示例可参见 `Files.hpp` 尾部说明。

- TISE 算到第 ns 个本征态，则会在 `res` 中产生 ns 组 `norm_idx.dat` 与 `energy_idx.dat`，其中 `idx` 从 0 到 ns-1，表示从基态到第 ns-1 激发态。绘制第 i 态结果时，可以改动 `../bin/plot.py` 中 `loadtxt` 读取数据的文件名 `res/norm_idx.dat` 与 `res/energy_idx.dat`，其他文件名保持原样。

- 类 `InitWave` 提供了波函数的初始化方法，包括模型如 `InitWaveGaussian` 与 `InitWaveRandom`，也可以直接从文件中读取波函数：`InitWaveFromFile`。一般可以用 TISE 方法产生本征态波函数，如，将结果存储为 `res_im/wf_i.dat`，再通过 `InitWaveFromFile` 读取该波函数用于 TDSE 计算，实时间演化结果存放于 `res_re` 中。为了能够使用坐标网格， `InitWaveFunc` 已从 `Initialize` 函数中分离，可以传入已创建好的网格。

- 不同于 TISE 计算会产生 `wf_i.dat`，`norm_i.dat` 与 `energy_i.dat`，其中 `i` 为 0 到 ns-1，TDSE 计算只会产生一组相关数据，其中 `i` 为 0。绘制结果时，所有文件名下标均为 0。

- 绘制程序 `../bin/plot.py` 会根据 `res/pot_0.dat` 数据，自动分辨 TISE （只有一组势能）与 TDSE （`nt` 组势能）计算

## 结构

    ├── bin
    │   ├── CMakeLists.txt
    │   ├── plot.py
    │   ├── tdse.cpp
    │   ├── tdseHarmonicOscillator.hpp
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
