// interfalce desc
#ifndef _UCLOUD_RTC_ENGINE_SDK_H_
#define _UCLOUD_RTC_ENGINE_SDK_H_

#include "UCloudRtcComDefine.h"

class UCloudRtcEventListener
{
public:
	virtual void onServerDisconnect() {}
	///���뷿��ص�
	///@param code ������  0�ɹ�
	///@param msg ������Ϣ
	///@param uid �û�id
	///@param roomid ����id
	virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) {}

	///�뿪����ص�
	///@param code ������  0�ɹ�
	///@param msg ������Ϣ
	///@param uid �û�id
	///@param roomid ����id
	virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}

	///���������ص�
	///@param uid �û�id
	///@param roomid ����id
	virtual void onRejoining(const char* uid, const char* roomid) {}

	///���¼��뷿��ɹ��ص�
	///@param uid �û�id
	///@param roomid ����id
	virtual void onReJoinRoom(const char* uid, const char* roomid) {}

	///�����������ص�
	///@param code ������  0 succ
	///@param msg ���ط���������Ϣ
	///@param info �����ɹ��󱾵�����Ϣ
	virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	///������ȡ�������ص�
	///@param code ������  0 succ
	///@param msg ���ط���������Ϣ
	///@param info ȡ�������ɹ��󱾵�����Ϣ
	virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	///Զ���û�����ص�
	///@param uid Զ���û�id
	virtual void onRemoteUserJoin(const char* uid) {}

	///Զ���û��뿪�ص�
	///@param uid Զ���û�id
	///@param reson �뿪ԭ��
	virtual void onRemoteUserLeave(const char* uid, int reson) {}

	///Զ���������ص�
	///@param info Զ������Ϣ
	virtual void onRemotePublish(tUCloudRtcStreamInfo& info) {}

	///Զ����ȡ�������ص�
	///@param info Զ������Ϣ
	virtual void onRemoteUnPublish(tUCloudRtcStreamInfo& info) {}

	///���Ļص�
	///@param code ���Ľ�� 0 succ
	///@param msg ������ʾ��Ϣ
	///@param info ��������Ϣ
	virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	///ȡ�����Ļص�
	///@param code ȡ�����Ľ�� 0 succ
	///@param msg ������ʾ��Ϣ
	///@param info ��������Ϣ
	virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	///����mute�ص�
	///@param code mute�ص���� 0 succ
	///@param msg  ��ʾ��Ϣ
	///@param mediatype ý������
	///@param tracktype track����
	///@param mute mute״̬
	virtual void onLocalStreamMuteRsp(const int code, const char* msg,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}

	///Զ��mute�ص�
	///@param code mute�ص���� 0 succ
	///@param msg  ��ʾ��Ϣ
	///@param uid  Զ���û�id
	///@param mediatype ý������
	///@param tracktype track����
	///@param mute mute״̬
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}

	///Զ����Ƶ�������Ƶ��״̬�ص�
	///@param uid  Զ���û�id
	///@param mediatype ý������
	///@param tracktype track����
	///@param mute mute״̬
	virtual void onRemoteTrackNotify(const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}

	///����¼�ƻص�
	///@param code  0 succ
	///@param msg ������ʾ��Ϣ
	///@param info ¼����Ϣ
	virtual void onStartRecord(const int code, const char* msg, tUCloudRtcRecordInfo& info) {}

	///ֹͣ¼�ƻص�

	///@param code  0 succ 0��������ֹͣ�ɹ� ��0�����쳣ֹͣ��Ҫ���¿���
	///@param msg ������ʾ��Ϣ
	///@param recordid ¼��ID
	virtual void onStopRecord(const int code, const char* msg, const char* recordid) {}

	///��������ͳ�ƻص�
	///@param rtstats ͳ����Ϣ
	virtual void onSendRTCStats(tUCloudRtcStreamStats& rtstats) {}

	///Զ������ͳ�ƻص�
	///@param rtstats ͳ����Ϣ
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats) {}

	///Զ����Ƶ�����ص�
	///@param uid �û�ID
	///@param volume ������С
	virtual void onRemoteAudioLevel(const char* uid, int volume) {}

	///�������ֻص�
	///@param uid �û�ID
	///@param rtype ��������������
	///@param Quality ����
	virtual void onNetworkQuality(const char* uid, eUCloudRtcNetworkQuality&rtype, eUCloudRtcQualityType& Quality) {}

	///����״̬�ص�
	///@param state rtmp״̬
	///@param url cdn��ַ
	///@param code ������
	virtual void onRtmpStreamingStateChanged(const int 	state, const char* url, int code) {};

	///���Ƹ��»�����ص�
	///@param cmd ��������
	///@param code ������
	///@param msg ������Ϣ
	virtual void onRtmpUpdateMixStreamRes(eUCloudRtmpOpration& cmd,const int code, const char* msg) {};

	///�豸����ص�
	///@param code �豸����ص�
	virtual void onCaptureError(const int code, const int detail) {}

	///������Ƶ�����ص�
	///@param volume ������С
	virtual void onLocalAudioLevel(int volume) {}


	///Զ����Ƶ������֡�ص�
	///@param uid �û�id
	///@param elapsed �Ӽ��뷿�䵽�յ�Զ����Ƶ�����ʱ��
	virtual void onFirstRemoteAudioFrame(const char* uid, int elapsed) {}


	///Զ����Ƶ��֡�ص�
	///@param uid �û�id
	///@param width ���
	///@param height �߶�
	///@param elapsed �Ӽ��뷿�䵽�յ�Զ����Ƶ��Ⱦ�����ʱ��
	virtual void onFirstRemoteVideoFrame(const char* uid, int width, int height, int elapsed) {}

	///�Զ�����Ϣ�ӿڷ��ͽ��
	/// @param code ����
	/// @param msg 
	virtual void onSendMsgRsp(int code, const char*msg) {};

	///�㲥��Ϣ֪ͨ
	///@param uid �û�id
	///@param msg �û���Ϣ
	virtual void onBroadMsgNotify(const char*uid, const char*msg) {};

	///����֪ͨ
	///@param code ������
	virtual void onKickoff(int code) {}

	///����ص�
	///@param warn ������
	virtual void onWarning(int warn) {}

	///����ص�
	///@param error ������
	virtual void onError(int error) {}
};

class _EXPORT_API UCloudRtcEngine
{
public:
	///��������
	///@param bIsInline �Ƿ�����Բɼ�
	///@return ��������engine
	static UCloudRtcEngine *sharedInstance(bool bIsInline = true);
	static UCloudRtcEngine *sharedInstance(tUCloudRtcInitContext* context);

	///��������
	static void destroy();	

    ///��ȡsdk�汾
    ///@return sdk�汾��
    virtual const char *getSdkVersion() = 0;

	///ע�����
	///@param listener �����Իص��ӿڵ�ʵ��
	virtual void regRtcEventListener(UCloudRtcEventListener* listener) = 0;

	///����sdkģʽ
	///@param mode sdkʹ��ģʽ ��ʽģʽ ����ģʽ
	///@return 0 succ
	virtual int setSdkMode(eUCloudRtcSdkMode mode) = 0;

	///���ý��뷽ʽ
	///@param from ���������
	///@return 0 succ
	virtual int setServerGetFrom(eUCloudServerGetFrom from) = 0;

	///����Ƶ�����
	///@param roomtype �������� ��� С��
	///@return 0 succ
	virtual int setChannelType(eUCloudRtcChannelType roomtype) = 0;

	///���ý�ɫ
	///@param role ���� ���� ������
	///@return 0 succ
	virtual int setStreamRole(eUCloudRtcUserStreamRole role) = 0;

	///������־����
	///@param level ��־����
	virtual void setLogLevel(eUCloudRtcLogLevel level) = 0;

	///����key
	///@param seckey ��������̨��appkey
	virtual void setTokenSecKey(const char* seckey) = 0;

	///�����Զ�����
	///@param autoPub �Զ�����
	///@param autoSub �Զ�����
	///@return 0 succ
	virtual int setAutoPublishSubscribe(bool autoPub, bool autoSub) = 0;


	///�����Ƿ���Ƶ
	///@param audioOnly �Ƿ���Ƶ
	///@return 0 succ
	virtual int setAudioOnlyMode(bool audioOnly) = 0;

	///���ñ���
	///@param codec ��������
	///@return 0 succ
	virtual int setVideoCodec(eUCloudRtcVideoCodec codec) = 0;

	///�÷�������ע�������۲�������
	///@param codec ��������
	virtual void registerAudioFrameObserver(UCloudIAudioFrameObserver *observer) = 0;

	///�÷�������ע����Ƶ�۲�������
	///@param codec ��������
	virtual void registerVideoFrameObserver(UCloudIVideoFrameObserver *observer) = 0;

	///����rtsp����
	///@param type ý������
	///@param enable �Ƿ�ʹ����չrtsp��
	///@param rtspurl rtsp��ַ
	///@return 0 succ
	virtual int enableExtendRtspVideocapture(eUCloudRtcMeidaType type, bool enable, const char* rtspurl) = 0;
	
	///�����ⲿ�ɼ���Ƶ
	///@param enable �Ƿ�ʹ����չ���ⲿ�ɼ�����ͷ
	///@param videocapture �ⲿ��ƵԴ
	///@return 0 succ
	virtual int enableExtendVideocapture(bool enable, UCloudRtcExtendVideoCaptureSource* videocapture) = 0;
	
	///��ʼ���ⲿ��ƵԴ
	///@param audiocapture �ⲿ��ƵԴ
	///@return 0 succ
	virtual int initExtendAudioSource(UCloudRtcExtendAudioCaptureSource* audiocapture) = 0;

	///�����ⲿ�ɼ���Ƶ
	///@param enable �Ƿ�ʹ����չ���ⲿ�ɼ���Ƶ
	///@param audiocapture �ⲿ��ƵԴ(note :�����ȳ�ʼ��initExtendAudioSourceһ��)
	///@return 0 succ
	virtual int enableExtendAudiocapture(bool enable, UCloudRtcExtendAudioCaptureSource* audiocapture) = 0;
	
	///��������
	///@param filepath �ļ�·��
	///@param replace �Ƿ������˷�
	///@param loop �Ƿ�ѭ��
	///@param musicvol ����
	///@return 0 succ
	virtual int startAudioMixing(const char* filepath, bool replace, bool loop, float musicvol) = 0;
	
	///ֹͣ����
	///@return 0 succ
	virtual int stopAudioMixing() = 0;
	
	///ע����Ƶ���ջص�
	///@param callback ������UCloudRtcAudioFrameCallback ��ʵ�� (note :��setChanleType�����)
	///@return 0 succ
	virtual void regAudioFrameCallback(UCloudRtcAudioFrameCallback* callback) = 0;
	
	///ע���豸���֪ͨ�ص�
	///@param callback ������UcloudRtcDeviceChanged ��ʵ��
	///@return 0 succ
	virtual void regDeviceChangeCallback(UcloudRtcDeviceChanged* callback) = 0;
	
	///���뷿��
	///@param auth ��Ȩ��Ϣ
	///@return 0 succ
	virtual int joinChannel(tUCloudRtcAuth& auth) = 0;
	
	///�뿪����
	///@return 0 succ
	virtual int leaveChannel() = 0;
	
	///��ȡ������Ŀ
	///@return ��Ŀ
	virtual int getDesktopNums() = 0;
	
	///��ȡ������Ϣ
	///@param pos λ��
	///@param [out] info ������Ϣ
	///@return 0 succ
	virtual int getDesktopInfo(int pos, tUCloudRtcDeskTopInfo& info) = 0;
	
	///��ȡ������Ŀ
	virtual int getWindowNums() = 0;
	
	///��ȡ���洰����Ϣ
	///@param pos λ��
	///@param [out] info ������Ϣ
	///@return 0 succ
	virtual int getWindowInfo(int pos, tUCloudRtcDeskTopInfo& info) = 0;
	
	///���������������
	///@param desktoptype ׿������
	///@return 0 succ
	virtual int setUseDesktopCapture(eUCloudRtcDesktopType desktoptype) = 0;

	///�����������profile
	///@param profile �ֱ���
	virtual void setDesktopProfile(eUCloudRtcScreenProfile profile) = 0;

	///��������������
	///@param pgram �������
	virtual void setCaptureScreenPagrams(tUCloudRtcScreenPargram& pgram) = 0;

	///���ü��뷿��ǰ�Ƿ�������ͷ
	///@param mute �Ƿ������Ƶ  true����ֹ false:��
	///@return 0 succ
	virtual int muteCamBeforeJoin(bool mute) = 0;

	///���ü��뷿��ǰ�Ƿ�mute mic
	///@param mute �Ƿ����mic  true����ֹ false:��
	///@return 0 succ
	virtual int muteMicBeforeJoin(bool mute) = 0;

	///���ö��ĳɹ����Ƿ�mute����ͷ
	///@param mute �Ƿ������Ƶ  true����ֹ false:��
	///@return 0 succ
	virtual int muteRomoteCamBeforeSub(bool mute) = 0;

	///���ö��ĳɹ����Ƿ�mute mic
	///@param mute �Ƿ����mic  true����ֹ false:��
	///@return 0 succ
	virtual int muteRomoteMicBeforeSub(bool mute) = 0;

	///���ñ��뷢����Ƶ����
	///@param profile �ֱ���
	///@param videoconfig video����
	virtual void setVideoProfile(eUCloudRtcVideoProfile profile, tUCloudVideoConfig& videoconfig) = 0;
	
	///���òɼ���Ⱦ��Ƶ�ֱ���
	///@param profile �ֱ���
	///@param videoconfig video����
	virtual void setVideoCaptureProfile(eUCloudRtcVideoProfile profile) = 0;
	
	///�л�����ͷ
	///@param info �豸��Ϣ
	///@return 0 succ
	virtual int switchCamera(tUCloudRtcDeviceInfo& info) = 0;

    ///���ر�����Ƶ�ɼ�
    ///@param enable �����رձ�����Ƶ�ɼ�
    ///@return 0 succ
    virtual int enableLocalCamera(bool enable) = 0;

	///����
	///@param type ý������ ����ͷ��������
	///@param hasvideo �Ƿ����Ƶ
	///@param hasaudio �Ƿ����Ƶ
	///@return 0 succ
	virtual int publish(eUCloudRtcMeidaType type, bool hasvideo, bool hasaudio) = 0;

	///ȡ������
	///@param type ý������
	///@return 0 succ
	virtual int unPublish(eUCloudRtcMeidaType type) = 0;

	///��ʼԤ��
	///@param view Ԥ����veiw��Ϣ
	///@return 0 succ
	virtual int startPreview(tUCloudRtcVideoCanvas& view) = 0;

	///ֹͣԤ��
	///@param view Ԥ����veiw��Ϣ
	///@return 0 succ
	virtual int stopPreview(tUCloudRtcVideoCanvas& view) = 0;

	///mute�������
	///@param mute true:�� false:��
	///@return 0 succ
	virtual int muteLocalMic(bool mute, eUCloudRtcMeidaType streamtype = UCLOUD_RTC_MEDIATYPE_VIDEO) = 0;

	///mute������Ƶ
	///@param mute true:�� false:��
	///@param streamtype ý������ 
	///@return 0 succ
	virtual int muteLocalVideo(bool mute, eUCloudRtcMeidaType streamtype) = 0;

	///����
	///@param info:���ĵ���
	///@return 0 succ
	virtual int subscribe(tUCloudRtcStreamInfo& info) = 0;

	///ȡ������
	///@param info:ȡ�����ĵ���
	///@return 0 succ
	virtual int unSubscribe(tUCloudRtcStreamInfo& info) = 0;


	///����Զ����Ⱦ
	///@param view:����Զ����Ⱦ����ͼ��Ϣ
	///@return 0 succ
	virtual int startRemoteView(tUCloudRtcVideoCanvas& view) = 0;


	///ֹͣԶ����Ⱦ
	///@param view:��ͼ��Ϣ
	///@return 0 succ
	virtual int stopRemoteView(tUCloudRtcVideoCanvas& view) = 0;

	///muteԶ����Ƶ
	///@param info:mute����Ϣ
	///@param info:mute true:�� false:��
	///@return 0 succ
	virtual int muteRemoteAudio(tUCloudRtcMuteSt& info, bool mute) = 0;


	///mute Զ����Ƶ
	///@param info:mute����Ϣ
	///@param info:mute true:�� false:��
	///@return 0 succ
	virtual int muteRemoteVideo(tUCloudRtcMuteSt& info, bool mute) = 0;


	///�Ƿ�������
	///@param enable true:�� false:��
	///@return 0 succ
	virtual int enableAllAudioPlay(bool enable) = 0;


	///��ʼ¼��
	///@param recordconfig ¼������
	///@return 0 succ
	virtual int startRecord(tUCloudRtcRecordConfig& recordconfig) = 0;

	///ֹͣ¼��
	///@return 0 succ
	virtual int stopRecord() = 0;

	///��������ͷ�Ƿ���
	///@param enable true:�� false:��
	///@return 0 succ
	virtual int configLocalCameraPublish(bool enable) = 0;

	///��������ͷ�Ƿ���
	///@return true false
	virtual bool isLocalCameraPublishEnabled() = 0;

	///���÷������濪��
	///@param enable true:�� false:��
	///@return 0 succ
	virtual int configLocalScreenPublish(bool enable) = 0;

	///���������Ƿ���
	///@return true false
	virtual bool isLocalScreenPublishEnabled() = 0;

	///���ñ�����Ƶ����
	///@param enable true:�� false:��
	///@return 0 succ
	virtual int configLocalAudioPublish(bool enable) = 0;

	///���ط����Ƿ��ֹ
	///@return true false
	virtual bool isLocalAudioPublishEnabled() = 0;

	///�Ƿ��Զ�����
	///@return true false
	virtual bool isAutoPublish() = 0;

	///�Ƿ��Զ�����
	///@return true false
	virtual bool isAutoSubscribe() = 0;

	///�Ƿ���Ƶ
	///@return true false
	virtual bool isAudioOnly() = 0;

	///��·����
	///@param url cdn��ַ
	///@param config ת������(note: ��ʼģ����Զ�ѡ��mlayouts[0]�������б����֧��3���ڷ������л�)
	///@return 0 succ
	virtual int addPublishStreamUrl(const char* url, tUCloudRtcTranscodeConfig *config) = 0;

	///����ת������
	///@param url cdn ��ַ
	///@param ת�Ƹ�������
	///@return 0 succ
	virtual int updateTranscodeConfig(const char* url, tUCloudRtcTranscodeConfig *config) = 0;

	///ֹͣ��·����
	///@param url cdn��ַ
	///@return 0 succ
	virtual int removePublishStreamUrl(const char* url) = 0;


	///������·������������
	///@param cmd rtmp��������
	///@param streams ת�Ƶ�������
	///@param streams ת�Ƶ�������
	///@return 0 succ
	virtual int updateRtmpMixStream(eUCloudRtmpOpration cmd, tUCloudRtcRelayStream* streams,int length) = 0;

	///����mute���ˮӡͼ yuv420��ʽ �ڲ��Զ����� 
	///@param rgb��ʽ���ֽ�����
	///@param ����
	///@return 0 succ
	virtual int setMuteBackImage(const unsigned char* image,const int width,const int height) = 0;

	///����ϵͳ�ɼ���
	///@param enabe true:���� fasle:�ر�
	///@return 0 succ
	virtual int enableCapturePlayBack(bool enable) = 0;



	///�����Զ�����Ϣ
	virtual int sendMessage(const char*msg) = 0;

	///��ȡ�����ļ�������ʱ��
	virtual int getAudioMixingDuration() = 0;

	///��ȡ������ǰ���Ž���
	virtual int getAudioMixingCurrentPosition() = 0;

	///�ָ���ǰ����
	virtual int resumeAudioMixing() = 0;

	///��ͣ��ǰ����
	virtual int pauseAudioMixing() = 0;

	///���ò��Ž���
	virtual int setAudioMixingPosition(int) = 0;

	///���»�������
	virtual int updateAudioMixingVolume(int) = 0;

    ///����һ֡�ⲿ�ɼ�����Ƶ���ݸ�SDK
    ///@param video ��Ƶ����
    ///@return 0 succ
    virtual int pushVideoFrameData(tUCloudRtcVideoFrame *video) = 0;

    ///����һ֡�ⲿ�ɼ�����Ƶ���ݸ�SDK
    ///@param audio ��Ƶ����
    ///@return 0 succ
    virtual int pushAudioFrameData(tUCloudRtcAudioFrame *audio) = 0;

    ///�����ⲿ�ɼ����ݵĻ�ȡ��ʽ 
    ///@param mode  UCloud_EMDM_PUSH���������ݸ�sdk   UCloud_EMDM_PULL��SDK������
    ///@return 0 succ
    virtual int SetExtendMediaDataMode(eUCloudExtendMediaDataMode mode) = 0;

    ///������Ƶ�ı�������
    ///@param audio_profile  UCloud_Audio_Profile_Default����ͨ��������  UCloud_Audio_Profile_Music ������ģʽ
    ///@return 0 succ
    virtual int setAudioProfile(eUCloudAudioProfile audio_profile) = 0;

    ///���������ӳ�ʱ��
    ///@param delay_ms �ӳ�ʱ�䣬 ��λms
    ///@return 0 succ
    virtual int setAudioDelayTime(int delay_ms) = 0;
	
	//¼��
	virtual const char* acquire(const char* jsonobj) = 0;
	virtual const char* startMix(const char* jsonobj) = 0;
	virtual const char* stopMix(const char* jsonobj) = 0;
	virtual const char* queryMix(const char* jsonobj) = 0;
	virtual const char* updateMix(const char* jsonobj) = 0;

	virtual const char* getTestToken(const char* appid, const char* uid, const char* rid) = 0;
};

_EXPORT_API_C UCloudRtcEngine* getUCloudRtcEngineInterface(tUCloudRtcInitContext* context);
_EXPORT_API_C void releaseUCloudRtcEngineInterface(UCloudRtcEngine** engine);
#endif
