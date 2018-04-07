#pragma once


// CPERva2Fo �Ի���

class CPERva2Fo : public CDialogEx
{
	DECLARE_DYNAMIC(CPERva2Fo)

public:
	CPERva2Fo(PIMAGE_NT_HEADERS32 pNTHeader,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPERva2Fo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RVA2FO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnBnClickedButtonRva2F0();		//����FO
	DECLARE_MESSAGE_MAP()
private:
	CString m_strVA;					//VA
	CString m_strRVA;					//RVA
	CString m_strFO;					//FO

	PIMAGE_NT_HEADERS32 m_pNTHeader;	//NTͷ
	
public:
	static DWORD RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt);	//��̬�����ⲿ����
};
