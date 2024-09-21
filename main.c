#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Structs - ============================================

typedef struct{
    
    int codigo;
    char nome[50];
    float preco;

}Produto;

typedef struct{
    
    Produto produto;
    int quantidade;

}Carrinho;

//Variáveis Globais - ==================================

int proximoCodigo = 1;
#define MAX_PRODUTOS 50
Produto* listaProdutos[MAX_PRODUTOS];
int numProdutos = 0;

//Funções Auxiliares - =================================

Produto *criarProduto(char* nome, float preco){
    Produto *p = calloc(1, sizeof(Produto));
    strcpy(p->nome, nome);
    p->preco = preco;
    p->codigo = proximoCodigo++;

    return p;
}

void infoProduto(Produto *p){
    if (p == NULL) {
        printf("Produto inválido!\n");
        return;
    }

    printf("\nInformações do Produto:\n");
    printf("Código: %d\n", p->codigo);
    printf("Nome: %s\n", p->nome);
    printf("Preço: R$ %.2f\n", p->preco);
}

//Funções - ============================================

void cadastrarProduto(){

    char nome[50];
    float preco;

    printf("\nOpção selecionada: [(1)] - | Cadastrar um produto |\n");


    printf("Digite o nome do produto:\n>> ");
    scanf("%s", &nome);

    printf("Digite o preço do produto:\n>> ");
    scanf("%f", &preco);

    Produto *p = criarProduto(nome, preco);

    infoProduto(p);

    if(numProdutos < MAX_PRODUTOS){
        listaProdutos[numProdutos++] = p;
        printf("\nProduto cadastrado.\n");
    }else{
        printf("\nErro: Numero máximo de produtos cadastrados atingido.\n");
    }

}

void listarProdutos(){
    printf("\nOpção selecionada: [(2)] - | Listar os produtos cadastrados |\n");

    if (numProdutos == 0){
        printf("\nNenhum produto foi cadastrado.\n");
        return;
    }

    for (int i = 0; i < numProdutos; i++){
        infoProduto(listaProdutos[i]);
    }

}

void comprarProduto(){
    printf("\nOpção selecionada: [(3)] - | Adicionar produtos ao carrinho |\n");
}

void visualizarCarrinho(){
    printf("\nOpção selecionada: [(4)] - | Visualizar o carrinho |\n");
}

void fecharPedido(){
    printf("\nOpção selecionada: [(5)] - | Finalizar o pedido |\n");
}

void temNoCarrinho(){
    printf("\nOpção selecionada: [(6)] - | Verificar a presença de um produto no carrinho |\n");
}

void pegarProdutoPorCodigo(){
    printf("\nOpção selecionada: [(7)] - | Pegar um produto por código |\n");
}

void fecharPrograma(){
    printf("\nFinalizando programa...\nAté a próxima!");
}

void erro(){
    printf("\nOpção inválida, tente novamente.\n");
}

//Função Menu - ==========================================

void menu(){
    setlocale(LC_ALL, "pt_BR.UTF8");

    Produto produtos[50]; //Array estático, armazena até 50 produtos no total
    Carrinho carrinho[50]; //Array estático, armazena até 50 produtos no carrinho

    int escolhaMenu;

    int quantidadeProdutos = 0;

    printf("---------------------------------\n");
    printf("=================================\n");
    printf("=== | Mercadinho da Esquina | ===\n");
    printf("=================================\n");
    printf("---------------------------------\n");
    
    do{

        printf("\nDigite o que gostaria de fazer:\n\n");

        printf("[1] - Cadastrar um produto\n[2] - Listar os produtos cadastrados\n[3] - Adicionar produtos ao carrinho\n[4] - Visualizar o carrinho\n[5] - Finalizar o pedido\n[6] - Verificar a presença de um produto no carrinho\n[7] - Pegar um produto por código\n[8] - Fechar o programa\n\n>> ");
        scanf("%d", &escolhaMenu);

        switch(escolhaMenu){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos(produtos, quantidadeProdutos);
                break;
            case 3:
                comprarProduto();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                fecharPedido();
                break;
            case 6:
                temNoCarrinho();
                break;
            case 7:
                pegarProdutoPorCodigo();
                break;
            case 8:
                fecharPrograma();
                break;
            default:
                erro();
                break;
        }
    }while(escolhaMenu != 8);
}

//Main - ===============================================

int main(){
    
    Produto produto;

    printf("  _    _       _                    _     _           _         _____      _    __  _ _                 _        ____                ___ _       \n");
    printf(" | |  | |     (_)                  (_)   | |         | |       / ____|    | |  /_/ | (_)               | |      |  _ \\              /_/ (_)      \n");
    printf(" | |  | |_ __  ___   _____ _ __ ___ _  __| | __ _  __| | ___  | |     __ _| |_ ___ | |_  ___ __ _    __| | ___  | |_) |_ __ __ _ ___ _| |_  __ _ \n");
    printf(" | |  | | '_ \\| \\ \\ / / _ \\ '__/ __| |/ _` |/ _` |/ _` |/ _ \\ | |    / _` | __/ _ \\| | |/ __/ _` |  / _` |/ _ \\ |  _ <| '__/ _` / __| | | |/ _` |\n");
    printf(" | |__| | | | | |\\ V /  __/ |  \\__ \\ | (_| | (_| | (_| |  __/ | |___| (_| | || (_) | | | (_| (_| | | (_| |  __/ | |_) | | | (_| \\__ \\ | | | (_| |\n");
    printf("  \\____/|_| |_|_| \\_/ \\___|_|  |___/_|\\__,_|\\__,_|\\__,_|\\___|  \\_____\\__,_|\\__\\___/|_|_|\\___\\__,_|  \\__,_|\\___| |____/|_|  \\__,_|___/_|_|_|\\__,_|\n\n");
  
    menu();

    return 0;
}

//Arthur Lemos Bendini - UC24101142 - ================