// PEDelay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VSafe.h"
#include "PEDelay.h"
#include "PERva2Fo.h"


// CPEDelay �Ի���

IMPLEMENT_DYNAMIC(CPEDelay, CDialogEx)

CPEDelay::CPEDelay(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DELAY, pParent)
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPEDelay::~CPEDelay()
{
}

void CPEDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_DELAY_DLL, m_ListDelayDll);
	DDX_Control(pDX, IDC_LIST_DELAY_FUN, m_ListDelayFun);
}


BEGIN_MESSAGE_MAP(CPEDelay, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DELAY_DLL, &CPEDelay::OnNMClickListDelayDll)
END_MESSAGE_MAP()


// CPEDelay ��Ϣ�������


BOOL CPEDelay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_ListDelayDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);

	GetDelayDllInfo();

	m_ListDelayFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPEDelay::OnNMClickListDelayDll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ������
	int nSel = m_ListDelayDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
		return;
	}

	//��ȡ���
	int  dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 2), NULL, 16);

	if (dwINTF0 == -1)
	{
		dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//ת��
	m_pDelayThunk = (PIMAGE_THUNK_DATA32)((PBYTE)m_pDos + dwINTF0);

	//��ȡ������Ϣ
	GetDelayFunInfo();

	*pResult = 0;
}

//****************************************************************
// Brief 	: ��ȡ�ӳٵ������Ϣ
// Method	: GetDelayDllInfo
// FullName	: CPEDelay::GetDelayDllInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CPEDelay::GetDelayDllInfo()
{
	PBYTE pBuf = (PBYTE)m_pDos;
	DWORD dwFO = CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress, m_pNTHeader);
	PIMAGE_DELAYLOAD_DESCRIPTOR pDelay = (PIMAGE_DELAYLOAD_DESCRIPTOR)(pBuf + dwFO);

	//ѭ������
	while (pDelay->DllNameRVA)
	{
		m_DelayDllName = (CHAR*)(pBuf + CPERva2Fo::RVA2FO(pDelay->DllNameRVA, m_pNTHeader));
		m_DelayINT.Format(L"%p", CPERva2Fo::RVA2FO(pDelay->ImportAddressTableRVA, m_pNTHeader));
		m_DelayIAT.Format(L"%p", CPERva2Fo::RVA2FO(pDelay->ImportNameTableRVA, m_pNTHeader));

		m_ListDelayDll.AddItem(3, m_DelayDllName, m_DelayINT, m_DelayIAT);
		pDelay++;
	}
}

//****************************************************************
// Brief 	: ��ȡ�ӳٵ��뺯����Ϣ
// Method	: GetDelayFunInfo
// FullName	: CPEDelay::GetDelayFunInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CPEDelay::GetDelayFunInfo()
{
	m_ListDelayFun.DeleteAllItems();

	PBYTE pBuf = (PBYTE)m_pDos;

	//ѭ������
	while (m_pDelayThunk->u1.AddressOfData)
	{
		//�������
		if (IMAGE_SNAP_BY_ORDINAL32(m_pDelayThunk->u1.Ordinal))
		{
			m_DelayFunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pDelayThunk->u1.Ordinal));
			m_DelayFunName = L"--";
		}
		//��������
		else
		{
			PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)(pBuf +
				CPERva2Fo::RVA2FO(m_pDelayThunk->u1.AddressOfData, m_pNTHeader));

			m_DelayFunOrdinal.Format(L"%X", pName->Hint);
			m_DelayFunName = (CHAR*)pName->Name;
		}
		m_ListDelayFun.AddItem(2, m_DelayFunOrdinal, m_DelayFunName);
		m_pDelayThunk++;
	}
}
