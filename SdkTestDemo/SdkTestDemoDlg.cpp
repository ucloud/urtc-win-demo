// SdkTestDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SdkTestDemo.h"
#include "SdkTestDemoDlg.h"
#include "afxdialogex.h"
#include "URTCConfig.h"
#include "SdkUtil.h"
#include "json/json.h"
#include "RTCEventDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdkTestDemoDlg 对话框
#include <string>
#include <stdint.h>


CSdkTestDemoDlg::CSdkTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SFU, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_userid = URTCConfig::getInstance()->getUserId();
	m_campub = false;
	m_screenpub = false;
	m_leaveroom = false;
	m_isclose = false;
	m_startrecord = false;
	m_startaudiomix = false;
}

void CSdkTestDemoDlg::OnMuteAudio(std::string userid, eUCloudRtcMeidaType mediatype, bool mute) {
	if (userid == "camera")
	{
		tRTCStreamMute mutest;
		mutest.mMute = mute;
		mutest.mUserid = m_userid;
		m_rtcengine->MuteLocalCamAudio(mutest);
	}
	else if (userid == "screen")
	{
	}
	else {
		tRTCStreamMute mutest;
		mutest.mMute = mute;
		mutest.mUserid = userid;
		m_rtcengine->MuteRemoteCamAudio(mutest);
	}
}

void CSdkTestDemoDlg::OnMuteVideo(std::string userid, eUCloudRtcMeidaType mediatype, bool mute) {
	if (userid == "camera")
	{
		tRTCStreamMute mutest;
		mutest.mMute = mute;
		mutest.mUserid = m_userid;
		m_rtcengine->MuteLocalCamVideo(mutest);
	}
	else if (userid == "screen")
	{
		tRTCStreamMute mutest;
		mutest.mMute = mute;
		mutest.mUserid = m_userid;
		m_rtcengine->MuteLocalScreen(mutest);
	}
	else 
	{
		if (mediatype == UCLOUD_RTC_MEDIATYPE_VIDEO)
		{
			tRTCStreamMute mutest;
			mutest.mMute = mute;
			mutest.mUserid = userid;
			m_rtcengine->MuteRemoteCamVideo(mutest);
		}
		else 
		{
			tRTCStreamMute mutest;
			mutest.mMute = mute;
			mutest.mUserid = userid;
			m_rtcengine->MuteRemoteScreen(mutest);
		}
	}
}

void CSdkTestDemoDlg::OnCloseMedia(std::string type, std::string id) 
{

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

void CSdkTestDemoDlg::InitURTCConfig()
{

	if (URTCConfig::getInstance()->isAudioOnly())
	{
		m_videocheck.ShowWindow(FALSE);
		m_audiocheck.SetCheck(1);
		m_audiocheck.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PUBS)->ShowWindow(FALSE);
	}
	else {
		m_audiocheck.SetCheck(1);
		m_videocheck.SetCheck(1);
	}

	if (URTCConfig::getInstance()->getStreamRole() == UCLOUD_RTC_USER_STREAM_ROLE_SUB)
	{
		GetDlgItem(IDC_BUTTON_PUBC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PUBS)->ShowWindow(FALSE);
		m_audiocheck.ShowWindow(FALSE);
		m_videocheck.ShowWindow(FALSE);
	}

	if (URTCConfig::getInstance()->isAutoPublish())
	{
		GetDlgItem(IDC_BUTTON_PUBC)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PUBS)->ShowWindow(FALSE);
		m_audiocheck.ShowWindow(FALSE);
		m_videocheck.ShowWindow(FALSE);
	}

	m_rtcengine->SetCodecType(URTCConfig::getInstance()->getCodecType());
	m_roomid = URTCConfig::getInstance()->getRoomId();

	m_rtcengine->MuteCamBeforeJoin(URTCConfig::getInstance()->getMuteCamBeforeJoin());
	m_rtcengine->MuteMicBeforeJoin(URTCConfig::getInstance()->getMuteMicBeforeJoin());

	tRTCAuthInfo auth;
	auth.mAppid = URTCConfig::getInstance()->getAppId();
	auth.mRoomid = m_roomid.data();
	auth.mUserid = m_userid.data();
	auth.mToken = "test";
	int ret = m_rtcengine->JoinRoom(auth);
}


BEGIN_MESSAGE_MAP(CSdkTestDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CSdkTestDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSdkTestDemoDlg::OnBnClickedCancel)
	ON_MESSAGE(RTC_EVENT_UCLOUD, &CSdkTestDemoDlg::OnRTCUCloudMsg)
	ON_BN_CLICKED(IDC_BUTTON_PUBC, &CSdkTestDemoDlg::OnBnClickedButtonPubC)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEROOM, &CSdkTestDemoDlg::OnBnClickedButtonLeaveroom)
	ON_BN_CLICKED(IDC_BUTTON_PUBS, &CSdkTestDemoDlg::OnBnClickedButtonPubs)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, &CSdkTestDemoDlg::OnBnClickedButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_MIXFILE, &CSdkTestDemoDlg::OnBnClickedButtonMixfile)
END_MESSAGE_MAP()


// CSdkTestDemoDlg 消息处理程序
BOOL CSdkTestDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::string channel = "channel_" + URTCConfig::getInstance()->getRoomId();
	this->SetWindowTextW(Ansi2WChar(channel.data()).data());
	//InitMinDump();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetDlgItemText(IDC_EDIT_USERID, Ansi2WChar(m_userid.data()).data());

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
	m_rtcengine = RTCEngineFactory::createRtcEngine(RTC_CHANNELTYPE_UCLOUD);
	m_rtcengine->InitRTCEngine(this->GetSafeHwnd());

	InitURTCConfig();
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
	//CDialogEx::OnOK();
}


void CSdkTestDemoDlg::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
}

void CSdkTestDemoDlg::OnClose()
{
	if (!m_leaveroom)
	{
		int ret = m_rtcengine->LeaveRoom(m_roomid);
		if (ret != 0)
		{
			m_rtcengine->UnInitRTCEngine();
			CDialogEx::OnCancel();
		}
		m_isclose = true;
	}
	else {
		m_rtcengine->UnInitRTCEngine();
		CDialogEx::OnCancel();
	}
}

HRESULT CSdkTestDemoDlg::OnRTCUCloudMsg(WPARAM data, LPARAM lp)
{
	tEventMsg* callmsg = (tEventMsg*)data;
	int eventid = callmsg->mEventid;

	switch (eventid)
	{
	case URTC_EVENT_MSG_JOINROOM_RSP:
		OnJoinRoomHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_LEAVEROOM_RSP:
		OnLeaveRoomHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REJOINING :
		OnServerReconnectingHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REJOINED :
		OnReJoinRoomHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_ERRORMSG :
		OnSdkErrorHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTEUSERLEAVE :
	case URTC_EVENT_MSG_REMOTEUSERJOIN :
		OnUserStHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_LOCALPUBLISH_RSP :
		OnPulibshStreamHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_LOCALUNPUBLISH_RSP:
		OnUnPulibshStreamHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTEPUBLISH:
	case URTC_EVENT_MSG_REMOTEUNPUBLISH:
		OnStreamStHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTESUB_RSP :
		OnSubStreamHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_KICKOFF :
		OnKickoffHandler(callmsg->mJsonMsg);
		break;

	case URTC_EVENT_MSG_LOCALSTREAMMUTE_RSP :
		OnLocalStreamMuteHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTESTREAMMUTE_RSP :
		OnRemoteStreamMuteHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTETRACKST :
		OnRemoteTrackStNotify(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTE_AUDIOVOL :
		OnRemoteAudioVolHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_LOCAL_AUDIOVOL :
		OnLocalAudioVolHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_LOCAL_ST_UPDATE:
		OnSendStHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_REMOTE_ST_UPDATE:
		OnRemoteStHandler(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_ONSERVERDIS :
		OnServerDisconnectHandler("");
		break;
	case URTC_EVENT_MSG_ELEC_STARTRECORD :
		OnStartRecord(callmsg->mJsonMsg);
		break;
	case URTC_EVENT_MSG_ELEC_STOPRECORD:
		OnStopRecord(callmsg->mJsonMsg);
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

void CSdkTestDemoDlg::OnJoinRoomHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_RECORD)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_MIXFILE)->EnableWindow(true);
		OnMessageShow("加入房间成功");
	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "加入房间失败 " + msg + " " + errcode;
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
	OnMessageShow("重连成功");
}

void CSdkTestDemoDlg::OnLeaveRoomHandler(std::string jsonmsg) {
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);

	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	if (code == 0)
	{
		GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
		SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
		SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
		GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_RECORD)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_MIXFILE)->EnableWindow(false);
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
	OnLeaveRoom();
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
		tRTCRenderView canvas;
		canvas.mVidoview = (int)m_localWnd->GetVideoHwnd();
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mUserid = m_userid;
		canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;

		m_rtcengine->StartLocalRender(canvas);
		m_localWnd->setUsed(true);
		m_localWnd->setReady(true);

		m_localWnd->muteVideo(URTCConfig::getInstance()->getMuteCamBeforeJoin());
		m_localWnd->muteAudio(URTCConfig::getInstance()->getMuteMicBeforeJoin());
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
		tRTCRenderView canvas;
		canvas.mVidoview = (int)m_screenWnd->GetVideoHwnd();
		canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		canvas.mUserid = m_userid;
		canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
		m_screenWnd->setUsed(true);
		m_screenWnd->setReady(true);
		m_screenpub = true;
		m_rtcengine->StartLocalRender(canvas);
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

		std::string desc = "取消发布失败 " + msg + " " + errcode;
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
		std::string desc = "取消发布失败 " + msg + " " + errcode;
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
	char buf[32] = { 0 };
	sprintf_s(buf, "%d", mtype);
	eUCloudRtcMeidaType type = (mtype == 1) ? UCLOUD_RTC_MEDIATYPE_VIDEO : UCLOUD_RTC_MEDIATYPE_SCREEN;
	if (code == 0)
	{
		std::string msg = "订阅 " + uid + buf + "成功";
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

			tRTCRenderView canvas;
			canvas.mVidoview = (int)videoview->GetVideoHwnd();
			canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
			canvas.mUserid = uid.data();
			canvas.mStreamMtype = mtype;
			canvas.mRenderType =  UCLOUD_RTC_RENDER_TYPE_D3D;
			m_rtcengine->StartRemoteRender(canvas);
		}

	}
	else {
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string msg = "订阅 " + uid + buf + " 失败 " + errcode;
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
		stream->mStreamMtype = mtype;
		stream->mUserid = userid;
		stream->mEnalbeaudio = retObj["data"]["audio"].asBool();
		stream->mEnalbevideo = retObj["data"]["video"].asBool();
		stream->mEnalbedata = retObj["data"]["data"].asBool();

		char buf[8] = { 0 };
		sprintf_s(buf, "%d", stream->mStreamMtype);
		m_streamsmap.insert(std::make_pair(stream->mUserid + buf, stream));
		std::string desc = "流加入：";
		OnMessageShow(desc);
		std::string msg = "userid: " + userid;
		OnMessageShow(msg);
		std::string mt = buf;
		std::string streamdesc = "mediatype: " + mt;
		OnMessageShow(streamdesc);
	}
	else if (cmd == "remove")
	{
		UnSubscribeStream(mtype, userid);
		std::string desc = "流移除：";
		OnMessageShow(desc);
		std::string msg = "userid: " + userid;
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
	OnMessageShow(" 信令服务断开，正在尝试重连......");
}

void CSdkTestDemoDlg::OnServerDisconnectHandler(std::string jsonmsg) {
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
	SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);

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
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
	SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
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
		sprintf_s(mutecontent, " mtype=%d&&ttype=%d&&op=%d", mediatype, trackype, mute);
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

void CSdkTestDemoDlg::OnStartRecord(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);
	std::string desc = "";
	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	std::string recordid = retObj["data"]["recordid"].asString();
	if (code == 0)
	{
		m_startrecord = true;
		SetDlgItemText(IDC_BUTTON_RECORD, L"停止录制");
		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, " recordid ", recordid.data());
		std::string content = mutecontent;
		std::string desc = "开启录制成功 " + msg + " " + content;
		OnMessageShow(desc);

	}
	else 
	{
		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, " err code=%d", code);
		std::string content = mutecontent;
		std::string desc = "开启录制失败 " + msg + " " + content;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnStopRecord(std::string jsonmsg)
{
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg.c_str(), retObj, false);
	std::string desc = "";
	int code = retObj["code"].asInt();
	std::string msg = retObj["msg"].asString();
	std::string filename = retObj["data"]["filename"].asString();
	if (code == 0)
	{
		m_startrecord = true;
		SetDlgItemText(IDC_BUTTON_RECORD, L"开启录制");
		std::string desc = "停止录制成功 ";
		OnMessageShow(desc);

	}
	else
	{
		char mutecontent[128] = { 0 };
		sprintf_s(mutecontent, " err code=%d", code);
		std::string content = mutecontent;
		std::string desc = "停止录制失败 " + msg + " " + content;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::ReleaseUserAllRes() {
	m_campub = false;
	m_screenpub = false;
	m_roomid = "";
	m_startaudiomix = false;
	m_startrecord = false;

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
					sprintf_s(buf, "%d", info->mStreamMtype);
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
	m_rtcengine->UnInitRTCEngine();
	CDialogEx::OnCancel();
}

void CSdkTestDemoDlg::OnBnClickedButtonPubC()
{
	if (m_campub)
	{
		tRTCStreamInfo info;
		info.mEnableVideo = m_videocheck.GetCheck();
		info.mEnableAudio = m_audiocheck.GetCheck();
		info.mEnableData = false;
		info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		info.mUserid = m_userid;
		m_rtcengine->UnPublishStream(info);
		SetDlgItemText(IDC_BUTTON_PUBC, L"发布媒体");
		m_campub = !m_campub;
	}
	else {
		bool audioEnable = m_audiocheck.GetCheck();
		bool videoEnable = m_videocheck.GetCheck();
		if (!audioEnable && !videoEnable)
		{
			AfxMessageBox(L"发布视频最少需要选择一种媒体");
			return;
		}
		m_localWnd->SetUserId("camera");
		tRTCStreamInfo info;
		info.mEnableVideo = videoEnable;
		info.mEnableAudio = audioEnable;
		info.mEnableData = false;
		info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		info.mUserid = m_userid;
		int ret = m_rtcengine->PublishStream(info);
	}
}


void CSdkTestDemoDlg::OnBnClickedButtonLeaveroom()
{
	int ret = m_rtcengine->LeaveRoom(m_roomid);
	if (ret != 0)
	{
		m_rtcengine->UnInitRTCEngine();
		CDialogEx::OnCancel();
	}
	m_leaveroom = true;
}

void CSdkTestDemoDlg::OnBnClickedButtonPubs()
{
	if (m_screenpub)
	{
		tRTCStreamInfo info;
		info.mEnableVideo = m_videocheck.GetCheck();
		info.mEnableAudio = m_audiocheck.GetCheck();
		info.mEnableData = false;
		info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
		info.mUserid = m_userid;
		m_rtcengine->UnPublishStream(info);
		SetDlgItemText(IDC_BUTTON_PUBS, L"发布桌面");
		m_screenpub = !m_screenpub;
	}
	else 
	{
		tRTCStreamInfo info;
		info.mEnableVideo = true;
		info.mEnableAudio = false;
		info.mEnableData = false;
		info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
		info.mUserid = m_userid;
		int ret = m_rtcengine->PublishStream(info);
		m_screenWnd->SetUserId("screen");
	}
}

void CSdkTestDemoDlg::OnMessageShow(std::string msg) {
	if (m_msglist.GetCount()>300)
	{
		m_msglist.ResetContent();
	}
	m_msglist.AddString(Ansi2WChar(msg.data()).data());
}

void CSdkTestDemoDlg::OnBnClickedButtonRecord()
{
	tRTCRenderView canvas;
	canvas.mVidoview = (int)m_localWnd->GetVideoHwnd();
	canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	canvas.mUserid = m_userid;
	canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
	canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StopLocalRender(canvas);

	CVideoWnd* videoview = nullptr;
	videowndit wnit = m_remoteWnds.begin();
	if (wnit != m_remoteWnds.end() )
	{
		videoview = *wnit;

		tRTCRenderView rcanvas;
		rcanvas.mVidoview = (int)videoview->GetVideoHwnd();
		rcanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
		rcanvas.mUserid = videoview->GetUserId();
		rcanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		rcanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
		m_rtcengine->StopRemoteRender(rcanvas);
	}

	/*tRTCRenderView ccanvas;
	ccanvas.mVidoview = (int)videoview->GetSafeHwnd();
	ccanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	ccanvas.mUserid = m_userid;
	ccanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
	ccanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StartLocalRender(ccanvas);

	tRTCRenderView nscanvas;
	nscanvas.mVidoview = (int)m_localWnd->GetSafeHwnd();
	nscanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	nscanvas.mUserid = videoview->GetUserId();
	nscanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
	nscanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StartLocalRender(nscanvas);*/
	

	/*tRTCRenderView scanvas;
	scanvas.mVidoview = (int)m_screenWnd->GetVideoHwnd();
	scanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	scanvas.mUserid = m_userid;
	scanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
	scanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StopLocalRender(scanvas);

	tRTCRenderView ncanvas;
	ncanvas.mVidoview = (int)m_screenWnd->GetVideoHwnd();
	ncanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	ncanvas.mUserid = m_userid;
	ncanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
	ncanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StartLocalRender(ncanvas);

	tRTCRenderView nscanvas;
	nscanvas.mVidoview = (int)m_localWnd->GetVideoHwnd();
	nscanvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	nscanvas.mUserid = m_userid;
	nscanvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
	nscanvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
	m_rtcengine->StartLocalRender(nscanvas);*/

	/*tRTCRenderView canvas;
	canvas.mVidoview = (int)GetSafeHwnd();
	canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
	canvas.mUserid = m_userid;
	canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
	canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;*/

	//m_rtcengine->StartLocalRender(canvas);


	//if (m_rtcengine)
	//{
	//	if (m_startrecord)
	//	{
	//		m_rtcengine->StopRecord();
	//	}
	//	else
	//	{
	//		tRecordConfig recordconfig;
	//		recordconfig.mMainviewmediatype = 1;
	//		recordconfig.mMainviewuid = m_userid.data();
	//		recordconfig.mProfile = 1;
	//		recordconfig.mRecordType = 2;
	//		recordconfig.mWatermarkPos = 1;
	//		recordconfig.mBucket = "urtc-test";
	//		recordconfig.mBucketRegion = "cn-bj";
	//		m_rtcengine->StartRecord(recordconfig);
	//	}
	//}
}


void CSdkTestDemoDlg::OnBnClickedButtonMixfile()
{
	if (m_startaudiomix)
	{
		if (m_rtcengine)
		{
			m_rtcengine->StopMixFile();
			m_startaudiomix = false;
		}
		
	}
	else 
	{
		CString defaultDir = L"D://"; 
		CString fileName = L"*.mp3";     
		CString filter = L"File(*.mp3 |*.wav)";
		CFileDialog openFileDlg(true, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);
		INT_PTR result = openFileDlg.DoModal();
		CString filePath;
		if (result == IDOK) 
		{
			filePath = openFileDlg.GetPathName();
		}
		if (filePath.GetLength() <=0)
		{
			return;
		}
		std::string temp = WChar2Ansi(filePath.GetBuffer());
		filePath.ReleaseBuffer();
		const char* filepathc = temp.data();
		if (m_rtcengine)
		{
			m_rtcengine->StartMixFile(filepathc, false, true, 0.8f);
			m_startaudiomix = true;
		}
		
	}
}
