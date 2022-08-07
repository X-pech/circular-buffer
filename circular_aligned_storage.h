#ifndef CIRCULAR_ALIGNED_STORAGE_H
#define CIRCULAR_ALIGNED_STORAGE_H

#include "circular_base.h"

template <typename T, int S>
class circular_aligned_storage : public circular_base<T, S>
{
    T &get(const size_t &i) override
    {
        return *reinterpret_cast<T *>(data() + i);
    }

    T get(const size_t &i) const override
    {
        return *reinterpret_cast<const T *>(data() + i);
    }

    void set(const size_t &i, const T &v) override
    {
        new (reinterpret_cast<T *>(data() + i)) T(v);
    }

    void remove(const size_t &i) override
    {
        reinterpret_cast<T *>(data() + i)->~T();
    }

public:
    circular_aligned_storage() : circular_base<T, S>(){};

protected:
    typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type data_cell;
    virtual data_cell *data() = 0;
    virtual const data_cell *data() const = 0;
};

#endif // CIRCULAR_ALIGNED_STORAGE_H
