#include "HashUtility.h"
#include <functional>

size_t HashUtility::Hash(std::string const& str)
{
    return std::hash<std::string>{}(str);
}

size_t HashUtility::Hash(std::wstring const& str)
{
    return std::hash<std::wstring>{}(str);
}
