
// VSafeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "VSafeDlg.h"
#include "afxdialogex.h"

#include "Antivirus.h"
#include "Protection.h"
#include "Extented.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVSafeDlg 对话框



CVSafeDlg::CVSafeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VSAFE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_V);
}

void CVSafeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_BtVSafe);
	DDX_Control(pDX, IDC_BUTTON2, m_BtAntivirus);
	DDX_Control(pDX, IDC_BUTTON3, m_BtProtection);
	DDX_Control(pDX, IDC_BUTTON4, m_BtExtended);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CVSafeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON2, IDC_BUTTON4, On_ButtonTab)//按钮关联TAB切换窗口
	ON_CONTROL_RANGE(BN_CLICKED, ID_32801, ID_32806, OnMenuTop)			//主菜单消息处理;
	ON_BN_CLICKED(IDC_BUTTON1, &CVSafeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CVSafeDlg 消息处理程序

BOOL CVSafeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化背景色
	m_Brush.CreateSolidBrush(RGB(255, 255, 255));

	//初始化角标
	m_BtVSafe.LoadStdImage(IDB_PNG0	, L"PNG");
	//初始化按钮
	m_BtAntivirus.LoadStdImage(IDB_PNG1, L"PNG");
	m_BtProtection.LoadStdImage(IDB_PNG2, L"PNG");
	m_BtExtended.LoadStdImage(IDB_PNG3, L"PNG");
	m_BtOther.LoadStdImage(IDB_PNG4, L"PNG");

	//初始化Tab控件
	m_TabCtrl.MyInserItem(3, L"", L"", L"");
	m_TabCtrl.MyInsertChild(3,
		new CAntivirus, IDD_DIALOG0,
		new CProtection, IDD_DIALOG1,
		new CExtented, IDD_DIALOG2);

	//注册全局快捷键;
	::RegisterHotKey(GetSafeHwnd(), 0x1234, MOD_CONTROL, 'H');	//必须大写字母;
	::RegisterHotKey(GetSafeHwnd(), ID_32801, MOD_ALT, '1');
	::RegisterHotKey(GetSafeHwnd(), ID_32802, MOD_ALT, '2');
	::RegisterHotKey(GetSafeHwnd(), ID_32803, MOD_ALT, '3');
	::RegisterHotKey(GetSafeHwnd(), ID_32804, MOD_ALT, '4');
	::RegisterHotKey(GetSafeHwnd(), ID_32805, MOD_ALT, '5');
	::RegisterHotKey(GetSafeHwnd(), ID_32806, MOD_ALT, '6');


	/*手动请求管理员权限;

	BOOL bAdmin = IsAdmin();
	BOOL bHig = IsHighest();

	if (bAdmin&&bHig)
	{
	::ShowWindow(GetDlgItem(IDC_BUTTON_UAC)->m_hWnd, SW_HIDE);
	//管理员权限允许拖曳文件;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);
	}
	else
	{
	SendDlgItemMessage(IDC_BUTTON_UAC, BCM_SETSHIELD, 0, true);
	}*/

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVSafeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVSafeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//检测管理员权限
bool CVSafeDlg::IsAdmin()
{
	//获取管理员SID
	PBYTE pSID[SECURITY_MAX_SID_SIZE] = {};
	DWORD dwSize = SECURITY_MAX_SID_SIZE;
	if (!CreateWellKnownSid(
		WinBuiltinAdministratorsSid,
		NULL,
		pSID,
		&dwSize))
	{
		return false;
	}
	BOOL bAdmin = 0;

	//检测令牌是否包含管理员SID
	if (!CheckTokenMembership(NULL, pSID, &bAdmin))
	{
		bAdmin = false;
	}
	if (!bAdmin)
	{
		//判断系统
		if (IsWindowsVistaOrGreater())
		{
			//获取完整令牌
			HANDLE hToken = 0;
			if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
			{
				return false;
			}
			TOKEN_LINKED_TOKEN tlk = {};
			DWORD dwLen = 0;
			if (!GetTokenInformation(hToken, TokenLinkedToken, &tlk,
				sizeof(TOKEN_LINKED_TOKEN), &dwLen))
			{
				return false;
			}

			//检测令牌是否包含管理员SID
			if (!CheckTokenMembership(tlk.LinkedToken, pSID, &bAdmin))
			{
				bAdmin = FALSE;
			}
			CloseHandle(tlk.LinkedToken);
			CloseHandle(hToken);
		}
	}

	return bAdmin;
}

//检测是否最高权限
bool CVSafeDlg::IsHighest()
{
	HANDLE hToken = 0;
	//获取当前令牌
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		return false;
	}
	//获取完整令牌
	TOKEN_ELEVATION_TYPE tet = {};
	DWORD dwLen = 0;
	if (!GetTokenInformation(hToken, TokenElevationType, &tet,
		sizeof(TOKEN_ELEVATION_TYPE), &dwLen))
	{
		return false;
	}

	//是否受限账户
	if (tet == TokenElevationTypeLimited)
	{
		return false;
	}
	CloseHandle(hToken);
	return true;

}



//重绘按钮
HBRUSH CVSafeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//切换子窗口
void CVSafeDlg::On_ButtonTab(UINT nID)
{
	DWORD dwSel = nID - IDC_BUTTON2;
	m_TabCtrl.ButtonSelchange(dwSel);
}

//响应菜单
void CVSafeDlg::OnMenuTop(UINT id)
{
	//标志位
	int Flag = 0;

	switch (id)
	{
	case ID_32801:
		LockWorkStation();
		break;
	case ID_32802:
		SetSuspendState(TRUE, FALSE, FALSE);
		break;
	case ID_32803:
		SetSuspendState(FALSE, FALSE, FALSE);
		break;
	case ID_32804:
		ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER);
		break;
	case ID_32805:
		//关机提示;
		Flag = MessageBox(L"确定要关机吗？\r\n点击【确定】关机\r\n点击【取消】继续", L"是否关机?", MB_OKCANCEL);
		if (Flag == IDCANCEL)
		{
			break;
		}
		else
		{
			ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER);
		}
		break;
	case ID_32806:
		//重启提示;
		Flag = MessageBox(L"确定要重启吗？\r\n点击【确定】重启\r\n点击【取消】继续", L"是否重启?", MB_OKCANCEL);
		if (Flag == IDCANCEL)
		{
			break;
		}
		else
		{
			ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER);
		}
		break;
	}
}


BOOL CVSafeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	//响应快捷键;
	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0x1234))
	{
		if (IsWindowVisible() == TRUE)
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
		}
	}
	else if ((pMsg->message == WM_HOTKEY) &&
		((pMsg->wParam == ID_32801) ||
		(pMsg->wParam == ID_32802) ||
			(pMsg->wParam == ID_32803) ||
			(pMsg->wParam == ID_32804) ||
			(pMsg->wParam == ID_32805) ||
			(pMsg->wParam == ID_32806)))
	{
		OnMenuTop(pMsg->wParam);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//VSafe菜单
void CVSafeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取弹出菜单;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU1);

	CMenu* pSub = pMenu->GetSubMenu(0);

	//获取鼠标位置;
	CPoint point;
	GetCursorPos(&point);

	//弹出;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
}
