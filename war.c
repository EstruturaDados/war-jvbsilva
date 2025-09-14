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
#include <ctype.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
enum{
    MAX_TERRITORIOS = 5,
    TAM_STRING = 50
};

const char invalid_value_error_msg[] = "Valor inválido.\n";

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int num_tropas;
};

// Função para mostrar mensagem de erro ao entrar valor inválido
void show_error_msg(){
    printf("%s",invalid_value_error_msg);
}

// Função para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para remover espaços no início e final da string
void trimString(char str[]) {
  int start = 0, end = strlen(str) - 1;

  // Remove leading whitespace
  while (isspace(str[start])) {
    start++;
  }
  // Remove trailing whitespace
  while (end > start && isspace(str[end])) {
    end--;
  }
  // If the string was trimmed, adjust the null terminator
  if (start > 0 || end < (strlen(str) - 1)) {
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
  }
}

// Função para garantir: 
// - string não vazia;
// - string sem espaços no início e fim;
// - limpeza do buffer quando input menor que TAM_STRING;
void get_str_input(const char input_msg[], char target[]){
    while(1){
        printf("%s",input_msg);
        fgets(target, TAM_STRING, stdin); // Read input as a string
        if (strchr(target, '\n') == NULL) {  // no newline → leftovers
            limparBufferEntrada();
        }
        trimString(target); // Remove espaços no inicio e final
        if(strlen(target) != 0){
            break;
        }else{
            show_error_msg();
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
        if (*endptr == '\0' && number > 0) {
            *target = number;
            valid = 1;
            break;
        } else {
            show_error_msg();
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
