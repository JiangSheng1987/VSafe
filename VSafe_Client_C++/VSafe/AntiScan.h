#pragma once
#include "MyList.h"
#include "afxwin.h"
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>

// CAntiScan �Ի���

class CAntiScan : public CDialogEx
{
	DECLARE_DYNAMIC(CAntiScan)

public:
	CAntiScan(CString FilePath,DWORD dwType, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAntiScan();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANTISCAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAntiPause();		  //��ͣ
	afx_msg void OnBnClickedButtonAntiCancle();		  //ȡ��
	afx_msg void OnBnClickedButtonAntiOk();			  //OK
	DECLARE_MESSAGE_MAP()

private:
	
	CMyList m_ListAntiScan;		  //��Ϣ�б�
	CStatic m_TextScanInfo;		  //ɨ����Ϣ
								  
	DWORD 	m_dwScanType;		  //ɨ������
	bool	m_IsPause;			  //��ͣ
	bool	m_IsCancle;			  //ȡ��
	CString m_FolderPath;		  //�ļ���·��
	CString m_FilePath;			  //�ļ�·��
								  
	CString m_ScanFileFath;		  //ɨ��·��
	CString m_ScanMd5;			  //ɨ��MD5
	CString m_ScanType;			  //ɨ������

	std::vector<CString>  m_vecDisk;		   //�������̷�
	std::vector<CString>  m_vecFilePath;	   //�ļ�·��
											   
	std::vector<CString>  m_vecVirusDatabase;  //������
	std::vector<CString>  m_vecBlack;		   //������
	std::vector<CString>  m_vecWhite;		   //������

	const TCHAR* szFileName[3] = {			   //���ز������ļ�
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
		
	void AntiScan();							//ɨ��ַ�
	void FastScan();							//����ɨ��
	void ScanAll();								//����ɨ��
	void ScanFile();							//�ļ�
	void ScanFloder(CString FloderName);		//�ļ���
	//void CloudScan();							//����
	void ScanProcess();							//����												
	void ReadDataBase();						//��ȡ������												
	bool DataBaseCMP(CString strMD5);			//�Ա�MD5

public:
	HANDLE hScanThread;
	static UINT  MyThreadScan(LPVOID lpParam);	//ȫ��ɨ��ص�����;

};
