#pragma once

#include "boost/filesystem.hpp"

namespace graphcpp::testing
{
	namespace fs = boost::filesystem;
    
	const auto test_data_path = fs::path(TEST_DATA_PATH);
}
