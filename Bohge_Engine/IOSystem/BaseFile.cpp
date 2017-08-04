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
#include "BaseFile.h"



namespace IOSystemPlugin
{
	//-------------------------------------------------------------------------------------------------------
	BaseFile::BaseFile( const eastl::string& url )
		:m_FileUrl( url ),
		m_ActionType(AT_NONE),
		m_isOpen(false),
		m_FileSize(0),
		m_PosIndex(0),
		m_BufferSize(0),
		m_ReadedBufferSize(0),
		m_pDatas(NULL)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	BaseFile::~BaseFile(void)
	{
		ASSERT( false == m_isOpen );
	}
	//-------------------------------------------------------------------------------------------------------
	bool BaseFile::OpenFile( ActionType at )
	{
		ASSERT( m_isOpen == false );
		m_isOpen = _DoOpenFile( at );
		if ( m_isOpen )
		{
			switch( at )
			{
			case AT_READ:
				{
					m_BufferSize = m_FileSize > FC_FILEBUFFER ? FC_FILEBUFFER : m_FileSize;
					m_pDatas = NEW byte[m_BufferSize];
					m_ReadedBufferSize += m_BufferSize;
					_DoReadFile( m_pDatas, m_BufferSize );//�������
				}break;
			case AT_WRITE:
				{
					m_BufferSize = FC_FILEBUFFER;
					m_pDatas = NEW byte[m_BufferSize];
				}break;
			default:ASSERT(false);
			}
		}
		m_ActionType = m_isOpen ? at : AT_NONE;
		return m_isOpen;
	}
	//-------------------------------------------------------------------------------------------------------
	bool BaseFile::CloseFile()
	{
		if ( m_isOpen )
		{
			if ( m_PosIndex != 0 && AT_WRITE == m_ActionType )
			{
				_DoWriteFile( m_pDatas, m_PosIndex );
			}
			m_isOpen = !_DoCloseFile();
			m_PosIndex = 0;
			SAFE_DELETE( m_pDatas );
		}
		return !m_isOpen;
	}
	//-------------------------------------------------------------------------------------------------------
	int BaseFile::Seek( int to, int whence )
	{
		int result = 0;
		ASSERT( m_isOpen == true );
		switch( m_ActionType )
		{
		case AT_READ:
			{
				switch( whence )
				{
				case SEEK_SET:
					{
						result = _DoSeekFile( to, whence );
						m_ReadedBufferSize = to;
						m_BufferSize = m_FileSize - m_ReadedBufferSize > FC_FILEBUFFER ? FC_FILEBUFFER : m_FileSize - m_ReadedBufferSize;
					}break;
				case SEEK_CUR:
					{
						int realto = to - m_BufferSize + m_PosIndex;
						m_ReadedBufferSize += realto;
						result = _DoSeekFile( realto, whence );
						m_BufferSize = m_FileSize - m_ReadedBufferSize > FC_FILEBUFFER ? FC_FILEBUFFER : m_FileSize - m_ReadedBufferSize;
					}break;
				case SEEK_END:
					{
						result = _DoSeekFile( to, whence );
						m_ReadedBufferSize = m_FileSize - to;
						m_BufferSize = to > FC_FILEBUFFER ? FC_FILEBUFFER : to;
					}break;
				default: ASSERT(false);
				}
				m_PosIndex = m_BufferSize;//�ƿյ���buffer���ݶ�
			}break;
		case AT_WRITE:
			{
				if ( 0 != m_PosIndex )
				{
					_DoWriteFile( m_pDatas, m_PosIndex );//����������д��
					m_PosIndex = 0;
				}
				result = _DoSeekFile( to, whence );
			}break;
		default:
			{
				ASSERT( false );
			}break;
		}
		return result;
	}
	//-------------------------------------------------------------------------------------------------------
	int BaseFile::Tell()
	{
		ASSERT( m_isOpen == true );
		switch( m_ActionType )
		{
		case AT_READ: return _DoTell() - m_BufferSize + m_PosIndex;
		case AT_WRITE:return _DoTell() + m_PosIndex;
		default: ASSERT( false ); break;
		}
		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	int BaseFile::ReadFile( void* data, int bitesize )
	{
		if ( !m_isOpen )
		{
			OpenFile( AT_READ );
		}
		ASSERT( AT_READ == m_ActionType );
		if ( bitesize > m_BufferSize || bitesize > ( m_BufferSize - m_PosIndex ) )
		{
			int readsize = m_BufferSize - m_PosIndex;//buffer�е�ʣ�����ݼ��س�����
			memcpy( data, m_pDatas + m_PosIndex, readsize );
			int remainsize = bitesize - readsize;//ʣ����Ҫ��ȡ��
			if ( remainsize > FC_FILEBUFFER )//��ʣ�����Ҫ��ȡ�Ĵ���buffer
			{
				m_ReadedBufferSize += remainsize;
				if ( 0 == _DoReadFile( ((byte*)data)+readsize,  remainsize ) )//�������,0Ϊû������
				{
					return 0;
				}
				m_BufferSize = m_FileSize - m_ReadedBufferSize > FC_FILEBUFFER ? FC_FILEBUFFER : m_FileSize - m_ReadedBufferSize;
				m_ReadedBufferSize += m_BufferSize;
				m_PosIndex = 0;
				if ( 0 == _DoReadFile( m_pDatas,  m_BufferSize ) )//�������,0Ϊû������
				{
					return 0;
				}
			}
			else
			{
				m_BufferSize = m_FileSize - m_ReadedBufferSize > FC_FILEBUFFER ? FC_FILEBUFFER : m_FileSize - m_ReadedBufferSize;
				m_ReadedBufferSize += m_BufferSize;
				if ( 0 == _DoReadFile( m_pDatas,  m_BufferSize ) )//�������,0Ϊû������
				{
					return 0;
				}
				int remainsize = bitesize - readsize;//ʣ����Ҫ��ȡ��
				memcpy( ((byte*)data)+readsize, m_pDatas, remainsize );
				m_PosIndex = remainsize;
			}
		}
		else
		{
			memcpy( data, m_pDatas + m_PosIndex, bitesize );
			m_PosIndex += bitesize;
		}
		return bitesize;
	}
	//-------------------------------------------------------------------------------------------------------
	int BaseFile::WriteFile( const void* data, int bitesize )
	{
		if ( !m_isOpen )
		{
			OpenFile( AT_WRITE );
		}
		ASSERT( AT_WRITE == m_ActionType );
		if ( bitesize > m_BufferSize || bitesize > ( m_BufferSize - m_PosIndex ) )
		{
			if ( 0 != m_PosIndex )
			{
				_DoWriteFile( m_pDatas, m_PosIndex );
			}
			_DoWriteFile( data, bitesize );
			m_PosIndex = 0;
		}
		else
		{
			memcpy( m_pDatas + m_PosIndex, data, bitesize );
			m_PosIndex += bitesize;
		}
		m_FileSize += bitesize;
		return bitesize;
	}
	//-------------------------------------------------------------------------------------------------------
	const eastl::string& BaseFile::GetFilePath()
	{
		return m_FileUrl;
	}
	//-------------------------------------------------------------------------------------------------------
	uint BaseFile::GetSize()
	{
		return _GetFileSize();
	}
	//-------------------------------------------------------------------------------------------------------
	bool BaseFile::isOpen()
	{
		return m_isOpen;
	}

}