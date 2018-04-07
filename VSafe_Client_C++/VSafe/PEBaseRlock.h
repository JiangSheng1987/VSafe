#pragma once
#include "MyList.h"
#include <vector>
using namespace std;

// CPEBaseRlock 对话框

class CPEBaseRlock : public CDialogEx
{
	DECLARE_DYNAMIC(CPEBaseRlock)

public:
	CPEBaseRlock(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEBaseRlock();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELOC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListSection(NMHDR *pNMHDR, LRESULT *pResult);			//响应点击事件
	DECLARE_MESSAGE_MAP()

public:
	PIMAGE_DOS_HEADER m_pDos;					 //DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;			 //NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;			 //目录头
	PIMAGE_BASE_RELOCATION m_pReloc;			 //重定位表

	vector<PIMAGE_BASE_RELOCATION> m_vecPReloc; //重定位区块
	CMyList m_ListSection;						//区块列表
	CMyList m_ListData;							//区块数据
												
	CString m_RelocOrdinal;						//序号
	CString m_SectionName;						//数据块位置
	CString m_RelocRVA;							//RVA
	CString m_NumberBlock;						//数据
												
												
	CString m_DataOrinal;						//序号
	CString m_Type;								//类型
	CString m_DataFO;							//FO
	CString m_DataRVA;							//RVA
	CString m_DataAdd;							//地址
	CString m_DataInfo;							//数据信息

	void GetRelocInfo();							 //重定位信息
	void GetSectionName(DWORD dwRVA);				 //获取区块名
	void GetDataInfo(PIMAGE_BASE_RELOCATION pReloc); //获取区块内容
	
};

typedef struct MyStruct
{
	WORD offset : 12;	//重定位小偏移
	WORD type : 4;		//重定位类型
}TYPEOFFSET;