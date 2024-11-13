# 文件说明
## main.cpp
这主要就用来解析命名行参数的主程序文件
## playmusicthread.h/playmusicthread.cpp
等待播放音乐时间的一个线程
# 程序使用说明
+ -S 指定多少s后提醒  
+ -M 指定多少min后提醒   
+ -H 指定多少hour后提醒   
+ -P 指定提醒后的播放的音频文件路径   
+ -T 指定具体时间后播放音乐，具体日期时间格式**yyyy-MM-dd hh:mm:ss**   
**AT和H/M/S互斥,必须有-P和其他的时间选项**
**请务必遵守[GPL](https://www.gnu.org/licenses/gpl-3.0.html)**   
