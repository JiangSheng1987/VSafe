#include "stdafx.h"

#include "TmProcess.h"
#include "TmFileInfo.h"

#include <TlHelp32.h>
#include <tchar.h>

// CTmProcess �Ի���

IMPLEMENT_DYNAMIC(CTmProcess, CDialogEx)

CTmProcess::CTmProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROCESS, pParent)
{

}

CTmProcess::~CTmProcess()
{
}

void CTmProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Process_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CTmProcess, CDialogEx)
	ON_COMMAND(ID_32784, &CTmProcess::On32784)
	ON_COMMAND(ID_32787, &CTmProcess::OnClose)
	ON_COMMAND(ID_32786, &CTmProcess::OnAttribute)
	ON_CONTROL_RANGE(BN_CLICKED, ID_32781, ID_32783, &CTmProcess::OnMenuClick)
	ON_NOTIFY(NM_RCLICK, IDC_Process_LIST1, &CTmProcess::OnRclickProcessList1)	
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_Process_LIST1, &CTmProcess::OnColumnclickProcessList1)
	ON_COMMAND(ID_33333, &CTmProcess::OnHook)
	ON_COMMAND(ID_32825, &CTmProcess::OnOffHook)
END_MESSAGE_MAP()


// CTmProcess ��Ϣ�������


BOOL CTmProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	//��ʼ���б�;
	m_List.AddColumn(5, L"����", 100, L"PID", 50,L"������PID",80 ,L"�߳�����", 80, L"·��", 180);
	//��ʾ����;
	ShowProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


//****************************************************************
// Brief 	: ��ʾ����;
// Method	: ShowProcess
// FullName	: CTmProcess::ShowProcess
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::ShowProcess()
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"HELP ��������ʧ�ܣ�");
		return;
	}

	//��ʼ��������Ϣ�ṹ��;
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapShot, &pi))
	{
		MessageBox(L"��ȡ������Ϣʧ��");
		return;
	}
	do
	{
		TCHAR *szBuf[5] = { new TCHAR[MAX_PATH], new TCHAR[6],  new TCHAR[6],  new TCHAR[6], new TCHAR[MAX_PATH], };
		szBuf[0] = pi.szExeFile;
		if (pi.th32ProcessID > 0&& pi.th32ParentProcessID>0&& pi.cntThreads>=0)
		{
			_stprintf_s(szBuf[1], 6, L"%d", pi.th32ProcessID);
			_stprintf_s(szBuf[2], 6, L"%d", pi.th32ParentProcessID);
			_stprintf_s(szBuf[3], 6, L"%d", pi.cntThreads);
		}
		else
		{
			szBuf[1] = L"  ";
			szBuf[2] = L"  ";
			szBuf[3] = L"  ";
		}

		//��Ҫ��ȡ·���Ľ���
		HANDLE hPro = OpenProcess(PROCESS_QUERY_INFORMATION
			| PROCESS_QUERY_LIMITED_INFORMATION,
			FALSE, pi.th32ProcessID);
		//��ȡ��������·��;
		if (hPro)
		{
			DWORD dwSize = MAX_PATH;
			QueryFullProcessImageName(hPro, NULL, szBuf[4], &dwSize);
		}
		else
		{
			szBuf[4] = L"��Ȩ����";
		}
		m_List.AddItem(5, szBuf[0], szBuf[1], szBuf[2], szBuf[3], szBuf[4]);
		CloseHandle(hPro);
	} while (Process32Next(hSnapShot, &pi));

	return;
}




//****************************************************************
// Brief 	: �����Ҽ��˵�;
// Method	: OnRclickProcessList1
// FullName	: CTmProcess::OnRclickProcessList1
// Access	: public 
// Returns	: void
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//****************************************************************

void CTmProcess::OnRclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��ȡ�����˵�;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU2);
	
	CMenu* pSub = pMenu->GetSubMenu(0);

	//��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}


//****************************************************************
// Brief 	: ��Ӧ�Ҽ��˵�;
// Method	: OnMenuClick
// FullName	: CTmProcess::OnMenuClick
// Access	: public 
// Returns	: void
// Parameter: UINT id
//****************************************************************

void CTmProcess::OnMenuClick(UINT id)
{
	// TODO: �ڴ���������������
	//��ȡѡ����;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));
	
	CTmProcessInfo DlgA(this,id,PID);
	DlgA.DoModal();
}


//****************************************************************
// Brief 	: ˢ��
// Method	: On32784
// FullName	: CTmProcess::On32784
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::On32784()
{
	// TODO: �ڴ���������������
	//ˢ�½���;
	m_List.DeleteAllItems();
	ShowProcess();
}


//****************************************************************
// Brief 	: �������̣�
// Method	: OnClose
// FullName	: CTmProcess::OnClose
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::OnClose()
{
	// TODO: �ڴ���������������
	//��ȡPid;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));
	//��ȡ���;
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
	if (TerminateProcess(hProcess,0))
	{
		MessageBox(L"�����ɹ�!");
	}
	else
	{
		MessageBox(L"����ʧ��!");
	}
	CloseHandle(hProcess);
	m_List.DeleteAllItems();
	ShowProcess();
}


//****************************************************************
// Brief 	: �ļ�����;
// Method	: OnAttribute
// FullName	: CTmProcess::OnAttribute
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::OnAttribute()
{
	// TODO: �ڴ���������������
	//��ȡѡ����;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	CString Path=m_List.GetItemText(nSel, 4);
	if ((Path[0]>='a'&&Path[0]<='z')||
		(Path[0] >= 'A'&&Path[0] <= 'Z'))
	{
		CTmFileInfo DlgF(Path);
		DlgF.DoModal();
	}
	else
	{
		MessageBox(L"��ѡ����Ȩ�޷��ʵ�·��");
	}	
}


//****************************************************************
// Brief 	: �����ͷ����;
// Method	: OnColumnclickProcessList1
// FullName	: CTmProcess::OnColumnclickProcessList1
// Access	: public 
// Returns	: void
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//****************************************************************

void CTmProcess::OnColumnclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�����;
	int Sort_Colum = pNMLV->iSubItem;

	//0��4���ַ�������;������������;
	if (Sort_Colum==0||Sort_Colum==4)
		m_List.SortItemsPlus(Sort_Colum, false);
	else
		m_List.SortItemsPlus(Sort_Colum);

	*pResult = 0;
}


void CTmProcess::OnHook()
{
	// TODO: �ڴ���������������
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));

	//ѡ��DLL�ļ�
	CFileDialog dlg(TRUE, _T("dll"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("��̬���ӿ�|*.dll|�����ļ�|*||"));
	if (dlg.DoModal() == IDOK) {

		//��ȡDLL·��
		m_DllPath = dlg.GetPathName();

	}
	else
	{
		return;
	}

	//��ȡ��ǰ���̾����
	DWORD dwPID = GetCurrentProcessId();

	//�����ļ�ӳ�䣻����PID
	HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL, PAGE_READWRITE, 0, 0x10, L"PID");

	PVOID pVoid = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	//д���ļ�ӳ��
	memcpy_s(pVoid, 0X10, &dwPID, 4);


	//�򿪽���
	m_hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

	//Զ���������ڴ�
	PVOID pBuf = VirtualAllocEx(m_hRemoteProcess, NULL, 0x1000,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!pBuf)
	{
		MessageBox(L"Hookʧ�ܣ�");
		return;
	}
	//д��·��
	WriteProcessMemory(m_hRemoteProcess, pBuf, m_DllPath,
		(m_DllPath.GetLength() + 1) * sizeof(WCHAR), NULL);

	
	//�����߳�
	HANDLE hRemoteThread = CreateRemoteThread(m_hRemoteProcess, NULL, NULL,
		(LPTHREAD_START_ROUTINE)LoadLibrary, pBuf, 0, NULL);		
		
	//�ȴ��߳��˳�
	WaitForSingleObject(hRemoteThread, -1);

	//��ȡDLL��Ŀ����̵ľ��
	DWORD dwRemoteModule;
	GetExitCodeThread(hRemoteThread, &dwRemoteModule);
	m_RemoteModule = (HMODULE)dwRemoteModule;

	//�ͷ�
	//CloseHandle(m_hRemoteProcess);
	VirtualFreeEx(m_hRemoteProcess, pBuf, 0, MEM_DECOMMIT);

	return;
}


void CTmProcess::OnOffHook()
{
	// TODO: �ڴ���������������

	//�ж��Ƿ�HOOK
	if (!m_hRemoteProcess||!m_RemoteModule)
	{
		MessageBox(L"����OnHook��");
		return;
	}

	//����Զ���̵߳���FreeLibrary
	HANDLE RemoteThread = CreateRemoteThread(m_hRemoteProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)FreeLibrary, (LPVOID)m_RemoteModule, 0, NULL);

	if (RemoteThread == NULL)
	{
		MessageBox(L"ж��ʧ�ܣ�");
		return;
	}

	WaitForSingleObject(RemoteThread, INFINITE);
	CloseHandle(m_hRemoteProcess);
	m_hRemoteProcess = NULL;
	m_RemoteModule = NULL;
	return;
}
