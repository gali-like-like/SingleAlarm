# 文件说明
## main.cpp
这主要就用来解析命名行参数的主程序文件
## playmusicthread.h/playmusicthread.cpp
等待播放音乐时间的一个线程
# 程序使用说明
## 参数说明
+ -S 指定多少s后提醒  
+ -M 指定多少min后提醒   
+ -H 指定多少hour后提醒   
+ -P 指定提醒后的播放的音频文件路径   
+ -T 指定具体时间后播放音乐，具体日期时间格式**yyyy-MM-dd hh:mm:ss**
## 使用步骤
+ 点击releases的其中一个版本

+ 下载Pack.7z  

+ 安装Pack.7z,并打开cmd,输入对应的命令
## 常用命令
+ 具体日期时间点后播放音乐
```
# 假设音频文件放在D:\music\a.mp3
Remind.exe -T "2024-11-14 17:30:00" -P D:\music\a.mp3
```
+ 几个小时后播放音乐
```
# 两小时后播放音频文件
Remind.exe -H 2 -P D:\music\a.mp3
```
+ 几个分钟后播放音乐
```
# 两分钟后播放这个音频文件
Remind.exe -M 2 -P D:\music\a.mp3
```
+ 几秒后播放音乐
```
# 30s后播放音乐
Remind.exe -S 30 -P D:\music\a.mp3
```
+ 1.5小时后播放音乐
```
Remind.exe -H 1 -M 30 -P D:\music\a.mp3
```
**音频文件位置别放到C盘,程序有可能读取不到**
**T和H/M/S互斥,必须有-P和其他的时间选项**
**请务必遵守[GPL](https://www.gnu.org/licenses/gpl-3.0.html)**   
