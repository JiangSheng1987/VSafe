#pragma once
#include "MyList.h"

// CEnumWindow 对话框

typedef struct _MYWINDOWINFO
{
	TCHAR hWnd[MAX_PATH+1];
	TCHAR WindowName[MAX_PATH+1];
	TCHAR ClassName[MAX_PATH+1];
}MYWINDOWINFO, *PMYWINDOWINFO;


class CEnumWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CEnumWindow)

public:
	CEnumWindow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnumWindow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_WINDOW};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnRclickWindowList1(NMHDR *pNMHDR, LRESULT *pResult);		//右键菜单;
	afx_msg void OnPopMenu(UINT id);										//响应右键菜单;
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_WindowList;
	void EnumWindow();			//添加窗口;
public:
	static BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam);			//枚举窗口回调函数;

};
