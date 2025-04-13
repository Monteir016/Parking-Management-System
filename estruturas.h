#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20 // Máximo de parques que podem ser criados
#define LEITURA 10000 // Máximo de entradas e saídas do mesmo carro
#define BUFSIZE 8192 // Tamanho máximo de caracteres que podem ser lidos
#define MATRICULA 9 // Tamanho máximo de caracteres de uma matrícula
#define HORAS 6 // Tamanho máximo de caracteres de uma hora
#define DATA 11 // Tamanho máximo de caracteres de uma data

typedef struct Carro{
    //estrutura que guarda a informação de entrada um carro num parque
    char hr_entrada[HORAS],data_entrada[DATA];
    char matricula[MATRICULA];
    struct Carro *prox;
} Carro;

typedef struct Parque{
    //estrutura que guarda a informação de um parque
    char *nome;
    int capacidade, lugares_disponiveis;
    float valori; //valor de permanência por cada 15 minutos na 1ªhora
    float valorf; //valor de permanência por cada 15 minutos depois da 1ªhora
    float valord; //valor de permanência máximo por dia
    Carro *carros;
    struct Parque *prox;
} Parque;

typedef struct Registo{
    //estrutura que guarda a informação das entradas e saídas dos carros
    char matricula[MATRICULA],data_entrada[DATA],hr_entrada[HORAS];
    char *nome,data_saida[DATA],hr_saida[HORAS];
    char data_entrada_inicial[DATA],hr_entrada_inicial[HORAS];
    float valor_pago;
    struct Registo *prox;
} Registo;

#endif