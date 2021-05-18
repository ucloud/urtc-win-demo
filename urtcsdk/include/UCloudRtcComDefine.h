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
#define MAX_DEVICE_ID_LENGTH 512 
#define MAX_WINDOWS_TILE_LEN 256 

//���뷽ʽ����
typedef enum
{
	UCLOUD_RTC_SERVER_GET_FROM_UTECH = 1,
	UCLOUD_RTC_SERVER_GET_FROM_USER_GATEWAY,
	UCLOUD_RTC_SERVER_GET_FROM_USER_DIRECT
}eUCloudServerGetFrom;

//�豸��Ϣ
typedef struct {
	//�豸����
	char mDeviceName[MAX_DEVICE_ID_LENGTH];
	//�豸ID
	char mDeviceId[MAX_DEVICE_ID_LENGTH];
}tUCloudRtcDeviceInfo;

//ý������
typedef struct {
	//ʹ��video
	bool mVideoEnable;
	//ʹ��audio
	bool mAudioEnable;
}tUCloudRtcMediaConfig;

//��������
typedef struct
{
	//��Ļ����
	long mScreenindex;
	//x����
	int  mXpos;
	//y����
	int mYpos;
	//���
	int mWidth;
	//����
	int mHeight;
}tUCloudRtcScreenPargram;

//��������
typedef enum {
	//��Ļ
	UCLOUD_RTC_DESKTOPTYPE_SCREEN = 1,
	//����
	UCLOUD_RTC_DESKTOPTYPE_WINDOW
}eUCloudRtcDesktopType;

//���洰����Ϣ
typedef struct
{
	//��������
	eUCloudRtcDesktopType mType;
	//����id
	int mDesktopId;
	int mScreenW;
	int mScreenH;
	//����
	char mDesktopTitle[MAX_WINDOWS_TILE_LEN];
}tUCloudRtcDeskTopInfo;

//�������
typedef enum {
	UCLOUD_RTC_TRACKTYPE_AUDIO = 1,
	UCLOUD_RTC_TRACKTYPE_VIDEO 
}eUCloudRtcTrackType;

//ý������
typedef enum {
	//��
	UCLOUD_RTC_MEDIATYPE_NONE = 0,
	//����ͷ��(�������Ƶ��)
	UCLOUD_RTC_MEDIATYPE_VIDEO = 1,
	//����
	UCLOUD_RTC_MEDIATYPE_SCREEN = 2
}eUCloudRtcMeidaType;

//����Ϣ
typedef struct {
	//�û�ID
	const char* mUserId;
	//��ID
	const char* mStreamId;
	//ʹ��VIDEO
	bool mEnableVideo;
	//ʹ��AUDIO
	bool mEnableAudio;
	//ʹ��Data
	bool mEnableData;
	//mute video״̬
	bool mMuteVideo;
	//mute audio״̬
	bool mMuteAudio;
	//ý������
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcStreamInfo;

//mute ״̬
typedef struct {
	//�û�ID
	const char* mUserId;
	//��ID
	const char* mStreamId;
	//�Ƿ�mute
	bool mMute;
	//ý������
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcMuteSt;

//¼�Ƶ�profile
typedef enum {
	UCLOUD_RTC_RECORDPROFILE_SD = 1, 
	UCLOUD_RTC_RECORDPROFILE_HD, 
	UCLOUD_RTC_RECORDPROFILE_HDPLUS, 
}eUCloudRtcRecordProfile;

//¼������
typedef enum {
	//����Ƶģʽ
	UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1, 
	//����Ƶģʽ
	UCLOUD_RTC_RECORDTYPE_AUDIOVIDEO
}eUCloudRtcRecordType;

//ˮӡλ��
typedef enum {
	UCLOUD_RTC_WATERMARKPOS_LEFTTOP = 1,
	UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM,
	UCLOUD_RTC_WATERMARKPOS_RIGHTTOP,
	UCLOUD_RTC_WATERMARKPOS_RIGHTBOTTOM
}eUCloudRtcWaterMarkPos;

//ˮӡ����
typedef enum {
	//Ĭ����
	UCLOUD_RTC_WATERMARK_TYPE_NONE = 0,
	//ʱ��ˮӡ
	UCLOUD_RTC_WATERMARK_TYPE_TIME = 1,
	//ͼƬˮӡ
	UCLOUD_RTC_WATERMARK_TYPE_PIC,
	//����ˮӡ
	UCLOUD_RTC_WATERMARK_TYPE_TEXT,
}eUCloudRtcWaterMarkType;

//ת��ģʽ
typedef enum {
	//�Զ�
	UCLOUD_RTC_AUTO = 1,
	//�ֶ�
	UCLOUD_RTC_MANAUL = 2,
}eUCloudRtcRelayMode;

//��Ⱦ��������
typedef enum {
	//default full
	UCLOUD_RTC_RENDER_MODE_DEFAULT = 0,
	//fit ģʽ
	UCLOUD_RTC_RENDER_MODE_FIT = 1,
	//fillģʽ
	UCLOUD_RTC_RENDER_MODE_FILL = 2 
} eUCloudRtcRenderMode;

//��Ⱦ����
typedef enum {
	//GDI
	UCLOUD_RTC_RENDER_TYPE_GDI = 1,
	//D3D
	UCLOUD_RTC_RENDER_TYPE_D3D = 2,
	//�ⲿ��Ⱦ
	UCLOUD_RTC_RENDER_TYPE_EXTEND = 3,
} eUCloudRtcRenderType;

//��־����
typedef enum {
	UCLOUD_RTC_LOG_LEVEL_DEBUG,
	UCLOUD_RTC_LOG_LEVEL_INFO,
	UCLOUD_RTC_LOG_LEVEL_WARN,
	UCLOUD_RTC_LOG_LEVEL_ERROR,
	UCLOUD_RTC_LOG_LEVEL_NONE,
} eUCloudRtcLogLevel;

//��Ƶprofile
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

//����profile
typedef enum {
	UCLOUD_RTC_SCREEN_PROFILE_LOW = 1,
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE = 2,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH = 3,

	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS = 4,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_1 = 5,     //���2m���� 25֡
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS_1 = 6, //���2.5m���� 25֡
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_0 = 7,     //���1.6m���� 15֡
	UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS_0 = 8 //���2m���� 18֡
} eUCloudRtcScreenProfile;

//Ӧ������
typedef enum {
	//��Ƶ����ģʽ
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION,
	//ֱ��ģʽ
	UCLOUD_RTC_CHANNEL_TYPE_BROADCAST
}eUCloudRtcChannelType;

//Ȩ������
typedef enum {
	// ����Ȩ��
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, 
	// ����Ȩ��
	UCLOUD_RTC_USER_STREAM_ROLE_SUB,
	// ������
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH 
} eUCloudRtcUserStreamRole;

//SDK ģʽ
typedef enum {
	//��ʽģʽ token��appserver����
	UCLOUD_RTC_SDK_MODE_NORMAL, 
	//����ģʽ sdk�ڲ����� ������appkey
	UCLOUD_RTC_SDK_MODE_TRIVAL, 
} eUCloudRtcSdkMode;

//��Ƶ��������
typedef enum {
	UCLOUD_RTC_CODEC_VP8 = 1, 
	UCLOUD_RTC_CODEC_H264 
} eUCloudRtcVideoCodec;

//��Ƶ��������
typedef enum {
	UCLOUD_RTC_CODEC_OPUS = 1, //default
} eUCloudRtcAudioCodec;

//FRAME ����
typedef enum {
	UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 = 1,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGB24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_BGR24,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_RGBA,
	UCLOUD_RTC_VIDEO_FRAME_TYPE_ARGB,
}eUCloudRtcVideoFrameType;

//��������������
typedef enum {
	//����
	UCLOUD_RTC_NETWORK_TX = 1, 
	//����
	UCLOUD_RTC_NETWORK_RX = 2,  
}eUCloudRtcNetworkQuality;

//��������
typedef enum {
	//δ֪
	UCLOUD_RTC_QUALITY_UNKNOWN = 0, 
	//�ܻ�
	UCLOUD_RTC_QUALITY_DOWN = 5,  
	//��ǿ�ܹ�ͨ����˳��
	UCLOUD_RTC_QUALITY_BAD = 4,  
	//�û����۸�����覴õ���Ӱ�칵ͨ
	UCLOUD_RTC_QUALITY_POOR =  3, 
	// �û����۸о��� excellent ���
	UCLOUD_RTC_QUALITY_GOOD = 2, 
	//������������
	UCLOUD_RTC_QUALITY_EXCELLENT = 1, 
}eUCloudRtcQualityType;

//rtmp״̬
typedef enum {
	//����δ��ʼ��ֹͣ
	RTMP_STREAM_PUBLISH_STATE_IDLE ,   
	//��������
	RTMP_STREAM_PUBLISH_STATE_RUNNING, 
	//����ʧ�� ���code
	RTMP_STREAM_PUBLISH_STATE_FAILURE ,
	//ֹͣ����ʧ�� ���code
	RTMP_STREAM_PUBLISH_STATE_STOPFAILURE, 
	//�쳣ֹͣ����(������ʱֹͣ)
	RTMP_STREAM_PUBLISH_STATE_EXCEPTIONSTOP, 
	//���²��ֽ��
	RTMP_STREAM_PUBLISH_STATE_UPDATECONFIGRES,  //code Ϊ0ʱ����succ
}eUCloudRtmpState;

// ��Ⱦ��ͼ
typedef struct
{
	//������ͼ
	void* mVideoView;
	//�û�id
	const char* mUserId;
	//��ID
	const char* mStreamId;
	//������
	eUCloudRtcMeidaType mStreamMtype;
	//��Ⱦ����ģʽ
	eUCloudRtcRenderMode mRenderMode;
	//��Ⱦ����
	eUCloudRtcRenderType mRenderType;
	//when extend render this decide callback frametype
	eUCloudRtcVideoFrameType mVideoFrameType;
}tUCloudRtcVideoCanvas;

//��Ȩ��Ϣ
typedef struct
{
	const char* mAppId = nullptr;
	const char* mRoomId = nullptr;
	const char* mUserId = nullptr;
	const char* mUserToken = nullptr;
	const char* mServerUrl = nullptr;
}tUCloudRtcAuth;

//����Ϣ
typedef struct {
	//�û�id
	const char* mUserId;
	//��id
	const char* mStreamId;
	//������
	int mStreamMtype;
	//track���� 1 audio 2 video
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
	//������
	float mPacketLostRate = 0.0f;
}tUCloudRtcStreamStats;

//¼����Ϣ
typedef struct {
	//¼��ID
	const char* mRecordId;
	//¼���ļ���
	const char* mFileName;
	//region
	const char* mRegion;
	//bucket
	const char* mBucket;
	//����id
	const char* mRoomid;
}tUCloudRtcRecordInfo;

//��Ƶ֡��Ϣ
typedef struct {
	//�û�id
	const char* mUserId;
	//��ID
	const char* mStreamId;
	//audio ����
	void* mAudioData;
	int mBytePerSimple;
	//������
	int mSimpleRate;
	//������
	int mChannels;
	int mNumSimples;
	long long renderTimeMs;
}tUCloudRtcAudioFrame;

//��Ƶ֡��Ϣ
typedef struct {
	//��Ƶ����
	unsigned char* mDataBuf;
	int mWidth;
	int mHeight;
	//frametype
	eUCloudRtcVideoFrameType mVideoType;
	long long renderTimeMs;
}tUCloudRtcVideoFrame;

//��Ƶ��Ϣ����
typedef struct {
	int mWidth;
	int mHeight;
	//֡��
	int mFrameRate;
    int mBitrate; //kbps
}tUCloudVideoConfig;

//��������ɫ����
typedef struct  {
	int mRed;
	int mGreen;
	int mBlue;
}tUCloudBackgroundColor;

typedef enum {
    UCloud_EMDM_UNKNOWN = 0,
    UCloud_EMDM_PUSH,       //����ģʽ
    UCloud_EMDM_PULL,       //����ģʽ
}eUCloudExtendMediaDataMode;

typedef enum {
    UCloud_Audio_Profile_Default = 0,  //Ĭ��ģʽ�� �������� 32K����
    UCloud_Audio_Profile_Stand,  //��׼ģʽ�� �������� 64K����
    UCloud_Audio_Profile_Stand_Stereo, //��׼�������� ˫������ 80K����
    UCloud_Audio_Profile_Hight,   //������ģʽ�� �������� 96K����
    UCloud_Audio_Profile_Hight_Stereo, //�������������� ˫������ 128K����
    UCloud_Audio_Profile_Stand_Stereo_Disable_2A, // ��׼�������� ˫������ 80K���ʣ� ����AEC�� AGC
    UCloud_Audio_Profile_Hight_Disable_2A,   //������ģʽ�� �������� 96K���ʣ� ����AEC�� AGC
    UCloud_Audio_Profile_Hight_Stereo_Disable_2A, //�������������� ˫������ 128K���ʣ� ����AEC�� AGC
}eUCloudAudioProfile;

//��Ƶ��������
typedef enum {
	UCLOUD_QUALITY_CB = 0, //CB
	UCLOUD_QUALITY_B,
	UCLOUD_QUALITY_M,
	UCLOUD_QUALITY_E,
	UCLOUD_QUALITY_H
}eUCloudRtcQualityLevel;

//ת�ƻ�����������
typedef enum {
	RTMP_STREAM_ADD,	 //���
	RTMP_STREAM_REMOVE,  //ɾ��
}eUCloudRtmpOpration;

//ת�Ƶ���
typedef struct UCloudRtcRelayStream {
	const char* mUid;
	eUCloudRtcMeidaType mType;
	UCloudRtcRelayStream() {
		mUid = nullptr;
		mType = UCLOUD_RTC_MEDIATYPE_NONE;
	}
}tUCloudRtcRelayStream;

//ת�ƻ�����������
typedef enum {
	MIX_LAYOUT_OLD,       //����֮ǰģ��
	MIX_LAYOUT_FLOW,	  //��ʽ����
	MIX_LAYOUT_TEACH,	  //���β���
	MIX_LAYOUT_CUSTOM,    //�Զ���
	MIX_LAYOUT_ADAPTION1, //����ģʽ
	MIX_LAYOUT_ADAPTION2, //����ģʽ
	MIX_LAYOUT_ADAPTION3, //����ģʽ
}eUCloudMixLayout;

typedef int UcloudRtcLayoutLsit[3];
//ת������
typedef struct UCloudRtcTranscodeConfig {
	//����ɫ
	tUCloudBackgroundColor mbgColor; 
	//֡��
	int mFramerate;
	//����
	int mBitrate;   
	//�����˵�uid
	const char*  mMainViewUid; 
	//�����˷��õ�ý������
	int mMainviewType; 
	//����ֱ��ʿ��
	int mWidth; 
	//����ֱ��ʸ߶�
	int mHeight; 
	//�����б�
	UcloudRtcLayoutLsit mlayouts;
	//��ǰʹ�õò��� 1.��ʽ���� 2.����ģʽ 3.�Զ��岼�� 4.ģ������Ӧ1 5.ģ������Ӧ2 6.����ģʽ
	eUCloudMixLayout mLayout;
	//mLayout=3 ʱ�Զ���������
	const char*  mStyle; 
	//�������û�
	tUCloudRtcRelayStream *mStreams; 
	//�����û���
	int mStreamslength;
	//ˮӡλ��
	eUCloudRtcWaterMarkPos mWatermarkPos;
	//ˮӡ����
	eUCloudRtcWaterMarkType mWaterMarkType;
	//ˮӡurl  ΪͼƬˮӡʱ
	const char* mWatermarkUrl;
	//�Ƿ���Ƶ
	bool mIsAudio;
	//ģʽ
	eUCloudRtcRelayMode mMode;
	//������(����������״̬����1���� ת���Զ�ֹͣ)
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

//¼����Ϣ
typedef struct UCloudRtcRecordConfig {
	//¼�Ƶ������û�id
	const char* mMainviewuid;   
	//�洢bucket
	const char* mBucket;    
	//�洢region
	const char* mBucketRegion;  
	//¼��profile
	eUCloudRtcRecordProfile mProfile;  
	//¼������
	eUCloudRtcRecordType mRecordType;
	//ˮӡλ��
	eUCloudRtcWaterMarkPos mWatermarkPos;
	//������ý������
	eUCloudRtcMeidaType mMainviewmediatype; 
	//ˮӡ����
	eUCloudRtcWaterMarkType mWaterMarkType;  
	//ˮӡurl  ΪͼƬˮӡʱ
	const char* mWatermarkUrl;	
	//�Ƿ��Զ� (true .�Զ���false:�ֶ�)
	bool mIsaverage;		
	//ģ������
	int mMixerTemplateType;	
	//֡��ֻ����15�ı���
	int mFps;
	//����
	int mBitrate;
	//�������û�
	tUCloudRtcRelayStream *mStreams;
	//�������û�����
	int mStreamslength; 
	// 0.ȡ����mIsaverage 1.��ʽ���� 2.����ģʽ 3.�Զ��岼�� 4.ģ������Ӧ1 5.ģ������Ӧ2
	int mLayout; 
	UCloudRtcRecordConfig() {
		mWatermarkUrl = nullptr;
		mMainviewuid = nullptr;
		mBucket = nullptr;
		mBucketRegion = nullptr;
		mStreams = nullptr;
		mLayout = MIX_LAYOUT_OLD;
		mFps = 0;
		mBitrate = 0;
		mIsaverage = true;
	}
}tUCloudRtcRecordConfig;

typedef enum {
	DEVICE_VIDEO,      //��Ƶ�豸
	DEVICE_AUDIO,	 //��Ƶ�豸
}eUCloudDeviceType;

typedef enum {
	INTEL_MEDIACODEC,  //intel hard codec
	AMD_MEDIACODEC,   //amd chard odec  
}eUcloudMediaCodec;

typedef struct 
{
	bool mIsInline  = true;
	const char* mLogPath  = nullptr;
	const char* mLogName  = nullptr;
	eUCloudRtcLogLevel mLogLevel = UCLOUD_RTC_LOG_LEVEL_DEBUG;
	int mMaxReconnect = 999;
	bool mIsMediaCodec = false;
	eUcloudMediaCodec mMediaCodec = INTEL_MEDIACODEC;
}tUCloudRtcInitContext;

//�豸��λص�
class UcloudRtcDeviceChanged
{
public:
	///�����豸
	///@param dtype �豸����
	///@param dccname ����
	///@param len ����
	virtual void onInterfaceArrival(eUCloudDeviceType dtype,const char* dccname, int len) {}

	///�Ƴ��豸
	///@param dtype �豸����
	///@param dccname ����
	///@param len ����
	virtual void onInterfaceRemoved(eUCloudDeviceType dtype, const char* dccname, int len) {}

	///�豸���Ըı�
	///@param dtype �豸����
	///@param dccname �豸����
	///@param len ����
	virtual void onInterfaceChangeValue(eUCloudDeviceType dtype, const char* dccname, int len) {}
	virtual ~UcloudRtcDeviceChanged() {}
};

//��Ƶ�����ص�
class UCloudRtcAudioFrameCallback
{
public:
	///������ƵԴ����callback
	///@param audioframe ��Ƶ����
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	///Զ����ƵԴ����callback
	///@param audioframe ��Ƶ����
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	///���غ�Զ����ƵԴ����callback
	///@param audioframe ��Ƶ����
	virtual void onLoaclRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
};

//�ⲿ��ƵԴ(�ѷ��� ����UCloudIAudioFrameObserver )
class  UCloudRtcExtendAudioCaptureSource
{
public:
	virtual ~UCloudRtcExtendAudioCaptureSource() {}
	///��ƵԴ���� �ڲ����Զ����ô˽ӿ�
	///@param audioframe ��Ƶ����
	virtual  bool doCaptureAudioFrame(tUCloudRtcAudioFrame* audioframe) = 0;
};

//�ⲿ��ƵԴ���ѷ��� ����UCloudIVideoFrameObserver��
class  UCloudRtcExtendVideoCaptureSource
{
public:
	///��ƵԴ���� �ڲ����Զ����ô˽ӿ�
	///@param videoframe ��Ƶ֡
	virtual  bool doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe) = 0;
};

//��Ƶ�豸startcapture�����ص�
class UCloudRtcVideoFrameObserver 
{
public:
	///��Ƶ�ɼ����ݻص�
	///@param videoframe ��Ƶ����
	///@param buflen ����
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};

//�ⲿ��Ⱦ
class UCloudRtcExtendVideoRender
{
public:
	///�ⲿ��Ⱦ
	///@param videoframe �³�����Ƶ֡
	virtual  void onRemoteFrame(const tUCloudRtcVideoFrame* videoframe) = 0;
};



//��Ƶ�����ص�
class UCloudIVideoFrameObserver
{
public:
	///��Ƶ�ɼ���ÿһ֡�ûص�
	///@param videoframe ��Ƶ����
	virtual  bool onCaptureFrame(tUCloudRtcVideoFrame *videoFrame) = 0;
	
};

//��Ƶ�����ص�
class UCloudIAudioFrameObserver
{
public:
	///��Ƶ�ɼ���ÿһ֡�ûص�
	///@param  audioFrame ��Ƶ����
	virtual  bool onCaptureFrame(tUCloudRtcAudioFrame* audioFrame) = 0;

};
#endif

