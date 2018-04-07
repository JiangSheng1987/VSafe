// PEBaseRlock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEBaseRlock.h"
#include "PERva2Fo.h"


// CPEBaseRlock �Ի���

IMPLEMENT_DYNAMIC(CPEBaseRlock, CDialogEx)

CPEBaseRlock::CPEBaseRlock(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RELOC, pParent)
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPEBaseRlock::~CPEBaseRlock()
{
}

void CPEBaseRlock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECTION, m_ListSection);
	DDX_Control(pDX, IDC_LIST_DATA, m_ListData);
}


BEGIN_MESSAGE_MAP(CPEBaseRlock, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SECTION, &CPEBaseRlock::OnNMClickListSection)
END_MESSAGE_MAP()


// CPEBaseRlock ��Ϣ�������


BOOL CPEBaseRlock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListSection.AddColumn(4, L"����", 100, L"����", 150, L"RVA", 200, L"����", 150);

	GetRelocInfo();

	m_ListData.AddColumn(6, L"����", 50, L"RVA", 80, L"FO", 80, L"����", 80,L"FAR",100, L"Data",150);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡ�ض�λ����Ϣ
// Method	: GetRelocInfo
// FullName	: CPEBaseRlock::GetRelocInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CPEBaseRlock::GetRelocInfo()
{	
	//��ʱָ��
	PBYTE pBuf = (PBYTE)m_pDos;

	//��ȡ�ض�λ��
	m_pReloc = (PIMAGE_BASE_RELOCATION)(pBuf + 
		CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, m_pNTHeader));
	
	//��������
	DWORD dwRelocOrinal = 0;

	//ѭ����ȡ
	while (m_pReloc->VirtualAddress)
	{
		//��������
		m_vecPReloc.push_back(m_pReloc);

		//���
		m_RelocOrdinal.Format(L"%d", dwRelocOrinal);
		//RVA
		m_RelocRVA.Format(L"%p", m_pReloc->VirtualAddress);
		//����
		GetSectionName(m_pReloc->VirtualAddress);
		//����
		DWORD dwCount = (m_pReloc->SizeOfBlock - 8) / sizeof(WORD);
		m_NumberBlock.Format(L"%X", dwCount);
		//����
		m_ListSection.AddItem(4, m_RelocOrdinal,m_SectionName,m_RelocRVA, m_NumberBlock);
		//����ѭ��
		dwRelocOrinal++;
		m_pReloc = (PIMAGE_BASE_RELOCATION)((PBYTE)m_pReloc + m_pReloc->SizeOfBlock);
	}

}

//****************************************************************
// Brief 	: ��ȡ����������������
// Method	: GetSectionName
// FullName	: CPEBaseRlock::GetSectionName
// Access	: public 
// Returns	: void
// Parameter: DWORD dwRVA
//****************************************************************

void CPEBaseRlock::GetSectionName(DWORD dwRVA)
{
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(m_pNTHeader);
	//ѭ������
	for (int i = 0; i < m_pNTHeader->FileHeader.NumberOfSections; i++)
	{
		//�ȶԵ�ַ
		if (dwRVA >= pSec[i].VirtualAddress&&
			dwRVA <= pSec[i].VirtualAddress + pSec[i].SizeOfRawData)
		{
			//������	RVA	VS	FO	FS
			CHAR pName[9] = {};
			memcpy_s(pName, 9, pSec[i].Name, 8);
			m_SectionName = pName;
			return;
		}
	}

	m_SectionName = L"--";
}


//****************************************************************
// Brief 	: ��ȡ������ϸ��Ϣ
// Method	: GetDataInfo
// FullName	: CPEBaseRlock::GetDataInfo
// Access	: public 
// Returns	: void
// Parameter: PIMAGE_BASE_RELOCATION pReloc
//****************************************************************

void CPEBaseRlock::GetDataInfo(PIMAGE_BASE_RELOCATION pReloc)
{
	m_ListData.DeleteAllItems();
	PBYTE pBuf = (PBYTE)m_pDos;

	DWORD dwCount = (pReloc->SizeOfBlock - 8) / sizeof(WORD);
	TYPEOFFSET *pOffset = (TYPEOFFSET*)(pReloc + 1);

	//ѭ�����
	for (DWORD i=0;i<dwCount;i++)
	{
		m_DataOrinal.Format(L"%d", i);

		DWORD RvaFinal = pReloc->VirtualAddress + pOffset[i].offset;
		m_DataRVA.Format(L"%X", RvaFinal);

		DWORD dwFO = CPERva2Fo::RVA2FO(RvaFinal, m_pNTHeader);
		m_DataFO.Format(L"%X", dwFO);

		m_Type.Format(L"%d", pOffset[i].type);

		//�ж�����
		if (pOffset[i].type==3)
		{
			PDWORD pDataFind = (PDWORD)(pBuf + dwFO);
			m_DataAdd.Format(L"%X", *pDataFind);

			//ת��ʵ�����ݵ�ַ
			DWORD dwDataVA = *pDataFind;
			DWORD dwDataRVA = dwDataVA - m_pNTHeader->OptionalHeader.ImageBase;
			DWORD dwDataFO = CPERva2Fo::RVA2FO(dwDataRVA, m_pNTHeader);

			//ʹ���޷���PBYTE����
			PBYTE pDataByte = (PBYTE)(pBuf + dwDataFO);			
			//�ж���������
			if ((*pDataByte>='A'&&*pDataByte <='z')&&
				(*(pDataByte +1) >= 'A'&&*(pDataByte + 1) <= 'z'))
			{
				m_DataInfo = pDataByte;
			}
			else
			{
				//���ʮ�������ֽ�
				m_DataInfo.Format(L"%02X  %02X  %02X  %02X  %02X  %02X  ",
					*(pDataByte),
					*(pDataByte + 1),
					*(pDataByte + 2),
					*(pDataByte + 3),
					*(pDataByte + 4),
					*(pDataByte + 5));
			}
		}
		else
		{			
			m_DataAdd = L"--";
			m_DataInfo = L"--";
		}

		m_ListData.AddItem(6, m_DataOrinal, m_DataRVA, m_DataFO, m_Type,m_DataAdd, m_DataInfo);
	}


}


//��Ӧ����б��¼�
void CPEBaseRlock::OnNMClickListSection(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ������
	int nSel = m_ListSection.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
		return;
	}

	int nOrdinal = wcstol(m_ListSection.GetItemText(nSel, 0), NULL, 10);

	//��ȡ�ض�λ������ϸ��Ϣ
	GetDataInfo(m_vecPReloc[nOrdinal]);


	*pResult = 0;
}
