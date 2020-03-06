
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
	m_videolist.clear();
	m_audiolist.clear();
}

bool ExtendMediaCapturer::pushVideoFrame(tUCloudRtcVideoFrame* frame) 
{
	if (m_videolist.size() > 30) {
		delete[]frame->mDataBuf;
		delete frame;
		frame = nullptr;
		return false;
	}
	m_vbuflock.lock() ;
	m_videolist.push_back(frame);
	m_vbuflock.unlock() ;
}

bool ExtendMediaCapturer::pushAudioFrame(tUCloudRtcAudioFrame* frame) 
{
	if (m_audiolist.size() > 3) {
		delete[]frame->mAudioData;
		delete frame;
		frame = nullptr;
		return false;
	}
	m_buflock.lock() ;
	m_audiolist.push_back(frame);
	m_buflock.unlock() ;
}

bool ExtendMediaCapturer::doCaptureVideoFrame(tUCloudRtcVideoFrame* frame) 
{
	if (m_videolist.empty() ) {
		return true;
	}
	m_vbuflock.lock();
	tUCloudRtcVideoFrame *pFrame = m_videolist.front();
	m_videolist.pop_front();
	m_vbuflock.unlock();

	frame->mWidth = pFrame->mWidth ;
	frame->mHeight = pFrame->mHeight;

	frame->mVideoType = pFrame->mVideoType;
	memcpy(frame->mDataBuf, pFrame->mDataBuf, pFrame->mHeight*pFrame->mWidth) ;
	
	
	delete[]pFrame->mDataBuf;
	delete pFrame;
	return true ;
}

bool ExtendMediaCapturer::doCaptureAudioFrame(tUCloudRtcAudioFrame* frame) 
{
	if (m_audiolist.empty()  ) {
	
		return true;
	}
	m_buflock.lock();
	tUCloudRtcAudioFrame *pFrame = m_audiolist.front();
	m_audiolist.pop_front();
	m_buflock.unlock();

	frame->mBytePerSimple = pFrame->mBytePerSimple;
	frame->mChannels = pFrame->mChannels;

	frame->mNumSimples = pFrame->mNumSimples;
	frame->mSimpleRate = pFrame->mSimpleRate;
	frame->mStreamId = pFrame->mStreamId;
	frame->mUserId = pFrame->mUserId;
	memcpy(frame->mAudioData, pFrame->mAudioData, 480*2*2);
	
	delete[]pFrame->mAudioData;
	delete pFrame;
	pFrame = nullptr;
	return true;
}