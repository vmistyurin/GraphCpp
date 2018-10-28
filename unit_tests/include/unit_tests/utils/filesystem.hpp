#pragma once

#include "boost/filesystem.hpp"

namespace graphcpp_testing
{
	namespace fs = boost::filesystem;

	#define CURRENT_DIRECTORY fs::path(__FILE__).parent_path()
}