#pragma once


// CPETimeData �Ի���

class CPETimeData : public CDialogEx
{
	DECLARE_DYNAMIC(CPETimeData)

public:
	CPETimeData(DWORD   TimeDateStamp, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPETimeData();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonTs2TD();				//��Ӧ��ť
	DECLARE_MESSAGE_MAP()
private:
	DWORD   m_dwTimeDateStamp;	//ʱ���
	CString m_TimeStamp;		//ʱ���
	CString m_TimeData;			//ʱ��/����

	void TimeStamp2TimeData(DWORD   TimeDateStamp);		//ת��ʱ��
	
};
