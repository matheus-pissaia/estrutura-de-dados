# include <iostream>
# include <vector>
# include "Stack.h"

Stack stack = Stack();
std::vector<std::vector<char>> matrix = {};

void read_input() {
    std::string line;

    while (std::cin >> line) {
        std::vector<char> aux(line.cbegin(), line.cend());
        matrix.push_back(aux);
    }
}

int get_island_size(int& initial_x, int& initial_y) {
    int rows_length = matrix.size();
    int columns_length = matrix[0].size();
    int island_size = 0;

    stack.push(initial_x, initial_y);

    while (not stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        if (
            x >= 0 && x < rows_length &&
            y >= 0 && y < columns_length &&
            matrix[x][y] == '1'
        ) {
            // Mark the cell as visited
            matrix[x][y] = '0';
            island_size += 1;

            //  Add adjacent non-visited cells to the stack
            // dx
            stack.push(x + 1, y);
            stack.push(x - 1, y);
            // dy
            stack.push(x, y + 1);
            stack.push(x, y - 1);
        }
    }

    return island_size;
}

int main() {
    read_input();

    int biggest_island_size = 0;

    // Assign the amount of columns and rows of the matrix to each variable
    int rows_length = matrix.size();
    int columns_length = matrix[0].size();

    for (int i = 0; i < rows_length; i++) {
        for (int j = 0; j < columns_length; j++) {
            if (matrix[i][j] == '1') {
                int island_size = get_island_size(i, j);

                if (island_size > biggest_island_size)
                    biggest_island_size = island_size;
            }
        }
    };

    std::cout << biggest_island_size;

    return 0;
}
