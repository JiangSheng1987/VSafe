#pragma once
#include "MyList.h"
#include <vector>

// CPEResourceInfo 对话框

class CPEResourceInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPEResourceInfo)

public:
	CPEResourceInfo(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEResourceInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESOURCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListResourcetype(NMHDR *pNMHDR, LRESULT *pResult);		//响应列表点击

	DECLARE_MESSAGE_MAP()

private:

	PIMAGE_DOS_HEADER m_pDos;												   //DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;										   //NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;										   //目录头
																			   
	DWORD m_ResouceStar;													   //资源起始位置
	PIMAGE_RESOURCE_DIRECTORY m_FirstDirFirstStruct;						   //目录一结构体一
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_FirstDirSecondStruct;					   //目录一结构头二
																			   
	PIMAGE_RESOURCE_DIRECTORY m_SecondDirFirstStruct;						   //目录二结构体一
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_SecondDirSecondStruct;				   //目录二结构体二
	std::vector<PIMAGE_RESOURCE_DIRECTORY>	m_vecSecondDirFirstStruct;		   //目录二结构体二容器
																			   
	PIMAGE_RESOURCE_DIRECTORY m_ThirdDirFirstStruct;						   //目录三结构体一
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_ThirdDirSecondStruct;					   //目录三结构体二
	PIMAGE_RESOURCE_DATA_ENTRY m_ResouceFinal;								   //最终资源
																			   
	void GetResourceType();													   //获取资源类型
	void GetResourceInfo(DWORD dwIndex);									   //获取资源详细信息
																			   

	CString m_TypeIndex;			  //类型索引
	CString m_TypeName;				  //类型名称
	CString m_TypeNumber;			  //类型数量
									  
	CString m_ResouceIndex;			  //序号
	CString m_ResourceInfo;			  //信息
	CString m_ResourceName;			  //名称
	CString m_ResourceLanguage;		  //语言
	CString m_ResourceRVA;			  //RVA
	CString m_ResourceSize;			  //大小
									  
	CMyList m_ListResourceType;		  //资源类型LIST
	CMyList m_ListResourceInfo;		  //资源信息LIST

	//资源名称数组
	const CHAR *szResouceTypes[17] = { "",
		"鼠标(Cursor)","位图(Bitmap)","图标(Icon)","菜单(Menu)",
		"对话框(Dialog)", "字符串列表(String Table)", "字体目录(Font Directory)", "字体(Font)",
		"快捷键(Accelerators)", "非格式化资源(Unformatted)", "消息列表(Message Table)", "鼠标指针组(Group Cursor)",
		"", "图标组(Group Icon)", "", "版本信息" };
	
	
};
