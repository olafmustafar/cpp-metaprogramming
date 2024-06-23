#include "constructfromargs.h"
#include "paramnames.h"
#include "params.h"
#include "paramscount.h"
#include <cassert>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

struct Foo {
    int v;
};
struct Bar {
    Foo a;
    Foo b;
};

struct Gus {
    Foo a;
    Bar b;
};

struct Tar {};

struct Dur {
    Tar tar;
};

void test_func(int a, int b) { std::cout << a << " and " << b << "\n"; }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_PARAMETERS(Gus, Foo, Bar);
DECLARE_PARAMETERS(Bar, Foo, Foo)
DECLARE_PARAMETERS(Foo, int)
DECLARE_PARAMETERS(Tar)
DECLARE_PARAMETERS(Dur, Tar)

int main() {
    assert(params_count_v<Foo> == 1);
    assert(params_count_v<Bar> == 2);
    assert(params_count_v<Gus> == 3);
    assert(params_count_v<Dur> == 0);
    assert(params_count_v<Tar> == 0);
    assert(params_count_v<int> == 1);

    assert((std::is_same_v<param_sizes_t<Foo>, std::index_sequence<1>>));
    assert((std::is_same_v<param_sizes_t<Bar>, std::index_sequence<1, 1>>));
    assert((std::is_same_v<param_sizes_t<Gus>, std::index_sequence<1, 2>>));

    {
        std::vector<std::string> args = {"123", "321", "11"};
        auto gus = construct_from_args<Gus>(args);
        assert(gus.a.v == 123);
        assert(gus.b.a.v == 321);
        assert(gus.b.b.v == 11);
    }

    {
        std::vector<std::string> args = {"11", "23"};
        auto bar = construct_from_args<Bar>(args);
        assert(bar.a.v == 11);
        assert(bar.b.v == 23);
    }

    {
        std::vector<std::string> args = {"1"};
        auto foo = construct_from_args<Foo>(args);
        assert(foo.v == 1);
    }

    {
        std::vector<std::string> args = {};
        auto tar = construct_from_args<Tar>(args);
        auto dur = construct_from_args<Dur>(args);
    }

    auto x = param_names<Gus>();
    for (auto &xx : x) {
        std::cout << xx << "\n";
    }
}
