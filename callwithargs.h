#pragma once
#include <stddef.h>
#include <tuple>
#include <utility>

template <size_t Begin, size_t N>
struct call_with_args {
    template <typename Func, typename... Args, typename std::size_t... I>
    static void call_impl(Func f, std::index_sequence<I...>, Args... args) {
        auto tup = std::make_tuple(args...);
        return f(std::get<Begin + I>(tup)...);
    }

    template <typename Func, typename... Args>
    static void call(Func f, Args... args) {
        return call_impl(f, std::make_index_sequence<N>{}, args...);
    }
};
