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
#include "LuaScriptSystem.h"
#include "ScriptTypeConstruct.h"
#include "ScriptCallBridge.h"
#include "ScriptFunction.h"
#include "ScriptUtility.h"
#include "ScriptClass.h"
#include "ScriptType.h"
#include "Rtti.hpp"

extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lobject.h"
}

#include "lua_tinker.hpp"

#include <vector>

using namespace std;






namespace BohgeEngine
{
	//-------------------------------------------------------------------------------------------------------
	LuaScriptSystem::LuaScriptSystem(void)
		:m_LuaState(NULL)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	LuaScriptSystem::~LuaScriptSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::_RegisterScriptTypeConstruct( const char* cn, void* func )
	{
		lua_getglobal(m_LuaState, cn );
		ASSERT(lua_istable(m_LuaState, -1));
		{
			lua_newtable(m_LuaState);
			lua_pushstring(m_LuaState, "__call");
			lua_pushcclosure(m_LuaState, (lua_CFunction)func, 0);
			lua_rawset(m_LuaState, -3);
			lua_setmetatable(m_LuaState, -2);
		}
		lua_pop(m_LuaState, 1);
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::Initialize()
	{
		m_LuaState = luaL_newstate();
		luaL_openlibs(m_LuaState);

		//ע��ϵͳ����
		_DoRegisterClass( "Int" );
		_RegisterScriptTypeConstruct( "Int", &IntConstruct );
		_DoRegisterClass( "Float" );
		_RegisterScriptTypeConstruct( "Float", &FloatConstruct );
		_DoRegisterClass( "Double" );
		_RegisterScriptTypeConstruct( "Double", &DoubleConstruct );
		_DoRegisterClass( "Bool" );
		_RegisterScriptTypeConstruct( "Bool", &BoolConstruct );

		lua_getglobal( m_LuaState, "package" );
		lua_getfield( m_LuaState, -1, "path" ); // get field "path" from table at top of stack (-1)
		std::string cur_path = lua_tostring( m_LuaState, -1 ); // grab path string from top of stack
		cur_path.append( ";" ); // do your path magic here
		cur_path.append( "E:/Bohge_Engine_New_Architecture/Bohge_External/lua-5.2.2/lua_tinker_0.5c/?.lua" );
		lua_pop( m_LuaState, 1 ); // get rid of the string on the stack we just pushed on line 5
		lua_pushstring( m_LuaState, cur_path.c_str() ); // push the new one
		lua_setfield( m_LuaState, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
		lua_pop( m_LuaState, 1 ); // get rid of package table from top of stack
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::_DoRegisterClass( const char* cn )
	{
		lua_newtable(m_LuaState);

		//ע��������
		lua_pushstring(m_LuaState, "__name");
		lua_pushstring(m_LuaState, cn );
		lua_rawset(m_LuaState, -3);

		//Ԫ��
		lua_pushstring(m_LuaState, "__index");
		lua_pushcclosure(m_LuaState, lua_tinker::meta_get, 0);
		lua_rawset(m_LuaState, -3);

		lua_pushstring(m_LuaState, "__newindex");
		lua_pushcclosure(m_LuaState, lua_tinker::meta_set, 0);
		lua_rawset(m_LuaState, -3);

		lua_pushstring(m_LuaState, "__gc");
		lua_pushcclosure(m_LuaState, &ClassDestruct, 0);
		lua_rawset(m_LuaState, -3);

		//����ȫ������
		lua_setglobal( m_LuaState, cn );
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::_DoRegisterFunction( ScriptClass* sc )
	{
		uint funcCount = sc->GetFunctionListCount();
		for ( int i = 0 ; i < funcCount ; ++ i )
		{
			_RegisterClassFunction( sc, i, _FunctionNameMapping( sc->GetFunctionListName(i) ) );
		}
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::RegisterClass( const ScriptClass& c )
	{
		ScriptClass* sc = NEW ScriptClass( c );
		m_ScriptClassArray.push_back( sc );
		_DoRegisterClass( sc->GetTypeName().c_str() );
		if ( c.isDriverType() )//ע��̳���
		{
			lua_getglobal(m_LuaState, c.GetTypeName().c_str());
			lua_pushstring(m_LuaState, "__parent");
			lua_getglobal(m_LuaState, c.GetBaseTypeName().c_str());
			lua_rawset(m_LuaState, -3);
			lua_pop(m_LuaState, 1);
		}
		_DoRegisterFunction( sc );
		_DoRegisterConstant( sc );
	}
	//-------------------------------------------------------------------------------------------------------
	const char* LuaScriptSystem::_FunctionNameMapping( const std::string& name )
	{
		if ( name == __ADD )
		{
			return "__add";
		}
		else if( name == __SUB )
		{
			return "__sub";
		}
		else if( name == __MUL )
		{
			return "__mul";
		}
		else if( name == __DIV )
		{
			return "__div";
		}
		else if( name == __CON )
		{
			return "__call";
		}
		return name.c_str();
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::_RegisterClassFunction( ScriptClass* c, int index, const char* name )
	{
		lua_CFunction func = NULL;
		bool isCon = string("__call") == name ? true : false;
		lua_getglobal(m_LuaState, c->GetTypeName().c_str());//�õ���ı���
		ASSERT(lua_istable(m_LuaState, -1));

		if ( isCon )lua_newtable(m_LuaState);//����ǹ�����Ҫ�¼�Ԫ��

		lua_pushstring(m_LuaState, name );//���������������ջ
		lua_pushlightuserdata(m_LuaState, c );//��ScriptClass��Ϣ�����ջ
		lua_pushnumber(m_LuaState, index );//�������������е�λ�������ջ
		if ( c->isOverrideFunction( index ) )
		{
			if ( isCon ) func = &OverrideClassConstruct;
			else func = &OverrideClassFunction;
		}
		else
		{
			if ( isCon ) func = &SingleClassConstruct;
			else func = &SingleClassFunction;
		}
		lua_pushcclosure(m_LuaState, func, 2);//ע�ắ����֪ͨlua����ӵ������upvalue
		lua_rawset(m_LuaState,-3);
		
		if ( isCon )lua_setmetatable(m_LuaState, -2);

		lua_pop(m_LuaState, 1);
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::_DoRegisterConstant( ScriptClass* sc )
	{
		uint funcCount = sc->GetClassConstantCount();
		for ( int i = 0 ; i < funcCount ; ++ i )
		{
			CLassConstant cc = sc->GetClassConstant( i );
			lua_getglobal(m_LuaState, sc->GetTypeName().c_str());//�õ���ı���
			ASSERT(lua_istable(m_LuaState, -1));

			lua_pushstring(m_LuaState, cc.first.c_str() );//�����������ջ
			ScriptValue* userdata = (ScriptValue*)lua_newuserdata(m_LuaState, sizeof(ScriptValue) );
			userdata->SetValue( cc.second, true );			
			lua_rawset(m_LuaState, -3);
		}
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::SetGlobal( const string& name, RttiObject* obj )
	{
		ScriptValue* userdata = (ScriptValue*)lua_newuserdata(m_LuaState, sizeof(ScriptValue) );
		userdata->SetValue( obj, true );
		lua_getglobal( m_LuaState, obj->GetTypeName().c_str() );//�õ��������
		ASSERT(lua_istable(m_LuaState, -1));
		lua_setmetatable( m_LuaState, -2 );
		lua_setglobal( m_LuaState, name.c_str() );//���һ��ȫ�ֱ���
	}
	//-------------------------------------------------------------------------------------------------------
	void LuaScriptSystem::LoadScript( const std::string& name )
	{
		lua_tinker::dofile( m_LuaState, name.c_str() );
		m_ModuleList.push_back( name );
	}

}
