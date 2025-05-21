
// HexedMFCView.cpp : implementation of the CHexedMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HexedMFC.h"
#endif

#include "HexedMFCDoc.h"
#include "HexedMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHexedMFCView

IMPLEMENT_DYNCREATE(CHexedMFCView, CView)

BEGIN_MESSAGE_MAP(CHexedMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHexedMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHexedMFCView construction/destruction

CHexedMFCView::CHexedMFCView() noexcept
{
	// TODO: add construction code here

}

CHexedMFCView::~CHexedMFCView()
{
}

BOOL CHexedMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHexedMFCView drawing

void CHexedMFCView::OnDraw(CDC* /*pDC*/)
{
	CHexedMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHexedMFCView printing


void CHexedMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHexedMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHexedMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHexedMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHexedMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHexedMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHexedMFCView diagnostics

#ifdef _DEBUG
void CHexedMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CHexedMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHexedMFCDoc* CHexedMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexedMFCDoc)));
	return (CHexedMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CHexedMFCView message handlers
