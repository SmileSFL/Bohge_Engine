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
#include "Framework/ShaderParameter.h"

#include <EASTL/map.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>


namespace LuaMaterialSystemPlugin
{
	class ShaderLibrary;
	//����ഫ�ݽ���û�д����Ƭ�����ͣ����ⲿ��Ҫʹ�õ�ʱ��
	//����ShaderLibrary����Ϊ��ʶ������ݣ������ʹ�þ���ԭʼ�ı�
	class ShaderSegment
	{
	private:
		bool							m_isOriginal;//Ƭ���Ƿ���ԭʼ�������������
		eastl::string						m_SegmentName;//Ƭ������
		eastl::string						m_SegmentCode;//Ƭ�ϴ���
		eastl::string						m_Function;//Lua������
		BohgeEngine::ParameterMap		m_InputParameter;//����Ĳ���
		BohgeEngine::ParameterMap		m_OutputParameter;//����Ĳ���
	public:
		ShaderSegment( const eastl::string& name, const eastl::string& code );
		ShaderSegment( const ShaderSegment& ss );
		~ShaderSegment(void);
	private:
		void _Docopy( const ShaderSegment& ss );
		void _ReadParameter( ShaderLibrary& host, BohgeEngine::ParameterMap& into, const char* which );
	public:
		void operator = ( const ShaderSegment& ss );
		void ReleaseResource();//�ͷ�ȫ���Լ��ص�shader��
		void ProcessSegment( ShaderLibrary& host );//��Ƭ��Ϊԭʼ���ݵ�ʱ�򣬽��д���
		void RenameInputParameter( const BohgeEngine::ShaderParameter::InputsType& ty, const eastl::string& to );
		void RenameOutputParameter( const BohgeEngine::ShaderParameter::InputsType& ty, const eastl::string& to );
		bool isNeedInput( const BohgeEngine::ShaderParameter::InputsType& ty );
		bool isProvider( const BohgeEngine::ShaderParameter::InputsType& ty );
	public:
		BOHGE_FORCEINLINE bool isOriginal() const
		{
			return m_isOriginal;
		}
		BOHGE_FORCEINLINE const eastl::string& GetName() const
		{
			return m_SegmentName;
		}
		BOHGE_FORCEINLINE const eastl::string& GetCode() const
		{
			return m_SegmentCode;
		}
		BOHGE_FORCEINLINE const BohgeEngine::ParameterMap& GetSegmentInput() const
		{
			return m_InputParameter;
		}
		BOHGE_FORCEINLINE const BohgeEngine::ParameterMap& GetSegmentOutput() const
		{
			return m_OutputParameter;
		}
	};

	typedef eastl::vector< ShaderSegment* > Segments;
}

