#pragma once


// CMyTab
//�Զ�����չTAB;

class CMyTab : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTab)

public:
	CMyTab();
	virtual ~CMyTab();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);		
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);	//ѡ��л�;
	void ButtonSelchange(DWORD dwSel);									//��ť�л�;
	
	void MyInserItem(DWORD dwCount, ...);							//����ѡ���ǩ;	
	void MyInsertChild(DWORD dwCount, ...);							//����ӶԻ���;	
	DWORD m_dwCount;												//�����ӶԻ�����Ϣ;
	CDialogEx* m_pWnd[10];											//�Ӵ�������;
};


