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
#include "IResourceProperty.h"
#include "Delegate.hpp"
#include "IMetadata.h"
#include "IJob.h"


namespace BohgeEngine
{
	class IAsyncResource;
	class BOHGE_FRAMEWORK IAsyncSource : public IJob //��Դ��ԭʼ����
	{
		RTTI_ABSTRACT_DRIVER_TYPE_DECLEAR( IAsyncSource, IJob )
	private:
		SmartPtr<IAsyncSource>*							m_pSelfReference;
		ISourceMetadataList*							m_pISourceMetadataList;
		Delegate1<void,const SmartPtr<IAsyncSource>& >*	m_pSourceLoadedCallBack;
		Delegate1<void,const SmartPtr<IAsyncSource>& >*	m_pSourceLoadedDelayDependsCallBack;//�����ӳټ��ص���Դ������ԭʼ��Դ�Ѿ��������
		Delegate1<void,IAsyncResource*>::FunctionType*	m_FuncPtr;
		IResourceProperty::SourceType					m_eSourceType;
		IResourceProperty::DispatchThread				m_eDispatchThread;
		uint											m_nHashCode;
		uint											m_Depends;//�����Դ��������Դ��������Ĭ��Ϊ1����˼�Ƕ��Լ�������
		bool											m_HasDelayDepends;//�����ӳټ��ص���Դ
		bool											m_isHostingFree;//�й�ɾ��
	public:
		IAsyncSource( IResourceProperty::SourceType cst, IResourceProperty::DispatchThread dt, bool hf );
		IAsyncSource( const IAsyncSource& rhs );
		virtual ~IAsyncSource(void);
	private:
		virtual void _DoReleaseUnnecessaryDataAfterLoaded( ) = 0;
	private:
		virtual uint _GetResourceHashCode() const;//������Դ�Ĺ�ϣֵ
		virtual void _DoYieldJob();
	protected:
		void _DependenceReady( );//�Ѿ���һ��������׼����ϣ����Լ�����Դ��������
	public:
		Delegate1<void,const SmartPtr<IAsyncSource>& >::FunctionType* DependencePushed();//����һ��������Դ�����ؽ������������Դ������ϵĻص�
		Delegate1<void,const SmartPtr<IAsyncSource>& >::FunctionType* DependenceLoaded();//����һ��������Դ�����ؽ������������Դ������ϵĻص�
		void OnDependencePushed( const SmartPtr<IAsyncSource>&  dep );//��������Դ������Ϻ�
		void OnDependenceLoaded( const SmartPtr<IAsyncSource>&  dep );//��������Դ������Ϻ�
	public:
		void ClearMetadata();
		void ReleaseUnnecessaryDataAfterLoaded();//��Դ��make���ͷŲ���Ҫ������
	public:
		BOHGE_FORCEINLINE void SetSelfReference( SmartPtr<IAsyncSource>* self )
		{
			m_pSelfReference = self;
		}
		BOHGE_FORCEINLINE void SetDispatchThread( IResourceProperty::DispatchThread dt )
		{
			m_eDispatchThread = dt;
		}
		BOHGE_FORCEINLINE void SetListener( Delegate1<void,IAsyncResource*>::FunctionType* const ptr )
		{
			ASSERT( NULL == m_FuncPtr );
			m_FuncPtr = ptr;
		}
		BOHGE_FORCEINLINE void CastDoneEvent( IAsyncResource* res )
		{
			m_FuncPtr->Invoker( res );
		}
		//BOHGE_FORCEINLINE Delegate1<void,IAsyncResource*>::FunctionType* GetListener() const
		//{
		//	return m_FuncPtr;
		//}
		BOHGE_FORCEINLINE void SetLoadedCallBacke( Delegate1<void, const SmartPtr<IAsyncSource>& >::FunctionType* func )
		{
			m_pSourceLoadedCallBack->Connect( func );
		}
		BOHGE_FORCEINLINE void SetDelayDependLoadedCallBacke( Delegate1<void, const SmartPtr<IAsyncSource>& >::FunctionType* func )
		{
			m_pSourceLoadedDelayDependsCallBack->Connect( func );
		}
		BOHGE_FORCEINLINE IResourceProperty::SourceType GetSourceType() const
		{
			return m_eSourceType;
		}
		BOHGE_FORCEINLINE IResourceProperty::DispatchThread GetDispatchThread() const
		{
			return m_eDispatchThread;
		}
		BOHGE_FORCEINLINE void PushSourceMetadata( const IMetadata& meta )
		{
			m_pISourceMetadataList->push_back( static_cast<IMetadata*>( meta.Duplicate() ) );//���������ǲ�����NEW���ⲿ����
		}
		BOHGE_FORCEINLINE const ISourceMetadataList& GetSourceMetadata() const
		{
			return *m_pISourceMetadataList;
		}
		BOHGE_FORCEINLINE uint GetHashCode()
		{
			if ( 0 == m_nHashCode )
			{
				m_nHashCode = _GetResourceHashCode();
			}
			return m_nHashCode;
		}
		BOHGE_FORCEINLINE void HasDelayDepends()
		{
			m_HasDelayDepends = true;
		}
		BOHGE_FORCEINLINE bool isHostingFree()
		{
			return m_isHostingFree;
		}
	};
}
