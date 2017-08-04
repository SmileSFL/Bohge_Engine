// pThreadTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <windows.h>


using namespace std;

string SharedData;

void * thread_function_r(void *arg); //�̺߳���
/*
�ź�������������Ϊ�ṹsem_t������������һ�������͵���������sem_init����������ʼ��һ���ź���������ԭ��Ϊ������
extern int sem_init __P ((sem_t *__sem, int __pshared, unsigned int __value));����
__semΪָ���ź����ṹ��һ��ָ�룻__pshared��Ϊ��ʱ���ź����ڽ��̼乲������ֻ��Ϊ��ǰ���̵������̹߳���__value�������ź����ĳ�ʼֵ������
*/
sem_t sem_r, sem_w; //semphore���ź��������������ڱ�֤���̺��̼߳��ͬ��
pthread_mutex_t mutex; //����������֤�̷߳��ʵĻ��⣬����һ��������������
int main(int argc, char *argv[])
{
	int res;
	pthread_t a_thread_r, b_thread_r; //�߳�ID��������������ƣ�����Ϊpid_t

	/*�ź�����sem_init���������ģ�����������˵����
	����#include<semaphore.h>
	  int sem_init (sem_t *sem, int pshared, unsigned int value);
	  ��������������Ƕ���semָ�����ź������г�ʼ�������ú����Ĺ���ѡ���ָ��һ���������͵ĳ�ʼֵ��pshared�����������ź��������͡���� pshared��ֵ�ǣ����ͱ�ʾ���ǵ�ǰ��̵ľֲ��ź����������������̾��ܹ���������ź�����
	  */
	res = sem_init(&sem_r, 0, 0);
	if ( res != 0) 
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	res = sem_init(&sem_w, 0, 2);
	if ( res != 0) 
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ( pthread_mutex_init(&mutex, NULL) != 0 ) //����������֤�̷߳��ʵĻ��⣬���������ʼ����Ĭ�����Գ�ʼ������������NULL�����Ĺ���
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}


	for ( int i = 0 ; i < 10 ; i ++)
	{
		pthread_create(&a_thread_r, NULL, thread_function_r, new int(i) );
	}
	while(1) //�����ܡ�������ִ��д�����
	{
		sem_wait(&sem_r); //����sem_wait( sem_t *sem )������������ǰ�߳�ֱ���ź���sem��ֵ����0�����������sem��ֵ��һ������������Դ��ʹ�ú���١�����sem_trywait ( sem_t *sem )�Ǻ���sem_wait�����ķ������汾����ֱ�ӽ��ź���sem��ֵ��һ������sem_destroy(sem_t *sem)�����ͷ��ź���sem��
		pthread_mutex_lock(&mutex);
		if( 0 != SharedData.size() )
		{
			cout<<SharedData.c_str();
			SharedData.clear();
		}
		else
		{
			cout<<"Empty data\n";
		}
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_w); //����sem_post( sem_t *sem )���������ź�����ֵ�������߳�����������ź�����ʱ���������������ʹ���е�һ���̲߳���������ѡ�����ͬ�������̵߳ĵ��Ȳ��Ծ����ġ�
		Sleep(1);
	}
	return 0;
}
void * thread_function_r(void *arg) //�����ܡ��̸߳����ȡ
{
	int i = *((int*)arg);
	string num;
	num.resize( 1 );
	num[0] = '0' + i;
	while(1)
	{
		sem_wait(&sem_r);
		pthread_mutex_lock(&mutex); //��ȡ������������������������pthread_mutex_trylock���ԶԻ��������������ʧ�ܷ���EBUSY
		if ( 0 == SharedData.size() )
		{
			SharedData = "in ";
			SharedData += num;
			SharedData += " function wirted\n";
		}
		else
		{
			cout<<"Avoid over write ather's data\n";
		}
		pthread_mutex_unlock(&mutex); //�ͷŻ�����
		sem_post(&sem_w);
		Sleep(1);
	}
}