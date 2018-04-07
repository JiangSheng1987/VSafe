// PETLS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PETLS.h"
#include "PERva2Fo.h"


// CPETLS �Ի���

IMPLEMENT_DYNAMIC(CPETLS, CDialogEx)

CPETLS::CPETLS(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TLS, pParent)
	, m_TLSStart(_T(""))
	, m_TLSEnd(_T(""))
	, m_TLSIndex(_T(""))
	, m_TLSCallBack(_T(""))
	, m_TLSZero(_T(""))
	, m_TLSChara(_T(""))
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPETLS::~CPETLS()
{
}

void CPETLS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TLS, m_ListTLS);
	DDX_Text(pDX, IDC_EDIT_STARTVA, m_TLSStart);
	DDX_Text(pDX, IDC_EDIT_ENDVA, m_TLSEnd);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_TLSIndex);
	DDX_Text(pDX, IDC_EDIT_CALLBACK, m_TLSCallBack);
	DDX_Text(pDX, IDC_EDIT_ZERO, m_TLSZero);
	DDX_Text(pDX, IDC_EDIT_CHARA, m_TLSChara);
}


BEGIN_MESSAGE_MAP(CPETLS, CDialogEx)
END_MESSAGE_MAP()


// CPETLS ��Ϣ�������


BOOL CPETLS::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListTLS.AddColumn(2, L"����", 100, L"������ַ", 300);
	GetTLSInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡTLS��Ϣ
// Method	: GetTLSInfo
// FullName	: CPETLS::GetTLSInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPETLS::GetTLSInfo()
{
	PBYTE pBuf = (PBYTE)m_pDos;
	PIMAGE_TLS_DIRECTORY32 pTLS = (PIMAGE_TLS_DIRECTORY32)(pBuf + 
		CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress, m_pNTHeader));

	m_TLSStart.Format(L"%p", pTLS->StartAddressOfRawData);
	m_TLSEnd.Format(L"%p", pTLS->EndAddressOfRawData);
	m_TLSIndex.Format(L"%08X", pTLS->AddressOfIndex);
	m_TLSCallBack.Format(L"%p", pTLS->AddressOfCallBacks);
	m_TLSZero.Format(L"%08X", pTLS->SizeOfZeroFill);
	m_TLSChara.Format(L"%08X", pTLS->Characteristics);

	//�ҵ��ص�����-
	DWORD dwRVA = pTLS->AddressOfCallBacks - m_pNTHeader->OptionalHeader.ImageBase;
	PWORD pFunAdd = (PWORD)(pBuf + CPERva2Fo::RVA2FO(dwRVA, m_pNTHeader));
	DWORD dwIndex = 0;
	CString strIndex;
	while (*pFunAdd)
	{
		strIndex.Format(L"%d", dwIndex);
		m_FunAdd.Format(L"%p", *pFunAdd);
		m_ListTLS.AddItem(2, strIndex, m_FunAdd);
		pFunAdd++;
		dwIndex++;
	}

}
