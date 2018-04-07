#pragma once
#include "afxwin.h"
#include "GdipButton.h"

// CRocket �Ի���

class CRocket : public CDialogEx
{
	DECLARE_DYNAMIC(CRocket)

public:
	CRocket(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRocket();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROCKET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedRocket();				//�������
	DECLARE_MESSAGE_MAP()
private:
	 CGdipButton m_Rocket;	
public:
	HANDLE hRocketThread;
	static UINT  MyThreadRocket(LPVOID lpParam);	//�������ص�����;
};
