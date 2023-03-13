#pragma once

#include <chrono>
#include <type_traits>

namespace lava
{
	template<typename TBase, typename... TDerived>
	constexpr bool is_base_of_n_v = (std::is_base_of_v<TBase, TDerived> && ...);

	template<typename TBase, typename... TDerived>
	struct is_base_of_n : std::bool_constant<is_base_of_n_v<TBase, TDerived...>> {};

	template<typename TExpected, typename... TActual>
	constexpr bool is_same_as_n_v = (std::is_same_v<TExpected, TActual> && ...);

	template<typename TExpected, typename... TActual>
	struct is_same_as_n : std::bool_constant<is_same_as_n_v<TExpected, TActual...>> {};

	template<typename T>
	constexpr bool is_number_v = (std::is_integral_v<T> || std::is_floating_point_v<T>);

	template<typename T>
	struct is_number : std::bool_constant<(std::is_integral_v<T> || std::is_floating_point_v<T>)> {};
}
