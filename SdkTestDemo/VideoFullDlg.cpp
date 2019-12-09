// VideoFullDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoFullDlg.h"
#include "afxdialogex.h"


// VideoFullDlg 对话框

IMPLEMENT_DYNAMIC(VideoFullDlg, CDialogEx)

VideoFullDlg::VideoFullDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(VideoFullDlg::IDD, pParent)
{

}

VideoFullDlg::~VideoFullDlg()
{
}

void VideoFullDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VideoFullDlg, CDialogEx)
END_MESSAGE_MAP()


// VideoFullDlg 消息处理程序


BOOL VideoFullDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int cx,cy; 
	cx = GetSystemMetrics(SM_CXSCREEN); 
	cy = GetSystemMetrics(SM_CYSCREEN); 
	CRect rcTemp; 
	rcTemp.BottomRight() = CPoint(cx, cy); 
	rcTemp.TopLeft() = CPoint(0, 0); 
	MoveWindow(&rcTemp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//
void VideoFullDlg::BindChild(CVideoWnd* pDlg)
{
	if (NULL != pDlg)
	{
		CRect rc;
		GetClientRect(&rc);
		::SetParent(pDlg->GetVideoHwnd(), this->GetSafeHwnd());
		::MoveWindow(pDlg->GetVideoHwnd(), rc.left, rc.top,
			(rc.right - rc.left), (rc.bottom - rc.top), false);
	}
}


BOOL VideoFullDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		//判断是否按下键盘Enter键
		if(pMsg->wParam== VK_ESCAPE)
		{
			//Do anything what you want to
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
