#pragma once
#include "MyList.h"


// CPEImport �Ի���

class CPEImport : public CDialogEx
{
	DECLARE_DYNAMIC(CPEImport)

public:
	CPEImport(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEImport();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListDll(NMHDR *pNMHDR, LRESULT *pResult);		//��Ӧ����б�

	DECLARE_MESSAGE_MAP()
private:
	CMyList m_ListDll;						//DLL�б�
	CMyList m_ListFun;						//�����б�
											
	PIMAGE_DOS_HEADER m_pDos;				//DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//Ŀ¼��ַ
	PIMAGE_THUNK_DATA32 m_pThunk;			//INT��
											
	CString m_DllName;						//DLL��
	CString m_NameRVA;						//RVA
	CString m_INT;							//INT
	CString m_IAT;							//IAT
											
	CString m_FunOrdinal;					//�������
	CString m_FunName;						//��������
											
	void GetDllInfo();						//��ȡDLL��Ϣ
	void GetFunInfo();						//��ȡ������Ϣ
};
