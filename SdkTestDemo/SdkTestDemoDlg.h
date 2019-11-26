
// SdkTestDemoDlg.h : 头文件
//

#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>

#include "VideoWnd.h"
#include "VideoFullDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "RTCEngineFactory.h"
#include "VideoPackageQueue.h"
#include "UCloudRtcComDefine.h"
#include "UCloudRtcMediaDevice.h"


// CSdkTestDemoDlg 对话框
class CSdkTestDemoDlg : 
	public CDialogEx, 
	public CVideoWndCallback,
	public UCloudRtcVideoFrameObserver,
	public UCloudRtcExtendVideoCaptureSource
{
// 构造
public:
	CSdkTestDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

	//cvideowndcallback
	void OnMuteAudio(std::string userid, eUCloudRtcMeidaType mediatype, bool mute);
	void OnMuteVideo(std::string userid, eUCloudRtcMeidaType mediatype, bool mute);
	void OnCloseMedia(std::string type, std::string id);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_SFU};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg LRESULT OnRTCUCloudMsg(WPARAM data, LPARAM lp);
	afx_msg LRESULT OnVideoFrameCallback(WPARAM data, LPARAM lp);

	afx_msg void OnBnClickedButtonPubC();
	afx_msg void OnBnClickedButtonLeaveroom();
	afx_msg void OnBnClickedButtonPubs();

	//ucloudrtcvideoframeobserver
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen);

	//extendcapture
	virtual  bool doCaptureFrame(tUCloudRtcVideoFrame* videoframe);

private:
	CVideoWnd* CreateVideoWindow(eUCloudRtcMeidaType type, int x, int y, int w, int h);

	void InitURTCConfig();

	void OnJoinRoomHandler(std::string jsonmsg);
	void OnReJoinFailHandler(std::string jsonmsg);
	void OnReJoinRoomHandler(std::string jsonmsg);
	void OnLeaveRoomHandler(std::string jsonmsg);

	void OnPulibshStreamHandler(std::string jsonmsg);
	void OnPulibshCamStreamHandler(std::string jsonmsg);
	void OnPulibshScreenStreamHandler(std::string jsonmsg);

	void OnUnPulibshStreamHandler(std::string jsonmsg);
	void OnUnPulibshStreamScreenHandler(std::string jsonmsg);
	void OnUnPulibshStreamCamHandler(std::string jsonmsg);

	void OnSubStreamHandler(std::string jsonmsg);
	void OnUnSubStreamHandler(std::string jsonmsg);

	void OnStreamStHandler(std::string jsonmsg);
	void OnUserStHandler(std::string jsonmsg);

	void OnServerReconnectingHandler(std::string jsonmsg);
	void OnServerDisconnectHandler(std::string jsonmsg);

	void OnSdkErrorHandler(std::string jsonmsg);
	void OnKickoffHandler(std::string jsonmsg);

	void OnLocalStreamMuteHandler(std::string jsonmsg);
	void OnRemoteStreamMuteHandler(std::string jsonmsg);
	void OnRemoteTrackStNotify(std::string jsonmsg);

	void OnRemoteAudioVolHandler(std::string jsonmsg);
	void OnLocalAudioVolHandler(std::string jsonmsg);

	void OnRemoteStHandler(std::string jsonmsg);
	void OnSendStHandler(std::string jsonmsg);

	void OnStartRecord(std::string jsonmsg);
	void OnStopRecord(std::string jsonmsg);

	//用户离开 释放所有资源
	void ReleaseUserAllRes();
	void SubscribeAllStream();
	void SubscribeStream(int mediatype, std::string uid);
	void UnSubscribeStream(int mediatype, std::string uid);
	void UserLeave(std::string uid);
	void OnLeaveRoom();
	void OnMessageShow(std::string msg);

public:
	CListBox m_msglist;
	CButton m_videocheck;
	CButton m_audiocheck;

	VideoFullDlg* _pFullScreenDlg;
	RTCEngineBase* m_rtcengine;

	std::string m_userid;      // 自己用户id
	std::string m_roomid;     // roomid
	std::string m_roomtoken; //认证token

	std::map<std::string, tUserInfo*>   m_hashSessions;//userid<---> userinfo
	std::map<std::string, tStreamInfo*> m_streamsmap;//userid+mediatype<---> streaminfo 订阅列表对应
	std::map<std::string, CVideoWnd*>   m_mapRenders; //userid+mediatype<----> videorender
	CVideoWnd *m_localWnd;
	CVideoWnd *m_screenWnd;
	std::list<CVideoWnd*> m_remoteWnds; //所有wnd 预分配
	bool m_campub;
	bool m_screenpub;
	bool m_leaveroom;
	bool m_isclose;
	bool m_startrecord;
	bool m_startaudiomix;
	afx_msg void OnBnClickedButtonRecord();
	afx_msg void OnBnClickedButtonMixfile();
	CEdit m_rtsp1;
	CEdit m_rtsp2;
	unsigned char* m_lpImageBuffer;
	UCloudRtcMediaDevice* m_mediadevice;
};
