#include <iostream>
#include <exception>
#include <type_traits>
#include <cassert>
#include <vector>

#include "circular_buffer.h"
#include "circular_queue.h"
#include "circular_vector.h"

struct no_default_constructor_enjoyer
{
    int x;
    no_default_constructor_enjoyer() = delete;
    no_default_constructor_enjoyer(int s)
    {
        x = s * 100;
    }
};

template <template <typename, int> typename C>
void test()
{

    static const size_t N = 5;
    auto buffer = C<long long, N>();
    for (int i = 0; i < N; i++)
    {
        long long x = rand();
        buffer.push(x);
        std::cout << x << " ";
    }

    buffer.push(rand());

    std::cout << std::endl;

    for (int i = 0; i < N; i++)
    {
        std::cout << buffer.back() << " ";
        buffer.pop();
    }

    try
    {
        buffer.push(rand());
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Push safe throws!";
    }

    try
    {
        buffer.pop();
    }
    catch (const std::out_of_range &e)
    {
        std::cout << " Pop from empty throws!";
    }

    std::cout << "\nCool, it works. Let's test no-default-constructor case\n";

    auto testbuf = C<no_default_constructor_enjoyer, 20>();

    std::cout << "Success!\n";
}

int main()
{
    test<circular_buffer>();
    test<circular_queue>();
    test<circular_vector>();
}