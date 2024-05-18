#include <cstdlib>
#include <locale.h>
#include <iostream>
#include <limits>

template <typename T>
struct Node {
    T value;
    struct Node *next_element;
};

template <typename T>
struct List {
    Node <T> *beginning;
    Node <T> *ending;
};

template <typename T>
int hash_function(T value) {
    // Retorna o valor ASCII da primeira letra menos o valor ASCII de a(97)
    return (tolower(value[0]) - 97);
}

template <typename T>
bool verifica_alocacao_memoria(T *pointer) {
    // Verificar se a memória foi alocada corretamente
    if (pointer == nullptr) {
        std::cout << "\nFalha na alocação da memória para inicialização do " << pointer;
        return false;
    }

    return true;
}

template <typename T>
bool inicializar_lista(List <T> *list) {
    // Alocar memória para os ponteiros na lista
    list->beginning = new Node <T>;
    list->ending = new Node <T>;

    // Verificar se a memória foi alocada corretamente
    if (list->beginning == nullptr && list->ending == nullptr) {
        return false;
    }

    // Ponteiros tem valores nulos
    list->beginning = nullptr;
    list->ending = nullptr;

    return true;
}

template <typename T>
bool inserir(List <T> *list, T value) {
    // Cria uma nova node
    Node <T> *new_node = new Node <T>;

    // Verifica se a memória foi alocada corretamente
    if (new_node == nullptr) {
        std::cout << "\nNão há memória suficiente para um novo nó.";
        return false;
    }

    // Atribui os valores ao novo Node
    new_node->value = value;
    new_node->next_element = nullptr;
    
    // Se a lista está vazia
    if (list->beginning == nullptr && list->ending == nullptr) {
        // A nova Node é o inicio e o fim
        list->beginning = new_node;
        list->ending = new_node;
        
        return true;
    }
    
    // Se há um unico elemento
    if (list->beginning == list->ending) {
        // Adiciona o próximo elemento do unico atualmente da lista
        list->beginning->next_element = new_node;

        // O último elemento da lista é o mais recente
        list->ending = new_node;

        return true;
    }
    
    // Adicione new_node como o próximo elemento do atual último elemento da lista
    list->ending->next_element = new_node;
    
    // O new_node é o novo último elemento da lista
    list->ending = new_node;

    return true;
}

template <typename T>
bool retirar(List <T> *list, T value) {
    // Verificar se a lista está vazia
    if(list->beginning == nullptr && list->ending == nullptr) {
        return true;
    }

    // Verificar se a lista só contém um unico elemento
    if (list->ending == list->beginning) {
        // Esvaziar lista
        list->beginning = nullptr;
        list->ending = nullptr;

        return true ;
    }

    // Cria uma nova node para percorrer a lista
    Node <T> *temp_node = new Node <T>;

    // Verifica a alocação de memória
    if(!verifica_alocacao_memoria(temp_node)) {
        return false;
    }

    // Cria uma nova node para gravar a node anterior a temp_node
    Node <T> *before_temp_node = new Node <T>;

    // O novo node aponta para o inicio da lista
    temp_node = list->beginning;

    // Percorra a lista até achar o elemnto ou chegar no fim dela
    while (temp_node != nullptr && value != temp_node->value) {
        // Grava o elemento anterior ao próximo elemento
        before_temp_node = temp_node;

        // Vá para o próximo elemento da lista
        temp_node = temp_node->next_element;
    }

    // Verifica se o valor encontrado está no inicio da lista
    if (temp_node == list->beginning) {
        // O começo da lista vai ser o próximo elemento
        list->beginning = temp_node->next_element;
        std::cout << temp_node->next_element;

        return true;
    }

    // Verifica se o valor encontrado é o último da lista
    if (temp_node ==list->ending) {
        // O fim da lista vaide ser o anterior ao elemento retirado
        list->ending = before_temp_node;

        return true;
    }

    // Se chegou ao final da lista encontrando um elemento com o valor procurado
    if (temp_node != nullptr) {
        // Conectado os elementos antes e depois do retirada
        before_temp_node->next_element = temp_node->next_element;
        
        return true; // ??
    }

    return false;
}

template <typename T>
bool pesquisar(List <T> *list, T value) {
    // Cria uma nova node para percorrer a lista
    Node <T> *temp_node = new Node <T>;

    // Verifica a alocação de memória
    if(!verifica_alocacao_memoria(temp_node)) {
        return false;
    }   

    // Aponta a node para o inicio da lista
    temp_node = list->beginning;

    // Percorra a lista até achar o elemnto ou chegar no fim dela
    while (temp_node != nullptr && value != temp_node->value) {
        // Vá para o próximo elemento da lista
        temp_node = temp_node->next_element;
    }

    // Se o valor foi encontrado
    if (temp_node != nullptr) {
        return true;
    }

    return false;
}

template <typename T>
bool mostrar(List <T> *lists[]) {
    // Cria uma nova node para percorrer uma lista
    Node <T> *temp_node = new Node <T>;
    
    // Verifica a alocação de memória
    if(!verifica_alocacao_memoria(temp_node)) {
        return false;
    }   
    
    // Para cada lista em listas
    for (int i = 0; i < lists.length; i++) {
        // O temp_node aponta para o inicio da lista atual
        temp_node = (lists[i]->beginning);

        // Verifica se há lista está vazia
        if(temp_node != nullptr) {
            // Mostrar "Lista (indice+1): "
            std::cout << "\nLista " << i+1 << ": ";

            // Percorra a lista mostrando cada elemento
            while (temp_node != nullptr) {
                // Mostrar elemento
                std::cout << temp_node->value;
                if (temp_node->next_element != nullptr) {
                    std::cout << "->";
                }

                // Vá para o próximo elemento da lista
                temp_node = temp_node->next_element;
            }
            // Pule uma linha
            std::cout << "\n";
        }

    }

    if (temp_node == lists[lists.length]->ending) {
        return true;
    }

    return false;
}