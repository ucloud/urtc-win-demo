

# 1.0 版本
* 1 支持1对1 1对多音视频通话  单房间支持最多15人 6人同时连麦
* 2 支持纯音频通话模式
* 3 抗丢包 15%  
* 4 断线制动重连
* 5 支持配置自动发布模式
# 1.1 版本
* 1 增加桌面分享功能，并支持指定区域分享
* 2 增加sdk 模式设置，区分测试 正式模式方便测试
* 3 优化内存使用，内存占比减少 30% 
* 4 优化重连效果
# 1.2 版本
* 1 优化抗丢包能力，30%丢包通话基本连续
* 2 增加录制功能，最多支持6路混流录制
* 3 设备测试模块增加视频数据获取功能，方便加入美颜等视频前置处理功能
* 4 增加媒体自动重连能力，并增加视频数据数据实时回调接口
``` c++
int startCaptureFrame(eUCloudRtcVideoProfile profile,UCloudRtcVideoFrameObserver* observer)
``` 
用户可以通过UCloudRtcVideoFrameObserver 获取视频数据 处理后通过UCloudRtcExtendVideoCaptureSource
将数据再次输入到引擎，实现美颜处理
* 5 增加音频数据能量回调功能
* 6 增加外部媒体采集扩展能力
``` c++
int enableExtendVideocapture(bool enable, UCloudRtcExtendVideoCaptureSource* videocapture)
``` 
用户通过实现 UCloudRtcExtendVideoCaptureSource 接口实现外部输入源导入 实现视频前置处理
# 1.3 版本
* 1 优化抗丢包能力，视频最多抗30%丢包，音频最高抗70%丢包
* 2 增加音频文件输入功能，可以替换micphone 输入，支持mp3 wav文件格式 接口 
``` c++
startAudioMixing(const char* filepath, bool replace, bool loop,float musicvol)
``` 
* 3 增加音频数据获取功能，支持用户直接获取播放采集音频数据
``` c++
void regAudioFrameCallback(UCloudRtcAudioFrameCallback* callback) 
``` 
* 4 优化设备模块，音频和视频模块可以分别单独启用 变更后启动引擎调用方式
``` c++
m_mediadevice = UCloudRtcMediaDevice::sharedInstance();
m_mediadevice->InitAudioMoudle();
m_mediadevice->InitVideoMoudle();
``` 
* 5 减少库体积 减少依赖库 解决curl ssl 库和用户自己curl ssl 冲突问题 
* 6 引擎获取接口改变  
``` c++
UCloudRtcEngine *sharedInstance(UCloudRtcEventListener* listener)更改为 UCloudRtcEngine *sharedInstance() 事件监听通过regRtcEventListener(UCloudRtcEventListener* listener)进行注册 
``` 
