#include "stdafx.h"
#include "GLTexture.h"


CGLTexture::CGLTexture()
{
	this->m_ID = 0;
}

CGLTexture::~CGLTexture()
{
}

void CGLTexture::LoadFromFile(CString file)
{
	if (this->m_ID != 0) 
		this->Release();

	glGenTextures(1, &this->m_ID);
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
	DImage* TextureImage = new DImage();
	
	TextureImage->Load(file);

	TextureImage->Update();
	if (TextureImage->Width() != 0)
	{

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// definise ponavljanje po 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_TEXTURE_2D);
		/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			(GLsizei)TextureImage->Width(), (GLsizei)TextureImage->Height(),
			(GLint)0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, TextureImage->GetDIBBits());*/

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TextureImage->Width(), TextureImage->Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, TextureImage->GetDIBBits());

		glBindTexture(GL_TEXTURE_2D, this->m_ID);
		glDisable(GL_TEXTURE_2D);
	}
	delete TextureImage;
}

void CGLTexture::Select()
{
	if (this->m_ID != 0)
	{
		glBindTexture(GL_TEXTURE_2D, this->m_ID);
	}
}

void CGLTexture::Release()
{
	if (this->m_ID)
	{
		glDeleteTextures(1, &this->m_ID);
		this->m_ID = 0;
	}
}

void CGLTexture::PrepareTexturing(bool bEnableLighting)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	if (bEnableLighting)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		// kako se mesaju pikseli podloge i pikseli teksture 
	else                                                                    // ako je osvetljenje ukljuceno !!!!
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);         // samo zamenimo mrtvu podlogu zato sto nema veze

	glDisable(GL_BLEND);
}
