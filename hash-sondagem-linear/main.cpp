#include <string>
#include "HashTable.cpp"

HashTable read_input() {
    // Commands
    // 0 => insert
    // 1 => remove
    // -1 => done
    int command;
    int table_size;
    std::string string;

    std::cin >> table_size;

    HashTable table = HashTable(table_size);

    while (true) {
        std::cin >> command;

        if (command == -1)
            break;

        std::cin >> string;

        if (command == 0)
            table.insert(string);

        if (command == 1)
            table.remove(string);
    }

    return table;
}

int main(void)
{
    auto table = read_input();

    table.print_table();

    return 0;
}
