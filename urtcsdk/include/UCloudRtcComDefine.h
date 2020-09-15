#ifndef _UCLOUD_RTC_SDKENGINE_COMMONDEFINE_H_
#define _UCLOUD_RTC_SDKENGINE_COMMONDEFINE_H_

#ifdef _EXPORT
#define _EXPORT_API __declspec(dllexport)
#define _EXPORT_API_C extern "C" __declspec(dllexport)
#else
#define _EXPORT_API __declspec(dllimport)
#define _EXPORT_API_C  extern "C" __declspec(dllimport)
#endif

#define  C_API extern "C"
#define MAX_DEVICE_ID_LENGTH 128 
#define MAX_WINDOWS_TILE_LEN 256 

//接入方式设置
typedef enum
{
	UCLOUD_RTC_SERVER_GET_FROM_UTECH = 1,
	UCLOUD_RTC_SERVER_GET_FROM_USER_GATEWAY,
	UCLOUD_RTC_SERVER_GET_FROM_USER_DIRECT
}eUCloudServerGetFrom;

//设备信息
typedef struct {
	//设备名称
	char mDeviceName[MAX_DEVICE_ID_LENGTH];
	//设备ID
	char mDeviceId[MAX_DEVICE_ID_LENGTH];
}tUCloudRtcDeviceInfo;

//媒体配置
typedef struct {
	//使能video
	bool mVideoEnable;
	//使能audio
	bool mAudioEnable;
}tUCloudRtcMediaConfig;

//桌面配置
typedef struct
{
	//屏幕索引
	long mScreenindex;
	//x坐标
	int  mXpos;
	//y坐标
	int mYpos;
	//宽度
	int mWidth;
	//长度
	int mHeight;
}tUCloudRtcScreenPargram;

//桌面类型
typedef enum {
	//屏幕
	UCLOUD_RTC_DESKTOPTYPE_SCREEN = 1,
	//窗口
	UCLOUD_RTC_DESKTOPTYPE_WINDOW
}eUCloudRtcDesktopType;

//桌面窗口信息
typedef struct
{
	//桌面类型
	eUCloudRtcDesktopType mType;
	//桌面id
	int mDesktopId;
	int mScreenW;
	int mScreenH;
	//标题
	char mDesktopTitle[MAX_WINDOWS_TILE_LEN];
}tUCloudRtcDeskTopInfo;

//轨道类型
typedef enum {
	UCLOUD_RTC_TRACKTYPE_AUDIO = 1,
	UCLOUD_RTC_TRACKTYPE_VIDEO 
}eUCloudRtcTrackType;

//媒体类型
typedef enum {
	//无
	UCLOUD_RTC_MEDIATYPE_NONE = 0,
	//摄像头流(音轨和视频轨)
	UCLOUD_RTC_MEDIATYPE_VIDEO = 1,
	//桌面
	UCLOUD_RTC_MEDIATYPE_SCREEN = 2
}eUCloudRtcMeidaType;

//流信息
typedef struct {
	//用户ID
	const char* mUserId;
	//流ID
	const char* mStreamId;
	//使能VIDEO
	bool mEnableVideo;
	//使能AUDIO
	bool mEnableAudio;
	//使能Data
	bool mEnableData;
	//mute video状态
	bool mMuteVideo;
	//mute audio状态
	bool mMuteAudio;
	//媒体类型
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcStreamInfo;

//mute 状态
typedef struct {
	//用户ID
	const char* mUserId;
	//流ID
	const char* mStreamId;
	//是否mute
	bool mMute;
	//媒体类型
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcMuteSt;

//录制的profile
typedef enum {
	UCLOUD_RTC_RECORDPROFILE_SD = 1, 
	UCLOUD_RTC_RECORDPROFILE_HD, 
	UCLOUD_RTC_RECORDPROFILE_HDPLUS, 
}eUCloudRtcRecordProfile;

//录制类型
typedef enum {
	//纯音频模式
	UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1, 
	//音视频模式
	UCLOUD_RTC_RECORDTYPE_AUDIOVIDEO
}eUCloudRtcRecordType;

//水印位置
typedef enum {
	UCLOUD_RTC_WATERMARKPOS_LEFTTOP = 1,
	UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM,
	UCLOUD_RTC_WATERMARKPOS_RIGHTTOP,
	UCLOUD_RTC_WATERMARKPOS_RIGHTBOTTOM
}eUCloudRtcWaterMarkPos;

//水印类型
typedef enum {
	//默认无
	UCLOUD_RTC_WATERMARK_TYPE_NONE = 0,
	//时间水印
	UCLOUD_RTC_WATERMARK_TYPE_TIME = 1,
	//图片水印
	UCLOUD_RTC_WATERMARK_TYPE_PIC,
	//文字水印
	UCLOUD_RTC_WATERMARK_TYPE_TEXT,
}eUCloudRtcWaterMarkType;

//转推模式
typedef enum {
	//自动
	UCLOUD_RTC_AUTO = 1,
	//手动
	UCLOUD_RTC_MANAUL = 2,
}eUCloudRtcRelayMode;

//渲染缩放类型
typedef enum {
	//default full
	UCLOUD_RTC_RENDER_MODE_DEFAULT = 0,
	//fit 模式
	UCLOUD_RTC_RENDER_MODE_FIT = 1,
	//fill模式
	UCLOUD_RTC_RENDER_MODE_FILL = 2 
} eUCloudRtcRenderMode;

//渲染类型
typedef enum {
	//GDI
	UCLOUD_RTC_RENDER_TYPE_GDI = 1,
	//D3D
	UCLOUD_RTC_RENDER_TYPE_D3D = 2,
	//外部渲染
	UCLOUD_RTC_RENDER_TYPE_EXTEND = 3,
} eUCloudRtcRenderType;

//日志级别
typedef enum {
	UCLOUD_RTC_LOG_LEVEL_DEBUG,
	UCLOUD_RTC_LOG_LEVEL_INFO,
	UCLOUD_RTC_LOG_LEVEL_WARN,
	UCLOUD_RTC_LOG_LEVEL_ERROR,
	UCLOUD_RTC_LOG_LEVEL_NONE,
} eUCloudRtcLogLevel;

//视频profile
typedef enum {
	UCLOUD_RTC_VIDEO_PROFILE_NONE = -1, 
	UCLOUD_RTC_VIDEO_PROFILE_320_180 = 1,
	UCLOUD_RTC_VIDEO_PROFILE_320_240 = 2,
	UCLOUD_RTC_VIDEO_PROFILE_640_360 = 3,
	UCLOUD_RTC_VIDEO_PROFILE_640_480 = 4,
	UCLOUD_RTC_VIDEO_PROFILE_1280_720 = 5,
	UCLOUD_RTC_VIDEO_PROFILE_1920_1080 = 6,
	UCLOUD_RTC_VIDEO_PROFILE_240_180 = 7,
	UCLOUD_RTC_VIDEO_PROFILE_480_360 = 8,
	UCLOUD_RTC_VIDEO_PROFILE_960_720 = 9
} eUCloudRtcVideoProfile;

//桌面profile
typedef enum {
	UCLOUD_RTC_SCREEN_PROFILE_LOW = 1,
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE = 2,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH = 3,

	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS = 4,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_1 = 5,     //最大2m码率 25帧
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS_1 = 6, //最大2.5m码率 25帧
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_0 = 7,     //最大1.6m码率 15帧
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS_0 = 8 //最大2m码率 18帧
} eUCloudRtcScreenProfile;

//应用类型
typedef enum {
	//视频会议模式
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION,
	//直播模式
	UCLOUD_RTC_CHANNEL_TYPE_BROADCAST
}eUCloudRtcChannelType;

//权限设置
typedef enum {
	// 推流权限
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, 
	// 拉流权限
	UCLOUD_RTC_USER_STREAM_ROLE_SUB,
	// 推拉流
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH 
} eUCloudRtcUserStreamRole;

//SDK 模式
typedef enum {
	//正式模式 token有appserver生成
	UCLOUD_RTC_SDK_MODE_NORMAL, 
	//测试模式 sdk内部生成 需设置appkey
	UCLOUD_RTC_SDK_MODE_TRIVAL, 
} eUCloudRtcSdkMode;

//视频编码类型
typedef enum {
	UCLOUD_RTC_CODEC_VP8 = 1, 
	UCLOUD_RTC_CODEC_H264 
} eUCloudRtcVideoCodec;

//音频编码类型
typedef enum {
	UCLOUD_RTC_CODEC_OPUS = 1, //default
} eUCloudRtcAudioCodec;

//FRAME 类型
typedef enum {
	UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 = 1,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGB24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_BGR24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGBA,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_ARGB,
}eUCloudRtcVideoFrameType;

//网络上下型类型
typedef enum {
	//上行
	UCLOUD_RTC_NETWORK_TX = 1, 
	//下行
	UCLOUD_RTC_NETWORK_RX = 2,  
}eUCloudRtcNetworkQuality;

//网络评分
typedef enum {
	//未知
	UCLOUD_RTC_QUALITY_UNKNOWN = 0, 
	//很坏
	UCLOUD_RTC_QUALITY_DOWN = 5,  
	//勉强能沟通但不顺畅
	UCLOUD_RTC_QUALITY_BAD = 4,  
	//用户主观感受有瑕疵但不影响沟通
	UCLOUD_RTC_QUALITY_POOR =  3, 
	// 用户主观感觉和 excellent 差不多
	UCLOUD_RTC_QUALITY_GOOD = 2, 
	//网络质量极好
	UCLOUD_RTC_QUALITY_EXCELLENT = 1, 
}eUCloudRtcQualityType;

//rtmp状态
typedef enum {
	//推流未开始或停止
	RTMP_STREAM_PUBLISH_STATE_IDLE ,   
	//正在推流
	RTMP_STREAM_PUBLISH_STATE_RUNNING, 
	//推流失败 详见code
	RTMP_STREAM_PUBLISH_STATE_FAILURE ,
	//停止推流失败 详见code
	RTMP_STREAM_PUBLISH_STATE_STOPFAILURE, 
	//异常停止推流(无流超时停止)
	RTMP_STREAM_PUBLISH_STATE_EXCEPTIONSTOP, 
	//更新布局结果
	RTMP_STREAM_PUBLISH_STATE_UPDATECONFIGRES,  //code 为0时更新succ
}eUCloudRtmpState;

// 渲染视图
typedef struct
{
	//窗口视图
	void* mVideoView;
	//用户id
	const char* mUserId;
	//流ID
	const char* mStreamId;
	//流类型
	eUCloudRtcMeidaType mStreamMtype;
	//渲染缩放模式
	eUCloudRtcRenderMode mRenderMode;
	//渲染类型
	eUCloudRtcRenderType mRenderType;
	//when extend render this decide callback frametype
	eUCloudRtcVideoFrameType mVideoFrameType;
}tUCloudRtcVideoCanvas;

//鉴权信息
typedef struct
{
	const char* mAppId = nullptr;
	const char* mRoomId = nullptr;
	const char* mUserId = nullptr;
	const char* mUserToken = nullptr;
	const char* mServerUrl = nullptr;
}tUCloudRtcAuth;

//流信息
typedef struct {
	//用户id
	const char* mUserId;
	//流id
	const char* mStreamId;
	//流类型
	int mStreamMtype;
	//track类型 1 audio 2 video
	int mTracktype; 
	// audio bitrate,unit:bps
	int mAudioBitrate = 0;  
	// video bitrate 
	int mVideoBitrate = 0;
	// video width
	int mVideoWidth = 0;   
	// video height
	int mVideoHeight = 0;     
	// video frames per secon
	int mVideoFrameRate = 0;     
	//丢包率
	float mPacketLostRate = 0.0f;
}tUCloudRtcStreamStats;

//录制信息
typedef struct {
	//录制ID
	const char* mRecordId;
	//录制文件名
	const char* mFileName;
	//region
	const char* mRegion;
	//bucket
	const char* mBucket;
	//房间id
	const char* mRoomid;
}tUCloudRtcRecordInfo;

//音频帧信息
typedef struct {
	//用户id
	const char* mUserId;
	//流ID
	const char* mStreamId;
	//audio 数据
	void* mAudioData;
	int mBytePerSimple;
	//采用率
	int mSimpleRate;
	//声道数
	int mChannels;
	int mNumSimples;
	long long renderTimeMs;
}tUCloudRtcAudioFrame;

//视频帧信息
typedef struct {
	//视频数据
	unsigned char* mDataBuf;
	int mWidth;
	int mHeight;
	//frametype
	eUCloudRtcVideoFrameType mVideoType;
	long long renderTimeMs;
}tUCloudRtcVideoFrame;

//视频信息配置
typedef struct {
	int mWidth;
	int mHeight;
	//帧率
	int mFrameRate;
}tUCloudVideoConfig;

//合流背景色配置
typedef struct  {
	int mRed;
	int mGreen;
	int mBlue;
}tUCloudBackgroundColor;

//视频编码质量
typedef enum {
	UCLOUD_QUALITY_CB = 0, //CB
	UCLOUD_QUALITY_B,
	UCLOUD_QUALITY_M,
	UCLOUD_QUALITY_E,
	UCLOUD_QUALITY_H
}eUCloudRtcQualityLevel;

//转推混流操作类型
typedef enum {
	RTMP_STREAM_ADD,	 //添加
	RTMP_STREAM_REMOVE,  //删除
}eUCloudRtmpOpration;

//转推的流
typedef struct UCloudRtcRelayStream {
	const char* mUid;
	eUCloudRtcMeidaType mType;
	UCloudRtcRelayStream() {
		mUid = nullptr;
		mType = UCLOUD_RTC_MEDIATYPE_NONE;
	}
}tUCloudRtcRelayStream;

//转推混流操作类型
typedef enum {
	MIX_LAYOUT_OLD,       //兼容之前模板
	MIX_LAYOUT_FLOW,	  //流式布局
	MIX_LAYOUT_TEACH,	  //讲课布局
	MIX_LAYOUT_CUSTOM,    //自定义
	MIX_LAYOUT_ADAPTION1, //主讲模式
	MIX_LAYOUT_ADAPTION2, //多人模式
	MIX_LAYOUT_ADAPTION3, //单人模式
}eUCloudMixLayout;

typedef int UcloudRtcLayoutLsit[3];
//转推配置
typedef struct UCloudRtcTranscodeConfig {
	//背景色
	tUCloudBackgroundColor mbgColor; 
	//帧率
	int mFramerate;
	//码率
	int mBitrate;   
	//主讲人的uid
	const char*  mMainViewUid; 
	//主讲人放置的媒体类型
	int mMainviewType; 
	//输出分辨率宽度
	int mWidth; 
	//输出分辨率高度
	int mHeight; 
	//布局列表
	UcloudRtcLayoutLsit mlayouts;
	//当前使用得布局 1.流式布局 2.讲课模式 3.自定义布局 4.模板自适应1 5.模板自适应2 6.单人模式
	eUCloudMixLayout mLayout;
	//mLayout=3 时自定义风格内容
	const char*  mStyle; 
	//混流的用户
	tUCloudRtcRelayStream *mStreams; 
	//混流用户数
	int mStreamslength;
	//水印位置
	eUCloudRtcWaterMarkPos mWatermarkPos;
	//水印类型
	eUCloudRtcWaterMarkType mWaterMarkType;
	//水印url  为图片水印时
	const char* mWatermarkUrl;
	//是否纯音频
	bool mIsAudio;
	//模式
	eUCloudRtcRelayMode mMode;
	//控制人(若此人无流状态超过1分钟 转推自动停止)
	const char*  mKeyUid;
	UCloudRtcTranscodeConfig()
	{
		mlayouts[0] = MIX_LAYOUT_ADAPTION1;
		mlayouts[1] = MIX_LAYOUT_ADAPTION2;
		mlayouts[2] = MIX_LAYOUT_ADAPTION3;
		mMode = UCLOUD_RTC_AUTO;
		mIsAudio = false;
		mLayout = MIX_LAYOUT_TEACH;
		mKeyUid = nullptr;
		mMainViewUid = nullptr;
		mStreams = nullptr;
		mStyle = nullptr;
		mStreamslength = 0;
		mWatermarkUrl = nullptr;
		mWaterMarkType = UCLOUD_RTC_WATERMARK_TYPE_NONE;
	}
}tUCloudRtcTranscodeConfig;

//录制信息
typedef struct UCloudRtcRecordConfig {
	//录制的主流用户id
	const char* mMainviewuid;   
	//存储bucket
	const char* mBucket;    
	//存储region
	const char* mBucketRegion;  
	//录制profile
	eUCloudRtcRecordProfile mProfile;  
	//录制类型
	eUCloudRtcRecordType mRecordType;
	//水印位置
	eUCloudRtcWaterMarkPos mWatermarkPos;
	//主流的媒体类型
	eUCloudRtcMeidaType mMainviewmediatype; 
	//水印类型
	eUCloudRtcWaterMarkType mWaterMarkType;  
	//水印url  为图片水印时
	const char* mWatermarkUrl;	
	//是否均分 (true .流式布局，false:讲课模式)
	bool mIsaverage;		
	//模板类型
	int mMixerTemplateType;			

	//混流的用户
	tUCloudRtcRelayStream *mStreams;
	//混流的用户长度
	int mStreamslength; 
	// 0.取决于mIsaverage 1.流式布局 2.讲课模式 3.自定义布局 4.模板自适应1 5.模板自适应2
	int mLayout; 
	UCloudRtcRecordConfig() {
		mWatermarkUrl = nullptr;
		mMainviewuid = nullptr;
		mBucket = nullptr;
		mBucketRegion = nullptr;
		mStreams = nullptr;
		mLayout = MIX_LAYOUT_OLD;
	}
}tUCloudRtcRecordConfig;

typedef enum {
	DEVICE_VIDEO,      //视频设备
	DEVICE_AUDIO,	 //音频设备
}eUCloudDeviceType;

typedef struct 
{
	bool mIsInline;
	const char* mLogPath;
	const char* mLogName;
	eUCloudRtcLogLevel mLogLevel;
	int mMaxReconnect;
}tUCloudRtcInitContext;

//设备插拔回调
class _EXPORT_API UcloudRtcDeviceChanged
{
public:
	///发现设备
	///@param dtype 设备类型
	///@param dccname 名称
	///@param len 长度
	virtual void onInterfaceArrival(eUCloudDeviceType dtype,const char* dccname, int len) {}

	///移除设备
	///@param dtype 设备类型
	///@param dccname 名称
	///@param len 长度
	virtual void onInterfaceRemoved(eUCloudDeviceType dtype, const char* dccname, int len) {}

	///设备属性改变
	///@param dtype 设备类型
	///@param dccname 设备名称
	///@param len 长度
	virtual void onInterfaceChangeValue(eUCloudDeviceType dtype, const char* dccname, int len) {}
	virtual ~UcloudRtcDeviceChanged() {}
};

//音频监听回调
class  _EXPORT_API UCloudRtcAudioFrameCallback
{
public:
	///本地音频源数据callback
	///@param audioframe 音频数据
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	///远端音频源数据callback
	///@param audioframe 音频数据
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	///本地和远端音频源数据callback
	///@param audioframe 音频数据
	virtual void onLoaclRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
};

//外部音频源(已废弃 采用UCloudIAudioFrameObserver )
class  _EXPORT_API UCloudRtcExtendAudioCaptureSource
{
public:
	virtual ~UCloudRtcExtendAudioCaptureSource() {}
	///音频源数据 内部会自动调用此接口
	///@param audioframe 音频数据
	virtual  bool doCaptureAudioFrame(tUCloudRtcAudioFrame* audioframe) = 0;
};

//外部视频源（已废弃 采用UCloudIVideoFrameObserver）
class  _EXPORT_API UCloudRtcExtendVideoCaptureSource
{
public:
	///视频源数据 内部会自动调用此接口
	///@param videoframe 视频帧
	virtual  bool doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe) = 0;
};

//视频设备startcapture监听回调
class _EXPORT_API UCloudRtcVideoFrameObserver 
{
public:
	///视频采集数据回调
	///@param videoframe 视频数据
	///@param buflen 长度
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};

//外部渲染
class _EXPORT_API UCloudRtcExtendVideoRender
{
public:
	///外部渲染
	///@param videoframe 吐出的视频帧
	virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe) = 0;
};



//视频监听回调
class _EXPORT_API UCloudIVideoFrameObserver
{
public:
	///视频采集到每一帧得回调
	///@param videoframe 视频数据
	virtual  bool onCaptureFrame(tUCloudRtcVideoFrame *videoFrame) = 0;
	
};

//音频监听回调
class _EXPORT_API UCloudIAudioFrameObserver
{
public:
	///音频采集到每一帧得回调
	///@param  audioFrame 音频数据
	virtual  bool onCaptureFrame(tUCloudRtcAudioFrame* audioFrame) = 0;

};
#endif

