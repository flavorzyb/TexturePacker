# TexturePacker
=============

打包ios和安卓图片资源的工具

## 分为GUI和命令行两种模式

GUI模式操作起来很简单，一目了然不再说明

**命令行模式**

usage:

```bash
texturePacker -no-gui -i /usr/local/input -o /usr/local/tmp/output -f ios [-init /usr/local/cache] [-exclude /usr/local/input/aaa,/usr/local/input/bbb] [-min size]
```

arguments:

```
       -no-gui run application in console mode
       -i input directory path
       -o output directory path
       -f ios or android
       -min min size which will be convert
       -init setting init cache dir
       -exclude exclude path, split by ","
```

## Examples:

- 打包资源

```bash
 ./BipPacker.app/Contents/MacOS/BipPacker -no-gui -i ../CGame/CGame/Resources/UI/resources-iphonehd -o ../CGame/CGame/Resources/UI/resources-iphonehd -f ios -exclude ../CGame/CGame/Resources/UI/resources-iphonehd/particle_system_quad -min 102400
```

- 初始化cache

```bash
    UI_PATH=../CGame/CGame/Resources/UI/resources-iphonehd
    ./BipPacker.app/Contents/MacOS/BipPacker -no-gui -i ../CGame/CGame/Resources/UI/resources-iphonehd -o ../CGame/CGame/Resources/UI/resources-iphonehd -f ios -init ../cache/ios/UI

```
