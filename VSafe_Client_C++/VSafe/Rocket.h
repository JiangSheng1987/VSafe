#pragma once
#include "afxwin.h"
#include "GdipButton.h"

// CRocket 对话框

class CRocket : public CDialogEx
{
	DECLARE_DYNAMIC(CRocket)

public:
	CRocket(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRocket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROCKET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRocket();				//点击结束
	DECLARE_MESSAGE_MAP()
private:
	 CGdipButton m_Rocket;	
public:
	HANDLE hRocketThread;
	static UINT  MyThreadRocket(LPVOID lpParam);	//火箭发射回调函数;
};
