#pragma once


// CPEDirectory 对话框

class CPEDirectory : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDirectory)

public:
	CPEDirectory(PIMAGE_DOS_HEADER pDos,PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEDirectory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIRECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonExport();				//导出表
	afx_msg void OnBnClickedButtonImport();				//导入表
	afx_msg void OnBnClickedButtonBasereloc();			//重定位表
	afx_msg void OnBnClickedButtonTls();				//TLS表
	afx_msg void OnBnClickedButtonResouce();			//资源表
	afx_msg void OnBnClickedButtonDelay();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;							//DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;					//NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;					//目录头
	//绑定数组变量
	CString m_ArrRva[16];								//RVA数组
	CString m_ArrSize[16];								//Size数组
														
	void GetDirectoryInfo();							//获取目录信息

	CString m_Rva_In;			   //导入表
	CString m_Rva_Out;			   //导出表
	CString m_Rva_Resouce;		   //资源表
	CString m_Rva_Except;		   //例外
	CString m_Rva_Security;		   //安全
	CString m_Rva_BaseReloc;	   //重定位
	CString m_Rva_Debug;		   //调试
	CString m_Rva_Architecture;	   //版本
	CString m_Rva_GlobalPTR;	   //全局指针
	CString m_Rva_TLS;			   //TLS
	CString m_Rva_load;			   //载入配置
	CString m_Rva_Bound;		   //绑定目录
	CString m_Rva_IAT;			   //IAT表
	CString m_Rva_Delay;		   //延迟载入吧
	CString m_Rva_COM;			   //COM
	CString m_Rva_OT;			   //保留


	CString m_Size_In;			   //导入表
	CString m_Size_Out;			   //导出表
	CString m_Size_Resouce;		   //资源表
	CString m_Size_Except;		   //例外
	CString m_Size_Security;	   //安全
	CString m_Size_BaseReloc;	   //重定位
	CString m_Size_Debug;		   //调试
	CString m_Size_Architecture;   //版本
	CString m_Size_GlobalPTR;	   //全局指针
	CString m_Size_TLS;			   //TLS
	CString m_Size_Load;		   //载入配置
	CString m_Size_Bound;		   //绑定目录
	CString m_Size_IAT;			   //IAT表
	CString m_Size_Delay;		   //延迟载入吧
	CString m_Size_COM;			   //COM
	CString m_Size_OT;			   //保留
	
};
