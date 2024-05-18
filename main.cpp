#include <stdlib.h>
#include <locale.h>

#include "libraries/nodes.cpp"
#include "libraries/arvores.cpp"
#include "libraries/huffmanCoding.cpp"

using namespace std;

void decoracao(int numero);
void pause();
void clean_screen();
void clean_buffer();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Limpar a tela
    clean_screen();

    string texto = "AABBCCDDDEEEFFGGGHHHIIJJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ";

    // Criação da arvore de Huffman
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

    // Loop principal
    while(true) {
        // Mostre as op��es para entrada de texto
        cout << "\n";
        decoracao(150);
        cout << "\nComprimir texto";
        cout << "\n1.Selecionar Arquivo";
        cout << "\n2.Digitar Texto";
        cout << "\n3.Sair";
        cout << "\n";
        decoracao(150);

        // Pergunte ao usu�rios como ele quer prosseguir
        int escolha;
        while(true) {
            cout << "\nEscolher opçãoo: ";   
            cin >> escolha;

            if (1 <= escolha && escolha <= 3) {
                break;
            } else {
                cout << "\nEntrada invalida. Escolha um n�mero entre 1 e 3.";
            }
        }

        // Ler o arquivo de texto, ou o texto de entrada, e retornar uma lista com os caracteres do texto, e a frequencia com que eles aparecem
        switch (escolha)
        {
        case 1: // lerArquivo(); fun��o que le o arquivo e retorna uma lista com itens de huffman 
            break;
        
        default: // lerEntrada(); chama uma fun��o que le a entrada do usu�rio e retorna uma lista com itens de huffman
            break;
        }

        // 

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

