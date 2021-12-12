#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* máximo de contas e tamanho de nomes*/
#define NUM_CONTAS 2
#define MAX_NOME 256

/* protótipos das funções*/
bool menu(void);
void cadastrar_cliente(void);
int verifica_conta(int conta);
void mostrar_saldo(void);
void deposito(void);
void saque(void);
void listar_contas();

/* definição de tipos*/
struct Cliente {
    char nome[MAX_NOME];
    int cpf;
};

struct Conta {
    int numero_da_conta;
    struct Cliente cliente;
    float saldo;
};

/* reserva memória para contas*/
struct Conta registro_contas[NUM_CONTAS];

/*função principal*/
int main() {

    /*inicializa as contas*/
    int i;
    for (i = 0; i < NUM_CONTAS; i++) {
        registro_contas[i].cliente.cpf = 0;
    }

    /* acessa o menu*/
    menu();

    /* encerra a execução*/
    system("pause");
    return 0;
}

bool menu(void) {
    bool continua = true;
    while (continua){


        printf("\nESCOLHA A OPERACAO:\n");
        printf("1 - Consultar saldo\n");
        printf("2 - Fazer saque\n");
        printf("3 - Fazer deposito\n");
        printf("4 - Cadastrar nova conta\n");
        printf("5 - Listar contas cadastradas\n");
        printf("6 - Encerrar\n");


        int operacao = 0;
        scanf("%d", &operacao);
        switch (operacao) {
            case 1:
                mostrar_saldo();
                break;
            case 2:
                saque();
                break;
            case 3:
                deposito();
                break;
            case 4:
                cadastrar_cliente();
                break;
            case 5:
                listar_contas();
                break;
            case 6:
                continua = false;
                break;
            default:
                printf("\nOperacao nao encontrada.\n");
                break;
        }
    }
}

void cadastrar_cliente(void) {

    printf("\n### CADASTRO ###\n");

    /* localiza próximo espaço de conta vazio*/
    int conta = NUM_CONTAS + 1;
    int i;
    for (i = 0; i < NUM_CONTAS; i++) {
        if (registro_contas[i].cliente.cpf == 0) {
            conta = i;
            break;
        }
    }
    if (conta > NUM_CONTAS) {
        printf("\nNao ha mais espaco para cadastrar novas contas.\n");
    }
    else {
        /* captura os dados da conta*/
        fflush(stdin);
        printf("\nNome.: ");
        scanf("%s",registro_contas[conta].cliente.nome);

        printf("\nCPF.: ");
        scanf("%d",&registro_contas[conta].cliente.cpf);

        printf("\nNumero da conta do cliente.: ");
        scanf("%d",&registro_contas[conta].numero_da_conta);

        registro_contas[conta].saldo = 0.00;
        printf("\nCliente cadastrado com sucesso.\n");
    }
}

int verifica_conta(int conta) {
    int i;
    for (i = 0; i < NUM_CONTAS; i++){
        if (registro_contas[i].numero_da_conta == conta){
            return i;
        }
    }
    return NUM_CONTAS;
}

void mostrar_saldo(void) {
    printf("\n### SALDO ###\n");

    int conta = 0;
    printf("\nInsira o numero da conta: ");
    scanf("%d", &conta);

    int indice_conta = verifica_conta(conta);
    if (indice_conta < NUM_CONTAS){
        printf("\nConta: %d, Nome: %s, CPF: %d\n", registro_contas[indice_conta].numero_da_conta, registro_contas[indice_conta].cliente.nome, registro_contas[indice_conta].cliente.cpf);
        printf("Saldo.....: %.2f\n", registro_contas[indice_conta].saldo);
    }
    else {
        printf("\nConta nao encontrada.\n");
    }
}

void deposito(void) {

    printf("\n### DEPOSITO ###\n");

    int conta = 0;
    printf("\nInsira o numero da conta: ");
    scanf("%d", &conta);

    int indice_conta = verifica_conta(conta);

    if (indice_conta < NUM_CONTAS){
        float dep = 0;
        printf("\nInsira o valor do deposito: ");
        while (dep <= 0){
            scanf("%f", &dep);
            if (dep <= 0){
                printf("\nFavor inserir um valor maior que 0: ");
            }
            else {
                registro_contas[indice_conta].saldo += dep;
                printf("\nDeposito realizado.\n");
            }
        }
    }
    else {
        printf("\nConta nao encontrada.\n");
    }
}

void saque(void) {

    printf("\n### SAQUE ###\n");

    int conta = 0;
    printf("\nInsira o numero da conta: ");
    scanf("%d", &conta);

    int indice_conta = verifica_conta(conta);

    if (indice_conta < NUM_CONTAS){
        if (registro_contas[indice_conta].saldo > 0){
            printf("\nSaldo disponivel: %.2f\n", registro_contas[indice_conta].saldo);
            printf("Insira o valor do saque: ");
            float saque = 0;
            while (saque > registro_contas[indice_conta].numero_da_conta || saque <= 0){
                scanf("%f", &saque);
                if (saque > registro_contas[indice_conta].saldo){
                    printf("\nO saldo da conta nao e suficiente. Insira um valor menor: ");
                }
                else if (saque <= 0){
                    printf("\nO saque deve ser superior a 0. Insira um valor maior: ");
                }
                else {
                    registro_contas[indice_conta].saldo -= saque;
                    printf("\nSaque realizado. Saldo atual: %.2f\n", registro_contas[indice_conta].saldo);
                    break;
                }
            }
        }
        else {
            printf("\nA conta nao tem saldo.\n");
        }
    }
    else {
        printf("\nConta nao encontrada.\n");
    }
}

void listar_contas() {

    printf("\n### Contas cadastradas ###\n");
    int i;
    for (i = 0; i < NUM_CONTAS; i++) {
        if (i == 0 && registro_contas[i].cliente.cpf == 0) {
            printf("\nNenhuma conta cadastrada.\n");
            break;
        }
        if (registro_contas[i].cliente.cpf != 0) {
            printf("\nConta: %d, Nome: %s, CPF: %d\n", registro_contas[i].numero_da_conta, registro_contas[i].cliente.nome, registro_contas[i].cliente.cpf);
        }
    }
}
