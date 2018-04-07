// PERva2Fo.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PERva2Fo.h"



// CPERva2Fo 对话框

IMPLEMENT_DYNAMIC(CPERva2Fo, CDialogEx)

CPERva2Fo::CPERva2Fo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RVA2FO, pParent)
	, m_strVA(_T(""))
	, m_strRVA(_T(""))
	, m_strFO(_T(""))
{
	m_pNTHeader = pNTHeader;
}

CPERva2Fo::~CPERva2Fo()
{
}

void CPERva2Fo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VA, m_strVA);
	DDX_Text(pDX, IDC_EDIT_RVA, m_strRVA);
	DDX_Text(pDX, IDC_EDIT_FO, m_strFO);
}


BEGIN_MESSAGE_MAP(CPERva2Fo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RVA2F0, &CPERva2Fo::OnBnClickedButtonRva2F0)
END_MESSAGE_MAP()


// CPERva2Fo 消息处理程序


//****************************************************************
// Brief 	: RVA2FO转换
// Method	: OnBnClickedButtonRva2F0
// FullName	: CPERva2Fo::OnBnClickedButtonRva2F0
// Access	: protected 
// Returns	: void
//****************************************************************

void CPERva2Fo::OnBnClickedButtonRva2F0()
{
	// TODO: 在此添加控件通知处理程序代码
	//更新数据
	UpdateData(TRUE);

	//转换
	DWORD dwRva = wcstol(m_strRVA,NULL,16);	
	DWORD dwFO = RVA2FO(dwRva, m_pNTHeader);
	
	if (dwFO==-1)
	{
		MessageBox(L"地址范围有误！");
		return;
	}

	//VA
	DWORD dwVA = m_pNTHeader->OptionalHeader.ImageBase + dwRva;
	m_strVA.Format(L"%p", dwVA);
	m_strRVA.Format(L"%p", dwRva);
	m_strFO.Format(L"%p", dwFO);

	UpdateData(FALSE);
}

//****************************************************************
// Brief 	: RVA2FO外部调用
// Method	: RVA2FO
// FullName	: CPERva2Fo::RVA2FO
// Access	: public static 
// Returns	: DWORD
// Parameter: DWORD dwRva
// Parameter: PIMAGE_NT_HEADERS32 pNt
//****************************************************************

DWORD CPERva2Fo::RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt)
{
	//文件对齐与内存对齐相等
	if (pNt->OptionalHeader.FileAlignment == pNt->OptionalHeader.SectionAlignment)
	{	
		return dwRva;
	}
	//区段头
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(pNt);

	//循环查找
	for (int i = 0; i < pNt->FileHeader.NumberOfSections; i++)
	{
		//比对地址
		if (dwRva >= pSec[i].VirtualAddress&&
			dwRva <= pSec[i].VirtualAddress + pSec[i].SizeOfRawData)
		{
			return	dwRva - pSec[i].VirtualAddress + pSec[i].PointerToRawData;
		}
	}

	return -1;

}

