#pragma once
#include "MyList.h"


// CPEExport 对话框

class CPEExport : public CDialogEx
{
	DECLARE_DYNAMIC(CPEExport)

public:
	CPEExport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEExport();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;				//DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//目录地址

	CMyList m_ExportList;					//导出列表
	void GetExportInfo();					//获取导出表信息
											
	CString m_ListOrdinal;					//序号
	CString m_ListName;						//名称
	CString m_ListRVA;						//RVA
	CString m_ListFO;						//FO
											
	CString m_ExportRVA;					//导出RVA
	CString m_ExportSize;					//尺寸
	CString m_Name;							//名称
	CString m_Base;							//基址
	CString m_FunNumber;					//函数数量
	CString m_FunNumberName;				//名称函数数量
	CString m_FunAdd;						//函数地址
	CString m_FunNameAdd;					//函数名称地址
	CString m_FunOrdAdd;					//函数序号地址

};
