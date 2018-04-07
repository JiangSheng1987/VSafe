#pragma once
#include "MyList.h"
#include "afxwin.h"
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

// CAntiScan 对话框

class CAntiScan : public CDialogEx
{
	DECLARE_DYNAMIC(CAntiScan)

public:
	CAntiScan(CString FilePath,DWORD dwType, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAntiScan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANTISCAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAntiPause();		  //暂停
	afx_msg void OnBnClickedButtonAntiCancle();		  //取消
	afx_msg void OnBnClickedButtonAntiOk();			  //OK
	DECLARE_MESSAGE_MAP()

private:
	
	CMyList m_ListAntiScan;		  //信息列表
	CStatic m_TextScanInfo;		  //扫描信息
								  
	DWORD 	m_dwScanType;		  //扫描类型
	bool	m_IsPause;			  //暂停
	bool	m_IsCancle;			  //取消
	CString m_FolderPath;		  //文件夹路径
	CString m_FilePath;			  //文件路径
								  
	CString m_ScanFileFath;		  //扫描路径
	CString m_ScanMd5;			  //扫描MD5
	CString m_ScanType;			  //扫描类型

	std::vector<CString>  m_vecDisk;		   //驱动器盘符
	std::vector<CString>  m_vecFilePath;	   //文件路径
											   
	std::vector<CString>  m_vecVirusDatabase;  //病毒库
	std::vector<CString>  m_vecBlack;		   //黑名单
	std::vector<CString>  m_vecWhite;		   //白名单

	const TCHAR* szFileName[3] = {			   //本地病毒库文件
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
		
	void AntiScan();							//扫描分发
	void FastScan();							//快速扫描
	void ScanAll();								//快速扫描
	void ScanFile();							//文件
	void ScanFloder(CString FloderName);		//文件夹
	//void CloudScan();							//备用
	void ScanProcess();							//进程												
	void ReadDataBase();						//读取病毒库												
	bool DataBaseCMP(CString strMD5);			//对比MD5

public:
	HANDLE hScanThread;
	static UINT  MyThreadScan(LPVOID lpParam);	//全盘扫描回调函数;

};
