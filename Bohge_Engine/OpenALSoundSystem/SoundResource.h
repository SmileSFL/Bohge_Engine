//////////////////////////////////////////////////////////////////////////////////////
//
//						The Bohge Engine License (BEL)
//
//	Copyright (c) 2011-2014 Peng Zhao
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in 
//	all copies or substantial portions of the Software. And the logo of 
//	Bohge Engine shall be displayed full screen for more than 3 seconds 
//	when the software is started. Copyright holders are allowed to develop 
//	game edit based on Bohge Engine, The edit must be released under the MIT 
//	open source license if it is going to be published. In no event shall 
//	copyright holders be prohibited from using any code of Bohge Engine 
//	to develop any other analogous game engines.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//
//////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include "Decoder.h"


#include <EASTL/string.h>



namespace OpenALSoundSystemPlugin
{
	class Decoder;
	class SoundResource//������Դ
	{
		//������Դ����decoder���ϲ���������ڼ�����Դ�Ŀ��Խ�����ͬ��Դ�ļ��ع���
		//��һ��������Դ���ظ�ʹ�õ�ʱ��decoder������ʽ������Դ������֮������ȥ�ͷž���Դ
		//������������һ���Ŀռ���Դ��ȡʱ��
	private:
		BohgeEngine::SmartPtr<Decoder>		m_pDecoder;
		const char*							m_BufferAddress;
		uint								m_nBufferSize;
		uint								m_nCurrentBufferIndex;//��ǰ����buffer��index
		bool								m_isDone;
	public:
		SoundResource( BohgeEngine::SmartPtr<Decoder> decoder );
		~SoundResource(void);
	public:
		void FlushBufferData();
	public:
		BOHGE_FORCEINLINE const eastl::string& GetFilePath() const
		{
			return m_pDecoder->GetFilePath();
		}
		BOHGE_FORCEINLINE void RequestDecode()//Ҫ��������ݶ�
		{
			DecoderManager::Instance()->PushDecodeJob( m_pDecoder );
		}
		BOHGE_FORCEINLINE int GetFrequency() const
		{
			return m_pDecoder->GetFrequency();
		}
		BOHGE_FORCEINLINE Decoder::Format GetFormat() const
		{
			return m_pDecoder->GetFormat();
		}
		BOHGE_FORCEINLINE int GetChannels() const
		{
			return m_pDecoder->GetChannels();
		}
		BOHGE_FORCEINLINE int GetBufferSize() const
		{
			return m_nBufferSize;
		}
		BOHGE_FORCEINLINE int GetSourceSize() const
		{
			return m_pDecoder->GetSourceSize();
		}
		BOHGE_FORCEINLINE const char* GetBufferChunk() const//�õ����ݶ�
		{
			return m_BufferAddress;
		}
		BOHGE_FORCEINLINE bool isChunkReady() const
		{
			return m_pDecoder->isChunkReady( m_nCurrentBufferIndex );
		}
		BOHGE_FORCEINLINE bool isDone() const //�Ƿ񲥷����
		{
			return m_isDone;
		}
	};
}
