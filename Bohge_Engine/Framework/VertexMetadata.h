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
#include "VertexStream.h"
#include "SmartPtr.hpp"
#include "IMetadata.h"

namespace BohgeEngine
{
	//ͨ���������صķ�ʽ����������Դ
	class BOHGE_FRAMEWORK VertexMetadata : public IMetadata
	{
		RTTI_ABSTRACT_DRIVER_TYPE_DECLEAR( VertexMetadata, IMetadata )
	private:
		bool									m_isManageRelease;
		VertexStream*							m_rpStream;
		BufferObjectProperty::MemoryUseage		m_eUseage;
	public:
		VertexMetadata(BufferObjectProperty::MemoryUseage mu, bool mrel );
		virtual ~VertexMetadata();
	private:
		virtual VertexStream* _GetStream ( ) = 0;
	private:
		virtual void* _ReturnMetadata( );
	public:
		virtual void ProcessMetadata();//����ԭʼ��Դ
		virtual void ReleaseMetadate();
	public:
		BOHGE_FORCEINLINE BufferObjectProperty::MemoryUseage GetMemoryUseage()
		{
			return m_eUseage;
		}
	};



	//���ص�������Դ
	class LoadedVertexMetadata : public VertexMetadata
	{
		RTTI_DRIVER_TYPE_DECLEAR( LoadedVertexMetadata, IMetadata )
	private:
		VertexStream*		m_rpStream;
		uint				m_HashCode;
	public:
		LoadedVertexMetadata( BufferObjectProperty::MemoryUseage mu, VertexStream* ptr, uint hash );
		~LoadedVertexMetadata( void );
	private:
		virtual VertexStream* _GetStream ( );
	public:
		virtual void GetIdentifier( eastl::vector<byte>& bytes ) const;
	};
}
