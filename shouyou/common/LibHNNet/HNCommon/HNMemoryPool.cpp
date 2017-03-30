/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.

http://www.hotniao.com

All of the content of the software, including code, pictures,
resources, are original. For unauthorized users, the company
reserves the right to pursue its legal liability.
****************************************************************************/

#include "HNMemoryPool.h"   
#include "HNLog.h"
  
namespace HN {

HNMemPool::HNMemPool(std::size_t blockSize, int preAlloc, int maxAlloc)
	: m_blockSize(blockSize)
	, m_maxAlloc(maxAlloc)
	, m_allocated(preAlloc)  
{  
    if ( preAlloc < 0 || maxAlloc == 0 || maxAlloc < preAlloc )  
    {  
		HNLOG_DEBUG("HNMemPool::CMemPool parameter error. \n"); 
    }  
  
    int r = BLOCK_RESERVE;  
    if (preAlloc > r)  
        r = preAlloc;  
    if (maxAlloc > 0 && maxAlloc < r)  
        r = maxAlloc;  
    m_blocks.reserve(r);  
    for (int i = 0; i < preAlloc; ++i)  
    {  
        m_blocks.push_back(new char[m_blockSize]);  
    }  
}  
  
HNMemPool::~HNMemPool()  
{  
    for (BlockVec::iterator it = m_blocks.begin(); it != m_blocks.end(); ++it)  
    {  
        delete [] *it;  
    }  
}  

void* HNMemPool::get()
{  
	std::lock_guard <std::mutex> autoLock(_dataMutex);
    if (m_blocks.empty())  
    {  
        if (m_maxAlloc == 0 || m_allocated < m_maxAlloc)  
        {  
			char* ptr = new (std::nothrow) char[m_blockSize];
			if (ptr)
			{
				++m_allocated;
				return ptr;
			}
			else
			{
				cout << "HNMemPool::get HNMemPool exhausted." << endl;
				return nullptr;
			}
        }  
        else  
        {  
            cout<<"HNMemPool::get HNMemPool exhausted."<<endl;
			return nullptr;
        }  
    }  
    else
    {  
        char* ptr = m_blocks.back();  
        m_blocks.pop_back();
		//HNLOG_WARNING("HNMemPool Size  >> %d", m_blocks.size());
        return ptr;  
    }  
}  
  
void HNMemPool::release(void* ptr)
{  
	if (m_blocks.size() > BLOCK_RESERVE)
	{
		delete [] ptr;
		m_allocated--;
	}
	else
	{
		std::lock_guard <std::mutex> autoLock(_dataMutex);
		m_blocks.push_back(reinterpret_cast<char*>(ptr));
	}
	//HNLOG_WARNING("HNMemPool Size  >> %d", m_blocks.size());
}   

}