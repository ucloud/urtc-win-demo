#include "RTCEngineFactory.h"
#include "URTCEngineImpl.h"

RTCEngineBase* RTCEngineFactory::createRtcEngine(RTC_CHANNEL_TYPE chtype)
{
	RTCEngineBase* realengine = nullptr;
	switch (chtype)
	{
	case RTC_CHANNELTYPE_UCLOUD:
		realengine = new URTCEngineImpl;
		break;
	case RTC_CHANNELTYPE_AGORA:
		break;
	case RTC_CHANNELTYPE_ZEGO:
		break;
	default:
		break;
	}
	return realengine;
}
