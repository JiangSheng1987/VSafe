#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CExtented �Ի���

class CExtented : public CDialogEx
{
	DECLARE_DYNAMIC(CExtented)

public:
	CExtented(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExtented();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();


	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton20Pe();			//PEInfo
	afx_msg void OnBnClickedButtonClean();			//�����ļ�
	afx_msg void OnBnClickedButton23();				//�ļ�����
	afx_msg void OnBnClickedButton22();				//�����Ż�
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush2;		   //��ˢ
	CFont  m_fBlack2;		   //����
	CStatic m_TextTool;		   //��չ����
							   
	CMyButton m_BtPE;		   //PE��ť
	CMyButton m_BtClean;	   //����ť
	CMyButton m_BtRocket;	   //�ڴ水ť
	CMyButton m_BtOT;		   //�ļ���ť
public:	


};
