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
#include "ComponentProperty.h"
#include "NodeProperty.h"
#include "Object.hpp"


#include <EASTL/vector.h>

namespace BohgeEngine
{
	class BOHGE_FRAMEWORK Node : public Object
	{
		RTTI_TYPE_DECLEAR( Node )
	private:
		ComponentProperty::SubnodeMap		m_SubnodeMap;//�ӽڵ�
		ComponentProperty::ComponentMap		m_Components;//�������������
		eastl::string		m_NodeName;
		AttributeDelegate*	m_pAttributeDelegateArray;//�齨ע���ṩĳЩ����
		MessageDelegate*	m_pMessageDelegateArray;
		Node*				m_RootNode;//���ڵ�
		ushort				m_NodeDepth;
	public:
		Node(void);
		virtual ~Node(void);
	private:
		void _OnRootNodeChange( );
		void _SetFather( Node* root );
		void _RecaculateDepth();//�����ڵ�ı�ʱ�����¼���ÿ���ڵ��ÿ���ڵ���ֽڵ��depth
	public:
		void InsertIntoManager( const eastl::string& name );//���ڵ��ڵ�������У��ýű���ѯ
		void AttachNode( Node* node );//�ڵ�ǰ�ڵ��ϸ���һ���ӽڵ�
		void DetachNode( Node* node );//���뵱ǰ�ڵ���ӽڵ�;
		void AttachComponent( IComponent* com );//���һ���齨
		void ReleaseComponent( );//�ͷ�ȫ�������
		void RegisterAttributeProvider( NodeProperty::GetAttribute na, ProviderFunction* func );//ע��Ϊһ������ԭ
		void RegisterMessageListener( NodeProperty::SetAttribute mt, MessageFunction* func );//ע���¼�����
		void SendMessage( const NodeMessage& message );//���Լ�������͸��ڵ�㲥��Ϣ
		const Object* RootAttribute( NodeProperty::GetAttribute na ) const;
		const Object* Attribute( NodeProperty::GetAttribute na ) const;//�õ��ڵ�����
		void SetAttribute( NodeProperty::SetAttribute mt, const Object& obj );//����ĳ���ڵ�����
		IComponent* FindComponent( const eastl::string& name );//Ч�ʵ��£������ҵ�֮�󱣴�
	protected:
		BOHGE_FORCEINLINE ComponentProperty::SubnodeMap& _GetSubnodeMap()
		{
			return m_SubnodeMap;
		}
		BOHGE_FORCEINLINE Node* _GetRoot()
		{
			return m_RootNode;
		}
	public:
		template<typename T>
		BOHGE_FORCEINLINE const T* Attribute( NodeProperty::GetAttribute na )
		{
			return static_cast<const T*>( m_pAttributeDelegateArray[na].Unicast() );
		}
		BOHGE_FORCEINLINE ushort NodeDepth() const//�ýڵ�ĵ������
		{
			return m_NodeDepth;
		}
		BOHGE_FORCEINLINE const eastl::string& GetName() const
		{
			return m_NodeName;
		}
	};
}