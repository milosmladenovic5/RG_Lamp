#pragma once

class CGLMaterial
{
public:
	CGLMaterial();
	virtual ~CGLMaterial();

	void SelectFront();
	void SelectBack();
	void SelectFrontBack();
	
	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetEmission(float r, float g, float b, float a);
	void SetShininess(float s);
	
	//dodatne funkcije na osnovu prethodnih
	void SetWoodMaterial();
	void SetRedMetal();
	void SetWallMaterial();
	void SetFloorMaterial();
	void SetBulbMaterial();

protected:
	float m_vAmbient[4];
	float m_vDiffuse[4];
	float m_vSpecular[4];
	float m_vEmission[4];
	float m_fShininess;
};