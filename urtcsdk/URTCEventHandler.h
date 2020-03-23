#ifndef _UMEETING_URTCEVENTHANDLER_H_
#define _UMEETING_URTCEVENTHANDLER_H_

#include "UCloudRtcEngine.h"
#include "RTCDefine.h"
#include "RTCEventDefine.h"
#include <string>

class URTCEventHandler : public UCloudRtcEventListener {
public:
	URTCEventHandler();
	virtual ~URTCEventHandler();
	virtual void initEventHandler(void* callback);
	virtual void onServerDisconnect();
	virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid);
	virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid);
	virtual void onRejoining(const char* uid, const char* roomid);
	virtual void onReJoinRoom(const char* uid, const char* roomid);
	virtual void onRemoteUserJoin(const char* uid);
	virtual void onRemoteUserLeave(const char* uid, int reson);
	virtual void onRemotePublish(tUCloudRtcStreamInfo& info);
	virtual void onRemoteUnPublish(tUCloudRtcStreamInfo& info);
	virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onLocalStreamMuteRsp(const int code, const char* msg,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);
	virtual void onRemoteTrackNotify(const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);
	virtual void onError(int code);
	virtual void onKickoff(int code);
	virtual void onStartRecord(const int code, const char* msg, tUCloudRtcRecordInfo& info);
	virtual void onStopRecord(const int code, const char* msg, const char* recordid);
	virtual void onRemoteAudioLevel(const char* uid, int volume);
	virtual void onLocalAudioLevel(int volume);
	virtual void onSendRTCStats(tUCloudRtcStreamStats& rtstats);
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats);
	virtual void onNetworkQuality(const char* uid, eUCloudRtcNetworkQuality&rtype, eUCloudRtcQualityType& Quality);
	virtual void onRtmpStreamingStateChanged(const int 	state, const char* url, int code);

private:
	void dispatchEvent(int eventid, std::string jsonmsg);

	void* mCallback;
};

#endif
