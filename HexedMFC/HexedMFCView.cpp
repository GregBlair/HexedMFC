
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

//#include "CMFCToolBarComboBoxButton"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_GRIDCTRL 1

// CHexedMFCView

IMPLEMENT_DYNCREATE(CHexedMFCView, CView)

BEGIN_MESSAGE_MAP(CHexedMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_BUTTON_SELECT_COUNT, &CHexedMFCView::OnSelectBlockCount)
	ON_COMMAND(ID_PIECECOUNT_1, &CHexedMFCView::OnSelectBlockCount)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHexedMFCView::OnFilePrintPreview)
	ON_COMMAND(ID_PIECECOUNT_1, &CHexedMFCView::OnSelectBlockCount1)
	ON_COMMAND(ID_PIECECOUNT_2, &CHexedMFCView::OnSelectBlockCount2)
	ON_COMMAND(ID_PIECECOUNT_3, &CHexedMFCView::OnSelectBlockCount3)
	ON_COMMAND(ID_PIECECOUNT_4, &CHexedMFCView::OnSelectBlockCount4)
	ON_COMMAND(ID_PIECECOUNT_5, &CHexedMFCView::OnSelectBlockCount5)
	ON_COMMAND(ID_PIECECOUNT_6, &CHexedMFCView::OnSelectBlockCount6)
	ON_COMMAND(ID_PIECECOUNT_7, &CHexedMFCView::OnSelectBlockCount7)
	ON_COMMAND(ID_PIECECOUNT_8, &CHexedMFCView::OnSelectBlockCount8)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CHexedMFCView construction/destruction

CHexedMFCView::CHexedMFCView() noexcept
{
	// construct the Grid object           
	// Create the Windows control and attach it to the Grid object
	//m_wndGrid.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rectGrid, this, IDC_GRDID);
	// Insert columns:
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

void CHexedMFCView::OnSelectBlockCount()
{
	GetDocument()->SetBlockCount(5);
}

void CHexedMFCView::OnSelectBlockCount1()
{
	GetDocument()->SetBlockCount(1);
}

void CHexedMFCView::OnSelectBlockCount2()
{
	GetDocument()->SetBlockCount(2);
}

void CHexedMFCView::OnSelectBlockCount3()
{
	GetDocument()->SetBlockCount(3);
}

void CHexedMFCView::OnSelectBlockCount4()
{
	GetDocument()->SetBlockCount(4);
}

void CHexedMFCView::OnSelectBlockCount5()
{
	GetDocument()->SetBlockCount(5);
}

void CHexedMFCView::OnSelectBlockCount6()
{
	GetDocument()->SetBlockCount(6);
}

void CHexedMFCView::OnSelectBlockCount7()
{
	GetDocument()->SetBlockCount(7);
}

void CHexedMFCView::OnSelectBlockCount8()
{
	GetDocument()->SetBlockCount(8);
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
