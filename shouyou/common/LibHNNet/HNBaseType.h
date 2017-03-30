#ifndef __HN_BaseType_H__
#define __HN_BaseType_H__

typedef		char				CHAR;
typedef		unsigned char       BYTE;

typedef		unsigned short      WORD;

typedef		short               SHORT;

typedef		int					INT;
typedef		unsigned int		UINT;

typedef		long long			LLONG;
typedef		unsigned long long	ULLONG;

typedef		double              DOUBLE;
typedef		float               FLOAT;

#define		INVALID_VALUE			UINT(-1)

#define		INVALID_DESKNO			BYTE(-1)
#define		INVALID_DESKSTATION		BYTE(-1)
#define		INVALID_USER_ID         INT(-1)
#define		INVALID_MONEY			ULLONG(-1)

#include <cstring>

#include <cassert>

enum emSocketStatus
{
	SocketStatus_UNKNOW = 0,
	SocketStatus_SUCCESS,
	SocketStatus_RECV,
	SocketStatus_DISCONNECT,
	SocketStatus_ERROR
};

#endif	//__HN_BaseType_H__
