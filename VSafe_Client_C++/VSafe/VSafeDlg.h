
// VSafeDlg.h : ͷ�ļ�
//
//********************************************
// @Brief 	: ��ȫ��ʿ
// @Author	: D&K
// @Email 	: D.K_01@qq.com
// @Date 	: 2018/3/25
// @Version : ver 1.0
//********************************************

#pragma once
#include "afxwin.h"
#include "GdipButton.h"
#include "MyTab.h"
#include <VersionHelpers.h>


// CVSafeDlg �Ի���
class CVSafeDlg : public CDialogEx
{
// ����
public:
	CVSafeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VSAFE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//�ػ水ť
	afx_msg void OnBnClickedButton1();		//�����˵�
	afx_msg void On_ButtonTab(UINT nID);	//��ť�л�����
	afx_msg void OnMenuTop(UINT id);		//��Ӧ��ݼ�
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_Brush;		//������ɫ
	
	CMyTab m_TabCtrl;

	CGdipButton m_BtVSafe;
	CGdipButton m_BtAntivirus;
	CGdipButton m_BtProtection;
	CGdipButton m_BtExtended;
	CGdipButton m_BtOther;	

	bool	IsAdmin();							//������ԱȨ��//����
	bool	IsHighest();						//������Ȩ��	//����
};
