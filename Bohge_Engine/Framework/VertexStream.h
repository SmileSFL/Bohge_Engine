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
#include "BufferObjectProperty.h"
#include "VertexStreamLayout.h"
#include "VertexCompress.h"
#include "3DMath.h"

#include <EASTL/vector.h>

namespace BohgeEngine
{
	class BOHGE_FRAMEWORK VertexStream : public Object
	{
		RTTI_TYPE_DECLEAR( VertexStream );
	private:
		enum Constant
		{
			VC_RESERVE_BUFFER_SIZE = 256,
		};
	private:
		struct VertexPusher//����ѹե�ṹ��
		{
			VertexCompress::VertexCompressFunction		CompressPtr;//ѹ������ָ��
			uint										IndicesCount;//��������
			byte										PointerStride;//��ַƫ�Ƶ�byteλ
			byte										Count;
			byte										Bytesize;//ÿһ������������byte����
			VertexPusher():CompressPtr(NULL),PointerStride(0),Count(0),Bytesize(0),IndicesCount(0){}
			void ResetIndices()
			{
				IndicesCount = 0;
			}
		};
	private:
		typedef eastl::vector<VertexPusher*> VertexPusherVector;
		typedef eastl::vector<byte> Buffer;
	private:
		VertexStreamLayout		m_Layout;//���ݹ���
		VertexPusherVector		m_VertexPusherVector;
		vector2d				m_FlushInterval;//��Ҫ�����µ�����
		uint					m_nReserveVertexCount;//Ԥ����Ķ����ڴ����
		uint					m_nVertexCount;//�������
		byte					m_nChunkStride;//ÿһ�����ݵĴ�С
		Buffer					m_Buffer;
	public:
		VertexStream(void);
		VertexStream( const VertexStream& rhs );
		~VertexStream(void);
	private:
		void _SetVertexType( Attributes::ShaderAttributes sa, BufferObjectProperty::DataType source, BufferObjectProperty::DataType dest, int count );//���buffer������ count��ÿһ������float������
	public:
		void ReserveBuffer( uint size );//����buffer
		void ReleaseBuffer();
	public:
		//-------------------------------------------------------------------------------------------------------
		template<typename T>
		void SetVertexType( Attributes::ShaderAttributes sa, BufferObjectProperty::DataType source, BufferObjectProperty::DataType dest )//��������ѹ���������������͵����ݣ���������
		{
			_SetVertexType( sa, source, dest, T::Size() );
		}
		//-------------------------------------------------------------------------------------------------------
		void PushVertexData( Attributes::ShaderAttributes sa, const Volume& data )
		{
			if ( m_nVertexCount >= m_nReserveVertexCount )
			{
				ReserveBuffer( m_nReserveVertexCount + VC_RESERVE_BUFFER_SIZE );
			}
			PushVertexDataFast( sa, data );
		}
		//-------------------------------------------------------------------------------------------------------
		void PushVertexDataFast( Attributes::ShaderAttributes sa, const Volume& data )
		{
			VertexPusher* pusher = m_VertexPusherVector[sa];
			ASSERT( data.Count() == pusher->Count );
			pusher->CompressPtr( data.Data(), &m_Buffer[ pusher->IndicesCount*m_nChunkStride+pusher->PointerStride], pusher->Count, pusher->Bytesize );
			++ pusher->IndicesCount;
			//m_nVertexCount = Math::GetMax( m_nVertexCount, pusher->IndicesCount );//�ҵ�������ֵ�������ֵ�ǵ�ǰ��������
			m_nVertexCount = pusher->IndicesCount;//�ǰ�ȫ�����������������ݶ�ʧ��ȱʧ��������push��ʱ�������ݰ�ȫ��
			m_FlushInterval.m_y = m_nVertexCount;
		}
		//-------------------------------------------------------------------------------------------------------
		void ChangeVertexData( Attributes::ShaderAttributes sa, uint index, const Volume& data )
		{
			VertexPusher* pusher = m_VertexPusherVector[sa];
			ASSERT( data.Count() == pusher->Count );
			pusher->CompressPtr( data.Data(), &m_Buffer[ index*m_nChunkStride+pusher->PointerStride], pusher->Count, pusher->Bytesize );
		}
	public:
		BOHGE_FORCEINLINE const void* GetBufferData() const
		{
			return &m_Buffer[0];
		}
		BOHGE_FORCEINLINE const void* GetBufferData( uint vertexIndex ) const
		{
			return &m_Buffer[m_nChunkStride * vertexIndex ];
		}
		BOHGE_FORCEINLINE const void* GetReflushBufferData() const
		{
			return &m_Buffer[ m_nChunkStride * m_FlushInterval.m_x ];
		}
		BOHGE_FORCEINLINE uint GetVertexStride() const
		{
			return m_nChunkStride;
		}
		BOHGE_FORCEINLINE uint GetVertexSize() const
		{
			return m_nChunkStride;
		}
		BOHGE_FORCEINLINE uint GetVertexCount() const
		{
			return m_nVertexCount;
		}
		BOHGE_FORCEINLINE const VertexStreamLayout& GetLayout() const
		{
			return m_Layout;
		}
		BOHGE_FORCEINLINE const Buffer& GetBufferArray() const
		{
			return m_Buffer;
		}
		BOHGE_FORCEINLINE bool hasVertex( Attributes::ShaderAttributes sa )
		{
			return NULL != m_VertexPusherVector[sa];
		}
		BOHGE_FORCEINLINE void SetReflushInterval( int begin, int end )
		{
			m_FlushInterval.m_x = begin;
			m_FlushInterval.m_y = end;
		}
		BOHGE_FORCEINLINE const vector2d& GetReflushInterval() const
		{
			return m_FlushInterval;
		}
	};
}
