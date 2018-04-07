// PEImport.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEImport.h"
#include "PERva2Fo.h"


// CPEImport 对话框

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


// CPEImport 消息处理程序


BOOL CPEImport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);
	
	GetDllInfo();

	m_ListFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



//****************************************************************
// Brief 	: 获取DLL信息
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

	//循环查找
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
// Brief 	: 获取函数信息
// Method	: GetFunInfo
// FullName	: CPEImport::GetFunInfo
// Access	: private 
// Returns	: void
//****************************************************************

void CPEImport::GetFunInfo()
{
	m_ListFun.DeleteAllItems();

	PBYTE pBuf = (PBYTE)m_pDos;

	//循环查找
	while (m_pThunk->u1.AddressOfData)
	{
		//序号命名
		if (IMAGE_SNAP_BY_ORDINAL32(m_pThunk->u1.Ordinal))
		{
			m_FunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pThunk->u1.Ordinal));
			m_FunName = L"--";
		}
		//名称命名
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
// Brief 	: 响应点击DLL信息
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
	// TODO: 在此添加控件通知处理程序代码
	//获取选中数据
	int nSel = m_ListDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
		return;
	}

	//获取序号
	int  dwINTF0 = wcstoll(m_ListDll.GetItemText(nSel, 2), NULL, 16);
	
	if (dwINTF0==-1)
	{
		dwINTF0= wcstoll(m_ListDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//转换
	m_pThunk = (PIMAGE_THUNK_DATA32)((PBYTE)m_pDos + dwINTF0);

	//获取函数信息
	GetFunInfo();

	*pResult = 0;
}
