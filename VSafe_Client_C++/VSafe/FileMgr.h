#pragma once
#include "MyList.h"
#include <vector>


// CFileMgr �Ի���

class CFileMgr : public CDialogEx
{
	DECLARE_DYNAMIC(CFileMgr)

public:
	CFileMgr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileMgr();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILEMGR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonWindow();		//ö�ٴ���
	afx_msg void OnBnClickedButtonGo();			//ת��·��
	afx_msg void OnBnClickedButtonBefore();		//��ǰ
	afx_msg void OnBnClickedButtonAfter();		//���
	afx_msg void OnBlack();						//����
	afx_msg void OnWhite();						//����
	afx_msg void OnDiskView();					//������
	afx_msg void OnFileInfo();					//�ļ���Ϣ

	afx_msg void OnNMRClickListFile(NMHDR *pNMHDR, LRESULT *pResult);//�����Ҽ��˵�
	afx_msg void OnNMDblclkListFile(NMHDR *pNMHDR, LRESULT *pResult);//˫����
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListFileMgr;						 //�ļ��б�
		
	CString m_FileType;							 //�ļ�����
	CString m_FilePath;							 //�ļ�·��
	CString m_CurrentPath;						 //��ǰ·��
	CString m_AfterPath;						 //���·��
	CString m_BeforPath;						 //��ǰ·��	
												 
	std::vector<CString> m_vecFileList;			 //·���嵥
	void GetDiskInfo();							 //��ȡ�̷���Ϣ
	void OpenFloder();							 //���ļ���
												 
	void ReadDataBase(DWORD dwType);			 //��ȡ������
	void SaveDataBase(DWORD dwType);			 //���没����
												 
	std::vector<CString>  m_vecData;			 //�ļ���������
												 
	const TCHAR* szFileName[3] = {				 //���ݿ��ļ�
		L"db\\VirusDataBase.txt",
		L"db\\WhiteList.txt",
		L"db\\BlackList.txt" };
public:

	
	
};
