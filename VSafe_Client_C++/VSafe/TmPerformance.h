#pragma once
#include "ChartCtrl/ChartCtrl.h"

#include <vector>
#include "afxwin.h"
using std::vector;

// CPerformance �Ի���


class CPerformance : public CDialogEx
{
	DECLARE_DYNAMIC(CPerformance)

public:
	CPerformance(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerformance();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {	IDD = IDD_DIALOG_PERFO};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonRelease();
	DECLARE_MESSAGE_MAP()
private:	

	static UINT  MyThreadFunction(LPVOID lpParam);	//�̻߳ص�����;
	void GetSysInfo();	//��ȡϵͳ�汾��Ϣ
	void GetMem();		//��ȡ�ڴ��С;
	double m_dwMem;		//�ڴ��С;
	void InitFont();	//��ʼ������;		
	CFont m_Font;		//����;
	HANDLE hThread;
	bool m_bClose;	

	//��������;
	CStatic m_TextSysInfo;

	CStatic m_TextCPU;
	CStatic m_TextMem;
	CStatic m_TextDisk;
	CStatic m_TextNet;

	CStatic m_NumCPU;
	CStatic m_NumMem;
	CStatic m_NumDiskRead;
	CStatic m_NumDiskWirte;
	CStatic m_NumNetDown;	
	CStatic m_NumNetUP;

	//��̬��ͼ;
	CChartCtrl m_ChartCPU1;	//ͼ��ؼ�;

	CChartFont labelFont;	//��ǩ����;
	CChartFont labelFont2;	//��ǩ����;�ֺŴ�һ��;

	double m_CPUArr[100];	//CPU����;
	double m_MEMArr[100];	//MEM����;
	double m_X[100];		//X������;

	void Paint();			//��ͼ������;
	void InitChart();		//��ʼ��ͼ����Ϣ;
	void InsertCharData(double dCPU,double dMEM);	//��������;

	void RocketGo();
		
};
