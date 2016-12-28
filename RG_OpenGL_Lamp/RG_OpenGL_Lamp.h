
// RG_OpenGL_Lamp.h : main header file for the RG_OpenGL_Lamp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRG_OpenGL_LampApp:
// See RG_OpenGL_Lamp.cpp for the implementation of this class
//

class CRG_OpenGL_LampApp : public CWinApp
{
public:
	CRG_OpenGL_LampApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRG_OpenGL_LampApp theApp;
