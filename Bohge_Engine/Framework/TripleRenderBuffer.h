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
#include "RenderBufferState.h"
#include "IInserter.h"

namespace BohgeEngine
{
	class IThreadMutex;
	//ʹ������buffer������߳���Ҫ��Ⱦ������
	//��һ������Ⱦ�У��ڶ����Ѿ������ϵȴ���Ⱦ�������������
	class BOHGE_FRAMEWORK TripleRenderBuffer : public IInserter
	{
		RTTI_DRIVER_TYPE_DECLEAR( TripleRenderBuffer, IInserter );
	private:
		enum Constant
		{
			TRC_BUFFER_SIZE	= 3,
		};
	private:
		RenderBufferState			m_RenderPipeArray[TRC_BUFFER_SIZE];
		IThreadMutex*				m_pMutex;
		RenderBufferState*			m_rpRendering;//������Ⱦ��
		RenderBufferState*			m_rpWaiting;//�ȴ���Ⱦ��
		RenderBufferState*			m_rpFlushing;//��������
		bool						m_isNewBuffer;//�Ƿ����µ���Ⱦ����
	public:
		TripleRenderBuffer(void);
		~TripleRenderBuffer(void);
	public:
		void SwapFlushingBuffer();//�������buffer
		void SwapActivedBuffer();//����
	public:
		virtual IntersectedType::Volume Intersect( const Aabbox3df& entity );
		virtual const Frustumf& GetFrustum( );
		virtual void Pushback( IComponent* com );
	public:
		BOHGE_FORCEINLINE void CopyCameraState( const ICamera& came )
		{
			m_rpFlushing->CopyCameraState( came );
		}
		BOHGE_FORCEINLINE bool isNewBuffer()//�Ƿ����µ���Ⱦ����
		{
			return m_isNewBuffer;
		}
		BOHGE_FORCEINLINE const PipelineProperty::VisableRender& GetVisableRender()
		{
			return m_rpRendering->GetVisableRender();
		}
		BOHGE_FORCEINLINE ICamera* GetCamera()
		{
			return m_rpRendering->GetCamera();
		}
	};
}
