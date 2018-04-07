// Extented.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "Extented.h"
#include "afxdialogex.h"
#include "PEInfo.h"
#include "TmClean.h"
#include "TmEnumWindow.h"
#include "TmPerformance.h"
#include "TmProcess.h"
#include "FileMgr.h"
// CExtented 对话框

IMPLEMENT_DYNAMIC(CExtented, CDialogEx)

CExtented::CExtented(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CExtented::~CExtented()
{
}

void CExtented::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_20, m_BtPE);
	DDX_Control(pDX, IDC_BUTTON_21, m_BtClean);
	DDX_Control(pDX, IDC_BUTTON_22, m_BtRocket);
	DDX_Control(pDX, IDC_BUTTON_23, m_BtOT);
	DDX_Control(pDX, IDC_TEXT_TOOL, m_TextTool);
}


BEGIN_MESSAGE_MAP(CExtented, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_20_PE, &CExtented::OnBnClickedButton20Pe)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CExtented::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_23, &CExtented::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON_22, &CExtented::OnBnClickedButton22)
END_MESSAGE_MAP()


// CExtented 消息处理程序


BOOL CExtented::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Brush2.CreateSolidBrush(RGB(255, 255, 255));
	//加载文字
	m_fBlack2.CreatePointFont(200, L"微软雅黑");
	m_TextTool.SetFont(&m_fBlack2);

	//按钮

	m_BtPE.SetTextFont(120, L"微软雅黑");
	m_BtPE.SetMouseColor(RGB(250, 120, 40));
	m_BtPE.SetBackColor(RGB(255, 170, 50));
	m_BtPE.SetTextColor(RGB(255, 255, 255));
	m_BtPE.SetLockColor(RGB(255, 255, 255));

	m_BtClean.SetTextFont(120, L"微软雅黑");
	m_BtClean.SetMouseColor(RGB(250, 120, 40));
	m_BtClean.SetBackColor(RGB(255, 170, 50));
	m_BtClean.SetTextColor(RGB(255, 255, 255));
	m_BtClean.SetLockColor(RGB(255, 255, 255));

	m_BtRocket.SetTextFont(120, L"微软雅黑");
	m_BtRocket.SetMouseColor(RGB(250, 120, 40));
	m_BtRocket.SetBackColor(RGB(255, 170, 50));
	m_BtRocket.SetTextColor(RGB(255, 255, 255));
	m_BtRocket.SetLockColor(RGB(255, 255, 255));

	m_BtOT.SetTextFont(120, L"微软雅黑");
	m_BtOT.SetMouseColor(RGB(250, 120, 40));
	m_BtOT.SetBackColor(RGB(255, 170, 50));
	m_BtOT.SetTextColor(RGB(255, 255, 255));
	m_BtOT.SetLockColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//重绘按钮
HBRUSH CExtented::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush2;
	}

	//更改文字属性3
	if (IDC_TEXT_TOOL == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CExtented::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_PE));
	CRect rect;
	GetDlgItem(IDC_PE)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//pe.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}




//获取PE信息
void CExtented::OnBnClickedButton20Pe()
{
	// TODO: 在此添加控件通知处理程序代码
	CPEInfo *pPE = new CPEInfo;
	pPE->Create(IDD_PEINFO_DIALOG);
	pPE->ShowWindow(SW_NORMAL);
}

//清理垃圾
void CExtented::OnBnClickedButtonClean()
{
	// TODO: 在此添加控件通知处理程序代码
	CClean *pClean = new CClean;
	pClean->DoModal();
}

//文件浏览
void CExtented::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileMgr *pFM = new CFileMgr;
	pFM->DoModal();
}

//性能优化
void CExtented::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	CPerformance *pPM = new CPerformance;
	pPM->DoModal();
}


