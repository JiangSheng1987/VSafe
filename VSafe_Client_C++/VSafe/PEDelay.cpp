// PEDelay.cpp : 实现文件
//

#include "stdafx.h"
#include "VSafe.h"
#include "PEDelay.h"
#include "PERva2Fo.h"


// CPEDelay 对话框

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


// CPEDelay 消息处理程序


BOOL CPEDelay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ListDelayDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);

	GetDelayDllInfo();

	m_ListDelayFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPEDelay::OnNMClickListDelayDll(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取选中数据
	int nSel = m_ListDelayDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
		return;
	}

	//获取序号
	int  dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 2), NULL, 16);

	if (dwINTF0 == -1)
	{
		dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//转换
	m_pDelayThunk = (PIMAGE_THUNK_DATA32)((PBYTE)m_pDos + dwINTF0);

	//获取函数信息
	GetDelayFunInfo();

	*pResult = 0;
}

//****************************************************************
// Brief 	: 获取延迟导入表信息
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

	//循环查找
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
// Brief 	: 获取延迟导入函数信息
// Method	: GetDelayFunInfo
// FullName	: CPEDelay::GetDelayFunInfo
// Access	: public 
// Returns	: void
//****************************************************************

void CPEDelay::GetDelayFunInfo()
{
	m_ListDelayFun.DeleteAllItems();

	PBYTE pBuf = (PBYTE)m_pDos;

	//循环查找
	while (m_pDelayThunk->u1.AddressOfData)
	{
		//序号命名
		if (IMAGE_SNAP_BY_ORDINAL32(m_pDelayThunk->u1.Ordinal))
		{
			m_DelayFunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pDelayThunk->u1.Ordinal));
			m_DelayFunName = L"--";
		}
		//名称命名
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
