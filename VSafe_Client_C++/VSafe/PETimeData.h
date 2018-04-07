#pragma once


// CPETimeData 对话框

class CPETimeData : public CDialogEx
{
	DECLARE_DYNAMIC(CPETimeData)

public:
	CPETimeData(DWORD   TimeDateStamp, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPETimeData();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonTs2TD();				//响应按钮
	DECLARE_MESSAGE_MAP()
private:
	DWORD   m_dwTimeDateStamp;	//时间戳
	CString m_TimeStamp;		//时间戳
	CString m_TimeData;			//时间/日期

	void TimeStamp2TimeData(DWORD   TimeDateStamp);		//转换时间
	
};
