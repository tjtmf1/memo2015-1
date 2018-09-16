#include "stdafx.h"
#include <WinSock2.h>
#include <mysql.h>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define ADDRESS	"54.201.117.101"
#define ID		"root"
#define PASSWD	"root"
#define DBNAME	"memo"
//
//CString char2CString(char* inp)
//{
//	int len;
//	CString str;
//	BSTR buf;
//
//	len = MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), NULL, NULL);
//	buf = SysAllocStringLen(NULL, len);
//	MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), buf, len);
//	str.Format(_T("%s"), buf);
//
//	return str;
//}
//char* CString2char(CString& str)
//{
//	long len = str.GetLength();
//	len = len * 2;
//	char* szTemp = new char[len + 1];
//	memset(szTemp, 0, len + 1);
//	USES_CONVERSION;
//	strcpy_s(szTemp, len, T2A(str));
//
//	return szTemp;
//}