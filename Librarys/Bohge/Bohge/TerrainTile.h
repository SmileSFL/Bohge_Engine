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



/////////////////////////
//		地形		   //
/////////////////////////

#pragma once
#include "aabrect.hpp"
#include "aabbox.hpp"
#include "SecenProperty.h"
#include <map>


namespace BohgeEngine
{
	class ICamera;
	class Material;
	class Texture2D;
	class RendBuffer;
	class TerrainChunk;
	class VertexBuffer;
	class TerrainTile 
	{
	protected:
		bool								m_isInView;//是否可见
		aabbox3df							m_BindBox;
		TerrainProperty						m_Property;//地形属性
		vector2d							m_Offset;//地形在大的地形途中的位置索引
		aabrectf							m_WorldRange;//范围

		TerrainChunk*						m_QTNode;//地形树
		//绘制相关
		Material*							m_TerrainMaterial;
		RendBuffer*							m_TerrainBuffer;//地形的buffer
		VertexBuffer*						m_pVertexBuffer;

		//逻辑相关
		float								m_ScaleInv;
		std::vector< float >				m_Hegiht;//地形的高度

	public:
		void AssignMaterial( const bool& isCast, const ICamera& camera );//通过阴影摄像机确定渲染每一块的材质
		void Update( uint milisecon, std::multimap< float, TerrainChunk* >& tmap );
	public:
		TerrainTile( const TerrainProperty& ppy );
		~TerrainTile( );
		void Load( const std::string& path, const std::string& TexPath );
	public:
		BOHGE_FORCEINLINE aabbox3df& BindBox()
		{
			return m_BindBox;
		}
		BOHGE_FORCEINLINE bool& isInView()
		{
			return m_isInView;
		}
		BOHGE_FORCEINLINE float GetHeight( float x, float y, float& outDepth ) const
		{
			if ( m_WorldRange.isInsert( x, y ) )
			{
				int xindex = ( x - m_WorldRange.LeftBottom().m_x ) * m_ScaleInv;
				int yindex = ( y - m_WorldRange.LeftBottom().m_y ) * m_ScaleInv;
				outDepth = m_Hegiht[ yindex*m_Property.m_TileSize+xindex];
				return true;
			}
			return false;
		}
		BOHGE_FORCEINLINE bool GetHeightForWater( float x, float y, float& outDepth ) const
		{
			if ( m_WorldRange.isInsert( x, y ) )
			{
				int xindex = ( x - m_WorldRange.LeftBottom().m_x ) * m_ScaleInv;
				int yindex = ( y - m_WorldRange.LeftBottom().m_y ) * m_ScaleInv;
				outDepth = m_Hegiht[ yindex*m_Property.m_TileSize+xindex];
				return true;
			}
			return false;
		}
	};

}