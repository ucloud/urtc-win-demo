#pragma once
#include "afxwin.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CButton m_setting;
	CEdit m_userid;
	CEdit m_roomid;
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonDeviceTest();
	afx_msg void OnBnClickedButtonSetting();
	CButton m_mutecambefore;
	CButton m_mutemicbefore;
};
