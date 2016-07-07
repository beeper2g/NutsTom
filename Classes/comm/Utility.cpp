#include "Utility.h"
#include "Cocos2dxPlatform.h"
#include <stdlib.h>
#include <sys/stat.h>


#ifdef WIN32
#include <direct.h>
#include <sys/stat.h>
#include <windows.h>
#include <io.h>
#else
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#endif

namespace Utility
{
bool copyFile(const char* to, const char* from)
{
    ssize_t file_size = 0;  
    Data data = FileUtils::getInstance()->getDataFromFile(from);
    if (data.isNull())
    {
        return false;
    }

    FILE * file_to = fopen(to, "wb");
    if (NULL != file_to)
    {
        fwrite(data.getBytes(), 1, data.getSize(), file_to);
        fflush(file_to);
        fclose(file_to);
    }
    return (NULL!=file_to);
}

void makeFolder(const char* folder)
{
#ifdef WIN32
    _mkdir(folder);
#else
    umask(0);
    mkdir(folder, S_IRWXG|S_IRWXO|S_IRWXU);
#endif
}

std::string getWriteablePathRoot()
{
    std::string strPath(FileUtils::getInstance()->getWritablePath());
    makeFolder(strPath.c_str());
    return strPath;

}

std::string getFullPathName(const char* path, const char* fileName)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
    return fileName;//FileUtils::getInstance()->fullPathFromRelativeFile(fileName, path);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
    return FileUtils::getInstance()->fullPathForFilename(fileName);
#else
    std::string temp(path);
    temp += "/";
    temp += fileName;
    return FileUtils::getInstance()->fullPathForFilename(temp.c_str());  
#endif
}

std::string getWriteablePathName(const char* file)
{
    return (Utility::getWriteablePathRoot()+file);
}

}