#pragma once
#include "MyList.h"
#include <vector>

// CPEResourceInfo �Ի���

class CPEResourceInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPEResourceInfo)

public:
	CPEResourceInfo(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEResourceInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESOURCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListResourcetype(NMHDR *pNMHDR, LRESULT *pResult);		//��Ӧ�б���

	DECLARE_MESSAGE_MAP()

private:

	PIMAGE_DOS_HEADER m_pDos;												   //DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;										   //NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;										   //Ŀ¼ͷ
																			   
	DWORD m_ResouceStar;													   //��Դ��ʼλ��
	PIMAGE_RESOURCE_DIRECTORY m_FirstDirFirstStruct;						   //Ŀ¼һ�ṹ��һ
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_FirstDirSecondStruct;					   //Ŀ¼һ�ṹͷ��
																			   
	PIMAGE_RESOURCE_DIRECTORY m_SecondDirFirstStruct;						   //Ŀ¼���ṹ��һ
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_SecondDirSecondStruct;				   //Ŀ¼���ṹ���
	std::vector<PIMAGE_RESOURCE_DIRECTORY>	m_vecSecondDirFirstStruct;		   //Ŀ¼���ṹ�������
																			   
	PIMAGE_RESOURCE_DIRECTORY m_ThirdDirFirstStruct;						   //Ŀ¼���ṹ��һ
	PIMAGE_RESOURCE_DIRECTORY_ENTRY m_ThirdDirSecondStruct;					   //Ŀ¼���ṹ���
	PIMAGE_RESOURCE_DATA_ENTRY m_ResouceFinal;								   //������Դ
																			   
	void GetResourceType();													   //��ȡ��Դ����
	void GetResourceInfo(DWORD dwIndex);									   //��ȡ��Դ��ϸ��Ϣ
																			   

	CString m_TypeIndex;			  //��������
	CString m_TypeName;				  //��������
	CString m_TypeNumber;			  //��������
									  
	CString m_ResouceIndex;			  //���
	CString m_ResourceInfo;			  //��Ϣ
	CString m_ResourceName;			  //����
	CString m_ResourceLanguage;		  //����
	CString m_ResourceRVA;			  //RVA
	CString m_ResourceSize;			  //��С
									  
	CMyList m_ListResourceType;		  //��Դ����LIST
	CMyList m_ListResourceInfo;		  //��Դ��ϢLIST

	//��Դ��������
	const CHAR *szResouceTypes[17] = { "",
		"���(Cursor)","λͼ(Bitmap)","ͼ��(Icon)","�˵�(Menu)",
		"�Ի���(Dialog)", "�ַ����б�(String Table)", "����Ŀ¼(Font Directory)", "����(Font)",
		"��ݼ�(Accelerators)", "�Ǹ�ʽ����Դ(Unformatted)", "��Ϣ�б�(Message Table)", "���ָ����(Group Cursor)",
		"", "ͼ����(Group Icon)", "", "�汾��Ϣ" };
	
	
};
