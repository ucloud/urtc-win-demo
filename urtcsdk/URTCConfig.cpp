#include "URTCConfig.h"
#include "SdkUtil.h"

URTCConfig* URTCConfig::mSInstance = new URTCConfig();
URTCConfig* URTCConfig::getInstance()
{
	return mSInstance;
}

URTCConfig::URTCConfig()
{
	mVideoprofile = UCLOUD_RTC_VIDEO_PROFILE_640_360;
	mSeckey = "you key ";
	mAppid = "you appid";
	mPrivateAddr = "wss://ip:port/ws";
	mAutoPub = false;
	mAutoSub = true;

	mPubVideo = true;
	mPubAudio = true;
	mPubScreen = false;

	mAudioOnly = false;

	mRole = UCLOUD_RTC_USER_STREAM_ROLE_BOTH;
	mSdkMode = UCLOUD_RTC_SDK_MODE_TRIVAL;

	mChannelType = UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION;
	mUserid = "win_" + get_randrom_string(8);
	mRoomid = "123";
}
URTCConfig::~URTCConfig()
{

}

void URTCConfig::setVideoProfile(eUCloudRtcVideoProfile profile)
{
	this->mVideoprofile = profile;
}

eUCloudRtcVideoProfile URTCConfig::getVideoProfile()
{
	return this->mVideoprofile;
}

void URTCConfig::setSecKey(std::string key)
{
	this->mSeckey = key;
}
std::string URTCConfig::getSecKey()
{
	return this->mSeckey;
}

void URTCConfig::setMuteCamBeforeJoin(bool mute)
{
	this->mMuteCamBeforeJoin = mute;
}

bool URTCConfig::getMuteCamBeforeJoin()
{
	return this->mMuteCamBeforeJoin ;
}

void URTCConfig::setMuteMicBeforeJoin(bool mute)
{
	this->mMuteMicBeforeJoin = mute;
}

bool URTCConfig::getMuteMicBeforeJoin()
{
	return this->mMuteMicBeforeJoin;
}

void URTCConfig::setAutoPublish(bool isauto)
{
	this->mAutoPub = isauto;
}
bool URTCConfig::isAutoPublish()
{
	return this->mAutoPub;
}

void URTCConfig::setAutoSubscribe(bool isauto)
{
	this->mAutoSub = isauto;
}
bool URTCConfig::isAutoSubscribe()
{
	return this->mAutoSub;
}

void URTCConfig::setAutoPubVideo(bool isauto)
{
	this->mPubVideo = isauto;
}
bool URTCConfig::isAutoPubVideo()
{
	return this->mPubVideo;
}

void URTCConfig::setAutoPubAudio(bool isauto)
{
	this->mPubAudio = isauto;
}
bool URTCConfig::isAutoPubAudio()
{
	return this->mPubAudio;
}

void URTCConfig::setAutoPubScreen(bool isauto)
{
	this->mPubScreen = isauto;
}
bool URTCConfig::isAutoPubScreen()
{
	return this->mPubScreen;
}

void URTCConfig::setAudioOnly(bool only)
{
	this->mAudioOnly = only;
}
bool URTCConfig::isAudioOnly()
{
	return this->mAudioOnly;
}

void URTCConfig::setStreamRole(eUCloudRtcUserStreamRole role)
{
	this->mRole = role;
}
eUCloudRtcUserStreamRole URTCConfig::getStreamRole()
{
	return this->mRole;
}

void URTCConfig::setChannelType(eUCloudRtcChannelType chtype)
{
	this->mChannelType = chtype;
}
eUCloudRtcChannelType URTCConfig::getChannelType()
{
	return this->mChannelType;
}

void URTCConfig::setSdkMode(eUCloudRtcSdkMode mode)
{
	this->mSdkMode = mode;
}
eUCloudRtcSdkMode URTCConfig::getSdkMode()
{
	return this->mSdkMode;
}

void URTCConfig::setCodecType(eUCloudRtcVideoCodec codec)
{
	this->mCodec = codec;
}

eUCloudRtcVideoCodec URTCConfig::getCodecType()
{
	return this->mCodec;
}

void URTCConfig::setAppId(std::string appid)
{
	this->mAppid = appid;
}
std::string URTCConfig::getAppId()
{
	return this->mAppid;
}

void URTCConfig::setUserId(std::string uid)
{
	this->mUserid = uid;
}
std::string URTCConfig::getUserId()
{
	return this->mUserid;
}

void URTCConfig::setRoomId(std::string rid)
{
	this->mRoomid = rid;
}
std::string URTCConfig::getRoomId()
{
	return this->mRoomid;
}


void  URTCConfig::setPrivateMode(bool bMode) {
	mPrivateMode = bMode;
}

bool  URTCConfig::getPrivateMode() {
	return mPrivateMode;
}


void  URTCConfig::setPrivateAddr(std::string& addr) {
	mPrivateAddr = addr;
}

std::string& URTCConfig::getPrivatAddr() {
	return mPrivateAddr;
}

void  URTCConfig::setIntelMediaCodec(bool bUseMediaCodec) {
	mIntelMediaCodec = bUseMediaCodec;
}
bool  URTCConfig::getIntelMediaCodec() {
	return mIntelMediaCodec;
}