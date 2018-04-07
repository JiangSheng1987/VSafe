// PEImport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEImport.h"
#include "PERva2Fo.h"


// CPEImport �Ի���

IMPLEMENT_DYNAMIC(CPEImport, CDialogEx)

CPEImport::CPEImport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMPORT, pParent)
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPEImport::~CPEImport()
{
}

void CPEImport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DLL, m_ListDll);
	DDX_Control(pDX, IDC_LIST_FUN, m_ListFun);
}


BEGIN_MESSAGE_MAP(CPEImport, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DLL, &CPEImport::OnNMClickListDll)
END_MESSAGE_MAP()


// CPEImport ��Ϣ�������


BOOL CPEImport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);
	
	GetDllInfo();

	m_ListFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



//****************************************************************
// Brief 	: ��ȡDLL��Ϣ
// Method	: GetDllInfo
// FullName	: CPEImport::GetDllInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEImport::GetDllInfo()
{
	PBYTE pBuf =(PBYTE)m_pDos;
	DWORD dwFO = CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress, m_pNTHeader);
	PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)(pBuf + dwFO);

	//ѭ������
	while (pImport->Name)
	{
		m_DllName = (CHAR*)(pBuf + CPERva2Fo::RVA2FO(pImport->Name, m_pNTHeader));
		m_INT.Format(L"%p", CPERva2Fo::RVA2FO(pImport->OriginalFirstThunk, m_pNTHeader));
		m_IAT.Format(L"%p", CPERva2Fo::RVA2FO(pImport->FirstThunk, m_pNTHeader));
		
		m_ListDll.AddItem(3, m_DllName, m_INT, m_IAT);
		pImport++;
	}
}

//****************************************************************
// Brief 	: ��ȡ������Ϣ
// Method	: GetFunInfo
// FullName	: CPEImport::GetFunInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEImport::GetFunInfo()
{
	m_ListFun.DeleteAllItems();

	PBYTE pBuf = (PBYTE)m_pDos;

	//ѭ������
	while (m_pThunk->u1.AddressOfData)
	{
		//�������
		if (IMAGE_SNAP_BY_ORDINAL32(m_pThunk->u1.Ordinal))
		{
			m_FunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pThunk->u1.Ordinal));
			m_FunName = L"--";
		}
		//��������
		else
		{
			PIMAGE_IMPORT_BY_NAME pName =(PIMAGE_IMPORT_BY_NAME)(pBuf + 
				CPERva2Fo::RVA2FO(m_pThunk->u1.AddressOfData, m_pNTHeader));

			m_FunOrdinal.Format(L"%X",pName->Hint);
			m_FunName = (CHAR*)pName->Name;
		}
		m_ListFun.AddItem(2, m_FunOrdinal, m_FunName);
		m_pThunk++;
	}

}

//****************************************************************
// Brief 	: ��Ӧ���DLL��Ϣ
// Method	: OnNMClickListDll
// FullName	: CPEImport::OnNMClickListDll
// Access	: protected 
// Returns	: void
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//****************************************************************

void CPEImport::OnNMClickListDll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡѡ������
	int nSel = m_ListDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
		return;
	}

	//��ȡ���
	int  dwINTF0 = wcstoll(m_ListDll.GetItemText(nSel, 2), NULL, 16);
	
	if (dwINTF0==-1)
	{
		dwINTF0= wcstoll(m_ListDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//ת��
	m_pThunk = (PIMAGE_THUNK_DATA32)((PBYTE)m_pDos + dwINTF0);

	//��ȡ������Ϣ
	GetFunInfo();

	*pResult = 0;
}
