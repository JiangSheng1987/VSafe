#pragma once
#include "MyList.h"
#include "TmProcessInfo.h"


// CTmProcess 对话框

class CTmProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CTmProcess)

public:
	CTmProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTmProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {	IDD = IDD_DIALOG_PROCESS};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void On32784();					//刷新;
	afx_msg void OnClose();					//结束进程;
	afx_msg void OnAttribute();				//文件属性;
	afx_msg void OnColumnclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult);	//点击列头排序;
	afx_msg void OnMenuClick(UINT id);											//响应右键菜单;
	afx_msg void OnRclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult);			//弹出菜单;

	DECLARE_MESSAGE_MAP()
private:
	CMyList m_List;		
	void ShowProcess();		//显示进程;
private:
	CString m_DllPath;
	HANDLE m_hRemoteProcess;
	HMODULE m_RemoteModule;
	afx_msg void OnHook();
	afx_msg void OnOffHook();
};
