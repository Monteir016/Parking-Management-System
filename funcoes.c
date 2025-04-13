#include "funcoes.h"
#include "estruturas.h"

Parque *Vparque = NULL; // Variável necessário para começar a lista Parque
Registo *Vregisto = NULL; // Variável necessário para começar a lista Registo

int num_parque = 0; // Variável que guarda o número de parques que exitem
char hora_anterior[HORAS]; // Variável que guarda a hora anterior
char data_anterior[DATA];  // Variável que guarda a data anterior

void adiciona_dta(){
    // Função que inicializa as variáveis hora_anterior e data_anterior
    // "teste" é utilizado para verificar se o carro ainda não saiu
    strcpy(hora_anterior,"teste"); 
    strcpy(data_anterior,"teste");
}

//// Funções que identificam elementos dentro das estruturas ////

// Função que procura um parque pelo nome dentro da lista Parques e o retorna
Parque* identifica_parque(char *nome){
    Parque *parque_atual = Vparque;
    while (parque_atual != NULL) {
        if (strcmp(nome, parque_atual->nome) == 0) {
            return parque_atual;
        }
        parque_atual = parque_atual->prox;
    }
    printf("%s: no such parking.\n", nome); // Caso não encontre o parque
    return NULL;
}

// Função que retorna um carro pelo nome da matrícula
Carro* identifica_carro(char *matricula, Parque *parque){
    Carro *carro_atual = parque->carros;
    while (carro_atual != NULL) {
        if (strcmp(matricula, carro_atual->matricula) == 0) {
            return carro_atual;
        }
        carro_atual = carro_atual->prox;
    }
    return NULL;
}

// Função que retorna um registo pelo nome da matrícula
Registo* identifica_registo(char *matricula){
    Registo *registo_atual = Vregisto;
    while (registo_atual != NULL) {
        if (strcmp(matricula, registo_atual->matricula) == 0 
        && strcmp(registo_atual->hr_saida,"teste") == 0) {
            return registo_atual;
        }
        registo_atual = registo_atual->prox;
    }
    return NULL;
}

// Função que retorna um array de carros com a mesma matrícula
void identifica_carro_registo(char *matricula, int *num_carros_encontrados, Registo *carros_encontrados[LEITURA]) {
    int num_carros = 0;
    Registo *registo_atual = Vregisto;
    while (registo_atual != NULL) {
        if (strcmp(matricula, registo_atual->matricula) == 0) {
            carros_encontrados[num_carros] = registo_atual;
            num_carros++;
        }
        registo_atual = registo_atual->prox;
    }
    carros_encontrados[num_carros] = NULL;
    *num_carros_encontrados = num_carros;
}

/* Função que retorna um array de registo de carros que estiveram no mesmo
parque e saíram no mesmo dia */
void identifica_faturacao_dia(Parque *parque,char *data, 
int *num_carros_encontrados, Registo *carros[LEITURA]) {
    int num_carros = 0;
    Registo *registo = Vregisto;
    while (registo != NULL) {
        if (strcmp(parque->nome, registo->nome) == 0 
        && strcmp(data, registo->data_saida) == 0) {
            carros[num_carros] = registo;
            num_carros++;
        }
        registo = registo->prox;
    }
    carros[num_carros] = NULL;
    *num_carros_encontrados = num_carros;
}

/* Função que retorna um array de registo de carros 
que estiveram no mesmo parque */
void identifica_faturacao_nome(Parque *parque, int *num_carros_encontrados, Registo *carros[LEITURA]) {
    int num_carros = 0;
    Registo *registo = Vregisto;
    while (registo != NULL) {
        if (strcmp(parque->nome, registo->nome) == 0
        && strcmp(registo->hr_saida, "teste") != 0) {
            carros[num_carros] = registo;
            num_carros++;
        }
        registo = registo->prox;
    }
    carros[num_carros] = NULL;
    *num_carros_encontrados = num_carros;
    }

//// Funções que verificam condições ////

// Verifica se a faz parte das 6 combinações possíveis de matrículas
int verifica_combinacao(char c1,char c2,char c3,char c4,char c5,char c6) {
    return ((isalpha(c1) && isalpha(c2) && isdigit(c3) 
    && isdigit(c4) && isdigit(c5) && isdigit(c6)) ||
        (isdigit(c1) && isdigit(c2) && isalpha(c3) 
        && isalpha(c4) && isdigit(c5) && isdigit(c6)) ||
        (isdigit(c1) && isdigit(c2) && isdigit(c3) 
        && isdigit(c4) && isalpha(c5) && isalpha(c6)) ||
        (isdigit(c1) && isdigit(c2) && isalpha(c3) 
        && isalpha(c4) && isalpha(c5) && isalpha(c6)) ||
        (isalpha(c1) && isalpha(c2) && isdigit(c3) 
        && isdigit(c4) && isalpha(c5) && isalpha(c6)) ||
        (isalpha(c1) && isalpha(c2) && isalpha(c3) 
        && isalpha(c4) && isdigit(c5) && isdigit(c6)));
}
// Verifica se a matrícula é válida
int verifica_matricula(char *matricula){
    char c1,c2,c3,c4,c5,c6;
    sscanf(matricula,"%c%c-%c%c-%c%c",&c1,&c2,&c3,&c4,&c5,&c6);
    if (verifica_combinacao(c1, c2, c3, c4, c5, c6)) {
        return 1;
    } else {
        printf("%c%c-%c%c-%c%c: invalid licence plate.\n",c1,c2,c3,c4,c5,c6);
        return 0;
    }
}

// Verifica se o carro já está no parque
int verifica_carro(char *matricula){
    Parque *estacionamento = Vparque;
    while(estacionamento != NULL){
        Carro *matricula_comp = estacionamento->carros;
        while (matricula_comp != NULL) {
            if (strcmp(matricula, matricula_comp->matricula) == 0) {
                printf("%s: invalid vehicle entry.\n", matricula);
                return 0;
            }
            matricula_comp = matricula_comp->prox;
        }
        estacionamento = estacionamento->prox;
    }
    return 1;
}

// Verifica se a data e hora são válidas e posteriores ao último registo
int verifica_data_hora(char *data, char *hr){
    int dia,mes,ano,hora,minuto;
    sscanf(data,"%d-%d-%d",&dia,&mes,&ano);
    sscanf(hr,"%d:%d",&hora,&minuto);
    int dias_mes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (strcmp(hora_anterior,"teste")!=0 && strcmp(data_anterior,"teste")!=0) {
        int dia1,mes1,ano1,hora1,minuto1;
        sscanf(data_anterior, "%d-%d-%d", &dia1, &mes1, &ano1);
        sscanf(hora_anterior, "%d:%d", &hora1, &minuto1);
        if ((1 <= dia && dia <= dias_mes[mes-1]) && (1 <= mes && mes <= 12) && (0000 <= ano && ano <= 2100) &&
            (0 <= hora && hora <= 23) && (0 <= minuto && minuto <= 59) && (ano > ano1 || (ano == ano1 && mes > mes1) 
            || (ano == ano1 && mes == mes1 && dia > dia1) || (ano == ano1 && mes == mes1 && dia == dia1 && hora > hora1) ||
            (ano == ano1 && mes == mes1 && dia == dia1 && hora == hora1 && minuto >= minuto1))) {
            return 1;
        } else {
            printf("invalid date.\n");
            return 0;
            }
    }
    else if ((1 <= dia && dia <= dias_mes[mes-1]) && (1 <= mes && mes <= 12) && (0000 <= ano && ano <= 2100) &&
        (0 <= hora && hora <= 23) && (0 <= minuto && minuto <= 59)) {
        return 1;
    } else {
        printf("invalid date.\n");
        return 0;
    }
}

// Verifica se a data é válida e anterior ao último registo
int verifica_data(char *data){
    int dia,mes,ano,dia1,mes1,ano1;
    sscanf(data,"%d-%d-%d",&dia,&mes,&ano);
    sscanf(data_anterior, "%d-%d-%d", &dia1, &mes1, &ano1);
    int dias_mes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((1 <= dia && dia <= dias_mes[mes-1]) && (1 <= mes && mes <= 12) && (0000 <= ano && ano <= 2100) 
    && (ano < ano1 || (ano == ano1 && mes < mes1) || (ano == ano1 && mes == mes1 && dia < dia1) 
    || (ano == ano1 && mes == mes1 && dia == dia1))) {
        return 1;
    } else {
        printf("invalid date.\n");
        return 0;
    }
}

// Verifica se as condições para criar um parque são válidas
int verifica_condições(char *nome, int capacidade, float valori, float valorf, float valord,int num_parque){
    Parque *parque_atual = Vparque;
    while (parque_atual != NULL) {
        // Verifica se o parque já existe
        if (strcmp(nome, parque_atual->nome) == 0) {
            printf("%s: parking already exists.\n", nome);
            return 0;
        }
        parque_atual = parque_atual->prox;
    }
    // Verifica se a existe capacidade no parque
    if (capacidade<=0){
        printf("%d: invalid capacity.\n",capacidade);
        return 0;
    }
    // Verifica se os valores são válidos
    if(valori <= 0 || valorf <= 0 || valord <= 0 ||!(valori < valorf && valorf < valord)){
        printf("invalid cost.\n");
        return 0;
    }
    // Verifica se o máximo de parques foi atingido
    if(num_parque >= MAX){
        printf("too many parks.\n");
        return 0;
    }
    return 1;
}

// Verifica se o carro está no parque
int verifica_carro_parque(char *matricula,Parque *parque){ 
    Carro *matricula_carro=parque->carros;
    while(matricula_carro != NULL){
        if (strcmp(matricula,matricula_carro->matricula) == 0){
            return 1;
        }
        matricula_carro=matricula_carro->prox;
    }
    printf("%s: invalid vehicle exit.\n",matricula);
    return 0;
}

//// Funções auxiliares ////

// Função que calcula o total de minutos numa data e hora
long calcula_minutos(int ano, int mes, int dia, int hora, int minuto) {
    long total_minutos = 0;
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    total_minutos += ano * 525600;
    for (int i = 0; i < mes - 1; i++) {
        total_minutos += 1440 * dias_mes[i];
    }
    total_minutos += 1440 * dia;
    total_minutos += 60 * hora;
    total_minutos += minuto;
    return total_minutos;
}

// Função que calcula o custo total de um carro
void calcula_custos(float valori, float valorf, float valord, long minutos_total, float *valor_total) {
    if (minutos_total <= 4) {
        float adicionar = minutos_total * valori;
        if (adicionar > valord) {
            adicionar = valord;
        }
        *valor_total += adicionar;
        return;
    } else if (minutos_total > 4 && minutos_total <= 96) {
        float adicionar= (4 * valori) + ((minutos_total - 4) * valorf);
        if (adicionar > valord) {
            adicionar = valord;
        }
        *valor_total += adicionar;
        return;
    } else if (minutos_total > 96) {
        *valor_total += valord;
        minutos_total = minutos_total - 96;
        calcula_custos(valori, valorf, valord, minutos_total, valor_total);
    }
}

// Função que calcula o valor total que o carro pagou
float calcula_valor(Carro *carro, Parque *parque, char *hr_saida, char *data_saida) {
    int dia1, mes1, ano1, hora1, minuto1, dia2, mes2, ano2, hora2, minuto2;
    sscanf(carro->data_entrada, "%d-%d-%d", &dia1, &mes1, &ano1);
    sscanf(carro->hr_entrada, "%d:%d", &hora1, &minuto1);
    sscanf(data_saida, "%d-%d-%d", &dia2, &mes2, &ano2);
    sscanf(hr_saida, "%d:%d", &hora2, &minuto2);
    float valor_total = 0.0;
    float valori = parque->valori;
    float valorf = parque->valorf;
    float valord = parque->valord;
    long minutos_entrada, minutos_saida,minutos_total;
    minutos_entrada = calcula_minutos(ano1, mes1, dia1, hora1, minuto1);
    minutos_saida = calcula_minutos(ano2, mes2, dia2, hora2, minuto2);
    // Calcula o total de minutos que o carro esteve no parque
    minutos_total = minutos_saida - minutos_entrada;
    // Divide em intervalos de 15 minutos arrendando para cima
    if (minutos_total % 15 == 0) {
        minutos_total = minutos_total / 15;
    } else {
        minutos_total = (minutos_total / 15) + 1;
    }
    calcula_custos(valori, valorf, valord, minutos_total, &valor_total);
    return valor_total;
}

// Função que calcula a faturação de um dia
void calcula_faturacao_dia(Registo *carros[], int num_carros) {
    char comparar[DATA];
    float valor_total = 0.0;
    int i = 0;
    while (i < num_carros) {
        strcpy(comparar, carros[i]->data_saida);
        int j = i;
        while (j < num_carros && strcmp(comparar, carros[j]->data_saida) == 0) {
            valor_total += carros[j]->valor_pago;
            j++;
        }
        printf("%s %.2f\n", carros[i]->data_saida, valor_total);
        valor_total = 0.0;
        i = j;
    }
}

// Função que adiciona um parque à lista de parques
void adiciona_parque(char *nome, int capacidade, float valori, float valorf, float valord, Parque *novo_parque) {
    novo_parque->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(novo_parque->nome, nome);
    novo_parque->capacidade = capacidade;
    novo_parque->lugares_disponiveis = capacidade;
    novo_parque->valori = valori;
    novo_parque->valorf = valorf;
    novo_parque->valord = valord;
    novo_parque->carros = NULL;
    novo_parque->prox = NULL;
    if (Vparque == NULL) {
        Vparque = novo_parque;
        num_parque++;
    } else {
        Parque *parque_atual = Vparque;
        while (parque_atual->prox != NULL) {
            parque_atual = parque_atual->prox;
        }
        parque_atual->prox = novo_parque;
        num_parque++;
    }
}

// Função que copia o registo de entrada para a lista de registos
void copia_registo_entrada(Parque *parque, Registo *novo_registo, 
char *hr_entrada, char *matricula, char *data_ea) {
    int hr_entrada1, minuto_entrada1;
    strcpy(novo_registo->hr_saida, "teste");
    strcpy(novo_registo->data_saida, "teste");
    sscanf(hr_entrada, "%02d:%02d", &hr_entrada1, &minuto_entrada1);
    sprintf(novo_registo->hr_entrada, "%02d:%02d", hr_entrada1, minuto_entrada1);
    strcpy(novo_registo->matricula, matricula);
    strcpy(novo_registo->data_entrada, data_ea);
    strcpy(hora_anterior, hr_entrada);
    strcpy(data_anterior, data_ea);
    novo_registo->nome = malloc(strlen(parque->nome) + 1);
    strcpy(novo_registo->nome, parque->nome);
    novo_registo->prox = NULL;
    if (Vregisto == NULL) {
        Vregisto = novo_registo;
    } else {
        Registo *registo_atual = Vregisto;
        while (registo_atual->prox != NULL) {
            registo_atual = registo_atual->prox;
        }
        registo_atual->prox = novo_registo;
    }
}

// Função que adiciona um carro à lista de carros e regista a entrada
void adicionar_carro(Parque *parque, char *matricula, char *data_ea, 
char *hr_entrada) {
    Carro *novo_carro = malloc(sizeof(Carro));
    Registo *novo_registo = malloc(sizeof(Registo));
    strcpy(novo_carro->matricula, matricula);
    strcpy(novo_carro->data_entrada, data_ea);
    strcpy(novo_carro->hr_entrada, hr_entrada);
    novo_carro->prox = NULL;
    if (parque->carros == NULL) {
        parque->carros = novo_carro;
    } else {
        Carro *carro_atual = parque->carros;
        while (carro_atual->prox != NULL) {
            carro_atual = carro_atual->prox;
        }
        carro_atual->prox = novo_carro;
    }
    copia_registo_entrada(parque, novo_registo, hr_entrada, matricula, data_ea);
    parque->lugares_disponiveis -= 1;
}

// Função que retira um carro da lista de carros e regista a saída
void retira_carro(Carro *carro,char *hr_saida,char *data_saida,Parque *parque,Registo *registo) {
    int hr_saida1, minuto_saida1;
    sscanf(hr_saida, "%02d:%02d", &hr_saida1, &minuto_saida1);
    sprintf(registo->hr_saida, "%02d:%02d", hr_saida1, minuto_saida1);
    strcpy(registo->data_saida, data_saida);
    strcpy(hora_anterior, hr_saida);
    strcpy(data_anterior, data_saida);
    float valor_pago = calcula_valor(carro, parque, hr_saida, data_saida);
    registo->valor_pago = valor_pago;
    if (parque->carros == carro) {
        parque->carros = carro->prox;
    } else {
        Carro *carro_atual = parque->carros;
        while (carro_atual->prox != carro) {
            carro_atual = carro_atual->prox;
        }
        carro_atual->prox = carro->prox;
    }
    // Liberta a memória do carro
    free(carro);
    return;
}

// Função que compara os carros para ordenar através de merge sort
void comparar_carros(Registo *carros[], int anterior, int agr, int dps, 
char conteudo) {
    int i, j, k;
    int n1 = agr - anterior + 1;
    int n2 = dps - agr;
    Registo *E[n1], *D[n2];
    for (i = 0; i < n1; i++)
        E[i] = carros[anterior + i];
    for (j = 0; j < n2; j++)
        D[j] = carros[agr + 1 + j];
    i = 0;
    j = 0; 
    k = anterior;
    while (i < n1 && j < n2) {
        if (conteudo == 0 && strcmp(E[i]->nome, D[j]->nome) <= 0) {
            carros[k] = E[i];
            i++;
        } else if (conteudo == 1 && strcmp(E[i]->data_saida, 
        D[j]->data_saida) <= 0) {
            if (strcmp(E[i]->data_saida, D[j]->data_saida) < 0) {
                carros[k] = E[i];
                i++;
            } else if (strcmp(E[i]->data_saida, D[j]->data_saida) == 0) {
                int hr_saida1, minuto_saida1, hr_saida2, minuto_saida2;
                sscanf(E[i]->hr_saida, "%02d:%02d", &hr_saida1, &minuto_saida1);
                sscanf(D[j]->hr_saida, "%02d:%02d", &hr_saida2, &minuto_saida2);
                if (hr_saida1 < hr_saida2 || (hr_saida1 == hr_saida2 && minuto_saida1 <= minuto_saida2)) {
                    carros[k] = E[i];
                    i++;
                } else {
                    carros[k] = D[j];
                    j++;
                }
            } else {
                carros[k] = D[j];
                j++;
            }
        } else {
            carros[k] = D[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        carros[k] = E[i];
        i++;
        k++;
    }
    while (j < n2) {
        carros[k] = D[j];
        j++;
        k++;
    }
}

// Função que compara os parques para ordenar através de merge sort
void comparar_parques(Parque *lparques[], int anterior, int agr, int dps){
    int i, j, k;
    int n1 = agr - anterior + 1;
    int n2 = dps - agr;
    Parque *E[n1], *D[n2];
    for (i = 0; i < n1; i++)
        E[i] = lparques[anterior + i];
    for (j = 0; j < n2; j++)
        D[j] = lparques[agr + 1 + j];
    i = 0; 
    j = 0; 
    k = anterior;
    while (i < n1 && j < n2) {
        if (strcmp(E[i]->nome, D[j]->nome) <= 0) {
            lparques[k] = E[i];
            i++;
        } else {
            lparques[k] = D[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        lparques[k] = E[i];
        i++;
        k++;
    }
    while (j < n2) {
        lparques[k] = D[j];
        j++;
        k++;
    }
}

// Função que ordena a lista de carros e parques
void ordena_lista_carros(Registo *carros[], Parque *lparques[], int anterior,
int dps, char conteudo) {
    if (anterior < dps) {
        int agr = anterior + (dps - anterior) / 2;
        ordena_lista_carros(carros, lparques, anterior, agr, conteudo);
        ordena_lista_carros(carros, lparques, agr + 1, dps, conteudo);
        if (lparques != NULL){
            comparar_parques(lparques, anterior, agr, dps);
        }
        if (carros != NULL){
            comparar_carros(carros, anterior, agr, dps, conteudo);
        }
    }
}

// Função que lista os parques existentes
void lista_parques(Parque *lparques[LEITURA]) {
    Parque *parque_atual = Vparque;
    int i = 0;
    while (parque_atual != NULL && i < num_parque) {
        lparques[i] = parque_atual;
        parque_atual = parque_atual->prox;
        i++;
    }
    lparques[num_parque] = NULL;
    return;
}

// Função que limpa a memória de um parque
void limpa_parque(Parque *parque) {
    while (parque->carros != NULL) {
        Carro *carro = parque->carros;
        parque->carros = parque->carros->prox;
        free(carro);
    }
    if (Vparque == parque) {
        Vparque = parque->prox;
    } else {
        Parque *prev = Vparque;
        while (prev->prox != NULL && prev->prox != parque){
            prev = prev->prox;
        }
        if (prev->prox != NULL) {
            prev->prox = parque->prox;
        }
    }
    free(parque->nome);
    free(parque);
}

// Função que faz a lista dos valores facturados num determinado dia
void faturacao_2(char *nome, char *data, char conteudo) {
    Parque *parque = identifica_parque(nome);
    Registo *carros[LEITURA];
    int num_carros = 0;
    if (parque != NULL && verifica_data(data)) {
        identifica_faturacao_dia(parque, data, &num_carros, carros);
        ordena_lista_carros(carros, NULL, 0, num_carros-1, conteudo);
        for (int i = 0; i < num_carros; i++) {
                printf("%s %s %.2f\n",carros[i]->matricula,
                carros[i]->hr_saida,carros[i]->valor_pago);
            }
    }
}

// Função que faz o resumo da facturação diária do parque de estacionamento
void faturacao_1(char *nome, char conteudo) {
    Parque *parque = identifica_parque(nome);
    Registo *carros[LEITURA];
    int num_carros = 0;
    if (parque != NULL) {
        identifica_faturacao_nome(parque, &num_carros, carros);
        ordena_lista_carros(carros, NULL, 0, num_carros-1, conteudo);
        calcula_faturacao_dia(carros, num_carros);
    }
}

// Função que remove um registo da lista de registos
void remove_registo_parque(char *nome) {
    Registo *atual = Vregisto;
    Registo *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            Registo *registo = atual;
            atual = atual->prox;
            if (anterior == NULL) {
                Vregisto = atual;
            } else {
                anterior->prox = atual;
            }
            free(registo);
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}


//// Funções principais ////

// Função que cria um parque de estacionamento
void cria_parque(char *s) {
    int capacidade;
    float valori, valorf, valord;
    char nome[BUFSIZE];
    if (strlen(s) > 2) {
        // Verifica se o nome do parque tem aspas
        if (s[2] == '"') {
            sscanf(s, "p \"%[^\"]\" %d %f %f %f",nome,
            &capacidade,&valori,&valorf,&valord);
        } else {
            sscanf(s, "p %s %d %f %f %f",nome,
            &capacidade,&valori,&valorf,&valord);
        }
    } else {
        Parque *parque_atual = Vparque;
        while (parque_atual != NULL) {
            printf("%s %d %d\n", parque_atual->nome, parque_atual->capacidade,
                   parque_atual->lugares_disponiveis);
            parque_atual = parque_atual->prox;
        }
        return;
    }
    Parque *novo_parque = malloc(sizeof(Parque));
    if (!(verifica_condições(nome, capacidade, valori, valorf, 
    valord,num_parque))){
        free(novo_parque);
        return;
    }
    adiciona_parque(nome, capacidade, valori, valorf, valord, novo_parque);
}

// Função que regista a entrada de um veículo
void entrada_veiculos(char *s){
    char data[DATA],hr_entrada[HORAS],matricula[MATRICULA];
    if (strlen(s) > 2) {
        char nome[BUFSIZE];
        // Verifica se o nome do parque tem aspas
        if (s[2] == '"') {
            sscanf(s, "e \"%[^\"]\" %s %s %s",nome,matricula,data,hr_entrada);
        } else {
            sscanf(s, "e %s %s %s %s", nome, matricula, data, hr_entrada);
        }
        Parque *parque = identifica_parque(nome);
        if (parque != NULL) {
            if (parque->lugares_disponiveis <= 0) {
                printf("%s: parking is full.\n", nome);
            } else {
                if (verifica_matricula(matricula) && verifica_carro(matricula)
                && verifica_data_hora(data, hr_entrada)) {
                    adicionar_carro(parque, matricula, data, hr_entrada);
                    Carro *carro_atual = parque->carros;
                    while (carro_atual != NULL) {
                        carro_atual = carro_atual->prox;
                    }
                    printf("%s %d\n", nome, parque->lugares_disponiveis);
                }
            } 
        }  
    }
}

// Função que regista a saída de um veículo
void saida_veiculos(char *s){
    char hr_saida[HORAS],matricula[MATRICULA],data_saida[DATA],nome[BUFSIZE];
    if (strlen(s) > 2){
        if (s[2] == '"') {
            // Verifica se o nome do parque tem aspas
            sscanf(s, "s \"%[^\"]\" %s %s %s", nome, matricula, 
            data_saida, hr_saida);
        } else {
            sscanf(s, "s %s %s %s %s",nome,matricula,data_saida,hr_saida);
        }
        Parque *parque = identifica_parque(nome);
        if (parque!=NULL&& verifica_matricula(matricula)&&
        verifica_carro_parque(matricula,parque)&& 
        verifica_data_hora(data_saida,hr_saida)){
            Carro *carro=identifica_carro(matricula,parque);
            Registo *registo=identifica_registo(matricula);
            if (registo != NULL) {
                retira_carro(carro, hr_saida, data_saida, parque, registo);
                parque->lugares_disponiveis+=1;
                int hr_entrada1,minutos_entrada1,hr_saida1,minuto_saida1;
                sscanf(registo->hr_entrada,"%02d:%02d",
                &hr_entrada1,&minutos_entrada1);
                sscanf(registo->hr_saida,"%02d:%02d",
                &hr_saida1,&minuto_saida1);
                printf("%s %s %02d:%02d %s %02d:%02d %.2f\n",registo->matricula,
                registo->data_entrada,hr_entrada1,minutos_entrada1,
                registo->data_saida,hr_saida1,minuto_saida1,registo->valor_pago);
            }
        }
    }
}

// Função que lista as entradas e saídas de um veículo
void lista_veiculos(char *s) {
    int num_carros = 0;
    char conteudo = 0; // ordenar pelo nome
    Registo *carros[LEITURA];
    char matricula[MATRICULA];
    sscanf(s, "v %s", matricula);
    if (verifica_matricula(matricula)) {
        identifica_carro_registo(matricula, &num_carros, carros);
        if (num_carros == 0) {
            printf("%s: no entries found in any parking.\n", matricula);
        } else {
            ordena_lista_carros(carros,NULL,0,num_carros-1,conteudo);
            for (int i = 0; i < num_carros; i++) {
                // Retorna o registo do carro dependendo se já saiu ou não
                if (strcmp(carros[i]->hr_saida, "teste")==0){
                    printf("%s %s %s\n", carros[i]->nome, 
                    carros[i]->data_entrada, carros[i]->hr_entrada);
                } else {
                    printf("%s %s %s %s %s\n", carros[i]->nome, 
                    carros[i]->data_entrada, carros[i]->hr_entrada, 
                    carros[i]->data_saida,carros[i]->hr_saida);
                }
            }
        }
    }
}

// Função que mostra a facturação de um parque de estacionamento
void faturacao(char *s){
    char nome[BUFSIZE], data[DATA];
    char conteudo = 1; // ordenar pela data
    // Verifica se o nome do parque tem aspas
    if (s[2] == '"') {
        // Verifica se tem um ou dois argumentos
        if (sscanf(s, "f \"%[^\"]\" %s", nome, data) == 2){
            faturacao_2(nome,data,conteudo);
        }
        else if (sscanf(s, "f \"%[^\"]\"", nome) == 1){
            faturacao_1(nome,conteudo);
        }
    }
    else{
        if (sscanf(s, "f %s %s", nome, data) == 2){
            faturacao_2(nome,data,conteudo);
        }
        else if (sscanf(s, "f %s", nome) == 1){
            faturacao_1(nome,conteudo);
        }
    }
}

// Função que remove um parque de estacionamento e as suas entradas e saídas
void remove_parque(char *s){
    int conteudo = 0; // ordenar pelo nome
    char nome[BUFSIZE];
    if (s[2] == '"') {
        sscanf(s, "r \"%[^\"]\"", nome);
    } else {
        sscanf(s, "r %s", nome);
    }
    Parque *parque = identifica_parque(nome);
    Parque *lparques[LEITURA];
    if (parque != NULL) {
        limpa_parque(parque);
        remove_registo_parque(nome);
        num_parque--;
        lista_parques(lparques);
        ordena_lista_carros(NULL, lparques, 0, num_parque-1, conteudo);
        for (int i = 0; i < num_parque; i++) {
            printf("%s\n", lparques[i]->nome);
        }
    }
}

// Função que liberta a memória alocada
void limpa_memoria() {
    Parque *parque_atual = Vparque;
    while (parque_atual != NULL) {
        Carro *carro_atual = parque_atual->carros;
        while (carro_atual != NULL) {
            Carro *carro_temp = carro_atual;
            carro_atual = carro_atual->prox;
            free(carro_temp);
        }
        Parque *parque_temp = parque_atual;
        parque_atual = parque_atual->prox;
        free(parque_temp->nome);
        free(parque_temp);
    }
    Vparque = NULL;
    Registo *registo_atual = Vregisto;
    while (registo_atual != NULL) {
        Registo *registo_temp = registo_atual;
        registo_atual = registo_atual->prox;
        free(registo_temp->nome);
        free(registo_temp);
    }
    Vregisto = NULL;
}


