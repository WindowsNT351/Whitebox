### Whitebox

## ❓ 什么是 Whitebox
Whitebox是用于86Box的Windows CE x86镜像模拟的启动器，包括将NK.bin加载进磁盘文件，修改自动执行文件的LOADCEPC参数，自动打开86Box等。
## 📥 如何使用
# 命令行
```
Whitebox.exe [LOADCEPC参数] [Whitebox参数] <NK的路径>
[LOADCEPC参数]为标准LOADCEPC参数，参见LOADCEPC.exe
[Whitebox参数]：
  - /B:<86Box配置文件路径> 默认为PRO1.cfg 
    提供两个示例配置文件：PRO2.cfg用于WINCE2.0-WINCE2.12以及HPC2000，PRO1.cfg用于其他镜像
```
 例如:
  - Whitebox /L:800x600x16 /M:PRO1.cfg NK.bin 以800x600，16位色启动高版本VESA显示驱动镜像
  - Whitebox /D:3 /M:PRO2.cfg NK.bin 以800x600，8位色启动低版本VGA8BPP显示驱动镜像

# Whitebox.ini配置文件
```
[Img]
imgPath=模板img镜像路径 默认为./samp.img
nkAddrOffset=模板img的NK.bin地址偏移量 默认为0x81000
batAddrOffset=模板img的RUNCEPC.bat地址偏移量 默认为0x4081000
[86Box]
emulPath=86Box可执行文件路径 默认为86Box.exe
emulDir=86Box文件路径 默认为./
```