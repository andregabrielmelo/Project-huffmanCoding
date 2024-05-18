#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <iostream>

/** Definição da árvore */
struct nodeArvore {
    int frequencia;
    char letra;
    struct nodeArvore *esquerda;
    struct nodeArvore *direita;
};

/** Definição da fila de prioridade (implementada como lista simplesmente encadeada) */
struct nodeLista {
    nodeArvore *noArvore;
    struct nodeLista *proximo;
};

// Lista
struct Lista {
    nodeLista *inicio;
    nodeLista *fim;
};

Lista *novaLista(nodeLista *inicio, nodeLista *fim) {
    // Aloca memória
    Lista *novo = new Lista;

    // Adiciona o começo e fim
    novo->inicio = inicio;
    novo->fim = fim;

    return novo;
}

nodeLista *novoNodeLista(nodeArvore *node)
{
    // Aloca memória
    nodeLista *novo = new nodeLista;

    // Adiciona a árvore ao nó
    novo->noArvore = node;

    // Faz o campo próximo apontar para NULL
    novo->proximo = NULL;

    return novo;
}

nodeArvore *novoNodeArvore(char letra, int frequencia, nodeArvore *esquerda, nodeArvore *direita)
{
    // Aloca memória
    nodeArvore *novo = new nodeArvore;

    // Atribui na árvore os valores passados como parâmetro
    novo->letra = letra;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}

nodeArvore *pegarNodeArvore(Lista *lista, char letra) {
    // nó auxiliar que inicia apontando para o primeiro nó da lista 
    nodeLista *aux = lista->inicio;

    // Laço que percorre a lista e insere o nó na posição certa de acordo até achar o nó com aquela letra
    while (aux != nullptr && aux->noArvore->letra != letra) {
        aux = aux->proximo;
    }    

    // Se foi encontrado uma node com aquela letra, retorna o nó 
    if (aux != nullptr) {
        return aux->noArvore;
    }   

    return nullptr;
}

void mostrarLista(Lista *lista) {
    // nó auxiliar que inicia apontando para o primeiro nó da lista 
    nodeLista *aux = lista->inicio;

    // Laço que percorre a lista e mostra os elementos
    while (aux != nullptr) {

        // Mostra o elemnto (letra:frequencia)
        std::cout << aux->noArvore->letra << ":" << aux->noArvore->frequencia;

        if (aux->proximo != nullptr) {
            std::cout << "->";
        }

        // Vai para o próximo elemento da lista
        aux = aux->proximo;
    }    
}

// template aqui?
// Inserir de forma ordenada
void insereLista(Lista *lista, nodeLista *node)  {
    // Se a lista passada como parâmetro não tem um nó no início (vazia), insira o nó no início
    if (!lista->inicio)
    {
        lista->inicio = node;
    }

    // Se o campo 'frequência' do 'nó' parâmetro for menor que o campo 'frequência' do primeiro item (head)
    // da lista, incluir o novo nó como inicio da lisa, e colocar o inicio antigo como next desse novo
    else if (node->noArvore->frequencia < lista->inicio->noArvore->frequencia)
    {
        node->proximo = lista->inicio;
        lista->inicio = node;
    }
    else
    {
        // nó auxiliar que inicia apontando para o segundo nó da lista (head->proximo)
        nodeLista *aux = lista->inicio->proximo;
        // nó auxiliar que inicia apontando para o primeiro nó da lista
        nodeLista *aux_anterior = lista->inicio;

        // Laço que percorre a lista e insere o nó na posição certa de acordo com sua frequência.
        //
        // Se sabe que aux começa apontando para o segundo item da lista e aux_anterior apontando para o primeiro.
        // Sendo assim, os ponteiros seguirão mudando de posição enquanto aux não for o fim da lista,
        // e enquanto a frequência do nó apontado por aux for menor ou igual a frequência do 'nó' parâmetro.

        while (aux != nullptr && aux->noArvore->frequencia <= node->noArvore->frequencia) {
            aux_anterior = aux;
            aux = aux->proximo;
        }

        // Se insere o nó na posição certa.
        aux_anterior->proximo = node;
        node->proximo = aux;
    }
}

/** Função que 'solta' o nó apontado por 'head' da lista (o de menor frequência)
* (faz backup do nó e o desconecta da lista)
* @param: uma lista encadeada.
*/

nodeArvore *popMinLista(Lista *lista) {

    // Ponteiro auxilar que aponta para o primeiro nó da lista
    nodeLista *aux = lista->inicio;

    // Ponteiro auxiliar que aponta para a árvore contida em aux (árvore do primeiro nó da lista)
    nodeArvore *aux_arvore = aux->noArvore;

    // Aponta o 'head' da lista para o segundo elemento dela
    lista->inicio = aux->proximo;

    // Libera o ponteiro aux
    free(aux);
    aux = NULL;

    return aux_arvore;
}

Lista *novoHuffmanList(std::string texto) {
    // Cria uma nova lista
    Lista *lista = novaLista(nullptr, nullptr);

    // Cria um nó de arvore temporario para comparar valores
    nodeArvore *temp_node = novoNodeArvore(NULL, NULL, nullptr, nullptr);

    // Percorre o texto, criando uma node para cada caractere, 
    // e contando quantas vezes cada caractere aparece
    for (int i = 0; i < texto.length(); i++) {
        // Procura uma node com aquela letra na lista
        temp_node = pegarNodeArvore(lista, texto[i]);

        // Se ele não for encontrado
        if (temp_node == nullptr) {
            // Cria um novo node de arvore
            nodeArvore *novo_nodeArvore = novoNodeArvore(texto[i], 1, nullptr, nullptr);

            // Cria um novo node de lista
            nodeLista *novo_nodeLista = novoNodeLista(novo_nodeArvore);

            // Insere na lista
            insereLista(lista, novo_nodeLista);
        } else { 
            // Aumenta a frequencia
            temp_node->frequencia++;
        }
    }

    return lista;
}

void organizarHuffmanLista(Lista *lista) {
    // nó auxiliar que inicia apontando para o primeiro nó da lista 
    nodeLista *aux = lista->inicio;

    // nó temporario para guaradar nó
    nodeLista *temp_node = novoNodeLista(nullptr);

    // Laço que percorre a lista e mostra os elementos
    while (aux != lista->fim) {

        // Se esse elemento tem uma frequencia maior que o próximo
        // troque eles de lugar
        if (aux->proximo != nullptr && aux->noArvore->frequencia > aux->proximo->noArvore->frequencia) {
            temp_node = aux;
            aux = aux->proximo;
            aux->proximo = temp_node;
        }

        // Vai para o próximo elemento da lista
        aux = aux->proximo;
    }   
}


// struct huffmanItem {
//     char character = NULL; // guarda a letra
//     int frequency = NULL; // guarda a frquência com que ela aparece
// };

// template <typename T>
// bool inserir(List <T> *list, T value) {
//     // Cria uma nova node
//     Node <T> *new_node = new Node <T>;

//     // Verifica se a memÃ³ria foi alocada corretamente
//     if (new_node == nullptr) {
//         std::cout << "\nNÃ£o hÃ¡ memÃ³ria suficiente para um novo nÃ³.";
//         return false;
//     }

//     // Atribui os valores ao novo Node
//     new_node->value = value;
//     new_node->next_element = nullptr;
    
//     // Se a lista estÃ¡ vazia
//     if (list->beginning == nullptr && list->ending == nullptr) {
//         // A nova Node Ã© o inicio e o fim
//         list->beginning = new_node;
//         list->ending = new_node;
        
//         return true;
//     }
    
//     // Se hÃ¡ um unico elemento
//     if (list->beginning == list->ending) {
//         // Adiciona o prÃ³ximo elemento do unico atualmente da lista
//         list->beginning->next_element = new_node;

//         // O Ãºltimo elemento da lista Ã© o mais recente
//         list->ending = new_node;

//         return true;
//     }
    
//     // Adicione new_node como o prÃ³ximo elemento do atual Ãºltimo elemento da lista
//     list->ending->next_element = new_node;
    
//     // O new_node Ã© o novo Ãºltimo elemento da lista
//     list->ending = new_node;

//     return true;
// }

// bool pesquisarHuffman(List <huffmanItem> *list, char value) {
//     // Cria uma nova node para percorrer a lista
//     Node <huffmanItem> *temp_node = new Node <huffmanItem>;

//     // Aponta a node para o inicio da lista
//     temp_node = list->beginning;

//     // Percorra a lista atÃ© achar o elemnto ou chegar no fim dela
//     while (temp_node != nullptr && value != temp_node->value.character) {
//         // VÃ¡ para o prÃ³ximo elemento da lista
//         temp_node = temp_node->next_element;
//     }

//     // Se o valor foi encontrado
//     if (temp_node != nullptr) {
//         return true;
//     }

//     return false;
// }

// Node <huffmanItem> *getHuffmanItem(List <huffmanItem> *list, char value){
//     // Cria uma nova node para percorrer a lista
//     Node <huffmanItem> *temp_node = new Node <huffmanItem>;

//     // Aponta a node para o inicio da lista
//     temp_node = list->beginning;

//     // Percorra a lista atÃ© achar o elemnto ou chegar no fim dela
//     while (temp_node != nullptr && value != temp_node->value.character) {
//         // VÃ¡ para o prÃ³ximo elemento da lista
//         temp_node = temp_node->next_element;
//     }

//     // Se o valor foi encontrado
//     if (temp_node != nullptr) {
//         return temp_node;
//     }

//     return nullptr;
// }

// template <typename T>
// List <T>* trafomarHuffmanLista(std::string text) {
//     // Cria lista
//     List *lista_huffman = new List<huffmanItem>;
//     inicializar_lista(lista_huffman);

//     // Temp huffmanItem node
//     Node <huffmanItem> *temp_huffman_item = new Node <huffmanItem>;

//     // Percorre o texto
//     for (int i = 0; i < text.length; i++) {
//         if(pesquisarHuffman(lista_huffman, text[i])) { // se o elemnto já está na lista
//             temp_huffman_item = getHuffmanItem(lista_huffman, text[i]); // pega o elemento
//             temp_huffman_item->value.frequency++; // aumenta seu contador
//         } else {
//             // Cria uma nova node
//             Node <huffmanItem> *temp_node = new Node <huffmanItem>;
//             temp_node->value.character = text[i];
//             temp_node->value.frequency++;

//             // Adiciona na lista de forma ordenada, baseado na frequencia
//         }
//     }
// }

// std::string lerArquivo() {
//     std::ifstream file;

//     std::string file_name;
//     std::cout << "\nNome do arquivo: ";
//     std::cin >> file_name;

//     file.open(file_name); // abre arquivo 
//     std::string line;

//     std::string texto = "";
//     while (getline(file, line)){
//         texto += line;
//     }

//     return texto;
// }

// std::string lerEntrada() {
//     std::string texto;
//     std::cout << "\nTexto: ";
//     std::cin >> texto;

//     return texto;
// }


