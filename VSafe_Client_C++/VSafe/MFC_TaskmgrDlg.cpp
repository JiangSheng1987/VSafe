
// MFC_TaskmgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_TaskmgrDlg.h"
//�����Դ�����;
#include <powrprof.h>
#pragma  comment(lib,"powrprof.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_TaskmgrDlg �Ի���


CMFC_TaskmgrDlg::CMFC_TaskmgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_TASKMGR_DIALOG, pParent)
{
	//����ͼ��;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMFC_TaskmgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_TaskmgrDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, ID_32801, ID_32806, &CMFC_TaskmgrDlg::OnMenuTop)	//���˵���Ϣ����;
END_MESSAGE_MAP()


// CMFC_TaskmgrDlg ��Ϣ�������

BOOL CMFC_TaskmgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_TaskmgrDlg::OnPaint()
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
HCURSOR CMFC_TaskmgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//****************************************************************
// Brief 	: ���˵���Ϣ����;
// Method	: OnMenuTop
// FullName	: CMFC_TaskmgrDlg::OnMenuTop
// Access	: protected 
// Returns	: void
// Parameter: UINT id
//****************************************************************

void CMFC_TaskmgrDlg::OnMenuTop(UINT id)
{
	//��ȡ�ػ�����Ȩ��;
	HANDLE hToken = NULL;
	HANDLE hProcess = GetCurrentProcess();
	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tp = { 0 };
	LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

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

//****************************************************************
// Brief 	: ��д��Ϣת���麯��;
// Method	: PreTranslateMessage
// FullName	: CMFC_TaskmgrDlg::PreTranslateMessage
// Access	: virtual protected 
// Returns	: BOOL
// Parameter: MSG * pMsg
//****************************************************************

BOOL CMFC_TaskmgrDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	//��Ӧ��ݼ�;
	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0x1234))
	{
		if (IsWindowVisible()==TRUE)
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
		}
	}
	else if ((pMsg->message == WM_HOTKEY) &&
			((pMsg->wParam == ID_32801)||
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




