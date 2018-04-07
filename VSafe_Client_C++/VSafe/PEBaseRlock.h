#pragma once
#include "MyList.h"
#include <vector>
using namespace std;

// CPEBaseRlock �Ի���

class CPEBaseRlock : public CDialogEx
{
	DECLARE_DYNAMIC(CPEBaseRlock)

public:
	CPEBaseRlock(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEBaseRlock();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELOC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnNMClickListSection(NMHDR *pNMHDR, LRESULT *pResult);			//��Ӧ����¼�
	DECLARE_MESSAGE_MAP()

public:
	PIMAGE_DOS_HEADER m_pDos;					 //DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;			 //NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;			 //Ŀ¼ͷ
	PIMAGE_BASE_RELOCATION m_pReloc;			 //�ض�λ��

	vector<PIMAGE_BASE_RELOCATION> m_vecPReloc; //�ض�λ����
	CMyList m_ListSection;						//�����б�
	CMyList m_ListData;							//��������
												
	CString m_RelocOrdinal;						//���
	CString m_SectionName;						//���ݿ�λ��
	CString m_RelocRVA;							//RVA
	CString m_NumberBlock;						//����
												
												
	CString m_DataOrinal;						//���
	CString m_Type;								//����
	CString m_DataFO;							//FO
	CString m_DataRVA;							//RVA
	CString m_DataAdd;							//��ַ
	CString m_DataInfo;							//������Ϣ

	void GetRelocInfo();							 //�ض�λ��Ϣ
	void GetSectionName(DWORD dwRVA);				 //��ȡ������
	void GetDataInfo(PIMAGE_BASE_RELOCATION pReloc); //��ȡ��������
	
};

typedef struct MyStruct
{
	WORD offset : 12;	//�ض�λСƫ��
	WORD type : 4;		//�ض�λ����
}TYPEOFFSET;