#pragma once
#include "MyList.h"
#include <vector>


// CFileMgr 对话框

class CFileMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CFileMgr)

public:
	CFileMgr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileMgr();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILEMGR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonWindow();		//枚举窗口
	afx_msg void OnBnClickedButtonGo();			//转到路径
	afx_msg void OnBnClickedButtonBefore();		//向前
	afx_msg void OnBnClickedButtonAfter();		//向后
	afx_msg void OnBlack();						//拉黑
	afx_msg void OnWhite();						//拉白
	afx_msg void OnDiskView();					//驱动器
	afx_msg void OnFileInfo();					//文件信息

	afx_msg void OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult);//单击右键菜单
	afx_msg void OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult);//双击打开
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListFileMgr;						 //文件列表
		
	CString m_FileType;							 //文件类型
	CString m_FilePath;							 //文件路径
	CString m_CurrentPath;						 //当前路径
	CString m_AfterPath;						 //向后路径
	CString m_BeforPath;						 //向前路径	
												 
	std::vector<CString> m_vecFileList;			 //路径清单
	void GetDiskInfo();							 //获取盘符信息
	void OpenFloder();							 //打开文件夹
												 
	void ReadDataBase(DWORD dwType);			 //读取病毒库
	void SaveDataBase(DWORD dwType);			 //保存病毒库
												 
	std::vector<CString>  m_vecData;			 //文件操作缓存
												 
	const TCHAR* szFileName[3] = {				 //数据库文件
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
public:

	
	
};
