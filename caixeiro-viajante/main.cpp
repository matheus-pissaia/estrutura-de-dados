# include <iostream>
# include <cstdio>
# include "CircularLinkedList.h"

CircularLinkedList* linked_list = new CircularLinkedList();

void read_input() {
    int x, y;

    std::cin >> x >> y;

    while(x != -1){
        linked_list->insert(x, y);

        std::cin >> x >> y;
    }
}

int main() {
    read_input();

    double cost_before = linked_list->calculate_total_distance();
    linked_list->improve_route();
    double cost_after = linked_list->calculate_total_distance();

    std::printf("Cost before: %.2f\n", cost_before);
    std::printf("Cost after: %.2f\n", cost_after);

    return 0;
}