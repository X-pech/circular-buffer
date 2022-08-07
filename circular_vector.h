#ifndef CIRCULAR_VECTOR_H
#define CIRCULAR_VECTOR_H

#include <vector>
#include "circular_base.h"

template <typename T, int S>
class circular_vector : public circular_base<T, S>
{
    std::vector<T> _data;

    T &get(const size_t &i) override
    {
        return _data[i];
    }

    T get(const size_t &i) const override
    {
        return _data[i];
    }

    void set(const size_t &i, const T &val) override
    {
        if (_data.size() < S) {
            assert(i == _data.size());
            _data.push_back(val);
        } else {
            _data[i] = val;
        }
    }

    void remove(const size_t &i) override
    {
        _data[i].~T();
    }

public:
    circular_vector() : circular_base<T, S>()
    {
        _data = std::vector<T>();
        _data.reserve(S);
    };
};

#endif // CIRCULAR_VECTOR_H
