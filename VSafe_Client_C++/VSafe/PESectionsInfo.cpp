// PESectionsInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PESectionsInfo.h"



// CPESectionsInfo �Ի���

IMPLEMENT_DYNAMIC(CPESectionsInfo, CDialogEx)

CPESectionsInfo::CPESectionsInfo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SECTIONS, pParent)
{
	m_pNTHeader = pNTHeader;
}

CPESectionsInfo::~CPESectionsInfo()
{
}

void CPESectionsInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECTIONS, m_SectionInfoList);
}


BEGIN_MESSAGE_MAP(CPESectionsInfo, CDialogEx)
END_MESSAGE_MAP()


// CPESectionsInfo ��Ϣ�������


BOOL CPESectionsInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SectionInfoList.AddColumn(6, L"Name", 100, L"RVA", 100, L"VS", 100, L"FO", 100, L"FS", 100, L"Cha..", 100);
	GetSectionsInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡ������Ϣ
// Method	: GetSectionsInfo
// FullName	: CPESectionsInfo::GetSectionsInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPESectionsInfo::GetSectionsInfo()
{
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(m_pNTHeader);
	for (int i = 0; i < m_pNTHeader->FileHeader.NumberOfSections; i++)
	{
		//������	RVA	VS	FO	FS
		CHAR pName[9] = {};
		memcpy_s(pName, 9, pSec[i].Name, 8);
		m_strName = pName;
		m_strRVA.Format(L"%p", pSec[i].VirtualAddress);
		m_strVS.Format(L"%p", pSec[i].Misc.VirtualSize);
		m_strFO.Format(L"%p", pSec[i].PointerToRawData);
		m_strFS.Format(L"%p", pSec[i].SizeOfRawData);
		m_strCha.Format(L"%p", pSec[i].Characteristics);

		m_SectionInfoList.AddItem(6, m_strName, m_strRVA, m_strVS, m_strFO, m_strFS, m_strCha);

	}
}
