#ifndef _UMEETING_URTCENGINEIMPL_H_
#define _UMEETING_URTCENGINEIMPL_H_

#include "UCloudRtcEngine.h"
#include "RTCEngineBase.h"
#include "URTCEventHandler.h"



class URTCEngineImpl :   
	public RTCEngineBase{
public:
	URTCEngineImpl();
	virtual ~URTCEngineImpl();

	virtual int InitRTCEngine(void* callback) ;
	virtual int UnInitRTCEngine() ;

	virtual std::string getSdkVersion();
	virtual int EnableRtspSource(int mediatype, bool enable, std::string rtspurl);

	virtual int JoinRoom(tRTCAuthInfo& auth);
	virtual int LeaveRoom(std::string& roomid);
	virtual int SetCodecType(int codec);

	virtual int MuteCamBeforeJoin(bool mute);
	virtual int MuteMicBeforeJoin(bool mute);
	virtual int enableExtendVideoSource(bool enable, UCloudRtcExtendVideoCaptureSource* source);
	virtual int enableExtendAudiocapture(bool enable, UCloudRtcExtendAudioCaptureSource* source);
	virtual void RegDeviceChangeCallback(UcloudRtcDeviceChanged* callback);
	virtual int PublishStream(tRTCStreamInfo& streaminfo) ;
	virtual int UnPublishStream(tRTCStreamInfo& streaminfo) ;
	virtual int StartLocalRender(tRTCRenderView& renderview);
	virtual int StopLocalRender(tRTCRenderView& renderview);
	virtual int MuteLocalCamVideo(tRTCStreamMute& mute) ;
	virtual int MuteLocalCamAudio(tRTCStreamMute& mute);
	virtual int MuteLocalScreen(tRTCStreamMute& mute);

	virtual int SubRemoteStream(tRTCStreamInfo& streaminfo);
	virtual int UnSubRemoteStream(tRTCStreamInfo& streaminfo);
	virtual int StartRemoteRender(tRTCRenderView& renderview);
	virtual int StopRemoteRender(tRTCRenderView& renderview);
	virtual int MuteRemoteCamVideo(tRTCStreamMute& mute);
	virtual int MuteRemoteCamAudio(tRTCStreamMute& mute);
	virtual int MuteRemoteScreen(tRTCStreamMute& mute) ;

	virtual int StartRecord(tRecordConfig& config);
	virtual int StopRecord() ;

	virtual int StartMixFile(const char* filepath, bool replace, bool loop, float musicvol);
	virtual int StopMixFile();


	virtual int StartPushCDN(const char* url, tUCloudRtcTranscodeConfig *config);
	virtual int StopPushCDN(const char* url) ;
private:

	UCloudRtcEngine*   m_rtcengine;
	URTCEventHandler* m_eventhandler;
};

#endif

