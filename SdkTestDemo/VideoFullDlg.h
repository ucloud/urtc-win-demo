#pragma once
#include "VideoWnd.h"

// VideoFullDlg 对话框

class VideoFullDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VideoFullDlg)

public:
	VideoFullDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VideoFullDlg();

// 对话框数据
	enum 
	{
		IDD = IDD_VIDEO_WND_FULL
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void BindChild(CVideoWnd* pDlg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
