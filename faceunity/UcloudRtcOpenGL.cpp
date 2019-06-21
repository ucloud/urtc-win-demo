#include "stdafx.h"
#include "UcloudRtcOpenGL.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
//#pragma comment(lib,"glew32.lib")
//#pragma comment(lib,"glut32.lib")

CUcloudRtcOpenGl::CUcloudRtcOpenGl()
{

}

CUcloudRtcOpenGl::~CUcloudRtcOpenGl()
{
	wglMakeCurrent(hDc, nullptr);
	wglDeleteContext(hRC);
}

PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1u,
	PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW,
	PFD_TYPE_RGBA,
	32u,
	0u, 0u, 0u, 0u, 0u, 0u,
	8u,
	0u,
	0u,
	0u, 0u, 0u, 0u,
	24u,
	8u,
	0u,
	PFD_MAIN_PLANE,
	0u,
	0u, 0u };

void CUcloudRtcOpenGl::Init(int nWidth, int nHeight, HWND wnd)
{

	/*HWND hw = CreateWindowExA(
		0, "EDIT", "", ES_READONLY,
		0, 0, 1, 1,
		NULL, NULL,
		GetModuleHandleA(NULL), NULL);*/
	HDC hgldc = GetDC(wnd);
	int spf = ChoosePixelFormat(hgldc, &pfd);
	int ret = SetPixelFormat(hgldc, spf, &pfd);
	HGLRC hglrc = wglCreateContext(hgldc);
	wglMakeCurrent(hgldc, hglrc);

	//hglrc就是创建出的OpenGL context
	printf("hw=%08x hgldc=%08x spf=%d ret=%d hglrc=%08x\n",
		wnd, hgldc, spf, ret, hglrc);
//#if 1
//	m_nWidth = nWidth;
//	m_nHeight = nHeight;
//	glDisable(GL_LIGHTING);
//	glDisable(GL_DEPTH_TEST);
//	glEnable(GL_TEXTURE_2D);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, nWidth, 0, nHeight, 0, 1000);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//#else
//	glClearColor(0.0, 1.0, 1.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//
//	glMatrixMode(GL_PROJECTION);
//	gluPerspective(60, (GLfloat)nWidth / (GLfloat)nHeight, 0.0, 100.0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//#endif

}

bool CUcloudRtcOpenGl::SetupPixelFormat(HDC hdc0)
{
	int nPixelFormat;
	hDc = hdc0;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小  
		1,														 // 版本号  
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图  
		PFD_SUPPORT_OPENGL |              // 支持OpenGL  
		PFD_DOUBLEBUFFER,                 // 双缓存模式  
		PFD_TYPE_RGBA,                    // RGBA 颜色模式  
		24,                               // 24 位颜色深度  
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位  
		0,                                // 没有非透明度缓存  
		0,                                // 忽略移位位  
		0,                                // 无累加缓存  
		0, 0, 0, 0,                       // 忽略累加位  
		32,                               // 32 位深度缓存     
		0,                                // 无模板缓存  
		0,                                // 无辅助缓存  
		PFD_MAIN_PLANE,                   // 主层  
		0,                                // 保留  
		0, 0, 0                           // 忽略层,可见性和损毁掩模  
	};

	if (!(nPixelFormat = ChoosePixelFormat(hDc, &pfd))){
		MessageBox(NULL, L"can not find proper mode", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	SetPixelFormat(hDc, nPixelFormat, &pfd);
	hRC = wglCreateContext(hDc);
	wglMakeCurrent(hDc, hRC);
	return TRUE;
}

void CUcloudRtcOpenGl::Reshap(int nWidth, int nHeight)
{
	//glViewport(0, 0, nWidth, nHeight);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective
	//	(60.0f,
	//	(GLfloat)nWidth / (GLfloat)nHeight,
	//	0.1f,
	//	100.0f
	//	);
	////gluLookAt(10,5,10,0,0,0,0,1,0);  
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

void CUcloudRtcOpenGl::Render(std::tr1::shared_ptr<unsigned char>frame)
{
#if 0
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glEnd();
	SwapBuffers(hDc);
#else

	//glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0.5, 0.5, 0.0, 1.0);
	//glDisable(GL_BLEND);

	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,frame.get());
	//
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glBegin(GL_TRIANGLE_FAN);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(0, 0, 0.0f);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(0, m_nHeight, 0.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(m_nWidth, m_nHeight, 0);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(m_nWidth, 0, 0.0f);
	//glEnd();
#endif
}