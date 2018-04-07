#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP()

private:
	int m_Style;		
	bool b_InRect;
	CString m_strText;

	COLORREF m_TextColor;
	COLORREF m_BackColor;

	COLORREF m_LockColor;	
	COLORREF m_MouseColor;

	CRect    m_BtRect;
	CFont*	 m_pFont;

	void DrawButton(CDC *pDC);

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:

	void SetText(CString str);
	void SetTextColor(COLORREF color);
	void SetBackColor(COLORREF color);
	void SetLockColor(COLORREF color);
	void SetMouseColor(COLORREF color);
	void SetTextFont(int FontHight, LPCTSTR FontName);

};


