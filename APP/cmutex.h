﻿/*-----------------------------------------------------------------------------------------
**
** 版权(Copyright): Inory, 2022~2023
**
** 文件名(Filename): cmutex.h
**
** 描述(Description): 本文件定义Mutex类,该类实现互斥锁,用于保证共享数据操作完整性
**
** 设计注记(Design Annotation):
**
** 作者(Author):
**      Inory, 2023年1月2日开始编写本文件
**
** 更改历史(Modification History):
**      Inory, 2023年1月2日 创建本文件
**      $Revision$
**      $Date$
**      $Author$
**      $Log$
**
**-----------------------------------------------------------------------------------------
*/
#ifndef CMUTEX_H
#define CMUTEX_H

/*-----------------------------------------------------------------------------------------
**										   Include
**-----------------------------------------------------------------------------------------
*/
#include "global.h"
#ifdef WINDOWS
#include <windows.h>
#endif

/*-----------------------------------------------------------------------------------------
**                                     Class Definition
**-----------------------------------------------------------------------------------------
*/
/* <类描述> */
/* 1)对互斥量进行封装 */
/* 2) */
typedef struct SCMutex
{
	/* 互斥量上锁 */
	void (*lock)(void* this);
	/* 互斥量解锁 */
	void (*unlock)(void* this);

	char privateData[8];
} CMutex;

/*-----------------------------------------------------------------------------------------
**                                   Function Declaration
**-----------------------------------------------------------------------------------------
*/
/* 构造函数 */
extern CMutex* CreateCMutex(void);
/* 析构函数 */
extern void DestroyCMutex(CMutex* this);

#endif /* CMUTEX_H */
