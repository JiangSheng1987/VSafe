// Protection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "Protection.h"
#include "afxdialogex.h"
#include "TmProcess.h"
#include "Run.h"
#include "Software.h"
#include "Services.h"

// CProtection �Ի���

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


// CProtection ��Ϣ�������


BOOL CProtection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ������ɫ
	m_Brush1.CreateSolidBrush(RGB(255, 255, 255));

	//��������
	m_fBlack1.CreatePointFont(200, L"΢���ź�");
	m_TextSelfDefense.SetFont(&m_fBlack1);

	//��ť

	m_BtProcess.SetTextFont(120, L"΢���ź�");
	m_BtProcess.SetMouseColor(RGB(250, 120, 40));
	m_BtProcess.SetBackColor(RGB(255, 170, 50));
	m_BtProcess.SetTextColor(RGB(255, 255, 255));
	m_BtProcess.SetLockColor(RGB(255, 255, 255));

	m_BtService.SetTextFont(120, L"΢���ź�");
	m_BtService.SetMouseColor(RGB(250, 120, 40));
	m_BtService.SetBackColor(RGB(255, 170, 50));
	m_BtService.SetTextColor(RGB(255, 255, 255));
	m_BtService.SetLockColor(RGB(255, 255, 255));

	m_BtSoftware.SetTextFont(120, L"΢���ź�");
	m_BtSoftware.SetMouseColor(RGB(250, 120, 40));
	m_BtSoftware.SetBackColor(RGB(255, 170, 50));
	m_BtSoftware.SetTextColor(RGB(255, 255, 255));
	m_BtSoftware.SetLockColor(RGB(255, 255, 255));

	m_BtStartup.SetTextFont(120, L"΢���ź�");
	m_BtStartup.SetMouseColor(RGB(250, 120, 40));
	m_BtStartup.SetBackColor(RGB(255, 170, 50));
	m_BtStartup.SetTextColor(RGB(255, 255, 255));
	m_BtStartup.SetLockColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CProtection::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush1;
	}

	//������������2
	if (IDC_TEXT_SD == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CProtection::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_BOX));
	CRect rect;
	GetDlgItem(IDC_BOX)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//box.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}

//�鿴����
void CProtection::OnBnClickedButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTmProcess *pTM = new CTmProcess;
	pTM->DoModal();
}

//������
void CProtection::OnBnClickedButtonRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRun * pRun = new CRun;
	pRun->DoModal();
}

//�������
void CProtection::OnBnClickedButtonSoftware()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSoftware pSW = new CSoftware;
	pSW.DoModal();
}

//ϵͳ����
void CProtection::OnBnClickedButtonServices()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CServices *pSer = new CServices;
	pSer->DoModal();
}
