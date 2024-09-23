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

int proximoCodigo = 1; //Mostra qual deve ser o próximo código do produto registrado

//Atribuições para a lista de produtos
#define MAX_PRODUTOS 50
Produto* listaProdutos[MAX_PRODUTOS];
int numProdutos = 0;

//Atribuições para o carrinho
#define MAX_CARRINHO 50
Produto* carrinho[MAX_CARRINHO];
int numCarrinho = 0;
float valorTotalCarrinho = 0;

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

int produtoExiste(char* nome){
    for(int i = 0; i < numProdutos; i++){
        if(strcasecmp(listaProdutos[i]->nome, nome) == 0){
            return 1;
        }
    }
    return 0;
}

//Funções - ============================================

void cadastrarProduto(){

    char nome[50];
    float preco;
    int verifyPreco;

    printf("\nOpção selecionada: [(1)] - | Cadastrar um produto |\n");

    getchar();

    printf("Digite o nome do produto:\n>> ");
    scanf("%[^\n]", nome);

    if(produtoExiste(nome)){
        printf("\nErro: Produto com o nome '%s' já está cadastrado.\n", nome);
        return;
    }

    do {
        printf("Digite o preço do produto:\n>> ");
        verifyPreco = scanf("%f", &preco);

        if (verifyPreco != 1) {
            printf("\nErro: Entrada inválida. Digite um número válido para o preço.\n");

            // Limpa o buffer de entrada
            while (getchar() != '\n');  // Limpa até encontrar uma nova linha
        }

    } while (verifyPreco != 1);  // Repete até a entrada ser válida
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

    char nome[50];

    getchar();

    printf("Digite o nome do produto que deseja adicionar ao carrinho:\n>> ");
    scanf("%[^\n]", nome);

    for(int i = 0; i < numProdutos; i++){
        if(strcasecmp(listaProdutos[i]->nome, nome) == 0){
            if(numCarrinho < MAX_CARRINHO){
                carrinho[numCarrinho++] = listaProdutos[i];
                valorTotalCarrinho += listaProdutos[i]->preco;
                printf("\nProduto '%s' adicionado ao carrinho!\n", listaProdutos[i]->nome);
            }else{
                printf("\nErro: Carrinho cheio! Não é possível adicionar mais produtos.\n");
            }
            return;
        }
    }
    printf("\nErro: Produto com nome '%s' não encontrado.\n", nome);
}

void visualizarCarrinho(){
    printf("\nOpção selecionada: [(4)] - | Visualizar o carrinho |\n");

    if (numCarrinho == 0){
        printf("\nNenhum produto foi adicionado ao carrinho.\n");
        return;
    }

    for (int i = 0; i < numCarrinho; i++){
        infoProduto(carrinho[i]);
    }
}

void fecharPedido(){
    printf("\nOpção selecionada: [(5)] - | Finalizar o pedido |\n");

    if(numCarrinho == 0){
        printf("\nO carrinho está vazio. Não há nada para finalizar.\n");
        return;
    }

    printf("\nValor a pagar: R$ %.2f\n", valorTotalCarrinho);
    printf("\nObrigado pela preferência. Até a próxima!\n");

    numCarrinho = 0;
    valorTotalCarrinho = 0;
}

void temNoCarrinho(){
    char nome[50];
    int encontrado = 0;

    getchar();

    printf("\nOpção selecionada: [(6)] - | Verificar a presença de um produto no carrinho |\n");
    printf("\nDigite o nome de um produto registrado para verificar se ele está no carrinho\n>> ");
    
    scanf("%[^\n]", nome);

    for (int i = 0; i < numCarrinho; i++){
        if(strcasecmp(carrinho[i]->nome, nome) == 0){
            printf("\nO produto '%s' está no carrinho!\n", nome);
            encontrado = 1;
            break;
        }    
    }

    if(!encontrado){
        printf("\nO produto '%s' não está no carrinho.\n", nome);
    }
}


void pegarProdutoPorCodigo(){
    int codigo;
    printf("\nOpção selecionada: [(7)] - | Pegar um produto por código |\n");

    printf("\nDigite o código do produto que deseja ver:\n>> ");
    scanf("%d", &codigo);

    printf("\nProduto com código %d:\n", codigo);
    infoProduto(listaProdutos[codigo - 1]);

    
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
         if(scanf("%d", &escolhaMenu) != 1){
            printf("\nDigite um número válido.\n");

            while(getchar() != '\n');
            continue;
        }

        switch(escolhaMenu){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
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

//Cadastro e adição de produtos ao carrinho não levam letras maiúsculas em consideração
//Detectar inputs incorretos do usuário e fazer ele repetir o input até acertar
