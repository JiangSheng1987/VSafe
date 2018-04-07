#pragma once
#include "MyList.h"


// CRun �Ի���

class CRun : public CDialogEx
{
	DECLARE_DYNAMIC(CRun)

public:
	CRun(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRun();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_RUN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnNMRClickListRun(NMHDR *pNMHDR, LRESULT *pResult);//�����˵�
	afx_msg void OnMenuModifyData(UINT uID);						//��Ӧ�˵�
	DECLARE_MESSAGE_MAP()
private:
	CString	m_Name;		  //����
	CString m_Key;		  //��ֵ
						  
	HKEY m_hRootKey1;	  //����1
	HKEY m_hRootKey2;	  //����2
	CString m_Root1;	  //����1
	CString m_Root2;	  //����2
	CString m_SubKey1;	  //�Ӽ�1
	CString m_SubKey2;	  //�Ӽ�2
						  
	CMyList m_ListRun;	  //�б�
						  
	void DeleRun();		  //ɾ��������
	void UpDataRun();	  //ˢ��������
	void AddRun();		  //���������
	void GetRunInfo(HKEY hRootKey, CString Path);//��ȡ������
public:
	
};
