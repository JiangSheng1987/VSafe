#pragma once

// CTmFileInfo 对话框

class CTmFileInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CTmFileInfo)

public:
	CTmFileInfo(CString  Path, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTmFileInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_FILEINFO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();	//点击OK;
	DECLARE_MESSAGE_MAP()


private:

	CString m_StrFileName;		//文件名;
	CString m_StrType;			//类型;
	CString m_StrPath;			//路径;
	CString m_StrSize;			//大小;
	CString m_StrCreatTime;		//创建时间;
	CString m_StrViewTime;		//访问时间;
	CString m_StrChangeTime;	//修改时间;
	CString m_StrMD5;			//MD5
	BOOL m_bOnlyRead;			//只读;
	BOOL m_bHide;				//隐藏;	
	void GetFileInfo();
public:
	
};
