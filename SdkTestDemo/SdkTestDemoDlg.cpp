// SdkTestDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SdkTestDemo.h"
#include "SdkTestDemoDlg.h"
#include "afxdialogex.h"
#include "URTCConfig.h"
#include "SdkUtil.h"
#include "RTCEventDefine.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"  
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSdkTestDemoDlg �Ի���
#include <string>
#include <stdint.h>

#define VIDEO_FRAME_CALLBACK 20000

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
	_pFullScreenDlg = nullptr;
	m_lpImageBuffer = new unsigned char[0x800000];
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
	DDX_Control(pDX, IDC_EDIT_RTSP1, m_rtsp1);
	DDX_Control(pDX, IDC_EDIT_RTSP2, m_rtsp2);
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

	/*m_mediadevice = UCloudRtcMediaDevice::sharedInstance();
		m_mediadevice = UCloudRtcMediaDevice::sharedInstance();
	m_rtcengine->enableExtendVideoSource(true, this);
	CVideoPackageQueue::GetInstance()->SetVideoFrameLen(640 * 360 * 3/2);*/

	m_mediadevice = nullptr;

	tRTCAuthInfo auth;
	auth.mAppid = URTCConfig::getInstance()->getAppId();
	auth.mRoomid = m_roomid.data();
	auth.mUserid = m_userid.data();
	auth.mServerUrl = "wss://urtc.ibusre.cn:5005";
	int ret = m_rtcengine->JoinRoom(auth);
}


BEGIN_MESSAGE_MAP(CSdkTestDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(VIDEO_FRAME_CALLBACK, &CSdkTestDemoDlg::OnVideoFrameCallback)
	ON_BN_CLICKED(IDOK, &CSdkTestDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSdkTestDemoDlg::OnBnClickedCancel)
	ON_MESSAGE(RTC_EVENT_UCLOUD, &CSdkTestDemoDlg::OnRTCUCloudMsg)
	ON_BN_CLICKED(IDC_BUTTON_PUBC, &CSdkTestDemoDlg::OnBnClickedButtonPubC)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEROOM, &CSdkTestDemoDlg::OnBnClickedButtonLeaveroom)
	ON_BN_CLICKED(IDC_BUTTON_PUBS, &CSdkTestDemoDlg::OnBnClickedButtonPubs)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, &CSdkTestDemoDlg::OnBnClickedButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_MIXFILE, &CSdkTestDemoDlg::OnBnClickedButtonMixfile)
END_MESSAGE_MAP()


// CSdkTestDemoDlg ��Ϣ�������
BOOL CSdkTestDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	std::string channel = "userid_" + m_userid+ "@channel_" + URTCConfig::getInstance()->getRoomId();
	this->SetWindowTextW(Ansi2WChar(channel.data()).data());
	//InitMinDump();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect rcBtn;
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->GetWindowRect(&rcBtn);
	ScreenToClient(rcBtn);
	int y = rcBtn.bottom + 2;

	//������Ƶ����
	m_localWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, 0, y, 240, 240);
	m_localWnd->SetParent(this);
	m_localWnd->SetTitle(L"Local (Camera)");
	m_localWnd->SetUserId("camera");
	m_localWnd->RegisterCallback(this);

	//�������洰��
	m_screenWnd  = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_SCREEN, 242, y, 240, 240);
	//m_screenWnd->SetParent(this);
	m_screenWnd->SetTitle(L"Local (Screen)");
	m_screenWnd->SetUserId("screen");
	m_screenWnd->RegisterCallback(this);

	//Զ����Ⱦ����
	for (int i = 2; i <= 3; ++i) {
		CVideoWnd *pWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, 242 * i, y, 240, 240);
		//pWnd->SetParent(this);
		pWnd->RegisterCallback(this);
		m_remoteWnds.emplace_back(pWnd);
	}

	y += 242;
	for (int i = 0; i < 4; ++i) {
		CVideoWnd *pWnd = CreateVideoWindow(UCLOUD_RTC_MEDIATYPE_VIDEO, i * 242, y, 240, 240);
		//pWnd->SetParent(this);
		pWnd->RegisterCallback(this);
		m_remoteWnds.emplace_back(pWnd);
	}
	m_rtcengine = RTCEngineFactory::createRtcEngine(RTC_CHANNELTYPE_UCLOUD);
	m_rtcengine->InitRTCEngine(this->GetSafeHwnd());

	InitURTCConfig();
	_pFullScreenDlg = new VideoFullDlg();
	if (NULL != _pFullScreenDlg)
	{
		_pFullScreenDlg->Create(VideoFullDlg::IDD, this);
		_pFullScreenDlg->ShowWindow(SW_HIDE);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CSdkTestDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	if (m_mediadevice)
	{
		m_mediadevice->stopCaptureFrame();
	}
	UCloudRtcMediaDevice::destory();
	m_rtcengine->UnInitRTCEngine();
	CDialogEx::OnCancel();
}

LRESULT CSdkTestDemoDlg::OnVideoFrameCallback(WPARAM data, LPARAM lp)
{
	unsigned char* videoframe = (unsigned char*)data;
	int buflen = lp;
	CVideoPackageQueue::GetInstance()->PushVideoPackage(videoframe, buflen);
	delete[] videoframe;
	return 0;
}

LRESULT CSdkTestDemoDlg::OnRTCUCloudMsg(WPARAM data, LPARAM lp)
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

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
		if (code == 0)
		{
			GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_RECORD)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON_MIXFILE)->EnableWindow(true);
			OnMessageShow("���뷿��ɹ�");
		}
		else {
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;
			std::string desc = "���뷿��ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}
	}
}

void CSdkTestDemoDlg::OnReJoinFailHandler(std::string jsonmsg) {
	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;
		std::string desc = "���¼��뷿��ʧ�� " + msg + " " + errcode;
		OnMessageShow(desc);
	}
}

void CSdkTestDemoDlg::OnReJoinRoomHandler(std::string jsonmsg) {
	OnMessageShow("�����ɹ�");
}

void CSdkTestDemoDlg::OnLeaveRoomHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		if (code == 0)
		{
			GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
			SetDlgItemText(IDC_BUTTON_PUBC, L"����ý��");
			SetDlgItemText(IDC_BUTTON_PUBS, L"��������");
			GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_RECORD)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_MIXFILE)->EnableWindow(false);
			OnMessageShow("�˳�����ɹ�");
		}
		else
		{
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;
			std::string desc = "�˳�����ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}
		// �ͷ�������Դ
		m_localWnd->setUsed(false);
		m_screenWnd->setUsed(false);
		ReleaseUserAllRes();

		// �رմ����뿪����
		OnLeaveRoom();
	}
}

void CSdkTestDemoDlg::OnPulibshStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		int mtype = object["mtype"].GetInt();
		if (mtype == UCLOUD_RTC_MEDIATYPE_VIDEO)
		{
			OnPulibshCamStreamHandler(jsonmsg);
		}
		else {
			OnPulibshScreenStreamHandler(jsonmsg);
		}
	}
}

void CSdkTestDemoDlg::OnPulibshCamStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		if (code == 0)
		{
			SetDlgItemText(IDC_BUTTON_PUBC, L"ֹͣ����");
			OnMessageShow("����ͷ�����ɹ�");
			tRTCRenderView canvas;
			canvas.mVidoview = (void*)m_localWnd->GetVideoHwnd();
			canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
			canvas.mUserid = m_userid;
			canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
			canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_GDI;

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
			std::string desc = "����ͷ����ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}

	}
}

void CSdkTestDemoDlg::OnPulibshScreenStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		if (code == 0)
		{
			SetDlgItemText(IDC_BUTTON_PUBS, L"ֹͣ����");
			OnMessageShow("���淢���ɹ�");
			tRTCRenderView canvas;
			canvas.mVidoview = (void*)m_screenWnd->GetVideoHwnd();
			canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
			canvas.mUserid = m_userid;
			canvas.mStreamMtype = UCLOUD_RTC_MEDIATYPE_SCREEN;
			canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_GDI;
			m_screenWnd->setUsed(true);
			m_screenWnd->setReady(true);
			m_screenpub = true;
			m_rtcengine->StartLocalRender(canvas);
		}
		else {
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;
			std::string desc = "���淢��ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}

	}
}

void CSdkTestDemoDlg::OnUnPulibshStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		int mtype = object["mtype"].GetInt();
		if (mtype == UCLOUD_RTC_MEDIATYPE_VIDEO)
		{
			OnUnPulibshStreamCamHandler(jsonmsg);
		}
		else {
			OnUnPulibshStreamScreenHandler(jsonmsg);
		}
	}
}

void CSdkTestDemoDlg::OnUnPulibshStreamScreenHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
		if (code == 0)
		{
			OnMessageShow("������ȡ������");
		}
		else {
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;

			std::string desc = "ȡ������ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}

		SetDlgItemText(IDC_BUTTON_PUBS, L"��������");
		m_screenpub = false;
		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(true);
		m_screenWnd->setUsed(false);

	}
}

void CSdkTestDemoDlg::OnUnPulibshStreamCamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
		if (code == 0)
		{
			OnMessageShow("����ͷ��ȡ������");
		}
		else {
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;
			std::string desc = "ȡ������ʧ�� " + msg + " " + errcode;
			OnMessageShow(desc);
		}

		SetDlgItemText(IDC_BUTTON_PUBC, L"����ý��");
		GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(true);
		m_campub = false;
		m_localWnd->setUsed(false);

	}
}

void CSdkTestDemoDlg::OnSubStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		const rapidjson::Value& object = doc["data"];
		int mtype = object["mtype"].GetInt();
		std::string uid = object["uid"].GetString();

		char buf[32] = { 0 };
		sprintf_s(buf, "%d", mtype);
		eUCloudRtcMeidaType type = (mtype == 1) ? UCLOUD_RTC_MEDIATYPE_VIDEO : UCLOUD_RTC_MEDIATYPE_SCREEN;
		if (code == 0)
		{
			std::string msg = "���� " + uid + buf + "�ɹ�";
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
				canvas.mVidoview = (void*)videoview->GetVideoHwnd();
				canvas.mRenderMode = UCLOUD_RTC_RENDER_MODE_FIT;
				canvas.mUserid = uid.data();
				canvas.mStreamMtype = mtype;
				canvas.mRenderType = UCLOUD_RTC_RENDER_TYPE_D3D;
				m_rtcengine->StartRemoteRender(canvas);
			}

		}
		else {
			char num[32] = { 0 };
			sprintf_s(num, " err code = %d", code);
			std::string errcode = num;
			std::string msg = "���� " + uid + buf + " ʧ�� " + errcode;
			OnMessageShow(msg);
		}
	}
	
}

void CSdkTestDemoDlg::OnUnSubStreamHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		std::string msg = doc["msg"].GetString();
		const rapidjson::Value& object = doc["data"];
		int mtype = object["mtype"].GetInt();
		std::string uid = object["uid"].GetString();

		UnSubscribeStream(mtype, uid);
	}
}

void CSdkTestDemoDlg::OnStreamStHandler(std::string jsonmsg) {
	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		std::string cmd = object["cmd"].GetString();
		int mtype = object["mtype"].GetInt();
		std::string userid = object["uid"].GetString();

		if (cmd == "add")
		{
			tStreamInfo* stream = new tStreamInfo;
			stream->mStreamMtype = mtype;
			stream->mUserid = userid;
			stream->mEnalbeaudio = object["audio"].GetBool();
			stream->mEnalbevideo = object["video"].GetBool();
			stream->mEnalbedata = object["data"].GetBool();

			char buf[8] = { 0 };
			sprintf_s(buf, "%d", stream->mStreamMtype);
			m_streamsmap.insert(std::make_pair(stream->mUserid + buf, stream));
			std::string desc = "�����룺";
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
			std::string desc = "���Ƴ���";
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
}

void CSdkTestDemoDlg::OnUserStHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		std::string cmd = object["cmd"].GetString();
		std::string userid = object["uid"].GetString();

		if (cmd == "join")
		{
			userit uit = m_hashSessions.find(userid);
			if (uit == m_hashSessions.end())
			{
				tUserInfo* user = new tUserInfo;
				user->mUserid = userid;
				m_hashSessions.emplace(std::make_pair(userid, user));
			}

			OnMessageShow("userid: " + userid + " ���뷿��");
		}
		else if (cmd == "leave")
		{
			UserLeave(userid);
			OnMessageShow("userid: " + userid + " �뿪����");
		}
	}
}

void  CSdkTestDemoDlg::OnServerReconnectingHandler(std::string jsonmsg) {
	OnMessageShow(" �������Ͽ������ڳ�������......");
}

void CSdkTestDemoDlg::OnServerDisconnectHandler(std::string jsonmsg) {
	GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON_PUBC, L"����ý��");
	SetDlgItemText(IDC_BUTTON_PUBS, L"��������");
	GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);

	m_localWnd->setUsed(false);
	m_screenWnd->setUsed(false);

	m_campub = false;
	m_screenpub = false;
	m_audiocheck.SetCheck(1);
	m_videocheck.SetCheck(1);
	OnMessageShow("����������Ͽ�");
}

void CSdkTestDemoDlg::OnSdkErrorHandler(std::string jsonmsg) {
	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
		char num[32] = { 0 };
		sprintf_s(num, " err code = %d", code);
		std::string errcode = num;

		OnMessageShow("sdkerror: " + errcode);
	}
}

void CSdkTestDemoDlg::OnKickoffHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		char num[32] = { 0 };
		sprintf_s(num, " = %d", code);
		std::string errcode = num;
		GetDlgItem(IDC_BUTTON_LEAVEROOM)->EnableWindow(false);
		SetDlgItemText(IDC_BUTTON_PUBC, L"����ý��");
		SetDlgItemText(IDC_BUTTON_PUBS, L"��������");
		GetDlgItem(IDC_BUTTON_PUBC)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PUBS)->EnableWindow(false);
		m_campub = false;
		m_screenpub = false;
		m_localWnd->setUsed(false);
		m_screenWnd->setUsed(false);

		ReleaseUserAllRes();
		OnMessageShow("kick off : " + errcode);
	}
	
}

void CSdkTestDemoDlg::OnLocalStreamMuteHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
	
		const rapidjson::Value& object = doc["data"];
		int mediatype = object["mtype"].GetInt();
		int trackype = object["ttype"].GetInt();
		bool mute = object["mute"].GetBool();

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
			std::string desc = "�����ɹ�" + msg + " " + content;
			OnMessageShow(desc);

		}
		else {
			char mutecontent[128] = { 0 };
			sprintf_s(mutecontent, " err code=%d&&mtype=%d&&ttype=%d&&op=%d", code, mediatype, trackype, mute);
			std::string content = mutecontent;
			std::string desc = "mute Զ�� " + msg + " " + content;
			OnMessageShow(desc);
		}
	}
}

void CSdkTestDemoDlg::OnRemoteStreamMuteHandler(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		const rapidjson::Value& object = doc["data"];
		std::string uid = object["uid"].GetString();
		int mediatype = object["mtype"].GetInt();
		int trackype = object["ttype"].GetInt();
		bool mute = object["mute"].GetBool();
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
			std::string desc = "�����ɹ�" + msg + " " + content;
			OnMessageShow(desc);

		}
		else {
			char mutecontent[128] = { 0 };
			sprintf_s(mutecontent, "err code=%d&&uid=%s mtype=%d&&ttype=%d&&op=%d", code,
				uid.data(), mediatype, trackype, mute);
			std::string content = mutecontent;
			std::string desc = "mute Զ�� " + msg + " " + content;
			OnMessageShow(desc);
		}
	}
	
}

void CSdkTestDemoDlg::OnRemoteTrackStNotify(std::string jsonmsg) {

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{

		const rapidjson::Value& object = doc["data"];
		std::string uid = object["uid"].GetString();
		int mtype = object["mtype"].GetInt();
		int ttype = object["ttype"].GetInt();
		bool mute = object["mute"].GetBool();
		if (mtype == UCLOUD_RTC_MEDIATYPE_SCREEN)
		{
			std::string desc = mute ? "�ر�" : "��";
			OnMessageShow(uid + " " + desc + " " + "����");
		}
		else {
			if (ttype == UCLOUD_RTC_TRACKTYPE_AUDIO)
			{
				std::string desc = mute ? "�ر�" : "��";
				OnMessageShow(uid + " " + desc + " " + "��˷�");
			}
			else
			{
				std::string desc = mute ? "�ر�" : "��";
				OnMessageShow(uid + " " + desc + " " + "����ͷ");
			}

		}
	}
}

void CSdkTestDemoDlg::OnRemoteAudioVolHandler(std::string jsonmsg)
{

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		std::string uid = object["uid"].GetString();
		int vol = object["vol"].GetInt();
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
	
}

void CSdkTestDemoDlg::OnLocalAudioVolHandler(std::string jsonmsg)
{
	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		int vol = object["vol"].GetInt();
		m_localWnd->setVol(vol);
	}
}

void CSdkTestDemoDlg::OnRemoteStHandler(std::string jsonmsg)
{

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		std::string uid = object["uid"].GetString();
		int mediatype = object["mtype"].GetInt();
		int tracktype = object["ttype"].GetInt();
		int bitrate = object["bitrate"].GetInt();
		float lostrate = object["lostrate"].GetInt();

		if (tracktype == UCLOUD_RTC_TRACKTYPE_VIDEO)
		{
			char buf[256] = { 0 };
			int height = object["height"].GetInt();
			int width = object["width"].GetInt();
			int framerate = object["framerate"].GetInt();
			sprintf_s(buf, "%s mtype:%d %d %0.2f height:%d width:%d framerate:%d",
				uid.data(), mediatype, bitrate, lostrate, height, width, framerate);
			std::string info = buf;
			//OnMessageShow("Զ����Ƶ: " + info);
		}
		else
		{
			char buf[256] = { 0 };
			sprintf_s(buf, "%s mtype:%d %d %0.2f ",
				uid.data(), mediatype, bitrate, lostrate);
			std::string info = buf;
			//OnMessageShow("Զ����Ƶ: " + info);
		}
	}
}

void CSdkTestDemoDlg::OnSendStHandler(std::string jsonmsg)
{
	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		const rapidjson::Value& object = doc["data"];
		int mediatype = object["mtype"].GetInt();
		int tracktype = object["ttype"].GetInt();
		int bitrate = object["bitrate"].GetInt();
		float lostrate = object["lostrate"].GetInt();

		if (tracktype == UCLOUD_RTC_TRACKTYPE_VIDEO)
		{
			char buf[256] = { 0 };
			int height = object["height"].GetInt();
			int width = object["width"].GetInt();
			int framerate = object["framerate"].GetInt();
			sprintf_s(buf, "mtype:%d %d %0.2f height:%d*width:%d*framerate:%d",
				mediatype, bitrate, lostrate, height, width, framerate);
			//OnMessageShow("������Ƶ: " + info);
		}
		else
		{
			char buf[256] = { 0 };
			sprintf_s(buf, "mtype:%d %d %0.2f ",
				mediatype, bitrate, lostrate);
			std::string info = buf;
			//OnMessageShow("������Ƶ: " + info);
		}
	}
}

void CSdkTestDemoDlg::OnStartRecord(std::string jsonmsg)
{

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();

		const rapidjson::Value& object = doc["data"];
		std::string recordid = object["recordid"].GetString();
		std::string filename = object["filename"].GetString();
		std::string bucket = object["bucket"].GetString();
		std::string region = object["region"].GetString();
		if (code == 0)
		{
			m_startrecord = true;
			SetDlgItemText(IDC_BUTTON_RECORD, L"ֹͣ¼��");
			OnMessageShow("¼���ַ��");
			char mutecontent[1024] = { 0 };
			sprintf_s(mutecontent, "https://%s.%s.ufileos.com/%s.mp4 ", bucket.data(), region.data(), filename.data());
			//std::string content = mutecontent;
			//std::string desc = "����¼�Ƴɹ� " + msg + " " + content;
			OnMessageShow(mutecontent);

		}
		else
		{
			char mutecontent[128] = { 0 };
			sprintf_s(mutecontent, " err code=%d", code);
			std::string content = mutecontent;
			std::string desc = "����¼��ʧ�� " + msg + " " + content;
			OnMessageShow(desc);
		}
	}
}

void CSdkTestDemoDlg::OnStopRecord(std::string jsonmsg)
{

	rapidjson::Document doc;
	if (!doc.Parse(jsonmsg.data()).HasParseError())
	{
		int code = doc["code"].GetInt();
		std::string msg = doc["msg"].GetString();
		if (code == 0)
		{
			m_startrecord = true;
			SetDlgItemText(IDC_BUTTON_RECORD, L"����¼��");
			std::string desc = "ֹͣ¼�Ƴɹ� ";
			OnMessageShow(desc);

		}
		else
		{
			char mutecontent[128] = { 0 };
			sprintf_s(mutecontent, " err code=%d", code);
			std::string content = mutecontent;
			std::string desc = "ֹͣ¼��ʧ�� " + msg + " " + content;
			OnMessageShow(desc);
		}
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
			std::string msg = "�Ѵﵽ����Ԥ����������";
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
		SetDlgItemText(IDC_BUTTON_PUBC, L"����ý��");
		m_campub = !m_campub;
		if (m_mediadevice)
		{
			m_mediadevice->stopCaptureFrame();
		}
	}
	else {
		bool audioEnable = m_audiocheck.GetCheck();
		bool videoEnable = m_videocheck.GetCheck();
		if (!audioEnable && !videoEnable)
		{
			AfxMessageBox(L"������Ƶ������Ҫѡ��һ��ý��");
			return;
		}
		m_localWnd->SetUserId("camera");
		tRTCStreamInfo info;
		info.mEnableVideo = videoEnable;
		info.mEnableAudio = audioEnable;
		info.mEnableData = false;
		info.mStreamMtype = UCLOUD_RTC_MEDIATYPE_VIDEO;
		info.mUserid = m_userid;
		CString text;
		GetDlgItemText(IDC_EDIT_RTSP1, text);
		std::string utf8name = WChatToUTF8Str(text.GetBuffer());
		char* rtspurl = const_cast<char*> (utf8name.data());
		if (strlen(rtspurl) > 0)
		{
			m_rtcengine->EnableRtspSource(UCLOUD_RTC_MEDIATYPE_VIDEO, true, rtspurl);
		}
		else 
		{
			m_rtcengine->EnableRtspSource(UCLOUD_RTC_MEDIATYPE_VIDEO, false, "");
		}
		if (m_mediadevice)
		{
			m_mediadevice->startCaptureFrame(UCLOUD_RTC_VIDEO_PROFILE_640_360, this);
		}
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
		SetDlgItemText(IDC_BUTTON_PUBS, L"��������");
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
		CString text;
		GetDlgItemText(IDC_EDIT_RTSP2, text);
		std::string utf8name = WChatToUTF8Str(text.GetBuffer());
		char* rtspurl = const_cast<char*> (utf8name.data());
		if (strlen(rtspurl) > 0)
		{
			m_rtcengine->EnableRtspSource(UCLOUD_RTC_MEDIATYPE_SCREEN, true, rtspurl);
		}
		else
		{
			m_rtcengine->EnableRtspSource(UCLOUD_RTC_MEDIATYPE_SCREEN, false, "");
		}
		int ret = m_rtcengine->PublishStream(info);
		m_screenWnd->SetUserId("screen");
	}
}

void CSdkTestDemoDlg::onCaptureFrame(unsigned char* videoframe, int buflen)
{
	unsigned char* buf = new unsigned char[buflen];
	memset(buf, 0, buflen);
	memcpy(buf, videoframe, buflen);
	PostMessage(VIDEO_FRAME_CALLBACK, (WPARAM)buf, buflen);
}

bool CSdkTestDemoDlg::doCaptureFrame(tUCloudRtcVideoFrame* videoframe)
{

	SIZE_T nBufferSize = 0x800000;
	memset(m_lpImageBuffer, 0, 0x800000);
	BOOL bSuccess = CVideoPackageQueue::GetInstance()->PopVideoPackage(m_lpImageBuffer, &nBufferSize);
	if (!bSuccess)
		return false;
	if (videoframe)
	{
		videoframe->mDataBuf = m_lpImageBuffer;
		videoframe->mHeight = 360;
		videoframe->mWidth = 640;
		videoframe->mVideoType = UCLOUD_RTC_VIDEO_FRAME_TYPE_I420;
	}
	return true;
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
	if (m_rtcengine)
	{
		if (m_startrecord)
		{
			m_rtcengine->StopRecord();
		}
		else
		{
			tRecordConfig recordconfig;
			recordconfig.mMainviewmediatype = 1;
			recordconfig.mMainviewuid = m_userid.data();
			recordconfig.mProfile = 1;
			recordconfig.mRecordType = 2;
			recordconfig.mWatermarkPos = 1;

			recordconfig.mWaterMarkType = 3;
			recordconfig.mWatermarkUrl = "hello urtc";
			recordconfig.mIsaverage = false;
			recordconfig.mMixerTemplateType = 5;
			m_rtcengine->StartRecord(recordconfig);
		}
	}
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
