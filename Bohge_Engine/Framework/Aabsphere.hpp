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
#ifndef BOHGE_AABSPHERE
#define BOHGE_AABSPHERE
#else
#error( "Do not include this file in other files" )
#endif // BASEMATHDECLAR
#include "Object.hpp"


namespace BohgeEngine
{

	template <typename T>
	class Aabsphere : public Object
	{
		RTTI_TYPE_DECLEAR( Aabsphere<T> );
	private:
		vector3<T>		m_Center;//����
		T				m_Radius;//�뾶
	public:
		Aabsphere()
		{
		}
		Aabsphere(vector3<T> const & center, T const & radius)
			: m_Center(center),
			m_Radius(radius)
		{
		}

		// ��ֵ������
		BOHGE_FORCEINLINE Aabsphere& MoveOn(vector3<T> const & rhs)
		{
			m_Center += rhs;
			return *this;
		}
		BOHGE_FORCEINLINE Aabsphere& Scale(T const & rhs)
		{
			m_Radius *= rhs;
			return *this;
		}
		BOHGE_FORCEINLINE Aabsphere& operator=(Aabsphere const & rhs)
		{
			if (this != &rhs)
			{
				this->m_Center = rhs.m_Center;
				this->m_Radius = rhs.m_Radius;
			}
			return *this;
		}
		BOHGE_FORCEINLINE void SetCenter(const vector3<T>& v)
		{
			m_Center = v;
		}
		BOHGE_FORCEINLINE vector3<T> const & GetCenter() const
		{
			return m_Center;
		}
		BOHGE_FORCEINLINE void SetRadius( T& r )
		{
			m_Radius = r;
		}
		BOHGE_FORCEINLINE T GetRadius() const	
		{
			return m_Radius;
		}
		BOHGE_FORCEINLINE bool IsEmpty() const
		{
			return Math::isEqual(m_Radius, 0.0f);
		}
		BOHGE_FORCEINLINE T MaxRadiusSq() const
		{
			return m_Radius * m_Radius;
		}
		BOHGE_FORCEINLINE bool Intersect(vector3<T> const & v) const
		{
			return Math::Aabsphere_Vector3_Intersect( *this, v );
		}
		BOHGE_FORCEINLINE bool Intersect(Aabsphere<T> const & sphere) const
		{
			return Math::Aabsphere_Aabsphere_Intersect( *this, sphere );
		}
		BOHGE_FORCEINLINE bool Intersect( const Aabbox3d<T>& box ) const
		{
			return Math::Aabbox3d_Aabsphere_Intersect( box, *this );
		}
	};
}