#include "URTCEngineImpl.h"
#include "URTCConfig.h"

URTCEngineImpl::URTCEngineImpl()
{
	m_eventhandler = new URTCEventHandler;
}

URTCEngineImpl::~URTCEngineImpl()
{
	UnInitRTCEngine();
}

int URTCEngineImpl::InitRTCEngine(void* callback)
{
	m_eventhandler->initEventHandler(callback);
	m_rtcengine = UCloudRtcEngine::sharedInstance();
	m_rtcengine->regRtcEventListener(m_eventhandler);
	m_rtcengine->setChannelType(URTCConfig::getInstance()->getChannelType());
	m_rtcengine->setStreamRole(URTCConfig::getInstance()->getStreamRole());
	m_rtcengine->setTokenSecKey(URTCConfig::getInstance()->getSecKey().data());
	m_rtcengine->setAudioOnlyMode(URTCConfig::getInstance()->isAudioOnly());
	m_rtcengine->setAutoPublishSubscribe(URTCConfig::getInstance()->isAutoPublish(), 
		URTCConfig::getInstance()->isAutoSubscribe());
	m_rtcengine->configLocalAudioPublish(URTCConfig::getInstance()->isAutoPubAudio());
	m_rtcengine->configLocalCameraPublish(URTCConfig::getInstance()->isAutoPubVideo());
	m_rtcengine->configLocalScreenPublish(URTCConfig::getInstance()->isAutoPubScreen());
	m_rtcengine->setVideoProfile(URTCConfig::getInstance()->getVideoProfile());
	m_rtcengine->setDesktopProfile(UCLOUD_RTC_SCREEN_PROFILE_HIGH_PLUS);
	m_rtcengine->setSdkMode(URTCConfig::getInstance()->getSdkMode());
	return 0;
}

int URTCEngineImpl::UnInitRTCEngine()
{
	if (m_rtcengine)
	{
		m_rtcengine->destroy();
		m_rtcengine = nullptr;
	}

	if (m_eventhandler)
	{
		delete m_eventhandler;
		m_eventhandler = nullptr;
	}
	return 0;
}

std::string URTCEngineImpl::getSdkVersion()
{
	if (m_rtcengine)
	{
		return m_rtcengine->getSdkVersion();
	}
	return "";
}


int URTCEngineImpl::JoinRoom(tRTCAuthInfo& auth)
{
	if (m_rtcengine)
	{
		tUCloudRtcAuth uauth;
		uauth.mAppId = auth.mAppid.data();
		uauth.mUserId = auth.mUserid.data();
		uauth.mRoomId = auth.mRoomid.data();
		uauth.mUserToken = auth.mToken.data();
		return m_rtcengine->joinChannel(uauth);
	}
	return -1;
}

int URTCEngineImpl::LeaveRoom(std::string& roomid)
{
	if (m_rtcengine)
	{
		return m_rtcengine->leaveChannel();
	}
	return -1;
}

int URTCEngineImpl::SetCodecType(int codec)
{
	if (m_rtcengine)
	{
		return m_rtcengine->setVideoCodec((eUCloudRtcVideoCodec)codec);
	}
	return -1;
}

int URTCEngineImpl::MuteCamBeforeJoin(bool mute)
{
	if (m_rtcengine)
	{
		return m_rtcengine->muteCamBeforeJoin(mute);
	}
	return -1;
}

int URTCEngineImpl::MuteMicBeforeJoin(bool mute)
{
	if (m_rtcengine)
	{
		return m_rtcengine->muteMicBeforeJoin(mute);
	}
	return -1;
}

int URTCEngineImpl::PublishStream(tRTCStreamInfo& streaminfo)
{
	if (m_rtcengine)
	{
		return m_rtcengine->publish((eUCloudRtcMeidaType)streaminfo.mStreamMtype, streaminfo.mEnableVideo, streaminfo.mEnableAudio);
	}
	return -1;
}
int URTCEngineImpl::UnPublishStream(tRTCStreamInfo& streaminfo)
{
	if (m_rtcengine)
	{
		return m_rtcengine->unPublish((eUCloudRtcMeidaType)streaminfo.mStreamMtype);
	}
	return -1;
}
int URTCEngineImpl::StartLocalRender(tRTCRenderView& renderview)
{
	if (m_rtcengine)
	{
		tUCloudRtcVideoCanvas canvas;
		canvas.mUserId = renderview.mUserid.data();
		canvas.mStreamMtype = (eUCloudRtcMeidaType)renderview.mStreamMtype;
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mVideoView = renderview.mVidoview;
		canvas.mRenderType = (eUCloudRtcRenderType)renderview.mRenderType;
		return m_rtcengine->startPreview(canvas);
	}
	return -1;
}
int URTCEngineImpl::StopLocalRender(tRTCRenderView& renderview)
{
	if (m_rtcengine)
	{
		tUCloudRtcVideoCanvas canvas;
		canvas.mStreamMtype = (eUCloudRtcMeidaType)renderview.mStreamMtype;
		return m_rtcengine->stopPreview(canvas);
	}
	return -1;
}
int URTCEngineImpl::MuteLocalCamVideo(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		return m_rtcengine->muteLocalVideo(mute.mMute, UCLOUD_RTC_MEDIATYPE_VIDEO);
	}
	return -1;
}
int URTCEngineImpl::MuteLocalCamAudio(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		return m_rtcengine->muteLocalMic(mute.mMute);
	}
	return -1;
}

int URTCEngineImpl::MuteLocalScreen(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		return m_rtcengine->muteLocalVideo(mute.mMute, UCLOUD_RTC_MEDIATYPE_SCREEN);
	}
	return -1;
}

int URTCEngineImpl::SubRemoteStream(tRTCStreamInfo& streaminfo)
{
	if (m_rtcengine)
	{
		tUCloudRtcStreamInfo info;
		info.mUserId = streaminfo.mUserid.data();
		info.mStreamMtype = (eUCloudRtcMeidaType)streaminfo.mStreamMtype;
		info.mEnableVideo = streaminfo.mEnableVideo;
		info.mEnableAudio = streaminfo.mEnableAudio;
		info.mEnableData = false;
		return m_rtcengine->subscribe(info);
	}
	return -1;
}
int URTCEngineImpl::UnSubRemoteStream(tRTCStreamInfo& streaminfo)
{
	if (m_rtcengine)
	{
		tUCloudRtcStreamInfo info;
		info.mUserId = streaminfo.mUserid.data();
		info.mStreamMtype = (eUCloudRtcMeidaType)streaminfo.mStreamMtype;
		info.mEnableVideo = streaminfo.mEnableVideo;
		info.mEnableAudio = streaminfo.mEnableAudio;
		info.mEnableData = false;
		return m_rtcengine->unSubscribe(info);
	}
	return -1;
}
int URTCEngineImpl::StartRemoteRender(tRTCRenderView& renderview)
{
	if (m_rtcengine)
	{
		tUCloudRtcVideoCanvas canvas;
		canvas.mUserId = renderview.mUserid.data();
		canvas.mStreamMtype = (eUCloudRtcMeidaType)renderview.mStreamMtype;
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mVideoView = renderview.mVidoview;
		canvas.mRenderType = (eUCloudRtcRenderType)renderview.mRenderType;
		return m_rtcengine->startRemoteView(canvas);
	}
	return -1;
}
int URTCEngineImpl::StopRemoteRender(tRTCRenderView& renderview) 
{
	if (m_rtcengine)
	{
		tUCloudRtcVideoCanvas canvas;
		canvas.mUserId = renderview.mUserid.data();
		canvas.mStreamMtype = (eUCloudRtcMeidaType)renderview.mStreamMtype;
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mVideoView = renderview.mVidoview;
		return m_rtcengine->stopRemoteView(canvas);
	}
	return -1;
}
int URTCEngineImpl::MuteRemoteCamVideo(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		tUCloudRtcMuteSt mutest;
		mutest.mMute = mute.mMute;
		mutest.mUserId = mute.mUserid.data();
		mutest.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		return m_rtcengine->muteRemoteVideo(mutest, mute.mMute);
	}
	return -1;
}

int URTCEngineImpl::MuteRemoteCamAudio(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		tUCloudRtcMuteSt mutest;
		mutest.mMute = mute.mMute;
		mutest.mUserId = mute.mUserid.data();
		mutest.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		return m_rtcengine->muteRemoteAudio(mutest, mute.mMute);
	}
	return -1;
}

int URTCEngineImpl::MuteRemoteScreen(tRTCStreamMute& mute)
{
	if (m_rtcengine)
	{
		tUCloudRtcMuteSt mutest;
		mutest.mMute = mute.mMute;
		mutest.mUserId = mute.mUserid.data();
		mutest.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
		return m_rtcengine->muteRemoteVideo(mutest, mute.mMute);
	}
	return -1;
}

int URTCEngineImpl::StartRecord(tRecordConfig& config)
{
	if (m_rtcengine)
	{
		tUCloudRtcRecordConfig uconfig;
		uconfig.mMainviewmediatype = (eUCloudRtcMeidaType)config.mMainviewmediatype;
		uconfig.mMainviewuid = config.mMainviewuid;
		uconfig.mProfile = (eUCloudRtcRecordProfile)config.mProfile;
		uconfig.mRecordType = (eUCloudRtcRecordType)config.mRecordType;
		uconfig.mWatermarkPos = (eUCloudRtcWaterMarkPos)config.mWatermarkPos;
		uconfig.mBucket = config.mBucket;
		uconfig.mBucketRegion = config.mBucketRegion;
		return m_rtcengine->startRecord(uconfig);
	}
	return -1;
}

int URTCEngineImpl::StopRecord()
{
	if (m_rtcengine)
	{
		return m_rtcengine->stopRecord();
	}
	return -1;
}

int URTCEngineImpl::StartMixFile(const char* filepath, bool replace, bool loop, float musicvol)
{
	if (m_rtcengine)
	{
		return m_rtcengine->startAudioMixing(filepath, replace, loop, musicvol);
	}
	return -1;
}

int URTCEngineImpl::StopMixFile()
{
	if (m_rtcengine)
	{
		return m_rtcengine->stopAudioMixing();
	}
	return -1;
}