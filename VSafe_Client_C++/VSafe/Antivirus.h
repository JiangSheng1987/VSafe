#pragma once
#include "afxwin.h"
#include "MyButton.h"
#include "ClientSocket.h"
#include <vector>
// CAntivirus �Ի���

class CAntivirus : public CDialogEx
{
	DECLARE_DYNAMIC(CAntivirus)

public:
	CAntivirus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAntivirus();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedButtonScanFast();	  //����ɨ��
	afx_msg void OnBnClickedButtonScanAll();	  //ȫ��ɨ��
	afx_msg void OnBnClickedButtonScanDiy();	  //�Զ���ɨ��
	afx_msg void OnBnClickedButtonCloud();		  //�Ʋ�ɱ

	DECLARE_MESSAGE_MAP()

private:
	CBrush m_Brush0;			   //�ػ��ˢ
	CFont  m_fBlack00;			   //������
	CFont  m_fBlack01;			   //С����

	CStatic m_TextVSProtection;	   //���ڱ���
	CStatic m_TextDataBase;		   //���ݿ�
	CStatic m_TextIsolation;	   //������
	CStatic m_TextTrust;		   //������
	CStatic m_TextCloud;		   //���ӷ������ɹ�

	CMyButton m_BtAllScan;		   //��ťȫ�̲�ɱ
	CMyButton m_BtPriScan;		   //���ٲ�ɱ
	CMyButton m_BtCustomScan;	   //�Զ����ɱ
	CMyButton m_BtCloudScan;	   //�Ʋ�ɱ

	CClientSocket m_Socket;			//Socket�ͻ���
	CString		  m_MD5;			//MD5
	CString		  m_DatabaseTime;	//��������ʱ��
	std::vector<CString>  m_vecMD5;	//��ȡ���ݿ�MD5����

	void UpdataDataBase(DWORD dwType);	//��ȡ��������	

	const TCHAR* szFileName[4] = {		//������������
		L" ",
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
private:

	HANDLE hUpdataThread;							//�߳̾��
	static UINT  MyThreadUpdata(LPVOID lpParam);	//�������ݿ�ص�����;
	
};
