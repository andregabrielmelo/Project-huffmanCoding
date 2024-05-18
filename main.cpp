#include <stdlib.h>
#include <locale.h>

#include "libraries/nodes.cpp";
#include "libraries/arvores.cpp";
#include "libraries/huffmanCoding.cpp";

using namespace std;

void decoracao(int numero);
void pause();
void clean_screen();
void clean_buffer();

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    while(true) {
        // Mostre as opções para entrada de texto
        decoracao(150);
        cout << "\nComprimir texto";
        cout << "\n1.Selecionar Arquivo";
        cout << "\n2.Digitar Texto";
        cout << "\n3.Sair";
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
        switch (escolha)
        {
        case 1: // lerArquivo(); função que le o arquivo e retorna uma lista com itens de huffman 
            break;
        
        default: // lerEntrada(); chama uma função que le a entrada do usuário e retorna uma lista com itens de huffman
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

