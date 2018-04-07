#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "ClientSocket.h"
#include <vector>
// CAntivirus 对话框

class CAntivirus : public CDialogEx
{
	DECLARE_DYNAMIC(CAntivirus)

public:
	CAntivirus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAntivirus();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedButtonScanFast();	  //快速扫描
	afx_msg void OnBnClickedButtonScanAll();	  //全盘扫描
	afx_msg void OnBnClickedButtonScanDiy();	  //自定义扫描
	afx_msg void OnBnClickedButtonCloud();		  //云查杀

	DECLARE_MESSAGE_MAP()

private:
	CBrush m_Brush0;			   //重绘笔刷
	CFont  m_fBlack00;			   //大字体
	CFont  m_fBlack01;			   //小字体

	CStatic m_TextVSProtection;	   //正在保护
	CStatic m_TextDataBase;		   //数据库
	CStatic m_TextIsolation;	   //隔离区
	CStatic m_TextTrust;		   //信任区
	CStatic m_TextCloud;		   //连接服务器成功

	CMyButton m_BtAllScan;		   //按钮全盘查杀
	CMyButton m_BtPriScan;		   //快速查杀
	CMyButton m_BtCustomScan;	   //自定义查杀
	CMyButton m_BtCloudScan;	   //云查杀

	CClientSocket m_Socket;			//Socket客户端
	CString		  m_MD5;			//MD5
	CString		  m_DatabaseTime;	//更新数据时间
	std::vector<CString>  m_vecMD5;	//读取数据库MD5缓存

	void UpdataDataBase(DWORD dwType);	//读取本地数据	

	const TCHAR* szFileName[4] = {		//本地数据名称
		L" ",
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
private:

	HANDLE hUpdataThread;							//线程句柄
	static UINT  MyThreadUpdata(LPVOID lpParam);	//更新数据库回调函数;
	
};
