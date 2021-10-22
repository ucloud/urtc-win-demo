#ifndef _UMEETING_URTCONFIG_H_
#define _UMEETING_URTCONFIG_H_

#include "UCloudRtcComDefine.h"

#include <string>
#include <map>
#include <list>

class URTCConfig
{
public:
	static URTCConfig* getInstance();

	void setVideoProfile(eUCloudRtcVideoProfile profile);
	eUCloudRtcVideoProfile getVideoProfile();

	void setSecKey(std::string key);
	std::string getSecKey();

	void setMuteCamBeforeJoin(bool mute);
	bool getMuteCamBeforeJoin();

	void setMuteMicBeforeJoin(bool mute);
	bool getMuteMicBeforeJoin();

	void setAutoPublish(bool isauto);
	bool isAutoPublish();

	void setAutoSubscribe(bool isauto);
	bool isAutoSubscribe();

	void setAutoPubVideo(bool isauto);
	bool isAutoPubVideo();

	void setAutoPubAudio(bool isauto);
	bool isAutoPubAudio();

	void setAutoPubScreen(bool isauto);
	bool isAutoPubScreen();

	void setAudioOnly(bool only);
	bool isAudioOnly();

	void setStreamRole(eUCloudRtcUserStreamRole role);
	eUCloudRtcUserStreamRole getStreamRole();

	void setChannelType(eUCloudRtcChannelType chtype);
	eUCloudRtcChannelType getChannelType();

	void setSdkMode(eUCloudRtcSdkMode mode);
	eUCloudRtcSdkMode getSdkMode();

	void setCodecType(eUCloudRtcVideoCodec codec);
	eUCloudRtcVideoCodec getCodecType();

	void setAppId(std::string appid);
	std::string getAppId();

	void setUserId(std::string uid);
	std::string getUserId();

	void setRoomId(std::string rid);
	std::string getRoomId();

	void setPrivateMode(bool bMode);
	bool getPrivateMode();

	void setPrivateAddr(std::string& addr);
	std::string& getPrivatAddr();

	void setIntelMediaCodec(bool bUseMediaCodec);
	bool getIntelMediaCodec();
protected:
	URTCConfig();
	~URTCConfig();
private:
	static URTCConfig* mSInstance;

	eUCloudRtcVideoProfile mVideoprofile;
	std::string mSeckey;

	bool mAutoPub;
	bool mAutoSub;

	bool mPubVideo;
	bool mPubAudio;
	bool mPubScreen;

	bool mMuteCamBeforeJoin = false;
	bool mMuteMicBeforeJoin = false;

	bool mAudioOnly;

	eUCloudRtcUserStreamRole mRole;
	eUCloudRtcSdkMode mSdkMode;

	eUCloudRtcChannelType mChannelType;
	eUCloudRtcVideoCodec mCodec;
	std::string mAppid;

	std::string mUserid;
	std::string mRoomid;

	std::string mPrivateAddr;
	bool mPrivateMode = false;

	bool mIntelMediaCodec = false;
};

#endif
