#include "stdafx.h"
#include "TmFileInfo.h"
#include "Md5.h"

// CTmFileInfo 对话框

IMPLEMENT_DYNAMIC(CTmFileInfo, CDialogEx)

CTmFileInfo::CTmFileInfo(CString  Path, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILEINFO, pParent)
	, m_StrFileName(_T(""))
	, m_StrType(_T(""))
	, m_StrPath(Path)
	, m_StrCreatTime(_T(""))
	, m_StrViewTime(_T(""))
	, m_StrChangeTime(_T(""))
	, m_bOnlyRead(FALSE)
	, m_bHide(FALSE)
	, m_StrSize(_T(""))
	, m_StrMD5(_T(""))
{
	
}

CTmFileInfo::~CTmFileInfo()
{
}

void CTmFileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StrFileName);
	DDX_Text(pDX, IDC_EDIT2, m_StrType);
	DDX_Text(pDX, IDC_EDIT3, m_StrPath);
	DDX_Text(pDX, IDC_EDIT4, m_StrCreatTime);
	DDX_Text(pDX, IDC_EDIT5, m_StrViewTime);
	DDX_Text(pDX, IDC_EDIT6, m_StrChangeTime);
	DDX_Check(pDX, IDC_CHECK1, m_bOnlyRead);
	DDX_Check(pDX, IDC_CHECK2, m_bHide);
	DDX_Text(pDX, IDC_EDIT7, m_StrSize);
	DDX_Text(pDX, IDC_EDIT8, m_StrMD5);
}


BEGIN_MESSAGE_MAP(CTmFileInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTmFileInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CTmFileInfo 消息处理程序

//初始化;
BOOL CTmFileInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetFileInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//****************************************************************
// Brief 	: 点击确定;
// Method	: OnBnClickedOk
// FullName	: CTmFileInfo::OnBnClickedOk
// Access	: public 
// Returns	: void
//****************************************************************

void CTmFileInfo::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	DWORD Attr = GetFileAttributes(m_StrPath);
	Attr = Attr &~FILE_ATTRIBUTE_READONLY &~FILE_ATTRIBUTE_HIDDEN;

	//多选框状态;
	if (m_bOnlyRead)
	{
		Attr |= FILE_ATTRIBUTE_READONLY;
	}
	if (m_bHide)
	{
		Attr |= FILE_ATTRIBUTE_HIDDEN;
	}
	//设置文件属性;
	SetFileAttributes(m_StrPath, Attr);

	CDialogEx::OnOK();
}

void CTmFileInfo::GetFileInfo()
{
	//获取文件信息;	
	CFileStatus FileStatus;
	if (CFile::GetStatus(m_StrPath, FileStatus))
	{
		m_StrFileName = FileStatus.m_szFullName;
		m_StrCreatTime.Format(FileStatus.m_ctime.Format("%Y年%m月%d日  %H:%M:%S"));
		m_StrChangeTime.Format(FileStatus.m_mtime.Format("%Y年%m月%d日  %H:%M:%S"));
		m_StrViewTime.Format(FileStatus.m_atime.Format("%Y年%m月%d日  %H:%M:%S"));

		//文件尺寸;
		if (FileStatus.m_size / 1024 < 1)
			m_StrSize.Format(L"%d Byte", FileStatus.m_size);
		else if (FileStatus.m_size / 1024 / 1024 < 1)
			m_StrSize.Format(L"%d KB", FileStatus.m_size / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 < 1)
			m_StrSize.Format(L"%d MB", FileStatus.m_size / 1024 / 1024);
		else if (FileStatus.m_size / 1024 / 1024 / 1024 / 1024 < 1)
			m_StrSize.Format(L"%d GB", FileStatus.m_size / 1024 / 1024 / 1024);

		//文件属性;
		if ((FileStatus.m_attribute & CFile::readOnly) == CFile::readOnly)
		{
			m_bOnlyRead = TRUE;
		}
		if ((FileStatus.m_attribute & CFile::hidden) == CFile::hidden)
		{
			m_bHide = TRUE;
		}

		//MD5		
		CStringA strPath = CW2A(m_StrPath.GetBuffer(), CP_THREAD_ACP);
		m_StrMD5= md5FileValue(strPath.GetBuffer());

		//获取文件类型;
		SHFILEINFO FileInfo = {};
		SHGetFileInfo(m_StrPath, 0, &FileInfo, sizeof(SHFILEINFO), SHGFI_TYPENAME);
		m_StrType = FileInfo.szTypeName;				

		UpdateData(FALSE);
	}

	else
	{
		MessageBox(L"无权限访问");
	}
}
