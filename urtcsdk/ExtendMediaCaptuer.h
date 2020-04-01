#ifndef _UCLOUD_RTC_EXTENDCAPTURER_H_
#define _UCLOUD_RTC_EXTENDCAPTURER_H_

#include "UCloudRtcEngine.h"
#include "BufferQueue.h"
#include <list>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>

typedef struct RtcVideoFrame {
	//视频数据
	unsigned char* mVideoData;
	int mBuflen;
	int mWidth;
	int mHeight;
	eUCloudRtcVideoFrameType mVideoType;
public:
	RtcVideoFrame()
	{
		mVideoData = nullptr;
		mBuflen = 0;
		mWidth = 0;
		mHeight = 0;
		mVideoType = UCLOUD_RTC_VIDEO_FRAME_TYPE_I420;
	}
}tRtcVideoFrame;

typedef struct RtcAudioFrame {
	void* mAudioData;
	int mBytePerSimple;
	int mSimpleRate;
	int mChannels;
	int mNumSimples;
public:
	RtcAudioFrame() {
		mAudioData = nullptr;
		mBytePerSimple = 0;
		mSimpleRate = 0;
		mSimpleRate = 0;
		mNumSimples = 0;
	}

}tRtcAudioFrame;

template <typename T>
class FrameList {
private:
	std::list<T> list;

private:
	std::atomic_flag m_buflock = ATOMIC_FLAG_INIT;
public:
	FrameList() {};
	~FrameList() {};

	void Lock()
	{
		while (m_buflock.test_and_set(std::memory_order_acquire))
		{
			;
		}
	}

	void Unlock()
	{
		m_buflock.clear(std::memory_order_release);
	}

	void Push(T data)
	{
		Lock();
		list.push_back(data);
		Unlock();
	}

	T Front()
	{
		Lock();
		T data = list.front();
		Unlock();

		return data;
	}

	void PopFront()
	{
		Lock();
		list.pop_front();
		Unlock();
	}

	bool IsEmpty()
	{
		Lock();
		if (list.empty())
		{
			Unlock();
			return true;
		}
		else
		{
			Unlock();
			return false;
		}
	}

	int Size() {
		//Lock();
		return list.size();
		//Unlock();
	}
};

//视频缓冲队列
class VideoList {
public:
	VideoList() {
		m_lpImageBuffer = new BYTE[0x800000];
		memset(m_lpImageBuffer, 0x00, sizeof(m_lpImageBuffer));
		m_nPackageSize = 0;
		m_nBufferSize = 0x800000;
		m_bufQueue.Create(3, 0x800000);
	};
	~VideoList() {
		m_bufQueue.FreeAllBusyBlock();
		m_bufQueue.Close();
		delete m_lpImageBuffer;
		m_lpImageBuffer = nullptr;
	};
public:
	void setVideoFrameLen(const int &len)
	{
		m_nPackageSize = len;
	}
	bool pushVideoFrame(tRtcVideoFrame* pframe) 
	{
		if (!pframe || !pframe->mVideoData || pframe->mWidth <= 0 ||
			pframe->mHeight <= 0) {
			return false;
		}

		if (m_list.Size() > 3) {
			return false;
		}

		if (pushVideoPackage(pframe->mVideoData, pframe->mBuflen)) {
			tUCloudRtcVideoFrame frame;
			frame.mHeight = pframe->mHeight;
			frame.mWidth = pframe->mWidth;
			frame.mVideoType = pframe->mVideoType;
			frame.mDataBuf = nullptr;

			m_list.Push(frame);
			return true;
		}
		return false;
	};
	bool popVideoFrame(tRtcVideoFrame* pframe) {
		if (m_list.IsEmpty()) {
			return false;
		}
		SIZE_T  nBufferSize = 0x800000;
		memset(m_lpImageBuffer, 0x00, sizeof(m_lpImageBuffer));
		if (popVideoPackage(m_lpImageBuffer, &nBufferSize)) {
			tUCloudRtcVideoFrame frame = m_list.Front();
			m_list.PopFront();

			pframe->mVideoData = m_lpImageBuffer;
			pframe->mHeight = frame.mHeight;
			pframe->mWidth = frame.mWidth;
			pframe->mVideoType = frame.mVideoType;
			pframe->mBuflen = nBufferSize;
			return true;
		}
		return false;
	};
private:
	bool pushVideoPackage(LPCVOID lpVideoPackage, SIZE_T nPackageLen)
	{
		if (m_bufQueue.GetFreeCount() == 0)
			m_bufQueue.FreeBusyHead(NULL, 0);

		LPVOID lpBuffer = m_bufQueue.AllocBuffer(FALSE);
		if (lpBuffer == NULL)
			return FALSE;

		_ASSERT(m_bufQueue.GetBytesPreUnit() >= nPackageLen);

		memcpy_s(lpBuffer, m_bufQueue.GetBytesPreUnit(), lpVideoPackage, nPackageLen);

		return TRUE;
	}

	bool popVideoPackage(LPVOID lpVideoPackage, SIZE_T *nPackageSize)
	{
		_ASSERT(nPackageSize != NULL);

		if (nPackageSize == 0)
			return FALSE;

		if (m_bufQueue.GetBusyCount() == 0)
			return FALSE;

		if (*nPackageSize < m_nPackageSize) {
			*nPackageSize = m_nPackageSize;
			return FALSE;
		}

		*nPackageSize = m_nPackageSize;
		m_bufQueue.FreeBusyHead(lpVideoPackage, m_nPackageSize);

		return TRUE;
	}
private:
	FrameList<tUCloudRtcVideoFrame> m_list;
	CBufferQueue		m_bufQueue;
	unsigned int				m_nPackageSize;
	unsigned int				m_nBufferSize;
	BYTE* m_lpImageBuffer;
};

//音频缓冲队列
class AudioList{
public:
	AudioList() {
		m_lpAudioBuffer = new BYTE[480*2*2];
		m_bufQueue.Create(3, 480*2*2);
	};
	~AudioList() {
		m_bufQueue.FreeAllBusyBlock();
		m_bufQueue.Close();
		delete m_lpAudioBuffer;
		m_lpAudioBuffer = nullptr;
	};
	void setAudioFrameLen(const int &len)
	{
		m_nPackageSize = len;
	}

	bool pushAudioFrame(tRtcAudioFrame *pframe) {
		if (!pframe || !pframe->mAudioData || pframe->mBytePerSimple <= 0 ||
			pframe->mChannels <= 0 || pframe->mSimpleRate <= 0 ||
			pframe->mNumSimples <= 0) {
			return false;
		}

		if (m_list.Size() > 3) {
			return false;
		}

		if (pushAudioPackage(pframe->mAudioData, m_nPackageSize)) {
			tUCloudRtcAudioFrame frame;
			frame.mAudioData = pframe->mAudioData;
			frame.mChannels = pframe->mChannels;
			frame.mBytePerSimple = pframe->mBytePerSimple;
			frame.mNumSimples = pframe->mNumSimples;
			frame.mSimpleRate = pframe->mSimpleRate;
			frame.mStreamId = nullptr;
			frame.mUserId = nullptr;

			m_list.Push(frame);
			return true;
		}
		return false;
	};
	bool popAudioFrame(tRtcAudioFrame *pframe) {
		if (m_list.IsEmpty()) {
			return false;
		}
		SIZE_T  nBufferSize = 480*2*2;
		memset(m_lpAudioBuffer, 0x00, sizeof(m_lpAudioBuffer));
		if (popAudioPackage(m_lpAudioBuffer, &nBufferSize)) {
			tUCloudRtcAudioFrame frame = m_list.Front();
			m_list.PopFront();

			pframe->mAudioData = m_lpAudioBuffer;
			pframe->mBytePerSimple = frame.mBytePerSimple;
			pframe->mChannels = frame.mChannels;
			pframe->mNumSimples = frame.mNumSimples;
			pframe->mSimpleRate = frame.mSimpleRate;
			return true;
		}
		return false;
	};
private:
	bool pushAudioPackage(LPCVOID lpVideoPackage, SIZE_T nPackageLen)
	{
		if (m_bufQueue.GetFreeCount() == 0)
			m_bufQueue.FreeBusyHead(NULL, 0);

		LPVOID lpBuffer = m_bufQueue.AllocBuffer(FALSE);
		if (lpBuffer == NULL)
			return FALSE;

		_ASSERT(m_bufQueue.GetBytesPreUnit() >= nPackageLen);

		memcpy_s(lpBuffer, m_bufQueue.GetBytesPreUnit(), lpVideoPackage, nPackageLen);

		return TRUE;
	}

	bool popAudioPackage(LPVOID lpVideoPackage, SIZE_T *nPackageSize)
	{
		_ASSERT(nPackageSize != NULL);

		if (nPackageSize == 0)
			return FALSE;

		if (m_bufQueue.GetBusyCount() == 0)
			return FALSE;

		if (*nPackageSize < m_nPackageSize) {
			*nPackageSize = m_nPackageSize;
			return FALSE;
		}

		*nPackageSize = m_nPackageSize;
		m_bufQueue.FreeBusyHead(lpVideoPackage, m_nPackageSize);

		return TRUE;
	}
private:
	FrameList<tUCloudRtcAudioFrame> m_list;
	CBufferQueue		m_bufQueue;
	unsigned int				m_nPackageSize;
	unsigned int				m_nBufferSize;

	BYTE* m_lpAudioBuffer;

};

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

	bool pushVideoFrame(tRtcVideoFrame* frame) ;
	bool pushAudioFrame(tRtcAudioFrame* frame) ;

	bool doCaptureVideoFrame(tUCloudRtcVideoFrame* frame)  ;
	bool doCaptureAudioFrame(tUCloudRtcAudioFrame* frame) ;
private :
	ExtendMediaCapturer();
	static ExtendMediaCapturer* sInstance ;

	AudioList m_audiolist ;
	VideoList m_videolist;
	
};
#endif

