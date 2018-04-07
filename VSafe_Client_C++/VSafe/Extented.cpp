// Extented.cpp : ʵ���ļ�
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
// CExtented �Ի���

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


// CExtented ��Ϣ�������


BOOL CExtented::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Brush2.CreateSolidBrush(RGB(255, 255, 255));
	//��������
	m_fBlack2.CreatePointFont(200, L"΢���ź�");
	m_TextTool.SetFont(&m_fBlack2);

	//��ť

	m_BtPE.SetTextFont(120, L"΢���ź�");
	m_BtPE.SetMouseColor(RGB(250, 120, 40));
	m_BtPE.SetBackColor(RGB(255, 170, 50));
	m_BtPE.SetTextColor(RGB(255, 255, 255));
	m_BtPE.SetLockColor(RGB(255, 255, 255));

	m_BtClean.SetTextFont(120, L"΢���ź�");
	m_BtClean.SetMouseColor(RGB(250, 120, 40));
	m_BtClean.SetBackColor(RGB(255, 170, 50));
	m_BtClean.SetTextColor(RGB(255, 255, 255));
	m_BtClean.SetLockColor(RGB(255, 255, 255));

	m_BtRocket.SetTextFont(120, L"΢���ź�");
	m_BtRocket.SetMouseColor(RGB(250, 120, 40));
	m_BtRocket.SetBackColor(RGB(255, 170, 50));
	m_BtRocket.SetTextColor(RGB(255, 255, 255));
	m_BtRocket.SetLockColor(RGB(255, 255, 255));

	m_BtOT.SetTextFont(120, L"΢���ź�");
	m_BtOT.SetMouseColor(RGB(250, 120, 40));
	m_BtOT.SetBackColor(RGB(255, 170, 50));
	m_BtOT.SetTextColor(RGB(255, 255, 255));
	m_BtOT.SetLockColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//�ػ水ť
HBRUSH CExtented::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush2;
	}

	//������������3
	if (IDC_TEXT_TOOL == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(250, 120, 40));
		pDC->SetBkMode(TRANSPARENT);
		hbr = CreateSolidBrush(RGB(255, 255, 255));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CExtented::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CClientDC *pDC = new CClientDC(GetDlgItem(IDC_PE));
	CRect rect;
	GetDlgItem(IDC_PE)->GetWindowRect(&rect);
	Graphics graphics(pDC->m_hDC);
	Image image(L"res//pe.png");
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	delete pDC;
}




//��ȡPE��Ϣ
void CExtented::OnBnClickedButton20Pe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPEInfo *pPE = new CPEInfo;
	pPE->Create(IDD_PEINFO_DIALOG);
	pPE->ShowWindow(SW_NORMAL);
}

//��������
void CExtented::OnBnClickedButtonClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CClean *pClean = new CClean;
	pClean->DoModal();
}

//�ļ����
void CExtented::OnBnClickedButton23()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileMgr *pFM = new CFileMgr;
	pFM->DoModal();
}

//�����Ż�
void CExtented::OnBnClickedButton22()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPerformance *pPM = new CPerformance;
	pPM->DoModal();
}


