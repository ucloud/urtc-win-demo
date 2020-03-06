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

typedef struct {
	char mDeviceName[MAX_DEVICE_ID_LENGTH];
	char mDeviceId[MAX_DEVICE_ID_LENGTH];
}tUCloudRtcDeviceInfo;

typedef struct {
	bool mVideoEnable;
	bool mAudioEnable;
}tUCloudRtcMediaConfig;

typedef struct
{
	long mScreenindex;
	int  mXpos;
	int mYpos;
	int mWidth;
	int mHeight;
}tUCloudRtcScreenPargram;

typedef enum {
	UCLOUD_RTC_DESKTOPTYPE_SCREEN = 1,
	UCLOUD_RTC_DESKTOPTYPE_WINDOW
}eUCloudRtcDesktopType;

typedef struct
{
	eUCloudRtcDesktopType mType;
	int mDesktopId;
	char mDesktopTitle[MAX_WINDOWS_TILE_LEN];
}tUCloudRtcDeskTopInfo;

typedef enum {
	UCLOUD_RTC_TRACKTYPE_AUDIO = 1,
	UCLOUD_RTC_TRACKTYPE_VIDEO 
}eUCloudRtcTrackType;

typedef enum {
	UCLOUD_RTC_MEDIATYPE_NONE = 0,
	UCLOUD_RTC_MEDIATYPE_VIDEO = 1,
	UCLOUD_RTC_MEDIATYPE_SCREEN = 2
}eUCloudRtcMeidaType;

typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mEnableVideo;
	bool mEnableAudio;
	bool mEnableData;
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcStreamInfo;

typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mMute;
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcMuteSt;

typedef enum {
	UCLOUD_RTC_RECORDPROFILE_SD = 1, 
	UCLOUD_RTC_RECORDPROFILE_HD, 
	UCLOUD_RTC_RECORDPROFILE_HDPLUS, 
}eUCloudRtcRecordProfile;

typedef enum {
	UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1, 
	UCLOUD_RTC_RECORDTYPE_AUDIOVIDEO
}eUCloudRtcRecordType;

typedef enum {
	UCLOUD_RTC_WATERMARKPOS_LEFTTOP = 1,
	UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM,
	UCLOUD_RTC_WATERMARKPOS_RIGHTTOP,
	UCLOUD_RTC_WATERMARKPOS_RIGHTBOTTOM
}eUCloudRtcWaterMarkPos;

typedef enum {
	UCLOUD_RTC_WATERMARK_TYPE_TIME = 1,
	UCLOUD_RTC_WATERMARK_TYPE_PIC,
	UCLOUD_RTC_WATERMARK_TYPE_TEXT,
}eUCloudRtcWaterMarkType;

//render type
typedef enum {
	UCLOUD_RTC_RENDER_MODE_DEFAULT = 0, //default full
	UCLOUD_RTC_RENDER_MODE_FIT = 1, 
	UCLOUD_RTC_RENDER_MODE_FILL = 2 
} eUCloudRtcRenderMode;

//render type
typedef enum {
	UCLOUD_RTC_RENDER_TYPE_GDI = 1,
	UCLOUD_RTC_RENDER_TYPE_D3D = 2,
	UCLOUD_RTC_RENDER_TYPE_EXTEND = 3,
} eUCloudRtcRenderType;

/**
*  log level
*/
typedef enum {
	UCLOUD_RTC_LOG_LEVEL_DEBUG,
	UCLOUD_RTC_LOG_LEVEL_INFO,
	UCLOUD_RTC_LOG_LEVEL_WARN,
	UCLOUD_RTC_LOG_LEVEL_ERROR,
	UCLOUD_RTC_LOG_LEVEL_NONE,
} eUCloudRtcLogLevel;

//video profile
typedef enum {
	UCLOUD_RTC_VIDEO_PROFILE_NONE = -1, 
	UCLOUD_RTC_VIDEO_PROFILE_320_180 = 1,
	UCLOUD_RTC_VIDEO_PROFILE_320_240 = 2,
	UCLOUD_RTC_VIDEO_PROFILE_640_360 = 3,
	UCLOUD_RTC_VIDEO_PROFILE_640_480 = 4,
	UCLOUD_RTC_VIDEO_PROFILE_1280_720 = 5,
	UCLOUD_RTC_VIDEO_PROFILE_1920_1080 = 6
} eUCloudRtcVideoProfile;

typedef enum {
	UCLOUD_RTC_SCREEN_PROFILE_LOW = 1,
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE = 2,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH = 3,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS = 4
} eUCloudRtcScreenProfile;


typedef enum {
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION,
	UCLOUD_RTC_CHANNEL_TYPE_BROADCAST
}eUCloudRtcChannelType;

//stream role 
typedef enum {
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, // up
	UCLOUD_RTC_USER_STREAM_ROLE_SUB,// down
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH //both
} eUCloudRtcUserStreamRole;

//sdk mode
typedef enum {
	UCLOUD_RTC_SDK_MODE_NORMAL, 
	UCLOUD_RTC_SDK_MODE_TRIVAL, 
} eUCloudRtcSdkMode;

typedef enum {
	UCLOUD_RTC_CODEC_VP8 = 1, //default
	UCLOUD_RTC_CODEC_H264
} eUCloudRtcVideoCodec;

typedef enum {
	UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 = 1,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGB24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_BGR24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGBA,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_ARGB,
}eUCloudRtcVideoFrameType;


typedef enum {
	UCLOUD_RTC_NETWORK_TX = 1,  //上行
	UCLOUD_RTC_NETWORK_RX = 2,  //下行
}eUCloudRtcNetworkQuality;

typedef enum {
	UCLOUD_RTC_QUALITY_UNKNOWN = 0, //未知
	UCLOUD_RTC_QUALITY_DOWN = 1,  //很坏
	UCLOUD_RTC_QUALITY_BAD = 2,  //勉强能沟通但不顺畅
	UCLOUD_RTC_QUALITY_POOR =  3, //用户主观感受有瑕疵但不影响沟通
	UCLOUD_RTC_QUALITY_GOOD = 4, // 用户主观感觉和 excellent 差不多
	UCLOUD_RTC_QUALITY_EXCELLENT = 5, //网络质量极好
}eUCloudRtcQualityType;

typedef struct {
	const char* mMainviewuid;
	const char* mBucket;
	const char* mBucketRegion;
	eUCloudRtcRecordProfile mProfile;
	eUCloudRtcRecordType mRecordType;
	eUCloudRtcWaterMarkPos mWatermarkPos;
	eUCloudRtcMeidaType mMainviewmediatype;

	eUCloudRtcWaterMarkType mWaterMarkType;
	const char* mWatermarkUrl; //when mWaterMarkType is text this is text content
	bool mIsaverage; //record layout is one big other average 
	int mMixerTemplateType; //record layout (1 -- 9 )

}tUCloudRtcRecordConfig;

// render view
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


typedef struct
{
	const char* mAppId;
	const char* mRoomId;
	const char* mUserId;
	const char* mUserToken;
}tUCloudRtcAuth;

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

typedef struct {
	const char* mRecordId;
	const char* mFileName;
	const char* mRegion;
	const char* mBucket;
	const char* mRoomid;
}tUCloudRtcRecordInfo;


typedef struct {
	const char* mUserId;
	const char* mStreamId;
	void* mAudioData;
	int mBytePerSimple;
	int mSimpleRate;
	int mChannels;
	int mNumSimples;
}tUCloudRtcAudioFrame;

typedef struct {
	unsigned char* mDataBuf;
	int mWidth;
	int mHeight;
	eUCloudRtcVideoFrameType mVideoType;
}tUCloudRtcVideoFrame;

typedef struct {
	int mWidth;
	int mHeight;
	int mFrameRate;
}tUCloudVideoConfig;


class _EXPORT_API UcloudRtcDeviceChanged
{
public:
	virtual void onInterfaceArrival(const char* dccname, int len) {}
	virtual void onInterfaceRemoved(const char* dccname, int len) {}
	virtual void onInterfaceChangeValue(const char* dccname, int len) {}
	virtual ~UcloudRtcDeviceChanged() {}
};

class  _EXPORT_API UCloudRtcAudioFrameCallback
{
public:
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
};

class  _EXPORT_API UCloudRtcExtendAudioCaptureSource
{
public:
	virtual ~UCloudRtcExtendAudioCaptureSource() {}
	virtual  bool doCaptureAudioFrame(tUCloudRtcAudioFrame* audioframe) = 0;
};

class  _EXPORT_API UCloudRtcExtendVideoCaptureSource
{
public:
	virtual  bool doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe) = 0;
};

class _EXPORT_API UCloudRtcVideoFrameObserver 
{
public:
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};

class _EXPORT_API UCloudRtcExtendVideoRender
{
public:
	virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe) = 0;
};

#endif

