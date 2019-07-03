# 1 描述
URTCWin 是UCloud推出的一款适用于 Windows 平台的实时音视频 SDK，支持windows7 及以上系统，提供了音视频通话基础功能，提供灵活的接口，支持高度定制以及二次开发，如果使用electron addon 请参考[urtc-electron-demo](https://github.com/ucloud/urtc-electron-demo.git)。
# 2 功能列表
## 2.1 基本功能
* 基本的音视频通话功能	
* 支持内置音视频采集的常见功能	
* 支持静音关闭视频功能	
* 支持视频尺寸的配置(180P - 1080P)	
* 支持自动重连	
* 支持丰富的消息回调	
* 支持纯音频互动	
* 支持视频的大小窗口切换	
* 支持获取视频房间统计信息（帧率、码率、丢包率等）	
* 支持编码镜像功能		
* 支持屏幕录制功能	
## 2.2 增值功能
* 电子白板
* 终端智能测试（摄像头、麦克风、网络、播放器）
* AI鉴黄
* 视频录制/视频存储
* 视频水印
* 视频直播CDN分发
* 美颜
* 贴纸/滤镜/哈哈镜
* 背景分割
* 手势
* 虚拟形象
* 变声
# 3 方案介绍
## 3.1 方案架构
![](http://urtcwater.cn-bj.ufileos.com/%E5%9B%BE%E7%89%871.png)
## 3.2 方案优势
* 利用边缘节点就近接入
* 可用性99.99%
* 智能链路调度
* 自有骨干专线+Internet传输优化
* 数据报文AES加密传输
* 全API开放调度能力
* 端到端链路质量探测
* 多点接入线路容灾
* 抗丢包视频30% 音频70%
* 国内平均延时低于75ms 国际平均延时低于200ms
# 4 应用场景
## 4.1 主播连麦
支持主播之间连麦一起直播，带来与传统单向直播不一样的体验
48KHz 采样率、全频带编解码以及对音乐场景的特殊优化保证观众可以听到最优质的声音
## 4.2 视频会议
小范围实时音视频互动，提供多种视频通话布局模板，更提供自定义布局方式，保证会议发言者互相之间的实时性，提升普通观众的观看体验
## 4.3 泛文娱
### 4.3.1 一对一社交
客户可以利用UCloud实时音视频云实现 QQ、微信、陌陌等社交应用的一对一视频互动
### 4.3.2 狼人杀游戏
支持15人视频通话，玩家可在游戏中选择只开启语音或同时开启音视频
## 4.4 在线教育
支持自动和手动发布订阅视频流，方便实现课堂虚拟分组概念，同时支持根据角色设置流权限，保证课程秩序
## 4.5 在线客服
线上开展音视频对话，对客户的资信情况进行审核，方便金融科技企业实现用户在线签约、视频开户验证以及呼叫中心等功能
提供云端存储空间及海量数据的处理能力，提供高可用的技术和高稳定的平台
# 5 接入使用
你可以直接使用umeeting 下面封装的模块（工程目录下 urtcsdk）进行使用，或者自己按照下面步骤集成
## 5.1 开发环境
* Visual Studio 2015 及其它c++ 开发环境 
* Win32 Platform
## 5.2 导入 SDK
* 将 include 文件添加到项目的 INCLUDE 目录下。
* 将 lib 放入项目的 LIB 目录下。
* 将 dll 下的 dll 文件复制到你的可执行文件所在的目录下。
 
## 5.3 初始化
``` c++
Class UcloudRtcEventListenerImpl ： public UcloudRtcEventListener {
……
};
UcloudRtcEventListener* eventhandler = new UcloudRtcEventListenerImpl

m_rtcengine = UCloudRtcEngine::sharedInstance(eventhandler);
m_rtcengine->setSdkMode (1); // 1 testmode 0 normal
m_rtcengine->setTokenSecKey(TEST_SECKEY);//测试模式下设置自己的秘钥
m_rtcengine->setStreamRole(STREAM_BOTH);
m_rtcengine->setAudioOnlyMode(false);
m_rtcengine->setAutoPublishSubscribe(false, true);
m_rtcengine->configLocalAudioPublish(false)；
m_rtcengine->configLocalCameraPublish(true);
m_rtcengine->configLocalScreenPublish(false);
m_rtcengine->setVideoProfile(UCLOUD_RTC_VIDEO_PROFILE_640_360);
```

## 5.4 加入房间
``` c++
tUCloudRtcAuth auth;
auth.mAppId = appid;
auth.mRoomId = roomid;
auth.mUserId = userid;
auth.mUserToken = "1223222";
m_rtcengine->joinChannel(auth);
```

## 5.5 发布流
``` c++
tUCloudRtcMediaConfig config;
config.mAudioEnable = true;
config.mVideoEnable = true;
m_rtcengine->publish(UCLOUD_RTC_MEDIATYPE_VIDEO, config.mVideoEnable,config.mAudioEnable);
```

## 5.6 取消发布
``` c++
tUCloudRtcVideoCanvas view;
view.mVideoView = (int)m_localWnd->GetVideoHwnd();
view.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;		
m_rtcengine->stopPreview(view);
m_rtcengine->unPublish(UCLOUD_RTC_MEDIATYPE_VIDEO);
``` 

## 5.6 订阅流
``` c++
m_rtcengine->subscribe(tUCloudRtcStreamInfo & info)
```

## 5.7 取消订阅：
``` c++
m_rtcengine->unSubscribe(tUCloudRtcStreamInfo& info)
```

## 5.8 离开房间
``` c++
m_rtcengine->leaveChannel ()
```


