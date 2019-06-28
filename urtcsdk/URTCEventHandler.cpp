#include "URTCEventHandler.h"
#include "RTCEventDefine.h"
#include "RTCDefine.h"
#include "json/json.h"
#include <windows.h>

URTCEventHandler::URTCEventHandler()
{
	mCallback = nullptr;
}

URTCEventHandler::~URTCEventHandler() 
{
	mCallback = nullptr;
}
void URTCEventHandler::initEventHandler(void* callback)
{
	mCallback = callback;
}
void URTCEventHandler::onServerDisconnect()
{
	dispatchEvent(URTC_EVENT_MSG_ONSERVERDIS,"" );
}

void URTCEventHandler::onJoinRoom(int code, const char* msg, const char* uid, const char* roomid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;

	dispatchEvent(URTC_EVENT_MSG_JOINROOM_RSP, writer.write(jsonmsg));
}
void URTCEventHandler::onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;

	dispatchEvent(URTC_EVENT_MSG_LEAVEROOM_RSP, writer.write(jsonmsg));
}

void URTCEventHandler::onRejoining(const char* uid, const char* roomid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;

	dispatchEvent(URTC_EVENT_MSG_REJOINING, writer.write(jsonmsg));
}

void URTCEventHandler::onReJoinRoom(const char* uid, const char* roomid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;

	dispatchEvent(URTC_EVENT_MSG_REJOINED, writer.write(jsonmsg));
}

void URTCEventHandler::onRemoteUserJoin(const char* uid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["cmd"] = "join";

	dispatchEvent(URTC_EVENT_MSG_REMOTEUSERJOIN, writer.write(jsonmsg));
}

void URTCEventHandler::onRemoteUserLeave(const char* uid, int reson)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["cmd"] = "leave";
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["reson"] = reson;

	dispatchEvent(URTC_EVENT_MSG_REMOTEUSERLEAVE, writer.write(jsonmsg));
}

void URTCEventHandler::onRemotePublish(tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["cmd"] = "add";
	jsonmsg["data"]["uid"] = info.mUserId;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["audio"] = info.mEnableAudio;
	jsonmsg["data"]["video"] = info.mEnableVideo;
	jsonmsg["data"]["data"] = info.mEnableData;

	dispatchEvent(URTC_EVENT_MSG_REMOTEPUBLISH, writer.write(jsonmsg));
}

void URTCEventHandler::onRemoteUnPublish(tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["cmd"] = "remove";
	jsonmsg["data"]["uid"] = info.mUserId;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["audio"] = info.mEnableAudio;
	jsonmsg["data"]["video"] = info.mEnableVideo;
	jsonmsg["data"]["data"] = info.mEnableData;

	dispatchEvent(URTC_EVENT_MSG_REMOTEUNPUBLISH, writer.write(jsonmsg));
}

void URTCEventHandler::onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;

	dispatchEvent(URTC_EVENT_MSG_LOCALPUBLISH_RSP, writer.write(jsonmsg));
	
}

void URTCEventHandler::onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;

	dispatchEvent(URTC_EVENT_MSG_LOCALUNPUBLISH_RSP, writer.write(jsonmsg));
}

void URTCEventHandler::onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["uid"] = info.mUserId;

	dispatchEvent(URTC_EVENT_MSG_REMOTESUB_RSP, writer.write(jsonmsg));
}

void URTCEventHandler::onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;

	dispatchEvent(URTC_EVENT_MSG_REMOTEUNSUBE_RSP, writer.write(jsonmsg));
}

void URTCEventHandler::onLocalStreamMuteRsp(const int code, const char* msg,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;

	dispatchEvent(URTC_EVENT_MSG_LOCALSTREAMMUTE_RSP, writer.write(jsonmsg));
}
void URTCEventHandler::onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;

	dispatchEvent(URTC_EVENT_MSG_REMOTESTREAMMUTE_RSP, writer.write(jsonmsg));
}

void URTCEventHandler::onRemoteTrackNotify(const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;

	dispatchEvent(URTC_EVENT_MSG_REMOTETRACKST, writer.write(jsonmsg));
}

void URTCEventHandler::onError(int code)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;

	dispatchEvent(URTC_EVENT_MSG_ERRORMSG, writer.write(jsonmsg));
}

void URTCEventHandler::onKickoff(int code)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;

	dispatchEvent(URTC_EVENT_MSG_KICKOFF, writer.write(jsonmsg));
}
void URTCEventHandler::onStartRecord(const int code, const char* msg, const char* recordid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["recordid"] = recordid;

}

void URTCEventHandler::onStopRecord(const int code, const char* msg, const char* recordid)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
}


void URTCEventHandler::onRemoteAudioLevel(const char* uid, int volume)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["vol"] = volume;

	dispatchEvent(URTC_EVENT_MSG_REMOTE_AUDIOVOL, writer.write(jsonmsg));
}

void URTCEventHandler::onLocalAudioLevel(int volume)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["vol"] = volume;

	dispatchEvent(URTC_EVENT_MSG_LOCAL_AUDIOVOL, writer.write(jsonmsg));
}

void URTCEventHandler::onSendRTCStats(tUCloudRtcStreamStats& rtstats)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["mtype"] = rtstats.mStreamMtype;
	jsonmsg["data"]["ttype"] = rtstats.mTracktype;
	if (rtstats.mTracktype == UCLOUD_RTC_TRACKTYPE_AUDIO)
	{
		jsonmsg["data"]["bitrate"] = rtstats.mAudioBitrate;
		jsonmsg["data"]["lostrate"] = rtstats.mPacketLostRate;
	}
	else
	{
		jsonmsg["data"]["bitrate"] = rtstats.mVideoBitrate;
		jsonmsg["data"]["lostrate"] = rtstats.mPacketLostRate;
		jsonmsg["data"]["height"] = rtstats.mVideoHeight;
		jsonmsg["data"]["width"] = rtstats.mVideoWidth;
		jsonmsg["data"]["framerate"] = rtstats.mVideoFrameRate;
	}

	dispatchEvent(URTC_EVENT_MSG_LOCAL_ST_UPDATE, writer.write(jsonmsg));
}

void URTCEventHandler::onRemoteRTCStats(tUCloudRtcStreamStats rtstats)
{
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = rtstats.mUserId;
	jsonmsg["data"]["mtype"] = rtstats.mStreamMtype;
	jsonmsg["data"]["ttype"] = rtstats.mTracktype;
	if (rtstats.mTracktype == UCLOUD_RTC_TRACKTYPE_AUDIO)
	{
		jsonmsg["data"]["bitrate"] = rtstats.mAudioBitrate;
		jsonmsg["data"]["lostrate"] = rtstats.mPacketLostRate;
	}
	else
	{
		jsonmsg["data"]["bitrate"] = rtstats.mVideoBitrate;
		jsonmsg["data"]["lostrate"] = rtstats.mPacketLostRate;
		jsonmsg["data"]["height"] = rtstats.mVideoHeight;
		jsonmsg["data"]["width"] = rtstats.mVideoWidth;
		jsonmsg["data"]["framerate"] = rtstats.mVideoFrameRate;
	}

	dispatchEvent(URTC_EVENT_MSG_REMOTE_ST_UPDATE, writer.write(jsonmsg));
}

void URTCEventHandler::dispatchEvent(int eventid, std::string jsonmsg)
{
	if (mCallback)
	{
		tEventMsg* eventmsg = new tEventMsg;
		eventmsg->mEventid = eventid;
		eventmsg->mJsonMsg = jsonmsg;

		HWND msgwnd = (HWND)mCallback;
		PostMessage(msgwnd, RTC_EVENT_UCLOUD, (WPARAM)eventmsg, 0);
	}
	
}