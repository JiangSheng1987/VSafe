// PEResourceInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEResourceInfo.h"
#include "PERva2Fo.h"


// CPEResourceInfo �Ի���

IMPLEMENT_DYNAMIC(CPEResourceInfo, CDialogEx)

CPEResourceInfo::CPEResourceInfo(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RESOURCE, pParent)
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

CPEResourceInfo::~CPEResourceInfo()
{
}

void CPEResourceInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESOURCETYPE, m_ListResourceType);
	DDX_Control(pDX, IDC_LIST_RESOURCEINFO, m_ListResourceInfo);
}


BEGIN_MESSAGE_MAP(CPEResourceInfo, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESOURCETYPE, &CPEResourceInfo::OnNMClickListResourcetype)
END_MESSAGE_MAP()


// CPEResourceInfo ��Ϣ�������


BOOL CPEResourceInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListResourceType.AddColumn(3, L"����", 100, L"����", 200,L"��Դ����",100);

	m_ListResourceInfo.AddColumn(5, L"����", 50, L"����", 180, L"����", 50, L"��ԴRVA", 80, L"��ԴSize", 80);

	GetResourceType();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡ��Դ������Ϣ
// Method	: GetResourceType
// FullName	: CPEResourceInfo::GetResourceType
// Access	: private 
// Returns	: void
//****************************************************************

void CPEResourceInfo::GetResourceType()
{
	PBYTE	pBuf = (PBYTE)m_pDos;	
	DWORD dwResouceFO = CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress, m_pNTHeader);
	
	//��һ��Ŀ¼��һ���ṹ��
	m_FirstDirFirstStruct = (PIMAGE_RESOURCE_DIRECTORY)(pBuf + dwResouceFO);
	//�ڶ����ṹ��
	m_FirstDirSecondStruct = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(m_FirstDirFirstStruct + 1);

	//��Դ��ʼλ��
	m_ResouceStar = (DWORD)m_FirstDirFirstStruct;

	//��Դ������
	DWORD dwNumberResouceType = m_FirstDirFirstStruct->NumberOfNamedEntries +
		m_FirstDirFirstStruct->NumberOfIdEntries;
	
	//ѭ�����
	for (DWORD i = 0; i < dwNumberResouceType; i++)
	{
		//�ж���Դ����
		//�ַ�������
		if (m_FirstDirSecondStruct[i].NameIsString)
		{
			//�ҵ��ַ�����ַ
			DWORD dwNameFO = m_FirstDirSecondStruct[i].NameOffset + m_ResouceStar;
			PIMAGE_RESOURCE_DIR_STRING_U pNameU = (PIMAGE_RESOURCE_DIR_STRING_U)(dwNameFO);
			TCHAR* pName = new TCHAR[pNameU->Length + 1]{};
			memcpy_s(pName, sizeof(TCHAR)*(pNameU->Length + 1),
				pNameU->NameString, sizeof(TCHAR)*(pNameU->Length));

			//printf("%S\n", pName);
			m_TypeName = pName;
		}
		else
		{
			if (m_FirstDirSecondStruct[i].Name <= 16 &&
				m_FirstDirSecondStruct[i].Name >= 0 &&
				m_FirstDirSecondStruct[i].Name != 13 &&
				m_FirstDirSecondStruct[i].Name != 15)
			{
				//printf("%s\n", szResouceTypes[m_FirstDirSecondStruct[i].Name]);
				m_TypeName = szResouceTypes[m_FirstDirSecondStruct[i].Name];
			}
			else
			{
				//printf("%d\n", m_FirstDirSecondStruct[i].Id);
				m_TypeName.Format(L"%04X", m_FirstDirSecondStruct[i].Id);
			}
		}

		m_SecondDirFirstStruct =
			(PIMAGE_RESOURCE_DIRECTORY)(m_FirstDirSecondStruct[i].OffsetToDirectory + m_ResouceStar);
		//�ڶ���Ŀ¼	�ڶ����ṹ��
		m_SecondDirSecondStruct =
			(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(m_SecondDirFirstStruct + 1);
		//��Դ����
		DWORD dwNumberResouceID = m_SecondDirFirstStruct->NumberOfIdEntries +
			m_SecondDirFirstStruct->NumberOfNamedEntries;

		//��������
		m_vecSecondDirFirstStruct.push_back(m_SecondDirFirstStruct);

		m_TypeIndex.Format(L"%04X", i);

		m_TypeNumber.Format(L"%04X", dwNumberResouceID);

		m_ListResourceType.AddItem(3,m_TypeIndex, m_TypeName, m_TypeNumber);

	}


}

//****************************************************************
// Brief 	: ��ȡ��ϸ��Դ��Ϣ
// Method	: GetResourceInfo
// FullName	: CPEResourceInfo::GetResourceInfo
// Access	: private 
// Returns	: void
// Parameter: DWORD dwIndex
//****************************************************************

void CPEResourceInfo::GetResourceInfo(DWORD dwIndex)
{
	m_ListResourceInfo.DeleteAllItems();
	//�ڶ���Ŀ¼	��һ���ṹ��
	PIMAGE_RESOURCE_DIRECTORY SecondDirFirstStruct = m_vecSecondDirFirstStruct[dwIndex];	

	//�ڶ���Ŀ¼	�ڶ����ṹ��
	PIMAGE_RESOURCE_DIRECTORY_ENTRY SecondDirSecondStruct =
		(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(SecondDirFirstStruct + 1);

	//��Դ����
	DWORD dwNumberResouceID = SecondDirFirstStruct->NumberOfIdEntries +
		SecondDirFirstStruct->NumberOfNamedEntries;

	//ѭ����ȡ
	for (DWORD j = 0; j < dwNumberResouceID; j++)
	{
		//�ж���������
		if (SecondDirSecondStruct[j].NameIsString)
		{

			DWORD dwNameFO = SecondDirSecondStruct[j].NameOffset + m_ResouceStar;
			PIMAGE_RESOURCE_DIR_STRING_U pNameU = (PIMAGE_RESOURCE_DIR_STRING_U)(dwNameFO);
			TCHAR* pName = new TCHAR[pNameU->Length + 1]{};
			memcpy_s(pName, sizeof(TCHAR)*(pNameU->Length + 1),
				pNameU->NameString, sizeof(TCHAR)*(pNameU->Length));
			//printf("|----%S\n", pName);
			m_ResourceName = pName;
		}
		else
		{
			//printf("|----%d\n", m_SecondDirSecondStruct[j].Id);
			m_ResourceName.Format(L"%04X", SecondDirSecondStruct[j].Id);
		}

		//������Ŀ¼
		//��һ���ṹ��
		PIMAGE_RESOURCE_DIRECTORY ThirdDirFirstStruct =
			(PIMAGE_RESOURCE_DIRECTORY)(SecondDirSecondStruct[j].OffsetToDirectory + m_ResouceStar);
		//�ڶ����ṹ��
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ThirdDirSecondStruct =
			(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(ThirdDirFirstStruct + 1);
		//printf("|----|----|�������ࣺ%04X\n", ThirdDirSecondStruct->Name);
		m_ResourceLanguage.Format(L"%04X", ThirdDirSecondStruct->Name);
		//������Ϣ
		PIMAGE_RESOURCE_DATA_ENTRY ResouceFinal =
			(PIMAGE_RESOURCE_DATA_ENTRY)(ThirdDirSecondStruct->OffsetToData + m_ResouceStar);
		//printf("|----|----|----|��ԴRVA:%08X\n", ResouceFinal->OffsetToData);
		//printf("|----|----|----|��ԴSize:%X\n", ResouceFinal->Size);
		m_ResourceRVA.Format(L"%08X", ResouceFinal->OffsetToData);
		m_ResourceSize.Format(L"%08X", ResouceFinal->Size);
		m_ResouceIndex.Format(L"%04X", j);
		m_ListResourceInfo.AddItem(5, m_ResouceIndex, m_ResourceName, m_ResourceLanguage, m_ResourceRVA, m_ResourceSize);

	}

}

//��Ӧ�б����¼�
void CPEResourceInfo::OnNMClickListResourcetype(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡѡ������

	int nSel = m_ListResourceType.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
		return;
	}

	DWORD  dwINTF0 = wcstoll(m_ListResourceType.GetItemText(nSel, 0), NULL, 16);
	
	//��ȡ��ϸ��Դ��Ϣ
	GetResourceInfo(dwINTF0);

	*pResult = 0;
}
