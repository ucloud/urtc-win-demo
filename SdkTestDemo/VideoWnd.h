#pragma once
#include <string>
#include "stdafx.h"
#include "resource.h"
#include "UCloudRTCComDefine.h"
#include "afxcmn.h"

class CVideoWndCallback {
public:
    virtual ~CVideoWndCallback() {}
    virtual void OnMuteAudio(std::string userid, eUCloudRtcMeidaType mediatype,  bool mute) = 0;
	virtual void OnMuteVideo(std::string userid, eUCloudRtcMeidaType mediatype, bool mute) = 0;
    virtual void OnCloseMedia(std::string type, std::string id) = 0;
};

// CVideoWnd 对话框

class CVideoWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoWnd)

    CVideoWndCallback *m_pObserver;
    int m_nWidth;
    int m_nHeight;
    std::wstring m_Title;
	std::string m_userid;

    int m_nToolBarHeight;
    int m_nCtrlBarHeight;

	CToolTipCtrl    m_stat;

    CRect m_rcContainer;
	bool m_isUse;
	bool m_isReady;
    void centerVideo(CRect rcContainer, int w, int h);

public:
	CVideoWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoWnd();

	void Reset();

	bool isUsed();
	void setUsed(bool use);
	void setReady(bool ready);
    int  RegisterCallback(CVideoWndCallback *o);
    HWND GetVideoHwnd();
    void  SetResolution(int w, int h) {
        bool bChanged = false;
        if (m_nWidth != w || m_nHeight != h) {
            bChanged = true;
        }
        m_nWidth = w;
        m_nHeight = h;
        centerVideo(m_rcContainer, w, h);
        if (bChanged) {
            SetTitle(m_Title);
        }

    }

    void SetTitle(std::wstring strTitle);
	void SetType(eUCloudRtcMeidaType type);
	void TestEnble();

	void SetUserId(std::string streamid);
	std::string GetUserId();

	void muteAudio(bool mute);
	void muteVideo(bool mute);

	void setVol(int level);

	eUCloudRtcMeidaType m_type; //渲染type
	bool m_fullscreen;
	CWnd* m_parent;
	CRect m_old;
	bool m_videostart;
	bool m_audiomute;
	bool m_videomute;
	int m_xpos;
	int m_ypos;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_WND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnVideoOn();
	afx_msg void OnBnClickedBtnMuteA();
	afx_msg void OnBnClickedBtnMuteV();
	CProgressCtrl m_volprocess;
	CProgressCtrl m_vol;
	bool m_isfull;
	afx_msg void OnStnDblclickVideo();
};
