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
#include "WindowsIOSystem.h"
#ifdef _PLATFORM_WINDOWS
#include "Framework/Predefine.h"
#include "Framework/Log.h"
#include "ZipFile.h"
#include "UsualFile.h"
#include "EncryptFile.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>

using namespace eastl;


namespace IOSystemPlugin
{
	//-------------------------------------------------------------------------------------------------------
	WindowsIOSystem::WindowsIOSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	WindowsIOSystem::~WindowsIOSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	void WindowsIOSystem::_DoMakeFolder( const eastl::string& path )
	{
		string npath;
		if ( string::npos != path.find( '.' ) )
		{
			npath = path.substr( 0, path.find_last_of("/\\") );
		}
		else
		{
			npath = path;
		}
		if( access(path.c_str(),0) == -1 ) //����ļ��в�����
		{
			DEBUGLOG("make folder %s\n", npath.c_str());
			mkdir(npath.c_str());
		}
	}
	//-------------------------------------------------------------------------------------------------------
	bool WindowsIOSystem::_DoIsFileExist( const eastl::string& filename )
	{
		if( 0 == access(filename.c_str(), 0) )//���ֱ�Ӵ���
		{
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------------
	bool WindowsIOSystem::_DoDeleteFile( const eastl::string& strFileName )
	{
		if( isFileExist(strFileName) )
		{
			remove( strFileName.c_str() );
		}
		return true;
	}
	////-------------------------------------------------------------------------------------------------------
	//eastl::vector<eastl::string> WindowsIOSystem::GetFileNamesWithExpand( const eastl::string& path, const eastl::string& exp )
	//{
	//	vector<string> files;
	//	string fullpath = path;
	//	struct _finddata_t c_file; 
	//	intptr_t   hFile; 
	//	if(_chdir(fullpath.c_str())) 
	//	{
	//		DEBUGLOG("Cant' open direction, %s\n", fullpath.c_str() );
	//		ASSERT(false);
	//	} 
	//	else 
	//	{
	//		hFile = _findfirst("*.*", &c_file); 
	//		if( 0 < c_file.size )
	//		{
	//			DEBUGLOG("include file, %s\n", c_file.name );
	//			string filename = c_file.name;
	//			if ( exp.empty() || string::npos != filename.find(exp) )
	//			{
	//				files.push_back( filename.substr(filename.find_last_of("/\\")+1) );
	//			}
	//		}
	//	}
	//	while(_findnext(hFile, &c_file) == 0) 
	//	{ 
	//		if( 0 < c_file.size )
	//		{
	//			DEBUGLOG("include file, %s\n", c_file.name );
	//			string filename = c_file.name;
	//			if ( exp.empty() || string::npos != filename.find(exp) )
	//			{
	//				files.push_back( filename.substr(filename.find_last_of("/\\")+1) );
	//			}
	//		}
	//	} 
	//	_findclose(hFile); 
	//	return files;
	//}
	//-------------------------------------------------------------------------------------------------------
	BohgeEngine::IFile* WindowsIOSystem::_DoFileFactory( const eastl::string& path )
	{
		if ( string::npos != path.find(".enc") )
		{
			return NEW EncryptFile( path );
		}
		else if ( string::npos != path.find(".zip") )
		{
			return NEW ZipFile( path );
		}
		else
		{
			return NEW UsualFile( path );
		}
		ASSERT(false);
		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void WindowsIOSystem::RecycleBin( BohgeEngine::IFile* file )
	{
		SAFE_DELETE( file );
	}

}
#endif