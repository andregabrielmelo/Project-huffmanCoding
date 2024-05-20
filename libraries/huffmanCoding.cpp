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

// Inserir de forma ordenada
void insereLista(Lista *lista, nodeLista *node)  {
    // Se a lista passada como par�metro n�o tem um n� no in�cio (vazia), insira o n� no in�cio
    if (lista->inicio == nullptr) 
    {
        lista->inicio = node;
        lista->fim = node;
    }

    // Se o campo 'frequ�ncia' do 'n�' par�metro for menor que o campo 'frequ�ncia' do primeiro item (head)
    // da lista, incluir o novo n� como inicio da lisa, e colocar o inicio antigo como next desse novo
    else if (node->noArvore->frequencia < lista->inicio->noArvore->frequencia) {
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

nodeArvore *popMinLista(Lista *lista) {
    // Verfiicar se a lista � valida
    if (lista->inicio == nullptr) {
        return nullptr;
    }

    // Ponteiro auxilar que aponta para o primeiro n� da lista
    nodeLista *aux = lista->inicio;

    // Ponteiro auxiliar que aponta para a �rvore contida em aux (�rvore do primeiro n� da lista)
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
    // Verifica se a lista � v�lida, verifica se n�o � uma lista unica
    if (lista->inicio == nullptr || lista->inicio->proximo == nullptr) {
        return;
    }

    nodeLista *novo_inicio = nullptr; // Lista tempor�ria para n�s ordenados
    nodeLista *current = lista->inicio;

    // Percorre a lista, at� zerar a lista (current == nullptr)
    while (current != nullptr) {
        nodeLista *next = current->proximo; // Armazena o pr�ximo n�
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
    lista->inicio = novo_inicio; // Atualiza o in�cio da lista com a lista ordenada
}

nodeArvore *criarArvoreHuffman(Lista *lista) {
    // Enquanto houver mais de um n� na lista
    while (lista->inicio != nullptr && lista->inicio->proximo != nullptr) {
        // Pega os dois n�s de menor frequ�ncia
        nodeArvore *esquerda = popMinLista(lista);
        nodeArvore *direita = popMinLista(lista);

        // Verificar as frequ�ncias dos n�s removidos
        if (esquerda == nullptr || direita == nullptr) {
            std::cout << "Erro: n�s removidos s�o nulos!" << std::endl;
            return nullptr;
        }

        // Cria um novo n� com a soma das frequ�ncias dos dois n�s
        nodeArvore *novo = novoNodeArvore(NULL, esquerda->frequencia + direita->frequencia, esquerda, direita);

        // Cria um novo n� de lista com o n� criado
        nodeLista *novo_nodeLista = novoNodeLista(novo);

        // Insere o n� na lista
        insereLista(lista, novo_nodeLista);
    }

    // Retorna o n� restante na lista
    return popMinLista(lista);
}

void mostrarArvoreHuffman(nodeArvore *raiz, int profundidade=0) {
    // Verificar se � um n� valido
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
    // Verificar se � um n� valido
    if (raiz == nullptr) {
        return;
    }

    // Se � uma folha, imprime a letra e frequ�ncia
    if (raiz->esquerda == nullptr && raiz->direita == nullptr) {
        std::cout << raiz->letra << ", " << raiz->frequencia << ", " << codigo << "\n";
    }

    tabelaHuffman(raiz->esquerda, codigo + "0");
    tabelaHuffman(raiz->direita, codigo + "1");
}
