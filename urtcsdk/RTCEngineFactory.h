#ifndef _UMEETING_RTCENGINEFACTORY_H_
#define _UMEETING_RTCENGINEFACTORY_H_

#include "RTCEngineBase.h"
#include "RTCDefine.h"

class RTCEngineFactory {
public:
	static RTCEngineBase* createRtcEngine(RTC_CHANNEL_TYPE chtype);
};

#endif
