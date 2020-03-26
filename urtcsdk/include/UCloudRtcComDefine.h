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

//设备信息
typedef struct {
	char mDeviceName[MAX_DEVICE_ID_LENGTH];
	char mDeviceId[MAX_DEVICE_ID_LENGTH];
}tUCloudRtcDeviceInfo;

//媒体配置
typedef struct {
	bool mVideoEnable;
	bool mAudioEnable;
}tUCloudRtcMediaConfig;

//桌面配置
typedef struct
{
	long mScreenindex;
	int  mXpos;
	int mYpos;
	int mWidth;
	int mHeight;
}tUCloudRtcScreenPargram;

//桌面类型
typedef enum {
	UCLOUD_RTC_DESKTOPTYPE_SCREEN = 1,
	UCLOUD_RTC_DESKTOPTYPE_WINDOW
}eUCloudRtcDesktopType;

//桌面窗口信息
typedef struct
{
	eUCloudRtcDesktopType mType;
	int mDesktopId;
	char mDesktopTitle[MAX_WINDOWS_TILE_LEN];
}tUCloudRtcDeskTopInfo;

//轨道类型
typedef enum {
	UCLOUD_RTC_TRACKTYPE_AUDIO = 1,
	UCLOUD_RTC_TRACKTYPE_VIDEO 
}eUCloudRtcTrackType;

//媒体类型
typedef enum {
	UCLOUD_RTC_MEDIATYPE_NONE = 0,
	UCLOUD_RTC_MEDIATYPE_VIDEO = 1,
	UCLOUD_RTC_MEDIATYPE_SCREEN = 2
}eUCloudRtcMeidaType;

//流信息
typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mEnableVideo;
	bool mEnableAudio;
	bool mEnableData;
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcStreamInfo;

//mute 状态
typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mMute;
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
	UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1, 
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
	UCLOUD_RTC_WATERMARK_TYPE_NONE = 0,
	UCLOUD_RTC_WATERMARK_TYPE_TIME = 1,
	UCLOUD_RTC_WATERMARK_TYPE_PIC,
	UCLOUD_RTC_WATERMARK_TYPE_TEXT,
}eUCloudRtcWaterMarkType;

//渲染类型
typedef enum {
	UCLOUD_RTC_RENDER_MODE_DEFAULT = 0, //default full
	UCLOUD_RTC_RENDER_MODE_FIT = 1, 
	UCLOUD_RTC_RENDER_MODE_FILL = 2 
} eUCloudRtcRenderMode;

//渲染类型
typedef enum {
	UCLOUD_RTC_RENDER_TYPE_GDI = 1,
	UCLOUD_RTC_RENDER_TYPE_D3D = 2,
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
	UCLOUD_RTC_VIDEO_PROFILE_1920_1080 = 6
} eUCloudRtcVideoProfile;

//桌面profile
typedef enum {
	UCLOUD_RTC_SCREEN_PROFILE_LOW = 1,
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE = 2,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH = 3,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS = 4
} eUCloudRtcScreenProfile;

//应用类型
typedef enum {
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION,
	UCLOUD_RTC_CHANNEL_TYPE_BROADCAST
}eUCloudRtcChannelType;

//权限设置
typedef enum {
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, // up
	UCLOUD_RTC_USER_STREAM_ROLE_SUB,// down
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH //both
} eUCloudRtcUserStreamRole;

//SDK 模式
typedef enum {
	UCLOUD_RTC_SDK_MODE_NORMAL, 
	UCLOUD_RTC_SDK_MODE_TRIVAL, 
} eUCloudRtcSdkMode;

//视频编码类型
typedef enum {
	UCLOUD_RTC_CODEC_VP8 = 1, //default
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
	UCLOUD_RTC_NETWORK_TX = 1,  //上行
	UCLOUD_RTC_NETWORK_RX = 2,  //下行
}eUCloudRtcNetworkQuality;

//网络评分
typedef enum {
	UCLOUD_RTC_QUALITY_UNKNOWN = 0, //未知
	UCLOUD_RTC_QUALITY_DOWN = 1,  //很坏
	UCLOUD_RTC_QUALITY_BAD = 2,  //勉强能沟通但不顺畅
	UCLOUD_RTC_QUALITY_POOR =  3, //用户主观感受有瑕疵但不影响沟通
	UCLOUD_RTC_QUALITY_GOOD = 4, // 用户主观感觉和 excellent 差不多
	UCLOUD_RTC_QUALITY_EXCELLENT = 5, //网络质量极好
}eUCloudRtcQualityType;

//rtmp状态
typedef enum {
	RTMP_STREAM_PUBLISH_STATE_IDLE , //推流未开始或停止  
	RTMP_STREAM_PUBLISH_STATE_RUNNING,  //正在推流
	RTMP_STREAM_PUBLISH_STATE_FAILURE , //推流失败 详见code
	RTMP_STREAM_PUBLISH_STATE_STOPFAILURE, //停止推流失败 详见code
	RTMP_STREAM_PUBLISH_STATE_EXCEPTIONSTOP, //异常停止推流(无流超时停止)
}eUCloudRtmpState;

// 渲染类型
typedef struct
{
	void* mVideoView;
	const char* mUserId;
	const char* mStreamId;
	eUCloudRtcMeidaType mStreamMtype;
	eUCloudRtcRenderMode mRenderMode;
	eUCloudRtcRenderType mRenderType;
	eUCloudRtcVideoFrameType mVideoFrameType; //when extend render this decide callback frametype
}tUCloudRtcVideoCanvas;

//鉴权信息
typedef struct
{
	const char* mAppId;
	const char* mRoomId;
	const char* mUserId;
	const char* mUserToken;
}tUCloudRtcAuth;

//流信息
typedef struct {
	const char* mUserId;
	const char* mStreamId;
	int mStreamMtype;
	int mTracktype; // 1 audio 2 video
	int mAudioBitrate = 0;     // audio bitrate,unit:bps
	int mVideoBitrate = 0;
	int mVideoWidth = 0;     // video width
	int mVideoHeight = 0;     // video height
	int mVideoFrameRate = 0;     // video frames per secon
	float mPacketLostRate = 0.0f;
}tUCloudRtcStreamStats;

//录制信息
typedef struct {
	const char* mRecordId;
	const char* mFileName;
	const char* mRegion;
	const char* mBucket;
	const char* mRoomid;
}tUCloudRtcRecordInfo;

//音频帧信息
typedef struct {
	const char* mUserId;
	const char* mStreamId;
	void* mAudioData;
	int mBytePerSimple;
	int mSimpleRate;
	int mChannels;
	int mNumSimples;
}tUCloudRtcAudioFrame;

//视频帧信息
typedef struct {
	unsigned char* mDataBuf;
	int mWidth;
	int mHeight;
	eUCloudRtcVideoFrameType mVideoType;
}tUCloudRtcVideoFrame;

//视频信息配置
typedef struct {
	int mWidth;
	int mHeight;
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
	MIX_LAYOUT_OLD,      //兼容之前模板
	MIX_LAYOUT_FLOW,	 //流式布局
	MIX_LAYOUT_TEACH,			 //讲课布局
	MIX_LAYOUT_CUSTOM,    //自定义
	MIX_LAYOUT_ADAPTION1, //自适应模板1
	MIX_LAYOUT_ADAPTION2, //自适应模板2
}eUCloudMixLayout;

//转推配置
typedef struct UCloudRtcTranscodeConfig {
	tUCloudBackgroundColor mbgColor;  //背景色
	int mFramerate; //帧率
	int mBitrate;   //码率
	const char*  mMainViewUid; //主讲人的uid
	int mMainviewType; //主讲人放置的流类型
	int mWidth;  //输出分辨率宽度
	int mHeight; //输出分辨率高度
	eUCloudMixLayout mLayout; // 1.流式布局 2.讲课模式 3.自定义布局 4.模板自适应1 5.模板自适应2
	const char*  mStyle; //mLayout=3 时自定义风格内容
	int mLenth;
	tUCloudRtcRelayStream *mStreams; //混流的用户
	int mStreamslength; //长度
	UCloudRtcTranscodeConfig()
	{
		mLayout = MIX_LAYOUT_TEACH;
		mMainViewUid = nullptr;
		mStreams = nullptr;
		mStyle = nullptr;
		mStreamslength = 0;
	}
}tUCloudRtcTranscodeConfig;

//录制信息
typedef struct UCloudRtcRecordConfig {
	const char* mMainviewuid;   //录制的主流用户id
	const char* mBucket;        //存储bucket
	const char* mBucketRegion;  //存储region
	eUCloudRtcRecordProfile mProfile;  //录制profile
	eUCloudRtcRecordType mRecordType;  //录制类型
	eUCloudRtcWaterMarkPos mWatermarkPos;  //水印位置
	eUCloudRtcMeidaType mMainviewmediatype;  //主流的媒体类型

	eUCloudRtcWaterMarkType mWaterMarkType;   //水印类型
	const char* mWatermarkUrl;		//水印url  为图片水印时
	bool mIsaverage;				//是否均分 (true .流式布局，false:讲课模式)
	int mMixerTemplateType;			//模板类型

	//新版录制新增参数
	tUCloudRtcRelayStream *mStreams; //混流的用户
	int mStreamslength; //混流的用户长度
	int mLayout; // 0.取决于mIsaverage 1.流式布局 2.讲课模式 3.自定义布局 4.模板自适应1 5.模板自适应2


	UCloudRtcRecordConfig() {
		mWatermarkUrl = nullptr;
		mMainviewuid = nullptr;
		mBucket = nullptr;
		mBucketRegion = nullptr;
		mStreams = nullptr;
		mLayout = MIX_LAYOUT_OLD;
	}
}tUCloudRtcRecordConfig;
//设备插拔回调
class _EXPORT_API UcloudRtcDeviceChanged
{
public:
	virtual void onInterfaceArrival(const char* dccname, int len) {}
	virtual void onInterfaceRemoved(const char* dccname, int len) {}
	virtual void onInterfaceChangeValue(const char* dccname, int len) {}
	virtual ~UcloudRtcDeviceChanged() {}
};

//音频监听回调
class  _EXPORT_API UCloudRtcAudioFrameCallback
{
public:
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
};

//外部音频源
class  _EXPORT_API UCloudRtcExtendAudioCaptureSource
{
public:
	virtual ~UCloudRtcExtendAudioCaptureSource() {}
	virtual  bool doCaptureAudioFrame(tUCloudRtcAudioFrame* audioframe) = 0;
};

//外部视频源
class  _EXPORT_API UCloudRtcExtendVideoCaptureSource
{
public:
	virtual  bool doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe) = 0;
};

//视频监听回调
class _EXPORT_API UCloudRtcVideoFrameObserver 
{
public:
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};

//外部渲染
class _EXPORT_API UCloudRtcExtendVideoRender
{
public:
	virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe) = 0;
};

#endif

