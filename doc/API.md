# UCloudRTC win SDK API 手册

* [UcloudRtcEngine引擎接口 类](#class)
    * [1.1  获取引擎 - UCloudRtcEngine](#class-UCloudRtcEngine)
    * [1.2  绑定监听事件 - regRtcEventListener ](#class-regRtcEventListener)
    * [1.3  设置SDK模式 - setSdkMode](#class-setSdkMode)
    * [1.4  设置通话模式 - setChannelType](#class-setChannelType)	
    * [1.5  设置流操作权限 - setStreamRole](#class-setStreamRole)
    * [1.6  设置纯音频模式 - setAudioOnlyMode](#class-setAudioOnlyMode)	
    * [1.7  设置自动发布和订阅 - setAutoPublishSubscribe](#class-setAutoPublishSubscribe)
    * [1.8  配置本地音频是否发布 - configLocalAudioPublish](#class-configLocalAudioPublish)
    * [1.9  是否发布音频 - isLocalAudioPublishEnabled](#class-isLocalAudioPublishEnabled)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
    * [ - ](#class-)
	



    * [1.7  设置日志等级 - setLogLevel](#class-setLogLevel)	
    * [1.4  获取SDK 版本 - getSdkVersion](#class-getSdkVersion)	
    * [1.2  销毁引擎 - destroy](#class-destroy)



	
<a name='class'></a>

## 一. class UcloudRtcEngine引擎接口类

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

###  1.4  设置流操作权限

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


<a name='class-'></a>

###  1.8  配置本地音频是否发布

virtual int configLocalAudioPublish(bool enable)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  enable[in]   | 是否可以发布本地音频     | bool | N |

**消息回调**

无


<a name='class-'></a>

###  1.9  是否发布音频

virtual bool isLocalAudioPublishEnabled()

**返回值**

true 发布音频;false 不发布音频。

**参数说明**    

无

**消息回调**

无


<a name='class-switchCamera'></a>

###  1.10  切换摄像头

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

###  1.11  设置RTSP视频源

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

###  1.12  设置自定义外部视频源

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

###  1.13  设置音频数据监听

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

###  1.14  添加micphone混音文件

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

###  1.15  停止micphone混音

virtual int stopAudioMixing()

**返回值**

详见错误码描述。

**参数说明**    

无

**消息回调**

无

<a name='class-joinChannel'></a>

###  1.16  加入房间

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

###  1.17  离开房间

virtual int leaveChannel()

**返回值**

详见错误码描述。

**参数说明**    

无

**消息回调**

code回调为0代表成功，其他代表失败。

具体参见 消息回调事件接口类对应接口virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}


<a name='class-startPreview'></a>

###  1.18  开启本地渲染

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

###  1.19  停止本地渲染

virtual int stopPreview (tUCloudRtcVideoCanvas& view)

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无


<a name='class-setVideoProfile'></a>

###  1.20  设置视频编码参数

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

<a name='class-setDesktopProfile'></a>

###  1.21  设置桌面编码参数

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

###  1.22  设置桌面采集参数

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

###  1.23  设置桌面采集类型

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

###  1.24  获取屏幕个数

virtual void getDesktopNums ()

**返回值**

屏幕个数。

**参数说明**    

无

**消息回调**

无

<a name='class-getDesktopInfo'></a>

###  1.25  获取屏幕信息

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

###  1.26  获取窗口个数

virtual void getWindowNums ()

**返回值**

窗口个数。

**参数说明**    

无

**消息回调**

无

<a name='class-getWindowInfo'></a>

###  1.27  获取窗口信息

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

<a name='class-muteCamBeforeJoin'></a>

###  1.28  入会关闭摄像头

virtual int muteCamBeforeJoin(bool mute)

入会时关闭摄像头，发送黑屏帧。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | true，关闭摄像头。 <br> false，打开摄像头。     | bool | N |

**消息回调**

无

<a name='class-muteMicBeforeJoin'></a>

###  1.29  入会关闭麦克风

virtual int muteMicBeforeJoin (bool mute)

入会时关闭麦克风。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mute[in]   | true，关闭麦克风。 <br> false，打开麦克风。     | bool | N |

**消息回调**

无

<a name='class-enableAllAudioPlay'></a>

###  1.30  静音

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

<a name='class-publish'></a>

###  1.31  发布本地流

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

###  1.32  停止发布本地流

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


<a name='class-muteLocalMic'></a>

###  1.33  打开/关闭本地麦克风

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

###  1.34  打开/关闭本地视频

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

<a name='class-startRemoteView'></a>

###  1.35  开启远端渲染

virtual int startRemoteView (tUCloudRtcVideoCanvas & view)

开启远端渲染,在订阅成功后才能调用。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无

<a name='class-stopRemoteView'></a>

###  1.36  停止远端渲染

virtual int stopRemoteView (tUCloudRtcVideoCanvas & view)

停止远端渲染,在订阅成功后才能调用。

**返回值**

详见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  view[in]  | 包含UserId、StreamId、StreamMtype等。<br> 详见tUCloudRtcVideoCanvas参数说明。    | struct | N |

**消息回调**

无




<a name='class-setLogLevel'></a>

###  1.7  设置日志等级

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

### 1.4  获取SDK 版本

static const char *getSdkVersion()

**返回值**

SDK的版本号

**参数说明**    

无

**消息回调**

无

<a name='class-setSdkMode'></a>

<a name='class-destroy'></a>

### 1.2  销毁引擎

static void destroy()

**返回值**

无

**参数说明**    

无

**消息回调**

无

<a name='class-regRtcEventListener'></a>

