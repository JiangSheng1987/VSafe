#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CProtection �Ի���

class CProtection : public CDialogEx
{
	DECLARE_DYNAMIC(CProtection)

public:
	CProtection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProtection();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton();				//���̹���
	afx_msg void OnBnClickedButtonRun();			//������
	afx_msg void OnBnClickedButtonSoftware();		//�������
	afx_msg void OnBnClickedButtonServices();		//�������
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush1;			   //��ˢ
	CFont  m_fBlack1;			   //����
	CStatic m_TextSelfDefense;	   //ϵͳ����

	CMyButton m_BtProcess;		   //���̰�ť
	CMyButton m_BtService;		   //����ť
	CMyButton m_BtSoftware;		   //�����ť
	CMyButton m_BtStartup;		   //�����ť

public:

};
