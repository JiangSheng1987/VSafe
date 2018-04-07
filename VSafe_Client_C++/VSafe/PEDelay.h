#pragma once
#include "MyList.h"


// CPEDelay 对话框

class CPEDelay : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDelay)

public:
	CPEDelay(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEDelay();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListDelayDll(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
private:

	CMyList m_ListDelayDll;				//DLL列表
	CMyList m_ListDelayFun;				//函数列表
	

	PIMAGE_DOS_HEADER m_pDos;				//DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//目录地址
	PIMAGE_THUNK_DATA32  m_pDelayThunk;		//INT表

	CString m_DelayDllName;					//DLL名
	CString m_DelayNameRVA;					//RVA
	CString m_DelayINT;						//INT
	CString m_DelayIAT;						//IAT

	CString m_DelayFunOrdinal;				//函数序号
	CString m_DelayFunName;					//函数名称

	void GetDelayDllInfo();					//获取DLL信息
	void GetDelayFunInfo();					//获取函数信息
	
};
