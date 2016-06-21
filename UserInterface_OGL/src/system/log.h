#pragma once
#include <common.h>
#include <iostream>
#include <sstream>

namespace ho {
namespace log {

	template<typename T>
	static HO_API void fatal(T msg)
	{
		std::cout << msg << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	template<typename T, typename... Args>
	static HO_API void fatal(T msg, Args&&... args)
	{
		std::cout << msg;
		fatal(args...);
	}

	template<typename T>
	static HO_API void print(T msg)
	{
		std::cout << msg << std::endl;
	}

	template<typename T, typename... Args>
	static HO_API void print(T msg, Args&&... args)
	{
		std::cout << msg;
		print(args...);
	}

}}