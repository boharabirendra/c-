#ifndef Vec_h_
#define Vec_h_

template <class _Tp>
class Vector
{

public:
    typedef unsigned int size_type;

    Vector()
    {
        _m_data = nullptr;
        _m_size = _m_capacity = 0;
    }

    Vector(const size_type _n, const _Tp &_value)
    {
        _m_data = new _Tp(_n * _alloc_factor);

        for (size_type i = 0; i < _n; i++)
        {
            _m_data[i] = _value;
        }

        _m_size = _n;
        _m_capacity = _n * _alloc_factor;
    }

    _Tp &operator[](size_type i)
    {
        return _m_data[i];
    }

    ~Vector()
    {
        if (_m_data != nullptr)
        {
            delete _m_data;
        }
    }

    size_type size()
    {
        return this->_m_size;
    }

    size_type capacity()
    {
        return this->_m_capacity;
    }

    void push_back(const _Tp &_val)
    {
        if (_m_size == _m_capacity)
        {
            _Tp *_m_temp_data = new _Tp(_m_capacity * 2);

            for (size_type i = 0; i < size(); i++)
            {
                _m_temp_data[i] = _m_data[i];
            }

            _m_data = _m_temp_data;
        }

        _m_data[size()] = _val;

        _m_size = size() + 1;
    }

private:
    size_type _m_size;
    size_type _m_capacity;
    _Tp *_m_data = nullptr;
    size_type _alloc_factor = 2;
};

#endif