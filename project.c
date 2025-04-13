#include "funcoes.h"

/**
 * Este código gere um parque de estacionamento
 *
 * Os comandos são:
 * - 'q': Terminar o programa
 * - 'p': Criar um estacionamento
 * - 'e': Entrada de um veículo
 * - 's': Saída de um veículo
 * - 'v': Listar veículos
 * - 'f': Calcular faturação
 * - 'r': Remover um estacionamento
 */

int main() {
    char s[BUFSIZE];
    adiciona_dta();
    while (1) {
        fgets(s, BUFSIZE, stdin);
        switch (s[0]) {
            case 'q':
                limpa_memoria();
                return 0;
            case 'p':
                cria_parque(s);
                continue;
            case 'e':
                entrada_veiculos(s);
                continue;
            case 's':
                saida_veiculos(s);
                continue;
            case 'v':
                lista_veiculos(s);
                continue;
            case 'f':
                faturacao(s);
                continue;
            case 'r':
                remove_parque(s);
                continue;
        }
    }
    return 0;
}

