// VideoTips.cpp : implementation file
//

#include "stdafx.h"
#include "SdkTestDemo.h"
#include "VideoTips.h"
#include "afxdialogex.h"


// VideoTips dialog

IMPLEMENT_DYNAMIC(VideoTips, CDialogEx)

VideoTips::VideoTips(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TIPS, pParent)
{

}

VideoTips::~VideoTips()
{
}

void VideoTips::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VideoTips, CDialogEx)
	ON_BN_CLICKED(IDOK, &VideoTips::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &VideoTips::OnBnClickedCancel)
END_MESSAGE_MAP()


// VideoTips message handlers


void VideoTips::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void VideoTips::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}
