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
#include "RenderTargetProperty.h"
#include "RenderTargetEntity.h"
#include "IFunctionInvoker.h"
#include "Object.hpp"


#include <EASTL/string.h>
namespace BohgeEngine
{
	class ScriptEntity;
	class IAsyncSource;
	class RenderObjectEntity;
	class BOHGE_FRAMEWORK PostEffect : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR( PostEffect );
	private:
		typedef eastl::list< RenderTargetEntity* > RenderTargetList;
		typedef eastl::list< RenderObjectEntity* > RenderObjectList;
	private:
		RenderTargetList		m_RenderTargetList;
		RenderObjectList		m_RenderObjectList;
		ScriptEntity*			m_pScript;
		IFunctionInvoker*		m_pProcess;
		IFunctionInvoker*		m_pResize;
		FunctionPtr				m_ResizeFunction;
		uint					m_Queue;
		byte					m_ResourceCount;
	public:
		PostEffect(void);
		virtual ~PostEffect(void);
	public:
		void CreatePostEffect( const eastl::string& path );
		void OnResizeview( const ViewResolution& size );
		void OnScriptLoaded( const SmartPtr<IAsyncSource>& sou );
		void OnResourceLoaded( const SmartPtr<IAsyncSource>& sou );
		RenderObjectEntity* CreateRenderObject( const eastl::string& path );//���ú���Ĳ���
		RenderTargetEntity* CreateRenderTarget( RenderTargetProperty::SwapTarget st, const vector2d& size );//����һ��RT
	public:
		BOHGE_FORCEINLINE uint GetQueue()
		{
			return m_Queue;
		}
		BOHGE_FORCEINLINE void ProcessPostEffect( RenderTargetEntity* org, RenderTargetEntity* scene, RenderTargetEntity* out )
		{
			m_pProcess->Invoke( org, scene, out );
		}
	};
}