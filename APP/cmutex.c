/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~2023
**
** 文件名(Filename): cmutex.c
**
** 描述(Description): 本文件定义Mutex类成员函数实现
**
** 包含的函数(Included Function):
**		CreateCMutex
**		DestroyCMutex
**		CMutexLock
**		CMutexUnLock
** 
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2023年1月3日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2023年1月3日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
/*-----------------------------------------------------------------------------------------
**										   Include
**-----------------------------------------------------------------------------------------
*/
#include "cmutex.h"

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 互斥量上锁 */
static void CMutexLock(void* this);
/* 互斥量解锁 */
static void CMutexUnlock(void* this);

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)对互斥量进行封装 */
/* 2) */
typedef struct SCMutexImpl
{
	/* 互斥量上锁 */
	void (*lock)(void* this);
	/* 互斥量解锁 */
	void (*unlock)(void* this);

#ifdef WINDOWS
	/* 互斥量句柄 */
	HANDLE _mutex;
#endif
	/* 互斥量锁状态 */
	bool _status;
} CMutexImpl;

/*-----------------------------------------------------------------------------------------
**                                   Function Definition
**-----------------------------------------------------------------------------------------
*/
/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CreateCMutex
** 
** 描述(Description): 本函数实现Mutex类构造函数
**
** 输入参数(Input Parameter):
** 
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**		Inory, 2023年1月3日 创建本函数
**		$Log$
** 
**.EH--------------------------------------------------------------------------------------
*/
CMutex* CreateCMutex(void)
{
	CMutex* this = __new(CMutex);

	if (this)
	{
		CMutexImpl* thisImpl = (CMutexImpl*)this;
		/* 成员变量初始化 */
#ifdef WINDOWS
		thisImpl->_mutex = CreateMutex(NULL, FALSE, NULL);
#endif
		thisImpl->_status = false;
		/* 成员函数初始化 */
		thisImpl->lock = CMutexLock;
		thisImpl->unlock = CMutexUnlock;
	}
	else
	{
		printf("Mutex::Mutex()--create Mutex error.\n");
		return nullptr;
	}

	return this;
}
/* END of CreateCMutex */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): DestroyMutex
**
** 描述(Description): 本函数实现Mutex类析构函数
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**		Inory, 2023年1月3日 创建本函数
**		$Log$
**
**.EH--------------------------------------------------------------------------------------
*/
void DestroyCMutex(CMutex* this)
{
#ifdef DEBUG
	printf("Mutex::~Mutex()\n");
#endif
}
/* END of DestroyMutex */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CMutexLock
**
** 描述(Description): 本函数实现互斥量上锁
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**		Inory, 2023年1月3日 创建本函数
**		$Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void CMutexLock(void* this)
{
#ifdef WINDOWS
	/* 互斥量上锁 */
	WaitForSingleObject(((CMutexImpl*)this)->_mutex, INFINITE);
#endif
	/* 锁状态 */
	((CMutexImpl*)this)->_status = true;
}
/* END of CMutexLock */

/*.BH--------------------------------------------------------------------------------------
**
** 函数名(Function Name): CMutexUnlock
**
** 描述(Description): 本函数实现互斥量解锁
**
** 输入参数(Input Parameter):
**
** 输出参数(Output Parameter):
**
** 返回值(Return Value):
**
** 设计注记(Design Annotation):
**
** 更改历史(Modification History):
**		Inory, 2023年1月3日 创建本函数
**		$Log$
**
**.EH--------------------------------------------------------------------------------------
*/
static void CMutexUnlock(void* this)
{
#ifdef WINDOWS
	/* 互斥量上锁 */
	ReleaseMutex(((CMutexImpl*)this)->_mutex);
#endif
	/* 锁状态 */
	((CMutexImpl*)this)->_status = false;
}
/* END of CMutexUnlock */
