// PEBaseRlock.cpp : 实现文件
//

#include "stdafx.h"
#include "PEBaseRlock.h"
#include "PERva2Fo.h"


// CPEBaseRlock 对话框

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


// CPEBaseRlock 消息处理程序


BOOL CPEBaseRlock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListSection.AddColumn(4, L"索引", 100, L"区段", 150, L"RVA", 200, L"数量", 150);

	GetRelocInfo();

	m_ListData.AddColumn(6, L"索引", 50, L"RVA", 80, L"FO", 80, L"类型", 80,L"FAR",100, L"Data",150);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//****************************************************************
// Brief 	: 获取重定位表信息
// Method	: GetRelocInfo
// FullName	: CPEBaseRlock::GetRelocInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CPEBaseRlock::GetRelocInfo()
{	
	//临时指针
	PBYTE pBuf = (PBYTE)m_pDos;

	//获取重定位表
	m_pReloc = (PIMAGE_BASE_RELOCATION)(pBuf + 
		CPERva2Fo::RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress, m_pNTHeader));
	
	//定义索引
	DWORD dwRelocOrinal = 0;

	//循环获取
	while (m_pReloc->VirtualAddress)
	{
		//存入容器
		m_vecPReloc.push_back(m_pReloc);

		//序号
		m_RelocOrdinal.Format(L"%d", dwRelocOrinal);
		//RVA
		m_RelocRVA.Format(L"%p", m_pReloc->VirtualAddress);
		//段名
		GetSectionName(m_pReloc->VirtualAddress);
		//数量
		DWORD dwCount = (m_pReloc->SizeOfBlock - 8) / sizeof(WORD);
		m_NumberBlock.Format(L"%X", dwCount);
		//插入
		m_ListSection.AddItem(4, m_RelocOrdinal,m_SectionName,m_RelocRVA, m_NumberBlock);
		//递增循环
		dwRelocOrinal++;
		m_pReloc = (PIMAGE_BASE_RELOCATION)((PBYTE)m_pReloc + m_pReloc->SizeOfBlock);
	}

}

//****************************************************************
// Brief 	: 获取数据所在区块名称
// Method	: GetSectionName
// FullName	: CPEBaseRlock::GetSectionName
// Access	: public 
// Returns	: void
// Parameter: DWORD dwRVA
//****************************************************************

void CPEBaseRlock::GetSectionName(DWORD dwRVA)
{
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(m_pNTHeader);
	//循环查找
	for (int i = 0; i < m_pNTHeader->FileHeader.NumberOfSections; i++)
	{
		//比对地址
		if (dwRVA >= pSec[i].VirtualAddress&&
			dwRVA <= pSec[i].VirtualAddress + pSec[i].SizeOfRawData)
		{
			//区段名	RVA	VS	FO	FS
			CHAR pName[9] = {};
			memcpy_s(pName, 9, pSec[i].Name, 8);
			m_SectionName = pName;
			return;
		}
	}

	m_SectionName = L"--";
}


//****************************************************************
// Brief 	: 获取区块详细信息
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

	//循环输出
	for (DWORD i=0;i<dwCount;i++)
	{
		m_DataOrinal.Format(L"%d", i);

		DWORD RvaFinal = pReloc->VirtualAddress + pOffset[i].offset;
		m_DataRVA.Format(L"%X", RvaFinal);

		DWORD dwFO = CPERva2Fo::RVA2FO(RvaFinal, m_pNTHeader);
		m_DataFO.Format(L"%X", dwFO);

		m_Type.Format(L"%d", pOffset[i].type);

		//判断类型
		if (pOffset[i].type==3)
		{
			PDWORD pDataFind = (PDWORD)(pBuf + dwFO);
			m_DataAdd.Format(L"%X", *pDataFind);

			//转换实际数据地址
			DWORD dwDataVA = *pDataFind;
			DWORD dwDataRVA = dwDataVA - m_pNTHeader->OptionalHeader.ImageBase;
			DWORD dwDataFO = CPERva2Fo::RVA2FO(dwDataRVA, m_pNTHeader);

			//使用无符号PBYTE类型
			PBYTE pDataByte = (PBYTE)(pBuf + dwDataFO);			
			//判断数据类型
			if ((*pDataByte>='A'&&*pDataByte <='z')&&
				(*(pDataByte +1) >= 'A'&&*(pDataByte + 1) <= 'z'))
			{
				m_DataInfo = pDataByte;
			}
			else
			{
				//输出十六进制字节
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


//响应点击列表事件
void CPEBaseRlock::OnNMClickListSection(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取选中数据
	int nSel = m_ListSection.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
		return;
	}

	int nOrdinal = wcstol(m_ListSection.GetItemText(nSel, 0), NULL, 10);

	//获取重定位区块详细信息
	GetDataInfo(m_vecPReloc[nOrdinal]);


	*pResult = 0;
}
