// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// ## 🧩 Nível Novato: Cadastro Inicial dos Territórios
// ### 🎯 Objetivo
// - Criar uma `struct` chamada `Territorio`.
// - Usar um **vetor estático de 5 elementos** para armazenar os territórios.
// - Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
// - Exibir o estado atual do mapa.
// ### ⚙️ Funcionalidades
// - Leitura de dados pelo terminal
// - Impressão organizada dos dados de todos os territórios
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
enum{
    MAX_TERRITORIOS = 5,
    TAM_STRING = 5
};

const char invalid_value_error_msg[] = "Valor inválido.\n";

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int num_tropas;
};

// Função para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para garantir: 
// - string não vazia;
// - limpeza do buffer quando input menor que TAM_STRING;
void get_str_input(const char input_msg[], char target[]){
    while(1){
        printf("%s",input_msg);
        fgets(target, TAM_STRING, stdin);
        // Checa se a função fgets truncou o input para em seguida limpar o buffe de entrada
        if (strchr(target, '\n') == NULL) {  
            limparBufferEntrada();
        // Se não truncou então existe um '\n' no final da string que iremos remover
        }else{
            target[strlen(target) - 1] = 0;
        }
        // Se a entrada do usuário tem pelo menos um caractere pare
        if(strlen(target) != 0){
            break;
        // Se a entrada for vazia informe e continue o loop até atender os critérios
        }else{
            printf("%s",invalid_value_error_msg);
        }
    }
    return;
}

// Função para ler inteiros
void get_int_input(const char input_msg[], int* target) {
    char buffer[TAM_STRING];
    char *endptr;
    long number;
    int valid = 0;

    while(!valid){
        get_str_input(input_msg,buffer);
        // Convertendo de string para inteiro
        number = strtol(buffer, &endptr, 10);
        // Validando conversão
        if ((*endptr == '\n' ||*endptr == '\0') && number > 0) {
            *target = number;
            valid = 1;
            break;
        } else {
            printf("%s",invalid_value_error_msg);
        }
    }
    return;
}

// Função para ler as informações de um Territorio
void read_territorio(struct Territorio territorios[], int num_territorio){
        printf("--- Cadastrando Territorio %d ---\n",num_territorio+1);
        get_str_input("Nome do territorio: ", territorios[num_territorio].nome);
        get_str_input("Cor do territorio: ", territorios[num_territorio].cor);
        get_int_input( "Número de Tropas: ", &territorios[num_territorio].num_tropas);
        printf("\n");        
}

void inicia_territorios(struct Territorio territorios[]){
    printf("==================================\n");
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n",MAX_TERRITORIOS);
    for(int i = 0; i < MAX_TERRITORIOS;i++){
        read_territorio(territorios, i);
    }
}

void exibe_estado_atual(struct Territorio territorios[]){
    printf("==================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL   \n");
    printf("==================================\n");
    printf("\n");
    for(int i = 0; i < MAX_TERRITORIOS;i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n",i+1,territorios[i].nome, territorios[i].cor, territorios[i].num_tropas);
    }
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    struct Territorio territorios[MAX_TERRITORIOS];
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    inicia_territorios(territorios);
    // - Exibe estado atual
    exibe_estado_atual(territorios);
    return 0;
}
