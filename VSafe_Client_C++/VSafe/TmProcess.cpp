#include "stdafx.h"

#include "TmProcess.h"
#include "TmFileInfo.h"

#include <TlHelp32.h>
#include <tchar.h>

// CTmProcess 对话框

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


// CTmProcess 消息处理程序


BOOL CTmProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	//初始化列表;
	m_List.AddColumn(5, L"名称", 100, L"PID", 50,L"父进程PID",80 ,L"线程数量", 80, L"路径", 180);
	//显示进程;
	ShowProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//****************************************************************
// Brief 	: 显示进程;
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
		MessageBox(L"HELP 函数调用失败！");
		return;
	}

	//初始化快照信息结构体;
	PROCESSENTRY32 pi = { sizeof(PROCESSENTRY32) };
	if (!Process32First(hSnapShot, &pi))
	{
		MessageBox(L"获取进程信息失败");
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

		//打开要获取路径的进程
		HANDLE hPro = OpenProcess(PROCESS_QUERY_INFORMATION
			| PROCESS_QUERY_LIMITED_INFORMATION,
			FALSE, pi.th32ProcessID);
		//获取进程完整路径;
		if (hPro)
		{
			DWORD dwSize = MAX_PATH;
			QueryFullProcessImageName(hPro, NULL, szBuf[4], &dwSize);
		}
		else
		{
			szBuf[4] = L"无权访问";
		}
		m_List.AddItem(5, szBuf[0], szBuf[1], szBuf[2], szBuf[3], szBuf[4]);
		CloseHandle(hPro);
	} while (Process32Next(hSnapShot, &pi));

	return;
}




//****************************************************************
// Brief 	: 弹出右键菜单;
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
	// TODO: 在此添加控件通知处理程序代码
	
	//获取弹出菜单;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU2);
	
	CMenu* pSub = pMenu->GetSubMenu(0);

	//获取鼠标位置;
	CPoint point;
	GetCursorPos(&point);

	//弹出;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}


//****************************************************************
// Brief 	: 响应右键菜单;
// Method	: OnMenuClick
// FullName	: CTmProcess::OnMenuClick
// Access	: public 
// Returns	: void
// Parameter: UINT id
//****************************************************************

void CTmProcess::OnMenuClick(UINT id)
{
	// TODO: 在此添加命令处理程序代码
	//获取选中项;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));
	
	CTmProcessInfo DlgA(this,id,PID);
	DlgA.DoModal();
}


//****************************************************************
// Brief 	: 刷新
// Method	: On32784
// FullName	: CTmProcess::On32784
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::On32784()
{
	// TODO: 在此添加命令处理程序代码
	//刷新进程;
	m_List.DeleteAllItems();
	ShowProcess();
}


//****************************************************************
// Brief 	: 结束进程；
// Method	: OnClose
// FullName	: CTmProcess::OnClose
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	//获取Pid;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));
	//获取句柄;
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
	if (TerminateProcess(hProcess,0))
	{
		MessageBox(L"结束成功!");
	}
	else
	{
		MessageBox(L"结束失败!");
	}
	CloseHandle(hProcess);
	m_List.DeleteAllItems();
	ShowProcess();
}


//****************************************************************
// Brief 	: 文件属性;
// Method	: OnAttribute
// FullName	: CTmProcess::OnAttribute
// Access	: public 
// Returns	: void
//****************************************************************

void CTmProcess::OnAttribute()
{
	// TODO: 在此添加命令处理程序代码
	//获取选中项;
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
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
		MessageBox(L"请选择有权限访问的路径");
	}	
}


//****************************************************************
// Brief 	: 点击列头排序;
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
	// TODO: 在此添加控件通知处理程序代码
	//获取点击列;
	int Sort_Colum = pNMLV->iSubItem;

	//0列4列字符串排序;其他整型排序;
	if (Sort_Colum==0||Sort_Colum==4)
		m_List.SortItemsPlus(Sort_Colum, false);
	else
		m_List.SortItemsPlus(Sort_Colum);

	*pResult = 0;
}


void CTmProcess::OnHook()
{
	// TODO: 在此添加命令处理程序代码
	int nSel = m_List.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	int PID = _wtoi(m_List.GetItemText(nSel, 1));

	//选择DLL文件
	CFileDialog dlg(TRUE, _T("dll"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("动态链接库|*.dll|所有文件|*||"));
	if (dlg.DoModal() == IDOK) {

		//获取DLL路径
		m_DllPath = dlg.GetPathName();

	}
	else
	{
		return;
	}

	//获取当前进程句柄；
	DWORD dwPID = GetCurrentProcessId();

	//创建文件映射；接收PID
	HANDLE hMap = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL, PAGE_READWRITE, 0, 0x10, L"PID");

	PVOID pVoid = MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	//写入文件映射
	memcpy_s(pVoid, 0X10, &dwPID, 4);


	//打开进程
	m_hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

	//远进程申请内存
	PVOID pBuf = VirtualAllocEx(m_hRemoteProcess, NULL, 0x1000,
		MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!pBuf)
	{
		MessageBox(L"Hook失败！");
		return;
	}
	//写入路径
	WriteProcessMemory(m_hRemoteProcess, pBuf, m_DllPath,
		(m_DllPath.GetLength() + 1) * sizeof(WCHAR), NULL);

	
	//创建线程
	HANDLE hRemoteThread = CreateRemoteThread(m_hRemoteProcess, NULL, NULL,
		(LPTHREAD_START_ROUTINE)LoadLibrary, pBuf, 0, NULL);		
		
	//等待线程退出
	WaitForSingleObject(hRemoteThread, -1);

	//获取DLL在目标进程的句柄
	DWORD dwRemoteModule;
	GetExitCodeThread(hRemoteThread, &dwRemoteModule);
	m_RemoteModule = (HMODULE)dwRemoteModule;

	//释放
	//CloseHandle(m_hRemoteProcess);
	VirtualFreeEx(m_hRemoteProcess, pBuf, 0, MEM_DECOMMIT);

	return;
}


void CTmProcess::OnOffHook()
{
	// TODO: 在此添加命令处理程序代码

	//判断是否HOOK
	if (!m_hRemoteProcess||!m_RemoteModule)
	{
		MessageBox(L"请先OnHook！");
		return;
	}

	//创建远程线程调用FreeLibrary
	HANDLE RemoteThread = CreateRemoteThread(m_hRemoteProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)FreeLibrary, (LPVOID)m_RemoteModule, 0, NULL);

	if (RemoteThread == NULL)
	{
		MessageBox(L"卸载失败！");
		return;
	}

	WaitForSingleObject(RemoteThread, INFINITE);
	CloseHandle(m_hRemoteProcess);
	m_hRemoteProcess = NULL;
	m_RemoteModule = NULL;
	return;
}
