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
#include "Framework/IAsyncEntity.h"
#include "Framework/SmartPtr.hpp"
#include "FontResource.h"
#include "FontSource.h"



#include <EASTL/list.h>

namespace BTextSystemPlugin
{
	class FontEntity : public BohgeEngine::IAsyncEntity< FontResource, FontSource >
	{
		RTTI_DRIVER_TYPE_DECLEAR( FontEntity, IAsyncEntity );
	public:
		FontEntity(void);
		virtual ~FontEntity(void);
	private:
		virtual void _OnCreateResource();//׼��������Դ��ʱ�����
		virtual void _OnResourceCreated();//��Դ������ϵĻص�
	public:
		BOHGE_FORCEINLINE void LoadText( const BohgeEngine::vector2d& size, const eastl::wstring& str, BohgeEngine::TextString& ts )
		{
			_GetResourcePtr()->LoadText( size, str, ts );
		}
		BOHGE_FORCEINLINE void UnLoadText( const BohgeEngine::vector2d& size, const eastl::wstring& str )
		{
			_GetResourcePtr()->UnLoadText( size, str );
		}
		BOHGE_FORCEINLINE const BohgeEngine::TextureEntity* GetTextureEntity()
		{
			_GetResourcePtr()->GetTextureEntity();
		}
	};
}

