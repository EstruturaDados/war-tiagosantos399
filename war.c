#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

//  Nível Novato: Struct do Território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

//  Nível Mestre: Sistema de Missões
typedef struct {
    int destruir_verde;
    int conquistar_3_territorios;
    int missao_atual;
} Missao;

//  Nível Aventureiro: Funções de Batalha
void inicializarTerritorios(Territorio *territorios, int quantidade);
void exibirMapa(const Territorio *territorios, int quantidade);
int simularBatalha(Territorio *atacante, Territorio *defensor);
int verificarMissao(const Missao *missao, const Territorio *territorios, int quantidade);
void menuPrincipal();

//  Nível Novato: Função principal
int main() {
    srand(time(NULL)); // Inicializar semente para números aleatórios
    menuPrincipal();
    return 0;
}

//  Nível Aventureiro: Inicialização dinâmica dos territórios
void inicializarTerritorios(Territorio *territorios, int quantidade) {
    // Dados pré-definidos para simplificar a entrada
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    const char *cores[] = {"Azul", "Vermelho", "Verde", "Amarelo", "Roxo"};
    const int tropas[] = {5, 3, 4, 2, 6};
    
    for (int i = 0; i < quantidade; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropas = tropas[i];
    }
}

//  Nível Novato: Exibição do mapa
void exibirMapa(const Territorio *territorios, int quantidade) {
    printf("\n=== MAPA ATUAL ===\n");
    printf("%-15s %-15s %-10s\n", "TERRITORIO", "EXERCITO", "TROPAS");
    printf("---------------------------------\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("%-15s %-15s %-10d\n", 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }
    printf("---------------------------------\n");
}

//  Nível Aventureiro: Simulação de batalha
int simularBatalha(Territorio *atacante, Territorio *defensor) {
    printf("\n=== BATALHA ===\n");
    printf("%s (%s) ataca %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Simular dados de batalha
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;
    
    printf("Dado de ataque: %d\n", dado_ataque);
    printf("Dado de defesa: %d\n", dado_defesa);
    
    // Lógica da batalha (empatas favorecem o atacante)
    if (dado_ataque >= dado_defesa) {
        defensor->tropas--;
        printf(" ATACANTE VENCEU! %s perde 1 tropa.\n", defensor->nome);
        
        // Verificar se defensor foi eliminado
        if (defensor->tropas <= 0) {
            printf(" %s FOI CONQUISTADO! Agora pertence ao exército %s.\n", 
                   defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1; // Tropa do conquistador
            return 1; // Conquista realizada
        }
    } else {
        atacante->tropas--;
        printf(" DEFENSOR VENCEU! %s perde 1 tropa.\n", atacante->nome);
    }
    
    return 0; // Nenhuma conquista
}

//  Nível Mestre: Verificação de missão
int verificarMissao(const Missao *missao, const Territorio *territorios, int quantidade) {
    int territorios_conquistados = 0;
    int exercito_verde_existe = 0;
    
    // Contar territórios conquistados (assumindo que Azul é o jogador)
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(territorios[i].cor, "Azul") == 0) {
            territorios_conquistados++;
        }
        if (strcmp(territorios[i].cor, "Verde") == 0) {
            exercito_verde_existe = 1;
        }
    }
    
    printf("\n=== VERIFICAÇÃO DE MISSÃO ===\n");
    
    switch (missao->missao_atual) {
        case 1: // Destruir exército Verde
            printf("Missão: Destruir o exército Verde\n");
            printf("Status: %s\n", exercito_verde_existe ? "PENDENTE" : "CONCLUÍDA!");
            return !exercito_verde_existe;
            
        case 2: // Conquistar 3 territórios
            printf("Missão: Conquistar 3 territórios\n");
            printf("Status: %d/3 territórios conquistados\n", territorios_conquistados);
            printf("Resultado: %s\n", territorios_conquistados >= 3 ? "CONCLUÍDA!" : "PENDENTE");
            return territorios_conquistados >= 3;
            
        default:
            return 0;
    }
}

//  Nível Mestre: Menu principal
void menuPrincipal() {
    //  Nível Aventureiro: Alocação dinâmica
    Territorio *territorios = (Territorio*)calloc(MAX_TERRITORIOS, sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("Erro na alocação de memória!\n");
        return;
    }
    
    // Inicializar territórios e missão
    inicializarTerritorios(territorios, MAX_TERRITORIOS);
    
    Missao missao;
    missao.missao_atual = 1; // Começa com a missão de destruir o Verde
    
    int opcao;
    int vitoria = 0;
    
    printf(" BEM-VINDO AO WAR ESTRUTURADO! \n");
    
    do {
        exibirMapa(territorios, MAX_TERRITORIOS);
        
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                // Sistema de ataque
                int atacante, defensor;
                
                printf("\nEscolha o território ATACANTE (1-%d): ", MAX_TERRITORIOS);
                scanf("%d", &atacante);
                printf("Escolha o território DEFENSOR (1-%d): ", MAX_TERRITORIOS);
                scanf("%d", &defensor);
                
                // Validar entradas
                if (atacante < 1 || atacante > MAX_TERRITORIOS || 
                    defensor < 1 || defensor > MAX_TERRITORIOS) {
                    printf("❌ Território inválido!\n");
                    break;
                }
                
                if (atacante == defensor) {
                    printf(" Não pode atacar o próprio território!\n");
                    break;
                }
                
                // Verificar se o atacante é do jogador (Azul)
                if (strcmp(territorios[atacante-1].cor, "Azul") != 0) {
                    printf(" Só pode atacar com territórios Azuis!\n");
                    break;
                }
                
                // Simular batalha
                simularBatalha(&territorios[atacante-1], &territorios[defensor-1]);
                
                // Verificar vitória após cada batalha
                vitoria = verificarMissao(&missao, territorios, MAX_TERRITORIOS);
                if (vitoria) {
                    printf("\n MISSÃO CONCLUÍDA! VOCÊ VENCEU O JOGO! \n");
                    opcao = 0; // Sair do jogo
                }
                break;
            }
                
            case 2:
                // Verificar missão atual
                vitoria = verificarMissao(&missao, territorios, MAX_TERRITORIOS);
                if (vitoria) {
                    // Avançar para próxima missão ou finalizar
                    if (missao.missao_atual == 1) {
                        printf("\n Missão 1 concluída! Avançando para Missão 2...\n");
                        missao.missao_atual = 2;
                    } else {
                        printf("\n TODAS AS MISSÕES CONCLUÍDAS! VOCÊ VENCEU! \n");
                        opcao = 0;
                    }
                }
                break;
                
            case 0:
                printf("Saindo do jogo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
        
        printf("\n");
        
    } while (opcao != 0);
    
    //  Nível Aventureiro: Liberar memória alocada
    free(territorios);
}