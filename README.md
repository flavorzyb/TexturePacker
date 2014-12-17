TexturePacker
=============

打包ios和安卓图片资源的工具

分为GUI和命令行两种模式

GUI模式操作起来很简单，一目了然不再说明
下面介绍下命令行模式：
usage: texturePacker -no-gui -i /usr/local/input -o /usr/local/tmp/output -f ios [-init /usr/local/cache] [-exclude /usr/local/input/aaa,/usr/local/input/bbb] [-min size]
       -no-gui run application in console mode 
       -i input directory path 
       -o output directory path 
       -f ios or android
       -min min size which will be convert
       -init setting init cache dir
       -exclude exclude path, split by ","

例如:
1). 打包资源
 ./BipPacker.app/Contents/MacOS/BipPacker -no-gui -i ../CGame/CGame/Resources/UI/resources-iphonehd -o ../CGame/CGame/Resources/UI/resources-iphonehd -f ios -exclude ../CGame/CGame/Resources/UI/resources-iphonehd/particle_system_quad -min 102400

2). 初始化cache
UI_PATH=../CGame/CGame/Resources/UI/resources-iphonehd
        ./BipPacker.app/Contents/MacOS/BipPacker -no-gui -i ../CGame/CGame/Resources/UI/resources-iphonehd -o ../CGame/CGame/Resources/UI/resources-iphonehd -f ios -init ../cache/ios/UI

[更新说明]
版本: 1.0.0 
更新内容:
        1. 支持ios图片资源格式打包
        2. 使用cache机制以提升打包资源速度
        3. 支持命令行模式运行
        4. 支持初始化cache
        
版本: 1.1.0 
更新内容:
        1. 优化cache规则，支持切版本时不再反复重构cache
        2. 重构cache数据结构
        3. 支持忽略列表功能
        4. 支持最小文件尺寸参数设置
        
版本: 1.2.0 
更新内容:
        1. 支持安卓版本图片资源格式打包
        2. 优化部分代码