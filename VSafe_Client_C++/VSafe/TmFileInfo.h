#pragma once

// CTmFileInfo �Ի���

class CTmFileInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CTmFileInfo)

public:
	CTmFileInfo(CString  Path, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTmFileInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_FILEINFO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();	//���OK;
	DECLARE_MESSAGE_MAP()


private:

	CString m_StrFileName;		//�ļ���;
	CString m_StrType;			//����;
	CString m_StrPath;			//·��;
	CString m_StrSize;			//��С;
	CString m_StrCreatTime;		//����ʱ��;
	CString m_StrViewTime;		//����ʱ��;
	CString m_StrChangeTime;	//�޸�ʱ��;
	CString m_StrMD5;			//MD5
	BOOL m_bOnlyRead;			//ֻ��;
	BOOL m_bHide;				//����;	
	void GetFileInfo();
public:
	
};
