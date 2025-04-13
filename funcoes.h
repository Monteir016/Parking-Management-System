#ifndef FUNCOES_H
#define FUNCOES_H
#include "estruturas.h"

void adiciona_dta();
// Funções que identificam elementos dentro das estruturas
Parque* identifica_parque(char *nome);
Carro* identifica_carro(char *matricula, Parque *parque);
Registo* identifica_registo(char *matricula);
void identifica_carro_registo(char *matricula, int *num_carros_encontrados,
Registo *carros_encontrados[LEITURA]);
void identifica_faturacao_dia(Parque *parque,char *data, 
int *num_carros_encontrados,
Registo *carros[LEITURA]);
void identifica_faturacao_nome(Parque *parque, int *num_carros_encontrados, 
Registo *carros[LEITURA]);

// Funções que verificam condições
int verifica_matricula(char *matricula);
int verifica_carro(char *matricula);
int verifica_data_hora(char *data, char *hr);
int verifica_data(char *data);
int verifica_condições(char *nome, int capacidade, float valori, 
float valorf, float valord,int num_parque);
int verifica_carro_parque(char *matricula,Parque *parque);

// Funções auxiliares
long calcula_minutos(int ano, int mes, int dia, int hora, int minuto);
void calcula_custos(float valori, float valorf, float valord, 
long minutos_total, float *valor_total);
float calcula_valor(Carro*carro,Parque*parque,char*hr_saida,char*data_saida);
void calcula_faturacao_dia(Registo *carros[], int num_carros);
void adiciona_parque(char *nome, int capacidade, float valori, float valorf, 
float valord, Parque *novo_parque);
void copia_registo_entrada(Parque *parque, Registo *novo_registo, 
char *hr_entrada, char *matricula, char *data_ea);
void adicionar_carro(Parque *parque, char *matricula, char *data_ea, 
char *hr_entrada);
void retira_carro(Carro *carro,char *hr_saida,char *data_saida,
Parque *parque,Registo *registo);
void comparar_carros(Registo *carros[], int anterior, int agr, int dps, 
char conteudo);
void comparar_parques(Parque *lparques[], int anterior, int agr, int dps);
void ordena_lista_carros(Registo *carros[], Parque *lparques[], int anterior,
int dps, char conteudo);
void lista_parques(Parque *lparques[LEITURA]);
void limpa_parque(Parque *parque);
void faturacao_2(char *nome, char *data, char conteudo);
void faturacao_1(char *nome, char conteudo);
void remove_registo_parque(char *nome);

// Funções principais
void cria_parque(char *s);
void entrada_veiculos(char *s);
void saida_veiculos(char *s);
void lista_veiculos(char *s);
void faturacao(char *s);
void remove_parque(char *s);
void limpa_memoria();

#endif