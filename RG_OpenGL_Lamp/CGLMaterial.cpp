#include "stdafx.h"
#include "CGLMaterial.h"
#include <GL\gl.h>
#include <GL\glu.h>

CGLMaterial::CGLMaterial()
{
	m_vAmbient[0] = 0.2f;	m_vAmbient[1] = 0.2f;
	m_vAmbient[2] = 0.2f;	m_vAmbient[3] = 1.0f;

	m_vDiffuse[0] = 0.8f;	m_vDiffuse[1] = 0.8f;
	m_vDiffuse[2] = 0.8f;	m_vDiffuse[3] = 1.0f;

	m_vSpecular[0] = 1.0f;	m_vSpecular[1] = 1.0f;
	m_vSpecular[2] = 1.0f;	m_vSpecular[3] = 1.0f;

	m_vEmission[0] = 0.0f;	m_vEmission[1] = 0.0f;
	m_vEmission[2] = 0.0f;	m_vEmission[3] = 1.0f;
	
	m_fShininess = 64.0f;
}

CGLMaterial::~CGLMaterial()
{
}

void CGLMaterial::SelectFront()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_vAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_vDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_vSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_vEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, m_fShininess);
}


void CGLMaterial::SelectBack()
{
	glMaterialfv(GL_BACK, GL_AMBIENT, m_vAmbient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, m_vDiffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, m_vSpecular);
	glMaterialfv(GL_BACK, GL_EMISSION, m_vEmission);
	glMaterialf(GL_BACK, GL_SHININESS, m_fShininess);
}

void CGLMaterial::SelectFrontBack()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_vAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_vDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_vSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_vEmission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_fShininess);
}

void CGLMaterial::SetAmbient(float r, float g, float b, float a)
{
	m_vAmbient[0] = r;	m_vAmbient[1] = g;
	m_vAmbient[2] = b;	m_vAmbient[3] = a;
}

void CGLMaterial::SetDiffuse(float r, float g, float b, float a)
{
	m_vDiffuse[0] = r;	m_vDiffuse[1] = g;
	m_vDiffuse[2] = b;	m_vDiffuse[3] = a;
}

void CGLMaterial::SetSpecular(float r, float g, float b, float a)
{
	m_vSpecular[0] = r;	m_vSpecular[1] = g;
	m_vSpecular[2] = b;	m_vSpecular[3] = a;

}

void CGLMaterial::SetEmission(float r, float g, float b, float a)
{	
	m_vEmission[0] = r;	m_vEmission[1] = g;
	m_vEmission[2] = b;	m_vEmission[3] = a;
}

void CGLMaterial::SetShininess(float s)
{
	if(s < 0.0) m_fShininess = 0.0;
	else 
		if(s > 128.0) m_fShininess = 128.0;
		else
			m_fShininess = s;
}

void CGLMaterial::SetWoodMaterial()
{
	this->SetAmbient(0.47f, 0.2f, 0.01f, 1.0f);
	this->SetDiffuse(1.0f, 0.5f, 0.2f, 1.0f);
	
	this->SetEmission(0.0f, 0.0f, 0.0f, 1.0f);

	this->SetSpecular(0.1f, 0.0f, 0.0f, 1.0f);
	this->SetShininess(7);
}

void CGLMaterial::SetRedMetal()
{	
	this->SetAmbient(0.3f, 0.15f, 0.1f, 1.0f);
	this->SetDiffuse(1.0f, 0.1f, 0.1f, 1.0f);
	
	this->SetEmission(0.0f, 0.0f, 0.0f, 1.0f);
	
	this->SetSpecular(1.0f, 0.8f, 0.8f, 1.0f);
	this->SetShininess(128);
}

void CGLMaterial::SetWallMaterial()
{
	this->SetAmbient(0.4f, 0.34f, 0.28f, 1.0f);
	this->SetDiffuse(0.5f, 0.48f, 0.36f, 1.0f);
	
	this->SetEmission(0.0f, 0.0f, 0.0f, 1.0f);
	
	this->SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
}

void CGLMaterial::SetFloorMaterial()
{
	this->SetAmbient(0.8f, 0.7f, 0.58f, 1.0f);
	this->SetDiffuse(0.8f, 0.7f, 0.58f, 1.0f);
	
	this->SetEmission(0.0f, 0.0f, 0.0f, 1.0f);
	
	this->SetSpecular(0.0f, 0.0f, 0.0f, 1.0f);
}

void CGLMaterial::SetBulbMaterial()
{
	this->SetDiffuse(0.0f, 0.0f, 0.8f, 1.0f);
	
	this->SetEmission(1.0f, 1.0f, 0.0f, 1.0f);
	
}