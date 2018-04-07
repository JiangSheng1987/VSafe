#pragma once


// CPEDirectory �Ի���

class CPEDirectory : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDirectory)

public:
	CPEDirectory(PIMAGE_DOS_HEADER pDos,PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEDirectory();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIRECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonExport();				//������
	afx_msg void OnBnClickedButtonImport();				//�����
	afx_msg void OnBnClickedButtonBasereloc();			//�ض�λ��
	afx_msg void OnBnClickedButtonTls();				//TLS��
	afx_msg void OnBnClickedButtonResouce();			//��Դ��
	afx_msg void OnBnClickedButtonDelay();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;							//DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;					//NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;					//Ŀ¼ͷ
	//���������
	CString m_ArrRva[16];								//RVA����
	CString m_ArrSize[16];								//Size����
														
	void GetDirectoryInfo();							//��ȡĿ¼��Ϣ

	CString m_Rva_In;			   //�����
	CString m_Rva_Out;			   //������
	CString m_Rva_Resouce;		   //��Դ��
	CString m_Rva_Except;		   //����
	CString m_Rva_Security;		   //��ȫ
	CString m_Rva_BaseReloc;	   //�ض�λ
	CString m_Rva_Debug;		   //����
	CString m_Rva_Architecture;	   //�汾
	CString m_Rva_GlobalPTR;	   //ȫ��ָ��
	CString m_Rva_TLS;			   //TLS
	CString m_Rva_load;			   //��������
	CString m_Rva_Bound;		   //��Ŀ¼
	CString m_Rva_IAT;			   //IAT��
	CString m_Rva_Delay;		   //�ӳ������
	CString m_Rva_COM;			   //COM
	CString m_Rva_OT;			   //����


	CString m_Size_In;			   //�����
	CString m_Size_Out;			   //������
	CString m_Size_Resouce;		   //��Դ��
	CString m_Size_Except;		   //����
	CString m_Size_Security;	   //��ȫ
	CString m_Size_BaseReloc;	   //�ض�λ
	CString m_Size_Debug;		   //����
	CString m_Size_Architecture;   //�汾
	CString m_Size_GlobalPTR;	   //ȫ��ָ��
	CString m_Size_TLS;			   //TLS
	CString m_Size_Load;		   //��������
	CString m_Size_Bound;		   //��Ŀ¼
	CString m_Size_IAT;			   //IAT��
	CString m_Size_Delay;		   //�ӳ������
	CString m_Size_COM;			   //COM
	CString m_Size_OT;			   //����
	
};
