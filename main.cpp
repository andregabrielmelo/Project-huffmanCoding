// Alunos: André Melo, Gabriel Mafra
// Link github: https://github.com/andregabrielmelo/Project-huffmanCoding/

#include <stdlib.h>
#include <locale.h>
#include <string> 
#include <fstream> 
#include <iostream>
#include <limits>

#include "libraries/huffmanCoding.cpp"

using namespace std;

void decoracao(int numero);
void pause();
void clean_screen();
void clean_buffer();

string lerArquivo();
string lerEntrada();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Loop principal
    while(true) {
        // Limpar a tela
        clean_screen();

        // Mostre as opções para entrada de texto
        cout << "\n";
        decoracao(150);
        cout << "\nComprimir texto com Alogoritimo de Huffman\n";
        cout << "\n1.Selecionar Arquivo";
        cout << "\n2.Digitar Texto";
        cout << "\n3.Sair";
        cout << "\n";
        decoracao(150);

        // Pergunte ao usuários como ele quer prosseguir
        int escolha;
        while(true) {
            cout << "\nEscolher opção: ";   
            cin >> escolha;

            if (1 <= escolha && escolha <= 3) {
                break;
            } else {
                cout << "\nEntrada invalida. Escolha um número entre 1 e 3.";
            }
        }

        // Ler o arquivo de texto, ou o texto de entrada, e retornar uma lista com os caracteres do texto, e a frequencia com que eles aparecem
        string texto;
        switch (escolha)
        {
        case 1: texto = lerArquivo(); break; // que lê o arquivo e retorna uma lista com itens de huffman 
        case 2: texto = lerEntrada(); break; // que lê a entrada do usuário e retorna uma lista com itens de huffman
        case 3: return 0; // que encerra o programa
        }

        // Mostar texto
        cout << "\nTexto lido: " << texto << "\n";

        // Criação da lista de Huffman
        Lista *huffmanList = novoHuffmanList(texto);

        // Mostrar a lista de Huffman 
        cout << "\n";
        cout << "\nLista de Huffman =>\n";
        mostrarLista(huffmanList);
        cout << "\n";
        
        // Mostrar a lista de Huffman ordenada
        cout << "\n";
        cout << "\nLista de Huffman ordenada =>\n";
        organizarHuffmanLista(huffmanList);
        mostrarLista(huffmanList);
        cout << "\n";

        // Criação da arvore de Huffman
        nodeArvore *huffmanTree = criarArvoreHuffman(huffmanList);

        // Mostrar a arvore de Huffman
        cout << "\n";
        cout << "\nArvore de Huffman =>\n";
        mostrarArvoreHuffman(huffmanTree);

        // Mostrar tabela com os valores e frequências
        cout << "\n";
        cout << "\nTabela de Huffman =>\n";
        cout << "\nLetra, Frequência, Códgio\n";
        tabelaHuffman(huffmanTree);

        // Pausar
        pause();

        // Liberar arvore 
        liberarArvore(huffmanTree);
    }
}

void decoracao(int numero) {
    for (int i = 0; i < numero; i++) {
        std::cout << "=";
    }
}

void pause() {
    // Limpar buffer
    clean_buffer();

    // Pausar
    std::cout << "\nPausado! Pressione algo para continuar...";
    std::cin.get(); 
}

void clean_screen() {
    std::cout << "\033[2J\033[1;1H";
}

void clean_buffer() {
    // Clean buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

string lerEntrada() {
    string texto;
    cout << "\nDigite o texto que deseja comprimir: ";
    cin >> texto;

    return texto;
}

string lerArquivo() {
    ifstream file;

    string file_name;
    cout << "\nDigite o nome do arquivo que deseja comprimir: ";
    cin >> file_name;

    file.open(file_name); // abre arquivo 
    
    // Verifica se o arquivo foi aberto
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        abort(); // talvez mudar
    }

    string line;
    string texto = "";
    while (getline(file, line)){
        texto += line;
    }

    file.close(); // fecha arquivo

    return texto;
}

