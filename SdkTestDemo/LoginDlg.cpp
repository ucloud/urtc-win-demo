// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "DeviceTestDlg.h"
#include "ConfigDlg.h"
#include "SdkTestDemoDlg.h"
#include "SdkUtil.h"
#include "URTCConfig.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_setting);
	DDX_Control(pDX, IDC_EDIT_USERID, m_userid);
	DDX_Control(pDX, IDC_EDIT_ROOMID, m_roomid);
	DDX_Control(pDX, IDC_MUTE_CAM_BEFOREJOIN, m_mutecambefore);
	DDX_Control(pDX, IDC_MUTE_MIC_BEFOREJOIN, m_mutemicbefore);
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_userid.SetWindowTextW(Ansi2WChar(URTCConfig::getInstance()->getUserId().data()).data());
	m_roomid.SetWindowTextW(Ansi2WChar(URTCConfig::getInstance()->getRoomId().data()).data());
	return TRUE;
}



BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_TEST, &CLoginDlg::OnBnClickedButtonDeviceTest)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLoginDlg::OnBnClickedButtonSetting)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButtonLogin()
{
	CString utext;
	m_userid.GetWindowTextW(utext);
	std::string userid = WChatToUTF8Str(utext.GetBuffer());
	if (userid.length() <= 0)
	{
		AfxMessageBox(L"用户ID");
		return;
	}

	CString rtext;
	m_roomid.GetWindowTextW(rtext);
	std::string roomid = WChatToUTF8Str(rtext.GetBuffer());
	if (roomid.length() <= 0)
	{
		AfxMessageBox(L"请输入房间ID");
		return;
	}

	URTCConfig::getInstance()->setUserId(userid);
	URTCConfig::getInstance()->setRoomId(roomid);

	URTCConfig::getInstance()->setMuteCamBeforeJoin(m_mutecambefore.GetCheck());
	URTCConfig::getInstance()->setMuteMicBeforeJoin(m_mutemicbefore.GetCheck());

	CSdkTestDemoDlg sdkdlg;
	sdkdlg.DoModal();
}


void CLoginDlg::OnBnClickedButtonDeviceTest()
{
	// TODO: 在此添加控件通知处理程序代码
	CDeviceTestDlg devdlg;
	devdlg.DoModal();
}


void CLoginDlg::OnBnClickedButtonSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	CConfigDlg configdlg;
	configdlg.DoModal();
}
