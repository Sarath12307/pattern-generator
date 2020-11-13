
// CounterThreadingView.cpp : implementation of the CCounterThreadingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CounterThreading.h"
#endif

#include "CounterThreadingDoc.h"
#include "CounterThreadingView.h"
#include "TestThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCounterThreadingView

IMPLEMENT_DYNCREATE(CCounterThreadingView, CView)

BEGIN_MESSAGE_MAP(CCounterThreadingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_START, &CCounterThreadingView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CCounterThreadingView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CCounterThreadingView::OnThreadResume)
END_MESSAGE_MAP()

// CCounterThreadingView construction/destruction

CCounterThreadingView::CCounterThreadingView()
	
{
	
	m_iCounter = 0;

	//rectangle initial coordinate
	rx1 = 127;
	ry1 = 127;
	rx2 = 700;
	ry2 = 445;

	//circle coordinate
	cx1 = 127;
	cy1 = 127;
	cy2 = 255;
	cx2 = 255;
	

	

}

CCounterThreadingView::~CCounterThreadingView()
{
}

BOOL CCounterThreadingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCounterThreadingView drawing

void CCounterThreadingView::OnDraw(CDC* pDC)
{
	CCounterThreadingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//m_iCounter++;
	CString strCounter;
	//strCounter.Format(L"The Counter is %d", m_iCounter);
	//pDC->TextOut(100, 100, strCounter);

	
	
	//creating rectangle
	
	
	
	CPen redpen;
	redpen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* pOldpen = pDC->SelectObject(&redpen);
	
	CPoint pt(rx1, ry1);
	CSize  sz(rx2, ry2);
	CRect myrect(pt, sz);
	pDC->Rectangle(myrect);
	pDC->SelectObject(pOldpen);
	
	do

	{
		//circle generation

		CBrush brushred(RGB(0, 0, 0));
		CBrush *pOldbrush = pDC->SelectObject(&brushred);

		pDC->Ellipse(cx1, cy1, cx2, cy2);

		pDC->SelectObject(pOldbrush);

		//case 1

		if (cx1 >= rx2)
		{
			a = -2;



		}
		//case 2
		if (cx1 <= rx1)
		{
			a = 2;


		}
		//case 3
		if (cy1 >= ry2)
		{
			b = -2;



		}
	//case 4
		if (cy1 <= ry1)
		{

			b = 2;

		}
		//changinig the coordinate valuse of circle
        cx1 = cx1 + a;
		cy1 = cy1 + b;
		cx2 = cx2 + a;
		cy2 = cy2 + b;
		
	} while (0);

}


// CCounterThreadingView printing

BOOL CCounterThreadingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCounterThreadingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCounterThreadingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCounterThreadingView diagnostics

#ifdef _DEBUG
void CCounterThreadingView::AssertValid() const
{
	CView::AssertValid();
}

void CCounterThreadingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCounterThreadingDoc* CCounterThreadingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCounterThreadingDoc)));
	return (CCounterThreadingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCounterThreadingView message handlers


void CCounterThreadingView::OnThreadStart()
{
	pThread = AfxBeginThread(CTestThread::RunThreadFunction, this);
}


void CCounterThreadingView::OnThreadPause()
{
	pThread -> SuspendThread();
}


void CCounterThreadingView::OnThreadResume()
{
	pThread->ResumeThread();
}
