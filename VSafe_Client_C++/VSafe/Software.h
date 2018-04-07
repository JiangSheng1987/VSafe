#pragma once
#include "MyList.h"
#include <vector>

// CSoftware �Ի���

//�Զ��������Ϣ�ṹ��
typedef struct _SOFTINFO
{
	WCHAR szSoftName[MAX_PATH];
	WCHAR szSoftPub[100];
	WCHAR szSoftDate[20];
	WCHAR szSoftSize[20];
	WCHAR szSoftVer[30];
	WCHAR szSoftInsPath[MAX_PATH];
	WCHAR szSoftUniPath[MAX_PATH];

}SOFTINFO, *PSOFTINFO;


class CSoftware : public CDialogEx
{
	DECLARE_DYNAMIC(CSoftware)

public:
	CSoftware(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSoftware();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SOFTWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnMenuSoftMG(UINT uID);										//��Ӧ�˵�
	afx_msg void OnNMRClickListSoftware(NMHDR *pNMHDR, LRESULT *pResult);		//�����˵�
	afx_msg void OnLvnColumnclickListSoftware(NMHDR *pNMHDR, LRESULT *pResult);	//�б���ͷ����
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListSoftware;				  //�б�
										  
	HKEY m_hRootKey;					  //����
	CString m_SubKey1;					  //�Ӽ�1
	CString m_SubKey2;					  //�Ӽ�2
										  
	CString m_KeyName;					  //����
	CString m_KeyNameVer;				  //�汾
	CString m_KeyNameDate;				  //����
	CString m_KeyNameSize;				  //��С
	CString m_KeyNamePub;				  //����
	CString m_KeyNameInsPath;			  //��װ·��
	CString m_KeyNameUniPath;			  //ж��·��
										  
	CString m_SoftName;					  //��ʾ����
	CString m_SoftPub;					  //����
	CString m_SoftDate;					  //����
	CString m_SoftSize;					  //�ߴ�
	CString m_SoftVer;					  //�汾
	CString m_SoftInsPath;				  //��װ·��
	CString m_SoftUniPath;				  //ж��·��

	std::vector<SOFTINFO> m_vecSoftInfo;	//�洢��Ϣ
	void GetSoftwareInfo(CString SubKey);	//��ȡ�����Ϣ
	void UpdateSoftInfo();					//ˢ��
	void OpenExploer();						//���ļ���
	void UnistallSoft();					//ж�����
public:
		
};
