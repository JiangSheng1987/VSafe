// PEResourceInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEResourceInfo.h"
#include "PERva2Fo.h"


// CPEResourceInfo 对话框

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


// CPEResourceInfo 消息处理程序


BOOL CPEResourceInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListResourceType.AddColumn(3, L"索引", 100, L"种类", 200,L"资源数量",100);

	m_ListResourceInfo.AddColumn(5, L"索引", 50, L"名称", 180, L"语言", 50, L"资源RVA", 80, L"资源Size", 80);

	GetResourceType();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//****************************************************************
// Brief 	: 获取资源类型信息
// Method	: GetResourceType
// FullName	: CPEResourceInfo::GetResourceType
// Access	: private 
// Returns	: void
//****************************************************************

void CPEResourceInfo::GetResourceType()
{
	PBYTE	pBuf = (PBYTE)m_pDos;	
	DWORD dwResouceFO = CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress, m_pNTHeader);
	
	//第一层目录第一个结构体
	m_FirstDirFirstStruct = (PIMAGE_RESOURCE_DIRECTORY)(pBuf + dwResouceFO);
	//第二个结构体
	m_FirstDirSecondStruct = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(m_FirstDirFirstStruct + 1);

	//资源起始位置
	m_ResouceStar = (DWORD)m_FirstDirFirstStruct;

	//资源种类数
	DWORD dwNumberResouceType = m_FirstDirFirstStruct->NumberOfNamedEntries +
		m_FirstDirFirstStruct->NumberOfIdEntries;
	
	//循环输出
	for (DWORD i = 0; i < dwNumberResouceType; i++)
	{
		//判断资源类型
		//字符串命名
		if (m_FirstDirSecondStruct[i].NameIsString)
		{
			//找到字符串地址
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
		//第二层目录	第二个结构体
		m_SecondDirSecondStruct =
			(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(m_SecondDirFirstStruct + 1);
		//资源数量
		DWORD dwNumberResouceID = m_SecondDirFirstStruct->NumberOfIdEntries +
			m_SecondDirFirstStruct->NumberOfNamedEntries;

		//存入容器
		m_vecSecondDirFirstStruct.push_back(m_SecondDirFirstStruct);

		m_TypeIndex.Format(L"%04X", i);

		m_TypeNumber.Format(L"%04X", dwNumberResouceID);

		m_ListResourceType.AddItem(3,m_TypeIndex, m_TypeName, m_TypeNumber);

	}


}

//****************************************************************
// Brief 	: 获取详细资源信息
// Method	: GetResourceInfo
// FullName	: CPEResourceInfo::GetResourceInfo
// Access	: private 
// Returns	: void
// Parameter: DWORD dwIndex
//****************************************************************

void CPEResourceInfo::GetResourceInfo(DWORD dwIndex)
{
	m_ListResourceInfo.DeleteAllItems();
	//第二层目录	第一个结构体
	PIMAGE_RESOURCE_DIRECTORY SecondDirFirstStruct = m_vecSecondDirFirstStruct[dwIndex];	

	//第二层目录	第二个结构体
	PIMAGE_RESOURCE_DIRECTORY_ENTRY SecondDirSecondStruct =
		(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(SecondDirFirstStruct + 1);

	//资源数量
	DWORD dwNumberResouceID = SecondDirFirstStruct->NumberOfIdEntries +
		SecondDirFirstStruct->NumberOfNamedEntries;

	//循环获取
	for (DWORD j = 0; j < dwNumberResouceID; j++)
	{
		//判断名称了下
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

		//第三层目录
		//第一个结构体
		PIMAGE_RESOURCE_DIRECTORY ThirdDirFirstStruct =
			(PIMAGE_RESOURCE_DIRECTORY)(SecondDirSecondStruct[j].OffsetToDirectory + m_ResouceStar);
		//第二个结构体
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ThirdDirSecondStruct =
			(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(ThirdDirFirstStruct + 1);
		//printf("|----|----|语言种类：%04X\n", ThirdDirSecondStruct->Name);
		m_ResourceLanguage.Format(L"%04X", ThirdDirSecondStruct->Name);
		//最终信息
		PIMAGE_RESOURCE_DATA_ENTRY ResouceFinal =
			(PIMAGE_RESOURCE_DATA_ENTRY)(ThirdDirSecondStruct->OffsetToData + m_ResouceStar);
		//printf("|----|----|----|资源RVA:%08X\n", ResouceFinal->OffsetToData);
		//printf("|----|----|----|资源Size:%X\n", ResouceFinal->Size);
		m_ResourceRVA.Format(L"%08X", ResouceFinal->OffsetToData);
		m_ResourceSize.Format(L"%08X", ResouceFinal->Size);
		m_ResouceIndex.Format(L"%04X", j);
		m_ListResourceInfo.AddItem(5, m_ResouceIndex, m_ResourceName, m_ResourceLanguage, m_ResourceRVA, m_ResourceSize);

	}

}

//响应列表点击事件
void CPEResourceInfo::OnNMClickListResourcetype(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//获取选中数据

	int nSel = m_ListResourceType.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
		return;
	}

	DWORD  dwINTF0 = wcstoll(m_ListResourceType.GetItemText(nSel, 0), NULL, 16);
	
	//获取详细资源信息
	GetResourceInfo(dwINTF0);

	*pResult = 0;
}
