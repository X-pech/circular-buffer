#ifndef CIRCULAR_BASE_H
#define CIRCULAR_BASE_H

template <typename T, int S>
class circular_base
{
protected:
    struct Index
    {
        size_t _i = 0;

        Index(const size_t &i = 0)
        {
            _i = i;
        }

        operator size_t()
        {
            return _i;
        }

        Index operator++(int)
        {
            Index old = _i;
            _i++;
            if (_i >= S)
            {
                _i -= S;
            }
            return old;
        }

        Index operator--(int)
        {
            Index old = _i;
            if (_i == 0)
            {
                _i += S;
            }
            _i--;
            return old;
        }

        bool operator==(const Index &r)
        {
            return _i == r._i;
        }

        bool operator!=(const Index &r)
        {
            return _i != r._i;
        }
    };

private:
    Index begin;
    Index end;
    size_t _size = 0;
    size_t capacity = 0;

    virtual T &get(const size_t &i) = 0;
    virtual T get(const size_t &i) const = 0;
    virtual void set(const size_t &i, const T &value) = 0;
    virtual void remove(const size_t &i) = 0;

    void throw_if_empty() const
    {
        if (this->size() == 0)
        {
            throw std::out_of_range("Tried to get element from an empty circular buffer");
        }
    }

public:
    circular_base()
    {
    }

    T &front()
    {
        throw_if_empty();
        return this->get(begin);
    }

    T front() const
    {
        throw_if_empty();
        return this->get(begin);
    }

    T &back()
    {
        throw_if_empty();
        Index nend = end;
        nend--;
        return this->get(nend);
    }

    T back() const
    {
        throw_if_empty();
        Index nend = end;
        nend--;
        return this->get(nend);
    }

    size_t size() const
    {
        return _size;
    }

    void push(const T &value)
    {
        this->set(end, value);
        if (_size == S)
        {
            begin++;
            _size--;
        }
        _size++;
        end++;
    }

    void push_safe(const T& value) {
        if (_size == S) {
            throw std::out_of_range("Tried to push to a full circular collection");
        }
    }

    void pop()
    {
        if (_size == 0)
        {
            throw std::out_of_range("Tried to pop from an empty circular collection");
        }

        this->remove(end);

        end--;
        _size--;
    }

    void clear()
    {
        while (size() != 0)
        {
            this->pop();
        }
    }
};

#endif // CIRCULAR_BASE_H