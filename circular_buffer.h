#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "circular_aligned_storage.h"

template <typename T, int S>
class circular_buffer : public circular_aligned_storage<T, S>
{
    using typename circular_aligned_storage<T, S>::data_cell;
    data_cell _data[S];

protected:
    data_cell *data() override
    {
        return _data;
    }

    const data_cell *data() const override
    {
        return _data;
    }

public:
    circular_buffer() : circular_aligned_storage<T, S>(){};
    ~circular_buffer()
    {
        this->clear();
    }
};

#endif //CIRCULAR_BUFFER_H
