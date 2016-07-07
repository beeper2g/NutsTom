/**
 * @file    Utility.h
 * @brief   通用辅助函数库集合
 * @version 1.0
 * @author  houguisang@vip.qq.com
 * @date    2014.5.12
 */
#ifndef __Utility_H__
#define __Utility_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <functional>
#include <algorithm>

#ifndef Max
#define Max(a,b) (((a) > (b)) ? (a) : (b))
#endif // !Max

#ifndef Min
#define Min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef SafeDelete
#define SafeDelete(ptr) if (nullptr!=ptr) delete ptr; ptr=nullptr;
#endif // !SafeDelete


namespace Utility
{
    
// 清除字符串空格
std::string& ltrim(std::string& s);
std::string& rtrim(std::string& s);
std::string& trim(std::string& s);

#define MAX_SPLITE_BUF_LEN  2048
template <typename _tFunc>
void SpliteStringImpl(char* src, char sep, _tFunc func)
{
    char* findPos = NULL;
    char* findSrc = src;
    for (;;)
    {
        findPos = strchr(findSrc, sep);
        if (NULL==findPos)
        {
            break;
        }
        int len = findPos-findSrc;
        findSrc[len] = '\0';
        func(findSrc);
        findSrc = findPos + 1;
    }
    if (NULL!=findSrc)
    {
        func(findSrc);
    }
//     char* pos = src;
//     char* tag = pos;
//     while (NULL!=tag && '\0'!=*tag)
//     {
//         if (*tag == sep)
//         {
//             *tag = '\0';
//             func(pos);
//             pos = tag+1;
//         }
//         ++tag;
//     }
//     if (pos!=tag || *pos=='\0')
//     {
//         func(pos);
//     }
}

template <typename _tFunc>
void SpliteStringStrImpl(char* src, const char* sepStr, _tFunc func)
{
    char* findPos = NULL;
    char* findSrc = src;
    int sepLen = strlen(sepStr);
    for (;;)
    {
        findPos = strstr(findSrc, sepStr);
        if (NULL==findPos)
        {
            break;
        }
        int len = findPos-findSrc;
        findSrc[len] = '\0';
        func(findSrc);
        findSrc = findPos + sepLen;
    }
    if (NULL!=findSrc)
    {
        func(findSrc);
    }
}

/**
 * 遍历拆分字符串，遇到结束符则结束调用
 */
template <typename _tFunc>
void SpliteString(const char* src, char sep, _tFunc func)
{
    size_t len = strlen(src);
    if (len > MAX_SPLITE_BUF_LEN)
    {
        char* buf = new char[len+1];
        buf[len] = 0;
        memcpy(buf, src, len);
        SpliteStringImpl(buf, sep, func);
        delete[] buf;
    }
    else
    {
        char buf[MAX_SPLITE_BUF_LEN] = {0};
        memcpy(buf, src, Min(MAX_SPLITE_BUF_LEN, len));
        SpliteStringImpl(buf, sep, func);
    }
}

/**
 * 以字符串作为拆分字符串的条件，对一个源字符串进行拆分，该操作不影响源字符串内容
 */
template <typename _tFunc>
void SpliteStringStr(const char* src, const char* sepStr, _tFunc func)
{
    size_t len = strlen(src);
    if (len > MAX_SPLITE_BUF_LEN)
    {
        char* buf = new char[len+1];
        buf[len] = 0;
        memcpy(buf, src, len);
        SpliteStringStrImpl(buf, sepStr, func);
        delete[] buf;
    }
    else
    {
        char buf[MAX_SPLITE_BUF_LEN] = {0};
        memcpy(buf, src, Min(MAX_SPLITE_BUF_LEN, len));
        SpliteStringStrImpl(buf, sepStr, func);
    }
}

struct TDeleteObject 
{
    template <typename T>
    void operator()(T* pT)
    {
        delete pT;
    }
};

template <typename _tContainer>
void clearContainer(_tContainer& container)
{
    std::for_each(container.begin(), container.end(), TDeleteObject());
    container.clear();
}

template <typename _tContainer, typename _tFunc>
void forEach(_tContainer& container, _tFunc func)
{
    std::for_each(container.begin(), container.end(), func);
}


bool copyFile(const char* to, const char* from);
void makeFolder(const char* folder);
std::string getWriteablePathRoot();
std::string getFullPathName(const char* path, const char* fileName);
std::string getWriteablePathName(const char* file);
}


#endif /*__Utility_H__*/