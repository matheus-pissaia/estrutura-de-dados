# include <iostream>
# include <cmath>

struct Point {
    int x, y;
};

struct Node
{
    struct Point *point;
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
            Point *new_point = new Point();
            new_point->x = x;
            new_point->y = y;

            Node *new_node = new Node();
            new_node->point = new_point;

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
            // There's no optimization for less then 4 points.
            if (_size < 4)
                return;

            // Note: in order to swap two nodes in a linked list, we need to have the previous and current Nodes references.
            // For example: ... -> [Node previous A] -> [A] -> ... [Node previous B] -> [B] -> ...
            Node *previousA = tail->next; // Head
            Node *currentA = previousA->next;

            // Starts comparison from head until it reaches the head again.
            for (size_t i = 0; i < _size; i++){
                Node *previousB = currentA;
                Node *currentB = currentA->next;

                // Initialize previous and closest with next node from currentA
                Node *previousClosestNode = NULL;
                Node *closestNode = NULL;

                // Initialize closest distance with next node from previousA
                double closestNodeDistance = calculate_distance(previousA->point, currentA->point);

                // Starts comparison from the Node next from head until it reaches itself.
                while(currentB != tail){
                    // calculate distance and gets the Node with closest point from currentA
                    double distance = calculate_distance(previousA->point, currentB->point);

                    if (distance < closestNodeDistance) {
                        closestNode = currentB;
                        previousClosestNode = previousB;
                        closestNodeDistance = distance;
                    }

                    // Update to next node
                    previousB = currentB;
                    currentB = currentB->next;
                };

                if (closestNode) {
                    // Swap currentA with closestNode
                    previousA->next = closestNode;
                    previousClosestNode->next = currentA;

                    auto temp = currentA->next;
                    currentA->next = closestNode->next;
                    closestNode->next = temp;

                    // Update tail with currentA if closest node swaped was the tail
                    if (closestNode == tail)
                        tail = currentA;
                }

                // Update to next node
                previousA = currentA;
                currentA = currentA->next;
            }
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
                totalDistance += calculate_distance(current_city->point, current_city->next->point);
                current_city = current_city->next;
            };

            return totalDistance;
        };

        // Calculates the distance between A and B points
        double calculate_distance(Point* a, Point* b){
            double dx = a->x - b->x;
            double dy = a->y - b->y;
            return sqrt(dx * dx + dy * dy);
        };

        void print(){
            auto pivot = tail->next; // Starts from head

            for (size_t i = 0; i < _size; i++){
                std::cout << pivot->point->x << " " << pivot->point->y << "\n";
                pivot = pivot->next;
            };
        };
};
