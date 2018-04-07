#pragma once
#include "MyList.h"


// CPEDelay �Ի���

class CPEDelay : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDelay)

public:
	CPEDelay(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEDelay();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListDelayDll(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
private:

	CMyList m_ListDelayDll;				//DLL�б�
	CMyList m_ListDelayFun;				//�����б�
	

	PIMAGE_DOS_HEADER m_pDos;				//DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;		//NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;		//Ŀ¼��ַ
	PIMAGE_THUNK_DATA32  m_pDelayThunk;		//INT��

	CString m_DelayDllName;					//DLL��
	CString m_DelayNameRVA;					//RVA
	CString m_DelayINT;						//INT
	CString m_DelayIAT;						//IAT

	CString m_DelayFunOrdinal;				//�������
	CString m_DelayFunName;					//��������

	void GetDelayDllInfo();					//��ȡDLL��Ϣ
	void GetDelayFunInfo();					//��ȡ������Ϣ
	
};
