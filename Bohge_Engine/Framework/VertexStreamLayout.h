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
#include "ShaderAttributes.h"



#include <EASTL/vector.h>
#include <EASTL/list.h>

namespace BohgeEngine
{
	//-------------------------------------------------------------------
	class VertexStreamLayout	//����Ĳ��ַ�ʽ��ʹ��Vertex�������ֱ�����
	{
	public:
		#pragma pack(push,1)
		class Layout
		{
		private:
			Attributes::ShaderAttributes	m_eAttributes;//���������
			BufferObjectProperty::DataType	m_eDataType;//�������ݵ�����
			bool							m_isNormalize;//�Ƿ�淶���ģ�һ��Ϊfalse
			byte							m_uDataCount;//ÿ���������ݵĸ���
			byte							m_uStride;//ÿ�����ݶε�biteƫ����
			byte							m_uOffset;//ÿ�����ݶε���ʼ��ַ
		public:
			Layout()
				:m_eAttributes((Attributes::ShaderAttributes)-1),
				m_eDataType((BufferObjectProperty::DataType)-1),
				m_isNormalize(false),
				m_uDataCount(0),
				m_uStride(0),
				m_uOffset(0)
			{
			}
			Layout( Attributes::ShaderAttributes attr, BufferObjectProperty::DataType dest, byte count, byte offset )
				:m_eAttributes(attr),
				m_eDataType(dest),
				m_uDataCount(count),
				m_isNormalize(false),
				m_uStride(0),
				m_uOffset( offset )
			{
				ASSERT( 0 != count );
				switch ( dest )
				{
				case BufferObjectProperty::DT_FLOAT: m_uStride = count * sizeof(float); m_isNormalize = false; break;
				case BufferObjectProperty::DT_HALF_FLOAT: m_uStride = count * sizeof(short); m_isNormalize = false; break;
				case BufferObjectProperty::DT_INT_8_8_8_8: m_uStride = sizeof(int); m_isNormalize = true; break;
				case BufferObjectProperty::DT_UINT_8_8_8_8: m_uStride = sizeof(int); m_isNormalize = true; break;
				case BufferObjectProperty::DT_INT_2_10_10_10: m_uStride = sizeof(int); m_isNormalize = true; break;
				case BufferObjectProperty::DT_UINT_10_10_10_2: m_uStride = sizeof(int); m_isNormalize = true; break;
				default: ASSERT(false && "Unkown vertex data type !\n");
				}
			}
		public:
			BOHGE_FORCEINLINE bool isActive()
			{
				return 0 != m_uDataCount;
			}
			BOHGE_FORCEINLINE Attributes::ShaderAttributes GetAttributes() const
			{
				return m_eAttributes;
			}
			BOHGE_FORCEINLINE byte DataCount() const
			{
				return m_uDataCount;
			}
			BOHGE_FORCEINLINE BufferObjectProperty::DataType DataType() const
			{
				return m_eDataType;
			}
			BOHGE_FORCEINLINE bool isNormalize() const
			{
				return m_isNormalize;
			}
			BOHGE_FORCEINLINE byte Stride() const
			{
				return m_uStride;
			}
			BOHGE_FORCEINLINE byte ByteSize() const//��ǰlayout�Ķ�������byte��Сֵ
			{
				return m_uStride;
			}
			BOHGE_FORCEINLINE byte Offset() const
			{
				return m_uOffset;
			}
		};
		#pragma pack(pop)
	private:
		typedef eastl::vector<Layout*>	LayoutVector;
		typedef eastl::list<Layout> LayoutList;//Ϊ�˿��ٵ�����Ⱦ�����ﻹ����list����
	private:
		LayoutVector		m_LayoutArray;
		LayoutList			m_LayoutList;
		uint				m_uStride;
	public:
		VertexStreamLayout(void)
			:m_uStride(0)
		{
			m_LayoutArray.resize( Attributes::ATTRIBUTE_COUNT, NULL );
		}
		VertexStreamLayout( const VertexStreamLayout& rhs )
		{
			m_LayoutArray.resize( Attributes::ATTRIBUTE_COUNT, NULL );
			m_uStride = rhs.m_uStride;
			for ( int i = 0 ; i < Attributes::ATTRIBUTE_COUNT; ++ i )
			{
				if ( rhs.m_LayoutArray[i] )
				{
					m_LayoutArray[i] = NEW Layout( *rhs.m_LayoutArray[i] );
					m_LayoutList.push_back( *m_LayoutArray[i] );
				}
			}
		}
		~VertexStreamLayout(void)
		{
			for ( int i = 0 ; i < Attributes::ATTRIBUTE_COUNT; ++ i )
			{
				SAFE_DELETE( m_LayoutArray[i] );
			}
		}
	public:
		//����һ������
		BOHGE_FORCEINLINE void SetVertexLayout( Attributes::ShaderAttributes attr, BufferObjectProperty::DataType dest, byte size )
		{
			m_LayoutArray[attr] = NEW Layout(attr,dest,size,m_uStride);
			m_uStride += m_LayoutArray[attr]->Stride();
			m_LayoutList.push_back( *m_LayoutArray[attr] );
		}
		BOHGE_FORCEINLINE const Layout& GetVertexLayout(  Attributes::ShaderAttributes attr ) const
		{
			return *m_LayoutArray[attr];
		}
		BOHGE_FORCEINLINE const eastl::list<Layout>* GetActivedLayoutList() const
		{
			return &m_LayoutList;
		}
	};
	typedef eastl::list<VertexStreamLayout::Layout> LayoutList;
}