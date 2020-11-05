#ifndef _UMEETING_RTCDEFINE_H_
#define _UMEETING_RTCDEFINE_H_

#include <string>
#include <map>
#include <list>
#include "UCloudRtcEngine.h"
enum RTC_CHANNEL_TYPE {
	RTC_CHANNELTYPE_UCLOUD,
	RTC_CHANNELTYPE_AGORA,
	RTC_CHANNELTYPE_ZEGO
};

struct tRTCAuthInfo
{
	std::string mUserid;
	std::string mRoomid;
	std::string mAppid;
	std::string mToken;
};

struct tRTCRenderView
{
	std::string mUserid;
	int mStreamMtype;//1 camera 2 screen
	void* mVidoview;
	int mRenderMode;
	int mRenderType; //1 gdi 2 dx 
};

struct tRTCStreamInfo
{
	std::string mUserid;
	int mStreamMtype; //1 camera 2 screen
	bool mEnableVideo;
	bool mEnableAudio;
	bool mEnableData;
};

struct tRTCStreamMute
{
	std::string mUserid;
	bool mMute;
};

class CVideoWnd;
//消息结构
struct tEventMsg
{
	int mEventid;
	std::string mJsonMsg;
};

// 用户信息
struct tUserInfo
{
	std::string mUserid;
};

//流信息
struct tStreamInfo
{
	int mStreamMtype;
	std::string mUserid;
	bool mEnalbevideo;
	bool mEnalbeaudio;
	bool mEnalbedata;
};


struct tRecordConfig
{
	const char* mMainviewuid;
	const char* mBucket;
	const char* mBucketRegion;
	int mProfile;
	int mRecordType;
	int mWatermarkPos;
	int mMainviewmediatype;

	int mWaterMarkType; // 1 time 2 picture 3 text
	const char* mWatermarkUrl; //when mWaterMarkType is text this is text content
	bool mIsaverage; //record layout is one big other average 
	int mMixerTemplateType; //record layout (1 -- 9 )
	int mfps;
	int mBitrate;
};

typedef std::map<std::string, tUserInfo*>::iterator userit;
typedef std::map<std::string, tStreamInfo*>::iterator streamit;
typedef std::map<std::string, CVideoWnd*>::iterator streamrenderit;
typedef std::list<CVideoWnd*>::iterator videowndit;


#endif