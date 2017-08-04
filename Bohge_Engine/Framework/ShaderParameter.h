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
#include "Plugindefine.h"
#include "Predefine.h"



#include <EASTL/string.h>
#include <EASTL/map.h>
#include <EASTL/list.h>

namespace BohgeEngine
{
	class ShaderLibrary;
	class BOHGE_FRAMEWORK ShaderParameter//����಻����ָ�룬��ָ��Ļ�����Ҫʵ�ֿ�������͸�ֵ����
	{
	public:
		enum FloatPrecision
		{
			FP_ERRORCODE = 0,//Lua�ò������ݵ�ʱ�����������Ϊ0
			FP_NONE,
			FP_LOW,
			FP_MEDIUM,
			FP_HIGH,
		};
		enum VariablesType
		{
			VT_ERRORCODE = 0,//Lua�ò������ݵ�ʱ�����������Ϊ0
			VT_FLOAT,
			VT_VEC2,
			VT_VEC3,
			VT_VEC4,
			VT_VEC2_ARRAY,
			VT_VEC3_ARRAY,
			VT_VEC4_ARRAY,
			VT_MAT3,
			VT_MAT4,
			VT_TEXTURE1D,
			VT_TEXTURE2D,
			VT_TEXTURE3D,
			VT_TEXTURECUBE,

			VT_COUNT,
		};
		enum InputsType//����Ĳ�������
		{
			//��������
			IT_ERRORCODE = 0,//Lua�ò������ݵ�ʱ�����������Ϊ0
			IT_LOCALSPACE_POSITION,//ԭʼλ��
			IT_LOCALSPACE_COORDNATE,//ԭʼ��������,һ��ʹ��������������һ��������������
			IT_LOCALSPACE_NORMAL,//ԭʼ����
			IT_LOCALSPACE_COLOR,//�����������ɫ
			IT_LOCALSPACE_TANGENT,//ԭʼ����
			IT_LOCALSPACE_BINORMAL,//ԭʼ������
			IT_LOCALSPACE_BONE_INEX,//ԭʼ��������
			IT_LOCALSPACE_BONE_WEIGHT,//ԭʼ����Ȩ��

			IT_WORLDSPACE_POSITION,//���������µ�λ��
			IT_WORLDSPACE_NORMAL,//���������µķ���
			IT_WORLDSPACE_TANGENT,//���������µ�����
			IT_WORLDSPACE_BINORMAL,//���������µĸ�����
			IT_WORLDSPACE_VIEWDIRECTION,//���������µ��Ӿ����߷���

			IT_SCREENSPACE_POSITION,//��Ļ�ռ�λ��[-1,1]
			IT_SCREENSPACE_COORDNATE,//��Ļ�ռ��������꣬����������Ļ[0,1]
			IT_SCREENSPACE_NORMAL,//��Ļ�ռ�ķ��ߣ�һ��û��
			IT_SCREENSPACE_TANGENT,//��Ļ�ռ�����ߣ�һ��û��
			IT_SCREENSPACE_BINORMAL,//��Ļ�ռ�ĸ����ߣ�һ��û��

			IT_WORLDSPACE_LIGHT_DISTANCE,//��Դ�Ͷ���ľ���
			IT_WORLDSPACE_DEPTH,//���

			IT_EMITTER_OFFSET,//���ӵĳߴ�ƫ��
			IT_EMITTER_LIFE,//������������
			IT_EMITTER_BORN,//���ӳ���ʱ��
			IT_EMITTER_AGE,//���ӵ�����ʱ��
			IT_EMITTER_SPEED,//�����ٶ�
			IT_EMITTER_ACCELERATION,//���Ӽ��ٶ�
			IT_EMITTER_SIZE,//���ӳߴ�
			IT_EMITTER_SIZE_CURVATURE,//���ӳߴ�����
			IT_EMITTER_COLOR,//��ɫ�仯
			IT_EMITTER_COLOR_CURVATURE,//��ɫ�仯����
			IT_EMITTER_SPIN,//����

			IT_USER_ATTRIBUTE_0,//�Զ��嶨����
			IT_USER_ATTRIBUTE_1,
			IT_USER_ATTRIBUTE_2,
			IT_USER_ATTRIBUTE_3,
			IT_USER_ATTRIBUTE_4,
			IT_USER_ATTRIBUTE_5,
			IT_USER_ATTRIBUTE_6,
			IT_USER_ATTRIBUTE_7,

			//ϵͳ�Ĵ���
			IT_SYSTEM_TIME,//��Ⱦ�߳������������ڵ�ʱ��
			IT_SYSTEM_TIME_SPAN,//��Ⱦ�̵߳�ǰ֡��ʱ��

			//ģ�ͼĴ���
			IT_LOCALSPACE_REAL_ARRAY,//��������
			IT_LOCALSPACE_DUAL_ARRAY,//��������
			IT_LOCALWORLD_TRANSFORM,//���ص�����ı任����
			IT_LOCALWORLD_ROTATION,//���ص���ת����
			IT_LOCALSCREEN_TRANSVIEWPROJ,//���ص���Ļ��mvp

			//������Ĵ�������
			IT_CAMERA_WORLDROTATION,//�������ת
			IT_CAMERA_WORLDPOSITION,//�����λ��
			IT_CAMERA_WORLDDIRECTION,//���������
			IT_CAMERA_VIEW,//�����view����
			IT_CAMERA_PROJECTION,//�����ͶӰ
			IT_CAMERA_VIEWPROJ,//�����vp����
			IT_CAMERA_LINERPARAM,//��������Ի�����

			//��Դ������
			IT_LIGHT_POSITION,
			IT_LIGHT_COLOR,
			IT_AMBIENT_COLOR,
			IT_LIGHT_ANGLE,//�۹�ƽǶ�
			IT_LIGHT_INNER_DIFF_INV,//�ǲ�
			IT_LIGHT_RANGE_INV,//�������
			IT_LIGHT_ATTENUATION,//˥��
			IT_LIGHT_VERTEX_DIRECTION,//�����������Ĺ��շ���
			IT_LIGHT_GIVEN_DIRECTION,//�ⲿ���ݹ��շ���

			//���ʽ��ܹ���ǿ��
			IT_MATERIAL_AMBIENT,//������
			IT_MATERIAL_DIFFUSE,//������
			IT_MATERIAL_SPECULAR,//����
			IT_MATERIAL_SPECULAR_LEVEL,//����ǿ��
			IT_MATERIAL_SHININESS,//�������

			//���պͲ��ʵĸ����Ͳ��������ǰ����ݶ���ˣ��ṩpsʹ�ã�һ��ʹ���������
			IT_LIGHT_MATERIAL_AMBIENT,//������
			IT_LIGHT_MATERIAL_LIGHT,//��������ɫ
			IT_LIGHT_MATERIAL_SPECULAR,//����

			//������ɫ��������
			IT_LIGHTING_DIFFUSE,//�����������ɫ
			IT_LIGHTING_SPECULAR,//�߹������ɫ
			IT_SURFACE_COLOR,//������ɫ

			//����
			IT_TEXTURE_AMBIENT,//������ͼ
			IT_TEXTURE_DIFFUSE,//��������
			IT_TEXTURE_SPECULAR,//������ɫ
			IT_TEXTURE_SPLEVEL,//����ȼ�
			IT_TEXTURE_GLOSSINESS,//����
			IT_TEXTURE_ILLUMINATION,//�Է���
			IT_TEXTURE_OPACITY,//͸����ͼ
			IT_TEXTURE_FITER,//������ͼ
			IT_TEXTURE_BUMP,//������ͼ
			IT_TEXTURE_REFLECTION,//������ͼ
			IT_TEXTURE_REFRACTION,//������ͼ
			IT_TEXTURE_DISPLACEMENT,//�Ӳ���ͼ
			IT_TEXTURE_TERRAIN_WEIGHT,//���ε���ͼ
			IT_TEXTURE_TERRAIN_DETAL,
			IT_TEXTURE_TERRAIN_BASE,
			IT_TEXTURE_TERRAIN_R,
			IT_TEXTURE_TERRAIN_G,
			IT_TEXTURE_TERRAIN_B,
			IT_TEXTURE_USER0,//�û��Զ����
			IT_TEXTURE_USER1,//�û��Զ����
			IT_TEXTURE_USER2,//�û��Զ����
			IT_TEXTURE_USER3,//�û��Զ����
			IT_TEXTURE_USER4,//�û��Զ����
			IT_TEXTURE_USER5,//�û��Զ����
			IT_TEXTURE_USER6,//�û��Զ����
			IT_TEXTURE_USER7,//�û��Զ����

			//��ɫ����
			IT_COLOR_RED,
			IT_COLOR_GREEN,
			IT_COLOR_BLUE,
			IT_COLOR_ALPHA,

			//�û��Զ��������
			IT_MATERIAL_USER_0,//�û��Զ����
			IT_MATERIAL_USER_1,//�û��Զ����
			IT_MATERIAL_USER_2,//�û��Զ����
			IT_MATERIAL_USER_3,//�û��Զ����
			IT_MATERIAL_USER_4,//�û��Զ����
			IT_MATERIAL_USER_5,//�û��Զ����
			IT_MATERIAL_USER_6,//�û��Զ����
			IT_MATERIAL_USER_7,//�û��Զ����
			IT_MATERIAL_USER_8,//�û��Զ����
			IT_MATERIAL_USER_9,//�û��Զ����
		};
	private:
		VariablesType	m_eType;
		FloatPrecision	m_ePrecision;
		InputsType		m_eInputType;
		eastl::string	m_ParamName;//shader�е�����
		eastl::string	m_ArraySize;
	public:
		ShaderParameter( const InputsType& it, const FloatPrecision& fp, const VariablesType& vt, const eastl::string& name );
		ShaderParameter( const InputsType& it, const FloatPrecision& fp, const VariablesType& vt, const eastl::string& name, const eastl::string& arraysize );
	public:
		eastl::string AsParameterString() const;//����һ��shader�����������߼Ĵ��������ַ���
		eastl::string AsVaryingString( const eastl::string& name ) const;//����һ��������������
		eastl::string AsVariables() const;//���һ������
		eastl::string AsVaryingEquation( const eastl::string& output ) const;//��ֵ��varying������
		eastl::string AsEquaToVarying( const eastl::string& intput ) const;
		bool isUniform() const;
	public:
		BOHGE_FORCEINLINE const eastl::string& GetName() const
		{
			return m_ParamName;
		}
		BOHGE_FORCEINLINE void SetName( const eastl::string& to )
		{
			m_ParamName = to;
		}
		BOHGE_FORCEINLINE const InputsType& GetInputsType() const
		{
			return m_eInputType;
		}
		BOHGE_FORCEINLINE const VariablesType& GetVariableType() const
		{
			return m_eType;
		}
	};


	typedef eastl::map< ShaderParameter::InputsType, ShaderParameter*> ParameterMap;

	struct ShaderParameterInfomation
	{
		ShaderParameter::VariablesType	m_eType;
		ShaderParameter::InputsType		m_eInputType;
		eastl::string						m_ParamName;
		ShaderParameterInfomation( const ShaderParameter::VariablesType& vt, const ShaderParameter::InputsType& it, const eastl::string& name )
			:m_eType(vt),m_eInputType(it),m_ParamName(name){}
	};
	typedef eastl::list< ShaderParameterInfomation > ShaderParameterInfomationList;
}