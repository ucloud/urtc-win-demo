#ifndef _UCLOUD_RTC_MEDIA_DEVICE_CPP_H_
#define _UCLOUD_RTC_MEDIA_DEVICE_CPP_H_
#include "UCloudRTCComDefine.h"

class  _EXPORT_API UCloudRtcAudioLevelListener
{
public:
	virtual void onMicAudioLevel(int volume) {}
};

class _EXPORT_API UCloudRtcMediaDevice {
public:
	static UCloudRtcMediaDevice *sharedInstance();
	static void destory();

	//初始化音频模块
	virtual int InitAudioMoudle() =0;
	//释放音频模块
	virtual int UnInitAudioMoudle() = 0;
	//初始化视频模块
	virtual int InitVideoMoudle() = 0;
	//释放视频模块
	virtual int UnInitVideoMoudle() = 0;
	//获取摄像头数目
	virtual int getCamNums() = 0;
	//获取录音设备数目
	virtual int getRecordDevNums() = 0;
	//获取播放设备数目
	virtual int getPlayoutDevNums() = 0;
	//获取摄像头信息
	virtual int getVideoDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;
	//获取录音设备信息
	virtual int getRecordDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;
	//获取播放设备信息
	virtual int getPlayoutDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;
	//获取当前摄像头
	virtual int getCurCamDev(tUCloudRtcDeviceInfo* info) = 0;
	//获取当前录音设备
	virtual int getCurRecordDev(tUCloudRtcDeviceInfo* info) = 0;
	//获取当前播放设备
	virtual int getCurPlayoutDev(tUCloudRtcDeviceInfo* info) = 0;
	//设置视频设备信息
	virtual int setVideoDevice(tUCloudRtcDeviceInfo* info) = 0;
	//设置录制设备信息
	virtual int setRecordDevice(tUCloudRtcDeviceInfo* info) = 0;
	//设置播放设备信息
	virtual int setPlayoutDevice(tUCloudRtcDeviceInfo* info) = 0;
	//获取播放音量
	virtual int getPlaybackDeviceVolume(int *volume) = 0;
	virtual int setPlaybackDeviceVolume(int volume) = 0;
	//获取录制音量
	virtual int getRecordingDeviceVolume(int *volume) = 0;
	virtual int setRecordingDeviceVolume(int volume) = 0;
	//开启cam测试
	virtual int startCamTest(const char deviceId[MAX_DEVICE_ID_LENGTH], 
		eUCloudRtcVideoProfile profile,
		void* hwnd) = 0;
	//停止摄像头测试
	virtual int stopCamTest() = 0;
	//开启录音测试
	virtual int startRecordingDeviceTest(UCloudRtcAudioLevelListener* audiolevel) = 0;
	//停止录音测试
	virtual int stopRecordingDeviceTest() = 0;
	//开启播放设备测试
	virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;
	//停止播放设备测试
	virtual int stopPlaybackDeviceTest() = 0;
	//开启摄像头Capture测试
	virtual int startCaptureFrame(eUCloudRtcVideoProfile profile,
		UCloudRtcVideoFrameObserver* observer) = 0;
	//停止摄像头Capture测试
	virtual int stopCaptureFrame() = 0;

protected:
	UCloudRtcMediaDevice() { }
	virtual ~UCloudRtcMediaDevice() {}
};

#endif







