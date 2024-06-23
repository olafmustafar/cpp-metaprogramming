#pragma once
#include "params.h"
#include <stddef.h>
#include <type_traits>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename... Tail>
struct params_count;

template <typename Tupl,
          typename = std::make_index_sequence<std::tuple_size_v<Tupl>>>
struct params_count_impl;

template <typename Tupl, std::size_t... Indexes>
struct params_count_impl<Tupl, std::index_sequence<Indexes...>> {
    static constexpr std::size_t value =
        params_count<std::tuple_element_t<Indexes, Tupl>...>::value;
};

template <>
struct params_count_impl<std::tuple<>, std::index_sequence<>> {
    static constexpr std::size_t value = 0;
};

template <typename T, typename... Tail>
struct params_count<T, Tail...> {
    static constexpr std::size_t value =
        params_count<T>::value + params_count<Tail...>::value;
};

template <typename T>
struct params_count<T> {
    static constexpr std::size_t value = params_count_impl<params_t<T>>::value;
};

template <Arithmetic T>
struct params_count<T> {
    static constexpr std::size_t value = 1;
};

template <typename T>
inline constexpr size_t params_count_v = params_count<T>::value;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

template <typename T,
          typename = std::make_index_sequence<std::tuple_size_v<params_t<T>>>>
struct param_sizes;

template <typename T, std::size_t... Indexes>
struct param_sizes<T, std::index_sequence<Indexes...>> {
    using Tupl = params_t<T>;
    using type = std::index_sequence<
        params_count_v<std::tuple_element_t<Indexes, Tupl>>...>;
};

template <typename T>
using param_sizes_t = param_sizes<T>::type;

