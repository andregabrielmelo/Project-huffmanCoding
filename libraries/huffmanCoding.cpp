#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <iostream>

/** Defini��o da �rvore */
struct nodeArvore {
    int frequencia;
    char letra;
    struct nodeArvore *esquerda;
    struct nodeArvore *direita;
};

/** Defini��o da fila de prioridade (implementada como lista simplesmente encadeada) */
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
    // Aloca mem�ria
    Lista *novo = new Lista;

    // Adiciona o come�o e fim
    novo->inicio = inicio;
    novo->fim = fim;

    return novo;
}

nodeLista *novoNodeLista(nodeArvore *node)
{
    // Aloca mem�ria
    nodeLista *novo = new nodeLista;

    // Adiciona a �rvore ao n�
    novo->noArvore = node;

    // Faz o campo pr�ximo apontar para NULL
    novo->proximo = NULL;

    return novo;
}

nodeArvore *novoNodeArvore(char letra, int frequencia, nodeArvore *esquerda, nodeArvore *direita)
{
    // Aloca mem�ria
    nodeArvore *novo = new nodeArvore;

    // Atribui na �rvore os valores passados como par�metro
    novo->letra = letra;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}

nodeArvore *pegarNodeArvore(Lista *lista, char letra) {
    // n� auxiliar que inicia apontando para o primeiro n� da lista 
    nodeLista *aux = lista->inicio;

    // La�o que percorre a lista e insere o n� na posi��o certa de acordo at� achar o n� com aquela letra
    while (aux != nullptr && aux->noArvore->letra != letra) {
        aux = aux->proximo;
    }    

    // Se foi encontrado uma node com aquela letra, retorna o n� 
    if (aux != nullptr) {
        return aux->noArvore;
    }   

    return nullptr;
}

void mostrarLista(Lista *lista) {
    // n� auxiliar que inicia apontando para o primeiro n� da lista 
    nodeLista *aux = lista->inicio;

    // La�o que percorre a lista e mostra os elementos
    while (aux != nullptr) {

        // Mostra o elemnto (letra:frequencia)
        std::cout << aux->noArvore->letra << ":" << aux->noArvore->frequencia;

        if (aux->proximo != nullptr) {
            std::cout << "->";
        }

        // Vai para o pr�ximo elemento da lista
        aux = aux->proximo;
    }    
}

// template aqui?
// Inserir de forma ordenada
void insereLista(Lista *lista, nodeLista *node)  {
    // Se a lista passada como par�metro n�o tem um n� no in�cio (vazia), insira o n� no in�cio
    if (!lista->inicio)
    {
        lista->inicio = node;
    }

    // Se o campo 'frequ�ncia' do 'n�' par�metro for menor que o campo 'frequ�ncia' do primeiro item (head)
    // da lista, incluir o novo n� como inicio da lisa, e colocar o inicio antigo como next desse novo
    else if (node->noArvore->frequencia < lista->inicio->noArvore->frequencia)
    {
        node->proximo = lista->inicio;
        lista->inicio = node;
    }
    else
    {
        // n� auxiliar que inicia apontando para o segundo n� da lista (head->proximo)
        nodeLista *aux = lista->inicio->proximo;
        // n� auxiliar que inicia apontando para o primeiro n� da lista
        nodeLista *aux_anterior = lista->inicio;

        // La�o que percorre a lista e insere o n� na posi��o certa de acordo com sua frequ�ncia.
        //
        // Se sabe que aux come�a apontando para o segundo item da lista e aux_anterior apontando para o primeiro.
        // Sendo assim, os ponteiros seguir�o mudando de posi��o enquanto aux n�o for o fim da lista,
        // e enquanto a frequ�ncia do n� apontado por aux for menor ou igual a frequ�ncia do 'n�' par�metro.

        while (aux != nullptr && aux->noArvore->frequencia <= node->noArvore->frequencia) {
            aux_anterior = aux;
            aux = aux->proximo;
        }

        // Se insere o n� na posi��o certa.
        aux_anterior->proximo = node;
        node->proximo = aux;
    }
}

/** Fun��o que 'solta' o n� apontado por 'head' da lista (o de menor frequ�ncia)
* (faz backup do n� e o desconecta da lista)
* @param: uma lista encadeada.
*/

nodeArvore *popMinLista(Lista *lista) {

    // Ponteiro auxilar que aponta para o primeiro n� da lista
    nodeLista *aux = lista->inicio;

    // Ponteiro auxiliar que aponta para a �rvore contida em aux (�rvore do primeiro n� da lista)
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

    // Cria um n� de arvore temporario para comparar valores
    nodeArvore *temp_node = novoNodeArvore(NULL, NULL, nullptr, nullptr);

    // Percorre o texto, criando uma node para cada caractere, 
    // e contando quantas vezes cada caractere aparece
    for (int i = 0; i < texto.length(); i++) {
        // Procura uma node com aquela letra na lista
        temp_node = pegarNodeArvore(lista, texto[i]);

        // Se ele n�o for encontrado
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
    // n� auxiliar que inicia apontando para o primeiro n� da lista 
    nodeLista *aux = lista->inicio;

    // n� temporario para guaradar n�
    nodeLista *temp_node = novoNodeLista(nullptr);

    // La�o que percorre a lista e mostra os elementos
    while (aux != lista->fim) {

        // Se esse elemento tem uma frequencia maior que o pr�ximo
        // troque eles de lugar
        if (aux->proximo != nullptr && aux->noArvore->frequencia > aux->proximo->noArvore->frequencia) {
            temp_node = aux;
            aux = aux->proximo;
            aux->proximo = temp_node;
        }

        // Vai para o pr�ximo elemento da lista
        aux = aux->proximo;
    }   
}


// struct huffmanItem {
//     char character = NULL; // guarda a letra
//     int frequency = NULL; // guarda a frqu�ncia com que ela aparece
// };

// template <typename T>
// bool inserir(List <T> *list, T value) {
//     // Cria uma nova node
//     Node <T> *new_node = new Node <T>;

//     // Verifica se a memória foi alocada corretamente
//     if (new_node == nullptr) {
//         std::cout << "\nNão há memória suficiente para um novo nó.";
//         return false;
//     }

//     // Atribui os valores ao novo Node
//     new_node->value = value;
//     new_node->next_element = nullptr;
    
//     // Se a lista está vazia
//     if (list->beginning == nullptr && list->ending == nullptr) {
//         // A nova Node é o inicio e o fim
//         list->beginning = new_node;
//         list->ending = new_node;
        
//         return true;
//     }
    
//     // Se há um unico elemento
//     if (list->beginning == list->ending) {
//         // Adiciona o próximo elemento do unico atualmente da lista
//         list->beginning->next_element = new_node;

//         // O último elemento da lista é o mais recente
//         list->ending = new_node;

//         return true;
//     }
    
//     // Adicione new_node como o próximo elemento do atual último elemento da lista
//     list->ending->next_element = new_node;
    
//     // O new_node é o novo último elemento da lista
//     list->ending = new_node;

//     return true;
// }

// bool pesquisarHuffman(List <huffmanItem> *list, char value) {
//     // Cria uma nova node para percorrer a lista
//     Node <huffmanItem> *temp_node = new Node <huffmanItem>;

//     // Aponta a node para o inicio da lista
//     temp_node = list->beginning;

//     // Percorra a lista até achar o elemnto ou chegar no fim dela
//     while (temp_node != nullptr && value != temp_node->value.character) {
//         // Vá para o próximo elemento da lista
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

//     // Percorra a lista até achar o elemnto ou chegar no fim dela
//     while (temp_node != nullptr && value != temp_node->value.character) {
//         // Vá para o próximo elemento da lista
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
//         if(pesquisarHuffman(lista_huffman, text[i])) { // se o elemnto j� est� na lista
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


