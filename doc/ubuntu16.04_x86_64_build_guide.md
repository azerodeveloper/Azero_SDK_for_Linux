# Ubuntu Linux 16.04 LTS (x86_64) 编译指引
这是一份快速指引你在Ubuntu Linux 16.04 LTS (x86_64)上编译Azero Sample项目并在Ubuntu Linux 16.04 LTS (x86_64)本地运行的简要手册。
阅读本文档之前强烈建议先阅读[AzeroSample项目的README](../README.pdf)

## 准备条件
* Ubuntu Linux 16.04 LTS x86_64
* 支持声音输入输出的硬件设备(麦克风与喇叭或语音头戴设备),音频输入必须支持16bit 16000Hz采样
* Ubuntu能连接互联网

## 开始
1. 更新最新的包
```
sudo apt update
sudo apt upgrade
```
2. 安装编译运行依赖包
```
sudo apt install -y wget gcc g++ cmake git openssl libgstreamer1.0-dev \
libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-good \
libgstreamer-plugins-good1.0-dev libgstreamer-plugins-bad1.0-dev \
gstreamer1.0-libav libasound2-dev idn2
```
可参考gcc/g++版本信息如下
```
gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
g++ (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609
```

3. 下载并编译代码
```
mkdir -p ~/git
cd ~/git
git clone https://github.com/sai-azero/Azero_Sample_for_Linux.git

cd Azero_Sample_for_Linux

mkdir third-party
cd third-party
wget -c http://www.portaudio.com/archives/pa_stable_v190600_20161030.tgz
tar xf pa_stable_v190600_20161030.tgz

cd portaudio
./configure --without-jack && make

cd ../../
./run.sh x86_64-linux
```
此时，本地目录下会生成sai_client可执行文件

4. 注册设备
参考[说明](../README.pdf)到官网注册设备

5. 修改配置文件
将~/git/Azero_Sample_for_Linux/sai_config/x86_64-linux 目录下config.json中
```
    "deviceInfo": {
        "clientId": "xxxxxx",
        "deviceSerialNumber": "xxxx",
        "productId": "xxxxx"
    },
```
clientId的值修改成已发布设备的"Client ID", productId的值修改成"产品ID",deviceSerialNumber做为演示程序可随便填写数字或字母组合。

6. 运行
```
cd ~/git/Azero_Sample_for_Linux
export LD_LIBRARY_PATH=$PWD/link-libs/x86_64-linux/lib
sudo ln -s $PWD/sai_config/x86_64-linux /data
./sai_client
```
大概等6秒后就能用"小易小易"唤醒Azero系统
