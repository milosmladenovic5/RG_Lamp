#pragma once
#include "GLTexture.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "CGLMaterial.h"


class CGLRenderer
{
private:
	CGLMaterial material;
	CGLTexture wood;
	CGLTexture wall;
	CGLTexture floor;
	CGLTexture lig;

public:
	float* vert;
	float* col;
	byte* ind;
	int nSteps;

	float lampBottomZAngle;
	float lampBottomXAngle;
	float lampMiddleZAngle;
	float lampMiddleXAngle;
	float lampTopZAngle;
	float lampTopXAngle;

	



public:
	CGLRenderer();
	virtual ~CGLRenderer();

	bool CreateGLContext(CDC* pDC);			// kreira OpenGL Rendering Context
	void PrepareScene(CDC* pDC);			// inicijalizuje scenu,
	void Reshape(CDC* pDC, int w, int h);	// kod koji treba da se izvrsi svaki put kada se promeni velicina prozora ili pogleda i
	void DrawScene(CDC* pDC);				// iscrtava scenu
	void DestroyScene(CDC* pDC);			// dealocira resurse alocirane u drugim funkcijama ove klase,

	void DrawAxes(double d);				// pomocna funkcija

	inline void IncLampBottomZAngle() { this->lampBottomZAngle += ((this->lampBottomZAngle >= 40.0) ? 0 : 5); };
	inline void DecLampBottomZAngle() { this->lampBottomZAngle -= ((this->lampBottomZAngle <= -40.0) ? 0 : 5); };

	inline void IncLampBottomXAngle() { this->lampBottomXAngle += ((this->lampBottomXAngle >= 50.0) ? 0 : 5); };
	inline void DecLampBottomXAngle() { this->lampBottomXAngle -= ((this->lampBottomXAngle <= -50.0) ? 0 : 5); };

	inline void IncLampMiddleZAngle() { this->lampMiddleZAngle += /*((this->lampBottomZAngle >= 120.0) ? 0 : 5);*/ 5; };
	inline void DecLampMiddleZAngle() { this->lampMiddleZAngle -= /*((this->lampBottomZAngle <= -120.0) ? 0 : 5);*/ 5; };

	inline void IncLampMiddleXAngle() { this->lampMiddleXAngle += /*((this->lampBottomXAngle >= 100.0) ? 0 : 5);*/ 5; };
	inline void DecLampMiddleXAngle() { this->lampMiddleXAngle -= /*((this->lampBottomXAngle <= -100.0) ? 0 : 5);*/ 5; };

	inline void IncLampTopZAngle() { this->lampTopZAngle += ((this->lampTopZAngle >= 25.0) ? 0 : 5); };
	inline void DecLampTopZAngle() { this->lampTopZAngle -= ((this->lampTopZAngle <= -30.0) ? 0 : 5); };

	inline void IncLampTopXAngle() { this->lampTopXAngle += ((this->lampTopXAngle >= 20.0) ? 0 : 5); };
	inline void DecLampTopXAngle() { this->lampTopXAngle -= ((this->lampTopXAngle <= -20.0) ? 0 : 5); };

	//-----------------lab_4---------------------
	void PrepareVABox(double a, double b, double c);
	void PrepareVAWall(double a);

	void DrawBox(float c1, float c2, float c3);
	void DrawTable(double a, double b, double c);
	void DrawWall(float c1, float c2, float c3);
	void DrawWalls(double size);
	void DrawLamp();
	void DrawLampHead(GLUquadric* quadric);

	//-----------------lab_5---------------------
	void DrawSide(double a, double b,int steps);
	void DrawBoxWithNormals(double a, double b, double c, int nSteps, bool bTexture);
	void SetLightModel();
	void SetPositionLight();
	//-----------------lab_6---------------------
	void DrawSideWithTexture(double a, double b, int steps);
	void DrawCylindricalObject(float r, float h, int steps);

protected:
	HGLRC	 m_hrc; //OpenGL Rendering Context 
};
