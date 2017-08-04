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
#include "Framework/GlobalDefine.h"
#include "Framework/3DMath.h"


#include <EASTL/map.h>
#include <EASTL/string.h>
namespace BGUI
{
	typedef eastl::map< uint, eastl::string > MaterialMap;
	namespace WidgetProperty
	{
#define WIDGET_STATUS_ENABLE (0.5f)
#define WIDGET_STATUS_DISABLE (2.0f)
		enum WidgetStatus
		{
			WS_ACTIVE = 0,
			WS_DISABLED,
			WS_PRESSED,
			WS_HIDE,
		};
		enum WidgetType
		{
			WT_PANEL = 0,
			WT_LABEL,
			WT_BUTTON,
			WT_STRING,
		};
		enum OptionalType//��ѡ����������
		{
			OT_TEXT = 0,
		};
		enum WidgetAdaptive//����ģʽ
		{
			WA_NARROW = 0,//�ȱ�����С��������С�����ű߽������ţ�
			WA_ENLARGE,//�ȱȷŴ󣨰����������ű߽������ţ�
			WA_TENSILE,//�ǵȱ���(����)
		};
		enum StringAlign
		{
			SA_LEFT_TOP	= 0,
			SA_CENTER,
		};

		static const char* BUTTON_ONPRESSED("OnPressed");
	}
}