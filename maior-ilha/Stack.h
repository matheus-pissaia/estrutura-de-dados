# include <tuple>

struct Node {
    std::tuple<int, int> value;
    struct Node *next;
};

class Stack {
    private:
        Node *_top;

    public:
        Stack() {
            _top = new Node();
            _top->next = nullptr;
        }

        bool empty() {
            return _top->next == nullptr;
        }
        
        void push(int x, int y) {
            Node *new_node = new Node();

            new_node->value = {x, y};
            new_node->next = _top->next;
            _top->next = new_node;
        }

        void pop() {
            if (not empty()) {
                auto to_delete = _top->next;
                _top->next = _top->next->next;

                delete to_delete;
            }
        }

        std::tuple<int, int> top() {
            return _top->next->value;
        }
};
