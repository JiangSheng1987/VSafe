// Protection.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "Protection.h"
#include "afxdialogex.h"
#include "TmProcess.h"
#include "Run.h"
#include "Software.h"
#include "Services.h"

// CProtection 对话框

IMPLEMENT_DYNAMIC(CProtection, CDialogEx)

CProtection::CProtection(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CProtection::~CProtection()
{
}

void CProtection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_10, m_BtProcess);
	DDX_Control(pDX, IDC_BUTTON_11, m_BtService);
	DDX_Control(pDX, IDC_BUTTON_12, m_BtSoftware);
	DDX_Control(pDX, IDC_BUTTON_13, m_BtStartup);
	DDX_Control(pDX, IDC_TEXT_SD, m_TextSelfDefense);
}


BEGIN_MESSAGE_MAP(CProtection, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON__PROCESS, &CProtection::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CProtection::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_SOFTWARE, &CProtection::OnBnClickedButtonSoftware)
	ON_BN_CLICKED(IDC_BUTTON_SERVICES, &CProtection::OnBnClickedButtonServices)
END_MESSAGE_MAP()


// CProtection 消息处理程序


BOOL CProtection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化背景色
	m_Brush1.CreateSolidBrush(RGB(255, 255, 255));

	//加载文字
	m_fBlack1.CreatePointFont(200, L"微软雅黑");
	m_TextSelfDefense.SetFont(&m_fBlack1);

	//按钮

	m_BtProcess.SetTextFont(120, L"微软雅黑");
	m_BtProcess.SetMouseColor(RGB(250, 120, 40));
	m_BtProcess.SetBackColor(RGB(255, 170, 50));
	m_BtProcess.SetTextColor(RGB(255, 255, 255));
	m_BtProcess.SetLockColor(RGB(255, 255, 255));

	m_BtService.SetTextFont(120, L"微软雅黑");
	m_BtService.SetMouseColor(RGB(250, 120, 40));
	m_BtService.SetBackColor(RGB(255, 170, 50));
	m_BtService.SetTextColor(RGB(255, 255, 255));
	m_BtService.SetLockColor(RGB(255, 255, 255));

	m_BtSoftware.SetTextFont(120, L"微软雅黑");
	m_BtSoftware.SetMouseColor(RGB(250, 120, 40));
	m_BtSoftware.SetBackColor(RGB(255, 170, 50));
	m_BtSoftware.SetTextColor(RGB(255, 255, 255));
	m_BtSoftware.SetLockColor(RGB(255, 255, 255));

	m_BtStartup.SetTextFont(120, L"微软雅黑");
	m_BtStartup.SetMouseColor(RGB(250, 120, 40));
	m_BtStartup.SetBackColor(RGB(255, 170, 50));
	m_BtStartup.SetTextColor(RGB(255, 255, 255));
	m_BtStartup.SetLockColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CProtection::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush1;
	}

	//更改文字属性2
	if (IDC_TEXT_SD == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CProtection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_BOX));
	CRect rect;
	GetDlgItem(IDC_BOX)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//box.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}

//查看进程
void CProtection::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CTmProcess *pTM = new CTmProcess;
	pTM->DoModal();
}

//启动项
void CProtection::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	CRun * pRun = new CRun;
	pRun->DoModal();
}

//软件管理
void CProtection::OnBnClickedButtonSoftware()
{
	// TODO: 在此添加控件通知处理程序代码
	CSoftware pSW = new CSoftware;
	pSW.DoModal();
}

//系统服务
void CProtection::OnBnClickedButtonServices()
{
	// TODO: 在此添加控件通知处理程序代码
	CServices *pSer = new CServices;
	pSer->DoModal();
}
