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
#include "Framework/Framework.h"
#include "Framework/Log.h"


#include "OpenGLGraphicSystem.h"
#include "IndicesBufferResourceGL.h"
#include "VertexBufferResourceGL.h"
#include "TextureResourceGL.h"
#include "ShaderResourceGL.h"
#include "MaterialResourceGL.h"
#include "RenderTargetResourceGL.h"
#include "RenderObjectResourceGL.h"


#include "glsl/glsl_optimizer.h"



#include <EASTL/set.h>

using namespace eastl;
using namespace BohgeEngine;

namespace OpenGLGraphicSystemPlugin
{
	//---------------------------------------------------------------------------------------------------------
	OpenGLGraphicSystem::OpenGLGraphicSystem(void)
		:m_hGLRC(NULL),
		m_hHDC(NULL),
		m_pGlslopt_ctx(NULL),
		m_uTextrueReferenceCount(0)
	{
	}
	//---------------------------------------------------------------------------------------------------------
	OpenGLGraphicSystem::~OpenGLGraphicSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::RegistEvent( BohgeEngine::Framework& framework )
	{
		IGraphicSystem::RegistEvent( framework );
		framework.RegisterEventListener( FrameworkEvent::ET_RENDER_ON_ENTRY, MEMBER_FUNC_PTR( &OpenGLGraphicSystem::OnFrameworkEntry ) );
		framework.RegisterEventListener( FrameworkEvent::ET_RENDER_ON_EXIT, MEMBER_FUNC_PTR( &OpenGLGraphicSystem::OnFrameworkExit ) );
	}
	//-------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::OnFrameworkEntry( float time, BohgeEngine::Framework& framework )
	{
		glEnable(GL_TEXTURE_2D);//Ĭ�ϴ�2D����
		glDisable(GL_DITHER);
		glDepthRangef( 0.0, 1.0 );
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDepthMask(false);
		glDisable(GL_BLEND);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable( GL_POINT_SPRITE );
		m_pGlslopt_ctx = glslopt_initialize( kGlslTargetOpenGL );
	}
	//-------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::OnFrameworkExit( float time, BohgeEngine::Framework& framework )
	{
		glslopt_cleanup( m_pGlslopt_ctx );
		m_pGlslopt_ctx = NULL;
	}
	//---------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::_CreateContext( void* hWindows )
	{
		GLuint PixelFormat; 
		static PIXELFORMATDESCRIPTOR pfd = { 
			sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
			1,                                // �汾�� 
			PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
			PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
			PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
			PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
			32,                               // 32 λ��ɫ��� 
			0, 0, 0, 0, 0, 0,                 // ������ɫλ 
			1,                                // û�з�͸���Ȼ��� 
			0,                                // ������λλ 
			0,                                // ���ۼӻ��� 
			0, 0, 0, 0,                       // �����ۼ�λ 
			24,                               // 24 λ��Ȼ���     
			8,                                // ��ģ�建�� //�Ķ���Ӱ
			0,                                // �޸������� 
			PFD_MAIN_PLANE,                   // ���� 
			0,                                // ���� 
			0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
		};
		m_hHDC = GetDC( *(HWND*)hWindows );

		// ѡ����ʵ�Device Context���ص��ʽ
		if (!(PixelFormat=ChoosePixelFormat(m_hHDC,&pfd)))  // Did Windows Find A Matching Pixel Format?
		{       
			::MessageBox(NULL,TEXT("Can't Find A Suitable PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION );
		}

		// �����µ�Device Context���ص��ʽ
		if(!SetPixelFormat(m_hHDC,PixelFormat,&pfd))   // Are We Able To Set The Pixel Format?
		{
			::MessageBox(NULL,TEXT("Can't Set The PixelFormat."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		}
		// ���ݵ�ǰ��Device Context�õ�rending context
		if (!(m_hGLRC=wglCreateContext(m_hHDC))) // Are We Able To Get A Rendering Context?
		{
			//KillGLWindow();        // Reset The Display
			::MessageBox(NULL,TEXT("Can't Create A GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		}
		// ���õ�ǰDevice context ��rendering context
		if(!wglMakeCurrent(m_hHDC, m_hGLRC))   // Try To Activate The Rendering Context
		{
			//KillGLWindow();        // Reset The Display
			::MessageBox(NULL,TEXT("Can't Activate The GL Rendering Context."),TEXT("ERROR"),MB_OK|MB_ICONEXCLAMATION);
		}

		GLenum err = glewInit(); 
		if (GLEW_OK != err) 
		{ 
			DEBUGLOG("Error: %s\n", glewGetErrorString(err)); 
		} 
		DEBUGLOG("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
		DEBUGLOG("OpenGL version is %s\n", glGetString( GL_VERSION ) );
		//if ( wglSwapIntervalEXT )//������֡�ʻᵼ��hdr�Ĵ���
		//{
		//	wglSwapIntervalEXT(0);
		//}
	}
	//---------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::_SwapBuffer()
	{
		wglMakeCurrent( m_hHDC, m_hGLRC);
		SwapBuffers( m_hHDC );
	}
	//---------------------------------------------------------------------------------------------------------
	void OpenGLGraphicSystem::CheckError()
	{
		GLenum error = glGetError();
		switch(error)
		{
		case GL_NO_ERROR:break;
		case GL_INVALID_ENUM:DEBUGLOG("An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.\n",1);break;
		case GL_INVALID_VALUE:DEBUGLOG("A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.\n",1);break;
		case GL_INVALID_OPERATION:DEBUGLOG("The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.\n",1);break;
		case GL_OUT_OF_MEMORY:DEBUGLOG("There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.\n",1);break;
		}
	}
	//---------------------------------------------------------------------------------------------------------
	BohgeEngine::ISharedResource* OpenGLGraphicSystem::CreateResource( BohgeEngine::IResourceProperty::SharedResourceType type )
	{
		switch( type )
		{
		case IResourceProperty::SRT_TEXTURE: return NEW TextureResourceGL();
		case IResourceProperty::SRT_VERTEXBUFFER: return NEW VertexBufferResourceGL();
		case IResourceProperty::SRT_INDICESBUFFER: return NEW IndicesBufferResourceGL();
		case IResourceProperty::SRT_SHADERPROGRAM: return NEW ShaderResourceGL();
		case IResourceProperty::SRT_MATERIAL: return NEW MaterialResourceGL();
		case IResourceProperty::SRT_RENDERTARGET: return NEW RenderTargetResourceGL();
		case IResourceProperty::SRT_RENDEROBJECT: return NEW RenderObjectResourceGL();
		default: ASSERT(false);
		}
		return NULL;
	}
	//---------------------------------------------------------------------------------------------------------
	eastl::string _GetVariableName( const eastl::string& str, std::size_t begin, std::size_t dir )//�õ�����ȫ��
	{
		size_t spb = begin;
		size_t spe;
		while(true)
		{
			spb += dir;
			if ( !Utility::NotVariablePart( str[spb] ) )
			{
				spe = spb + dir;
				break;
			}
		}
		while(true)
		{
			spe += dir;
			if ( Utility::NotVariablePart( str[spe] ) )
			{
				break;
			}
		}
		return str.substr( (spb < spe ? spb : spe)+1, spb < spe ? spe - spb : spb - spe );
	}
	bool _VariableModifier_Type( eastl::string& str, const eastl::string& vname, const char* modifier, eastl::string& type )//�Ƿ�Ϊĳ���������͵ı���
	{
		size_t start_pos = 0;
		do 
		{
			start_pos = str.find( vname, start_pos );
			if ( start_pos != eastl::string::npos )
			{
				size_t trunk = str.find_last_of( ';', start_pos );
				trunk = trunk != eastl::string::npos ? trunk : 0;
				string substr = str.substr( trunk, start_pos - trunk );
				size_t istype = substr.find( modifier );
				if ( istype != eastl::string::npos )
				{
					type = substr.substr( substr.find_first_of(' ') );
					return true;
				}
				start_pos += vname.size();
			}
		} while ( start_pos != eastl::string::npos );
		return false;
	}
	void _FixAttributeIndexingType( string& str, size_t begin )//�޸�����Attribute������
	{
		set<uint> handled;
		size_t start_pos = begin;
		do 
		{
			start_pos = str.find("[", start_pos);
			if ( start_pos != eastl::string::npos )
			{
				string vbname = _GetVariableName( str, start_pos, -1 );
				if ( handled.end() == handled.find(  Utility::HashCode( vbname ) ) )
				{
					handled.insert( Utility::HashCode( vbname ) );
					string type;
					if ( _VariableModifier_Type(str, vbname, "attribute", type ) )
					{
						string fixtoname = vbname + "_fixed_bohge";
						handled.insert( Utility::HashCode( fixtoname ) );
						string eqution = type + fixtoname + " = " + vbname + ";\r\n";
						Utility::ReplaceAllParamterName( str, vbname, fixtoname, start_pos-vbname.size() );
						str.insert( begin, eqution );
					}
				}
				start_pos += 1;
			}
		} while ( start_pos != eastl::string::npos );
	}
	size_t _FindMainFunction( eastl::string& str )//�ҵ���������
	{
		size_t start_pos = 0;
		do 
		{
			start_pos = str.find("main", start_pos);
			if( start_pos != eastl::string::npos )
			{
				size_t i = -1;
				bool istype = false;
				do 
				{
					istype = ! Utility::NotVariablePart( str[ start_pos + i-- ] );
				} while ( !istype );
				if ( 'd' == str[start_pos + ++i] )
				{
					start_pos = str.find("{", start_pos);
					return start_pos + 1;
				}
			}
			start_pos++;
		} while ( start_pos != eastl::string::npos );
		return eastl::string::npos;
	}
	void OpenGLGraphicSystem::ProcessShader( BohgeEngine::ShaderProperty::ShaderCode sc, eastl::string& code )
	{
		Utility::RemoveTargetString( code, "precision highp float;" );
		Utility::RemoveTargetString( code, "precision mediump float;" );
		Utility::RemoveTargetString( code, "precision lowp float;" );
		Utility::RemoveTargetString( code, "highp " );
		Utility::RemoveTargetString( code, "mediump " );
		Utility::RemoveTargetString( code, "lowp " );
		code.insert(0, "#define	MAXJOINTS	128\n" );
		code.insert(0, "#define	MAXARRAYSIZE	256\n" );
		code.insert(0, "#define	_WINDOWS_\n" );
		glslopt_shader_type type;
		switch( sc )
		{
		case ShaderProperty::SC_VERTEX: type = kGlslOptShaderVertex; break;
		case ShaderProperty::SC_FRAGMENT: type = kGlslOptShaderFragment; break;
		default:ASSERT(false);
		}

		glslopt_shader* shader = glslopt_optimize( m_pGlslopt_ctx, type, code.c_str(), 0 );
		if ( glslopt_get_status(shader) )
		{
			code = glslopt_get_output( shader );
		}
		else
		{
			const char* log = glslopt_get_log( shader );
			DEBUGLOG("Can't optimize shader, caz %s\n", log );
		}
		if ( ShaderProperty::SC_VERTEX == sc )
		{
			size_t mainbegin = _FindMainFunction(code);
			_FixAttributeIndexingType( code, mainbegin );
		}
		glslopt_shader_delete( shader );
	}
	//---------------------------------------------------------------------------------------------------------
	uint OpenGLGraphicSystem::GetMaxUniformArraySize()
	{
		return 256;//�������Ӧ
	}

}