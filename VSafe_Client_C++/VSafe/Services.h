#pragma once
#include "MyList.h"


// CServices �Ի���

class CServices : public CDialogEx
{
	DECLARE_DYNAMIC(CServices)

public:
	CServices(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServices();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVICES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnNMRClickListService(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ��˵�
	afx_msg void OnLvnColumnclickListService(NMHDR *pNMHDR, LRESULT *pResult);	//��ͷ����
	afx_msg void OnMenuService(UINT uID);										//����ֹͣ
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListServices;					  //�����б�
											  
	CString m_ServiceName;					  //����
	CString m_ServiceDesc;					  //����
	CString m_ServiceStatu;					  //״̬
	CString m_ServiceType;					  //����
											  
	void UpDataService();					  //ˢ�·���
	void GetServices();						  //��ȡ����
	void StartAndStopService(bool IsStart);	  //����/ֹͣ����

	const WCHAR* ServiceStatus[8] = {	//����״̬
		L" ",
		L"��ֹͣ",
		L"��������",
		L"����ֹͣ",
		L"��������",
		L"��������",
		L"��ͣ��",
		L"����ͣ",
	};

	const WCHAR* ServerStartType[6] = {	//������������
		L" ",
		L" ",
		L"�Զ�",
		L"�ֶ�",
		L"����",
		L" "
	};
public:
	
};
