// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_Style = 0;							//按钮形状风格
	b_InRect = false;						//鼠标进入标志
	m_strText = _T("");						//按钮文字（使用默认文字）
	m_TextColor = RGB(0, 0, 0);             //文字颜色（黑色）
	m_BackColor = RGB(243, 243, 243);       //背景色（灰白色）
	m_LockColor = GetSysColor(COLOR_GRAYTEXT);     //锁定按钮的文字颜色
	m_pFont = NULL;								   //字体指针
}
CMyButton::~CMyButton()
{
	if (m_pFont)     delete m_pFont;			   //删除字体
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyButton 消息处理程序




void CMyButton::DrawButton(CDC *pDC)
{
	//恢复状态
	if (m_Style == 3) 
		m_Style = 0;
	//根据状态调整边框颜色和文字颜色
	COLORREF bColor, fColor;     
	//bColor为边框颜色，fColor为文字颜色
	switch (m_Style)
	{
	case 0: bColor = m_BackColor;		 fColor = m_TextColor; break;   //正常按钮
	case 1: bColor = m_MouseColor;		 fColor = m_TextColor; break;   //鼠标进入时按钮
	case 2: bColor = RGB(204, 204, 204); fColor = m_TextColor; break;   //按下的按钮
	case 3: bColor = m_BackColor;		 fColor = m_TextColor; break;	//锁定的按钮
	}
	//绘制按钮背景
	CBrush Brush;
	Brush.CreateSolidBrush(bColor);     //背景刷
	pDC->SelectObject(&Brush);

	CPen Pen;
	Pen.CreatePen(PS_NULL, 0, bColor);
	pDC->SelectObject(&Pen);
	pDC->RoundRect(&m_BtRect, CPoint(0,0));    //画圆角矩形												
	
	if (GetFocus() == this)
		fColor = m_LockColor;

	//绘制按钮文字
	pDC->SetTextColor(fColor);         //画文字
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_strText, &m_BtRect, 
		DT_SINGLELINE | DT_CENTER  | DT_VCENTER | DT_END_ELLIPSIS);


	/*//绘制拥有焦点按钮的虚线框
	if (GetFocus() == this)
	{
		CRect Rect;
		Rect.SetRect(m_BtRect.left + 2, m_BtRect.top + 2, m_BtRect.right - 2, m_BtRect.bottom - 2);
		pDC->DrawFocusRect(&Rect);     //画拥有焦点的虚线框
	}*/
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	m_BtRect = lpDrawItemStruct->rcItem;     //获取按钮尺寸

	if (m_strText.IsEmpty())
		GetWindowText(m_strText);           //获取按钮文本

	int nSavedDC = pDC->SaveDC();
	VERIFY(pDC);
	
	DrawButton(pDC);    
	//绘制按钮

	pDC->RestoreDC(nSavedDC);
}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (!b_InRect || GetCapture() != this)     //鼠标进入按钮
	{
		b_InRect = true;     //设置进入标志
		SetCapture();        //捕获鼠标
		m_Style = 1;         //设置按钮状态
		Invalidate();        //重绘按钮
	}
	else
	{
		if (!m_BtRect.PtInRect(point))     //鼠标离开按钮
		{
			b_InRect = false;    //清除进入标志
			ReleaseCapture();    //释放捕获的鼠标
			m_Style = 0;         //设置按钮状态
			Invalidate();        //重绘按钮
		}
	}

	CButton::OnMouseMove(nFlags, point);
}


void CMyButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	if (m_pFont)     delete m_pFont;     //删除旧字体
	m_pFont = new CFont;
	m_pFont->CreatePointFont(FontHight, FontName);     //创建新字体
	SetFont(m_pFont);                 //设置字体
}

void CMyButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0, BS_OWNERDRAW);         //设置按钮属性为自绘
	CButton::PreSubclassWindow();
}


void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_Style = 2;
	Invalidate();         //重绘按钮

	CButton::OnLButtonDown(nFlags, point);
}


void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_Style = 1;
	Invalidate();         //重绘按钮

	CButton::OnLButtonUp(nFlags, point);
}
