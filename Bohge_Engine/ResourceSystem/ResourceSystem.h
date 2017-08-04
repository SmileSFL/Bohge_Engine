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
#include "Framework/IResourceSystem.h"

#include <EASTL/string.h>
#include <EASTL/list.h>
#include <EASTL/map.h>

namespace BohgeEngine
{
	class IMonopolySource;
	class ISharedSource;
	class ISharedResource;
	class IThreadMutex;
	class IJobDispatcher;
}

namespace ResourceSystemPlugin
{
	class ResourceSystem : public BohgeEngine::IResourceSystem
	{
	private:
		typedef eastl::map< intptr_t, BohgeEngine::SmartPtr<BohgeEngine::ISharedSource> > SourceMap;
	private:
		struct SharedResourcePair
		{
			BohgeEngine::ISharedResource*	Resource;
			BohgeEngine::SmartPtr<BohgeEngine::ISharedSource>	m_RootSource;//Ψһ������������صģ�������һЩ�����ڼ��ع�����
			SourceMap						m_NeederMap;
			SourceMap						m_WaitingMap;
			bool							m_isSourceLoaded;
			SharedResourcePair():Resource(NULL),m_isSourceLoaded(false){}
		};
	private:
		typedef eastl::map< uint, SharedResourcePair* > IResourcePairMap;//��Դ��map
		typedef eastl::list< BohgeEngine::SmartPtr<BohgeEngine::IAsyncSource> > ISourceList;
		typedef eastl::list< SharedResourcePair* > ResourcePairList;
	private:
		IResourcePairMap				m_IResourcePairMap[BohgeEngine::IResourceProperty::SST_COUNT];
		ISourceList						m_SharedRenderLoadedSource;//�Ѿ�������ϵȴ�make�Ķ���
		ISourceList						m_SharedLogicLoadedSource;//�Ѿ�������ϵȴ�make�Ķ���
		ISourceList						m_MonopolyRenderLoadedSource;
		ISourceList						m_MonopolyLogicLoadedSource;
		ResourcePairList				m_RenderReleaseResource;//��Ҫ��������Դ
		ResourcePairList				m_LogicReleaseResource;//��Ҫ��������Դ
		BohgeEngine::IThreadMutex*		m_pMutex;
		BohgeEngine::IJobDispatcher*	m_pIJobDispatcher;//�����߳�
	public:
		ResourceSystem(void);
		virtual ~ResourceSystem(void);
	private:
		void _ProcessSharedSource( ISourceList& que );
		void _ProcessMonopolySource( ISourceList& que );
		void _DoReleaseResource( ResourcePairList& que );
		
		void _LoadSharedSource( BohgeEngine::SmartPtr<BohgeEngine::ISharedSource> source );
		void _LoadMonoPolySource( BohgeEngine::SmartPtr<BohgeEngine::IMonopolySource> source );
		void _UnloadSharedSource( BohgeEngine::SmartPtr<BohgeEngine::ISharedSource> source );

		void _MonopolySourcrLoadedCallBacke( const BohgeEngine::SmartPtr<BohgeEngine::IMonopolySource>& source );
		void _SharedSourcrLoadedCallBacke( const BohgeEngine::SmartPtr<BohgeEngine::ISharedSource>& source );
	public://ע����¼�����
		void OnFrameworkEntry( float time, BohgeEngine::Framework& framework ); //ע��ϵͳ����rtti
		void OnFrameworkRenderExit( float time, BohgeEngine::Framework& framework );
		void OnFrameworkLogicExit( float time, BohgeEngine::Framework& framework );
		void OnFrameworkBeginUpdata( float time, BohgeEngine::Framework& framework );
		void OnFrameworkBeginRender( float time, BohgeEngine::Framework& framework );
	public:
		void OnSourceLoadedCallBack( const BohgeEngine::SmartPtr<BohgeEngine::IAsyncSource>& source );//���������첽�̼߳�����Ϻ󣬻�����������������push�������У��ȴ������߳���������Դ
	public:
		virtual void RegistEvent( BohgeEngine::Framework& framework ); //ע���¼�
		virtual void LoadResource( BohgeEngine::SmartPtr<BohgeEngine::IAsyncSource> source );//������Դ
		virtual void UnloadResource( BohgeEngine::SmartPtr<BohgeEngine::IAsyncSource> source );//ж����Դ
		virtual BohgeEngine::ILoader* LoaderFactory( BohgeEngine::IResourceProperty::SourceLoaderType slt );//������Դ������
		virtual void RecycleBin( BohgeEngine::ILoader* ptr );//������Դ
	};

}