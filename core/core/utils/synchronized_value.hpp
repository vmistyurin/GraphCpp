#pragma once

#include <functional>
#include <mutex>

namespace graphcpp
{
	template<class ValueType>
	class SynchronizedValue final
	{
	private:
		ValueType _value;
		mutable std::mutex _mutex;

	public:
		SynchronizedValue(ValueType&& value);

		void perform_function(std::function<void(ValueType&)> function);
		void perform_function(std::function<void(const ValueType&)> function) const;

		const ValueType& value() const;
	};

	template<class ValueType>
	SynchronizedValue<ValueType>::SynchronizedValue(ValueType&& value) :
		_value(std::move(value))
	{
	}

	template<class ValueType>
	void SynchronizedValue<ValueType>::perform_function(std::function<void(ValueType&)> function)
	{
		std::lock_guard lock(_mutex);

		function(_value);
	}

	template<class ValueType>
	void SynchronizedValue<ValueType>::perform_function(std::function<void(const ValueType&)> function) const
	{
		std::lock_guard lock(_mutex);

		function(_value);
	}

	template<class ValueType>
	const ValueType& SynchronizedValue<ValueType>::value() const
	{
		return _value;
	}
}
