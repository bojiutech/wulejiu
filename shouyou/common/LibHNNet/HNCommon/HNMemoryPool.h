﻿/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#ifndef MemoryPool_h__
#define MemoryPool_h__

#include <vector>
#include <iostream>
#include <mutex>
  
using namespace std;  
  
/* 
    在内存池中分配固定大小的内存块 
 
    该类的目的是加速内存分配速度，并且减少因重复分配相同 
    内存时产生的内存碎片，比如在服务器应用程序中。 
*/  
namespace HN
{
	class HNMemPool
	{  
	public:  
  
		//创建大小为blockSize的内存块，内存池数目为预分配的数目preAlloc   
		HNMemPool(std::size_t blockSize, int preAlloc = 0, int maxAlloc = 0);  
  
		~HNMemPool();  
  
		//获取一个内存块。如果内存池中没有足够的内存块，则会自动分配新的内存块   
		//如果分配的内存块数目达到了最大值，则会返回一个异常   
		void* get();  
  
		//释放当前内存块，将其插入内存池   
		void release(void* ptr);  
  
		//返回内存块大小   
		std::size_t blockSize() const;  
  
		//返回内存池中内存块数目   
		int allocated() const;  
  
		//返回内存池中可用的内存块数目   
		int available() const;  
  
	private:  
		HNMemPool();  
		HNMemPool(const HNMemPool&);  
		HNMemPool& operator = (const HNMemPool&);  
  
		enum  
		{  
			BLOCK_RESERVE = 32  
		};  
  
		typedef std::vector<char*> BlockVec;  
  
		std::size_t m_blockSize;  
		int         m_maxAlloc;  
		int         m_allocated;  
		BlockVec    m_blocks;
		std::mutex	_dataMutex;
	};  
  
	inline std::size_t HNMemPool::blockSize() const  
	{  
		return m_blockSize;  
	}  
  
  
	inline int HNMemPool::allocated() const  
	{  
		return m_allocated;  
	}  
  
  
	inline int HNMemPool::available() const  
	{  
		return (int) m_blocks.size();  
	}    
}

#endif // MemoryPool_h__
