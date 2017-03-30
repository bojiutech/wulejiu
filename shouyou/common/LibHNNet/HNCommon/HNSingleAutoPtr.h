﻿/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef __HN_AotuPtr_H__
#define __HN_AotuPtr_H__

#include <assert.h>

namespace HN 
{
	template <class T>
	class HNAutoPtr {
	public:
		HNAutoPtr(T * t): _t(t) {}
		
		~HNAutoPtr() 
		{
			delete _t;
		}

		T& operator *()
		{
			return *_t;
		}

		const T& operator *() const
		{
			return *_t;
		}

		T* operator->()
		{
			return _t;
		}

		const T* operator->() const
		{
			return _t;
		}

	private:
		T* _t;
	};


	template <class T>
	class HNPointerArray {
		T* t;
	public:
		HNPointerArray(T * t): t(t) {
		}

		~HNPointerArray() {
			delete [] t;
			t = nullptr;
		}

		T& operator [] (int i)
		{
			assert(i >= 0);
			return t[i];
		}

		const T& operator [] (int i) const
		{
			assert(i >= 0);
			return t[i];
		}

		operator T* ()
		{
			return t;
		}

		operator T* () const
		{
			return t;
		}
	};

};

#endif	//__HN_AotuPtr_H__
