
// HexedMFCView.h : interface of the CHexedMFCView class
//

#pragma once
#include "CPieceListGridCtrl.h"


class CHexedMFCView : public CView
{
protected: // create from serialization only
	CHexedMFCView() noexcept;
	DECLARE_DYNCREATE(CHexedMFCView)

// Attributes
public:
	CHexedMFCDoc* GetDocument() const;
	CPieceListGridCtrl m_gridCntl;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHexedMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnSelectBlockCount();
	afx_msg void OnSelectBlockCount1();
	afx_msg void OnSelectBlockCount2();
	afx_msg void OnSelectBlockCount3();
	afx_msg void OnSelectBlockCount4();
	afx_msg void OnSelectBlockCount5();
	afx_msg void OnSelectBlockCount6();
	afx_msg void OnSelectBlockCount7();
	afx_msg void OnSelectBlockCount8();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HexedMFCView.cpp
inline CHexedMFCDoc* CHexedMFCView::GetDocument() const
   { return reinterpret_cast<CHexedMFCDoc*>(m_pDocument); }
#endif

