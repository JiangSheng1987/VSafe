
// MFC_TaskmgrDlg.h : ͷ�ļ�
//

#pragma once
#include "Resource.h"

// CMFC_TaskmgrDlg �Ի���
class CMFC_TaskmgrDlg : public CDialogEx
{
// ����
public:
	CMFC_TaskmgrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TASKMGR_DIALOG };
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
	afx_msg void OnMenuTop(UINT id);

	DECLARE_MESSAGE_MAP()
public:	
	
};
