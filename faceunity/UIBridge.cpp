#include "UIBridge.h"
#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include "stdio.h"
#include <vector>
int oriWindowWidth = 0;
int oriWindowHeight = 0;
float scaleRatioW = 1.f;
float scaleRatioH = 1.f;
bool showUI = true;
extern HANDLE hMutex;
int UIBridge::bundleCategory = 0;
int UIBridge::renderBundleCategory = -1;
std::vector<std::string> UIBridge::categoryBundles[BundleCategory::Count];
int UIBridge::faceType = 0;

bool UIBridge::showItemSelectWindow = false;
bool UIBridge::showItemTipsWindow = false;
bool UIBridge::showDegubInfoWindow = false;
bool UIBridge::showFilterSlider = false;
uint32_t UIBridge::mFPS = 60;
uint32_t UIBridge::mResolutionWidth = 1280;
uint32_t UIBridge::mResolutionHeight = 720;
uint32_t UIBridge::mRenderTime = 33;

int UIBridge::m_curFilterIdx;
int UIBridge::m_curRenderItem = -1;
std::string UIBridge::mCurRenderItemName = "baimao_Animoji.bundle";
double UIBridge::mLastTime = 0.0;
int UIBridge::mEnableSkinDect = 1;
int UIBridge::mEnableHeayBlur = 0;
int UIBridge::mSelectedCamera = 0;
float UIBridge::mFaceBeautyLevel[5] = { 0.0f };
float UIBridge::mFaceShapeLevel[6] = { 0.0f };
float UIBridge::mFilterLevel[10] = { 100,100,100,100,100, 100,100,100,100,100 };
float UIBridge::mMakeupLevel[10] = { 100,100,100,100,100, 100,100,100,100,100 };

bool UIBridge::mNeedIpcWrite = false;
bool UIBridge::mNeedPlayMP3 = false;
bool UIBridge::mNeedStopMP3 = false;

void resetBeautyParam()
{
	UIBridge::mEnableSkinDect = 1;
	UIBridge::mEnableHeayBlur = 0;
	UIBridge::mFaceBeautyLevel[0] = 70;
	UIBridge::mFaceBeautyLevel[1] = 70;
	UIBridge::mFaceBeautyLevel[2] = 70;
	UIBridge::mFaceBeautyLevel[3] = 70;
	UIBridge::mFaceBeautyLevel[4] = 0;
}

void resetShapeParam()
{
	UIBridge::faceType = 0;
	UIBridge::mFaceShapeLevel[0] = 40;
	UIBridge::mFaceShapeLevel[1] = 40;
	UIBridge::mFaceShapeLevel[2] = -20;
	UIBridge::mFaceShapeLevel[3] = -20;
	UIBridge::mFaceShapeLevel[4] = 50;
	UIBridge::mFaceShapeLevel[5] = -10;
}

bool doesFileExist(const std::string& filename)
{
	DWORD attr = GetFileAttributesA(filename.c_str());
	return (attr != INVALID_FILE_ATTRIBUTES);
}

bool isDirectoryExists(const std::string& filename)
{
	DWORD attr = GetFileAttributesA(filename.c_str());
	return ((attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY));
}

int get_fps()
{
	static int fps = 0;
	static int lastTime = GetTickCount(); // ms
	static int frameCount = 0;

	++frameCount;

	int curTime = GetTickCount();
	if (curTime - lastTime > 1000) // 取固定时间间隔为1秒
	{
		fps = frameCount - 1;
		frameCount = 0;
		lastTime = curTime;
	}
	return fps;
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
