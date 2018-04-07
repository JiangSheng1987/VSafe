// MyTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTab.h"


// CMyTab

IMPLEMENT_DYNAMIC(CMyTab, CTabCtrl)

CMyTab::CMyTab()
{

}

CMyTab::~CMyTab()
{
}


BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTab::OnNMClick)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTab::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTab ��Ϣ�������




void CMyTab::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CMyTab::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CTabCtrl::PreSubclassWindow();
}


//****************************************************************
// Brief 	: ѡ��л�;
// Method	: OnTcnSelchange
// FullName	: CMyTab::OnTcnSelchange
// Access	: public 
// Returns	: void
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//****************************************************************

void CMyTab::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//������ǰѡ�ѡ����;
	DWORD dwSel = GetCurSel();
	//��������;
	for (size_t i=0;i<m_dwCount;i++)
	{
		m_pWnd[i]->ShowWindow(SW_HIDE);
	}
	//�������;
	if (dwSel >=m_dwCount)
	{
		return;
	}

	//�ƶ����ں�TAB�ͻ���һ����;
	CRect rt;
	GetClientRect(&rt);
	rt.DeflateRect(0, 0, 0, 0);		//TOPֵ��С;
	m_pWnd[dwSel]->MoveWindow(&rt, 1);
	m_pWnd[dwSel]->ShowWindow(SW_SHOW);
}

//****************************************************************
// Brief 	: ������ť�л�
// Method	: OnTcnSelchange
// FullName	: CMyTab::OnTcnSelchange
// Access	: public 
// Returns	: void
// Parameter: int nSel
//****************************************************************

void CMyTab::ButtonSelchange(DWORD  dwSel)
{
	//��������;
	for (size_t i = 0; i < m_dwCount; i++)
	{
		m_pWnd[i]->ShowWindow(SW_HIDE);
	}
	//�������;
	if (dwSel >= m_dwCount)
	{
		return;
	}

	//�ƶ����ں�TAB�ͻ���һ����;
	CRect rt;
	GetClientRect(&rt);
	rt.DeflateRect(0, 0, 0, 0);		//TOPֵ��С;
	m_pWnd[dwSel]->MoveWindow(&rt, 1);
	m_pWnd[dwSel]->ShowWindow(SW_SHOW);
}

//****************************************************************
// Brief 	: ���ѡ�;
// Method	: InserItem
// FullName	: CMyTab::InserItem
// Access	: public 
// Returns	: void
// Parameter: DWORD dwCount
// Parameter: ...ѡ���,ѡ���,...
//****************************************************************

void CMyTab::MyInserItem(DWORD dwCount, ...)
{
	//������;
	va_list va;
	va_start(va, dwCount);
	for (DWORD i=0;i<dwCount;i++)
	{
		TCHAR *p = va_arg(va, TCHAR*);
		InsertItem(i, p);
	}
	va_end(va);
}

//****************************************************************
// Brief 	: �����Ӵ���;
// Method	: MyInsertChild
// FullName	: CMyTab::MyInsertChild
// Access	: public 
// Returns	: void
// Parameter: DWORD dwCount
// Parameter: ...������,Dialog�ؼ�,������,Dialog�ؼ�...
//****************************************************************

void CMyTab::MyInsertChild(DWORD dwCount, ...)
{
	m_dwCount = dwCount;
	va_list va;
	va_start(va, dwCount);
	for (DWORD i=0;i<dwCount;i++)
	{
		m_pWnd[i] = va_arg(va, CDialogEx*);
		UINT uID = va_arg(va, UINT);
		m_pWnd[i]->Create(uID, this);
	}
	va_end(va);

	//�ƶ����ں�TAB�ͻ���һ����;
	CRect rt;
	GetClientRect(&rt);
	rt.DeflateRect(0, 0, 0, 0);
	m_pWnd[0]->MoveWindow(&rt, 1);
	m_pWnd[0]->ShowWindow(SW_SHOW);
}
