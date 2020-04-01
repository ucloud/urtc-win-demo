#include "stdafx.h"
#include "ExtendMediaCaptuer.h"
#include <string>
#include <vector>

ExtendMediaCapturer* ExtendMediaCapturer::sInstance = nullptr ;

ExtendMediaCapturer* ExtendMediaCapturer::createInstance() 
{
	if (sInstance == nullptr) {
		sInstance = new ExtendMediaCapturer();
		sInstance->initExtendMediaCapturer();
	}
	return sInstance ;
}

void ExtendMediaCapturer::initExtendMediaCapturer() {
	m_videolist.setVideoFrameLen(640 * 360 * 3 / 2);
	m_audiolist.setAudioFrameLen(480*2*2);

}
ExtendMediaCapturer* ExtendMediaCapturer::getInstance() 
{
	return sInstance ;
}

 void ExtendMediaCapturer::deleteInstance() {
	if (sInstance)
	{
		delete sInstance;
		sInstance = nullptr;
	}
}

ExtendMediaCapturer::ExtendMediaCapturer()
{

}

ExtendMediaCapturer::~ExtendMediaCapturer()
{
	
}

void ExtendMediaCapturer::reset() 
{	

}


bool ExtendMediaCapturer::pushVideoFrame(tRtcVideoFrame* pframe)
{
	return m_videolist.pushVideoFrame(pframe);
}

bool ExtendMediaCapturer::pushAudioFrame(tRtcAudioFrame* pframe)
{
	return m_audiolist.pushAudioFrame(pframe);
}

bool ExtendMediaCapturer::doCaptureVideoFrame(tUCloudRtcVideoFrame* pframe) 
{
	tRtcVideoFrame frame;

	if (m_videolist.popVideoFrame(&frame))
	{
		memcpy_s(pframe->mDataBuf, frame.mBuflen, frame.mVideoData, frame.mBuflen);
		pframe->mHeight = frame.mHeight;
		pframe->mWidth = frame.mWidth;
		pframe->mVideoType = frame.mVideoType;
		return true;
	}
	return false;
}

bool ExtendMediaCapturer::doCaptureAudioFrame(tUCloudRtcAudioFrame* pframe) 
{
	
	tRtcAudioFrame frame;

	if (m_audiolist.popAudioFrame(&frame))
	{
		pframe->mBytePerSimple = frame.mBytePerSimple;
		pframe->mChannels = frame.mChannels;

		pframe->mNumSimples = frame.mNumSimples;
		pframe->mSimpleRate = frame.mSimpleRate;
		pframe->mStreamId = "";
		pframe->mUserId = "";

		memcpy(pframe->mAudioData, frame.mAudioData, 480 * 2 * 2);
		return true;
	}
	return false;
}