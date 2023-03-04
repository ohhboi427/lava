#pragma once

#include <functional>
#include <vector>

namespace lava
{
	template<typename... Args>
	class event
	{
	public:
		using callback_t = std::function<void(Args...)>;

		event() = default;
		event(const event&) = delete;
		event(event&&) noexcept = delete;
		~event() = default;

		event& operator=(const event&) = delete;
		event& operator=(event&&) noexcept = delete;

		event& operator+=(const callback_t& callback)
		{
			m_callbacks.push_back(callback);

			return *this;
		}

		void operator()(const Args&... args)
		{
			for(auto& callback : m_callbacks)
			{
				callback(args...);
			}
		}

	private:
		std::vector<callback_t> m_callbacks;
	};
}
