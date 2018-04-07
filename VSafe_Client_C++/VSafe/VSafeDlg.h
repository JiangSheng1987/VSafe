
// VSafeDlg.h : 头文件
//
//********************************************
// @Brief 	: 安全卫士
// @Author	: D&K
// @Email 	: D.K_01@qq.com
// @Date 	: 2018/3/25
// @Version : ver 1.0
//********************************************

#pragma once
#include "afxwin.h"
#include "GdipButton.h"
#include "MyTab.h"
#include <VersionHelpers.h>


// CVSafeDlg 对话框
class CVSafeDlg : public CDialogEx
{
// 构造
public:
	CVSafeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VSAFE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//重绘按钮
	afx_msg void OnBnClickedButton1();		//弹出菜单
	afx_msg void On_ButtonTab(UINT nID);	//按钮切换窗口
	afx_msg void OnMenuTop(UINT id);		//响应快捷键
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush;		//主背景色
	
	CMyTab m_TabCtrl;

	CGdipButton m_BtVSafe;
	CGdipButton m_BtAntivirus;
	CGdipButton m_BtProtection;
	CGdipButton m_BtExtended;
	CGdipButton m_BtOther;	

	bool	IsAdmin();							//检测管理员权限//废弃
	bool	IsHighest();						//检测最高权限	//废弃
};
