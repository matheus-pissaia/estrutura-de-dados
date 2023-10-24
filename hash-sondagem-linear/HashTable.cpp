#include <iostream>
#include <string>
#include <vector>

class HashTable
{
    private:
        std::vector<std::string> _vector;

        bool _isEmpty(size_t& pos)
        {
            return _vector[pos] == "-1" || _vector[pos] == "-2";
        }

    public:
        HashTable(int len)
        {
            _vector = std::vector<std::string>(len);
            std::fill(_vector.begin(), _vector.end(), "-1");
        }

        void insert(std::string& el)
        {
            size_t pos = hash(el);

            if (_isEmpty(pos))
            {
                _vector[pos] = el;
                return;
            }

            if (_vector[pos] == el)
                return;

            // TODO improve last case to only use one for-loop (rotate vector maybe?)
            for (size_t i = pos + 1; i < _vector.size(); i++)
            {
                if (_isEmpty(i))
                {
                    _vector[i] = el;
                    return;
                }
            }

            for (size_t i = 0; i < pos; i++)
            {
                if (_isEmpty(i))
                {
                    _vector[i] = el;
                    return;
                }
            }
        }

        void remove(std::string& el)
        {
            size_t pos = hash(el);

            if (_vector[pos] == "-1" || _vector[pos] == "-2")
                return;

            if (_vector[pos] == el)
            {
                _vector[pos] = "-2";
                return;
            }

            // TODO improve last case to only use one for-loop (rotate vector maybe?)
            for (size_t i = pos + 1; i < _vector.size(); i++)
            {
                if (_vector[i] == el)
                {
                    _vector[i] = "-2";
                    return;
                }
            }

            for (size_t i = 0; i < pos; i++)
            {
                if (_vector[i] == el)
                {
                    _vector[i] = "-2";
                    return;
                }
            }
        }

        size_t hash(std::string& el)
        {
            return el.length() % _vector.size();
        }

        void print_table()
        {
            for (size_t i = 0; i < _vector.size(); i++)
            {
                std::cout << _vector[i] << "\n";
            }
        }
};
