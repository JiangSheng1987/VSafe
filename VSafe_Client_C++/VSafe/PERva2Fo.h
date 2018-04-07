#pragma once


// CPERva2Fo 对话框

class CPERva2Fo : public CDialogEx
{
	DECLARE_DYNAMIC(CPERva2Fo)

public:
	CPERva2Fo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPERva2Fo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVA2FO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnBnClickedButtonRva2F0();		//计算FO
	DECLARE_MESSAGE_MAP()
private:
	CString m_strVA;					//VA
	CString m_strRVA;					//RVA
	CString m_strFO;					//FO

	PIMAGE_NT_HEADERS32 m_pNTHeader;	//NT头
	
public:
	static DWORD RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt);	//静态函数外部调用
};
