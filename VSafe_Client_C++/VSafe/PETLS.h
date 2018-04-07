#pragma once
#include "MyList.h"


// CPETLS �Ի���

class CPETLS : public CDialogEx
{
	DECLARE_DYNAMIC(CPETLS)

public:
	CPETLS(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPETLS();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TLS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;		   //DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;  //Ŀ¼ͷ
	CString m_FunAdd;				   //������ַ
									   
	CMyList m_ListTLS;				   //TLS�б�
	CString m_TLSStart;				   //��ʼ��ַ
	CString m_TLSEnd;				   //������ַ
	CString m_TLSIndex;				   //����
	CString m_TLSCallBack;			   //�ص�����
	CString m_TLSZero;				   //���0����
	CString m_TLSChara;				   //����
									   
	void GetTLSInfo();				   //��ȡTLS��Ϣ
	
};
