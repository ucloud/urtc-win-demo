#pragma once
#include "stdafx.h"


// VideoTips dialog

class VideoTips : public CDialogEx
{
	DECLARE_DYNAMIC(VideoTips)

public:
	VideoTips(CWnd* pParent = NULL);   // standard constructor
	virtual ~VideoTips();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
