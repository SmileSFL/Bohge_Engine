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
#include "Framework/ShaderSource.h"
#include "ShaderSegment.h"

#include <EASTL/string.h>
#include <EASTL/list.h>
#include <EASTL/vector.h>
#include <EASTL/map.h>

//���complier����д�Ĳ��ã�̫���ָ����໥���úʹ��ݣ�
//̫���Ī���ĳ�Ա��������ʱ��Ҫ�ع�����
namespace LuaMaterialSystemPlugin
{
	class ShaderSegment;
	class ShaderAssembler
	{
	private:
		class ParameterNode //ÿһ��Ĳ����ڵ�
		{
		private:
			eastl::string									m_VaryingName;//�������ֻ��������һ��varying��ʱ����Ч
			const BohgeEngine::ShaderParameter*			m_pFragmentNeeder;//�������ֻ��������һ��varying��ʱ����Ч
			const BohgeEngine::ShaderParameter*			m_pParameter;//��¼����
			ShaderSegment*								m_pProvider;//�������ṩ�ߣ������root�㣬��û���ṩ�ߣ�����null
			eastl::list<ShaderSegment*>					m_pParamNeeders;//��Ҫ���������������
		public:
			ParameterNode( const BohgeEngine::ShaderParameter* sp, ShaderSegment* provider );//����ط������������������ṩ��
			void FixParametersName( const eastl::string& add );//�޸Ĳ����������ظ�
			BOHGE_FORCEINLINE void HaveNeeder( ShaderSegment* needer )//���������������
			{
				m_pParamNeeders.push_back( needer );
			}
			BOHGE_FORCEINLINE void HaveProvider( ShaderSegment* provider )//���������������
			{
				m_pProvider = provider;
			}
			BOHGE_FORCEINLINE const BohgeEngine::ShaderParameter* GetParameter() const
			{
				return m_pParameter;
			}
			BOHGE_FORCEINLINE ShaderSegment* GetProvider()
			{
				return m_pProvider;
			}
			BOHGE_FORCEINLINE void SetVaryingName( const eastl::string& name )
			{
				m_VaryingName = name;
			}
			BOHGE_FORCEINLINE const eastl::string& GetVaryingName()
			{
				return m_VaryingName;
			}
			BOHGE_FORCEINLINE void SetFragmentNeeder( const BohgeEngine::ShaderParameter* needer )
			{
				m_pFragmentNeeder = needer;
			}
			BOHGE_FORCEINLINE const BohgeEngine::ShaderParameter* GetFragmentNeeder()
			{
				return m_pFragmentNeeder;
			}
		};
		class ParameterLayer//�����㣬shader���Ⱥ�˳��Ĺ�ϵ�����ﰴ���Ⱥ�˳��ֲ�
		{
		public:
			typedef eastl::map< BohgeEngine::ShaderParameter::InputsType, ParameterNode* > NodeMap;
		private:
			NodeMap	m_ParameterNodeMap;//��һ����������ȫ������
		public:
			~ParameterLayer(void);
		public:
			ParameterNode* InsertParameter( const BohgeEngine::ShaderParameter* sp, ShaderSegment* provider );//����һ�����������������ǲ������ṩ�⣬NULLΪû���ṩ��
			ParameterNode* hasProvider( const BohgeEngine::ShaderParameter::InputsType& it );//�Ƿ���it���͵����
			void FixParametersName( const eastl::string& add );//�޸Ĳ����������ظ�
			eastl::string AsVertexParameter( BohgeEngine::ShaderSource& shader ) const;//�������shader�Ĳ�����˳���¼ȫ���Ĳ���
			eastl::string AsFragmentParameter( BohgeEngine::ShaderSource& shader ) const;//�������shader�Ĳ�����˳���¼ȫ���Ĳ���
			eastl::string AsVarying() const;//����varying�ַ���
			eastl::string AsVaryingEquation() const;//��vs�϶�varying���и�ֵ�ĵ�ʽ
			eastl::string AsEquaToVarying( ) const;//��ps�ϵ�ʽ�ر��ر���
			BOHGE_FORCEINLINE NodeMap& GetParameters()
			{
				return m_ParameterNodeMap;
			}
			BOHGE_FORCEINLINE bool isInlcude( const BohgeEngine::ShaderParameter::InputsType& it ) const
			{
				NodeMap::const_iterator node = m_ParameterNodeMap.find( it );
				if ( m_ParameterNodeMap.end() != node )
				{
					return true;
				}
				return false;
			}
		};
	private:
		typedef eastl::vector< ParameterLayer >		ParameterLayers;
	public:
		ShaderAssembler(void);
		~ShaderAssembler(void);
	private:
		void _ComposeFragment( const ParameterLayer& root, ParameterLayer& varying, const Segments& ps, BohgeEngine::ShaderSource& shader );
		void _ComposeVertex( const ParameterLayer& root, ParameterLayer& varying, const Segments& vs, BohgeEngine::ShaderSource& shader );
		void _FixName( ParameterLayers& layer );
		void _LinkVaryingRoute( ParameterLayers& vs_layer, ParameterLayer& ps_root, ParameterLayer& varying );
		void _LinkParameterRoute( const Segments& vs, ParameterLayers& layer );//��������������ϵ
	public:
		void CompileShader( const Segments& vs, const Segments& ps, BohgeEngine::ShaderSource& shader );
	};
}
