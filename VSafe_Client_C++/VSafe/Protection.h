#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CProtection 对话框

class CProtection : public CDialogEx
{
	DECLARE_DYNAMIC(CProtection)

public:
	CProtection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProtection();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton();				//进程管理
	afx_msg void OnBnClickedButtonRun();			//启动项
	afx_msg void OnBnClickedButtonSoftware();		//软件管理
	afx_msg void OnBnClickedButtonServices();		//服务管理
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush1;			   //笔刷
	CFont  m_fBlack1;			   //字体
	CStatic m_TextSelfDefense;	   //系统防护

	CMyButton m_BtProcess;		   //进程按钮
	CMyButton m_BtService;		   //服务按钮
	CMyButton m_BtSoftware;		   //软件按钮
	CMyButton m_BtStartup;		   //启动项按钮

public:

};
