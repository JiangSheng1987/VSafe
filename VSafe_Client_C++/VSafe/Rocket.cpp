// Rocket.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "Rocket.h"
#include "afxdialogex.h"


// CRocket 对话框

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

	// TODO:  在此添加额外的初始化
	m_Rocket.LoadStdImage(IDB_PNG5, L"PNG");

	//灰色透明
	COLORREF maskColor = RGB(240, 240, 240);
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | 0x80000); 
	//设置透明
	SetLayeredWindowAttributes(maskColor, 255, 1);

	//创建线程移动;
	hRocketThread = AfxBeginThread(MyThreadRocket, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CRocket::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	//绘制透明窗口
	if (nCtlColor == CTLCOLOR_DLG)
	{
		CBrush *brush;
		brush = new CBrush(RGB(240, 240, 240));
		return (HBRUSH)(brush->m_hObject);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//结束窗口
void CRocket::OnBnClickedRocket()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

//窗口移动线程
UINT CRocket::MyThreadRocket(LPVOID lpParam)
{
	CRocket* pRocket = (CRocket*)lpParam;

	//获取屏幕尺寸
	int scrWidth, scrHeight;
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);

	//计算坐标
	int nPosX = scrWidth - 200;
	int nPosY = scrHeight - 400;
	pRocket->MoveWindow(nPosX, nPosY, 100, 300);


	//循环移动
	while (true)
	{
		//间隔10
		Sleep(10);
		nPosY -= 10;
		pRocket->MoveWindow(nPosX, nPosY, 100, 300);
		
		//指定位置结束
		if (nPosY<=30)
		{
			break;
		}
	}

	pRocket->EndDialog(0);
	return 0;
}
