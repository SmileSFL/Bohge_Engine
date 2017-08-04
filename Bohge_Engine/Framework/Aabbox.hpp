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
#ifndef BOHGE_AABBOX
#define BOHGE_AABBOX
#else
#error( "Do not include this file in other files" )
#endif // BASEMATHDECLAR
#include "Object.hpp"



namespace BohgeEngine
{

	//λ�ù�ϵ
	//	   ulb----urb
	//     /|     /|
	//    ulf--urf |
	//    | dlb--|-drb
	//    |/     |/
	//    dlf---drf
	template <typename T>
	class Aabbox3d : public Object
	{
		RTTI_TYPE_DECLEAR( Aabbox3d<T> );
	private:
		enum CONSTANT
		{
			INCRES = 10,
		};
	public:
		enum Points
		{
			PS_ULB = 0,
			PS_ULF,
			PS_URF,
			PS_URB,

			PS_DRF,
			PS_DRB,
			PS_DLB,
			PS_DLF,
		};
		enum BoxPlane //�����ε���
		{
			BP_FRONT = 0,
			BP_RIGHT,
			BP_BACK,
			BP_LEFT,
			BP_UP,
			BP_DOWN,
		};
	private:
		bool			m_isIdentitat;//�Ƿ��ǳ�ʼֵ��û�иı��
		vector3<T>		m_vMin;	//��Զ��
		vector3<T>		m_vMax;	//�����
		vector3<T>		m_vCenter;
	public:
		Aabbox3d()
			:m_vMin(vector3<T>::Zero()),
			m_vMax(vector3<T>::Zero()),
			m_vCenter(vector3<T>::Zero()),
			m_isIdentitat(true)
		{
		}
		Aabbox3d( const Aabbox3d<T>& input)
			:m_vMin(input.m_vMin),
			m_vMax(input.m_vMax),
			m_vCenter(input.m_vCenter),
			m_isIdentitat(input.m_isIdentitat)
		{
		}
		Aabbox3d( const vector3<T>& minP, const vector3<T>& maxP )
		{
			m_isIdentitat = false;
			m_vMin.m_x = Math::GetMin( minP.m_x, maxP.m_x );
			m_vMin.m_y = Math::GetMin( minP.m_y, maxP.m_y );
			m_vMin.m_z = Math::GetMin( minP.m_z, maxP.m_z );

			m_vMax.m_x = Math::GetMax( minP.m_x, maxP.m_x );
			m_vMax.m_y = Math::GetMax( minP.m_y, maxP.m_y );
			m_vMax.m_z = Math::GetMax( minP.m_z, maxP.m_z );
			m_vCenter = ( m_vMax + m_vMin ) * 0.5f;
		}
		~Aabbox3d()
		{
		}
		BOHGE_FORCEINLINE void Reset() //��ʼ��
		{
			m_isIdentitat = true;
			m_vMin = vector3<T>::Zero();
			m_vMax = vector3<T>::Zero();
			m_vCenter = vector3<T>::Zero();
		}
		BOHGE_FORCEINLINE const vector3<T>& GetMin() const
		{
			return m_vMin;
		}
		BOHGE_FORCEINLINE const vector3<T>& GetMax() const
		{
			return m_vMax;
		}
		BOHGE_FORCEINLINE void SetMin( const vector3<T>& v )
		{
			m_vMin = v;
		}
		BOHGE_FORCEINLINE void SetMax( const vector3<T>& v )
		{
			m_vMax = v;
		}
		BOHGE_FORCEINLINE void MoveDir(const vector3<T>& dir)
		{
			m_vMin += dir;
			m_vMax += dir;
			m_vCenter += dir;
		}
		BOHGE_FORCEINLINE void SetCenter( const vector3<T>& c )
		{
			vector3<T> dir = c - m_vCenter;
			m_vMin += dir;
			m_vMax += dir;
			m_vCenter = c;
		}
		BOHGE_FORCEINLINE vector3<T> GetCenter() const
		{
			return m_vCenter;
		}
		BOHGE_FORCEINLINE vector3<T> GetHalfSize() const
		{
			return (m_vMax - m_vMin) * 0.5;
		}
		BOHGE_FORCEINLINE T MaxEdge() const //���һ����
		{
			vector3<T> edge = m_vMax - m_vMin;
			edge.m_x = Math::Abs( edge.m_x );
			edge.m_y = Math::Abs( edge.m_y );
			edge.m_z = Math::Abs( edge.m_z );
			return Math::GetMax( edge.m_x, Math::GetMax( edge.m_y, edge.m_z) );
		}
		BOHGE_FORCEINLINE Aabbox3d operator* (const vector3<T>& scale ) const
		{
			vector3<T> center = GetCenter();
			vector3<T> size = GetHalfSize();
			size *= scale;
			//ע����ת�Ժ�Ķ���λ�õ�ǰ�������仯����Ҫ���Ĺ��췽ʽ���˴���Ӱ���ཻ���ж�
			return Aabbox3d<T>( center - size , center + size );
		}
		BOHGE_FORCEINLINE Aabbox3d operator* (const Matrix44<T>& input ) const
		{
			Aabbox3d<T> temp;
			for ( int i = PS_ULB; i <= PS_DLF ; i ++)
			{
				vector4< T > point = vector4<T>( GetPoint( static_cast<Points>(i) ) );
				temp.Contains( vector3<T>( point * input ) );
			}
			return temp;
			//vector4<T> vmin( m_vMin );
			//vector4<T> vmax( m_vMax );
			//vmin = vmin * input;
			//vmax = vmax * input;
			////ע����ת�Ժ�Ķ���λ�õ�ǰ�������仯����Ҫ���Ĺ��췽ʽ���˴���Ӱ���ཻ���ж�
			//return aabbox3d<T>( vector3f( vmin ), vector3f( vmax ) );
		}
		BOHGE_FORCEINLINE const Aabbox3d& operator*= (const Matrix44<T>& input )
		{
			Reset();
			for ( int i = PS_ULB; i <= PS_DLF ; i ++)
			{
				vector4<T>point = vector4<T>( GetPoint( static_cast<Points>(i) ) );
				Contains( vector3<T>( point * input ) );
			}
			return *this;
		}
		BOHGE_FORCEINLINE const Aabbox3d& operator *= ( const T& r )
		{
			m_vMin *= r;
			m_vMax *= r;
			m_vCenter = ( m_vMax + m_vMin ) * 0.5f;
			return *this;
		}
		//��vertex�м���󶨺�
		BOHGE_FORCEINLINE Aabbox3d& operator= (const Aabbox3d& rhs )
		{
			m_vMin = rhs.m_vMin;
			m_vMax = rhs.m_vMax;
			m_vCenter = rhs.m_vCenter;
			m_isIdentitat = rhs.m_isIdentitat;
			return *this;
		}
		BOHGE_FORCEINLINE bool operator == (const Aabbox3d& rhs ) const
		{
			return m_vMin == rhs.m_vMin && m_vMax == rhs.m_vMax;
		}
	public:
		BOHGE_FORCEINLINE void Contains(const vector3<T>& pos)
		{
			if( m_isIdentitat )
			{
				m_isIdentitat = false;
				m_vMin = pos;
				m_vMax = pos;
			}
			else
			{
				if( pos.m_x < m_vMin.m_x)
				{
					m_vMin.m_x = pos.m_x;
				}
				if( pos.m_y < m_vMin.m_y)
				{
					m_vMin.m_y = pos.m_y;
				}
				if( pos.m_z < m_vMin.m_z)
				{
					m_vMin.m_z = pos.m_z;
				}

				if( pos.m_x > m_vMax.m_x)
				{
					m_vMax.m_x = pos.m_x;
				}
				if( pos.m_y > m_vMax.m_y)
				{
					m_vMax.m_y = pos.m_y;
				}
				if( pos.m_z > m_vMax.m_z)
				{
					m_vMax.m_z = pos.m_z;
				}
				m_vCenter = ( m_vMax + m_vMin ) * 0.5f;
			}
		}
		BOHGE_FORCEINLINE void Contains(const Aabbox3d<T>& box)
		{
			this->Contains( box.m_vMax );
			this->Contains( box.m_vMin );
		}
		//���Χ���ཻ������
		BOHGE_FORCEINLINE IntersectedType::Volume IntersectType(const Aabbox3d<T>& box) const
		{
			return Math::Aabbox3d_Aabbox3d_IntersectType( *this, box );
		}
		BOHGE_FORCEINLINE IntersectedType::Volume IntersectType(const Frustum<T>& frustum ) const
		{
			return Math::Frustum_Aabbox3d_IntersectType( frustum, *this );
		}
		//�����ཻ��,ע�⣬������ڰ�Χ���ڲ�������ֱ�ӷ���ԭ�㣬���Ǹ���ĸ���󶨺��Ǹ���
		BOHGE_FORCEINLINE bool IntersectPointWithRay( const Ray<T>& ray, vector3<T>& out ) const
		{
			return Math::Aabbox3d_Ray_IntersectPoint( *this, ray, out );
		}
		//���Χ���ཻ
		BOHGE_FORCEINLINE bool Intersect(const Aabbox3d<T>& box) const
		{
			return Math::Aabbox3d_Aabbox3d_Intersect( *this, box );
		}
		//����ཻ
		BOHGE_FORCEINLINE bool Intersect(const vector3<T>& pos) const
		{
			return Math::Aabbox3d_Vector3_Intersect( *this, pos );
		}
		/*�μ�ⷽ����������ԣ��ȼ���������ײ����*/
		BOHGE_FORCEINLINE bool Intersect( const Ray<T>& ray ) const
		{
			return Math::Aabbox3d_Ray_Intersect( *this, ray );
		}
		/*�μ�ⷽ����������ԣ��ȼ���������ײ����*/
		BOHGE_FORCEINLINE bool Intersect( const Line<T>& line ) const
		{
			return Math::Aabbox3d_Line_Intersect( *this, line );
		}
		//�������ཻ
		BOHGE_FORCEINLINE bool Intersect(Aabsphere<T> const & sphere) const
		{
			return Math::Aabbox3d_Aabsphere_Intersect( *this, sphere );
		}
		BOHGE_FORCEINLINE IntersectedType::Volume Intersect(Frustum<T> const & frustum) const
		{
			return Math::Frustum_Aabbox3d_Intersect( frustum, *this );
		}
		//ȡ�ö���
		BOHGE_FORCEINLINE vector3<T> GetPoint( Points p ) const
		{
			switch ( p )
			{
			case PS_ULB: return vector3<T>( m_vMin.m_x, m_vMax.m_y, m_vMin.m_z );
			case PS_ULF: return vector3<T>( m_vMin.m_x, m_vMax.m_y, m_vMax.m_z );
			case PS_URF: return m_vMax;
			case PS_URB: return vector3<T>( m_vMax.m_x, m_vMax.m_y, m_vMin.m_z );
			case PS_DRF: return vector3<T>( m_vMax.m_x, m_vMin.m_y, m_vMax.m_z );
			case PS_DRB: return vector3<T>( m_vMax.m_x, m_vMin.m_y, m_vMin.m_z );
			case PS_DLB: return m_vMin;
			case PS_DLF: return vector3<T>( m_vMin.m_x, m_vMin.m_y, m_vMax.m_z );
			}
			return vector3<T>();
		}
		//ȡ�ð󶨺��ӵ���
		BOHGE_FORCEINLINE Plane<T> GetPlane( BoxPlane bp ) const
		{
			//switch ( bp )
			//{
			//case BP_FRONT: return Plane<T>( m_vMax,
			//								vector3<T>( m_vMin.m_x, m_vMin.m_y, m_vMax.m_z ),
			//								vector3<T>( m_vMax.m_x, m_vMax.m_y, m_vMax.m_z ) );
			//case BP_RIGHT: return Plane<T>( m_vMax,
			//								vector3<T>( m_vMax.m_x, m_vMax.m_y, m_vMax.m_z ),
			//								vector3<T>( m_vMax.m_x, m_vMin.m_y, m_vMin.m_z ) );
			//case BP_BACK: return Plane<T>( m_vMin,
			//								vector3<T>( m_vMax.m_x, m_vMax.m_y, m_vMin.m_z ),
			//								vector3<T>( m_vMin.m_x, m_vMin.m_y, m_vMin.m_z ) );
			//case BP_LEFT: return Plane<T>( m_vMin,
			//								vector3<T>( m_vMin.m_x, m_vMax.m_y, m_vMax.m_z ),
			//								vector3<T>( m_vMin.m_x, m_vMin.m_y, m_vMin.m_z ) );
			//case BP_UP: return Plane<T>( m_vMin,
			//								vector3<T>( m_vMin.m_x, m_vMax.m_y, m_vMax.m_z ),
			//								vector3<T>( m_vMax.m_x, m_vMax.m_y, m_vMin.m_z ) );
			//case BP_DOWN: return Plane<T>( m_vMax,
			//								vector3<T>( m_vMin.m_x, m_vMin.m_y, m_vMax.m_z ),
			//								vector3<T>( m_vMax.m_x, m_vMin.m_y, m_vMin.m_z ) );
			//}
			switch ( bp )
			{
			case BP_FRONT: return Plane<T>( GetPoint(PS_DRF), GetPoint(PS_URF), GetPoint(PS_DLF) );
			case BP_RIGHT: return Plane<T>( GetPoint(PS_DRF), GetPoint(PS_URF), GetPoint(PS_DRB) );
			case BP_BACK: return Plane<T>( GetPoint(PS_ULB), GetPoint(PS_URB), GetPoint(PS_DLB) );
			case BP_LEFT: return Plane<T>( GetPoint(PS_ULB), GetPoint(PS_ULF), GetPoint(PS_DLB) );
			case BP_UP: return Plane<T>( GetPoint(PS_ULB), GetPoint(PS_ULF), GetPoint(PS_URB) );
			case BP_DOWN: return Plane<T>( GetPoint(PS_DRF), GetPoint(PS_DLF), GetPoint(PS_DRB) );
			}
			return Plane<T>();
		}
	};
}