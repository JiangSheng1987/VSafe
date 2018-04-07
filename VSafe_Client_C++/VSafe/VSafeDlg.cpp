
// VSafeDlg.cpp : ʵ���ļ�
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


// CVSafeDlg �Ի���



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
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON2, IDC_BUTTON4, On_ButtonTab)//��ť����TAB�л�����
	ON_CONTROL_RANGE(BN_CLICKED, ID_32801, ID_32806, OnMenuTop)			//���˵���Ϣ����;
	ON_BN_CLICKED(IDC_BUTTON1, &CVSafeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CVSafeDlg ��Ϣ�������

BOOL CVSafeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ������ɫ
	m_Brush.CreateSolidBrush(RGB(255, 255, 255));

	//��ʼ���Ǳ�
	m_BtVSafe.LoadStdImage(IDB_PNG0	, L"PNG");
	//��ʼ����ť
	m_BtAntivirus.LoadStdImage(IDB_PNG1, L"PNG");
	m_BtProtection.LoadStdImage(IDB_PNG2, L"PNG");
	m_BtExtended.LoadStdImage(IDB_PNG3, L"PNG");
	m_BtOther.LoadStdImage(IDB_PNG4, L"PNG");

	//��ʼ��Tab�ؼ�
	m_TabCtrl.MyInserItem(3, L"", L"", L"");
	m_TabCtrl.MyInsertChild(3,
		new CAntivirus, IDD_DIALOG0,
		new CProtection, IDD_DIALOG1,
		new CExtented, IDD_DIALOG2);

	//ע��ȫ�ֿ�ݼ�;
	::RegisterHotKey(GetSafeHwnd(), 0x1234, MOD_CONTROL, 'H');	//�����д��ĸ;
	::RegisterHotKey(GetSafeHwnd(), ID_32801, MOD_ALT, '1');
	::RegisterHotKey(GetSafeHwnd(), ID_32802, MOD_ALT, '2');
	::RegisterHotKey(GetSafeHwnd(), ID_32803, MOD_ALT, '3');
	::RegisterHotKey(GetSafeHwnd(), ID_32804, MOD_ALT, '4');
	::RegisterHotKey(GetSafeHwnd(), ID_32805, MOD_ALT, '5');
	::RegisterHotKey(GetSafeHwnd(), ID_32806, MOD_ALT, '6');


	/*�ֶ��������ԱȨ��;

	BOOL bAdmin = IsAdmin();
	BOOL bHig = IsHighest();

	if (bAdmin&&bHig)
	{
	::ShowWindow(GetDlgItem(IDC_BUTTON_UAC)->m_hWnd, SW_HIDE);
	//����ԱȨ��������ҷ�ļ�;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);
	}
	else
	{
	SendDlgItemMessage(IDC_BUTTON_UAC, BCM_SETSHIELD, 0, true);
	}*/

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVSafeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVSafeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//������ԱȨ��
bool CVSafeDlg::IsAdmin()
{
	//��ȡ����ԱSID
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

	//��������Ƿ��������ԱSID
	if (!CheckTokenMembership(NULL, pSID, &bAdmin))
	{
		bAdmin = false;
	}
	if (!bAdmin)
	{
		//�ж�ϵͳ
		if (IsWindowsVistaOrGreater())
		{
			//��ȡ��������
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

			//��������Ƿ��������ԱSID
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

//����Ƿ����Ȩ��
bool CVSafeDlg::IsHighest()
{
	HANDLE hToken = 0;
	//��ȡ��ǰ����
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		return false;
	}
	//��ȡ��������
	TOKEN_ELEVATION_TYPE tet = {};
	DWORD dwLen = 0;
	if (!GetTokenInformation(hToken, TokenElevationType, &tet,
		sizeof(TOKEN_ELEVATION_TYPE), &dwLen))
	{
		return false;
	}

	//�Ƿ������˻�
	if (tet == TokenElevationTypeLimited)
	{
		return false;
	}
	CloseHandle(hToken);
	return true;

}



//�ػ水ť
HBRUSH CVSafeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (nCtlColor == CTLCOLOR_DLG)
	{
		return  m_Brush;
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//�л��Ӵ���
void CVSafeDlg::On_ButtonTab(UINT nID)
{
	DWORD dwSel = nID - IDC_BUTTON2;
	m_TabCtrl.ButtonSelchange(dwSel);
}

//��Ӧ�˵�
void CVSafeDlg::OnMenuTop(UINT id)
{
	//��־λ
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
		//�ػ���ʾ;
		Flag = MessageBox(L"ȷ��Ҫ�ػ���\r\n�����ȷ�����ػ�\r\n�����ȡ��������", L"�Ƿ�ػ�?", MB_OKCANCEL);
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
		//������ʾ;
		Flag = MessageBox(L"ȷ��Ҫ������\r\n�����ȷ��������\r\n�����ȡ��������", L"�Ƿ�����?", MB_OKCANCEL);
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
	// TODO: �ڴ����ר�ô����/����û���

	//��Ӧ��ݼ�;
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

//VSafe�˵�
void CVSafeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ�����˵�;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU1);

	CMenu* pSub = pMenu->GetSubMenu(0);

	//��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);
}
