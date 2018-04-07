#pragma once
#include "MyList.h"


// CPEExport �Ի���

class CPEExport : public CDialogEx
{
	DECLARE_DYNAMIC(CPEExport)

public:
	CPEExport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEExport();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;				//DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//Ŀ¼��ַ

	CMyList m_ExportList;					//�����б�
	void GetExportInfo();					//��ȡ��������Ϣ
											
	CString m_ListOrdinal;					//���
	CString m_ListName;						//����
	CString m_ListRVA;						//RVA
	CString m_ListFO;						//FO
											
	CString m_ExportRVA;					//����RVA
	CString m_ExportSize;					//�ߴ�
	CString m_Name;							//����
	CString m_Base;							//��ַ
	CString m_FunNumber;					//��������
	CString m_FunNumberName;				//���ƺ�������
	CString m_FunAdd;						//������ַ
	CString m_FunNameAdd;					//�������Ƶ�ַ
	CString m_FunOrdAdd;					//������ŵ�ַ

};
