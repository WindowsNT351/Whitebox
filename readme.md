### Whitebox

## ❓ 什么是 Whitebox
Whitebox是用于86Box的Windows CE x86镜像模拟的启动器，包括将NK.bin加载进磁盘文件，修改自动执行文件的LOADCEPC参数，自动打开86Box等。
## 📥 如何使用
# 命令行
```
Whitebox.exe [LOADCEPC参数] [Whitebox参数] <NK的路径>
[LOADCEPC参数]为标准LOADCEPC参数，参见LOADCEPC.exe
[Whitebox参数]：
  - /M:<86Box配置文件路径> 默认为PRO1.cfg 
    提供两个示例配置文件：PRO2.cfg用于WINCE2.0-WINCE2.12以及HPC2000，PRO1.cfg用于其他镜像
```
 例如:
  - Whitebox /L:800x600x16 /M:PRO1.cfg NK.bin 以800x600，16位色启动高版本VESA显示驱动镜像
  - Whitebox /D:3 /M:PRO2.cfg NK.bin 以800x600，8位色启动低版本VGA8BPP显示驱动镜像

# Whitebox.ini配置文件
```
[Img]
imgPath=模板img镜像路径 默认为./samp.img
outPath=img输出文件 默认在当前用户TEMP文件夹
nkAddrOffset=模板img的NK.bin地址偏移量 默认为0x81000
batAddrOffset=模板img的RUNCEPC.bat地址偏移量 默认为0x4081000
[86Box]
emulPath=86Box可执行文件路径 默认为86Box.exe
emulMch=86Box机型 默认为p54tp4xe
hdCfgKey=86Box配置文件硬盘配置名 默认为hdd_01_fn
nvrPath=指定源Nvram位置 默认为机型名nvr文件
proOutPath=86Box配置文件输出路径 默认在当前用户TEMP文件夹
nvrOutPath=Nvram文件输出文件路径 默认在当前用户TEMP文件夹内的nvr文件夹
nvrOutDir=Nvram文件输出文件夹路径 默认为当前用户TEMP文件夹内的nvr文件夹
```
如果你想在本地文件夹运行Whitebox，请使用以下Whitebox.ini配置文件:
```
[Img]
outPath=".\outa.img"
[86Box]
proOutPath=".\outpro.cfg"
nvrOutPath=".\nvr2\p54tp4xe.nvr"
nvrOutDir=".\nvr2\"
```




Copyright 351Workshop 2025.
