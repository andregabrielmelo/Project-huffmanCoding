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
    // Verfiicar se a lista é valida
    if (lista->inicio == nullptr) {
        return nullptr;
    }

    // Ponteiro auxilar que aponta para o primeiro nó da lista
    nodeLista *aux = lista->inicio;

    // Ponteiro auxiliar que aponta para a árvore contida em aux (árvore do primeiro nó da lista)
    nodeArvore *aux_arvore = aux->noArvore;

    // Aponta o 'head' da lista para o segundo elemento dela
    lista->inicio = aux->proximo;

    // Libera o ponteiro aux
    delete aux;

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
    if (lista->inicio == nullptr || lista->inicio->proximo == nullptr) {
        return;
    }

    nodeLista *sorted = nullptr; // Lista temporária para nós ordenados
    nodeLista *current = lista->inicio;

    while (current != nullptr) {
        nodeLista *next = current->proximo; // Armazena o próximo nó
        // Insere current na lista ordenada
        if (sorted == nullptr || sorted->noArvore->frequencia >= current->noArvore->frequencia) {
            current->proximo = sorted;
            sorted = current;
        } else {
            nodeLista *sortedCurrent = sorted;
            while (sortedCurrent->proximo != nullptr && sortedCurrent->proximo->noArvore->frequencia < current->noArvore->frequencia) {
                sortedCurrent = sortedCurrent->proximo;
            }
            current->proximo = sortedCurrent->proximo;
            sortedCurrent->proximo = current;
        }
        current = next;
    }

    lista->inicio = sorted; // Atualiza o início da lista com a lista ordenada
}

nodeArvore *criarArvoreHuffman(Lista *lista) {
    // Enquanto houver mais de um nó na lista
    while (lista->inicio != nullptr && lista->inicio->proximo != nullptr) {
        // Pega os dois nós de menor frequência
        nodeArvore *esquerda = popMinLista(lista);
        nodeArvore *direita = popMinLista(lista);

        // Verificar as frequências dos nós removidos
        if (esquerda == nullptr || direita == nullptr) {
            std::cerr << "Erro: nós removidos são nulos!" << std::endl;
            return nullptr;
        }

        // Cria um novo nó com a soma das frequências dos dois nós
        nodeArvore *novo = novoNodeArvore(NULL, esquerda->frequencia + direita->frequencia, esquerda, direita);

        // Cria um novo nó de lista com o nó criado
        nodeLista *novo_nodeLista = novoNodeLista(novo);

        // Insere o nó na lista
        insereLista(lista, novo_nodeLista);
    }

    // Retorna o nó restante na lista
    return popMinLista(lista);
}

void mostrarArvoreHuffman(nodeArvore *raiz, int depth=0) {
    // Verificar se é um nó valido
    if (raiz == nullptr) {
        return;
    }
    
    // Print the current nodeTree with appropriate indentation
    for (int i = 0; i < depth; ++i) {
        std::cout << "    ";
    }
    std::cout << "  |---"; // Assuming 2 spaces for indentation
    
    // Verifique se a letra existe
    if (raiz->letra != NULL) {
        std::cout << raiz->letra << ":" << raiz->frequencia << "\n";
    } else {
        std::cout << ":" << raiz->frequencia << "\n";
    }

    // Recursively call the function for left and right subtrees with increased depth
    mostrarArvoreHuffman(raiz->esquerda, (depth + 1));
    mostrarArvoreHuffman(raiz->direita, (depth + 1));
}

// Tabela
// a:2 0
// b:3 01
void tabelaHuffman(nodeArvore *raiz, std::string code="") {
    // Verificar se é um nó valido
    if (raiz == nullptr) {
        return;
    }

    // Se é uma folha, guarda a letra e frequência
    if (raiz->esquerda == nullptr && raiz->direita == nullptr) {
        std::cout << raiz->letra << ", " << raiz->frequencia << ", " << code << "\n";
    }

    tabelaHuffman(raiz->esquerda, code + "0");
    tabelaHuffman(raiz->direita, code + "1");
}

// Testes
// int main() {
//     Lista *lista = novaLista(nullptr, nullptr);

//     // Adiciona nós com frequências conhecidas
//     insereLista(lista, novoNodeLista(novoNodeArvore('a', 5, nullptr, nullptr)));
//     insereLista(lista, novoNodeLista(novoNodeArvore('b', 9, nullptr, nullptr)));
//     insereLista(lista, novoNodeLista(novoNodeArvore('c', 12, nullptr, nullptr)));
//     insereLista(lista, novoNodeLista(novoNodeArvore('d', 13, nullptr, nullptr)));
//     insereLista(lista, novoNodeLista(novoNodeArvore('e', 16, nullptr, nullptr)));
//     insereLista(lista, novoNodeLista(novoNodeArvore('f', 45, nullptr, nullptr)));

//     // Cria a árvore de Huffman
//     nodeArvore *arvore = criarArvoreHuffman(lista);

//     // Mostra a árvore de Huffman
//     mostrarArvoreHuffman(arvore);

//     return 0;
// }
