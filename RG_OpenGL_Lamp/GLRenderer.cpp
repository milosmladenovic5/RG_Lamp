#include "stdafx.h"
#include "GLRenderer.h"

#define _USE_MATH_DEFINES
#include <math.h>

//#pragma comment(lib, "GL\\glut32.lib")

CGLRenderer::CGLRenderer()
{
	this->vert = nullptr;
	this->col = nullptr;
	this->ind = nullptr;

	this->lampBottomZAngle = 40.0;
	this->lampBottomXAngle = 0.0;

	this->lampMiddleZAngle = -80.0;
	this->lampMiddleXAngle = -20.0;

	this->lampTopZAngle = -30.0;
	this->lampTopXAngle = 20.0;
	this->nSteps = 8;

	
}

CGLRenderer::~CGLRenderer()
{
	if (this->vert != nullptr)
		delete this->vert;

	if (this->col != nullptr)
		delete this->col;

	if (this->ind != nullptr)
		delete this->ind;

}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	this->m_hrc = wglCreateContext(pDC->m_hDC);

	if (!this->m_hrc) return false;


	return true;
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	//---------------------------------
	glClearColor(1.0, 1.0, 1.0, 0);
	glEnable(GL_DEPTH_TEST);
	SetLightModel();
	CGLTexture::PrepareTexturing(true);

	this->wall.LoadFromFile(CString("wall.bmp"));
	this->wood.LoadFromFile(CString("wood.bmp"));
	this->floor.LoadFromFile(CString("floor.bmp"));
	this->lig.LoadFromFile(CString("Lightning.bmp"));

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// ... 
	wglMakeCurrent(NULL, NULL);
	if (this->m_hrc)
	{
		wglDeleteContext(this->m_hrc);
		this->m_hrc = NULL;
	}

	this->wood.Release();
	this->wall.Release();
	this->floor.Release();
}



void CGLRenderer::DrawScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	//---------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// glLoadIdentity — replace the current matrix with the identity matrix
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(10.0, 5.0, 1.0, -5.0, 0.0, 5.0, 0.0, 1.0, 0.0);
	//gluLookAt(10.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	

	//glDisable(GL_LIGHT0);

    DrawTable(5.1, 0.15, 3.2);
	DrawWalls(25.0);
	DrawLamp();
	//DrawAxes(10.0);
	DrawCylindricalObject(0.30, 2.0, 10);

	glFlush();

	
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);							// funkcija oslobadja DC koji je do tada koristio OpenGL rendering context
														// i nakon toga deselektuje tekuci rendering context
}

void CGLRenderer::PrepareVABox(double a, double b, double c)
{
	if (this->vert != nullptr)
		delete this->vert;

	if (this->ind != nullptr)
		delete this->ind;

	//this->~CGLRenderer();

	this->vert = new float[24];
	this->ind = new byte[24];
	

	// sa vert buferom samo definisem tacke a indeksi mi odredjuju nacin na koji se te tacke povezuju
	this->vert[0] = -a / 2; this->vert[1] = -b / 2; this->vert[2] = c / 2;			// vert0
	this->vert[3] = a / 2; this->vert[4] = -b / 2; this->vert[5] = c / 2;			// vert1
	this->vert[6] = a / 2; this->vert[7] = b / 2; this->vert[8] = c / 2;			// vert2
	this->vert[9] = -a / 2; this->vert[10] = b / 2; this->vert[11] = c / 2;			// vert3
	this->vert[12] = -a / 2; this->vert[13] = -b / 2; this->vert[14] = -c / 2;		// vert4
	this->vert[15] = a / 2; this->vert[16] = -b / 2; this->vert[17] = -c / 2;		// vert5
	this->vert[18] = a / 2; this->vert[19] = b / 2; this->vert[20] = -c / 2;		// vert6
	this->vert[21] = -a / 2; this->vert[22] = b / 2; this->vert[23] = c / 2;		// vert7



	this->ind[0] = 0; this->ind[1] = 1; this->ind[2] = 2; this->ind[3] = 3;			// quad1
	this->ind[4] = 1; this->ind[5] = 5; this->ind[6] = 6; this->ind[7] = 2;			// quad2
	this->ind[8] = 7; this->ind[9] = 6; this->ind[10] = 5; this->ind[11] = 4;       // quad3
	this->ind[12] = 0; this->ind[13] = 3; this->ind[14] = 7; this->ind[15] = 4;     // quad4
	this->ind[16] = 7; this->ind[17] = 3; this->ind[18] = 2; this->ind[19] = 6;     // quad5
	this->ind[20] = 0; this->ind[21] = 4; this->ind[22] = 5; this->ind[23] = 1;     // quad6
}

void CGLRenderer::PrepareVAWall(double a)
{
	if (this->vert != nullptr)
		delete this->vert;

	if (this->ind != nullptr)
		delete this->ind;


	this->vert = new float[12]; //12 za 3d
	this->ind = new byte[4];

	this->vert[0] = -a / 2; this->vert[1] = -a / 2; this->vert[2] = -a / 2;
	this->vert[3] = a / 2; this->vert[4] = -a / 2; this->vert[5] = -a / 2;			
	this->vert[6] = a / 2; this->vert[7] = a / 2; this->vert[8] = - a / 2;			
	this->vert[9] = -a / 2; this->vert[10] = a / 2; this->vert[11] = -a / 2;

	/*this->vert[0] = -a / 2; this->vert[1] = -a / 2;
	this->vert[2] = a / 2; this->vert[3] = -a / 2;
	this->vert[4] = a / 2; this->vert[5] = a / 2;
	this->vert[6] = -a / 2; this->vert[7] = a / 2;*/

	this->ind[0] = 0; this->ind[1] = 1; this->ind[2] = 2; this->ind[3] = 3;
}

void CGLRenderer::DrawBox(float c1, float c2, float c3)
{
	glShadeModel(GL_FLAT);
	glColor3f(c1, c2, c3);

	glVertexPointer(3, GL_FLOAT, 0, this->vert);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, this->ind);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void CGLRenderer::DrawTable(double a, double b, double c)
{
	//5.1, 0.17, 3.0
	//PrepareVABox(a, b, c);		//glavna ploca
	//glPushMatrix();
	//glRotatef(95.0, 0.0, 1.0, 0.0);
	//glRotatef(-12.0, 0.0, 0.0, 1.0);
	//glColor3f(1.000, 0.617, 0.478);
	//glPushMatrix();
	//glScalef(a, b, c);
	this->material.SetWoodMaterial();
	this->material.SelectFront();

	glEnable(GL_TEXTURE_2D);
	this->wood.Select();
	DrawBoxWithNormals(a, b, c, this->nSteps, true);
	glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
/*
	DrawBoxWithNormals(1.0, 1.0, 1.0, 10);
	DrawBoxWithNormals(1.000, 0.617, 0.478,10);*/
	//glPopMatrix();

	//PrepareVABox(0.9 * a, 4 * b, 0.9 * c);			// 90% od tableA, 4 * tableB, 90% od tableC
	glPushMatrix();										// sada ga samo spustamo dole po Y osi!
	glTranslatef(0, -2 * b, 0);
	glColor3f(0.804, 0.361, 0.361);
	DrawBoxWithNormals(0.9 * a, 4 * b, 0.9 * c, this->nSteps, false);
	//DrawBox(0.804, 0.361, 0.361);
	glPopMatrix();

	float legA = b;
	float legB = a * 0.7;
	float legC = b;

	//PrepareVABox(legA, legB, legC);						
	glPushMatrix();
	glTranslatef(-a / 2 - legA / 2, -b / 2 - legB / 1.9, -c / 2 - legC );
	//DrawBox(0.0, 0.89, 0.0);		
	glColor3f(0.0, 0.89, 0.0);							
	DrawBoxWithNormals(legA, legB, legC, this->nSteps, false);			// gornja levo

	glTranslatef(0, 0, c - legC);
	//DrawBox(0.0, 0.89, 0.0);					
	DrawBoxWithNormals(legA, legB, legC, this->nSteps, false);			// donja levo

	glTranslatef(a - legA , 0, 0);
	DrawBoxWithNormals(legA, legB, legC, this->nSteps, false);			// donja desno

	glTranslatef(0, 0, -c + legC * 2);
	DrawBoxWithNormals(legA, legB, legC, this->nSteps, false);			// gornja levo
	glPopMatrix();
}

void CGLRenderer::DrawWall(float c1, float c2, float c3)
{
	glShadeModel(GL_FLAT);
	glColor3f(c1, c2, c3);

	glVertexPointer(3, GL_FLOAT, 0, this->vert);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, this->ind);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRenderer::DrawWalls(double size)
{
	this->material.SetWallMaterial();
	this->material.SelectFront();

	//PrepareVAWall(size);
	glPushMatrix();
	glTranslatef(0.0, -size / 5 , -size / 2);
	//DrawWall(0.827, 0.827, 0.827);		// DESNI
	//glColor3f(0.827, 0.827, 0.827);
	glEnable(GL_TEXTURE_2D);
	this->wall.Select();
	DrawSideWithTexture(size, size, this->nSteps);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	
	glPushMatrix();
	//this->material.SetWallMaterial();
	this->material.SelectBack();

	glTranslatef(-size / 2.0, -size / 5.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	//DrawWall(0.753, 0.753, 0.753);	
	
	//glColor3f(0.753, 0.753, 0.753);
	glEnable(GL_TEXTURE_2D);
	this->wall.Select();
	DrawSideWithTexture(size, size, this->nSteps);				// LEVI
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -size / 5, 0.0);

	glRotatef(-90.0, 1.0, 0.0, 0.0);
	//DrawWall(0.502, 0.502, 0.502);	
	//glColor3f(0.502, 0.502, 0.502);

	this->material.SetFloorMaterial();
	this->material.SelectFront();
	glEnable(GL_TEXTURE_2D);
	this->floor.Select();
	DrawSideWithTexture(size, size, this->nSteps);				// POD
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawLamp()
{
	//glColor3f(0.68, 0.0, 0.0);
	this->material.SetRedMetal();
	this->material.SelectFront();

	GLUquadric* quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(-1.0, -0.05, 0.0);												// opciono
	gluSphere(quadric, 0.40, 32.0, 32.0);

	
	double lampBodyX = 0.10;
	double lampBodyY = 2.4;
	double lampBodyZ = 0.10;

	//PrepareVABox((GLfloat)lampBodyX, (GLfloat)lampBodyY, (GLfloat)lampBodyZ);
	glRotatef(this->lampBottomZAngle, 0.0, 0.0, 1.0);
	glRotatef(this->lampBottomXAngle, 1.0, 0.0, 0.0);
	glTranslatef(0.0, (GLfloat)(lampBodyY / 2.0) + 0.3, 0.0);					// 0.3 - korekcija za malo vise od poluprecnika sfere
	//DrawBox(0.68, 0.0, 0.0);
	//glColor3f(0.68, 0.0, 0.0);
	DrawBoxWithNormals(lampBodyX, lampBodyY, lampBodyZ, this->nSteps, false);

	//glColor3f(0.0, 0.0, 0.70);
	glTranslatef(0.0, (GLfloat)(lampBodyY / 2.0), 0.0);							// lampBodyY / 2.0 - ZATO STO SAM POCETNI STAP VEC TRANSLIRAO ZA POLA (POLA MU JE BILO ISPOD)
	gluSphere(quadric, 0.13, 32.0, 32.0);
	
	double lampUpperBodyY = lampBodyY / 1.92;

	//PrepareVABox((GLfloat)lampBodyX, (GLfloat)lampUpperBodyY, (GLfloat)lampBodyZ);
	glRotatef(this->lampMiddleZAngle, 0.0, 0.0, 1.0); 
	glRotatef(this->lampMiddleXAngle, 1.0, 0.0, 0.0); 
	glTranslatef(0.0, (GLfloat)(lampUpperBodyY / 2.0), 0.0);					// lampUpperBodyY / 2.0 - IZ ISTOG RAZLOGA KAO GORE
	//DrawBox(0.68, 0.0, 0.0);
	//glColor3f(0.68, 0.0, 0.0);
	DrawBoxWithNormals(lampBodyX, lampUpperBodyY, lampBodyZ, this->nSteps, false);


	glRotatef(this->lampTopZAngle, 0.0, 0.0, 1.0);
	glRotatef(this->lampTopXAngle, 1.0, 0.0, 0.0);
	DrawLampHead(quadric);

	glPopMatrix();
}

void CGLRenderer::DrawLampHead(GLUquadric* quadric)
{

	//PrepareVABox(0.65, 0.3, 0.3);
	 
	//glPushMatrix();
	glTranslatef(0.0, 0.7, 0.00);
	//glColor3f(0.68, 0.0, 0.0);
	DrawBoxWithNormals(0.65, 0.3, 0.3, this->nSteps, false);
	//DrawBox(0.68, 0.0, 0.0);
	
	glTranslatef(0.25, 0.0, 0.0);
	this->material.SetBulbMaterial();
	this->material.SelectFront();
	gluSphere(quadric, 0.14, 32.0, 32.0);
	SetPositionLight();

	glTranslatef(0.34, 0.0, 0.0);
	this->material.SetRedMetal();
	this->material.SelectFront();
	glEnable(GL_CLIP_PLANE0);
	GLdouble* clip = new GLdouble[4];
	clip[0] =-1.0;
	clip[1] = 0.0;
	clip[2] = 0.0;
	clip[3] = 0.160;
	// parametri funckije glClipPlane su broj clip ravni i niz koeficijenata clipping ravni po
	// jednacini A*x + B*y + C*z + D = 0
	// A, B, C su koeficijenti vektora ravni po kojoj zelimo da odsecemo, a x,y i z koordinate tacke koja se nalazi na datoj ravni
	// uprosceno: 1. 2. i 3. tacka su koeficijenti vektora ravni, a 4. je udaljenost clipping ravni od 0 ,0 ,0 koordinate po koordinati
	// za koju odsecamo
	glClipPlane(GL_CLIP_PLANE0, clip);
	
	gluSphere(quadric, 0.405, 32.0, 32.0);
	glDisable(GL_CLIP_PLANE0);
	
	delete clip;
}

void CGLRenderer::DrawSide(double a, double b, int steps)
{
	double stepX = a / steps;
	double stepY = b / steps;
	glNormal3f(0.0, 0.0, 1.0);

	double y = b / 2;
	for (int i = 0; i < steps; i++)
	{
		glBegin(GL_QUAD_STRIP);
		double x = -a / 2;
		for (int j = 0; j <= steps; j++)
		{	
		
			glVertex2d(x, y);
			glVertex2d(x, y - stepY);
			x += stepX;
			
		}
		glEnd();
		y -= stepY;
	}	
}

void CGLRenderer::DrawBoxWithNormals(double a, double b, double c, int nSteps, bool bTexture)
{
	double angle = 90.0;
	int i;
	glPushMatrix();
	for (i = 0; i < 2; i++)
	{
		//ova for petlja ce da nacrta stranice kvadra koje su 'prednja' i zadnja u odnosu na posmatraca

		glPushMatrix();
		glTranslatef(0.0, 0.0, c / 2.0);
		if (bTexture) 
			DrawSideWithTexture(a, b, nSteps);
		else 
			DrawSide(a, b, nSteps);
		glPopMatrix();
		glRotatef(180.0, 0.0, 1.0, 0.0);

	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(angle, 0.0, 1.0, 0.0);
	for (i = 0; i < 2; i++)
	{
		//ova for petlja ce da nacrta stranice kvadra koje su 'desna' i 'leva' u odnosu na posmatraca

		glPushMatrix();
		glTranslatef(0.0, 0.0, a / 2.0);
		if (bTexture) 
			DrawSideWithTexture(c, b, nSteps);
		else 
			DrawSide(c, b, nSteps);
		glPopMatrix();
		glRotatef(180.0, 0.0, 1.0, 0.);	
	}
	glPopMatrix();
	glPushMatrix();
	for (i = 0; i < 2; i++)
	{
		//ova for petlja ce da nacrta stranice kvadra koje su 'gornja' i 'donja' u odnosu na posmatraca

		glRotatef(angle, 1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, 0.0, b / 2.0);
		if (bTexture)
			DrawSideWithTexture(a, c, nSteps);
		else 
			DrawSide(a, c, nSteps);
		glPopMatrix();
		angle = 180.0;

	}
	glPopMatrix();
	//glPopMatrix();

}

void CGLRenderer::SetLightModel()
{
	// OVAJ IZVOR SVETLOSTI JE FIKSAN, ZATO STO SE POSTAVLJA PRE SVIH MODELVIEW TRANSFORMACIJA (funkcija PrepareScene())
	float ambientGlobal[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientGlobal);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHTING);
 
	float light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float light0_position[] = {-23.0, 10.0, 5.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientGlobal);				// isto kao globalno pa da se ne ponavlja!
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	
	glEnable(GL_LIGHT0);
}

void CGLRenderer::SetPositionLight()
{
	float light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	float light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float light1_position[] = { 0.0, 0.0, 1.0, 1.0 };

	float light1_spotDirection[] = { 1.0, 0.0, 0.0 };

	// Boja i intenzitet svetlosti
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	// Posmatrac je u koordinatnom pocetku i gleda u pravcu orijentacije negativne Z-ose
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spotDirection);

	// slabljenje
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	// faktori slabljenja sa povecanjem rastojanja


	// Usmeravanje izvora
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	// Polovina ugla kupe koja definise prostor osvetljen usmerenim izvorom svetlosti
	// validne vrednosti su od 0.0 do 90.0 i 180.0 - difoltni - KORISTI SE ZA NEUSMERENI IZVOR (KUPA => SFERA)
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	// Brzine opadanja intenziteta svetlosti, - OD SREDISNJE OSE KA OMOTACU KUPE
	// kada je 0.0 nema slabljenja
	// za ugao alfa racuna se kao cos^GL_SPOT_EXPONTENT(alfa)


	// Aktiviranje
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHTING);
}

void CGLRenderer::DrawSideWithTexture(double a, double b, int steps)
{
	float stepX = a / steps;
	float stepY = b / steps;
	float x = -a / 2.0 + stepX / 2.0, y;
	glNormal3f(0.0, 0.0, 1.0);
	for (int i = 0; i < steps; i++, x += stepX)
	{
		y = -b / 2.0 + stepY / 2.0;
		for (int j = 0; j < steps; j++, y += stepY)
		{
			glPushMatrix();
			glTranslatef(x, y, 0.0);
			glBegin(GL_QUADS);

	
			glTexCoord2f(0.0, 0.0);
			glVertex2f(-stepX / 2.0, -stepY / 2.0);
			
			glTexCoord2f(1.0, 0.0);
			glVertex2f(stepX / 2.0, -stepY / 2.0);

			glTexCoord2f(1.0, 1.0);
			glVertex2f(stepX / 2.0, stepY / 2.0);


			glTexCoord2f(0.0, 1.0);
			glVertex2f(-stepX / 2.0, +stepY / 2.0);
			glEnd();
			glPopMatrix();			
		}
	}		
}

void CGLRenderer::DrawCylindricalObject(float r, float h, int steps)
{
	glPushMatrix();
	glTranslatef(2.2, 0.45, 0.0);
	float step = 2.0 * M_PI / (float)steps;
	float textureStep = 1.0 / (float)steps;
	this->material.SetWallMaterial();
	this->material.SelectFront();
	glEnable(GL_TEXTURE_2D);
	this->lig.Select();
	glBegin(GL_QUAD_STRIP);
	float x0 = 0.0f;
	float angle = 0.0;

	//glNormal3f((float)cos(step), (float)sin(step), 0.0);
	for (angle = 0; angle <= 2.0 * M_PI; angle += step, x0 += textureStep)
	{

		glNormal3f((float)cos(angle), (float)sin(angle), 0.0);
		glTexCoord2f(x0, 1.0);
		glVertex3f(r * (float)cos(angle), r * (float)sin(angle), h / 2);

		glTexCoord2f(x0, 0.0);
		glVertex3f(r * (float)cos(angle), r * (float)sin(angle), -h / 2);
	}

	//glNormal3f(1.0, 0.0, 0.0);
	//glVertex3f(r, 0.0, h / 2.0);
	//glVertex3f(r, 0.0, -h / 2.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGLRenderer::DrawAxes(double d)
{
	glLineWidth(2.0);
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(d, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, d, 0.0);

	glColor3f(0.0, 0.0, 1.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, d);

	glEnd();
} // pomocna funkcija