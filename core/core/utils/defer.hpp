#pragma once

#include <functional>

namespace graphcpp
{
	class Defer final
	{
	private:
		std::function<void(void)> _action;

	public:
		explicit Defer(std::function<void(void)> action);
		~Defer();

		Defer& operator=(const Defer&) = delete;
		Defer(const Defer&) = delete;
		Defer(Defer&&) = delete;
		Defer& operator=(Defer&&) = delete;
	};
}