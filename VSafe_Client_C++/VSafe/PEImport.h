#pragma once
#include "MyList.h"


// CPEImport 对话框

class CPEImport : public CDialogEx
{
	DECLARE_DYNAMIC(CPEImport)

public:
	CPEImport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEImport();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListDll(NMHDR *pNMHDR, LRESULT *pResult);		//响应点击列表

	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListDll;						//DLL列表
	CMyList m_ListFun;						//函数列表
											
	PIMAGE_DOS_HEADER m_pDos;				//DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//目录地址
	PIMAGE_THUNK_DATA32 m_pThunk;			//INT表
											
	CString m_DllName;						//DLL名
	CString m_NameRVA;						//RVA
	CString m_INT;							//INT
	CString m_IAT;							//IAT
											
	CString m_FunOrdinal;					//函数序号
	CString m_FunName;						//函数名称
											
	void GetDllInfo();						//获取DLL信息
	void GetFunInfo();						//获取函数信息
};
