// FileMgr.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "FileMgr.h"
#include "afxdialogex.h"
#include "TmEnumWindow.h"
#include "TmFileInfo.h"
#include "Md5.h"

// CFileMgr 对话框

IMPLEMENT_DYNAMIC(CFileMgr, CDialogEx)

CFileMgr::CFileMgr(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILEMGR, pParent)
	, m_CurrentPath(_T(""))
{

}

CFileMgr::~CFileMgr()
{
}

void CFileMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListFileMgr);
	DDX_Text(pDX, IDC_EDIT_PATH, m_CurrentPath);
}


BEGIN_MESSAGE_MAP(CFileMgr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WINDOW, &CFileMgr::OnBnClickedButtonWindow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE, &CFileMgr::OnNMDblclkListFile)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CFileMgr::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_BEFORE, &CFileMgr::OnBnClickedButtonBefore)
	ON_BN_CLICKED(IDC_BUTTON_AFTER, &CFileMgr::OnBnClickedButtonAfter)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILE, &CFileMgr::OnNMRClickListFile)
	ON_COMMAND(ID_42003, &CFileMgr::OnBlack)
	ON_COMMAND(ID_42004, &CFileMgr::OnWhite)
	ON_COMMAND(ID_42005, &CFileMgr::OnDiskView)
	ON_COMMAND(ID_42006, &CFileMgr::OnFileInfo)
END_MESSAGE_MAP()


// CFileMgr 消息处理程序


BOOL CFileMgr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListFileMgr.AddColumn(3, L"名称", 150,L"类型",150, L"路径", 250);

	//获取磁盘信息
	GetDiskInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CFileMgr::GetDiskInfo()
{
	//获取盘符;
	TCHAR szBuf[1024] = {};
	GetLogicalDriveStrings(1024, szBuf);
	TCHAR *pstr = szBuf;

	while (*pstr)
	{
		m_vecFileList.push_back(pstr);
		//获取下一个盘符;
		pstr += _tcslen(pstr) + 1;
	}

	//循环输出;
	for (DWORD i = 0; i < m_vecFileList.size(); i++)
	{
		//获取文件类型;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(m_vecFileList[i], 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_FileType = FileInfo.szTypeName;

		m_ListFileMgr.AddItem(3, m_vecFileList[i], m_FileType, m_vecFileList[i]);
	}
}

//打开文件夹
void CFileMgr::OpenFloder()
{

	//判断路径是否为空;
	if (m_FilePath.IsEmpty())
	{
		//清空数据
		m_ListFileMgr.DeleteAllItems();
		m_vecFileList.clear();
		GetDiskInfo();
		return;
	}

	//清空数据
	m_ListFileMgr.DeleteAllItems();
	m_vecFileList.clear();

	//打开文件路径;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(m_FilePath, &wsd);

	//驱动器+*;文件夹\*;
	if (m_FilePath.GetLength()<4)
	{
		m_FilePath += L"*";
	}
	else
	{
		m_FilePath += L"\\*";
	}	
	
	hFind = FindFirstFile(m_FilePath, &wsd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		//过滤本级和上级;
		if (!wcscmp(wsd.cFileName, L".")
			|| !wcscmp(wsd.cFileName, L".."))
		{
			continue;
		}
		
		//转换文件名格式;
		TCHAR* szBuff = wsd.cFileName;
		//拼接文件名;
		CString FileFath = m_FilePath.Left(m_FilePath.GetLength() - 1);
		FileFath += wsd.cFileName;	

		//获取文件类型;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(FileFath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_FileType = FileInfo.szTypeName;

		m_vecFileList.push_back(FileFath);
		m_ListFileMgr.AddItem(3, szBuff,m_FileType, FileFath);

	} while (FindNextFile(hFind, &wsd));

	FindClose(hFind);
	
}

//读取数据
void CFileMgr::ReadDataBase(DWORD dwType)
{
	//读取黑名单
	CString strBlack = szFileName[dwType];
	CStdioFile sfBlack;
	if (sfBlack.Open(strBlack, CFile::modeRead))
	{
		CString temp;
		//循环读取
		while (sfBlack.ReadString(temp))
		{
			m_vecData.push_back(temp);
		}
		sfBlack.Close();
	}
}

//保存数据
void CFileMgr::SaveDataBase(DWORD dwType)
{
	//写入文件
	CString sFile = szFileName[dwType];
	CStdioFile sfFile;
	if (sfFile.Open(sFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		for (DWORD i = 0; i < m_vecData.size(); i++)
		{
			m_vecData[i] += L"\r\n";
			sfFile.WriteString(m_vecData[i]);
		}
		sfFile.Close();
	}
}

//枚举窗口
void CFileMgr::OnBnClickedButtonWindow()
{
	// TODO: 在此添加控件通知处理程序代码
	CEnumWindow pEW = new CEnumWindow;
	pEW.DoModal();
}

//打开文件或文件夹
void CFileMgr::OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取选中项
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	//获取路径
	m_FilePath = m_ListFileMgr.GetItemText(nSel, 2);

	//检测是否文件夹;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind1 = FindFirstFile(m_FilePath, &wsd);

	//检测是否驱动器
	if (m_FilePath.GetLength()<=3)
	{
		//文件夹打开获取信息;
		m_BeforPath = m_CurrentPath;
		m_CurrentPath = m_FilePath;
		OpenFloder();		
		UpdateData(FALSE);
		return;
	}

	//打开文件;
	if (!(wsd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		ShellExecute(NULL, _T("open"), m_FilePath, NULL, NULL, SW_SHOW);
		return;
	}
	else
	{
		//文件夹打开获取信息;
		m_BeforPath = m_CurrentPath;
		m_CurrentPath = m_FilePath;
		OpenFloder();		
		UpdateData(FALSE);
	}	

	*pResult = 0;
}

//转到路径
void CFileMgr::OnBnClickedButtonGo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_FilePath = m_CurrentPath;
	OpenFloder();
	UpdateData(FALSE);
}

//打开之前路径
void CFileMgr::OnBnClickedButtonBefore()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_BeforPath==m_CurrentPath)
	{
		return;
	}
	m_AfterPath = m_CurrentPath;
	m_FilePath = m_BeforPath;
	m_CurrentPath = m_BeforPath;

	OpenFloder();
	UpdateData(FALSE);
}

//打开之后路径
void CFileMgr::OnBnClickedButtonAfter()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_AfterPath == m_CurrentPath)
	{
		return;
	}
	m_BeforPath = m_CurrentPath;
	m_FilePath = m_AfterPath;
	m_CurrentPath = m_AfterPath;	
	
	OpenFloder();
	UpdateData(FALSE);

}

//弹出菜单
void CFileMgr::OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	//获取弹出菜单;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU2);

	CMenu* pSub = pMenu->GetSubMenu(6);

	//获取鼠标位置;
	CPoint point;
	GetCursorPos(&point);

	//弹出;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}

//加入黑名单
void CFileMgr::OnBlack()
{
	// TODO: 在此添加命令处理程序代码
	//获取所选文件
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	//获取路径
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);
	CStringA strPathA = CW2A(strPathW.GetBuffer(), CP_THREAD_ACP);

	//判断是否文件夹;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(strPathW, &wsd);
	if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		MessageBox(L"请选择正确的文件！");
		return;
	}

	//计算MD5
	CStringA strMD5A = md5FileValue(strPathA.GetBuffer());
	CString strMD5W= CA2W(strMD5A.GetBuffer(), CP_THREAD_ACP);

	//读写文件
	m_vecData.clear();
	ReadDataBase(2);
	m_vecData.push_back(strMD5W);
	SaveDataBase(2);

	MessageBox(L"添加成功！");
}

//加入白名单
void CFileMgr::OnWhite()
{
	// TODO: 在此添加命令处理程序代码

	//获取所选文件
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	//获取路径
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);
	CStringA strPathA = CW2A(strPathW.GetBuffer(), CP_THREAD_ACP);


	//判断是否文件夹;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(strPathW, &wsd);	
	if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		MessageBox(L"请选择正确的文件！");
		return;
	}

	//计算MD5
	CStringA strMD5A = md5FileValue(strPathA.GetBuffer());
	CString strMD5W = CA2W(strMD5A.GetBuffer(), CP_THREAD_ACP);

	//读写文件
	m_vecData.clear();
	ReadDataBase(1);
	m_vecData.push_back(strMD5W);
	SaveDataBase(1);

	MessageBox(L"添加成功！");
	
}


//转到本地磁盘
void CFileMgr::OnDiskView()
{
	// TODO: 在此添加命令处理程序代码

	//清空数据
	m_ListFileMgr.DeleteAllItems();
	m_vecFileList.clear();

	GetDiskInfo();

}

//文件属性
void CFileMgr::OnFileInfo()
{
	// TODO: 在此添加命令处理程序代码


	//获取所选文件
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
	}
	//获取路径
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);

	CTmFileInfo *pTFI = new CTmFileInfo(strPathW);
	pTFI->DoModal();
}
