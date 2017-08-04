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
#include "RenderTargetWarp.hpp"
#include "RenderObjectWarp.hpp"
#include "StaticCameraWrap.hpp"
#include "PathMetadataWarp.hpp"
#include "PostEffectWarp.hpp"
#include "FrameworkWrap.hpp"
#include "ICameraWarp.hpp"
#include "NodeWarp.hpp"

//����
#include "IActionSystemWarp.hpp"

//����
#include "IEnvironmentSystemWarp.hpp"

//��ȾAPI
#include "IGraphicSystemWarp.hpp"

//����
#include "IMaterialSystemWarp.hpp"

//�ڴ�
#include "IMemorySystemWarp.hpp"

//�ļ�
#include "IOSystemWrap.hpp"

//����
#include "IPhysicSystemWarp.hpp"

//����
#include "IPipelineSystemWarp.hpp"

//��Ⱦ����
#include "IRenderQueueSystemWarp.hpp"

//��Դϵͳ
#include "IResourceSystemWarp.hpp"

//�ű�
#include "IScriptSystemWrap.hpp"
#include "IFunctionInvokerWrap.hpp"

//����
#include "ISoundSystemWrap.hpp"

//�ı�
#include "ITextSystemWarp.hpp"

//�߳�
#include "IThreadSystemWrap.hpp"

//ʱ��
#include "ITimeSystemWarp.hpp"

//����
#include "IDownloadHandleWarp.hpp"
#include "IPostHandleWarp.hpp"
#include "IBaseHandleWarp.hpp"
#include "IWebSystemWarp.hpp"


//�齨��
#include "ComponentWarp.hpp"
#include "ScriptComponentWarp.hpp"

//������
#include "QuaternionWrap.hpp"
#include "Matrix33Wrap.hpp"
#include "Matrix44Wrap.hpp"
#include "Vector1Wrap.hpp"
#include "Vector2Wrap.hpp"
#include "Vector3Wrap.hpp"
#include "Vector4Wrap.hpp"


namespace BohgeEngine
{
	static void DoRegister( IScriptSystem& sys )
	{
		//���
		Register_ICamera( sys );
		Register_Framework( sys );

		//�����
		Register_StaticCamera( sys );
		//����
		Register_IActionSystem(sys);

		//����
		Register_IEnvironmentSystem(sys);

		//��ȾAPI
		Register_IGraphicSystem(sys);

		//����
		Register_IMaterialSystem( sys );

		//�ڴ�
		Register_IMemorySystem( sys );

		//�ļ�
		Register_IIOSystem( sys );

		//����
		Register_IPhysicSystem( sys );

		//����
		Register_IPipelineSystem(sys );

		//��Ⱦ����
		Register_IRenderQueueSystem(sys);

		//��Դϵͳ
		Register_IResourceSystem(sys);

		//�ű�
		Register_IScriptSystem(sys);
		Register_IFunctionInvoker(sys);

		//����
		Register_ISoundSystem(sys);

		//�ı�
		Register_ITextSystem( sys );

		//�߳�
		Register_IThreadSystem( sys );

		//ʱ��
		Register_ITimeSystem( sys );

		//webϵͳ
		Register_IBaseHandle( sys );
		Register_IPostHandle( sys );
		Register_IDownloadHandle( sys );
		Register_IWebSystem( sys );

		//�ļ�ϵͳ
		Register_IIOSystem( sys );

		//�齨
		Register_Node( sys );
		Register_IPostEffect( sys );
		Register_Component( sys );
		Register_ScriptComponent( sys );

		//ʵ��
		Register_PathMetadata( sys );

		//��Ⱦ
		Register_RenderObjectEntity( sys );
		Register_RenderTargetEntity( sys );

		//��ѧ��
		Register_vector1( sys );
		Register_vector2( sys );
		Register_vector3( sys );
		Register_vector4( sys );
		Register_Quaternion( sys );
		Register_Matrix33(sys);
		Register_Matrix44(sys);

	}
}