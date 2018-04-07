#pragma once


// CPEInfo �Ի���
class CPEInfo : public CDialogEx
{
// ����
public:
	CPEInfo(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg HCURSOR OnQueryDragIcon();			 
	afx_msg void OnPaint();						 
	afx_msg void OnDropFiles(HDROP hDropInfo);	 //��ҷ�ļ�
	afx_msg void OnBnClickedButtonRVA();		 //RVA����
	afx_msg void OnBnClickedButtonTime();		 //ʱ��ת��
	afx_msg void OnBnClickedButtonSections();	 //������Ϣ
	afx_msg void OnBnClickedButtonDirectory();	 //Ŀ¼��Ϣ
	afx_msg void OnBnClickedButton7();			//���ļ�
	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hFile;								//�ļ����	
	CString m_DeleFileName;							//�ļ�·��
	PIMAGE_DOS_HEADER m_pDos;					//DOSͷ
	PIMAGE_NT_HEADERS m_pNTHeader;				//NTͷ
	PIMAGE_FILE_HEADER m_pFileHeader;			//�ļ�ͷ
	PIMAGE_OPTIONAL_HEADER m_pOptionalHeader;	//��չͷ

	CString m_AddressOfEntryPoint;				//��ڵ�
	CString m_ImageBase;						//��ַ
	CString m_SizeOfImage;						//�����С
	CString m_BaseOfCode;						//�����ַ
	CString m_BaseOfData;						//���ݻ�ַ
	CString m_SectionAlignment;					//�ڴ����
	CString m_FileAlignment;					//�ļ�����
	CString m_Magic;							//X86/X64
	CString m_Subsystem;						//��ϵͳ
	CString m_NumberOfSections;					//��������
	CString m_TimeDateStamp;					//ʱ���
	CString m_SizeOfHeaders;					//����ͷ���ߴ�
	CString m_DllCharacteristics;				//��������
	CString m_NumberOfRvaAndSizes;				//Ŀ¼����
	CString m_SizeOfOptionalHeader;				//��չͷ��С
	CString m_CheckSum;							//У���

	void	GetFileInfo();						//��ȡ�ļ���Ϣ
public:
	
};
