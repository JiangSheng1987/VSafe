#pragma once
#include "MyList.h"


// CRun 对话框

class CRun : public CDialogEx
{
	DECLARE_DYNAMIC(CRun)

public:
	CRun(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_RUN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnNMRClickListRun(NMHDR *pNMHDR, LRESULT *pResult);//弹出菜单
	afx_msg void OnMenuModifyData(UINT uID);						//响应菜单
	DECLARE_MESSAGE_MAP()
private:
	CString	m_Name;		  //键名
	CString m_Key;		  //键值
						  
	HKEY m_hRootKey1;	  //主键1
	HKEY m_hRootKey2;	  //主键2
	CString m_Root1;	  //主键1
	CString m_Root2;	  //主键2
	CString m_SubKey1;	  //子键1
	CString m_SubKey2;	  //子键2
						  
	CMyList m_ListRun;	  //列表
						  
	void DeleRun();		  //删除启动项
	void UpDataRun();	  //刷新启动项
	void AddRun();		  //添加驱动型
	void GetRunInfo(HKEY hRootKey, CString Path);//获取启动项
public:
	
};
