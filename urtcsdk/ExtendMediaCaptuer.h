#ifndef _UCLOUD_RTC_EXTENDCAPTURER_H_
#define _UCLOUD_RTC_EXTENDCAPTURER_H_

#include "UCloudRtcEngine.h"

#include <list>
#include <vector>
#include <string>
#include <mutex>

class ExtendMediaCapturer: 
	public UCloudRtcExtendVideoCaptureSource,
	public UCloudRtcExtendAudioCaptureSource
{
public:
	static ExtendMediaCapturer* createInstance() ;
	static ExtendMediaCapturer* getInstance() ;
	
	static void deleteInstance() ;
	
	virtual ~ExtendMediaCapturer();
	void reset() ;
	void initExtendMediaCapturer();
	bool pushVideoFrame(tUCloudRtcVideoFrame* frame) ;
	bool pushAudioFrame(tUCloudRtcAudioFrame* frame) ;
	bool doCaptureVideoFrame(tUCloudRtcVideoFrame* frame)  ;
	bool doCaptureAudioFrame(tUCloudRtcAudioFrame* frame) ;
private :
	ExtendMediaCapturer();
	static ExtendMediaCapturer* sInstance ;

	std::mutex m_buflock ;
	std::mutex m_vbuflock;
	std::list<tUCloudRtcVideoFrame*> m_videolist ;
	std::list<tUCloudRtcAudioFrame*> m_audiolist ; 
};
#endif

