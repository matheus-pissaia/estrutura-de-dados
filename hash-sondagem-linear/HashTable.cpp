#include <iostream>
#include <string>
#include <vector>

class HashTable
{
    private:
        std::vector<std::string> _vector;

        /* 
            Checks if the position in the vector is empty.
            It returns `true` if the position contains either "-1" or "-2", indicating that it is empty.
            Otherwise, it returns `false`.
        */
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

        /* 
            Inserts an element into the hash table.

            If the position is empty, then the element is inserted there.

            If the position is not empty:
            1. Returns if the element on the current position is the same that we are trying to insert.
            2. Search an empty position to be inserted through the vector, using the linear probing strategy.
         */
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

        /* 
            Removes an element from the hash table.

            If the position is empty, then the function just returns.

            If the position is not empty:
            1. Removes the element on the current position if is the same that we passed.
            2. Search the element to be removed through the vector, using the linear probing strategy.
         */
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

        /* 
        
            The hash function that takes a string as input and returns the hash value. 
        
            The hash value is calculated as the length of the string modulo the size 
            of the hash table vector.
        */
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
