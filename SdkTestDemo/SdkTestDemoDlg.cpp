// SdkTestDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SdkTestDemo.h"
#include "SdkTestDemoDlg.h"
#include "afxdialogex.h"
#include "DeviceTestDlg.h"
#include "SdkUtil.h"
#include "json/json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static std::string get_randrom_string(int length)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	srand((unsigned)time(NULL));
	std::string str;
	for (int i = 0; i < length; ++i) {
		str += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return str;
}

#define  TEST_APP_ID "URtc-h4r1txxy"
#define  TEST_SECKEY "9129304dbf8c5c4bf68d70824462409f"
// CSdkTestDemoDlg 对话框
#include <string>
#include <stdint.h>

const int URTC_EVENT_MSG_BASE = WM_USER + 1;
const int URTC_EVENT_MSG_JOINROOM_RSP = URTC_EVENT_MSG_BASE + 1;
const int URTC_EVENT_MSG_LEAVEROOM_RSP = URTC_EVENT_MSG_BASE + 2;
const int URTC_EVENT_MSG_USERJOIN_NOTIFY = URTC_EVENT_MSG_BASE + 3;
const int URTC_EVENT_MSG_REJOINING = URTC_EVENT_MSG_BASE + 4;
const int URTC_EVENT_MSG_ERRORMSG = URTC_EVENT_MSG_BASE + 5;
const int URTC_EVENT_MSG_REMOTEUSERJOIN = URTC_EVENT_MSG_BASE + 6;
const int URTC_EVENT_MSG_REMOTEUSERLEAVE = URTC_EVENT_MSG_BASE + 7;

const int URTC_EVENT_MSG_LOCALPUBLISH_RSP = URTC_EVENT_MSG_BASE + 8;
const int URTC_EVENT_MSG_LOCALUNPUBLISH_RSP = URTC_EVENT_MSG_BASE + 9;
const int URTC_EVENT_MSG_REMOTEPUBLISH = URTC_EVENT_MSG_BASE + 10;
const int URTC_EVENT_MSG_REMOTEUNPUBLISH = URTC_EVENT_MSG_BASE + 11;
const int URTC_EVENT_MSG_REMOTESUB_RSP = URTC_EVENT_MSG_BASE + 12;
const int URTC_EVENT_MSG_REMOTEUNSUBE_RSP = URTC_EVENT_MSG_BASE + 13;
const int URTC_EVENT_MSG_KICKOFF = URTC_EVENT_MSG_BASE + 14;

const int URTC_EVENT_MSG_LOCALSTREAMMUTE_RSP = URTC_EVENT_MSG_BASE + 15;
const int URTC_EVENT_MSG_REMOTESTREAMMUTE_RSP = URTC_EVENT_MSG_BASE + 16;
const int URTC_EVENT_MSG_REMOTETRACKST = URTC_EVENT_MSG_BASE + 17;

const int URTC_EVENT_MSG_REJOINED = URTC_EVENT_MSG_BASE + 18;
const int URTC_EVENT_MSG_REMOTE_AUDIOVOL = URTC_EVENT_MSG_BASE + 19;
const int URTC_EVENT_MSG_LOCAL_AUDIOVOL = URTC_EVENT_MSG_BASE + 20;
const int URTC_EVENT_MSG_REMOTE_ST_UPDATE = URTC_EVENT_MSG_BASE + 21;
const int URTC_EVENT_MSG_LOCAL_ST_UPDATE = URTC_EVENT_MSG_BASE + 22;
const int URTC_EVENT_MSG_ONSERVERDIS = URTC_EVENT_MSG_BASE + 23;

CSdkTestDemoDlg* g_dlg;

typedef std::map<std::string, tUserInfo*>::iterator userit;
typedef std::map<std::string, tStreamInfo*>::iterator streamit;
typedef std::map<std::string, std::string>::iterator userstreammapit;
typedef std::map<std::string, CVideoWnd*>::iterator streamrenderit;
typedef std::list<CVideoWnd*>::iterator videowndit;


CSdkTestDemoDlg::CSdkTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SFU, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_userid = "win_"+get_randrom_string(12);
	m_campub = false;
	m_screenpub = false;
	m_leaveroom = false;
	m_maxretrynum = 3;
	m_nowretry = 0;
	m_isclose = false;
}

void CSdkTestDemoDlg::OnMuteAudio(std::string userid, eUCloudRtcMeidaType mediatype, bool mute) {
	if (userid == "camera")
	{
		m_rtcengine->muteLocalMic(mute);
	}
	else if (userid == "screen")
	{
	}
	else {
		tUCloudRtcMuteSt info;
		info.mUserId = const_cast<char*>(userid.data()) ;
		info.mStreamMtype = mediatype;
		m_rtcengine->muteRemoteAudio(info, mute);
	}
}

void CSdkTestDemoDlg::OnMuteVideo(std::string userid, eUCloudRtcMeidaType mediatype, bool mute) {
	if (userid == "camera")
	{
		m_rtcengine->muteLocalVideo(mute, UCLOUD_RTC_MEDIATYPE_VIDEO);
	}
	else if (userid == "screen")
	{
		m_rtcengine->muteLocalVideo(mute, UCLOUD_RTC_MEDIATYPE_SCREEN);
	}
	else {
		tUCloudRtcMuteSt info;
		info.mUserId = const_cast<char*>(userid.data());
		info.mStreamMtype = mediatype;
		m_rtcengine->muteRemoteVideo(info, mute);
		
	}
}

void CSdkTestDemoDlg::OnClose(std::string type, std::string id) {

}

void CSdkTestDemoDlg::onServerDisconnect()
{
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_ONSERVERDIS;

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_JOINROOM_RSP;

	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);

}
void CSdkTestDemoDlg::onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LEAVEROOM_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRejoining(const char* uid, const char* roomid) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REJOINING;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onReJoinRoom(const char* uid, const char* roomid) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REJOINED;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["roomid"] = roomid;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteUserJoin(const char* uid) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTEUSERJOIN;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["cmd"] = "join";
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteUserLeave(const char* uid, int reson) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTEUSERLEAVE;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["cmd"] = "leave";
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["reson"] = reson;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemotePublish(tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTEPUBLISH;
	Json::StyledWriter writer;
	Json::Value jsonmsg; 
	jsonmsg["data"]["cmd"] = "add";
	jsonmsg["data"]["uid"] = info.mUserId;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["audio"] = info.mEnableAudio;
	jsonmsg["data"]["video"] = info.mEnableVideo;
	jsonmsg["data"]["data"] = info.mEnableData;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteUnPublish(tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTEUNPUBLISH;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["cmd"] = "remove";
	jsonmsg["data"]["uid"] = info.mUserId;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["audio"] = info.mEnableAudio;
	jsonmsg["data"]["video"] = info.mEnableVideo;
	jsonmsg["data"]["data"] = info.mEnableData;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LOCALPUBLISH_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LOCALUNPUBLISH_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTESUB_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	jsonmsg["data"]["uid"] = info.mUserId;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTEUNSUBE_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = info.mStreamMtype;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onLocalStreamMuteRsp(const int code, const char* msg,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LOCALSTREAMMUTE_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}
void CSdkTestDemoDlg::onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTESTREAMMUTE_RSP;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	jsonmsg["msg"] = msg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteTrackNotify(const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTETRACKST;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["mtype"] = mediatype;
	jsonmsg["data"]["ttype"] = tracktype;
	jsonmsg["data"]["mute"] = mute;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onError(int code) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_ERRORMSG;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onKickoff(int code) {
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_KICKOFF;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["code"] = code;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteAudioLevel(const char* uid, int volume)
{
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTE_AUDIOVOL;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["uid"] = uid;
	jsonmsg["data"]["vol"] = volume;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onLocalAudioLevel(int volume)
{
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LOCAL_AUDIOVOL;
	Json::StyledWriter writer;
	Json::Value jsonmsg;
	jsonmsg["data"]["vol"] = volume;
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onSendRTCStats(tUCloudRtcStreamStats& rtstats)
{
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_LOCAL_ST_UPDATE;
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
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::onRemoteRTCStats(tUCloudRtcStreamStats rtstats)
{
	tCallMsg* callmsg = new tCallMsg;
	callmsg->eventid = URTC_EVENT_MSG_REMOTE_ST_UPDATE;
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
	callmsg->msg = writer.write(jsonmsg);

	PostMessage(URTC_EVENT_MSG_BASE, (WPARAM)callmsg, 0);
}

void CSdkTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_msglist);
	DDX_Control(pDX, IDC_CHECK_VIDEO, m_videocheck);
	DDX_Control(pDX, IDC_CHECK_AUDIO, m_audiocheck);
}

CVideoWnd* CSdkTestDemoDlg::CreateVideoWindow(eUCloudRtcMeidaType type, int x, int y, int w, int h) {
	CVideoWnd *pWnd = nullptr;
	pWnd = new CVideoWnd(this);
	pWnd->SetType(type);
	if (!pWnd->Create(IDD_VIDEO_WND, this)) {
		MessageBox(L"Create Failed");
		return FALSE;
	}

	pWnd->MoveWindow(x, y, 240, 240, true);
	pWnd->ShowWindow(SW_SHOW);
	return pWnd;
}


BEGIN_MESSAGE_MAP(CSdkTestDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CSdkTestDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSdkTestDemoDlg::OnBnClickedCancel)
	ON_MESSAGE(URTC_EVENT_MSG_BASE, &CSdkTestDemoDlg::OnCallBackMsg)
	ON_BN_CLICKED(IDC_BUTTON_JOIN, &CSdkTestDemoDlg::OnBnClickedButtonJoin)
	ON_BN_CLICKED(IDC_BUTTON_PUBC, &CSdkTestDemoDlg::OnBnClickedButtonPubC)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEROOM, &CSdkTestDemoDlg::OnBnClickedButtonLeaveroom)
	ON_BN_CLICKED(IDC_BUTTON_PUBS, &CSdkTestDemoDlg::OnBnClickedButtonPubs)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_TEST, &CSdkTestDemoDlg::OnBnClickedButtonDeviceTest)
END_MESSAGE_MAP()


// CSdkTestDemoDlg 消息处理程序
BOOL CSdkTestDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//InitMinDump();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	g_dlg = this;
	SetDlgItemText(IDC_EDIT_USERID, Ansi2WChar(m_userid.data()).data());
	SetDlgItemText(IDC_EDIT_ROOM, L"urtc1");
	GetDlgItem(IDC_EDIT_ROOM)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_JOIN)->EnableWindow(TRUE);

	CRect rcBtn;
	GetDlgItem(IDC_EDIT_USERID)->GetWindowRect(&rcBtn);
	ScreenToClient(rcBtn);
	int y = rcBtn.bottom + 2;

	//本地视频窗口
	m_localWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, 0, y, 240, 240);
	m_localWnd->SetTitle(L"Local (Camera)");
	m_localWnd->SetUserId("camera");
	m_localWnd->RegisterCallback(this);

	//本地桌面窗口
	m_screenWnd  = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_SCREEN, 242, y, 240, 240);
	m_screenWnd->SetTitle(L"Local (Screen)");
	m_screenWnd->SetUserId("screen");
	m_screenWnd->RegisterCallback(this);

	//远端渲染窗口
	for (int i = 2; i <= 3; ++i) {
		CVideoWnd *pWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, 242 * i, y, 240, 240);
		pWnd->RegisterCallback(this);
		m_remoteWnds.emplace_back(pWnd);
	}

	y += 242;
	for (int i = 0; i < 4; ++i) {
		CVideoWnd *pWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, i * 242, y, 240, 240);
		pWnd->RegisterCallback(this);
		m_remoteWnds.emplace_back(pWnd);
	}
	m_audiocheck.SetCheck(1);
	m_videocheck.SetCheck(1);
	m_rtcengine = UCloudRtcEngine::sharedInstance(this);
	m_rtcengine->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_BOTH);
	m_rtcengine->setTokenSecKey(TEST_SECKEY);
	m_rtcengine->setAudioOnlyMode(false);
	m_rtcengine->setAutoPublishSubscribe(false, true);
	m_rtcengine->configLocalAudioPublish(false);
	m_rtcengine->configLocalCameraPublish(true);
	m_rtcengine->configLocalScreenPublish(false);
	if (m_rtcengine->isAutoPublish())
	{
		if (m_rtcengine->isLocalCameraPublishEnabled() || m_rtcengine->isLocalAudioPublishEnabled())
		{
			GetDlgItem(IDC_BUTTON_PUBC)->ShowWindow(FALSE);
		}

		if (m_rtcengine->isLocalScreenPublishEnabled())
		{
			GetDlgItem(IDC_BUTTON_PUBS)->ShowWindow(FALSE);
		}
	}
	m_rtcengine->setVideoProfile(UCLOUD_RTC_VIDEO_PROFILE_640_360);
	m_rtcengine->getSdkVersion();
	m_rtcengine->setSdkMode(UCLOUD_RTC_SDK_MODE_TRIVAL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CSdkTestDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSdkTestDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSdkTestDemoDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CSdkTestDemoDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CSdkTestDemoDlg::OnClose()
{
	if (!m_leaveroom)
	{
		int ret = m_rtcengine->leaveChannel();
		if (ret != 0)
		{
			m_rtcengine->destroy();
			CDialogEx::OnCancel();
		}
		m_isclose = true;
	}
	else {
		m_rtcengine->destroy();
		CDialogEx::OnCancel();
	}
}


HRESULT CSdkTestDemoDlg::OnCallBackMsg(WPARAM data, LPARAM lp)
{
	tCallMsg* callmsg = (tCallMsg*)data;
	int eventid = callmsg->eventid;

	switch (eventid)
	{
	case URTC_EVENT_MSG_JOINROOM_RSP:
		OnJoinRoomHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_LEAVEROOM_RSP:
		OnLeaveRoomHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REJOINING :
		OnServerReconnectingHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REJOINED :
		OnReJoinRoomHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_ERRORMSG :
		OnSdkErrorHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTEUSERLEAVE :
	case URTC_EVENT_MSG_REMOTEUSERJOIN :
		OnUserStHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_LOCALPUBLISH_RSP :
		OnPulibshStreamHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_LOCALUNPUBLISH_RSP:
		OnUnPulibshStreamHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTEPUBLISH:
	case URTC_EVENT_MSG_REMOTEUNPUBLISH:
		OnStreamStHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTESUB_RSP :
		OnSubStreamHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_KICKOFF :
		OnKickoffHandler(callmsg->msg);
		break;

	case URTC_EVENT_MSG_LOCALSTREAMMUTE_RSP :
		OnLocalStreamMuteHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTESTREAMMUTE_RSP :
		OnRemoteStreamMuteHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTETRACKST :
		OnRemoteTrackStNotify(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTE_AUDIOVOL :
		OnRemoteAudioVolHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_LOCAL_AUDIOVOL :
		OnLocalAudioVolHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_LOCAL_ST_UPDATE:
		OnSendStHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_REMOTE_ST_UPDATE:
		OnRemoteStHandler(callmsg->msg);
		break;
	case URTC_EVENT_MSG_ONSERVERDIS :
		OnServerDisconnectHandler("");
		break;
	default:
		break;
	}
	if (callmsg)
	{
		delete callmsg;
	}
	return 0;
}

void CSdkTestDemoDlg::OnBnClickedButtonJoin()
{
	// TODO: Add your control notification handler code here
	CString text;
	GetDlgItemText(IDC_EDIT_ROOM, text);
	//CString uid;
	//GetDlgItemText(IDC_EDIT_USERID, uid);
	//m_userid = WChatToUTF8Str(uid.GetBuffer());
	m_roomid = WChatToUTF8Str(text.GetBuffer());
	if (m_roomid.length() <= 0)
	{
		m_roomid = "";
		AfxMessageBox(L"请输入房间ID");
		return;
	}
	if (m_rtcengine)
	{
		tUCloudRtcAuth auth;
		auth.mAppId = TEST_APP_ID;
		auth.mRoomId = m_roomid.data();
		auth.mUserId = m_userid.data();
		auth.mUserToken = "";
		int ret = m_rtcengine->joinChannel(auth);
	}
}

void CSdkTestDemoDlg::OnJoinRoomHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		GetDlgItem(IDC_BUTTON_JOIN)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(true);
		if (!m_rtcengine->isAutoPublish() )
		{
			if (m_rtcengine->isLocalCameraPublishEnabled() || m_rtcengine->isLocalAudioPublishEnabled())
			{
				GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
			}
			if (m_rtcengine->isLocalScreenPublishEnabled())
			{
				GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
			}

		}

		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_ROOM)->EnableWindow(false);
		OnMessageShow("加入房间成功");
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "加入房间失败 " + msg + " "+ errcode;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnReJoinFailHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);
	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();

	char num[32] = { 0 };
	sprintf_s(num, " err code = %d", code);
	std::string errcode = num;
	std::string desc = "重新加入房间失败 " + msg + " " + errcode;
	OnMessageShow(desc);
}

void CSdkTestDemoDlg::OnReJoinRoomHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	//int code = retObj["code"].asInt();
	//std::string msg = retObj["msg"].asString();
	//if (code == 0)
	//{
	//	Json::Value users = retObj["data"]["users"];

	//	for (int i = 0; i < users.size(); i++) {
	//		std::string userid = users[i]["uid"].asString();
	//		userit uit = m_hashSessions.find(userid);
	//		tUserInfo* user = nullptr;
	//		if (uit == m_hashSessions.end())
	//		{
	//			user = new tUserInfo;
	//			user->mUserid = userid;
	//			m_hashSessions.emplace(std::make_pair(userid, user));
	//			m_users.AddString(Ansi2WChar(userid.data()).data());
	//		}
	//		else {
	//			user = uit->second;
	//		}


	//		Json::Value streams = users[i]["streams"];
	//		for (int i = 0; i < streams.size(); i++) {
	//			std::string streamid = streams[i]["streamid"].asString();
	//			streamit sit = m_streamsmap.find(streamid);
	//			if (sit == m_streamsmap.end())
	//			{
	//				tStreamInfo * stream = new tStreamInfo;
	//				//stream->mStreamid = streamid;
	//				stream->mUserid = userid;
	//				stream->mEnalbevideo = streams[i]["video"].asBool();
	//				stream->mEnalbeaudio = streams[i]["audio"].asBool();
	//				stream->mEnalbedata = streams[i]["data"].asBool();

	//				m_streamsmap.emplace(std::make_pair(streamid, stream));
	//			}

	//			//user->mStreams.emplace(streamid);
	//		}
	//	}

	//	SubscribeAllStream();
		OnMessageShow("重连成功");
	//}
	//else {
	//	char num[32] = { 0 };
	//	sprintf_s(num, " err code = %d", code);
	//	std::string errcode = num;
	//	std::string desc = "重新加入房间失败 " + msg + " " + errcode;
	//	OnMessageShow(desc);
	//}
}

void CSdkTestDemoDlg::OnLeaveRoomHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_JOIN)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
		SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
		SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
		GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_ROOM)->EnableWindow(TRUE);
		OnMessageShow("退出房间成功");
	}
	else 
	{
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "退出房间失败 " + msg + " " + errcode;
		OnMessageShow(desc);
	}
	// 释放所有资源
	m_localWnd->setUsed(false);
	m_screenWnd->setUsed(false);
	ReleaseUserAllRes();

	// 关闭窗口离开房间
	if (m_isclose)
	{
		OnLeaveRoom();
	}
}

void CSdkTestDemoDlg::OnPulibshStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);
	
	int mtype = retObj["data"]["mtype"].asInt();
	if (mtype == UCLOUD_RTC_MEDIATYPE_VIDEO)
	{
		OnPulibshCamStreamHandler(jsonmsg);
	}
	else {
		OnPulibshScreenStreamHandler(jsonmsg);
	}

}

void CSdkTestDemoDlg::OnPulibshCamStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		SetDlgItemText(IDC_BUTTON_PUBC, L"停止发布");
		OnMessageShow("摄像头发布成功");
		tUCloudRtcVideoCanvas canvas;
		canvas.mVideoView = (int)m_localWnd->GetVideoHwnd();
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mUserId = "";
		canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;

		m_rtcengine->startPreview(canvas);
		m_localWnd->setUsed(true);
		m_localWnd->setReady(true);
		m_campub = true;
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "摄像头发布失败 " + msg+ " "+errcode;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnPulibshScreenStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		SetDlgItemText(IDC_BUTTON_PUBS, L"停止桌面");
		OnMessageShow("桌面发布成功");
		tUCloudRtcVideoCanvas canvas;
		canvas.mVideoView = (int)m_localWnd->GetVideoHwnd();
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mUserId = "";
		canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
		m_rtcengine->startPreview(canvas);
		m_screenWnd->setUsed(true);
		m_screenWnd->setReady(true);
		m_screenpub = true;
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "桌面发布失败 " + msg + " " + errcode;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnUnPulibshStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int mtype = retObj["data"]["mtype"].asInt();
	if (mtype == UCLOUD_RTC_MEDIATYPE_VIDEO)
	{
		OnUnPulibshStreamCamHandler(jsonmsg);
	}
	else {
		OnUnPulibshStreamScreenHandler(jsonmsg);
	}
}

void CSdkTestDemoDlg::OnUnPulibshStreamScreenHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		OnMessageShow("桌面已取消发布");
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;

		std::string desc = "取消发布失败 "+ msg+ " "+errcode;
		OnMessageShow(desc);
	}

	SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
	m_screenpub = false;
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(true);
	m_screenWnd->setUsed(false);
}

void CSdkTestDemoDlg::OnUnPulibshStreamCamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		OnMessageShow("摄像头已取消发布");
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "取消发布失败 "+ msg+ " "+ errcode;
		OnMessageShow(desc);
	}

	SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
	m_campub = false;
	m_localWnd->setUsed(false);
}

void CSdkTestDemoDlg::OnSubStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();

	std::string msg = retObj["msg"].asString();
	int mtype = retObj["data"]["mtype"].asInt();
	std::string uid = retObj["data"]["uid"].asString();
	char buf[32] = {0};
	sprintf_s(buf, "%d", mtype);
	eUCloudRtcMeidaType type = (mtype == 1) ? UCLOUD_RTC_MEDIATYPE_VIDEO : UCLOUD_RTC_MEDIATYPE_SCREEN;
	if (code == 0)
	{
		std::string msg = "订阅 "+ uid + buf + "成功";
		streamrenderit srit = m_mapRenders.find(uid + buf);
		CVideoWnd* videoview = nullptr;
		if (srit != m_mapRenders.end())
		{
			CVideoWnd* videoview = srit->second;
			if (videoview)
			{
				videoview->setUsed(true);
				videoview->SetUserId(uid);
				videoview->SetType(type);
				videoview->setReady(true);
			}
		}
		else {
			videowndit wnit = m_remoteWnds.begin();
			while (wnit != m_remoteWnds.end())
			{
				if (!(*wnit)->isUsed())
				{
					videoview = *wnit;
					videoview->setUsed(true);
					videoview->setReady(true);
					videoview->SetTitle(Ansi2WChar(uid.data()));
					videoview->SetType(type);
					videoview->SetUserId(uid);
					m_mapRenders.emplace(std::make_pair(uid + buf, videoview));
					break;
				}
				wnit++;
			}
		}
		OnMessageShow(msg);
		if (videoview)
		{
			tUCloudRtcVideoCanvas canvas;
			canvas.mVideoView = (int)m_localWnd->GetVideoHwnd();
			canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
			canvas.mUserId = const_cast<char*>(uid.data());
			canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
			m_rtcengine->startRemoteView(canvas);
		}

	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string msg = "订阅 " + uid + buf + " 失败 "+ errcode;
		OnMessageShow(msg);
	}
	
}

void CSdkTestDemoDlg::OnUnSubStreamHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string msg = retObj["msg"].asString();
	int mtype = retObj["data"]["mtype"].asInt();
	std::string uid = retObj["data"]["uid"].asString();
	UnSubscribeStream(mtype, uid);
}

void CSdkTestDemoDlg::OnStreamStHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string cmd = retObj["data"]["cmd"].asString();
	std::string userid = retObj["data"]["uid"].asString();
	int mtype = retObj["data"]["mtype"].asInt();
	if (cmd == "add")
	{
		tStreamInfo* stream = new tStreamInfo;
		stream->mediatype = mtype;
		stream->mUserid = userid;
		stream->mEnalbeaudio = retObj["data"]["audio"].asBool();
		stream->mEnalbevideo = retObj["data"]["video"].asBool();
		stream->mEnalbedata = retObj["data"]["data"].asBool();

		char buf[8] = {0};
		sprintf_s(buf, "%d", stream->mediatype);
		m_streamsmap.insert( std::make_pair(stream->mUserid+ buf, stream) );
		std::string desc = "流加入：";
		OnMessageShow(desc);
		std::string msg = "userid: " + userid ;
		OnMessageShow(msg);
		std::string mt = buf;
		std::string streamdesc = "mediatype: " + mt;
		OnMessageShow(streamdesc);
		if (!m_rtcengine->isAutoSubscribe())
		{
			SubscribeStream(mtype, userid);
		}
	}else if (cmd == "remove")
	{
		UnSubscribeStream(mtype, userid);
		std::string desc = "流移除：";
		OnMessageShow(desc);
		std::string msg =  "userid: " + userid;
		OnMessageShow(msg);
		char buf[32] = { 0 };
		sprintf_s(buf, "%d", mtype);
		std::string mt = buf;
		std::string streamdesc = "mediatype: " + mt;
		OnMessageShow(streamdesc);
	}
}

void CSdkTestDemoDlg::OnUserStHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string cmd = retObj["data"]["cmd"].asString();
	std::string userid = retObj["data"]["uid"].asString();

	if (cmd == "join")
	{
		userit uit = m_hashSessions.find(userid);
		if (uit == m_hashSessions.end())
		{
			tUserInfo* user = new tUserInfo;
			user->mUserid = userid;
			m_hashSessions.emplace(std::make_pair(userid, user));
		}

		OnMessageShow("userid: " + userid + " 加入房间");
	}
	else if (cmd == "leave")
	{
		UserLeave(userid);
		OnMessageShow("userid: " + userid + " 离开房间");
	}
}

void  CSdkTestDemoDlg::OnServerReconnectingHandler(std::string jsonmsg) {
	OnMessageShow(" 信令服务断开，正在尝试重连>>>>>>");
}

void CSdkTestDemoDlg::OnServerDisconnectHandler(std::string jsonmsg) {
	GetDlgItem(IDC_BUTTON_JOIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
	SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_ROOM)->EnableWindow(TRUE);

	m_localWnd->setUsed(false);
	m_screenWnd->setUsed(false);

	m_campub = false;
	m_screenpub = false;
	m_audiocheck.SetCheck(1);
	m_videocheck.SetCheck(1);
	OnMessageShow("信令服务器断开");
}

void CSdkTestDemoDlg::OnSdkErrorHandler(std::string jsonmsg) {

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	char num[32] = { 0 };
	sprintf_s(num, " err code = %d", code);
	std::string errcode = num;

	OnMessageShow("sdkerror: " + errcode);
}

void CSdkTestDemoDlg::OnKickoffHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	char num[32] = { 0 };
	sprintf_s(num, " err code = %d", code);
	std::string errcode = num;
	GetDlgItem(IDC_BUTTON_CREATE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_JOIN)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
	SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_ROOM)->EnableWindow(TRUE);
	m_campub = false;
	m_screenpub = false;
	m_localWnd->setUsed(false);
	m_screenWnd->setUsed(false);

	ReleaseUserAllRes();
	OnMessageShow("kick off : " + errcode);
}

void CSdkTestDemoDlg::OnLocalStreamMuteHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	int mediatype = retObj["data"]["mtype"].asInt();
	int trackype = retObj["data"]["ttype"].asInt();
	int mute = retObj["data"]["mute"].asInt();
	std::string desc = "";
	if (code == 0)
	{
		if (mediatype == UCLOUD_RTC_MEDIATYPE_VIDEO)
		{
			if (trackype == UCLOUD_RTC_TRACKTYPE_AUDIO)
			{
				m_localWnd->muteAudio(mute);
			}
			else {
				m_localWnd->muteVideo(mute);
				m_localWnd->muteVideo(mute);
			}
		}
		else 
		{
			m_screenWnd->muteVideo(mute);
		}

		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, " mtype=%d&&ttype=%d&&op=%d",mediatype, trackype, mute);
		std::string content = mutecontent;
		std::string desc = "操作成功" + msg + " " + content;
		OnMessageShow(desc);
		
	}
	else {
		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, " err code=%d&&mtype=%d&&ttype=%d&&op=%d", code, mediatype, trackype, mute);
		std::string content = mutecontent;
		std::string desc = "mute 远端 " + msg + " " + content;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnRemoteStreamMuteHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	std::string uid = retObj["data"]["uid"].asString();
	int mediatype = retObj["data"]["mtype"].asInt();
	int trackype = retObj["data"]["ttype"].asInt();
	int mute = retObj["data"]["mute"].asInt();
	std::string desc = "";
	if (code == 0)
	{

		char buf[32] = { 0 };
		sprintf_s(buf, "%d", mediatype);
		std::string mediakey = uid + buf;
		streamrenderit srit = m_mapRenders.find(mediakey);
		CVideoWnd* videoview = nullptr;
		if (srit != m_mapRenders.end())
		{
			videoview = srit->second;
		}

		if (mediatype == UCLOUD_RTC_MEDIATYPE_VIDEO)
		{
			if (trackype == UCLOUD_RTC_TRACKTYPE_AUDIO)
			{
				videoview->muteAudio(mute);
			}
			else {
				videoview->muteVideo(mute);
			}
		}
		else
		{
			videoview->muteVideo(mute);
		}

		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, "uid=%s mtype=%d&&ttype=%d&&op=%d", uid.data(), 
			mediatype, trackype, mute);
		std::string content = mutecontent;
		std::string desc = "操作成功" + msg + " " + content;
		OnMessageShow(desc);

	}
	else {
		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, "err code=%d&&uid=%s mtype=%d&&ttype=%d&&op=%d", code, 
			uid.data(), mediatype, trackype, mute);
		std::string content = mutecontent;
		std::string desc = "mute 远端 " + msg + " " + content;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnRemoteTrackStNotify(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string uid = retObj["data"]["uid"].asString();
	int mtype = retObj["data"]["mtype"].asInt();
	int ttype = retObj["data"]["ttype"].asInt();
	bool mute = retObj["data"]["mute"].asBool();

	if (mtype == UCLOUD_RTC_MEDIATYPE_SCREEN)
	{
		std::string desc = mute ? "关闭" : "打开";
		OnMessageShow(uid + " " + desc+ " "+ "桌面");
	}
	else {
		if (ttype == UCLOUD_RTC_TRACKTYPE_AUDIO)
		{
			std::string desc = mute ? "关闭" : "打开";
			OnMessageShow(uid + " " + desc + " " + "麦克风");
		}
		else 
		{
			std::string desc = mute ? "关闭" : "打开";
			OnMessageShow(uid + " " + desc + " " + "摄像头");
		}
	
	}

}

void CSdkTestDemoDlg::OnRemoteAudioVolHandler(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string uid = retObj["data"]["uid"].asString();
	int vol = retObj["data"]["vol"].asInt();

	char buf[8] = { 0 };
	sprintf_s(buf, "%d", UCLOUD_RTC_MEDIATYPE_VIDEO);
	std::string mediakey = uid + buf;
	streamrenderit srit = m_mapRenders.find(mediakey);
	if (srit != m_mapRenders.end())
	{
		if (srit->second)
		{
			srit->second->setVol(vol);
		}
	}
}

void CSdkTestDemoDlg::OnLocalAudioVolHandler(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);
	std::string uid = retObj["data"]["uid"].asString();
	int vol = retObj["data"]["vol"].asInt();
	m_localWnd->setVol(vol);
}

void CSdkTestDemoDlg::OnRemoteStHandler(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	std::string uid = retObj["data"]["uid"].asString();
	int mediatype = retObj["data"]["mtype"].asInt();
	int tracktype = retObj["data"]["ttype"].asInt();

	int bitrate = retObj["data"]["bitrate"].asInt();
	float lostrate = retObj["data"]["lostrate"].asFloat();

	if (tracktype == UCLOUD_RTC_MEDIATYPE_VIDEO)
	{
		char buf[256] = { 0 };
		int height = retObj["data"]["height"].asInt();
		int width = retObj["data"]["width"].asInt();
		int framerate = retObj["data"]["framerate"].asInt();
		sprintf_s(buf, "%s mtype:%d %d %0.2f height:%d width:%d framerate:%d",
			uid.data(), mediatype, bitrate, lostrate, height, width, framerate);
		std::string info = buf;
		//OnMessageShow("远端视频: " + info);
	}
	else
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "%s mtype:%d %d %0.2f ",
			uid.data() ,mediatype, bitrate, lostrate);
		std::string info = buf;
		//OnMessageShow("远端音频: " + info);
	}
}

void CSdkTestDemoDlg::OnSendStHandler(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int mediatype = retObj["data"]["mtype"].asInt();
	int tracktype = retObj["data"]["ttype"].asInt();

	int bitrate = retObj["data"]["bitrate"].asInt();
	float lostrate = retObj["data"]["lostrate"].asFloat();

	if (tracktype == UCLOUD_RTC_MEDIATYPE_VIDEO)
	{
		char buf[256] = {0};
		int height = retObj["data"]["height"].asInt();
		int width = retObj["data"]["width"].asInt();
		int framerate = retObj["data"]["framerate"].asInt();
		sprintf_s(buf, "mtype:%d %d %0.2f height:%d*width:%d*framerate:%d",
			mediatype, bitrate, lostrate, height, width, framerate) ;
		std::string info = buf;
		//OnMessageShow("本地视频: " + info);
	}
	else
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "mtype:%d %d %0.2f ",
			mediatype, bitrate, lostrate);
		std::string info = buf;
		//OnMessageShow("本地音频: " + info);
	}
}

void CSdkTestDemoDlg::ReleaseUserAllRes() {
	m_campub = false;
	m_screenpub = false;
	m_roomid = "";

	streamrenderit srit = m_mapRenders.begin();
	while (srit != m_mapRenders.end())
	{
		if (srit->second)
		{
			srit->second->SetUserId("");
			srit->second->setUsed(false);
			srit->second->SetTitle(L"");
		}
		m_mapRenders.erase(srit++);
	}

	streamit sit = m_streamsmap.begin();
	while (sit != m_streamsmap.end())
	{
		if (sit->second)
		{
			delete sit->second;
		}

		m_streamsmap.erase(sit++);
	}

	userit uit = m_hashSessions.begin();
	while (uit != m_hashSessions.end())
	{
		if (uit->second)
		{
			//uit->second->mStreams.clear();
			delete uit->second;
		}

		m_hashSessions.erase(uit++);
	}

	m_audiocheck.SetCheck(1);
	m_videocheck.SetCheck(1);
	m_msglist.ResetContent();
}

void CSdkTestDemoDlg::SubscribeAllStream() {
	streamit sit = m_streamsmap.begin();
	while (sit != m_streamsmap.end())
	{
		//std::string streamid = sit->second->mStreamid;
		std::string uid = sit->second->mUserid;
		//SubscribeStream(streamid, uid);
		sit++;
	}
}

void CSdkTestDemoDlg::SubscribeStream(int mediatype, std::string uid) {
	char buf[8] = {0};
	sprintf_s(buf, "%d", mediatype);
	std::string mediakey = uid + buf;
	streamit sit = m_streamsmap.find(mediakey);
	eUCloudRtcMeidaType type = (mediatype == 1) ? UCLOUD_RTC_MEDIATYPE_VIDEO : UCLOUD_RTC_MEDIATYPE_SCREEN;
	if (sit != m_streamsmap.end())
	{
		streamrenderit srit = m_mapRenders.find(mediakey);
		CVideoWnd* renderview = nullptr;
		if (srit == m_mapRenders.end())
		{
			videowndit wnit = m_remoteWnds.begin();
			while (wnit != m_remoteWnds.end())
			{
				if ( !(*wnit)->isUsed() )
				{
					renderview = *wnit;
					renderview->setUsed(true);
					renderview->SetTitle(Ansi2WChar(uid.data()));
					renderview->SetType(type);
					renderview->SetUserId(uid);
					m_mapRenders.emplace(std::make_pair(mediakey, renderview));
					break;
				}
				wnit++;
			}
		}
		else
		{
			renderview = srit->second;
		}

		if (renderview == nullptr)
		{
			std::string msg = "已达到本地预览窗口上限";
			OnMessageShow(msg);
			return;
		}
	}
}

void CSdkTestDemoDlg::UnSubscribeStream(int mediatype, std::string uid) {
	char buf[8] = {0};
	sprintf_s(buf, "%d", mediatype);
	std::string mediakey = uid + buf;
	streamrenderit srit = m_mapRenders.find(mediakey);
	if (srit != m_mapRenders.end())
	{
		CVideoWnd* videoview = srit->second;
		if (videoview)
		{
			videoview->SetType(UCLOUD_RTC_MEDIATYPE_NONE);
			videoview->SetUserId("");
			videoview->setUsed(false);
			videoview->SetTitle(L"");
		}
		m_mapRenders.erase(srit);
	}

	userit uit = m_hashSessions.find(uid);
	streamit sit = m_streamsmap.find(mediakey);
	if (sit != m_streamsmap.end() )
	{
		delete sit->second;
		m_streamsmap.erase(sit);
	}

}

void CSdkTestDemoDlg::UserLeave(std::string uid) {

	userit uit = m_hashSessions.find(uid);
	streamit sit = m_streamsmap.begin();
	if (uit != m_hashSessions.end())
	{
		while (sit != m_streamsmap.end())
		{
			tStreamInfo* info = sit->second;
			if (info)
			{
				if (info->mUserid == uid)
				{
					char buf[8] = { 0 };
					sprintf_s(buf, "%d", info->mediatype);
					streamrenderit srit = m_mapRenders.find(info->mUserid + buf);
					if (srit != m_mapRenders.end())
					{
						CVideoWnd* videoview = srit->second;
						if (videoview)
						{
							videoview->SetType(UCLOUD_RTC_MEDIATYPE_NONE);
							videoview->SetUserId("");
							videoview->setUsed(false);
							videoview->SetTitle(L"");
						}
						m_mapRenders.erase(srit);
						m_streamsmap.erase(sit++);
						continue;
					}
				}
			}
			sit++;
		}
		m_hashSessions.erase(uit);
	}
}

void CSdkTestDemoDlg::OnLeaveRoom() {
	m_rtcengine->destroy();
	CDialogEx::OnCancel();
}

void CSdkTestDemoDlg::OnBnClickedButtonPubC()
{
	if (m_campub)
	{
		m_rtcengine->unPublish(UCLOUD_RTC_MEDIATYPE_VIDEO);
		SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
		m_campub = !m_campub;
	}
	else {
		tUCloudRtcMediaConfig config;
		config.mAudioEnable = m_audiocheck.GetCheck();
		config.mVideoEnable = m_videocheck.GetCheck();
		if (!config.mAudioEnable && !config.mVideoEnable)
		{
			AfxMessageBox(L"发布视频最少需要选择一种媒体");
			return;
		}
		m_localWnd->SetUserId("camera");
		int ret = m_rtcengine->publish(UCLOUD_RTC_MEDIATYPE_VIDEO, config.mVideoEnable,
			config.mAudioEnable);
	}
}


void CSdkTestDemoDlg::OnBnClickedButtonLeaveroom()
{
	int ret = m_rtcengine->leaveChannel();
	if (ret != 0)
	{
		m_rtcengine->destroy();
		CDialogEx::OnCancel();
	}
	m_leaveroom = true;
}

void CSdkTestDemoDlg::OnBnClickedButtonPubs()
{
	if (m_screenpub)
	{
		m_rtcengine->unPublish(UCLOUD_RTC_MEDIATYPE_SCREEN);
		SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
		m_screenpub = !m_screenpub;
	}
	else 
	{
		tUCloudRtcMediaConfig config;
		config.mAudioEnable = false;
		config.mVideoEnable = true;
		m_screenWnd->SetUserId("screen");
		m_rtcengine->setDesktopProfile(UCLOUD_RTC_SCREEN_PROFILE_MIDDLE);
		m_rtcengine->publish(UCLOUD_RTC_MEDIATYPE_SCREEN, config.mVideoEnable,
			config.mAudioEnable);
	}
}


void CSdkTestDemoDlg::OnBnClickedButtonDeviceTest()
{
	CDeviceTestDlg devtestdlg;
	devtestdlg.DoModal();
}

void CSdkTestDemoDlg::OnMessageShow(std::string msg) {
	if (m_msglist.GetCount()>300)
	{
		m_msglist.ResetContent();
	}
	m_msglist.AddString(Ansi2WChar(msg.data()).data());
}
