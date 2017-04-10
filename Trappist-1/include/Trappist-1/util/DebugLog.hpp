#pragma once

#ifdef _DEBUG
#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;
#define LOG_IF(condition, msg) if(condition) { LOG(msg) }
#define ERR(msg) std::cerr << msg << std::endl;
#define ERR_IF(condition, msg) if(condition) { ERR(msg) }
#define IF(condition, statements) if(condition) { statements }
#define IF_ELSE(condition, statements_if, statements_else) if(condition) { statements_if } else { statements_else }
#else // _DEBUG
#define LOG(string)
#define LOG_IF(condition, string)
#define ERR(msg)
#define ERR_IF(condition, msg)
#define IF(condition, statements)
#define IF_ELSE(condition, statements_if, statements_else)
#endif // _DEBUG
