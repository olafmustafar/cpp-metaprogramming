#include "params.h"
#include "paramscount.h"
#include <string>
#include <vector>
#include <cassert>

static std::vector<std::string> take_n(size_t n, std::vector<std::string> &args) {
    std::vector<std::string> a{};
    for (size_t i = 0; i < n; i++) {
        a.push_back(args.front());
        args.erase(args.begin());
    }
    return a;
}

template <typename T>
T construct_from_args(std::vector<std::string> const &args);

template <typename T, size_t... ParamSizesI, size_t... TupleI>
T construct_from_args_impl(std::vector<std::string> &args,
                           std::index_sequence<ParamSizesI...>,
                           std::index_sequence<TupleI...>) {
    return T{construct_from_args<std::tuple_element_t<TupleI, params_t<T>>>(
        take_n(ParamSizesI, args))...};
}

template <typename T>
T construct_from_args(std::vector<std::string> const &args) {
    assert(args.size() == params_count_v<T>);

    std::vector<std::string> copy{args.begin(), args.end()};
    return construct_from_args_impl<T>(
        copy, param_sizes_t<T>{},
        std::make_index_sequence<param_tuple_size_v<T>>{});
}

template <>
inline int construct_from_args<int>(std::vector<std::string> const &args) {
    return std::stoi(args[0]);
}
