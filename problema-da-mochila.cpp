# include <vector>
# include <iostream>

struct Item {
    unsigned int t, d;
    float u, w, ratio;
};

unsigned int C = 0;
std::vector<Item> items = {};

void read_input() {
    unsigned int count = 0;

    while (true) {
        float u, w, d;

        std::cin >> u >> w >> d;

        if (u != -1 && w != -1 && d != -1) {
            Item novo;
            novo.t = count;
            novo.u = u;
            novo.w = w;
            novo.d = d;
            novo.ratio = u / w;

            items.push_back(novo);
            count++;
        }
        else {
            std::cin >> C;

            break;
        }
    }
}

// Uso do algoritmo `Bubble Sort` para realizar a ordenação.
void sort_items() {
    std::vector<Item>& v = items;
    unsigned int i, j, length = v.size();

    for (i = 0; i < length; i++) {
        for (j = 1; j < length - i; j++) {
            if (v[j - 1].ratio < v[j].ratio) {
                auto aux = v[j - 1];
                v[j - 1] = v[j];
                v[j] = aux;
            }
        }
    }
}

void select_items() {
    for (Item& item: items) {
        if (item.d < 1)
            continue;

        if (C < 1) break;

        unsigned int quantidade_maxima_possivel = C / item.w;

        if (quantidade_maxima_possivel < 1)
            continue;

        unsigned int quantidade_disponivel;

        quantidade_maxima_possivel > item.d
            ? quantidade_disponivel = item.d
            : quantidade_disponivel = quantidade_maxima_possivel;

        unsigned int peso_total = quantidade_disponivel * item.w;

        C = C - peso_total;

        std::cout
            << item.t
            << " "
            << quantidade_disponivel
            << "\n";
    }
}

int main() {
    read_input();

    sort_items();

    select_items();

    return 0;
}
