#pragma once
#include "MyList.h"


// CPESectionsInfo 对话框

class CPESectionsInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPESectionsInfo)

public:
	CPESectionsInfo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPESectionsInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_SectionInfoList;		   //区块信息列表
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NT头
									   
	CString	m_strName;				   //名称
	CString	m_strRVA;				   //RVA
	CString	m_strVS;				   //VS
	CString	m_strFO;				   //FO
	CString	m_strFS;				   //FS
	CString	m_strCha;				   //区块属性
									   
	void GetSectionsInfo();			   //获取区块信息
};
