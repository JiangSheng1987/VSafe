// PEExport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEExport.h"
#include "PERva2Fo.h"


// CPEExport �Ի���

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


// CPEExport ��Ϣ�������


BOOL CPEExport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ExportList.AddColumn(4, L"����", 50,L"RVA", 120, L"FO", 120, L"Name",150);
	GetExportInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡ��������Ϣ
// Method	: GetExportInfo
// FullName	: CPEExport::GetExportInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEExport::GetExportInfo()
{
	
	//�ҵ�Ŀ¼
	PBYTE pBuf = (PBYTE)m_pDos;
	DWORD dwExportRVA = m_pDataDir[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD dwExportSize = m_pDataDir[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	m_ExportRVA.Format(L"%p", dwExportRVA);
	m_ExportSize.Format(L"%X", dwExportSize);

	//�ҵ�������
	DWORD dwExportFO = CPERva2Fo::RVA2FO(dwExportRVA, m_pNTHeader);
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(pBuf + dwExportFO);
	m_Base.Format(L"%X", pExport->Base);
	m_FunNumber.Format(L"%X", pExport->NumberOfFunctions);
	//��������
	m_Name += (CHAR*)(pBuf + CPERva2Fo::RVA2FO(pExport->Name, m_pNTHeader));

	m_FunNumberName.Format(L"%X", pExport->NumberOfNames);
	m_FunNameAdd.Format(L"%p", pExport->AddressOfNames);
	m_FunOrdAdd.Format(L"%p", pExport->AddressOfNameOrdinals);
	m_FunAdd.Format(L"%p", pExport->AddressOfFunctions);

	//ѭ���������	RVA	 FO	������
	PDWORD pArrAdd = (PDWORD)(pBuf+ CPERva2Fo::RVA2FO(pExport->AddressOfFunctions, m_pNTHeader));
	PDWORD pArrName = (PDWORD)(pBuf + CPERva2Fo::RVA2FO(pExport->AddressOfNames, m_pNTHeader));
	PWORD pArrOrdinal = (PWORD)(pBuf + CPERva2Fo::RVA2FO(pExport->AddressOfNameOrdinals, m_pNTHeader));

	//��ַ��ѭ��
	for (int i=0;i<pExport->NumberOfFunctions;i++)
	{
		m_ListOrdinal.Format(L"%X", i + pExport->Base);
		m_ListRVA.Format(L"%p", pArrAdd[i]);
		DWORD dwFO = CPERva2Fo::RVA2FO(pArrAdd[i], m_pNTHeader);
		m_ListFO.Format(L"%X", dwFO);

		bool bFind = false;
		//��ű�ѭ��
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
