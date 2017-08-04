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
#include "IComponent.h"
#include "3DMath.h"



namespace BohgeEngine
{
	class BOHGE_FRAMEWORK TransformComponent : public IComponent
	{
		RTTI_DRIVER_TYPE_DECLEAR( TransformComponent, IComponent )
	private:
		mutable Matrix44f		m_WorldTransfrom;//����
		mutable Matrix44f		m_WorldTransfromInvers;//����
		mutable Matrix33f		m_WorldRotationMatrix;//��ת����
		mutable Quaternionf		m_WorldRotation;//��ת
		Quaternionf				m_LocalRotation;//��ת
		vector3f				m_LocalPosition;//λ��
		vector3f				m_LocalScale;//����
		mutable vector3f		m_WorldPosition;//λ��
		mutable vector3f		m_WorldScale;//����
		mutable bool			m_isWorldTransfromInversChange;
		mutable bool			m_isWorldRotationChange;
		mutable bool			m_isWorldTransfromChange;
		mutable bool			m_isScaleChange;
		mutable bool			m_isRotationChange;
		mutable bool			m_isPositionChange;
	public:
		TransformComponent(void);
		virtual ~TransformComponent(void);
	private:
		virtual void _DoOnAttachNode( );
	public:
		virtual void OnRootNodeChange( );
		virtual void Release( );
	private:
		void _DoSetLocalRotation( const Quaternionf& r );
		void _DoSetLocalPosition( const vector3f& p );	//���ҽӵ�ʱ�򸸽ڵ�����Ż�Ӱ���ֽڵ����λ��
		void _DoSetLocalScale( const vector3f& s );
	public:
		const Object* AttributeWorldPosition() const;
		const Object* AttributeWorldScale() const;
		const Object* AttributeWorldRotation() const;
		const Object* AttributeWorldTransform() const;
		const Object* AttributeWorldRotationMatrix() const;
		const Object* AttributeWorldTransformInvers() const;
		void MessageLoaclRotation( const NodeMessage& message );
		void MessageLoaclPosition( const NodeMessage& message );
		void MessageLoaclScale( const NodeMessage& message );
	public:
		void SetLocalRotation( const Quaternionf& r );
		void SetLocalPosition( const vector3f& p );	//���ҽӵ�ʱ�򸸽ڵ�����Ż�Ӱ���ֽڵ����λ��
		void SetLocalScale( const vector3f& s );
		void SetWorldRotation( const Quaternionf& r );//�����������ԣ�����ھֲ������ܶ�
		void SetWorldPosition( const vector3f& p );
		void SetWorldScale( const vector3f& s );
		const vector3f& GetWorldPosition() const;
		const vector3f& GetWorldScale() const;
		const Quaternionf& GetWorldRotation() const;
		const Matrix44f& GetWorldTransform() const;
		const Matrix33f& GetWorldRotationMatrix() const;
		const Matrix44f& GetWorldTransformInvers() const;
	};
}
