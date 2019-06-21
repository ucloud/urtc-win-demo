#pragma once

#include "gl3w.h"
#include "glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"
#include <iostream>
#include <memory>

class CUcloudRtcOpenGl
{
public:
	CUcloudRtcOpenGl();
	~CUcloudRtcOpenGl();

	HDC hDc;
	HGLRC hRC;

public:
	void Init(int nWidth,int nHeight, HWND wnd);

	bool SetupPixelFormat(HDC hdc0);

	void Reshap(int nWidth,int nHeight);
	
	void Render(std::tr1::shared_ptr<unsigned char>frame);

private:
	GLuint textureID = 0;
	int m_nWidth;
	int m_nHeight;	
};