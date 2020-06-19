#ifndef _UMEETING_RTCENGINEBASE_H_
#define _UMEETING_RTCENGINEBASE_H_

#include "RTCDefine.h"
class UCloudRtcExtendVideoCaptureSource;
class UCloudRtcExtendAudioCaptureSource;
class UcloudRtcDeviceChanged;
class RTCEngineBase{
public:
	virtual ~RTCEngineBase(){}

	virtual int InitRTCEngine(void* callback) = 0 ;
	virtual int UnInitRTCEngine() = 0;

	virtual std::string getSdkVersion() = 0;

	virtual void RegDeviceChangeCallback(UcloudRtcDeviceChanged* callback) = 0;

	virtual int EnableRtspSource(int mediatype, bool enable, std::string rtspurl) =0;

	virtual int JoinRoom(tRTCAuthInfo& auth) = 0;
	virtual int LeaveRoom(std::string& roomid) = 0;

	virtual int MuteCamBeforeJoin(bool mute) = 0;
	virtual int MuteMicBeforeJoin(bool mute) = 0;

	virtual int enableExtendVideoSource(bool enable, UCloudRtcExtendVideoCaptureSource* source) = 0;
	virtual int enableExtendAudiocapture(bool enable, UCloudRtcExtendAudioCaptureSource* audiocapture)  = 0;
	virtual int PublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnPublishStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartLocalRender(tRTCRenderView& renderview) = 0;
	virtual int StopLocalRender(tRTCRenderView& renderview) = 0;
	virtual int MuteLocalCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalScreenAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteLocalScreen(tRTCStreamMute& mute) = 0;

	virtual int SetCodecType(int codec) = 0;

	virtual int SubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int UnSubRemoteStream(tRTCStreamInfo& streaminfo) = 0;
	virtual int StartRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int StopRemoteRender(tRTCRenderView& renderview) = 0;
	virtual int MuteRemoteCamVideo(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteCamAudio(tRTCStreamMute& mute) = 0;
	virtual int MuteRemoteScreen(tRTCStreamMute& mute) = 0;

	virtual int StartRecord(tRecordConfig& config) = 0;
	virtual int StopRecord() = 0;

	virtual int StartMixFile(const char* filepath, bool replace, bool loop, float musicvol) = 0;
	virtual int StopMixFile() = 0;

	virtual int StartPushCDN(const char* url, tUCloudRtcTranscodeConfig *config) = 0;
	virtual int StopPushCDN(const char* url) = 0;

	virtual int SetStreamRole(int role) = 0;
};

#endif
