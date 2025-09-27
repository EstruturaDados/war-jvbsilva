// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
enum{
    MAX_TERRITORIOS = 5,
    TAM_NOME = 30,
    TAM_COR = 10
};

const char invalid_value_error_msg[] = "Valor inválido.\n";
const char line[] = "==================================\n";
const char semiline[] = "----------------------------------\n";

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// Declarações das funções
void liberarMemoria(struct Territorio* mapa);

// Função para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para garantir: 
// - string não vazia;
// - limpeza do buffer quando input menor que o tamanho máximo;
void get_str_input(const char input_msg[], char target[], int max_size){
    while(1){
        printf("%s",input_msg);
        fgets(target, max_size, stdin);
        // Checa se a função fgets truncou o input para em seguida limpar o buffer de entrada
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

// Função para ler inteiros usando scanf
void get_int_input(const char input_msg[], int* target) {
    int valid = 0;
    while(!valid){
        printf("%s", input_msg);
        if(scanf("%d", target) == 1 && *target >= 0){
            valid = 1;
            limparBufferEntrada();
        } else {
            printf("%s",invalid_value_error_msg);
            limparBufferEntrada();
        }
    }
    return;
}

// Função para ler as informações de um Territorio usando scanf para nome e tropas conforme requisitos
void read_territorio(struct Territorio territorios[], int num_territorio){
        printf("--- Cadastrando Territorio %d ---\n",num_territorio+1);
        
        get_str_input("Nome do territorio: ", territorios[num_territorio].nome, TAM_NOME);
        get_str_input("Cor do territorio: ", territorios[num_territorio].cor, TAM_COR);
        get_int_input("Número de Tropas: ", &territorios[num_territorio].tropas);
        printf("\n");
}


int read_num_territorios() {
    int num_territorios;
    get_int_input("Escolha a quantidade de territórios: ", &num_territorios);
    return num_territorios;
}

void inicia_territorios(struct Territorio* territorios, int* num_territorios) {
    printf("%s", line);
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n", *num_territorios);
    printf("%s", line);

    for (int i = 0; i < *num_territorios; i++) {
        read_territorio(territorios, i);
    }
}

void exibe_estado_atual(struct Territorio* territorios, int* num_territorios, int* p_turno) {
    // Incrementa o turno em 1 usando o ponteiro p_turno
    *p_turno += 1;
    
    // Exibe turno atual
    printf("%s", line);
    printf("             TURNO %d\n",*p_turno);
    printf("%s", semiline);
    printf("   MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("%s", line);
    printf("\n");

    // Exibe status atual dos territórios
    for (int i = 0; i < *num_territorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Função para simular o lançamento de um dado (1-6)
int rolar_dados() {
    return rand() % 6 + 1;
}

// Função de ataque conforme requisitos - utiliza rand() para simular dados de batalha
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    
    // Checa se atacante e defensor tem a mesma cor (proibido)
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("--- COMBATE ---\n");
        printf("Atacante e Defensor pertencem ao mesmo exército.\n");
        printf("Nada acontece.\n");
        return;
    }

    // Exibe o combate
    printf("--- COMBATE ---\n");
    int ataque = rolar_dados();
    printf("Atacante(%s) rolou %d\n", atacante->cor, ataque);
    int defesa = rolar_dados();
    printf("Defensor(%s) rolou %d\n", defensor->cor, defesa);
    
    // Calcula e exibe o resultado do ataque conforme requisitos
    printf("--- Resultado ---\n");

    // Se atacante vencer: transfere cor e metade das tropas
    if (ataque > defesa) {
        printf("Ataque(%s) ganhou!\n", atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        int tropas_transferidas = atacante->tropas / 2;
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;
        printf("Territorio %s conquistado pelo exercito %s!\n", defensor->nome, defensor->cor);
    } else {
        // Se atacante perder: perde uma tropa
        atacante->tropas -= 1;
        printf("Defesa(%s) ganhou!\n", defensor->cor);
        printf("Exercito Atacante(%s) perde uma tropa.\n", atacante->cor);
    }
    return;
}


void game_loop(struct Territorio* territorios, int* num_territorios) {
    
    int turno = 0;
    int* p_turno = &turno;

    while (1) {

        // - Exibe estado atual
        exibe_estado_atual(territorios, num_territorios, p_turno);

        // Turno de ataque
        int num_atacante = -1;
        int num_defensor = -1;
        printf("%s", line);
        printf("          FASE DE ATAQUE\n");
        printf("%s", line);

        // Checa se o usuário entrou um valor válido para o Atacante
        while (num_atacante < 0 || num_atacante > *num_territorios) {
            get_int_input("Digite o número do territorio ATACANTE ou 0 para sair: ", &num_atacante);
            if (num_atacante > *num_territorios) {
                printf("%s", invalid_value_error_msg);
            }
        }

        // Checa se o usuário digitou para sair
        if (num_atacante == 0) {
            break;
        }

        // Checa se o usuário entrou um valor válido para o Defensor
        while (num_defensor < 0 || num_defensor > *num_territorios) {
            get_int_input("Digite o número do territorio DEFENSOR ou 0 para sair: ", &num_defensor);
            if (num_defensor > *num_territorios) {
                printf("%s", invalid_value_error_msg);
            }
        }

        // Checa se o usuário digitou para sair
        if (num_defensor == 0) {
            break;
        }

        // Realiza o ataque
        atacar(&territorios[num_atacante - 1], &territorios[num_defensor - 1]);
    }
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {

    // - Aloca a memória para o mapa do mundo usando calloc conforme requisitos
    int num_territorios = read_num_territorios();
    struct Territorio* territorios = calloc(num_territorios, sizeof(struct Territorio));
    
    // Inicializa gerador de números aleatórios uma única vez
    srand(time(NULL));

    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    inicia_territorios(territorios, &num_territorios);

    // Entra no loop do jogo
    game_loop(territorios, &num_territorios);

    // Libera a memoria usando função específica conforme requisitos
    liberarMemoria(territorios);
    return 0;
}

// Função para liberar memória alocada dinamicamente conforme requisitos
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}
