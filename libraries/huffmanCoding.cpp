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

// Inserir de forma ordenada
void insereLista(Lista *lista, nodeLista *node)  {
    // Se a lista passada como parâmetro não tem um nó no início (vazia), insira o nó no início
    if (lista->inicio == nullptr) 
    {
        lista->inicio = node;
        lista->fim = node;
    }

    // Se o campo 'frequência' do 'nó' parâmetro for menor que o campo 'frequência' do primeiro item (head)
    // da lista, incluir o novo nó como inicio da lisa, e colocar o inicio antigo como next desse novo
    else if (node->noArvore->frequencia < lista->inicio->noArvore->frequencia) {
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
    // Verifica se a lista é válida, verifica se não é uma lista unica
    if (lista->inicio == nullptr || lista->inicio->proximo == nullptr) {
        return;
    }

    nodeLista *novo_inicio = nullptr; // Lista temporária para nós ordenados
    nodeLista *current = lista->inicio;

    // Percorre a lista, até zerar a lista (current == nullptr)
    while (current != nullptr) {
        nodeLista *next = current->proximo; // Armazena o próximo nó
        // Insere current na lista ordenada
        if (novo_inicio == nullptr || novo_inicio->noArvore->frequencia >= current->noArvore->frequencia) {
            current->proximo = novo_inicio;
            novo_inicio = current;
        } else { 
            nodeLista *inicioAtual = novo_inicio;
            while (inicioAtual->proximo != nullptr && inicioAtual->proximo->noArvore->frequencia < current->noArvore->frequencia) {
                inicioAtual = inicioAtual->proximo;
            }
            current->proximo = inicioAtual->proximo;
            inicioAtual->proximo = current;
        }
        current = next;
    }
    lista->inicio = novo_inicio; // Atualiza o início da lista com a lista ordenada
}

nodeArvore *criarArvoreHuffman(Lista *lista) {
    // Enquanto houver mais de um nó na lista
    while (lista->inicio != nullptr && lista->inicio->proximo != nullptr) {
        // Pega os dois nós de menor frequência
        nodeArvore *esquerda = popMinLista(lista);
        nodeArvore *direita = popMinLista(lista);

        // Verificar as frequências dos nós removidos
        if (esquerda == nullptr || direita == nullptr) {
            std::cout << "Erro: nós removidos são nulos!" << std::endl;
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

void mostrarArvoreHuffman(nodeArvore *raiz, int profundidade=0) {
    // Verificar se é um nó valido
    if (raiz == nullptr) {
        return;
    }
    
    // Print the current nodeTree with appropriate indentation
    for (int i = 0; i < profundidade; ++i) {
        std::cout << "    ";
    }
    std::cout << "  |---"; // Assuming 2 spaces for indentation
    
    // Verifique se a letra existe
    if (raiz->letra != NULL) {
        std::cout << raiz->letra << ":" << raiz->frequencia << "\n";
    } else {
        std::cout << ":" << raiz->frequencia << "\n";
    }

    // Recursively call the function for left and right subtrees with increased profundidade
    mostrarArvoreHuffman(raiz->esquerda, (profundidade + 1));
    mostrarArvoreHuffman(raiz->direita, (profundidade + 1));
}

// Tabela de Huffman
void tabelaHuffman(nodeArvore *raiz, std::string codigo="") {
    // Verificar se é um nó valido
    if (raiz == nullptr) {
        return;
    }

    // Se é uma folha, imprime a letra e frequência
    if (raiz->esquerda == nullptr && raiz->direita == nullptr) {
        std::cout << raiz->letra << ", " << raiz->frequencia << ", " << codigo << "\n";
    }

    tabelaHuffman(raiz->esquerda, codigo + "0");
    tabelaHuffman(raiz->direita, codigo + "1");
}
