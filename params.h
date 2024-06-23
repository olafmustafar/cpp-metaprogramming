#pragma once
#include <tuple>

#define DECLARE_PARAMETERS(X, ...)                                             \
    template <>                                                                \
    struct params<X> {                                                         \
        using type = std::tuple<__VA_ARGS__>;                                          \
        static constexpr const char *name = #X;                                \
    };

template <typename T>
struct params {
    using type = std::tuple<>;
    static constexpr const char *name = "";
};

template <typename T>
using params_t = typename params<T>::type;

template <typename T>
inline constexpr const char * param_name_v = params<T>::name;

template <typename T>
inline constexpr std::size_t param_tuple_size_v =
    std::tuple_size_v<params_t<T>>;
