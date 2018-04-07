#pragma once
#include "MyList.h"

// CClean 对话框

class CClean : public CDialogEx
{
	DECLARE_DYNAMIC(CClean)

public:
	CClean(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClean();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_CLEAN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();				//点击按钮;	
	afx_msg void OnDropFiles(HDROP hDropInfo);		//拖动文件处理;
	afx_msg void OnBnClickedCheckAll();				//全选
	afx_msg void OnBnClickedButtonClean();			//清理文件
	DECLARE_MESSAGE_MAP()
private:	
	DWORD m_dwIndex;
	CString m_DirName;								//文件夹路径;
	CString m_DeleVSName;							//删除文件类型;
	bool DeleFile(CString DirName,CString FileName);					//清理程序;

private:					//系统垃圾清理
	CMyList m_ListClean;
	CString m_Index;
	CString m_DeleFileName;
	CString m_Result;

	BOOL m_CbSystem;
	BOOL m_CbIE;
	BOOL m_CbRecycle;
	BOOL m_CbDisk;
	BOOL m_CbAll;

	CString m_PathA;
	CString m_PathB;

	CString m_PathIE;
	void CleanRecycle();
public:	
	
};
