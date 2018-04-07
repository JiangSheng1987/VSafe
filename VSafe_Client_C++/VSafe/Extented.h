#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CExtented 对话框

class CExtented : public CDialogEx
{
	DECLARE_DYNAMIC(CExtented)

public:
	CExtented(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExtented();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();


	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton20Pe();			//PEInfo
	afx_msg void OnBnClickedButtonClean();			//清理文件
	afx_msg void OnBnClickedButton23();				//文件管理
	afx_msg void OnBnClickedButton22();				//性能优化
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush2;		   //笔刷
	CFont  m_fBlack2;		   //字体
	CStatic m_TextTool;		   //扩展工具
							   
	CMyButton m_BtPE;		   //PE按钮
	CMyButton m_BtClean;	   //清理按钮
	CMyButton m_BtRocket;	   //内存按钮
	CMyButton m_BtOT;		   //文件按钮
public:	


};
