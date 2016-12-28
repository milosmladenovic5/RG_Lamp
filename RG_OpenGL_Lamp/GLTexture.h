#pragma once
#include "DImage.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
//#pragma comment(lib, "glaux.lib")


class CGLTexture
{
	GLuint m_ID;

public:
	CGLTexture();
	~CGLTexture();
	void LoadFromFile(CString str);
	void Select();
	void Release();
	static void PrepareTexturing(bool bEnableLighting);
};