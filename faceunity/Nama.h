#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <windows.h>
typedef unsigned char uchar;
namespace NamaExampleNameSpace
{
	class Nama
	{		
	public:
		using UniquePtr = std::unique_ptr<Nama>;
		static UniquePtr create(uint32_t width, uint32_t height, HWND wnd,bool enable = true);

		Nama();
		~Nama();
		bool CheckGLContext();
		bool Init(uint32_t& width, uint32_t& height, HWND wnd);
		bool IsInited() { return mHasSetup; }
		bool SelectBundle(std::string bundleName);
		bool CheckModuleCode(int category);
		void RenderItemEx(uchar* frame);
		uchar* RenderEx(uchar* frame);
		int  IsTracking();
		void SetCurrentShape(int index);
		void SetCurrentMakeup(int index);
		void UpdateFilter(int);
		void UpdateMakeupParams();
		void UpdateBeauty();
		void SwitchBeauty(bool);
	private:				
		int mBeautyHandles;
		int mLightMakeUpHandle;
		int mGestureHandles;
		int mFxaaHandles;
		uint32_t mFrameWidth, mFrameHeight;
		static bool mHasSetup;
	public:	
		static bool mEnableNama;
		int mIsBeautyOn;	
		int mIsDrawPoints;
		int mMaxFace;
		int mFrameID;		
		int mModuleCode, mModuleCode1;
		static std::string mFilters[6];
		HWND mHwnd;
		std::unordered_map<std::string, int> mBundlesMap;
	};

	size_t FileSize(std::ifstream& file);

	bool LoadBundle(const std::string& filepath, std::vector<char>& data);
}

template < class T>
std::string ConvertToString(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

struct MakeupParam
{
	std::string typeName;
	std::string valueName;
	std::string textureName;
	int value;
};
