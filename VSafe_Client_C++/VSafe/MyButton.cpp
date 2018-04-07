// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_Style = 0;							//��ť��״���
	b_InRect = false;						//�������־
	m_strText = _T("");						//��ť���֣�ʹ��Ĭ�����֣�
	m_TextColor = RGB(0, 0, 0);             //������ɫ����ɫ��
	m_BackColor = RGB(243, 243, 243);       //����ɫ���Ұ�ɫ��
	m_LockColor = GetSysColor(COLOR_GRAYTEXT);     //������ť��������ɫ
	m_pFont = NULL;								   //����ָ��
}
CMyButton::~CMyButton()
{
	if (m_pFont)     delete m_pFont;			   //ɾ������
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyButton ��Ϣ�������




void CMyButton::DrawButton(CDC *pDC)
{
	//�ָ�״̬
	if (m_Style == 3) 
		m_Style = 0;
	//����״̬�����߿���ɫ��������ɫ
	COLORREF bColor, fColor;     
	//bColorΪ�߿���ɫ��fColorΪ������ɫ
	switch (m_Style)
	{
	case 0: bColor = m_BackColor;		 fColor = m_TextColor; break;   //������ť
	case 1: bColor = m_MouseColor;		 fColor = m_TextColor; break;   //������ʱ��ť
	case 2: bColor = RGB(204, 204, 204); fColor = m_TextColor; break;   //���µİ�ť
	case 3: bColor = m_BackColor;		 fColor = m_TextColor; break;	//�����İ�ť
	}
	//���ư�ť����
	CBrush Brush;
	Brush.CreateSolidBrush(bColor);     //����ˢ
	pDC->SelectObject(&Brush);

	CPen Pen;
	Pen.CreatePen(PS_NULL, 0, bColor);
	pDC->SelectObject(&Pen);
	pDC->RoundRect(&m_BtRect, CPoint(0,0));    //��Բ�Ǿ���												
	
	if (GetFocus() == this)
		fColor = m_LockColor;

	//���ư�ť����
	pDC->SetTextColor(fColor);         //������
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_strText, &m_BtRect, 
		DT_SINGLELINE | DT_CENTER  | DT_VCENTER | DT_END_ELLIPSIS);


	/*//����ӵ�н��㰴ť�����߿�
	if (GetFocus() == this)
	{
		CRect Rect;
		Rect.SetRect(m_BtRect.left + 2, m_BtRect.top + 2, m_BtRect.right - 2, m_BtRect.bottom - 2);
		pDC->DrawFocusRect(&Rect);     //��ӵ�н�������߿�
	}*/
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	m_BtRect = lpDrawItemStruct->rcItem;     //��ȡ��ť�ߴ�

	if (m_strText.IsEmpty())
		GetWindowText(m_strText);           //��ȡ��ť�ı�

	int nSavedDC = pDC->SaveDC();
	VERIFY(pDC);
	
	DrawButton(pDC);    
	//���ư�ť

	pDC->RestoreDC(nSavedDC);
}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (!b_InRect || GetCapture() != this)     //�����밴ť
	{
		b_InRect = true;     //���ý����־
		SetCapture();        //�������
		m_Style = 1;         //���ð�ť״̬
		Invalidate();        //�ػ水ť
	}
	else
	{
		if (!m_BtRect.PtInRect(point))     //����뿪��ť
		{
			b_InRect = false;    //��������־
			ReleaseCapture();    //�ͷŲ�������
			m_Style = 0;         //���ð�ť״̬
			Invalidate();        //�ػ水ť
		}
	}

	CButton::OnMouseMove(nFlags, point);
}


void CMyButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnMouseLeave();
}


void CMyButton::SetText(CString str)
{
	m_strText = _T("");
	SetWindowText(str);
}

void CMyButton::SetTextColor(COLORREF color)
{
	m_TextColor = color;
	Invalidate();
}

void CMyButton::SetBackColor(COLORREF color)
{
	m_BackColor = color;
	Invalidate();
}

void CMyButton::SetLockColor(COLORREF color)
{
	m_LockColor = color;
	Invalidate();
}

void CMyButton::SetMouseColor(COLORREF color)
{
	m_MouseColor = color;
	Invalidate();
}

void CMyButton::SetTextFont(int FontHight, LPCTSTR FontName)
{
	if (m_pFont)     delete m_pFont;     //ɾ��������
	m_pFont = new CFont;
	m_pFont->CreatePointFont(FontHight, FontName);     //����������
	SetFont(m_pFont);                 //��������
}

void CMyButton::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	ModifyStyle(0, BS_OWNERDRAW);         //���ð�ť����Ϊ�Ի�
	CButton::PreSubclassWindow();
}


void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Style = 2;
	Invalidate();         //�ػ水ť

	CButton::OnLButtonDown(nFlags, point);
}


void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_Style = 1;
	Invalidate();         //�ػ水ť

	CButton::OnLButtonUp(nFlags, point);
}
