// Rocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "Rocket.h"
#include "afxdialogex.h"


// CRocket �Ի���

IMPLEMENT_DYNAMIC(CRocket, CDialogEx)

CRocket::CRocket(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ROCKET, pParent)
{

}

CRocket::~CRocket()
{
}

void CRocket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROCKET, m_Rocket);
}


BEGIN_MESSAGE_MAP(CRocket, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ROCKET, &CRocket::OnBnClickedRocket)
END_MESSAGE_MAP()



BOOL CRocket::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Rocket.LoadStdImage(IDB_PNG5, L"PNG");

	//��ɫ͸��
	COLORREF maskColor = RGB(240, 240, 240);
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | 0x80000); 
	//����͸��
	SetLayeredWindowAttributes(maskColor, 255, 1);

	//�����߳��ƶ�;
	hRocketThread = AfxBeginThread(MyThreadRocket, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CRocket::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	//����͸������
	if (nCtlColor == CTLCOLOR_DLG)
	{
		CBrush *brush;
		brush = new CBrush(RGB(240, 240, 240));
		return (HBRUSH)(brush->m_hObject);
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//��������
void CRocket::OnBnClickedRocket()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}

//�����ƶ��߳�
UINT CRocket::MyThreadRocket(LPVOID lpParam)
{
	CRocket* pRocket = (CRocket*)lpParam;

	//��ȡ��Ļ�ߴ�
	int scrWidth, scrHeight;
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);

	//��������
	int nPosX = scrWidth - 200;
	int nPosY = scrHeight - 400;
	pRocket->MoveWindow(nPosX, nPosY, 100, 300);


	//ѭ���ƶ�
	while (true)
	{
		//���10
		Sleep(10);
		nPosY -= 10;
		pRocket->MoveWindow(nPosX, nPosY, 100, 300);
		
		//ָ��λ�ý���
		if (nPosY<=30)
		{
			break;
		}
	}

	pRocket->EndDialog(0);
	return 0;
}
