#pragma once
#include "MyList.h"
#include "TmProcessInfo.h"


// CTmProcess �Ի���

class CTmProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CTmProcess)

public:
	CTmProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTmProcess();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {	IDD = IDD_DIALOG_PROCESS};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void On32784();					//ˢ��;
	afx_msg void OnClose();					//��������;
	afx_msg void OnAttribute();				//�ļ�����;
	afx_msg void OnColumnclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult);	//�����ͷ����;
	afx_msg void OnMenuClick(UINT id);											//��Ӧ�Ҽ��˵�;
	afx_msg void OnRclickProcessList1(NMHDR *pNMHDR, LRESULT *pResult);			//�����˵�;

	DECLARE_MESSAGE_MAP()
private:
	CMyList m_List;		
	void ShowProcess();		//��ʾ����;
private:
	CString m_DllPath;
	HANDLE m_hRemoteProcess;
	HMODULE m_RemoteModule;
	afx_msg void OnHook();
	afx_msg void OnOffHook();
};
