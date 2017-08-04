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
#include "MaterialProperty.h"
#include "IndicesStream.h"
#include "VertexStream.h"
#include "3DMath.h"



#include <EASTL/vector.h>
namespace BohgeEngine
{
	class IMetadata;
	namespace RenderObjectProperty
	{
		enum RenderProperty
		{
			RP_SHOW			= 1 << 0UL,
			RP_CULL			= 1 << 1UL,
			RP_LIGHT		= 1 << 2UL,
			RP_SHADOW		= 1 << 3UL,
		};
		enum RenderMode
		{
			RM_POINTS = 0,
			RM_LINES,
			RM_LINE_LOOP,
			RM_LINE_STRIP,
			RM_TRIANGLES,
			RM_TRIANGLE_STRIP,
			RM_TRIANGLE_FAN,
		};
		enum MeshChunk
		{
			MC_MESHES_DATA = MaterialProperty::ATTRIBUTE_END + 1,//��������
				MC_MD_VERTEX,
				MC_MD_NORMAL,//����
				MC_MD_BINORMAL,//������
				MC_MD_TANGENT,//����
				MC_MD_TEX_COORD,//��������
				MC_MD_BONEWEIGHT,//������Ϣ
				MC_MD_END = MC_MESHES_DATA + 100,
			MC_MESHES_INDICES,//ģ������
			MC_MESHES_RENDERMODE,//��Ⱦ��ʽ
			MC_MESHES_END = MC_MESHES_DATA + 999,//ģ�Ͷ�ȡ���
		};

		struct MeshStreamData
		{
			IndicesStream						m_Indices;
			VertexStream						m_Vertex;
			RenderObjectProperty::RenderMode	m_eMode;
		};

		typedef eastl::vector< IMetadata* > RenderMetadataVector;
	}
}