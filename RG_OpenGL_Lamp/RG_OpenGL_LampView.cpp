
// RG_OpenGL_LampView.cpp : implementation of the CRG_OpenGL_LampView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG_OpenGL_Lamp.h"
#endif

#include "RG_OpenGL_LampDoc.h"
#include "RG_OpenGL_LampView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRG_OpenGL_LampView

IMPLEMENT_DYNCREATE(CRG_OpenGL_LampView, CView)

BEGIN_MESSAGE_MAP(CRG_OpenGL_LampView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRG_OpenGL_LampView construction/destruction

CRG_OpenGL_LampView::CRG_OpenGL_LampView()
{
	// TODO: add construction code here

}

CRG_OpenGL_LampView::~CRG_OpenGL_LampView()
{
}

BOOL CRG_OpenGL_LampView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRG_OpenGL_LampView drawing

void CRG_OpenGL_LampView::OnDraw(CDC* pDC)
{
	CRG_OpenGL_LampDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	this->m_glRenderer.DrawScene(pDC);
}


// CRG_OpenGL_LampView printing

BOOL CRG_OpenGL_LampView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRG_OpenGL_LampView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRG_OpenGL_LampView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRG_OpenGL_LampView diagnostics

#ifdef _DEBUG
void CRG_OpenGL_LampView::AssertValid() const
{
	CView::AssertValid();
}

void CRG_OpenGL_LampView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRG_OpenGL_LampDoc* CRG_OpenGL_LampView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRG_OpenGL_LampDoc)));
	return (CRG_OpenGL_LampDoc*)m_pDocument;
}
#endif //_DEBUG


// CRG_OpenGL_LampView message handlers


int CRG_OpenGL_LampView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	this->m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CRG_OpenGL_LampView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	this->m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void CRG_OpenGL_LampView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	this->m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


BOOL CRG_OpenGL_LampView::OnEraseBkgnd(CDC* pDC)
{
	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CRG_OpenGL_LampView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	this->m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void CRG_OpenGL_LampView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'S' :
		this->m_glRenderer.IncLampBottomZAngle();
		break;
	case 'A':
		this->m_glRenderer.DecLampBottomZAngle();
		break;
	case 'X':
		this->m_glRenderer.IncLampBottomXAngle();
		break;
	case 'Z':
		this->m_glRenderer.DecLampBottomXAngle();
		break;
	case 'F':
		this->m_glRenderer.IncLampMiddleZAngle();
		break;
	case 'D':
		this->m_glRenderer.DecLampMiddleZAngle();
		break;
	case 'V':
		this->m_glRenderer.IncLampMiddleXAngle();
		break;
	case 'C':
		this->m_glRenderer.DecLampMiddleXAngle();
		break;
	case 'H':
		this->m_glRenderer.IncLampTopZAngle();
		break;
	case 'G':
		this->m_glRenderer.DecLampTopZAngle();
		break;
	case 'N':
		this->m_glRenderer.IncLampTopXAngle();
		break;
	case 'B':
		this->m_glRenderer.DecLampTopXAngle();
		break;
	default:
		break;
	}

	Invalidate();


	CView::OnKeyDown(nChar, nRepCnt, nFlags);

}
