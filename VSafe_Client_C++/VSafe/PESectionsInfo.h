#pragma once
#include "MyList.h"


// CPESectionsInfo �Ի���

class CPESectionsInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPESectionsInfo)

public:
	CPESectionsInfo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPESectionsInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_SectionInfoList;		   //������Ϣ�б�
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NTͷ
									   
	CString	m_strName;				   //����
	CString	m_strRVA;				   //RVA
	CString	m_strVS;				   //VS
	CString	m_strFO;				   //FO
	CString	m_strFS;				   //FS
	CString	m_strCha;				   //��������
									   
	void GetSectionsInfo();			   //��ȡ������Ϣ
};
