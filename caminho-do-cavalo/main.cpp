# include <iostream>
# include <unordered_map>
# include <queue>

// Defines a square as a pair (row , col):
struct Square
{

    unsigned row;
    unsigned col;

    Square(unsigned r, unsigned c)
    {
        row = r;
        col = c;
    }
};

class ChessBoard 
{
    private:
        int board[8][8] = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0};
        unsigned int _sz = 8;

    public:
        unsigned int size() const
        {
            return _sz;
        }

        int *operator[](unsigned i)
        {
            /* Enables the use of [] operator for ChessBoard objects */
            return board[i];
        }

        void fill(int value)
        {
            /* Fills all the board with a specific value */
            for (unsigned i = 0; i < size(); ++i)
            {
                for (unsigned j = 0; j < size(); ++j)
                {
                    board[i][j] = value;
                }
            }
        }
};

std::ostream& operator<< (std::ostream & out, ChessBoard &board)
{
    /* 
        Enables the use of std::cout << board
        to print the board . May be used for debugging .
    */
    for (auto i = 0; i < board.size(); ++i)
    {
        for (auto j = 0; j < board.size(); ++j)
        {
            out << board[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

bool square_valid(const Square &s, const ChessBoard &board)
{
    unsigned n = board.size();
    return s.row < n and s.col < n;
    // Since we are using unsigned for the squares , there is no need to check
    // whether values are >= 0.
}

unsigned get_knight_path_length(const Square &origin, const Square &dest)
{
    // The horizontally distances that the piece can traverse
    std::vector<int> dx = {1, 2, 2, 1, -1, -2, -2, -1};

    // The vertically distances that the piece can traverse
    std::vector<int> dy = {2, 1, -1, -2, -2, -1, 1, 2};

    std::queue<std::tuple<Square, int>> queue;

    // Store already visited squares on the board.
    uint visited[8][8] = {};

    // Aux variables
    uint new_x, new_y;

    queue.push({ origin, 0 });

    while (not queue.empty()) {
        auto [square, moves] = queue.front();
        queue.pop();
        
        if (square.row == dest.row && square.col == dest.col)
            return moves;

        for (size_t i = 0; i < 8; i++) {
            new_x = square.row + dx[i];
            new_y = square.col + dy[i];

            bool is_valid_position = new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8;

            if (is_valid_position && not visited[new_x][new_y]) {
                visited[new_x][new_y] = 1;
                queue.push({ Square(new_x, new_y), moves + 1 });
            }
        }
    }
}

int main(void)
{
    // Used to map the squares as char to indices of the board
    std ::unordered_map<char, unsigned> table = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7}};
    char icol, ocol;
    unsigned irow, orow;
    std::cin >> icol >> irow;
    std::cin.ignore(1); // Skip the ’\n’ char at the input ;
    std::cin >> ocol >> orow;

    Square origin(irow - 1, table[icol]);
    Square dest(orow - 1, table[ocol]);

    unsigned nmoves = get_knight_path_length(origin, dest);
    std::cout << "Movimentos: " << nmoves << '\n';
    
    return 0;
}