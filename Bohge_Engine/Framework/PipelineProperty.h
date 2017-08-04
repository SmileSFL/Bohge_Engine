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
#include "Object.hpp"



#include <EASTL/vector.h>
#include <EASTL/list.h>
#include <EASTL/map.h>

namespace BohgeEngine
{
	class PostEffect;
	class LightComponent;
	class RenderComponent;
	class PipelineProperty : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR( PipelineProperty );
	private:
		PipelineProperty(void){}
		~PipelineProperty(void){}
	public:
		typedef eastl::vector< RenderComponent* >	VisableRender;
		typedef eastl::vector< LightComponent* >	VisableLight;

		enum PiplineType
		{
			PLT_FORWARD_SINGLE_LIGHT = 0,//ǰ���͵�����Ч��Դ
			PLT_FORWARD_MULTI_LIGHT,//ǰ���Ͷ����Ч��Դ
			PLT_DEFFERRED_LIGHT,//�ӳ���Ⱦ
		};
		enum PassType//Ϊ�ӳ���Ⱦ��׼��
		{
			PT_LIGHTING_AMBIENT = 0,//��������
			PT_LIGHTING_DIRECTION,//ƽ�й�
			PT_LIGHTING_POINT,//���
			PT_LIGHTING_SPOT,//�۹��
			PT_UNIVERSAL_DEPTH,//������Ȼ���
			PT_UNIVERSAL_NORMAL,//��Ⱦ���ߵ�RT
			PT_UNIVERSAL_DECAL,//���������պ������ϣ�
			PT_UNIVERSAL_MULTI_RENDER_TARGET,//����ȾĿ����Ⱦ���ṩ�ӳ���Ⱦʹ��

			PT_UNIVERSAL_POST_EFFECT,//����

			PT_PASS_TYPE_COUNT,
		};
		enum ActivePassType
		{
			APT_LIGHTING_ALL					= 1 << 0L,//��ȫ������
			APT_UNIVERSAL_DEPTH					= 1 << 1L,//�򿪶�����Ⱦ���
			APT_UNIVERSAL_NORMAL				= 1 << 2L,//�򿪶�����Ⱦ����
			APT_UNIVERSAL_DECAL					= 1 << 3L,//����������
			APT_UNIVERSAL_MULTI_RENDER_TARGET	= 1 << 4L,//��mrt��Ⱦ
			APT_UNIVERSAL_POST_EFFECT			= 1 << 5L,//�򿪺���
		};

		enum LightType
		{
			LT_AMBIENT = 0,//�������ֵҪ��PassType��Ӧ
			LT_DIRECTIONAL,
			LT_POINT,
			LT_SPOT,
		};

		typedef eastl::vector< PassType >				ActivePassTypeArray;//��Ч��pass����
		typedef eastl::multimap< unsigned int, PostEffect* >	PostEffectMap;
	};
}