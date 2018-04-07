#pragma once
#include "MyList.h"

// CEnumWindow �Ի���

typedef struct _MYWINDOWINFO
{
	TCHAR hWnd[MAX_PATH+1];
	TCHAR WindowName[MAX_PATH+1];
	TCHAR ClassName[MAX_PATH+1];
}MYWINDOWINFO, *PMYWINDOWINFO;


class CEnumWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CEnumWindow)

public:
	CEnumWindow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnumWindow();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_WINDOW};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnRclickWindowList1(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ��˵�;
	afx_msg void OnPopMenu(UINT id);										//��Ӧ�Ҽ��˵�;
	DECLARE_MESSAGE_MAP()
private:
	CMyList m_WindowList;
	void EnumWindow();			//��Ӵ���;
public:
	static BOOL CALLBACK EnumWindowProc(HWND hWnd, LPARAM lParam);			//ö�ٴ��ڻص�����;

};
