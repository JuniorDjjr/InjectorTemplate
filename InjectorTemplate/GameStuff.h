/*
Some game related stuff.
Separated by namespace Game:: for better readability between your variables and game variables.
*/

#pragma once
#include "stdafx.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"

namespace Game
{
	int CallExample()
	{
		return ((int(__cdecl *)(int))(0xDEADC0DE))(123);
	}

	auto &variableExample = *(uint32_t*)(0xDEADC0DE);
}
