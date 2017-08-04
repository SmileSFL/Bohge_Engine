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
#include "Delegate.hpp"
#include "Config.h"




namespace BohgeEngine
{
	//����ͶӰˮ��Ĺ�ϵ����֡update�е����������ȫ��ͳһ����һ֡���У�����ᵼ�¶��߳�ˮ����������
	//�µ�������������x���ϵ���ת��Ҫ������watergrid
	//class ActionManager;
	class BOHGE_FRAMEWORK ICamera : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR( ICamera );
	private:
		enum CameraProjectionType
		{
			CPT_PERSPECTIVE = 0,
			CPT_ORTHOGRAPHI,
		};
	private:
		FunctionPtr				m_ResizeFunction;
		CameraProjectionType	m_ProjectionType;
		float			m_Near;
		float			m_Far;
		float			m_Middle;
		float			m_Fov;
		float			m_Aspect;
		vector2f		m_NearQ_Q;//��shader�����������
		vector3f		m_LineDepthParam;//������ȵĲ���
		vector3f		m_LineDepthParamBias;//������ȵĲ���,��ƫ�Ƶ�
		//��������updata�п϶��ı��
		bool			m_isChange;// ������б仯
		Matrix44f		m_View;//��ͼ����
		Matrix44f		m_Project; //ͶӰ����
		Matrix44f		m_ViewProject;//ͶӰ��ͼ
		Matrix44f		m_ProjectBias;//ͶӰ��ƫ�ƾ���

		//�����Ǳ���࣬����Ҫ��ʱ��ı��
		mutable bool			m_isDirtyRotation;
		mutable Matrix33f		m_Rotation;//��ת
		mutable bool			m_isDirtyTransform;
		mutable vector3f		m_Transform;//�������е�ƽ��
		mutable bool			m_isDirtyViewProjectBias;
		mutable Matrix44f		m_ViewProjectBias;//ͶӰ��ͼ�ı��˾���
		mutable bool			m_isDirtyUnView;
		mutable Matrix44f		m_UnView;//view�������
		mutable bool			m_isDirtyUnProject;
		mutable Matrix44f		m_UnProject;//project�������
		mutable bool			m_isDirtyUnViewProject;
		mutable Matrix44f		m_UnViewProject;//view,project�������
		mutable bool			m_isDirtyFrustum;//��׶���
		mutable Frustumf		m_Frustum;
		//���Ͻ���

		vector3f		m_Position;//λ��
		vector3f		m_LookAt;//����ĵ�
		vector3f		m_Up;//����
		vector3f		m_ViewDirction;//������

		bool			m_isNearFarChange;

		//�����Լ��
		Delegate1<bool, ICamera&>	m_EventOnCameraUpdate;
	protected:
		float			m_MoveSpeed;
		float			m_RotateSpeed;
		float			m_ZoomSpeed;
	private:
		void _DoCopy( const ICamera& rhs );
	public:
		ICamera();
		virtual ~ICamera();
		ICamera(const ICamera& rhs)
		{
			_DoCopy( rhs );
		}
		ICamera& operator = ( const ICamera& rhs )
		{
			_DoCopy( rhs );
			return *this;
		}
	protected:
		virtual void _OnlookAt( ){};//���ⲿ����lookat��ʱ�����_LookAt�������
		void _LookAt(const vector3f& position, const vector3f& lookAt, const vector3f& up);
	public:
		void OnResizeview( const ViewResolution& vr );
	public:
		/*����͸��ͶӰ����radian���ӽǿ�ȣ�aspect�Ǵ��ڿ�߱ȣ�near�ǽ�����ƽ�棬far��Զ����ƽ��*/
		void CreatePerspectiveProjection(float near, float farClip);
		void CreatePerspectiveProjection(float radian, float aspect, float near, float farClip);
		/*����ͶӰ����size�������еİ�Χ��Χ��aspect�Ǵ��ڿ�߱ȣ�near�ǽ�����ƽ�棬far��Զ����ƽ��*/
		void CreateOrthographiProjection(float w, float h, float n, float f);
		void CreateOrthographiProjection(float n, float f);
		/*����λ�ã�lookat����*/
		//void CreateView(vector3f& position, vector3f& dir, vector3f& up);
		void Update( );
		/*������Ļ�ռ䣨opengl����ϵ���ĵ㣬����ʰȡ����*/
		Rayf PickRay( const vector2f& secen );
		void Move( const vector3f& disvector );//�ƶ�һ�ξ��룬�����ƶ�
		void SetPosition(const vector3f& position);
		void SetForward(const vector3f& forward);
		void SetMoveRotateZoom( float mov, float rot, float zoom );//�����˶��ٶ�(unit/s)һ����Ļ�ռ䣨�������棩����ת�ĽǶȺ�����
		void AttachCamera();
		void DetachCamera();
	public:
		//virtual void OnActionInput( ActionManager& am ) = 0;
	public:
		BOHGE_FORCEINLINE FunctionPtr ConectOnUpdateCallBack( Delegate1<bool, ICamera&>::FunctionType* ptr )
		{
			return m_EventOnCameraUpdate.Connect( ptr );
		}
		BOHGE_FORCEINLINE void DisconectOnUpdateCallBack( FunctionPtr ptr )
		{
			m_EventOnCameraUpdate.ClearConnect( ptr );
		}
		BOHGE_FORCEINLINE void ClearOnUpdateCallBack( )
		{
			m_EventOnCameraUpdate.ClearConnect();
		}
		BOHGE_FORCEINLINE bool isNearFarChange()
		{
			bool r = m_isNearFarChange;
			m_isNearFarChange = false;
			return r;
		}
		BOHGE_FORCEINLINE float MoveSpeed()
		{
			return m_MoveSpeed;
		}
		BOHGE_FORCEINLINE float RotateSpeed()
		{
			return m_RotateSpeed;
		}
		BOHGE_FORCEINLINE float ZoomSpeed()
		{
			return m_ZoomSpeed;
		}
		BOHGE_FORCEINLINE float Fov() const
		{
			return m_Fov;
		}
		BOHGE_FORCEINLINE float Aspect() const
		{
			return m_Aspect;
		}
		BOHGE_FORCEINLINE void LookAt(const vector3f& position, const vector3f& look, const vector3f& up)
		{
			this->_LookAt(position, look, up);
			this->_OnlookAt( );
		}
		BOHGE_FORCEINLINE const vector3f& GetForward() const
		{
			return m_ViewDirction;
		}
		BOHGE_FORCEINLINE const vector3f& GetTransform() const
		{
			if ( m_isDirtyTransform )
			{
				m_isDirtyTransform = false;
				m_Transform = vector3f( GetView().a41, GetView().a42, GetView().a43 );
			}
			return m_Transform;
		}
		BOHGE_FORCEINLINE const Matrix33f& GetRotation() const
		{
			if( m_isDirtyRotation )
			{
				m_isDirtyRotation = false;
				m_Rotation = Matrix33f( GetView() );
			}
			return m_Rotation;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetView() const
		{
			return m_View;
		}
		/*����ͶӰ����*/
		BOHGE_FORCEINLINE const Matrix44f& GetProject() const
		{
			//if( m_isChange )
			//{
			//	Update();
			//}
			return m_Project;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetViewProj() const
		{
			//if( m_isChange )
			//{
			//	Update();
			//}
			return m_ViewProject;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetProjectBais() const
		{
			return m_ProjectBias;
		}
		/*������z-fighting��ʱ����õ�ƫ��ͶӰ����*/
		BOHGE_FORCEINLINE const Matrix44f& GetViewProjBias() const
		{
			if( m_isDirtyViewProjectBias )
			{
				m_isDirtyViewProjectBias = false;
				m_ViewProjectBias = GetView() * GetProjectBais();
			}
			return m_ViewProjectBias;
		}
		BOHGE_FORCEINLINE const vector3f& GetPosition() const
		{
			return m_Position;
		}
		BOHGE_FORCEINLINE const vector3f& GetLookAt() const
		{
			return m_LookAt;
		}
		BOHGE_FORCEINLINE const vector3f& GetUp() const
		{
			return m_Up;
		}
		BOHGE_FORCEINLINE float GetNear() const
		{
			return m_Near;
		}
		BOHGE_FORCEINLINE float GetFar() const
		{
			return m_Far;
		}
		BOHGE_FORCEINLINE float GetMiddle() const
		{
			return m_Middle;
		}
		BOHGE_FORCEINLINE const vector2f& GetNearQ_Q() const
		{
			return m_NearQ_Q;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetUnViewProj() const
		{
			if( m_isDirtyUnViewProject )
			{
				m_isDirtyUnViewProject = false;
				m_UnViewProject = GetUnProject() * GetUnView();
			}
			return m_UnViewProject;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetUnView() const
		{
			if( m_isDirtyUnView )
			{
				m_isDirtyUnView = false;
				GetView().GetInverse(m_UnView, false);
			}
			return m_UnView;
		}
		BOHGE_FORCEINLINE const Matrix44f& GetUnProject() const
		{
			if( m_isDirtyUnProject )
			{
				m_isDirtyUnProject = false;
				GetProject().GetInverse(m_UnProject);
			}
			return m_UnProject;
		}
		BOHGE_FORCEINLINE const Frustumf& GetFrustum() const//�õ���׶
		{
			if( m_isDirtyFrustum )
			{
				m_isDirtyFrustum = false;
				m_Frustum.FromMatrix( GetViewProj(), GetUnViewProj() );
			}
			return m_Frustum;
		}
		BOHGE_FORCEINLINE const vector3f& LineDepthParam() const//����ƽ��ֵ
		{
			//������ȹ�ʽ d = ( z - m_LineDepthParam.m_x ) * m_LineDepthParam.m_y;
			//����ʵ�ʾ��� z = d * m_LineDepthParam.m_z + m_LineDepthParam.m_x;
			return m_LineDepthParam;
		}
		BOHGE_FORCEINLINE const vector3f& LineDepthParamBais() const//����ƽ��ֵ
		{
			return m_LineDepthParamBias;
		}
	};






	//class TrackballCamera : public ICamera
	//{
	//private:
	//	bool		m_isReverse;
	//	vector2f	m_ZoomMaxMinPow;
	//	vector3f	m_Target;
	//	vector3f	m_VerticalAixs;//��ֱ�ƶ���
	//public:
	//	TrackballCamera( );
	//private:
	//	virtual void _OnlookAt( );//���ⲿ����lookat��ʱ�����_LookAt�������
	//public:
	//	virtual void OnActionInput( ActionManager& am );
	//public:
	//	void Rotate( float xd, float yd );//���뷶Χ[-n,n]�ֱ�����Χ��right��up��ת��rotSpeed*xd,yd�Ƕ�
	//	void ZoomInOut( float d );//�Ŵ���С��ͬ��
	//public:
	//	BOHGE_FORCEINLINE void SetZoomMaxMin( const vector2f& maxmin )
	//	{
	//		m_ZoomMaxMinPow.m_x = maxmin.m_x * maxmin.m_x;
	//		m_ZoomMaxMinPow.m_y = maxmin.m_y * maxmin.m_y;
	//	}
	//	BOHGE_FORCEINLINE const vector3f& GetTarget() const
	//	{
	//		return m_Target;
	//	}
	//};



	//class FPSCamera : public ICamera
	//{
	//private:
	//	vector3f	m_VerticalAixs;//��ֱ�ƶ���
	//public:
	//	FPSCamera( );
	//private:
	//	virtual void _OnlookAt( );//���ⲿ����lookat��ʱ�����_LookAt�������
	//public:
	//	virtual void OnActionInput( ActionManager& am );
	//public:
	//	void Rotate( float xd, float yd );//���뷶Χ[-n,n]�ֱ�����Χ��right��up��ת��rotSpeed*xd,yd�Ƕ�
	//	void Move( const vector3f& dis );//�ƶ�һ������
	//};




	//class EditCamera : public ICamera // ר��Ϊ�༭����Ƶ����
	//{
	//private:
	//	bool		m_isReverse;
	//	vector3f	m_Target;
	//	vector3f	m_VerticalAixs;//��ֱ�ƶ���
	//public:
	//	EditCamera( );
	//private:
	//	virtual void _OnlookAt( );//���ⲿ����lookat��ʱ�����_LookAt�������
	//public:
	//	virtual void OnActionInput( ActionManager& am );
	//public:
	//	void Rotate( float xd, float yd );//���뷶Χ[-n,n]�ֱ�����Χ��right��up��ת��rotSpeed*xd,yd�Ƕ�
	//	void Move( const vector3f& dis );//�ƶ�һ������
	//	void ZoomInOut( float d );
	//	BOHGE_FORCEINLINE const vector3f& GetTarget() const
	//	{
	//		return m_Target;
	//	}
	//};


	//�µ�������������x���ϵ���ת��Ҫ������watergrid
}