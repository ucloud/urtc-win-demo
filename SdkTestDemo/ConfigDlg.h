#pragma once
#include "afxwin.h"


// CConfigDlg 对话框

class CConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonSave();

	CEdit m_seckey;
	CButton m_autopub;
	CButton m_autosub;
	CButton m_pubvideo;
	CButton m_pubaudio;
	CButton m_pubscreen;
	CButton m_rolepub;
	CButton m_rolesub;
	CEdit m_appid;
	CButton m_audioonly;

	CComboBox m_videoprofile;
	int m_sdkmode;
	int m_chtype;
	afx_msg void OnBnClickedRadioNormal();
	afx_msg void OnBnClickedRadioChC();
	CStatic m_sectxt;
	afx_msg void OnBnClickedCheckAudioonly();
};
