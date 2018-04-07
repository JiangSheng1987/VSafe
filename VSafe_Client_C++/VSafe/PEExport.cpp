// PEExport.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEExport.h"
#include "PERva2Fo.h"


// CPEExport 对话框

IMPLEMENT_DYNAMIC(CPEExport, CDialogEx)

CPEExport::CPEExport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent)
	, m_ExportRVA(_T(""))
	, m_ExportSize(_T(""))
	, m_Name(_T(""))
	, m_Base(_T(""))
	, m_FunNumber(_T(""))
	, m_FunNumberName(_T(""))
	, m_FunAdd(_T(""))
	, m_FunNameAdd(_T(""))
	, m_FunOrdAdd(_T(""))
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPEExport::~CPEExport()
{
}

void CPEExport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXPORTRVA, m_ExportRVA);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_ExportSize);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_BASE, m_Base);
	DDX_Text(pDX, IDC_EDIT_NFUN, m_FunNumber);
	DDX_Text(pDX, IDC_EDIT_NNAME, m_FunNumberName);
	DDX_Text(pDX, IDC_EDIT_ADD, m_FunAdd);
	DDX_Text(pDX, IDC_EDIT_ADD_NAME, m_FunNameAdd);
	DDX_Text(pDX, IDC_EDIT_ADD_ORDINALS, m_FunOrdAdd);
	DDX_Control(pDX, IDC_LIST_EXPORT, m_ExportList);
}


BEGIN_MESSAGE_MAP(CPEExport, CDialogEx)
END_MESSAGE_MAP()


// CPEExport 消息处理程序


BOOL CPEExport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ExportList.AddColumn(4, L"索引", 50,L"RVA", 120, L"FO", 120, L"Name",150);
	GetExportInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//****************************************************************
// Brief 	: 获取导出表信息
// Method	: GetExportInfo
// FullName	: CPEExport::GetExportInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEExport::GetExportInfo()
{
	
	//找到目录
	PBYTE pBuf = (PBYTE)m_pDos;
	DWORD dwExportRVA = m_pDataDir[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD dwExportSize = m_pDataDir[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	m_ExportRVA.Format(L"%p", dwExportRVA);
	m_ExportSize.Format(L"%X", dwExportSize);

	//找到导出表
	DWORD dwExportFO = CPERva2Fo::RVA2FO(dwExportRVA, m_pNTHeader);
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(pBuf + dwExportFO);
	m_Base.Format(L"%X", pExport->Base);
	m_FunNumber.Format(L"%X", pExport->NumberOfFunctions);
	//函数名称
	m_Name += (CHAR*)(pBuf + CPERva2Fo::RVA2FO(pExport->Name, m_pNTHeader));

	m_FunNumberName.Format(L"%X", pExport->NumberOfNames);
	m_FunNameAdd.Format(L"%p", pExport->AddressOfNames);
	m_FunOrdAdd.Format(L"%p", pExport->AddressOfNameOrdinals);
	m_FunAdd.Format(L"%p", pExport->AddressOfFunctions);

	//循环插入序号	RVA	 FO	函数名
	PDWORD pArrAdd = (PDWORD)(pBuf+ CPERva2Fo::RVA2FO(pExport->AddressOfFunctions, m_pNTHeader));
	PDWORD pArrName = (PDWORD)(pBuf + CPERva2Fo::RVA2FO(pExport->AddressOfNames, m_pNTHeader));
	PWORD pArrOrdinal = (PWORD)(pBuf + CPERva2Fo::RVA2FO(pExport->AddressOfNameOrdinals, m_pNTHeader));

	//地址表循环
	for (int i=0;i<pExport->NumberOfFunctions;i++)
	{
		m_ListOrdinal.Format(L"%X", i + pExport->Base);
		m_ListRVA.Format(L"%p", pArrAdd[i]);
		DWORD dwFO = CPERva2Fo::RVA2FO(pArrAdd[i], m_pNTHeader);
		m_ListFO.Format(L"%X", dwFO);

		bool bFind = false;
		//序号表循环
		for (int j = 0; j < pExport->NumberOfNames; j++)
		{
			if (pArrOrdinal[j]==i)
			{
				m_ListName = "";
				m_ListName += (CHAR*)(pBuf + CPERva2Fo::RVA2FO(pArrName[j], m_pNTHeader));
				bFind = true;
				break;
			}

		}
		if (!bFind)
		{
			m_ListName = "--";
		}

		m_ExportList.AddItem(4, m_ListOrdinal, m_ListRVA, m_ListFO, m_ListName);
	}	

}
