#pragma once
#include "MyList.h"


// CServices 对话框

class CServices : public CDialogEx
{
	DECLARE_DYNAMIC(CServices)

public:
	CServices(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServices();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVICES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnNMRClickListService(NMHDR *pNMHDR, LRESULT *pResult);		//右键菜单
	afx_msg void OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult);	//列头排序
	afx_msg void OnMenuService(UINT uID);										//启动停止
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListServices;					  //服务列表
											  
	CString m_ServiceName;					  //名称
	CString m_ServiceDesc;					  //描述
	CString m_ServiceStatu;					  //状态
	CString m_ServiceType;					  //类型
											  
	void UpDataService();					  //刷新服务
	void GetServices();						  //获取服务
	void StartAndStopService(bool IsStart);	  //启动/停止服务

	const WCHAR* ServiceStatus[8] = {	//服务状态
		L" ",
		L"已停止",
		L"正在启动",
		L"正在停止",
		L"正在运行",
		L"即将继续",
		L"暂停中",
		L"已暂停",
	};

	const WCHAR* ServerStartType[6] = {	//服务启动类型
		L" ",
		L" ",
		L"自动",
		L"手动",
		L"禁用",
		L" "
	};
public:
	
};
