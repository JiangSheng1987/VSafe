// FileMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "FileMgr.h"
#include "afxdialogex.h"
#include "TmEnumWindow.h"
#include "TmFileInfo.h"
#include "Md5.h"

// CFileMgr �Ի���

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


// CFileMgr ��Ϣ�������


BOOL CFileMgr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListFileMgr.AddColumn(3, L"����", 150,L"����",150, L"·��", 250);

	//��ȡ������Ϣ
	GetDiskInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CFileMgr::GetDiskInfo()
{
	//��ȡ�̷�;
	TCHAR szBuf[1024] = {};
	GetLogicalDriveStrings(1024, szBuf);
	TCHAR *pstr = szBuf;

	while (*pstr)
	{
		m_vecFileList.push_back(pstr);
		//��ȡ��һ���̷�;
		pstr += _tcslen(pstr) + 1;
	}

	//ѭ�����;
	for (DWORD i = 0; i < m_vecFileList.size(); i++)
	{
		//��ȡ�ļ�����;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(m_vecFileList[i], 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_FileType = FileInfo.szTypeName;

		m_ListFileMgr.AddItem(3, m_vecFileList[i], m_FileType, m_vecFileList[i]);
	}
}

//���ļ���
void CFileMgr::OpenFloder()
{

	//�ж�·���Ƿ�Ϊ��;
	if (m_FilePath.IsEmpty())
	{
		//�������
		m_ListFileMgr.DeleteAllItems();
		m_vecFileList.clear();
		GetDiskInfo();
		return;
	}

	//�������
	m_ListFileMgr.DeleteAllItems();
	m_vecFileList.clear();

	//���ļ�·��;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(m_FilePath, &wsd);

	//������+*;�ļ���\*;
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
		//���˱������ϼ�;
		if (!wcscmp(wsd.cFileName, L".")
			|| !wcscmp(wsd.cFileName, L".."))
		{
			continue;
		}
		
		//ת���ļ�����ʽ;
		TCHAR* szBuff = wsd.cFileName;
		//ƴ���ļ���;
		CString FileFath = m_FilePath.Left(m_FilePath.GetLength() - 1);
		FileFath += wsd.cFileName;	

		//��ȡ�ļ�����;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(FileFath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_FileType = FileInfo.szTypeName;

		m_vecFileList.push_back(FileFath);
		m_ListFileMgr.AddItem(3, szBuff,m_FileType, FileFath);

	} while (FindNextFile(hFind, &wsd));

	FindClose(hFind);
	
}

//��ȡ����
void CFileMgr::ReadDataBase(DWORD dwType)
{
	//��ȡ������
	CString strBlack = szFileName[dwType];
	CStdioFile sfBlack;
	if (sfBlack.Open(strBlack, CFile::modeRead))
	{
		CString temp;
		//ѭ����ȡ
		while (sfBlack.ReadString(temp))
		{
			m_vecData.push_back(temp);
		}
		sfBlack.Close();
	}
}

//��������
void CFileMgr::SaveDataBase(DWORD dwType)
{
	//д���ļ�
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

//ö�ٴ���
void CFileMgr::OnBnClickedButtonWindow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEnumWindow pEW = new CEnumWindow;
	pEW.DoModal();
}

//���ļ����ļ���
void CFileMgr::OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ����
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ·��
	m_FilePath = m_ListFileMgr.GetItemText(nSel, 2);

	//����Ƿ��ļ���;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind1 = FindFirstFile(m_FilePath, &wsd);

	//����Ƿ�������
	if (m_FilePath.GetLength()<=3)
	{
		//�ļ��д򿪻�ȡ��Ϣ;
		m_BeforPath = m_CurrentPath;
		m_CurrentPath = m_FilePath;
		OpenFloder();		
		UpdateData(FALSE);
		return;
	}

	//���ļ�;
	if (!(wsd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		ShellExecute(NULL, _T("open"), m_FilePath, NULL, NULL, SW_SHOW);
		return;
	}
	else
	{
		//�ļ��д򿪻�ȡ��Ϣ;
		m_BeforPath = m_CurrentPath;
		m_CurrentPath = m_FilePath;
		OpenFloder();		
		UpdateData(FALSE);
	}	

	*pResult = 0;
}

//ת��·��
void CFileMgr::OnBnClickedButtonGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_FilePath = m_CurrentPath;
	OpenFloder();
	UpdateData(FALSE);
}

//��֮ǰ·��
void CFileMgr::OnBnClickedButtonBefore()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//��֮��·��
void CFileMgr::OnBnClickedButtonAfter()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//�����˵�
void CFileMgr::OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//��ȡ�����˵�;
	CMenu* pMenu = new CMenu;
	pMenu->LoadMenuW(IDR_MENU2);

	CMenu* pSub = pMenu->GetSubMenu(6);

	//��ȡ���λ��;
	CPoint point;
	GetCursorPos(&point);

	//����;
	pSub->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, NULL);

	*pResult = 0;
}

//���������
void CFileMgr::OnBlack()
{
	// TODO: �ڴ���������������
	//��ȡ��ѡ�ļ�
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ·��
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);
	CStringA strPathA = CW2A(strPathW.GetBuffer(), CP_THREAD_ACP);

	//�ж��Ƿ��ļ���;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(strPathW, &wsd);
	if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		MessageBox(L"��ѡ����ȷ���ļ���");
		return;
	}

	//����MD5
	CStringA strMD5A = md5FileValue(strPathA.GetBuffer());
	CString strMD5W= CA2W(strMD5A.GetBuffer(), CP_THREAD_ACP);

	//��д�ļ�
	m_vecData.clear();
	ReadDataBase(2);
	m_vecData.push_back(strMD5W);
	SaveDataBase(2);

	MessageBox(L"��ӳɹ���");
}

//���������
void CFileMgr::OnWhite()
{
	// TODO: �ڴ���������������

	//��ȡ��ѡ�ļ�
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ·��
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);
	CStringA strPathA = CW2A(strPathW.GetBuffer(), CP_THREAD_ACP);


	//�ж��Ƿ��ļ���;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(strPathW, &wsd);	
	if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
	{
		MessageBox(L"��ѡ����ȷ���ļ���");
		return;
	}

	//����MD5
	CStringA strMD5A = md5FileValue(strPathA.GetBuffer());
	CString strMD5W = CA2W(strMD5A.GetBuffer(), CP_THREAD_ACP);

	//��д�ļ�
	m_vecData.clear();
	ReadDataBase(1);
	m_vecData.push_back(strMD5W);
	SaveDataBase(1);

	MessageBox(L"��ӳɹ���");
	
}


//ת�����ش���
void CFileMgr::OnDiskView()
{
	// TODO: �ڴ���������������

	//�������
	m_ListFileMgr.DeleteAllItems();
	m_vecFileList.clear();

	GetDiskInfo();

}

//�ļ�����
void CFileMgr::OnFileInfo()
{
	// TODO: �ڴ���������������


	//��ȡ��ѡ�ļ�
	int nSel = m_ListFileMgr.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
	}
	//��ȡ·��
	CString strPathW = m_ListFileMgr.GetItemText(nSel, 2);

	CTmFileInfo *pTFI = new CTmFileInfo(strPathW);
	pTFI->DoModal();
}
