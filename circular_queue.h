#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "circular_aligned_storage.h"

// looks pretty useless, didn't want to lose code though

template <typename T, int S>
class circular_queue : public circular_aligned_storage<T, S>
{
    using typename circular_aligned_storage<T, S>::data_cell;
    data_cell *_data = new data_cell[S];

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
    circular_queue() : circular_aligned_storage<T, S>(){};

    ~circular_queue()
    {
        this->clear();
        delete[] _data;
    }
};
#endif // CIRCULAR_QUEUE_H
