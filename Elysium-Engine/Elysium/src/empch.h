/**
 * FILENAME		: empch.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: The precompiled header for the Elysium Puzzle Engine.
 */
#pragma once

// ------------- Utilities ------------- //

#include "Core/Utility/Asserts.h"

#include <iostream>
#include <functional>
#include <memory>
#include <utility>
#include <algorithm>
#include <tuple>

// ------------- Data Structures ------------- //

#include <string>
#include <sstream>
#include <vector>

// ------------- Platform Specific Includes ------------- //

#ifdef EM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif