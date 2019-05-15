#include "core/utils/defer.hpp"

#include <cassert>

using namespace graphcpp;

Defer::Defer(std::function<void(void)> action) :
	_action(std::move(action))
{
	assert(_action);
}

Defer::~Defer()
{
	_action();
}