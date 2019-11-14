// VideoWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "VideoWnd.h"
#include "afxdialogex.h"
#include "SdkUtil.h"


// CVideoWnd 对话框

IMPLEMENT_DYNAMIC(CVideoWnd, CDialogEx)

CVideoWnd::CVideoWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEO_WND, pParent)
{
    m_nWidth = 640;
    m_nHeight = 480;
    m_nToolBarHeight = m_nCtrlBarHeight = 0;
	m_fullscreen = false;
	m_parent = pParent;
	m_videostart = true;
	m_isUse = false;
	m_audiomute = false;
	m_videomute = false;
	m_isReady = false;
	m_isfull = false;
}

CVideoWnd::~CVideoWnd()
{
}

bool CVideoWnd::isUsed() {
	return m_isUse;
}

void  CVideoWnd::Reset() {
	m_videostart = true;
	m_audiomute = false;
	m_videomute = false;
	m_userid = "";
	m_Title = L"";
	SetTitle(m_Title);
	m_isReady = false;
	m_vol.SetPos(0);

	CString str = L"MuteV";
	SetDlgItemText(IDC_BTN_MUTE_V, str);

	CString stra = L"MuteA";
	SetDlgItemText(IDC_BTN_MUTE_A, stra);
	GetDlgItem(IDC_VIDEO)->Invalidate(TRUE);
}

void CVideoWnd::setUsed(bool use) {
	m_isUse = use;
	if (!m_isUse)
	{
		Reset();
	}
}

void CVideoWnd::setReady(bool ready) {
	m_isReady = ready;
	m_audiomute = false;
	m_videomute = false;
}

void CVideoWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS4, m_vol);
}

BOOL CVideoWnd::PreTranslateMessage(MSG* pMsg) {
	m_stat.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CVideoWnd, CDialogEx)
    ON_WM_SIZE()
    ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CVideoWnd::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_VIDEO_ON, &CVideoWnd::OnBnClickedBtnVideoOn)
	ON_BN_CLICKED(IDC_BTN_MUTE_A, &CVideoWnd::OnBnClickedBtnMuteA)
	ON_BN_CLICKED(IDC_BTN_MUTE_V, &CVideoWnd::OnBnClickedBtnMuteV)
	ON_STN_DBLCLK(IDC_VIDEO, &CVideoWnd::OnStnDblclickVideo)
END_MESSAGE_MAP()


// CVideoWnd 消息处理程序


void CVideoWnd::OnSize(UINT nType, int cx, int cy)
{

	m_xpos = cx;
	m_ypos = cy;
    CDialogEx::OnSize(nType, cx, cy);

    CRect rcClient;
    GetClientRect(&rcClient);
    
    // Close Button 
    CRect rcBtn;
    CWnd *pc = GetDlgItem(IDC_BTN_CLOSE);
    if (nullptr == pc) {
        return;
    }

	/*if (m_type == "local")
	{
		CString str = L"publish";
		SetDlgItemText(IDC_BTN_CLOSE, str);
	}*/
    pc->GetWindowRect(rcBtn);
	GetDlgItem(IDC_BTN_CLOSE)->MoveWindow(rcClient.right - rcBtn.Width(), 0, rcBtn.Width(), rcBtn.Height());
    
    // Auto Layout, center video
    m_rcContainer.SetRect(0, m_nToolBarHeight, rcClient.right, rcClient.bottom - m_nCtrlBarHeight);
    if (m_nWidth != 0 && m_nHeight != 0) {
        centerVideo(m_rcContainer, m_nWidth, m_nHeight);
    }

    int offset = 0;
    //Mute
	pc = GetDlgItem(IDC_BTN_MUTE);
    if (nullptr == pc) {
        return;
    }

    pc->GetWindowRect(rcBtn);
    GetDlgItem(IDC_BTN_MUTE_A)->MoveWindow(0, rcClient.bottom-rcBtn.Height(), rcBtn.Width(), rcBtn.Height());
    offset += rcBtn.Width();

    //Close Video
    //offset++;
    //pc = GetDlgItem(IDC_BTN_VIDEO_ON);
    //if (nullptr == pc) {
    //    return;
    //}

    //pc->GetWindowRect(rcBtn);
    //GetDlgItem(IDC_BTN_VIDEO_ON)->MoveWindow(offset, rcClient.bottom - rcBtn.Height(), rcBtn.Width(), rcBtn.Height());
    //offset += rcBtn.Width();

    //Role
    offset = offset+5;
    pc = GetDlgItem(IDC_BTN_MUTE_V);
    if (nullptr == pc) {
        return;
    }

    pc->GetWindowRect(rcBtn);
    GetDlgItem(IDC_BTN_MUTE_V)->MoveWindow(offset, rcClient.bottom - rcBtn.Height(), rcBtn.Width(), rcBtn.Height());
}


int  CVideoWnd::RegisterCallback(CVideoWndCallback *o)
{
    m_pObserver = o;
    return 0;
}


HWND CVideoWnd::GetVideoHwnd() {
    CWnd *pWnd = GetDlgItem(IDC_VIDEO);
    
    if (pWnd) {
        return pWnd->GetSafeHwnd();
    }

    return nullptr;
}

void CVideoWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: 在此处添加消息处理程序代码
                       // 不为绘图消息调用 CDialogEx::OnPaint()
    CRect rcClient;
    GetClientRect(&rcClient);
    //// Draw video background
	COLORREF black = RGB(20, 20, 20);
	m_rcContainer.SetRect(0, m_nToolBarHeight, rcClient.right, rcClient.bottom - m_nCtrlBarHeight);
	dc.FillSolidRect(m_rcContainer, black);
    
    // draw window edge
    HBRUSH hNull_Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    CBrush *pBrush = CBrush::FromHandle(hNull_Brush);
    CBrush* pOldBrush = dc.SelectObject(pBrush);

    dc.Rectangle(&rcClient);

    dc.SelectObject(pOldBrush);
    pBrush->DeleteObject();
}

void CVideoWnd::centerVideo(CRect rcContainer, int w, int h)
{
    int screenW = rcContainer.Width();
    int screenH = rcContainer.Height();

    int finalW, finalH;

    if (w > h && screenW > screenH) {
        finalW = screenW;
        finalH = screenW * h / w;
    }
    else {
        finalH = screenH;
        finalW = screenH * w / h;
    }

    CWnd *pWnd = GetDlgItem(IDC_VIDEO);
    CRect rcVideo;
    int x, y, x2, y2;
    x = rcContainer.left + (screenW - finalW) / 2;
    x2 = x + finalW;

    y = rcContainer.top + (screenH - finalH) / 2;
    y2 = y + finalH;

    rcVideo.SetRect(x, y, x2, y2);
	m_rcContainer.SetRect(x, y, x2, y2);
    pWnd->MoveWindow(rcVideo);

}


BOOL CVideoWnd::OnInitDialog()
{
    CDialogEx::OnInitDialog();
	m_vol.SetRange(0, 100);
	m_vol.SetPos(0);
    CRect rc;
    GetDlgItem(IDC_TITLE)->GetWindowRect(&rc);
    m_nToolBarHeight = rc.Height()+4;

    GetDlgItem(IDC_BTN_MUTE_A)->GetWindowRect(&rc);
    m_nCtrlBarHeight = rc.Height();

	m_stat.Create(this);
    return TRUE; 
}


void CVideoWnd::SetTitle(std::wstring strTitle) {
    m_Title = strTitle;
    CWnd *pWnd = GetDlgItem(IDC_TITLE);
    if (pWnd && pWnd->GetSafeHwnd()) {
        pWnd->SetWindowText(strTitle.c_str());
    }
}

void CVideoWnd::SetType(eUCloudRtcMeidaType type) {
	m_type = type;
}

void CVideoWnd::TestEnble() {
	m_stat.ShowWindow(FALSE);
	GetDlgItem(IDC_TITLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_MUTE_A)->ShowWindow(FALSE);
	GetDlgItem(IDC_BTN_MUTE_V)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS4)->ShowWindow(FALSE);
}

void CVideoWnd::SetUserId(std::string uid) {
	if (uid.length() <=0)
	{
		this->m_userid = uid;
		m_stat.Activate(FALSE); //设置是否启用提示
	}else{
		this->m_userid = uid;
		char buf[8] = {0};
		sprintf_s(buf, "%d", m_type);
		m_stat.AddTool(GetDlgItem(IDC_VIDEO), Ansi2WChar( ("uid: "+ uid + " mediatype: "+ buf).data()).data());
		m_stat.SetDelayTime(500); //设置延迟，如果为0则不等待，立即显示
		m_stat.SetTipTextColor(RGB(0, 0, 255)); //设置提示文本的颜色
		m_stat.SetTipBkColor(RGB(255, 255, 255)); //设置提示框的背景颜色

		m_stat.SetMaxTipWidth(600);//设置文本框的最大宽度，注意里边的数值单位为像素，所以要通过不断测试来选定最理想的宽度。利用此句可显示多行
		//m_stat.Activate(TRUE); //设置是否启用提示
	}
	
}

std::string CVideoWnd::GetUserId() {
	return this->m_userid;
}

void CVideoWnd::muteAudio(bool mute) {
	if (mute)
	{
		CString str = L"UnMuteA";
		SetDlgItemText(IDC_BTN_MUTE_A, str);
	}
	else {
		CString str = L"MuteA";
		SetDlgItemText(IDC_BTN_MUTE_A, str);
	}
	m_audiomute = mute;
}

void CVideoWnd::muteVideo(bool mute) {
	if (mute)
	{
		CString str = L"UnMuteV";
		SetDlgItemText(IDC_BTN_MUTE_V, str);
	}
	else {
		CString str = L"MuteV";
		SetDlgItemText(IDC_BTN_MUTE_V, str);
	}
	m_videomute = mute;
}

void CVideoWnd::setVol(int level)
{
	m_vol.SetPos(level);
}

void CVideoWnd::OnBnClickedBtnClose()
{
	if (m_pObserver)
	{
		m_pObserver->OnCloseMedia("", m_userid);
	}
}


void CVideoWnd::OnBnClickedBtnVideoOn()
{
	if (m_videostart)
	{
		CString str = L"start";
		SetDlgItemText(IDC_BTN_VIDEO_ON, str);
	}
	else {
		CString str = L"close";
		SetDlgItemText(IDC_BTN_VIDEO_ON, str);
	}
	m_videostart = !m_videostart;

	//m_pObserver->OnToggleVideo(m_type, m_streamid, m_videostart);
}


void CVideoWnd::OnBnClickedBtnMuteA()
{
	// TODO: Add your control notification handler code here
	if (m_isUse && m_isReady)
	{
		if (m_pObserver)
		{
			m_pObserver->OnMuteAudio(m_userid,m_type, !m_audiomute);
		}
	}
	
}


void CVideoWnd::OnBnClickedBtnMuteV()
{
	// TODO: Add your control notification handler code here
	if (m_isUse && m_isReady)
	{
		if (m_pObserver)
		{
			m_pObserver->OnMuteVideo(m_userid,m_type, !m_videomute);
		}
	}
	
}


void CVideoWnd::OnStnDblclickVideo()
{
}
