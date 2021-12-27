// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PlanetaryMotionView.cpp : implementation of the CPlanetaryMotionView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetaryMotion.h"
#endif

#include "PlanetaryMotionDoc.h"
#include "PlanetaryMotionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetaryMotionView

IMPLEMENT_DYNCREATE(CPlanetaryMotionView, CView)

BEGIN_MESSAGE_MAP(CPlanetaryMotionView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetaryMotionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPlanetaryMotionView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_STOP, &CPlanetaryMotionView::OnButtonStop)
	ON_COMMAND(ID_BUTTON_RESUME, &CPlanetaryMotionView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetaryMotionView construction/destruction

CPlanetaryMotionView::CPlanetaryMotionView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	x = 400;
	y = 200;
	x1 = 300 + 150 * cos(3);
	y1 = 200 + 150 * sin(3);
}

CPlanetaryMotionView::~CPlanetaryMotionView()
{
}

BOOL CPlanetaryMotionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetaryMotionView drawing

void CPlanetaryMotionView::OnDraw(CDC* pDC)
{
	CPlanetaryMotionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&redPen);
	pDC->Ellipse(450, 350, 150, 50);
	pDC->SelectObject(pOldPen);
	CPen bluePen;
	bluePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	CPen* pnewPen = pDC->SelectObject(&bluePen);
	pDC->Ellipse(400, 300, 200, 100);
	pDC->SelectObject(pnewPen);
	pDC->Ellipse(330, 230, 270, 170);
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	
	

	

	// TODO: add draw code for native data here
}


// CPlanetaryMotionView printing


void CPlanetaryMotionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetaryMotionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetaryMotionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetaryMotionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetaryMotionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetaryMotionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetaryMotionView diagnostics

#ifdef _DEBUG
void CPlanetaryMotionView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetaryMotionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetaryMotionDoc* CPlanetaryMotionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetaryMotionDoc)));
	return (CPlanetaryMotionDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetaryMotionView message handlers


void CPlanetaryMotionView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread = AfxBeginThread(CPlanetaryMotionView::StartThread,this);
	
}


void CPlanetaryMotionView::OnButtonStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();

}


void CPlanetaryMotionView::OnButtonResume()
{
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetaryMotionView::StartThread(LPVOID Param)
{
	CPlanetaryMotionView* pView= (CPlanetaryMotionView*)Param;
	int j = 0;
	while (1)
	{
		j = j + 6;
		pView->x = 300 + 100 * cos(j);
		pView->y = 200 + 100 * sin(j);
		pView->x1 = 300 + 150 * cos(j + 3);
		pView->y1 = 200 + 150 * sin(j + 3);
		pView->Invalidate();
		Sleep(500);
	}
	return 0;
}
