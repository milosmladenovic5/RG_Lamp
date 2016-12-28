
// RG_OpenGL_LampView.h : interface of the CRG_OpenGL_LampView class
//

#pragma once
#include "GLRenderer.h"

class CRG_OpenGL_LampView : public CView
{
protected: // create from serialization only
	CRG_OpenGL_LampView();
	DECLARE_DYNCREATE(CRG_OpenGL_LampView)

// Attributes
public:
	CRG_OpenGL_LampDoc* GetDocument() const;

protected:
	CGLRenderer m_glRenderer;

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
	virtual ~CRG_OpenGL_LampView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in RG_OpenGL_LampView.cpp
inline CRG_OpenGL_LampDoc* CRG_OpenGL_LampView::GetDocument() const
   { return reinterpret_cast<CRG_OpenGL_LampDoc*>(m_pDocument); }
#endif

