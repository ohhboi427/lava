#pragma once

#include <chrono>
#include <type_traits>

namespace lava
{
	template<typename TBase, typename... TDerived>
	concept is_base_of_n = (std::is_base_of_v<TBase, TDerived> && ...);

	template<typename TExpected, typename... TActual>
	concept is_same_as_n = (std::is_same_v<TExpected, TActual> && ...);
}
