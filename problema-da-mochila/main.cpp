# include <vector>
# include <iostream>

struct Item {
    unsigned int tipo, quantidade;
    float utilidade, peso, ratio;
};

unsigned int capacidade_mochila;
std::vector<Item> items = {};

void read_input() {
    unsigned int count = 0;

    while (true) {
        float utilidade, peso, quantidade;

        std::cin >> utilidade >> peso >> quantidade;

        if (utilidade != -1 && peso != -1 && quantidade != -1) {
            Item novo;
            novo.tipo = count;
            novo.utilidade = utilidade;
            novo.peso = peso;
            novo.quantidade = quantidade;
            novo.ratio = utilidade / peso;

            items.push_back(novo);
            count++;
        }
        else {
            std::cin >> capacidade_mochila;

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
        if (item.quantidade < 1)
            continue;

        if (capacidade_mochila < 1) break;

        unsigned int quantidade_maxima_possivel = capacidade_mochila / item.peso;

        if (quantidade_maxima_possivel < 1)
            continue;

        unsigned int quantidade_disponivel;

        quantidade_maxima_possivel > item.quantidade
            ? quantidade_disponivel = item.quantidade
            : quantidade_disponivel = quantidade_maxima_possivel;

        unsigned int peso_total = quantidade_disponivel * item.peso;

        capacidade_mochila = capacidade_mochila - peso_total;

        std::cout
            << item.tipo
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
