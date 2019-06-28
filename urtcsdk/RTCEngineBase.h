#ifndef _UMEETING_RTCENGINEBASE_H_
#define _UMEETING_RTCENGINEBASE_H_

#include "RTCDefine.h"

class RTCEngineBase{
public:
	virtual ~RTCEngineBase(){}

	virtual int InitRTCEngine(void* callback) = 0 ;
	virtual int UnInitRTCEngine() = 0;

	virtual std::string getSdkVersion() = 0;

	virtual int JoinRoom(tRTCAuthInfo& auth) = 0;
	virtual int LeaveRoom(std::string& roomid) = 0;

	virtual int PublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnPublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartLocalRender(tRTCRenderView& renderview) = 0;
	virtual int StopLocalRender(tRTCRenderView& renderview) = 0;
	virtual int MuteLocalCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalScreen(tRTCStreamMute& mute) = 0;

	virtual int SubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnSubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int StopRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int MuteRemoteCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteScreen(tRTCStreamMute& mute) = 0;

	virtual int StartRecord() = 0;
	virtual int StopRecord() = 0;
};

#endif
