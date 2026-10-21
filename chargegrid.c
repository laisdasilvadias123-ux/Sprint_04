#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSOES 50
#define TARIFA_KWH 1.85 // Valor por kWh em R$

// 1. Definição da Struct e Typedef
typedef struct {
    int id;
    char placa[10];
    float kwh;
    float tempoMinutos;
    float valorTotal;
} SessaoRecarga;

// Variáveis Globais de Controle
SessaoRecarga bancoDados[MAX_SESSOES];
int totalSessoes = 0;

// Protótipos das funções
void cadastrarSessao();
void listarSessoes();
void buscarSessao();
void ordenarPorValor();
void exibirRelatorioEstatisticas();

int main() {
    int opcao;

    do {
        printf("     CHARGEGRID INTELLIGENCE - GESTAO EV     \n");
        printf("1. Cadastrar Nova Sessao de Recarga\n");
        printf("2. Listar Todas as Sessoes\n");
        printf("3. Buscar Sessao por ID\n");
        printf("4. Ordenar Sessoes por Valor (Maior -> Menor)\n");
        printf("5. Exibir Relatorio Final e Estatisticas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarSessao();
                break;
            case 2:
                listarSessoes();
                break;
            case 3:
                buscarSessao();
                break;
            case 4:
                ordenarPorValor();
                break;
            case 5:
                exibirRelatorioEstatisticas();
                break;
            case 0:
                printf("\nEncerrando o sistema ChargeGrid Intelligence...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// 2. Função de Cadastro
void cadastrarSessao() {
    if (totalSessoes >= MAX_SESSOES) {
        printf("\n[ERRO] Memoria cheia! Nao e possivel cadastrar mais sessoes.\n");
        return;
    }

    SessaoRecarga s;
    s.id = totalSessoes + 1;

    printf("\n--- CADASTRO DE SESSAO (ID: %d) ---\n", s.id);
    printf("Placa do Veiculo: ");
    scanf("%s", s.placa);
    printf("Energia Consumida (kWh): ");
    scanf("%f", &s.kwh);
    printf("Tempo de Duracao (minutos): ");
    scanf("%f", &s.tempoMinutos);

    // Cálculo da Tarifação em R$
    s.valorTotal = s.kwh * TARIFA_KWH;

    bancoDados[totalSessoes] = s;
    totalSessoes++;

    printf("\n[SUCESSO] Sessao ID %d cadastrada com sucesso! Valor Total: R$ %.2f\n", s.id, s.valorTotal);
}

// 3. Função de Listagem
void listarSessoes() {
    if (totalSessoes == 0) {
        printf("\nNenhuma sessao cadastrada ate o momento.\n");
        return;
    }

    printf("%-5s | %-10s | %-10s | %-12s | %-12s\n", "ID", "PLACA", "KWH", "TEMPO(min)", "VALOR (R$)");
    for (int i = 0; i < totalSessoes; i++) {
        printf("%-5d | %-10s | %-10.2f | %-12.1f | R$ %-10.2f\n", 
               bancoDados[i].id, bancoDados[i].placa, bancoDados[i].kwh, 
               bancoDados[i].tempoMinutos, bancoDados[i].valorTotal);
    }
    printf("----------------------------------------------------------------------\n");
}

// 4. Função de Busca Sequencial O(n)
void buscarSessao() {
    if (totalSessoes == 0) {
        printf("\nNenhuma sessao cadastrada para buscar.\n");
        return;
    }

    int idBusca, encontrado = 0;
    printf("\nDigite o ID da Sessao que deseja buscar: ");
    scanf("%d", &idBusca);

    // Algoritmo de Busca Sequencial
    for (int i = 0; i < totalSessoes; i++) {
        if (bancoDados[i].id == idBusca) {
            printf("\n[SESSAO ENCONTRADA]:\n");
            printf("ID: %d | Placa: %s | Consumo: %.2f kWh | Tempo: %.1f min | Total: R$ %.2f\n",
                   bancoDados[i].id, bancoDados[i].placa, bancoDados[i].kwh, 
                   bancoDados[i].tempoMinutos, bancoDados[i].valorTotal);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\n[ALERTA] Sessao com ID %d nao foi encontrada.\n", idBusca);
    }
}

// 5. Função de Ordenação Bubble Sort O(n^2)
void ordenarPorValor() {
    if (totalSessoes <= 1) {
        printf("\nSessoes insuficientes para ordenar.\n");
        return;
    }

    SessaoRecarga temp;
    // Bubble Sort decrescente por Valor Total
    for (int i = 0; i < totalSessoes - 1; i++) {
        for (int j = 0; j < totalSessoes - i - 1; j++) {
            if (bancoDados[j].valorTotal < bancoDados[j + 1].valorTotal) {
                // Troca (Swap) da struct inteira
                temp = bancoDados[j];
                bancoDados[j] = bancoDados[j + 1];
                bancoDados[j + 1] = temp;
            }
        }
    }

    printf("\n[SUCESSO] Sessoes ordenadas com sucesso do maior para o menor valor!\n");
    listarSessoes();
}

// 6. Relatório e Estatísticas
void exibirRelatorioEstatisticas() {
    if (totalSessoes == 0) {
        printf("\nNenhum dado para gerar relatorio.\n");
        return;
    }

    float totalKwh = 0, faturamentoTotal = 0, totalTempo = 0;

    for (int i = 0; i < totalSessoes; i++) {
        totalKwh += bancoDados[i].kwh;
        faturamentoTotal += bancoDados[i].valorTotal;
        totalTempo += bancoDados[i].tempoMinutos;
    }

    printf("    RELATORIO ESTATISTICO DA ESTACAO EV     \n");
    printf("Total de Sessoes Registradas: %d\n", totalSessoes);
    printf("Energia Total Entregue:       %.2f kWh\n", totalKwh);
    printf("Tempo Total de Operacao:      %.1f minutos\n", totalTempo);
    printf("Faturamento Total Acumulado:  R$ %.2f\n", faturamentoTotal);
    printf("Media de Consumo por Sessao:  %.2f kWh\n", totalKwh / totalSessoes);
}