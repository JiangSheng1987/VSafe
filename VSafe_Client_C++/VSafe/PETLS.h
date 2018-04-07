#pragma once
#include "MyList.h"


// CPETLS 对话框

class CPETLS : public CDialogEx
{
	DECLARE_DYNAMIC(CPETLS)

public:
	CPETLS(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPETLS();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TLS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;		   //DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;  //目录头
	CString m_FunAdd;				   //函数地址
									   
	CMyList m_ListTLS;				   //TLS列表
	CString m_TLSStart;				   //起始地址
	CString m_TLSEnd;				   //结束地址
	CString m_TLSIndex;				   //索引
	CString m_TLSCallBack;			   //回调函数
	CString m_TLSZero;				   //填充0数量
	CString m_TLSChara;				   //属性
									   
	void GetTLSInfo();				   //获取TLS信息
	
};
