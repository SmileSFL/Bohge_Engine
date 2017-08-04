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
#include "Framework/IWebProperty.h"
#include "Framework/IWebSystem.h"



#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/map.h>

namespace BohgeEngine
{
	class IThreadMutex;
	class IJobDispatcher;
}

namespace CurlWebSystemPlugin
{	
	class DownloadHandle;
	class WebSystem : public BohgeEngine::IWebSystem
	{
	private:
		enum Constant
		{
			WC_CACHE_EACH_DOWNLOAD_SIZE = 1 * 1024 *1024,//ÿ1mb����һ����Ϣ
			WC_CACHE_DOWNLOAD_INFO_MAX_SIZE = 100,//��ౣ��100�����ؼ�¼
		};
	private:
		struct DownloadInfo
		{
			uint			m_Date;//����������ʱ��
			uint64			m_Size;//�ļ��ߴ磬����ȷ�������Ƿ��޸Ĺ�
			eastl::string	m_Url;//��������ַ
			eastl::string	m_Path;//���ص�ַ
		};
	private:
		typedef eastl::map< uint, DownloadInfo* > DonwloadInfoMap;//�Ѿ������ļ�����Ϣ
		typedef eastl::map< intptr_t, BohgeEngine::IBaseHandle* > HandleMap;
	private:
		DonwloadInfoMap*				m_pDonwloadInfoMap;
		HandleMap*						m_pHandleMap;
		eastl::string*					m_pCachePath;
		BohgeEngine::IThreadMutex*		m_pMapMutex;
		BohgeEngine::IJobDispatcher*	m_pJobDispatcher;
		uint64							m_DonwloadSize;
	public:
		WebSystem(void);
		~WebSystem(void);
	private:
		void _InsertDonwloadInfo( DownloadHandle* h );
		eastl::vector< BohgeEngine::IBaseHandle* > _PraseJobState( );
		void _CacheJobStates();
		void _PraseDownloadInfo();
		void _CacheDownloadInfo();//��¼������Ϣ
	public:
		void OnWebJobStateChange( BohgeEngine::IBaseHandle* h );
	public://ע����¼�����
		void OnFrameworkEntry( float time, BohgeEngine::Framework& framework ); //ע��ϵͳ����rtti
		void OnFrameworkExit( float time, BohgeEngine::Framework& framework );
	public:
		virtual void RegistEvent( BohgeEngine::Framework& framework ); //ע���¼�
		virtual eastl::vector< BohgeEngine::IBaseHandle* > SetCachePath( const eastl::string& path );//���û����ļ�Ŀ¼,���Ŀ¼�����л��棬��������棬�ж��Ƿ���δ��ɵ�����
		virtual BohgeEngine::IBaseHandle* WebFactory( BohgeEngine::IWebProperty::WebJobType jt );
		virtual void RecycleBin( BohgeEngine::IBaseHandle* h );
	public:
		bool isCaching( uint date, uint64 size, const eastl::string& url, const eastl::string& path ) const;
	};
}
