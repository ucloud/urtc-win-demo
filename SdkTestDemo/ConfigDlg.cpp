// ConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"
#include "URTCConfig.h"
#include "SdkUtil.h"


// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_DIALOG, pParent)
{
}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SECKEY, m_seckey);
	DDX_Control(pDX, IDC_CHECK_AUTOPUB, m_autopub);
	DDX_Control(pDX, IDC_CHECK_AUTOSUB, m_autosub);
	DDX_Control(pDX, IDC_CHECK_AUTOPUBV, m_pubvideo);
	DDX_Control(pDX, IDC_CHECK_AUTOPUBA, m_pubaudio);
	DDX_Control(pDX, IDC_CHECK_AUTOPUBS, m_pubscreen);
	DDX_Control(pDX, IDC_CHECK_PUBROLE, m_rolepub);
	DDX_Control(pDX, IDC_CHECK_SUBROLE, m_rolesub);
	DDX_Control(pDX, IDC_EDIT_APPID, m_appid);
	DDX_Control(pDX, IDC_CHECK_AUDIOONLY, m_audioonly);
	DDX_Control(pDX, IDC_COM_PROFILE, m_videoprofile);
	DDX_Radio(pDX, IDC_RADIO_NORMAL, m_sdkmode);
	DDX_Radio(pDX, IDC_RADIO_CH_C, m_chtype);
	DDX_Control(pDX, IDC_SEC_KEY, m_sectxt);
	DDX_Control(pDX, IDC_COM_CODEC, m_codectype);
	DDX_Control(pDX, IDC_CHECK_PRIVATEMODE, m_privatemode);
	DDX_Control(pDX, IDC_EDIT_PRIVATEADDR, m_privateaddr);
	DDX_Control(pDX, IDC_CHECK_INTELMEDIACODEC, m_intelmediacodec);
	
}

BOOL CConfigDlg::OnInitDialog()
{
	eUCloudRtcChannelType chtype = URTCConfig::getInstance()->getChannelType();
	if (chtype == UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION)
	{
		m_chtype = 0;
	}
	else
	{
		m_chtype = 1;
	}

	eUCloudRtcSdkMode sdkmode = URTCConfig::getInstance()->getSdkMode();
	if (sdkmode == UCLOUD_RTC_SDK_MODE_NORMAL)
	{
		m_sdkmode = 0;
	}
	else
	{
		m_sdkmode = 1;
	}
	CDialogEx::OnInitDialog();
	m_videoprofile.InsertString(0, L"320*180");
	m_videoprofile.InsertString(1, L"320*240");
	m_videoprofile.InsertString(2, L"640*360");
	m_videoprofile.InsertString(3, L"640*480");
	m_videoprofile.InsertString(4, L"1280*720");
	m_videoprofile.InsertString(5, L"1920*1080");
	int select = ((int)URTCConfig::getInstance()->getVideoProfile() ) -1;
	if (select<0 || select>5)
	{
		select = 0;
	}
	m_videoprofile.SetCurSel(select);

	//m_seckey.SetWindowTextW(Ansi2WChar(URTCConfig::getInstance()->getSecKey().data()).data());
	m_seckey.SetWindowTextW(Ansi2WChar("*****************************").data());
	m_appid.SetWindowTextW(Ansi2WChar(URTCConfig::getInstance()->getAppId().data()).data());

	bool audioonly = URTCConfig::getInstance()->isAudioOnly();
	m_audioonly.SetCheck(audioonly? 1:0);
	if (audioonly)
	{
		m_videoprofile.EnableWindow(FALSE);
		m_pubscreen.EnableWindow(FALSE);
		m_pubvideo.EnableWindow(FALSE);

		m_pubaudio.SetCheck(URTCConfig::getInstance()->isAutoPubAudio() ? 1 : 0);
	}
	else 
	{
		m_pubscreen.SetCheck(URTCConfig::getInstance()->isAutoPubScreen()? 1:0);
		m_pubvideo.SetCheck(URTCConfig::getInstance()->isAutoPubVideo() ? 1 : 0);
		m_pubaudio.SetCheck(URTCConfig::getInstance()->isAutoPubAudio() ? 1 : 0);
	}

	m_autopub.SetCheck(URTCConfig::getInstance()->isAutoPublish() ? 1 : 0);
	m_autosub.SetCheck(URTCConfig::getInstance()->isAutoSubscribe() ? 1 : 0);

	eUCloudRtcUserStreamRole role = URTCConfig::getInstance()->getStreamRole();
	switch (role)
	{
	case UCLOUD_RTC_USER_STREAM_ROLE_PUB :
	{
		m_rolesub.SetCheck(0);
		m_rolepub.SetCheck(1);
	}
		break;
	case  UCLOUD_RTC_USER_STREAM_ROLE_SUB :
	{
		m_rolesub.SetCheck(1);
		m_rolepub.SetCheck(0);
	}
		break;
	case UCLOUD_RTC_USER_STREAM_ROLE_BOTH :
	{
		m_rolesub.SetCheck(1);
		m_rolepub.SetCheck(1);
	}
		break;
	default:
	{
		m_rolesub.SetCheck(1);
		m_rolepub.SetCheck(0);
	}
		break;
	}
	if (sdkmode == 0)
	{
		m_sectxt.ShowWindow(FALSE);
		m_seckey.ShowWindow(FALSE);
	}
	else
	{
		m_sectxt.ShowWindow(TRUE);
		m_seckey.ShowWindow(TRUE);
	}

	m_codectype.InsertString(0, L"VP8");
	m_codectype.InsertString(1, L"H264");

	m_codectype.SetCurSel(1);

	m_privatemode.SetCheck(URTCConfig::getInstance()->getPrivateMode() ? 1 : 0);
	m_privateaddr.SetWindowTextW(Ansi2WChar(URTCConfig::getInstance()->getPrivatAddr().data()).data());

	m_intelmediacodec.SetCheck(URTCConfig::getInstance()->getIntelMediaCodec() ? 1 : 0);
	
	return TRUE;
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CConfigDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_RADIO_NORMAL, &CConfigDlg::OnBnClickedRadioNormal)
	ON_BN_CLICKED(IDC_RADIO_TRIVAL, &CConfigDlg::OnBnClickedRadioNormal)
	ON_BN_CLICKED(IDC_RADIO_CH_C, &CConfigDlg::OnBnClickedRadioChC)
	ON_BN_CLICKED(IDC_RADIO_LIVE, &CConfigDlg::OnBnClickedRadioChC)
	ON_BN_CLICKED(IDC_CHECK_AUDIOONLY, &CConfigDlg::OnBnClickedCheckAudioonly)
	ON_STN_CLICKED(IDC_SEC_KEY, &CConfigDlg::OnStnClickedSecKey)
	ON_BN_CLICKED(IDC_CHECK_PUBROLE, &CConfigDlg::OnBnClickedCheckPubrole)
	ON_BN_CLICKED(IDC_CHECK_SUBROLE, &CConfigDlg::OnBnClickedCheckSubrole)
	ON_BN_CLICKED(IDC_CHECK_PRIVATEMODE, &CConfigDlg::OnBnClickedCheckPrivatemode)
	ON_EN_CHANGE(IDC_EDIT_PRIVATEADDR, &CConfigDlg::OnEnChangeEditPrivateaddr)
	ON_BN_CLICKED(IDC_CHECK_INTELMEDIACODEC, &CConfigDlg::OnBnClickedCheckIntelmediacodec)
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序
void CConfigDlg::OnPaint()
{
	CDialogEx::OnPaint();
}

void CConfigDlg::OnBnClickedButtonSave()
{
	URTCConfig::getInstance()->setSdkMode((eUCloudRtcSdkMode)m_sdkmode);
	URTCConfig::getInstance()->setChannelType((eUCloudRtcChannelType)m_chtype);
	CString appid;
	m_appid.GetWindowTextW(appid);
	std::string appistr = WChatToUTF8Str(appid.GetBuffer());
	if (appistr.length()>0)
	{
		URTCConfig::getInstance()->setAppId(appistr);
	}

	if (m_sdkmode == 1)
	{
		CString seckey;
		m_seckey.GetWindowTextW(seckey);
		std::string keystr = WChatToUTF8Str(seckey.GetBuffer());
		if (keystr.length() > 0 && keystr != "*****************************")
		{
			URTCConfig::getInstance()->setSecKey(keystr);
		}
	}

	URTCConfig::getInstance()->setVideoProfile((eUCloudRtcVideoProfile)
		(m_videoprofile.GetCurSel() +1) );

	int pubrcheck = m_rolepub.GetCheck();
	int subrcheck = m_rolesub.GetCheck();

	if (m_chtype == 1)
	{
		if (pubrcheck && subrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_BOTH);
		}
		else if (pubrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_PUB);
		}
		else if (subrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_SUB);
		}
		else
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_SUB);
		}
		
	}
	else {
		if (pubrcheck && subrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_BOTH);
		}else if (pubrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_PUB);
		}else if (subrcheck)
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_SUB);
		}
		else 
		{
			URTCConfig::getInstance()->setStreamRole(UCLOUD_RTC_USER_STREAM_ROLE_SUB);
		}
	}

	int audioonly = m_audioonly.GetCheck();
	if (audioonly)
	{
		URTCConfig::getInstance()->setAudioOnly(true);
	}
	else {
		URTCConfig::getInstance()->setAudioOnly(false);
	}

	int autopub = m_autopub.GetCheck();
	if (autopub)
	{
		URTCConfig::getInstance()->setAutoPublish(true);
	}
	else {
		URTCConfig::getInstance()->setAutoPublish(false);
	}

	int autosub = m_autosub.GetCheck();
	if (autosub)
	{
		URTCConfig::getInstance()->setAutoSubscribe(true);
	}
	else {
		URTCConfig::getInstance()->setAutoSubscribe(false);
	}

	int pubvideo = m_pubvideo.GetCheck();
	if (pubvideo)
	{
		URTCConfig::getInstance()->setAutoPubVideo(true);
	}
	else {
		URTCConfig::getInstance()->setAutoPubVideo(false);
	}

	int pubaudio = m_pubaudio.GetCheck();
	if (pubaudio)
	{
		URTCConfig::getInstance()->setAutoPubAudio(true);
	}
	else {
		URTCConfig::getInstance()->setAutoPubAudio(false);
	}

	int pubscreen = m_pubscreen.GetCheck();
	if (pubscreen)
	{
		URTCConfig::getInstance()->setAutoPubScreen(true);
	}
	else {
		URTCConfig::getInstance()->setAutoPubScreen(false);
	}

	URTCConfig::getInstance()->setCodecType((eUCloudRtcVideoCodec)
		(m_codectype.GetCurSel() + 1));

	int privatemode = m_privatemode.GetCheck();
	if (privatemode) {
		URTCConfig::getInstance()->setPrivateMode(privatemode);
		CString addr;
		m_privateaddr.GetWindowTextW(addr);
		std::string addrstr = WChatToUTF8Str(addr.GetBuffer());
		if (addrstr.length() > 0)
		{
			URTCConfig::getInstance()->setPrivateAddr(addrstr);
		}
	}
	else {
		URTCConfig::getInstance()->setPrivateMode(false);
	}

	m_intelmediacodec.GetCheck() ? URTCConfig::getInstance()->setIntelMediaCodec(true):URTCConfig::getInstance()->setIntelMediaCodec(false);
	CDialogEx::OnOK();
}


void CConfigDlg::OnBnClickedRadioNormal()
{
	UpdateData(TRUE);
	if (m_sdkmode == 1)
	{
		m_sectxt.ShowWindow(TRUE);
		m_seckey.ShowWindow(TRUE);
	}
	else 
	{
		m_sectxt.ShowWindow(FALSE);
		m_seckey.ShowWindow(FALSE);
	}
}


void CConfigDlg::OnBnClickedRadioChC()
{
	UpdateData(TRUE);
	int pubrcheck = m_rolepub.GetCheck();
	int subrcheck = m_rolesub.GetCheck();


	m_rolepub.SetCheck(1);
	m_rolesub.SetCheck(1);

}


void CConfigDlg::OnBnClickedCheckAudioonly()
{
	UpdateData(TRUE);
	int checked = m_audioonly.GetCheck();
	if (checked == 0)
	{
		m_videoprofile.EnableWindow(TRUE);
		m_pubscreen.EnableWindow(TRUE);
		m_pubvideo.EnableWindow(TRUE);
	}
	else 
	{
		m_videoprofile.EnableWindow(FALSE);
		m_pubscreen.EnableWindow(FALSE);
		m_pubvideo.EnableWindow(FALSE);
	}
}


void CConfigDlg::OnStnClickedSecKey()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CConfigDlg::OnBnClickedCheckPubrole()
{
	/*if (m_chtype == 1)
	{
		if (m_rolesub.GetCheck())
		{
			m_rolesub.SetCheck(0);
		}
	}*/
}


void CConfigDlg::OnBnClickedCheckSubrole()
{
	/*if (m_chtype == 1)
	{
		if (m_rolepub.GetCheck())
		{
			m_rolepub.SetCheck(0);
		}
	}*/
}




void CConfigDlg::OnBnClickedCheckPrivatemode()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CConfigDlg::OnEnChangeEditPrivateaddr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CConfigDlg::OnBnClickedCheckIntelmediacodec()
{
	// TODO: 在此添加控件通知处理程序代码
}
