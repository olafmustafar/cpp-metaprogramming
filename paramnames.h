#pragma once
#include "params.h"
#include "paramscount.h"
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
std::vector<std::string>
param_names(std::string const &prefix = param_name_v<T>);

template <typename Tupl, std::size_t... I>
std::vector<std::string> param_names_impl(std::string const &prefix,
                                          std::index_sequence<I...>) {
    std::vector<std::vector<std::string>> vec{
        param_names<std::tuple_element_t<I, Tupl>>(
            prefix + "-" + param_name_v<std::tuple_element_t<I, Tupl>>)...};

    std::vector<std::string> joined{};
    for (auto &strvec : vec) {
        for (auto &str : strvec) {
            joined.push_back(str);
        }
    }
    return joined;
}

template <>
inline std::vector<std::string>
param_names_impl<std::tuple<>>(std::string const &prefix,
                               std::index_sequence<>) {
    return {prefix};
}

template <typename T>
std::vector<std::string> param_names(std::string const &prefix) {
    return param_names_impl<params_t<T>>(
        prefix, std::make_index_sequence<param_tuple_size_v<T>>{});
}
