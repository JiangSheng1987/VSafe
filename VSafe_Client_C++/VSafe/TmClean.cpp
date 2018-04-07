#include "stdafx.h"
#include "TmClean.h"

// CClean �Ի���

IMPLEMENT_DYNAMIC(CClean, CDialogEx)

CClean::CClean(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CLEAN, pParent)
	, m_DirName(_T(""))
	, m_DeleVSName(_T(""))
	, m_CbSystem(FALSE)
	, m_CbIE(FALSE)
	, m_CbRecycle(FALSE)
	, m_CbDisk(FALSE)
	, m_CbAll(FALSE)
{

}

CClean::~CClean()
{
}

void CClean::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_VSC_EDIT2, m_DirName);
	DDX_Text(pDX, IDC_VSC_EDIT1, m_DeleVSName);
	DDX_Control(pDX, IDC_LIST_CLEAN, m_ListClean);
	DDX_Check(pDX, IDC_CHECK_SYSTEM, m_CbSystem);
	DDX_Check(pDX, IDC_CHECK_IE, m_CbIE);
	DDX_Check(pDX, IDC_CHECK_RECYCLE, m_CbRecycle);
	DDX_Check(pDX, IDC_CHECK_DISK, m_CbDisk);
	DDX_Check(pDX, IDC_CHECK_ALL, m_CbAll);
}


BEGIN_MESSAGE_MAP(CClean, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_VSC_BUTTON1, &CClean::OnBnClickedButton1)	
	ON_BN_CLICKED(IDC_CHECK_ALL, &CClean::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CClean::OnBnClickedButtonClean)
END_MESSAGE_MAP()


// CClean ��Ϣ�������


//****************************************************************
// Brief 	: �����ť;
// Method	: OnBnClickedButton1
// FullName	: CClean::OnBnClickedButton1
// Access	: public 
// Returns	: void
//****************************************************************

void CClean::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ·��;
	UpdateData(TRUE);

	m_ListClean.DeleteAllItems();
	m_Result = L"�Զ�������";
	m_dwIndex = 1;
	
	//����;
	if (DeleFile(m_DirName,m_DeleVSName))
	{
		MessageBox(L"�������");
	}
	else
	{
		MessageBox(L"����ʧ��");
	}
}

//****************************************************************
// Brief 	: �����ļ�;
// Method	: DeleFile
// FullName	: CClean::DeleFile
// Access	: public 
// Returns	: bool
// Parameter: CString DirName
//****************************************************************

bool CClean::DeleFile(CString DirName,CString FileName)
{
	//��·���˳�;
	if (DirName.IsEmpty())
	{
		MessageBox(L"·������");
		return	false;
	}

	//�ж��Ƿ��ļ���;
	WIN32_FIND_DATA wsd = {};
	HANDLE hFind = FindFirstFile(DirName, &wsd);
	if (!(wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
	{
		MessageBox(L"�����ļ���");
		return false;
	}

	DirName += L"\\*";
	hFind = FindFirstFile(DirName, &wsd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"��·��ʧ��");
	}

	do
	{
		//���˱������ϼ�;
		if (!wcscmp(wsd.cFileName, L".")
			|| !wcscmp(wsd.cFileName, L".."))
		{
			continue;
		}
		//�ݹ�����ļ���;
		else if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			CString NextDir = DirName.Left(DirName.GetLength() - 1);
			NextDir += wsd.cFileName;
			DeleFile(NextDir, FileName);
		}
		//ת���ļ�����ʽ;
		TCHAR* szBuff = wsd.cFileName;
		//��ȡ��׺��;
		TCHAR* szExName = PathFindExtension(szBuff);
		//�ԱȺ�׺��;
		if (FileName.Find(szExName) >= 0)
		{
			//ɾ��ָ���ļ�;
			CString DeleFileName = DirName.Left(DirName.GetLength() - 1);
			DeleFileName += wsd.cFileName;
			DeleteFile(DeleFileName);
			m_Index.Format(L"%d", m_dwIndex);
			m_DeleFileName = DeleFileName;			
			m_ListClean.AddItem(3, m_Index, m_DeleFileName, m_Result);
			m_dwIndex++;
		}
		
	} while (FindNextFile(hFind, &wsd));

	FindClose(hFind);

	return true;
}



void CClean::CleanRecycle()
{
	//��ʼ��
	SHQUERYRBINFO RecycleBinInfo = {};
	RecycleBinInfo.cbSize = sizeof(SHQUERYRBINFO);

	//��ѯ��Ϣ
	SHQueryRecycleBin(NULL, &RecycleBinInfo);

	//���
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

//****************************************************************
// Brief 	: �϶��ļ���
// Method	: OnDropFiles
// FullName	: CClean::OnDropFiles
// Access	: public 
// Returns	: void
// Parameter: HDROP hDropInfo
//****************************************************************

void CClean::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	TCHAR szPatch[MAX_PATH] = { 0 };

	UINT nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (UINT idx = 0; idx < nCount; idx++)
	{
		DragQueryFile(hDropInfo, idx, szPatch, MAX_PATH);
		SetDlgItemText(IDC_VSC_EDIT2, szPatch);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}

//��ʼ��;
BOOL CClean::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//�������ԱȨ����ҷ�ļ�;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);		
	// 0x0049 == WM_COPYGLOBALDATA


	//���������ļ�����
	m_DeleVSName = L"\\\.obj \\\.tlog \\\.lastbuildstate \\\.idb \\\.pdb \\\.pch \\\.res \\\.ilk \\\.exe \\\.sdf \\\.ipch \\\.log \\\.db";
	m_DeleFileName = L"\\\.tmp \\\._mp \\\.log \\\.gid \\\.chk \\\.old \\\.bak";
	
	//����·��
	m_PathA = L"%%windir%%";
	m_PathB = L"%%systemdrive%%";
	m_PathIE = L"%%userprofile%%\\Local Settings\\Temporary Internet Files\\";

	m_ListClean.AddColumn(3, L"���", 50, L"�ļ�·��", 200, L"״̬", 100);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CClean::OnBnClickedCheckAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_CbAll)
	{
		m_CbSystem = TRUE;
		m_CbRecycle = TRUE;
		m_CbDisk = TRUE;
		m_CbIE = TRUE;
	}
	else
	{
		m_CbSystem = FALSE;
		m_CbRecycle = FALSE;
		m_CbDisk = FALSE;
		m_CbIE = FALSE;
	}
	UpdateData(FALSE);
}


//****************************************************************
// Brief 	: ��������
// Method	: OnBnClickedButtonClean
// FullName	: CClean::OnBnClickedButtonClean
// Access	: public 
// Returns	: void
//****************************************************************

void CClean::OnBnClickedButtonClean()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	m_ListClean.DeleteAllItems();
	m_dwIndex = 1;
	if (m_CbSystem)
	{
		m_Result = L"ϵͳ����";
		DeleFile(m_PathA, m_DeleFileName);
		DeleFile(m_PathB, m_DeleFileName);
	}

	if (m_CbIE)
	{
		m_Result = L"���������";
		DeleFile(m_PathIE, m_DeleFileName);
	}

	if (m_CbRecycle)
	{
		m_Result = L"����վ";
		CleanRecycle();
	}

	MessageBox(L"������ɣ�");
}
