#pragma once
#include "MyList.h"

// CClean �Ի���

class CClean : public CDialogEx
{
	DECLARE_DYNAMIC(CClean)

public:
	CClean(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClean();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_CLEAN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();				//�����ť;	
	afx_msg void OnDropFiles(HDROP hDropInfo);		//�϶��ļ�����;
	afx_msg void OnBnClickedCheckAll();				//ȫѡ
	afx_msg void OnBnClickedButtonClean();			//�����ļ�
	DECLARE_MESSAGE_MAP()
private:	
	DWORD m_dwIndex;
	CString m_DirName;								//�ļ���·��;
	CString m_DeleVSName;							//ɾ���ļ�����;
	bool DeleFile(CString DirName,CString FileName);					//�������;

private:					//ϵͳ��������
	CMyList m_ListClean;
	CString m_Index;
	CString m_DeleFileName;
	CString m_Result;

	BOOL m_CbSystem;
	BOOL m_CbIE;
	BOOL m_CbRecycle;
	BOOL m_CbDisk;
	BOOL m_CbAll;

	CString m_PathA;
	CString m_PathB;

	CString m_PathIE;
	void CleanRecycle();
public:	
	
};
