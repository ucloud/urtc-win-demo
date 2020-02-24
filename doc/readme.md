# UCloudRTC win SDK API 手册

* [一、UcloudRtcEngine引擎接口 类](#class)
    * [1.1  获取引擎 - UCloudRtcEngine](#class-UCloudRtcEngine)
    * [1.2  绑定监听事件 - regRtcEventListener ](#class-regRtcEventListener)
    * [1.3  设置SDK模式 - setSdkMode](#class-setSdkMode)
    * [1.4  设置通话模式 - setChannelType](#class-setChannelType)	
    * [1.5  设置流操作权限 - setStreamRole](#class-setStreamRole)
    * [1.6  设置纯音频模式 - setAudioOnlyMode](#class-setAudioOnlyMode)	
    * [1.7  设置自动发布和订阅 - setAutoPublishSubscribe](#class-setAutoPublishSubscribe)
    * [1.8  配置本地音频是否发布 - configLocalAudioPublish](#class-configLocalAudioPublish)
    * [1.9  是否发布音频 - isLocalAudioPublishEnabled](#class-isLocalAudioPublishEnabled)
    * [1.10  配置是否自动发布本地摄像头 - configLocalCameraPublish](#class-configLocalCameraPublish)
    * [1.11  是否发布摄像头 - isLocalCameraPublishEnabled](#class-isLocalCameraPublishEnabled)
    * [1.12  配置是否自动发布本地桌面 - configLocalScreenPublish](#class-configLocalScreenPublish)
    * [1.13  是否发布桌面 - isLocalScreenPublishEnabled](#class-isLocalScreenPublishEnabled)
    * [1.14  设置视频编码参数 - setVideoProfile](#class-setVideoProfile)
    * [1.15  入会时关闭摄像头 - muteCamBeforeJoin](#class-muteCamBeforeJoin)	
    * [1.16  入会时关闭麦克风 - muteMicBeforeJoin](#class-muteMicBeforeJoin)		
    * [1.17  加入房间 - joinChannel](#class-joinChannel)
    * [1.18  离开房间 - leaveChannel](#class-leaveChannel)	
    * [1.19  发布本地流 - publish](#class-publish)
    * [1.20  停止发布本地流 - unPublish](#class-unPublish)
    * [1.21  开启本地渲染 - startPreview](#class-startPreview)	
    * [1.22  停止本地渲染 - stopPreview](#class-stopPreview)	
    * [1.23 订阅远端媒体流 - subscribe](#class-subscribe)
    * [1.24 取消订阅远端媒体流 - unSubscribe](#class-unSubscribe)
    * [1.25  开启远端渲染 - startRemoteView](#class-startRemoteView)	
    * [1.26  停止远端渲染 - stopRemoteView](#class-stopRemoteView)	
    * [1.27  打开/关闭本地麦克风 - muteLocalMic](#class-muteLocalMic)	
    * [1.28  打开/关闭本地视频 - muteLocalVideo](#class-muteLocalVideo)		
    * [1.29  应用静音 - enableAllAudioPlay](#class-enableAllAudioPlay)	
    * [1.30  打开/关闭远端音频 - muteRemoteAudio](#class-muteRemoteAudio)	
    * [1.31  打开/关闭远端视频 - muteRemoteVideo](#class-muteRemoteVideo)	
    * [1.32  是否为自动发布模式 - isAutoPublish](#class-isAutoPublish)	
    * [1.33  是否为自动订阅模式 - isAutoSubscribe](#class-isAutoSubscribe)	
    * [1.34  切换摄像头 - switchCamera](#class-switchCamera)
    * [1.35  设置RTSP视频源 - enableExtendRtspVideocapture](#class-enableExtendRtspVideocapture)
    * [1.36  设置自定义外部视频源 - enableExtendVideocapture](#class-enableExtendVideocapture)	
    * [1.37  设置音频数据监听 - regAudioFrameCallback](#class-regAudioFrameCallback)	
    * [1.38  添加micphone混音文件 - startAudioMixing](#class-startAudioMixing)	
    * [1.39  停止micphone混音 - stopAudioMixing](#class-stopAudioMixing)	
    * [1.40  设置桌面编码参数 - setDesktopProfile](#class-setDesktopProfile)	
    * [1.41  设置桌面采集参数 - setCaptureScreenPagrams](#class-setCaptureScreenPagrams)	
    * [1.42  设置桌面采集类型 - setUseDesktopCapture](#class-setUseDesktopCapture)	
    * [1.43  获取屏幕个数 - getDesktopNums](#class-getDesktopNums)	
    * [1.44  获取屏幕信息 - getDesktopInfo](#class-getDesktopInfo)	
    * [1.45  获取窗口个数 - getWindowNums](#class-getWindowNums)
    * [1.46  获取窗口信息 - getWindowInfo](#class-getWindowInfo)	
    * [1.48  开启录制 - startRecord](#class-startRecord)	
    * [1.49  停止录制 - stopRecord](#class-stopRecord)	
    * [1.50  设置日志等级 - setLogLevel](#class-setLogLevel)	
    * [1.51  获取SDK 版本 - getSdkVersion](#class-getSdkVersion)	
    * [1.52  销毁引擎 - destroy](#class-destroy)	
* [二、UcloudMediaDevice设备引擎接口类](#Device)    
    * [2.1  初始化设备模块 - UCloudRtcMediaDevice](#Device-UCloudRtcMediaDevice)		
    * [2.2  销毁设备模块 - destory](#Device-destory)			
    * [2.3  初始化视频模块 - InitVideoMoudle](#Device-InitVideoMoudle)		
    * [2.4  销毁视频模块 - UnInitVideoMoudle](#Device-UnInitVideoMoudle)		
    * [2.5  初始化音频模块 - InitAudioMoudle](#Device-InitAudioMoudle)		
    * [2.6  销毁音频模块 - UnInitAudioMoudle](#Device-UnInitAudioMoudle)			
    * [2.7  获取摄像头数量 - getCamNums](#Device-getCamNums)		
    * [2.8  获取麦克风数量 - getRecordDevNums](#Device-getRecordDevNums)			
    * [2.9  获取播放设备数量 - getPlayoutDevNums](#Device-getPlayoutDevNums)		
    * [2.10  获取摄像头设备信息 - getVideoDevInfo](#Device-getVideoDevInfo)			
    * [2.11  获取麦克风设备信息 - getRecordDevInfo](#Device-getRecordDevInfo)		
    * [2.12  获取播放设备信息 - getPlayoutDevInfo](#Device-getPlayoutDevInfo)		
    * [2.13  获取当前使用的摄像头信息 - getCurCamDev](#Device-getCurCamDev)		
    * [2.14  获取当前使用的麦克风设备信息 - getCurRecordDev](#Device-getCurRecordDev)		
    * [2.15  获取当前使用的播放设备信息 - getCurPlayoutDev](#Device-getCurPlayoutDev)		
    * [2.16  设置视频设备 - setVideoDevice](#Device-setVideoDevice)		
    * [2.17  设置麦克风设备 - setRecordDevice](#Device-setRecordDevice)			
    * [2.18  设置播放设备 - setPlayoutDevice](#Device-setPlayoutDevice)		
    * [2.19  获取应用播放音量 - getPlaybackDeviceVolume](#Device-getPlaybackDeviceVolume)			
    * [2.20  设置应用播放音量 - setPlaybackDeviceVolume](#Device-setPlaybackDeviceVolume)		
    * [2.21  获取系统麦克风音量 - getRecordingDeviceVolume](#Device-getRecordingDeviceVolume)			
    * [2.22  设置系统麦克风音量 - setRecordingDeviceVolume](#Device-setRecordingDeviceVolume)		
    * [2.23  开始摄像头测试 - startCamTest](#Device-startCamTest)		
    * [2.24  停止摄像头测试 - stopCamTest](#Device-stopCamTest)			
    * [2.25  开始麦克风测试 - startRecordingDeviceTest](#Device-startRecordingDeviceTest)		
    * [2.26  停止麦克风测试 - stopRecordingDeviceTest](#Device-stopRecordingDeviceTest)		
    * [2.27  开始播放设备测试 - startPlaybackDeviceTest](#Device-startPlaybackDeviceTest)		
    * [2.28  停止播放设备测试 - stopPlaybackDeviceTest](#Device-stopPlaybackDeviceTest)			
    * [2.29  开始采集视频数据回调 - startCaptureFrame](#Device-startCaptureFrame)		
    * [2.30  停止采集视频数据回调 - stopCaptureFrame](#Device-stopCaptureFrame)			
* [三、接口错误表](#ErrCode)    
    * [3.1  事件回调错误码](#ErrCode-shijian)		
    * [3.2  函数值错误码](#ErrCode-hanshu)			
* [四、函数结构体说明](#struct)    
    * [4.1  设备信息类 - tUCloudRtcDeviceInfo](#struct-tUCloudRtcDeviceInfo)		
    * [4.2  媒体发布配置类 - tUCloudRtcMediaConfig](#struct-tUCloudRtcMediaConfig)		
    * [4.3  媒体轨道类型类型描述 - eUCloudRtcTrackType](#struct-eUCloudRtcTrackType)		
    * [4.4  媒体流类型描述 - eUCloudRtcMeidaType](#struct-eUCloudRtcMeidaType)		
    * [4.5  流信息结构体 - tUCloudRtcStreamInfo](#struct-tUCloudRtcStreamInfo)		
    * [4.6  录制水印位置 - eUCloudRtcWaterMarkPos](#struct-eUCloudRtcWaterMarkPos)		
    * [4.7  水印类型 - eUCloudRtcWaterMarkType](#struct-eUCloudRtcWaterMarkType)		
    * [4.8  Mute操作结构体 - tUCloudRtcMuteSt](#struct-tUCloudRtcMuteSt)		
    * [4.9  录制输出等级 - eUCloudRtcRecordProfile](#struct-eUCloudRtcRecordProfile)		
    * [4.10  录制媒体类型 - eUCloudRtcRecordType](#struct-eUCloudRtcRecordType)			
    * [4.11  录制配置信息 - tUCloudRtcRecordConfig](#struct-tUCloudRtcRecordConfig)		
    * [4.12  渲染模式 - eUCloudRtcRenderMode](#struct-eUCloudRtcRenderMode)		
    * [4.13  日志级别 - eUCloudRtcLogLevel](#struct-eUCloudRtcLogLevel)		
    * [4.14  视频质量参数 - eUCloudRtcVideoProfile](#struct-eUCloudRtcVideoProfile)		
    * [4.15  桌面输出参数 - eUCloudRtcScreenProfile](#struct-eUCloudRtcScreenProfile)		
    * [4.16  桌面采集参数 - tUCloudRtcScreenPargram](#struct-tUCloudRtcScreenPargram)		
    * [4.17  桌面采集类型 - eUCloudRtcDesktopType](#struct-eUCloudRtcDesktopType)		
    * [4.18  桌面参数 - tUCloudRtcDeskTopInfo](#struct-tUCloudRtcDeskTopInfo)		
    * [4.19  通道类型 - eUCloudRtcUserStreamRoleCHANNEL](#struct-eUCloudRtcUserStreamRoleCHANNEL)		
    * [4.20  流权限 - eUCloudRtcUserStreamRoleSTREAM](#struct-eUCloudRtcUserStreamRoleSTREAM)	
    * [4.21  渲染窗口 - tUCloudRtcVideoCanvas](#struct-tUCloudRtcVideoCanvas)		
    * [4.22  登录信息类 - tUCloudRtcAuth](#struct-tUCloudRtcAuth)		
    * [4.23  当前媒体状态统计 - tUCloudRtcStreamStats](#struct-tUCloudRtcStreamStats)		
    * [4.24  录制信息回调 - tUCloudRtcRecordInfo](#struct-tUCloudRtcRecordInfo)		
    * [4.25  音频帧 - tUCloudRtcAudioFrame](#struct-tUCloudRtcAudioFrame)		
    * [4.26  视频数据帧类型 - eUCloudRtcVideoFrameType](#struct-eUCloudRtcVideoFrameType)		
    * [4.27  视频数据帧 - tUCloudRtcVideoFrame](#struct-tUCloudRtcVideoFrame)		
    * [4.28  消息回调事件接口类 - UCloudRtcEventListener](#struct-UCloudRtcEventListener)		
    * [4.29  音频测试回调 - UCloudRtcMediaListener](#struct-UCloudRtcMediaListener)		
    * [4.30  音频数据回调 - UCloudRtcAudioFrameCallback](#struct-UCloudRtcAudioFrameCallback)			
    * [4.31  视频扩展数据源 - UCloudRtcExtendVideoCaptureSource](#struct-UCloudRtcExtendVideoCaptureSource)		
    * [4.32  视频数据回调 - UCloudRtcExtendVideoRender](#struct-UCloudRtcExtendVideoRender)		
    * [4.33  视频数据回调监听类（yuv420p格式） - UCloudRtcVideoFrameObserver](#struct-UCloudRtcVideoFrameObserver)		
    * [4.34  视频渲染类型 - eUCloudRtcRenderType](#struct-eUCloudRtcRenderType)		
    * [4.35  视频编码类型 - eUCloudRtcVideoCodec](#struct-eUCloudRtcVideoCodec)		
    * [4.36  视频参数 - tUCloudVideoConfig](#struct-tUCloudVideoConfig)		
    
	
<a name='class'></a>

## 一、 class UcloudRtcEngine引擎接口类

<a name='class-UCloudRtcEngine'></a>

### 1.1  获取引擎

static UCloudRtcEngine *sharedInstance()

**返回值**

UCloudRtcEngine* 引擎类指针

**参数说明**    

无

**消息回调**

无


### 1.2  绑定监听事件

void regRtcEventListener(UCloudRtcEventListener* listener)

**返回值** 

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  listener[in]   | UCloudRtcEventListener <br> eUCloudRtcSdkMode     | Class | N |

**消息回调**

无

### 1.3  设置SDK模式

virtual int setSdkMode (eUCloudRtcSdkMode mode)

**返回值**

参见错误描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mode[in]   | 可以设置为测试模式、正式模式。 <br> 详见eUCloudRtcSdkMode。     | enum | N |

**消息回调**

无

<a name='class-setChannelType('></a>

###  1.4  设置应用模式

virtual int setChannelType(eUCloudRtcUserStreamRole TYPE)

可以设置为会议模式、直播模式。会议模式，默认都有推流权限；直播模式，推流、拉流权限，只能任选其一。

**返回值**

参见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  TYPE[in]   | 可以设置为会议模式、直播模式。 <br> 详见eUCloudRtcUserStreamRole说明。     | enum | N |



<a name='class-setStreamRole'></a>

###  1.5  设置流操作权限

virtual int setStreamRole(eUCloudRtcUserStreamRole role)

**返回值**

参见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  role[in]   | 可以设置为上行推流、下行拉流、双向推拉流。 <br> 详见UCloudStreamRole说明。     | enum | N |


**消息回调**

无

<a name='class-setAudioOnlyMode'></a>

###  1.6  设置纯音频模式

virtual int setAudioOnlyMode(bool audioOnly)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  audioOnly[in]  | 是否设置为纯音频模式    | bool | N |

**消息回调**

无

<a name='class-setAutoPublishSubscribe'></a>

###  1.7  设置自动发布和订阅

virtual int setAutoPublishSubscribe(bool autoPub, bool autoSub)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  autoPub[in]  | 是否自动发布流     | bool | N |
|  autoSub[in]   | 是否自动订阅流     | bool | N |

**消息回调**

无


<a name='class-configLocalAudioPublish'></a>

###  1.8  配置是否自动发布本地音频

virtual int configLocalAudioPublish(bool enable)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in]   | 配置自动发布本地音频可选：是、否     | bool | N |

**消息回调**

无


<a name='class-isLocalAudioPublishEnabled'></a>

###  1.9  是否发布音频

virtual bool isLocalAudioPublishEnabled()

是否发布音频，必须在配置自动发布本地音频时，才能调用。

**返回值**

true 发布音频;false 不发布音频。

**参数说明**    

无

**消息回调**

无


<a name='class-configLocalCameraPublish'></a>

###  1.10  配置是否自动发布本地摄像头

virtual int configLocalCameraPublish(bool enable)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in]   | 配置自动发布本地视频可选：是、否     | bool | N |

**消息回调**

无

<a name='class-isLocalCameraPublishEnabled'></a>

###  1.11  是否发布摄像头

virtual bool isLocalCameraPublishEnabled()

是否发布摄像头，必须在配置自动发布本地摄像头时，才能调用。

**返回值**

true 发布摄像头;false 不发布摄像头。

**参数说明**    

无

**消息回调**

无

<a name='class-configLocalScreenPublish'></a>

###  1.12  配置是否自动发布本地桌面

virtual int configLocalScreenPublish (bool enable)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in]   | 配置自动发布本地桌面可选：是、否     | bool | N |

**消息回调**

无

<a name='class-isLocalScreenPublishEnabled'></a>

###  1.13  是否发布桌面

virtual bool isLocalScreenPublishEnabled()

是否发布桌面，必须在配置自动发布本地桌面时，才能调用。

**返回值**

true 发布桌面;false 不发布桌面。

**参数说明**    

无

**消息回调**

无


<a name='class-setVideoProfile'></a>

###  1.14  设置视频编码参数

virtual void setVideoProfile(eUCloudRtcVideoProfile& profile，tUCloudVideoConfig& videoconfig)

设置视频编码参数，可选定义好的编码视频分辨率；也可以自定义编码参数，设置视频编码宽、高、帧率。


**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  profile[in]   | 设置视频编码分辨率，详见eUCloudRtcVideoProfile参数说明     | enum | N |
| videoconfig[in]    | 设置视频编码宽、高、帧率 | struct| N |

自定义编码参数时，profile必须为 UCLOUD_RTC_VIDEO_PROFILE_NONE，用户自定义videoconfig参数成员必须指定有效值。

profile为有效值时，后面的参数无意义。

**消息回调**

无

<a name='class-muteCamBeforeJoin'></a>

###  1.15  入会时关闭摄像头

virtual int muteCamBeforeJoin(bool mute)

入会时是否关闭摄像头。如果关闭摄像头，会发送黑屏帧。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | true，关闭摄像头。 <br> false，打开摄像头。     | bool | N |

**消息回调**

无

<a name='class-muteMicBeforeJoin'></a>

###  1.16  入会时关闭麦克风

virtual int muteMicBeforeJoin (bool mute)

入会时是否关闭麦克风。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | true，关闭麦克风。 <br> false，打开麦克风。     | bool | N |

**消息回调**

无

<a name='class-joinChannel'></a>

###  1.17  加入房间

virtual int joinChannel(tUCloudRtcAuth & auth)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  auth[in]   | 加入房间参数，包含AppId、RoomId、UserId、Token。<br>详见tUCloudRtcAuth说明。    | struct | N |

**消息回调**

无



<a name='class-leaveChannel'></a>

###  1.18  离开房间

virtual int leaveChannel()

**返回值**

详见错误码描述。

**参数说明**    

无

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}


<a name='class-publish'></a>

###  1.19  发布本地流

virtual int publish(eUCloudRtcMeidaTypetype, bool hasvideo, bool hasaudio)

发布本地流，支持发布摄像头、发布桌面。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 发布流类型可选:摄像头、桌面。<br> 详见eUCloudRtcMeidaType参数说明。    | enum | N |
|  hasvideo[in]  | 发布流是否带视频    | bool | N |
|  hasaudio[in] | 发布流是否带音频    | bool | N |

**消息回调**

0 成功；其他失败。

具体参见 消息回调事件接口类对应接口virtual void onLocalPublish (const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

<a name='class-unPublish'></a>

###  1.20  停止发布本地流

virtual int unPublish(eUCloudRtcMeidaType type)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 发布流类型可选:摄像头、桌面。<br> 详见eUCloudRtcMeidaType参数说明。    | enum | N |

**消息回调**

0 成功；其他失败。

具体参见 消息回调事件接口类对应接口virtual void onLocalUnPublish (const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

<a name='class-startPreview'></a>

###  1.21  开启本地渲染

virtual int startPreview(tUCloudRtcVideoCanvas& view)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无

<a name='class-stopPreview'></a>

###  1.22  停止本地渲染

virtual int stopPreview (tUCloudRtcVideoCanvas& view)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无

<a name='class-subscribe'></a>

###  1.23 订阅远端媒体流

virtual int subscribe(tUCloudRtcStreamInfo & info)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 包含UserId、StreamId等。<br> 详见eUCloudRtcMeidaType参数说明。    | enum | N |

**消息回调**

0 成功；其他失败。

具体参见 消息回调事件接口类对应接口virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

<a name='class-unSubscribe'></a>

###  1.24 取消订阅远端媒体流

virtual void unSubscribe(tUCloudRtcStreamInfo& info)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 包含UserId、StreamId等。<br> 详见eUCloudRtcMeidaType参数说明。    | enum | N |

**消息回调**

0 成功；其他失败。

具体参见 消息回调事件接口类对应接口virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

<a name='class-startRemoteView'></a>

###  1.25  开启远端渲染

virtual int startRemoteView (tUCloudRtcVideoCanvas & view)

开启远端渲染,必须在订阅成功后才能调用。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无

<a name='class-stopRemoteView'></a>

###  1.26  停止远端渲染

virtual int stopRemoteView (tUCloudRtcVideoCanvas & view)

停止远端渲染,必须在订阅成功后才能调用。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无


<a name='class-muteLocalMic'></a>

###  1.27  打开/关闭本地麦克风

virtual int muteLocalMic(bool mute)

是否关闭本地麦克风。关闭后发送静音包。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | 是否关闭本地麦克风     | bool | N |

**消息回调**

0 成功；其他失败。

具体参见 消息回调事件接口类对应接口virtual void onLocalStreamMuteRsp(const int code, const char* msg, eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}


<a name='class-muteLocalVideo'></a>

###  1.28  打开/关闭本地视频

virtual int muteLocalVideo(bool mute, eUCloudRtcMeidaType mtype)

是否关闭本地视频。关闭后，发送黑屏帧。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | 是否关闭本地视频     | bool | N |
|  mtype[in]  | 流类型可选:摄像头、桌面。<br> 详见eUCloudRtcMeidaType参数说明。      | enum | N |

**消息回调**

无


<a name='class-enableAllAudioPlay'></a>

###  1.29  应用静音

virtual int enableAllAudioPlay(bool enable)

关闭应用的声音，静音。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in]  | true，打开声音播放。 <br> false，关闭应用声音。     | bool | N |

**消息回调**

无


<a name='class-muteRemoteAudio'></a>

###  1.30  打开/关闭远端音频

virtual int muteRemoteAudio (tUCloudRtcStreamInfo& info,bool mute)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 包含UserId、StreamId等。<br> 详见tUCloudRtcStreamInfo参数说明。    | enum | N |
|  mute[in]   | true，关闭远端音频。 <br> false，打开远端音频。     | bool | N |

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid, eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}


<a name='class-muteRemoteVideo'></a>

###  1.31  打开/关闭远端视频

virtual int muteRemoteVideo(tUCloudRtcStreamInfo& info, bool mute)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]   | 包含UserId、StreamId等。<br> 详见tUCloudRtcStreamInfo参数说明。    | enum | N |
|  mute[in]   | true，关闭远端视频。 <br> false，打开远端视频。     | bool | N |

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid, eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}


<a name='class-isAutoPublish'></a>

###  1.32  是否为自动发布模式

virtual bool isAutoPublish()

**返回值**

true 是，false 不是。

**参数说明**    

无

**消息回调**

无


<a name='class-isAutoSubscribe'></a>

###  1.33  是否为自动订阅模式

virtual bool isAutoSubscribe()

**返回值**

true 是，false 不是。

**参数说明**    

无

**消息回调**

无


<a name='class-switchCamera'></a>

###  1.34  切换摄像头

virtual int switchCamera(tUCloudRtcDeviceInfo& info)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  info[in]  | 切换的摄像头设备信息    | tUCloudRtcDeviceInfo| N |

**消息回调**

无

<a name='class-enableExtendRtspVideocapture'></a>

###  1.35  设置RTSP视频源

virtual int enableExtendRtspVideocapture(eUCloudRtcMeidaType type, bool enable, const char* rtspurl)

设置RTSP视频源，支持设置2路RTSP视频源。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  type[in]  | rtsp要替换的视频源     | eUCloudRtcMeidaType| N |
|  enable[in]  | 是否开启RTSP源输入     | bool | N |
|  rtspurl[in]  | rtsp 地址     | char* | N |

**消息回调**

无

<a name='class-enableExtendVideocapture'></a>

###  1.36  设置自定义外部视频源

virtual int enableExtendVideocapture(bool enable, UCloudRtcExtendVideoCaptureSource* videocapture)

设置自定义外部视频源。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in] | 是否开启自定义外部视频源输入     | bool| N |
|  Videocapture[in]  | 自定义外部数据源     | UCloudRtcExtendVideoCaptureSource | N |

**消息回调**

无

<a name='class-regAudioFrameCallback'></a>

###  1.37  设置音频数据监听

virtual void regAudioFrameCallback(UCloudRtcAudioFrameCallback* callback)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  callback[in]  | 音频回调监听     | UCloudRtcAudioFrameCallback | N |

**消息回调**

无


<a name='class-startAudioMixing'></a>

###  1.38  添加micphone混音文件

virtual int startAudioMixing(const char* filepath, bool replace, bool loop,float musicvol)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  filepath [in]   | 文件地址     | const char*| N |
|  replace[in]     | 是否取代mic 输入:true 替代、false 混合     | bool| N |
|  loop[in]  | 是否循环播放：true 循环播放、false 一次播放    | bool| N |
|  musicvol[in]   | 背景音音量（0.0 – 1.0），1.0表示原始音量    | float| N |

**消息回调**

无

<a name='class-stopAudioMixing'></a>

###  1.39  停止micphone混音

virtual int stopAudioMixing()

**返回值**

详见错误码描述。

**参数说明**    

无

**消息回调**

无




<a name='class-setDesktopProfile'></a>

###  1.40  设置桌面编码参数

virtual void setDesktopProfile (eUCloudRtcVideoProfile& profile)

设置桌面编码参数，可以设定桌面或者某一窗口的编码分辨率。

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  profile[in]   | 设置视频编码分辨率，详见eUCloudRtcVideoProfile参数说明     | enum | N |

**消息回调**

无

<a name='class-setCaptureScreenPagrams'></a>

###  1.41  设置桌面采集参数

virtual void setCaptureScreenPagrams (tUCloudRtcScreenPargram& par)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  par[in]   | 设置包含窗口或者桌面id标识、起始坐标、宽、高。<br> 详见tUCloudRtcScreenPargram参数说明。     | struct | N |

**消息回调**

无

<a name='class-setUseDesktopCapture'></a>

###  1.42  设置桌面采集类型

virtual int setUseDesktopCapture(eUCloudRtcDesktopType desktoptype)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  desktoptype [in]  | 可选采集的是桌面还是窗口。<br> 详见eUCloudRtcDesktopType参数说明。     | enum | N |

**消息回调**

无

<a name='class-getDesktopNums'></a>

###  1.43  获取屏幕个数

virtual void getDesktopNums ()

**返回值**

屏幕个数。

**参数说明**    

无

**消息回调**

无

<a name='class-getDesktopInfo'></a>

###  1.44  获取屏幕信息

virtual int getDesktopInfo(int pos, tUCloudRtcDeskTopInfo& info)

**返回值**

0 成功；其他失败。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  pos[in]   | 数组下标，个数通过getDesktopNums 获取     | int | N |
| info[in]    | 包含桌面/窗口类型、id 标识、桌面标题。<br> 详见tUCloudRtcDeskTopInfo参数说明。  | struct| N |

**消息回调**

无

<a name='class-getWindowNums'></a>

###  1.45  获取窗口个数

virtual void getWindowNums ()

**返回值**

窗口个数。

**参数说明**    

无

**消息回调**

无

<a name='class-getWindowInfo'></a>

###  1.46  获取窗口信息

virtual int getWindowInfo (int pos, tUCloudRtcDeskTopInfo& info)

**返回值**

0 成功；其他失败。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  pos[in]   | 数组下标，个数通过getWindowNums 获取     | int | N |
| info[in]    | 包含桌面/窗口类型、id 标识、桌面标题。<br> 详见tUCloudRtcDeskTopInfo参数说明。  | struct| N |

**消息回调**

无


<a name='class-startRecord'></a>

###  1.48  开启录制

virtual int startRecord(tUCloudRtcRecordConfig& recordconfig)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  recordconfig [in]  | 录制参数，具体详见tUCloudRtcRecordConfig。     | struct | N |

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onStartRecord(const int code, const char* msg, tUCloudRtcRecordInfo& info) {} 



<a name='class-stopRecord'></a>

###  1.49  停止录制

virtual int stopRecord ()

**返回值**

详见错误码描述。

**参数说明**    

无

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onStopRecord(const int code, const char* msg, const char* recordid) {} 


<a name='class-setLogLevel'></a>

###  1.50  设置日志等级

virtual void setLogLevel(eUCloudRtcLogLevel level)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  level[in]   | 可以设置为DEBUG、消息、告警、错误、无告警。 <br> 详见eUCloudRtcLogLevel说明。     | enum | N |

**消息回调**

无


<a name='class-getSdkVersion'></a>

### 1.51  获取SDK 版本

static const char *getSdkVersion()

**返回值**

SDK的版本号

**参数说明**    

无

**消息回调**

无

<a name='class-destroy'></a>

### 1.52  销毁引擎

static void destroy()

**返回值**

无

**参数说明**    

无

**消息回调**

无

<a name='Device'></a>

## 二、UcloudMediaDevice设备引擎接口类

<a name='Device-UCloudRtcMediaDevice'></a>

###  2.1  初始化设备模块

static UCloudRtcMediaDevice*sharedInstance()

**返回值**

UCloudRtcMediaDevice*  设备类指针

**参数说明**    

无

**消息回调**

无

<a name='Device-destory'></a>

###  2.2  销毁设备模块

static void destory()

**返回值**

无

**参数说明**    

无

**消息回调**

无

<a name='Device-InitVideoMoudle'></a>

###  2.3  初始化视频模块

virtual int InitVideoMoudle()

**返回值**

code回调为0代表成功，其他代表失败。

**参数说明**    

无

**消息回调**

无

<a name='Device-UnInitVideoMoudle'></a>

###  2.4  销毁视频模块

virtual int UnInitVideoMoudle()

**返回值**

0 成功，其他失败。

**参数说明**    

无

**消息回调**

无

<a name='Device-InitAudioMoudle'></a>

###  2.5  初始化音频模块

virtual int InitAudioMoudle ()

**返回值**

code回调为0代表成功，其他代表失败。

**参数说明**    

无

**消息回调**

无


<a name='Device-UnInitAudioMoudle'></a>

###  2.6  销毁音频模块

virtual int UnInitAudioMoudle()

**返回值**

code回调为0代表成功，其他代表失败。

**参数说明**    

无

**消息回调**

无

<a name='Device-getCamNums'></a>

###  2.7  获取摄像头数量

virtual int getCamNums()

**返回值**

摄像头的数量。

**参数说明**    

无

**消息回调**

无

<a name='Device-getRecordDevNums'></a>

###  2.8  获取麦克风数量

virtual int getRecordDevNums()

**返回值**

获取的麦克风数量。

**参数说明**    

无

**消息回调**

无

<a name='Device-getPlayoutDevNums'></a>

###  2.9  获取播放设备数量

virtual int getPlayoutDevNums()

**返回值**

获取的播放设备数量。

**参数说明**    

无

**消息回调**

无

<a name='Device-getVideoDevInfo'></a>

###  2.10  获取摄像头设备信息

virtual int getVideoDevInfo(int index, char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  index[in]  | 对应的数组下标     | int | N |
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无

<a name='Device-getRecordDevInfo'></a>

###  2.11  获取麦克风设备信息

virtual int getRecordDevInfo(int index, char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  index[in]  | 对应的数组下标     | int | N |
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无


<a name='Device-getPlayoutDevInfo'></a>

###  2.12  获取播放设备信息

virtual int getPlayoutDevInfo(int index, char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  index[in]  | 对应的数组下标     | int | N |
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无

<a name='Device-getCurCamDev'></a>

###  2.13  获取当前使用的摄像头信息

virtual int getCurCamDev (char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |


**消息回调**

无


<a name='Device-getCurRecordDev'></a>

###  2.14  获取当前使用的麦克风设备信息

virtual int getCurRecordDev (char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无


<a name='Device-getCurPlayoutDev'></a>

###  2.15  获取当前使用的播放设备信息

virtual int getCurPlayoutDev (char devname[MAX_DEVICE_NAME_LEN], char devid[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devname[in] | 设备名称     | char数组 | N |
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无

<a name='Device-setVideoDevice'></a>

###  2.16  设置视频设备

virtual int setVideoDevice(const char deviceId[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无


<a name='Device-setRecordDevice'></a>

###  2.17  设置麦克风设备

virtual int setRecordDevice(const char deviceId[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无

<a name='Device-setPlayoutDevice'></a>

###  2.18  设置播放设备

virtual int setPlayoutDevice (const char deviceId[MAX_DEVICE_NAME_LEN])

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  devid[in]  | 设备id 号     | char数组 | N |

**消息回调**

无

<a name='Device-getPlaybackDeviceVolume'></a>

###  2.19  获取应用播放音量

virtual int getPlaybackDeviceVolume (int *volume)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  volume[out] | 系统播放音量（0-255）     | int 指针 | N |

**消息回调**

无

<a name='Device-setPlaybackDeviceVolume'></a>

###  2.20  设置应用播放音量

virtual int setPlaybackDeviceVolume (int volume)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  volume[out] | 系统播放音量（0-255）     | int 指针 | N |

**消息回调**

无

<a name='Device-getRecordingDeviceVolume'></a>

###  2.21  获取系统麦克风音量

virtual int getRecordingDeviceVolume (int *volume)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  volume[out] | 系统麦克风音量（0-255）  | int 指针 | N |

**消息回调**

无

<a name='Device-setRecordingDeviceVolume'></a>

###  2.22  设置系统麦克风音量

virtual int setRecordingDeviceVolume (int volume)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  volume[out] | 系统麦克风音量（0-255）  | int 指针 | N |

**消息回调**

无

<a name='Device-startCamTest'></a>

###  2.23  开始摄像头测试

virtual int startCamTest(const char deviceId[MAX_DEVICE_NAME_LEN]，UCloudRtcVideoProfile& profile , void* videoview)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  deviceid[in]  | 摄像头的id     | char 数组 | N |
|  profile[in] | 摄像头的参数     | UCloudRtcVideoProfile | N |
|  videoview[in] | 显示的渲染窗口句柄    | char 数组 | N |

**消息回调**

无

<a name='Device-stopCamTest'></a>

###  2.24  停止摄像头测试

virtual int stopCamTest()

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

无

**消息回调**

无

<a name='Device-startRecordingDeviceTest'></a>

###  2.25  开始麦克风测试

virtual int startRecordingDeviceTest(UCloudRtcAudioLevelListener* audiolevel)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  volume[out] | 音频能量回调  | UCloudRtcAudioLevelListener| N |

**消息回调**

virtual void onMiceAudioLevel(int volume) {} volume 音频能量 （0--255）


<a name='Device-stopRecordingDeviceTest'></a>

###  2.26  停止麦克风测试

virtual int stopRecordingDeviceTest()

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

无

**消息回调**

无

<a name='Device-startPlaybackDeviceTest'></a>

###  2.27  开始播放设备测试

virtual int startPlaybackDeviceTest(const char* filePath)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  filePath[in]  | 播放文件的地址（wav 格式）     | const char* | N |

**消息回调**

无

<a name='Device-stopPlaybackDeviceTest'></a>

###  2.28  停止播放设备测试

virtual int stopPlaybackDeviceTest()

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

无

**消息回调**

无

<a name='Device-startCaptureFrame'></a>

###  2.29  开始采集视频数据回调

virtual int startCaptureFrame(eUCloudRtcVideoProfile profile,UCloudRtcVideoFrameObserver* observer)

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  profile[in]  | 采集的视频参数     | eUCloudRtcVideoProfile | N |
|  observer[in]  | 视频数据监听类     | UCloudRtcVideoFrameObserver | N |

**消息回调**

无

<a name='Device-stopCaptureFrame'></a>

###  2.30  停止采集视频数据回调

virtual int stopCaptureFrame()

**返回值**

code回调为0代表成功，其他代表失败。详见错误码描述。

**参数说明**    

无

**消息回调**

无

<a name='ErrCode'></a>

## 三、 接口错误表

<a name='ErrCode-shijian'></a>

###  3.1  事件回调错误码

```cpp
typedef enum _tUCloudRtcCallbackErrCode{    
	UCLOUD_RTC_CALLBACK_ERR_CODE_OK = 0,  //成功    
	UCLOUD_RTC_CALLBACK_ERR_SERVER_CON_FAIL = 5000, //服务器连接失败    
	UCLOUD_RTC_CALLBACK_ERR_SERVER_DIS, // 服务端连接断开    
	UCLOUD_RTC_CALLBACK_ERR_SAME_CMD,  //重复的调用    
	UCLOUD_RTC_CALLBACK_ERR_NOT_IN_ROOM, //未加入房间 无发进行操作     
	UCLOUD_RTC_CALLBACK_ERR_ROOM_JOINED, // 已加入房间 无需加入    
	UCLOUD_RTC_CALLBACK_ERR_SDK_INNER,   // SDK 内部错误    
	UCLOUD_RTC_CALLBACK_ERR_ROOM_RECONNECTING, // 重连中 请求无法投递          
	UCLOUD_RTC_CALLBACK_ERR_STREAM_PUBED,  // 流已经发布  无需发布    
	UCLOUD_RTC_CALLBACK_ERR_PUB_NO_DEV,  // 发布无可用 音频 视频设备    
	UCLOUD_RTC_CALLBACK_ERR_STREAM_NOT_PUB, //流没有发布 无法对流进行操作    
	UCLOUD_RTC_CALLBACK_ERR_STREAM_SUBED,  //流已经订阅  无需订阅    
	UCLOUD_RTC_CALLBACK_ERR_STREAM_NO_SUB, //流没有订阅  无法    
	UCLOUD_RTC_CALLBACK_ERR_SUB_NO_USER,   //无对应的用户 无法订阅    
	UCLOUD_RTC_CALLBACK_ERR_SUB_NO_STREAM,  // 无对应的媒体流    
	UCLOUD_RTC_CALLBACK_ERR_USER_LEAVING, // 用户正在离开房间  无法进行其他操作    
	UCLOUD_RTC_CALLBACK_ERR_NO_HAS_TRACK,  //无对应的媒体轨道    
	UCLOUD_RTC_CALLBACK_ERR_MSG_TIMEOUT, // 消息请求超时    
}tUCloudRtcCallbackErrCode;    
```

<a name='ErrCode-hanshu'></a>

###  3.2  函数值错误码

```cpp
typedef enum _tUCloudRtcReturnErrCode {    
	UCLOUD_RTC_RETURN_ERR_CODE_OK = 0,  //成功    
	UCLOUD_RTC_RETURN_ERR_AUTO_PUB = 1000, //自动发布    
	UCLOUD_RTC_RETURN_ERR_AUTO_SUB, //自动订阅    
	UCLOUD_RTC_RETURN_ERR_NOT_INIT, //引擎没有初始化    
	UCLOUD_RTC_RETURN_ERR_IN_ROOM, //已经加入房间    
	UCLOUD_RTC_RETURN_ERR_NOT_IN_ROOM, // 未加入房间    
	UCLOUD_RTC_RETURN_ERR_NOT_PUB_TRACK, //未发布对应媒体    
	UCLOUD_RTC_RETURN_ERR_INVAILED_PARGRAM, // 无效参数    
	UCLOUD_RTC_RETURN_ERR_INVAILED_WND_HANDLE, // 无效窗口句柄    
	UCLOUD_RTC_RETURN_ERR_INVAILED_MEDIA_TYPE, // 无效媒体类型    
	UCLOUD_RTC_RETURN_ERR_SUB_ONEMORE, // 最少订阅一种媒体    
	UCLOUD_RTC_RETURN_ERR_NO_PUB_ROLE, //无发布权限    
	UCLOUD_RTC_RETURN_ERR_NO_SUB_ROLE, //无订阅权限    
	UCLOUD_RTC_RETURN_ERR_CAM_NOT_ENABLE, //没有配置本地cam 发送    
	UCLOUD_RTC_RETURN_ERR_SCREEN_NOT_ENABLE, //没有配置本地screen 发送    
	UCLOUD_RTC_RETURN_ERR_AUDIO_MODE,        // 纯音频模式    
	UCLOUD_RTC_RETURN_ERR_SECKEY_INVALID ,    // seckey 无效    
	UCLOUD_RTC_RETURN_ERR_INVAILD_FILEPATH,    
	UCLOUD_RTC_RETURN_ERR_NOT_SUPORT_AUDIO_FORMAT,    
}tUCloudRtcReturnErrCode;    
```

<a name='struct'></a>

## 四、 函数结构体说明

<a name='struct-tUCloudRtcDeviceInfo'></a>

###  4.1  设备信息类

```cpp
typedef struct {    
	char mDeviceName[MAX_DEVICE_ID_LENGTH]; // 设备名称    
	char mDeviceId[MAX_DEVICE_ID_LENGTH];   // 设备id    
} tUCloudRtcDeviceInfo;    
```

<a name='struct-tUCloudRtcMediaConfig'></a>

###  4.2  媒体发布配置类

最少启用一种媒体
    
```cpp
typedef struct {    
	bool mVideoEnable; // 启用视频    
	bool mAudioEnable; // 启用音频    
}tUCloudRtcMediaConfig;    
```

<a name='struct-eUCloudRtcTrackType'></a>

###  4.3  媒体轨道类型类型描述

```cpp
typedef enum {    
	UCLOUD_RTC_TRACKTYPE_AUDIO = 1, // 音频轨道    
	UCLOUD_RTC_TRACKTYPE_VIDEO   // 视频轨道    
} eUCloudRtcTrackType;    
```
<a name='struct-eUCloudRtcMeidaType'></a>

###  4.4  媒体流类型描述

```cpp
typedef enum {    
   	UCLOUD_RTC_MEDIATYPE_NONE = 0, // 无效类型    
	UCLOUD_RTC_MEDIATYPE_VIDEO, // 摄像头    
	UCLOUD_RTC_MEDIATYPE_SCREEN  // 桌面流    
} eUCloudRtcMeidaType;    
```

<a name='struct-tUCloudRtcStreamInfo'></a>

###  4.5  流信息结构体

```cpp
typedef struct {    
	const char* mUserId;  // 用户id    
const char* mStreamId; // 流id    
	bool mEnableVideo;    //启用视频    
	bool mEnableAudio;    // 启用音频    
	bool mEnableData;     // 启用数据通道（暂时无效）    
	eUCloudRtcMeidaType mStreamMtype;// 流类型        
} tUCloudRtcStreamInfo;    
```

<a name='struct-eUCloudRtcWaterMarkPos'></a>


###  4.6  录制水印位置

```cpp
typedef enum {    
    UCLOUD_RTC_WATERMARKPOS_LEFTTOP = 1, //左上    
UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM， // 左下    
UCLOUD_RTC_WATERMARKPOS_RIGHTTOP， // 右上    
UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM， // 右下    
} eUCloudRtcWaterMarkPos;    
```

<a name='struct-eUCloudRtcWaterMarkType'></a>

###  4.7  水印类型

```cpp
typedef enum {    
	UCLOUD_RTC_WATERMARK_TYPE_TIME = 1, // 时间水印    
	UCLOUD_RTC_WATERMARK_TYPE_PIC, // 图片水印    
	UCLOUD_RTC_WATERMARK_TYPE_TEXT, // 文字水印    
} eUCloudRtcWaterMarkType;    
```

<a name='struct-tUCloudRtcMuteSt'></a>

###  4.8  Mute操作结构体

```cpp
typedef struct {        
	const char* mUserId; // 用户id    
    const char* mStreamId; // 流id    
	bool mMute;  //true 关闭媒体  false 打开媒体    
	eUCloudRtcMeidaType mStreamMtype; // 媒体流类型    
} tUCloudRtcMuteSt;    
```

<a name='struct-eUCloudRtcRecordProfile'></a>

###  4.9  录制输出等级

```cpp
typedef enum {
    UCLOUD_RTC_RECORDPROFILE_SD = 1, //标清 640*360
	UCLOUD_RTC_RECORDPROFILE_HD,    // 高清  1280*720
	UCLOUD_RTC_RECORDPROFILE_HDPLUS, //超清 1920*1080
} eUCloudRtcRecordProfile;
```

<a name='struct-eUCloudRtcRecordType'></a>

###  4.10  录制媒体类型

```cpp
typedef enum {
    UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1,  //直录音频（混音）
    UCLOUD_RTC_RECORDTYPE_AUDIOVIDEO     // 录制混音混流
} eUCloudRtcRecordType;
```

<a name='struct-tUCloudRtcRecordConfig'></a>

###  4.11  录制配置信息

```cpp
typedef struct {
	const char* mMainviewuid;    // 录制视频时大屏用户
    const char* mBucket;       //ufile 的存储名称
	const char* mBucketRegion;    //存储所在的地域目前仅支持存储在北京
	eUCloudRtcRecordProfile mProfile; // 输出等级
	eUCloudRtcRecordType mRecordType;  // 录制媒体类型
	eUCloudRtcWaterMarkPos mWatermarkPos; // 水印位置
	eUCloudRtcMeidaType mMainviewmediatype; // 主媒体类型
    eUCloudRtcWaterMarkType mWaterMarkType; // 水印类型
	const char* mWatermarkUrl;  // 当图片水印位水印url  当时文字水印为文字内容
	bool mIsaverage;  // 画面是否均分，不均为1大几小
	int mMixerTemplateType; //混流风格 (1 -- 9 )
} tUCloudRtcRecordConfig;
```

<a name='struct-eUCloudRtcRenderMode'></a>

###  4.12  渲染模式

```cpp
typedef enum {
    UCLOUD_RTC_RENDER_MODE_DEFAULT = 0, //默认平铺
    UCLOUD_RTC_RENDER_MODE_FIT, //保持比例
    UCLOUD_RTC_RENDER_MODE_FILL   //平铺
} eUCloudRtcRenderMode;
```

<a name='struct-eUCloudRtcLogLevel'></a>

###  4.13  日志级别

```cpp
typedef enum {
	UCLOUD_RTC_LOG_LEVEL_DEBUG,
	UCLOUD_RTC_LOG_LEVEL_INFO,
	UCLOUD_RTC_LOG_LEVEL_WARN,
	UCLOUD_RTC_LOG_LEVEL_ERROR,
	UCLOUD_RTC_LOG_LEVEL_NONE,
} eUCloudRtcLogLevel;
```

<a name='struct-eUCloudRtcVideoProfile'></a>

###  4.14  视频质量参数

```cpp
typedef enum {
    UCLOUD_RTC_VIDEO_PROFILE_NONE = -1,
	UCLOUD_RTC_VIDEO_PROFILE_320_180 = 1,
	UCLOUD_RTC_VIDEO_PROFILE_320_240 = 2,
	UCLOUD_RTC_VIDEO_PROFILE_640_360 = 3,
	UCLOUD_RTC_VIDEO_PROFILE_640_480 = 4,
	UCLOUD_RTC_VIDEO_PROFILE_1280_720 = 5,
	UCLOUD_RTC_VIDEO_PROFILE_1920_1080 = 6，
    UCLOUD_RTC_VIDEO_PROFILE_1920_1080_PLUS = 7// 1920*2*1080
} eUCloudRtcVideoProfile;
```

<a name='struct-eUCloudRtcScreenProfile'></a>

###  4.15  桌面输出参数

```cpp
typedef enum {
    UCLOUD_RTC_SCREEN_PROFILE_LOW = 1, //640*360
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE, //960*540
	UCLOUD_RTC_SCREEN_PROFILE_HIGH，// 1280*720
    UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS  // 1920*1080
} eUCloudRtcScreenProfile;
```

<a name='struct-tUCloudRtcScreenPargram'></a>

###  4.16  桌面采集参数

```cpp
typedef struct
{
	long mScreenId; // 窗或者桌面id标识
	int  mXpos; // 起始x坐标
	int mYpos; // 起始y坐标
	int mWidth;// 采集宽度
	int mHeight; // 采集高度
} tUCloudRtcScreenPargram;
```

<a name='struct-eUCloudRtcDesktopType'></a>

###  4.17  桌面采集类型

```cpp
typedef enum {
	UCLOUD_RTC_DESKTOPTYPE_SCREEN = 1, 采集桌面
	UCLOUD_RTC_DESKTOPTYPE_WINDOW 采集窗口
} eUCloudRtcDesktopType;
```

<a name='struct-tUCloudRtcDeskTopInfo'></a>

###  4.18  桌面参数

```cpp
typedef struct
{
	eUCloudRtcDesktopType mType;  桌面类型
	int mDesktopId;  id 标识
	char mDesktopTitle[MAX_WINDOWS_TILE_LEN]; //桌面标题
} tUCloudRtcDeskTopInfo;
```

<a name='struct-eUCloudRtcUserStreamRoleCHANNEL'></a>

###  4.19  通道类型

```cpp
typedef enum {
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION,   // 实时互动模式,
    UCLOUD_RTC_CHANNEL_TYPE_BROADCAST      // 直播模式
} eUCloudRtcUserStreamRole;
```

<a name='struct-eUCloudRtcUserStreamRoleSTREAM'></a>

###  4.20  流权限

```cpp
typedef enum {
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, // 上行推流
	UCLOUD_RTC_USER_STREAM_ROLE_SUB, // 下行拉流
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH //双向推拉流
} eUCloudRtcUserStreamRole;
```

<a name='struct-tUCloudRtcVideoCanvas'></a>

###  4.21  渲染窗口

```cpp
typedef struct 
{
    void* mVideoView;   // 渲染的窗口句柄
    const char* mUserId; // 用户id
    const char* mStreamId; //流id
	eUCloudRtcMeidaType mStreamMtype; // 媒体流类型
    eUCloudRtcRenderMode mRenderMode;  // 渲染模式
    eUCloudRtcRenderType mRenderType; // 自定义渲染 mVideoView 指定为自己的render 扩展类
} tUCloudRtcVideoCanvas;
```

<a name='struct-tUCloudRtcAuth'></a>

###  4.22  登录信息类

```cpp
typedef struct 
{
    const char* mAppId; // 平台分配的appid
	const char* mRoomId; // room 标识
	const char* mUserId; // 用户标识
	const char* mUserToken; // 用户通过用户服务器获取的token
} tUCloudRtcAuth;
```

<a name='struct-tUCloudRtcStreamStats'></a>

###  4.23  当前媒体状态统计

```cpp
typedef struct {
	const char* mUserId; // 用户id
    const char* mStreamId; //流id
	int mStreamMtype;// 媒体流类型 摄像头 桌面
	int mTracktype; // 媒体轨道类型 1 audio 2 video
	int mAudioBitrate = 0;     // audio bitrate,unit:bps
	int mVideoBitrate = 0;
	int mVideoWidth = 0;     // video width
	int mVideoHeight = 0;     // video height
	int mVideoFrameRate = 0;     // video frames per secon
	float mPacketLostRate = 0.0f;
} tUCloudRtcStreamStats;
```

<a name='struct-tUCloudRtcRecordInfo'></a>

###  4.24  录制信息回调

```cpp
typedef struct {
	const char* mRecordId;
	const char* mFileName;
	const char* mRegion;
	const char* mBucket;
	const char* mRoomid;
} tUCloudRtcRecordInfo;
```

<a name='struct-tUCloudRtcAudioFrame'></a>

###  4.25  音频帧

```cpp
typedef struct {
	const char* mUserId;
	const char* mStreamId;
	void* mAudioData; // 内存
	int mBytePerSimple; // 采样位数16bit
	int mSimpleRate;  // 采样频率
	int mChannels;    // 声道数
	int mNumSimples;  //采集样本数
} tUCloudRtcAudioFrame;
```

<a name='struct-eUCloudRtcVideoFrameType'></a>

###  4.26  视频数据帧类型

```cpp
typedef enum {
	UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 = 1,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGB24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGBA,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_ARGB,
} eUCloudRtcVideoFrameType;
```

<a name='struct-tUCloudRtcVideoFrame'></a>

###  4.27  视频数据帧

```cpp
typedef struct {
	unsigned char* mDataBuf;
	int mWidth;
	int mHeight;
	eUCloudRtcVideoFrameType mVideoType;
} tUCloudRtcVideoFrame;
```

<a name='struct-UCloudRtcEventListener'></a>

###  4.28  消息回调事件接口类

下面所有code 为0 代表成功，其他代表失败。

```cpp
class  UCloudRtcEventListener
{
public：
// 服务器断开
virtual void onServerDisconnect() {}
// 加入房间通知
virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) {}
// 离开房间通知
virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}
//房间重连中
virtual void onRejoining(const char* uid, const char* roomid) {}
// 房间重连成功
virtual void onReJoinRoom(const char* uid, const char* roomid) {}
// 本地流发布结果回调
virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo & info) {}
// 本地流取消发布结果回调
virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo & info) {}
// 远端有用户加入房间
virtual void onRemoteUserJoin(const char* uid) {}
// 远端有用户离开房间
virtual void onRemoteUserLeave(const char* uid,int reson) {}
// 远端用户发布视频
virtual void onRemotePublish(tUCloudRtcStreamInfo & info) {}
// 远端用户取消发布视频
virtual void onRemoteUnPublish(tUCloudRtcStreamInfo & info) {}
// 订阅某条视频流回调
virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo & info) {}
// 取消订阅某条视频流回调
virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo & info) {}
// 操作本地媒体流结果回调
virtual void onLocalStreamMuteRsp(const int code, const char* msg,	eUCloudRtcMeidaType mediatype, UCloudTracktype tracktype, bool mute) {}
// 操作远端媒体流结果回调
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid, eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
// 远端媒体流状态回调
	virtual void onRemoteTrackNotify(const char* uid, eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
//发送状态信息
	virtual void onSendRTCStats(tUCloudRtcStreamStats & rtstats) {}
//接收状态信息
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats) {}
//开启录制回调
virtual void onStartRecord (const int code, const char* msg, tUCloudRtcRecordInfo& info) {}
// 结束录制回调
virtual void onStopRecord (const int code, const char* msg, const char* recordid) {}
// 麦克风能量回调
	virtual void onMiceAudioLevel(int volume) {} 
// 远端能量回调
	virtual void onRemoteAudioLevel(const char* uid, int volume) {}
// 踢下线
virtual void onKickoff(int code) {}
// 警告
virtual void onWarning(int warn) {}
// 错误
    virtual void onError(int error) {}
};
```

<a name='struct-UCloudRtcMediaListener'></a>

###  4.29  音频测试回调

```cpp
class  UCloudRtcMediaListener
{
public:
	// 音频能量回调   （0--255）
    virtual void onMiceAudioLevel(int volume) {} 
};
```

<a name='struct-UCloudRtcAudioFrameCallback'></a>

###  4.30  音频数据回调

```cpp
class  UCloudRtcAudioFrameCallback
{
public:
	//本地音频回调
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
   // 远端混音数据
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {} 
};
```

<a name='struct-UCloudRtcExtendVideoCaptureSource'></a>

###  4.31  视频扩展数据源

用户可以扩展自己的视频输入 音频通过doCaptureFrame 采集数据。

```cpp
class  UCloudRtcExtendVideoCaptureSource
{
public:
	virtual  bool doCaptureFrame(tUCloudRtcVideoFrame* videoframe) = 0; 
};
```

<a name='struct-UCloudRtcExtendVideoRender'></a>

###  4.32  视频数据回调

用户结合渲染 可以获取数据进行自己渲染。

```cpp
class _EXPORT_API UCloudRtcExtendVideoRender
{
public:
	virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe) = 0;
};
```

<a name='struct-UCloudRtcVideoFrameObserver'></a>

###  4.33  视频数据回调监听类（yuv420p格式）

引擎内存回调camera 采集数据 和 扩展数据源使用方便做视频前置处理。

```cpp
class  UCloudRtcVideoFrameObserver
{
public:
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};
```

<a name='struct-eUCloudRtcRenderType'></a>

###  4.34  视频渲染类型

```cpp
typedef enum {
    UCLOUD_RTC_RENDER_TYPE_GDI = 1,
	UCLOUD_RTC_RENDER_TYPE_D3D = 2，
    UCLOUD_RTC_RENDER_TYPE_EXTEND = 3
} eUCloudRtcRenderType;
```

<a name='struct-eUCloudRtcVideoCodec'></a>

###  4.35  视频编码类型

```cpp
typedef enum {
	UCLOUD_RTC_CODEC_VP8 = 1, //default
	UCLOUD_RTC_CODEC_H264
} eUCloudRtcVideoCodec;
```

<a name='struct-tUCloudVideoConfig'></a>

###  4.36  视频参数

```cpp
typedef struct {
	int mWidth; // 宽
	int mHeight; // 高
	int mFrameRate; // 帧率
} tUCloudVideoConfig;
```
