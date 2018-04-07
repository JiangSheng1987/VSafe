#pragma once
#include "MyList.h"


// CTmProcessInfo �Ի���

class CTmProcessInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CTmProcessInfo)

public:
	CTmProcessInfo(CWnd* pParent, int nMID, int nPID);   // ��׼���캯��
	
	virtual ~CTmProcessInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {	IDD = IDD_DIALOG_PROCESS_INFO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickPoplist1(NMHDR *pNMHDR, LRESULT *pResult);	//�Ҽ��˵�;
	afx_msg void OnMenuThread(UINT id);								//��Ӧ�Ҽ��˵�;

	DECLARE_MESSAGE_MAP()
private:
	int m_nMenuID;				//�Ҽ��˵�ID;
	int m_nPID;					//����PID;
	bool m_bFlag;				//�Ƿ���ʾ�Ҽ��˵�;

	CMyList m_PopList;			//List;
	void ShowModule(int nPid);	//ģ��;
	void ShowThread(int nPid);	//�߳�;
	void ShowHeap(int nPid);	//��;
	
};
