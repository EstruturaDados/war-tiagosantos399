#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 50
#define MAX_COR 20

// Struct do Território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Funções
void cadastrarTerritorios(Territorio *territorios, int quantidade);
void mostrarFormacao(const Territorio *territorios, int quantidade);

int main() {
    printf("=============================================\n\n");
    printf(" Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n\n");

    
    Territorio territorios[MAX_TERRITORIOS];
    
    // Cadastrar os territórios
    cadastrarTerritorios(territorios, MAX_TERRITORIOS);
    
    // Mostrar a formação final
    mostrarFormacao(territorios, MAX_TERRITORIOS);
    
    return 0;
}

void cadastrarTerritorios(Territorio *territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("--- Nome do Território %d ---\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        
        printf("Cor: ");
        scanf(" %[^\n]", territorios[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
}

void mostrarFormacao(const Territorio *territorios, int quantidade) {
    printf("\n=== FORMAÇÃO DAS TROPAS ===\n\n");
    
    printf("-----------------------------------------\n");
    printf("| TERRITÓRIO     | COR       | TROPAS  |\n");
    printf("-----------------------------------------\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("| %-14s | %-9s | %-7d |\n", 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
        }
    
    printf("-----------------------------------------\n");
    }
    