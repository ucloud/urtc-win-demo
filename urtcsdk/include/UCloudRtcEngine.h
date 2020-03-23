// interfalce desc
#ifndef _UCLOUD_RTC_ENGINE_SDK_H_
#define _UCLOUD_RTC_ENGINE_SDK_H_

#include "UCloudRtcComDefine.h"

class  _EXPORT_API UCloudRtcEventListener
{
public:
	virtual void onServerDisconnect() {}
	//加入房间回调
	virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) {}
	//离开房间回调
	virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}
	//重新加入房间回调
	virtual void onRejoining(const char* uid, const char* roomid) {}
	//重新加入房间成功回调
	virtual void onReJoinRoom(const char* uid, const char* roomid) {}
	//本地流发布回调
	virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	//本地流取消发布回调
	virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	//远端用户加入回调
	virtual void onRemoteUserJoin(const char* uid) {}
	//远端用户离开回调
	virtual void onRemoteUserLeave(const char* uid, int reson) {}
	//远端流发布回调
	virtual void onRemotePublish(tUCloudRtcStreamInfo& info) {}
	//远端流取消发布回调
	virtual void onRemoteUnPublish(tUCloudRtcStreamInfo& info) {}
	//订阅回调
	virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	//取消订阅回调
	virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	//本地mute回调
	virtual void onLocalStreamMuteRsp(const int code, const char* msg,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
	//远端mute回调
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
	//远端音频轨或者视频轨状态回调
	virtual void onRemoteTrackNotify(const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
	//开启录制回调
	virtual void onStartRecord(const int code, const char* msg, tUCloudRtcRecordInfo& info) {}
	//停止录制回调
	virtual void onStopRecord(const int code, const char* msg, const char* recordid) {}
	//本地数据统计回调
	virtual void onSendRTCStats(tUCloudRtcStreamStats& rtstats) {}
	//远端数据统计回调
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats) {}
	//远端音频能量回调
	virtual void onRemoteAudioLevel(const char* uid, int volume) {}
	//网络评分回调
	virtual void onNetworkQuality(const char* uid, eUCloudRtcNetworkQuality&rtype, eUCloudRtcQualityType& Quality) {}
	//旁推状态回调
	virtual void onRtmpStreamingStateChanged(const int 	state, const char* url, int code) {};
	//旁推更新混合流回调
	virtual void onRtmpUpdateMixStreamRes(eUCloudRtmpOpration& cmd,const int code, const char* msg) {};
	//本地音频能量回调
	virtual void onLocalAudioLevel(int volume) {}
	//踢人通知
	virtual void onKickoff(int code) {}
	//警告回调
	virtual void onWarning(int warn) {}
	//错误回调
	virtual void onError(int error) {}
};

class _EXPORT_API UCloudRtcEngine
{
public:
	//创建引擎
	static UCloudRtcEngine *sharedInstance(bool bIsInline = true);
	//销毁引擎
	static void destroy();
	//获取sdk版本
	static const char *getSdkVersion();
	//注册监听
	virtual void regRtcEventListener(UCloudRtcEventListener* listener) = 0;
	//设置sdk模式
	virtual int setSdkMode(eUCloudRtcSdkMode mode) = 0;
	//设置频道类别
	virtual int setChannelType(eUCloudRtcChannelType roomtype) = 0;
	//设置角色
	virtual int setStreamRole(eUCloudRtcUserStreamRole role) = 0;
	//设置日志级别
	virtual void setLogLevel(eUCloudRtcLogLevel level) = 0;
	//设置key
	virtual void setTokenSecKey(const char* seckey) = 0;
	//设置自动发布
	virtual int setAutoPublishSubscribe(bool autoPub, bool autoSub) = 0;
	//设置音频自动发布
	virtual int setAudioOnlyMode(bool audioOnly) = 0;
	//设置编码
	virtual int setVideoCodec(eUCloudRtcVideoCodec codec) = 0;
	//开启rtsp推流
	virtual int enableExtendRtspVideocapture(eUCloudRtcMeidaType type, bool enable, const char* rtspurl) = 0;
	//开启外部采集视频
	virtual int enableExtendVideocapture(bool enable, UCloudRtcExtendVideoCaptureSource* videocapture) = 0;
	//开启外部采集音频
	virtual int enableExtendAudiocapture(bool enable, UCloudRtcExtendAudioCaptureSource* audiocapture) = 0;
	//开启混音
	virtual int startAudioMixing(const char* filepath, bool replace, bool loop, float musicvol) = 0;
	//停止混音
	virtual int stopAudioMixing() = 0;
	//注册音频接收回调
	virtual void regAudioFrameCallback(UCloudRtcAudioFrameCallback* callback) = 0;
	//注册设备插拔通知回调
	virtual void regDeviceChangeCallback(UcloudRtcDeviceChanged* callback) = 0;
	//加入房间
	virtual int joinChannel(tUCloudRtcAuth& auth) = 0;
	//离开房间
	virtual int leaveChannel() = 0;
	//获取桌面数目
	virtual int getDesktopNums() = 0;
	//获取桌面信息
	virtual int getDesktopInfo(int pos, tUCloudRtcDeskTopInfo& info) = 0;
	//获取窗口数目
	virtual int getWindowNums() = 0;
	//获取桌面窗口信息
	virtual int getWindowInfo(int pos, tUCloudRtcDeskTopInfo& info) = 0;
	//设置桌面分享类型
	virtual int setUseDesktopCapture(eUCloudRtcDesktopType desktoptype) = 0;
	//设置桌面分享profile
	virtual void setDesktopProfile(eUCloudRtcScreenProfile profile) = 0;
	//设置桌面分享参数
	virtual void setCaptureScreenPagrams(tUCloudRtcScreenPargram& pgram) = 0;
	//设置加入房间前是否开启摄像头
	virtual int muteCamBeforeJoin(bool mute) = 0;
	//设置加入房间前是否mute mic
	virtual int muteMicBeforeJoin(bool mute) = 0;
	//设置视频质量
	virtual void setVideoProfile(eUCloudRtcVideoProfile profile, tUCloudVideoConfig& videoconfig) = 0;
	//切换摄像头
	virtual int switchCamera(tUCloudRtcDeviceInfo& info) = 0;
	//发布
	virtual int publish(eUCloudRtcMeidaType type, bool hasvideo, bool hasaudio) = 0;
	//取消发布
	virtual int unPublish(eUCloudRtcMeidaType type) = 0;
	//开始预览
	virtual int startPreview(tUCloudRtcVideoCanvas& view) = 0;
	//停止预览
	virtual int stopPreview(tUCloudRtcVideoCanvas& view) = 0;
	//mute本地麦克
	virtual int muteLocalMic(bool mute) = 0;
	//mute本地音频
	virtual int muteLocalVideo(bool mute, eUCloudRtcMeidaType streamtype) = 0;
	//订阅
	virtual int subscribe(tUCloudRtcStreamInfo& info) = 0;
	//取消订阅
	virtual int unSubscribe(tUCloudRtcStreamInfo& info) = 0;
	//开启远端渲染
	virtual int startRemoteView(tUCloudRtcVideoCanvas& view) = 0;
	//停止远端渲染
	virtual int stopRemoteView(tUCloudRtcVideoCanvas& view) = 0;
	//mute远端音频
	virtual int muteRemoteAudio(tUCloudRtcMuteSt& info, bool mute) = 0;
	//mute 远端视频
	virtual int muteRemoteVideo(tUCloudRtcMuteSt& info, bool mute) = 0;
	//开启所以音频播放
	virtual int enableAllAudioPlay(bool enable) = 0;
	//开始录制
	virtual int startRecord(tUCloudRtcRecordConfig& recordconfig) = 0;
	//停止录制
	virtual int stopRecord() = 0;
	//设置摄像头是否开启
	virtual int configLocalCameraPublish(bool enable) = 0;
	//本地摄像头是否开启
	virtual bool isLocalCameraPublishEnabled() = 0;
	//设置分享桌面开启
	virtual int configLocalScreenPublish(bool enable) = 0;
	//分享桌面是否开启
	virtual bool isLocalScreenPublishEnabled() = 0;
	//配置本地音频发布
	virtual int configLocalAudioPublish(bool enable) = 0;
	//本地发布是否禁止
	virtual bool isLocalAudioPublishEnabled() = 0;
	//是否自动发布
	virtual bool isAutoPublish() = 0;
	//是否自动订阅
	virtual bool isAutoSubscribe() = 0;
	//是否纯音频
	virtual bool isAudioOnly() = 0;
	//旁路推流
	virtual int addPublishStreamUrl(const char* url, tUCloudRtcTranscodeConfig *config) = 0;
	//停止旁路推流
	virtual int removePublishStreamUrl(const char* url) = 0;
	//更新旁路推流合流的流
	virtual int updateRtmpMixStream(eUCloudRtmpOpration cmd, tUCloudRtcRelayStream* streams,int length) = 0;
protected:
	virtual ~UCloudRtcEngine() {}
};

#endif
