/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once
#include   <stdarg.h>


/// 打印调试信息
extern void DebugPrintf_debug(const char *p, ...);
/// 打印错误信息
extern void ErrorPrintf_debug(const char *p, ...);

#ifndef _DEBUG
# define DebugPrintf __noop
#else
# define DebugPrintf DebugPrintf_debug
#endif
# define DebugPrintf DebugPrintf_debug