# include <iostream>
# include <cmath>
# include <vector>

struct Node {
    int x, y;
    struct Node *next;
};

class CircularLinkedList {
    private:
        Node* tail;
        unsigned int _size;

    public:
        CircularLinkedList(){
            _size = 0;
        };

        // Inserts a new "city" with `x` and `y` coordinates at the end.
        void insert(int x, int y){
            Node *new_node = new Node();
            new_node->x = x;
            new_node->y = y;

            if (not tail) {
                tail = new_node;
                new_node->next = new_node;
            }
            else {
                // Node next from tail should always be the head.
                auto head = tail->next;

                // Update tail's next node to be the new node.
                tail->next = new_node;

                // The new node should be the tail now.
                new_node->next = head;
                tail = new_node;
            }

            _size++;
        };

        void improve_route(){
            bool optimal_route = false;

            double min_distance = calculate_total_distance();
            double local_distance = 0;

            Node *previous_node = tail;
            Node *current_node = previous_node->next;
            Node *next_node = current_node->next;

            while(not optimal_route) {
                optimal_route = true;

                for (size_t i = 0; i < _size; i++){
                    // Swap adjacent nodes order.
                    auto aux = next_node->next;
                    current_node->next = aux;
                    next_node->next = current_node;
                    previous_node->next = next_node;

                    local_distance = calculate_total_distance();

                    if (local_distance < min_distance) {
                        min_distance = local_distance;
                        optimal_route = false;
                    }

                    else {
                        // Return adjacent nodes back to original order.
                        next_node->next = aux;
                        current_node->next = next_node;
                        previous_node->next = current_node;
                    }
                }
            };
        };

        double calculate_total_distance(){
            /*
                Strange bug: `totalDistance` was a value 10 units above the expected every time,
                but when explicitly initialized with zero, worked just fine. WTFFF???

                How to replicate:

                Given the input:
                0 0
                0 10
                10 0
                10 10

                After running the `improve_route` method and printing the `totalDistance` on each loop,
                the first loop prints a value for `totalDistance` as 20 instead of 10. Thoughts??
             */
            double totalDistance = 0;
            Node *current_city = tail->next; // Starting from head

            for (size_t i = 0; i < _size; i++) {
                totalDistance += calculate_distance(current_city, current_city->next);
                current_city = current_city->next;
            };

            return totalDistance;
        };

        // Calculates the distance between A and B points
        double calculate_distance(Node* a, Node* b){
            double dx = a->x - b->x;
            double dy = a->y - b->y;
            return sqrt(dx * dx + dy * dy);
        };

        void print(){
            auto pivot = tail->next; // Starts from head

            for (size_t i = 0; i <= _size; i++){
                std::cout << pivot->x << " " << pivot->y << "\n";
                pivot = pivot->next;
            };
        };
};
