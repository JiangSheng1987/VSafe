#pragma once


// CPEInfo 对话框
class CPEInfo : public CDialogEx
{
// 构造
public:
	CPEInfo(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg HCURSOR OnQueryDragIcon();			 
	afx_msg void OnPaint();						 
	afx_msg void OnDropFiles(HDROP hDropInfo);	 //拖曳文件
	afx_msg void OnBnClickedButtonRVA();		 //RVA计算
	afx_msg void OnBnClickedButtonTime();		 //时间转换
	afx_msg void OnBnClickedButtonSections();	 //区段信息
	afx_msg void OnBnClickedButtonDirectory();	 //目录信息
	afx_msg void OnBnClickedButton7();			//打开文件
	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hFile;								//文件句柄	
	CString m_DeleFileName;							//文件路径
	PIMAGE_DOS_HEADER m_pDos;					//DOS头
	PIMAGE_NT_HEADERS m_pNTHeader;				//NT头
	PIMAGE_FILE_HEADER m_pFileHeader;			//文件头
	PIMAGE_OPTIONAL_HEADER m_pOptionalHeader;	//扩展头

	CString m_AddressOfEntryPoint;				//入口点
	CString m_ImageBase;						//基址
	CString m_SizeOfImage;						//镜像大小
	CString m_BaseOfCode;						//代码基址
	CString m_BaseOfData;						//数据基址
	CString m_SectionAlignment;					//内存对齐
	CString m_FileAlignment;					//文件对齐
	CString m_Magic;							//X86/X64
	CString m_Subsystem;						//子系统
	CString m_NumberOfSections;					//区段数量
	CString m_TimeDateStamp;					//时间戳
	CString m_SizeOfHeaders;					//所有头部尺寸
	CString m_DllCharacteristics;				//特征属性
	CString m_NumberOfRvaAndSizes;				//目录数量
	CString m_SizeOfOptionalHeader;				//扩展头大小
	CString m_CheckSum;							//校验和

	void	GetFileInfo();						//获取文件信息
public:
	
};
