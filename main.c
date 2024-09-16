#include <stdio.h>

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


//Funções - ============================================

void cadastrarProduto(){
    printf("\nOpção selecionada: [(1)] - | Cadastrar um produto |\n");
}

void listarProdutos(){
    printf("\nOpção selecionada: [(2)] - | Listar os produtos cadastrados |\n");
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

void erro(){}

//Função Menu - ==========================================

void menu(){

    int escolhaMenu;

    printf("---------------------------------\n");
    printf("=================================\n");
    printf("=== | Mercadinho da Esquina | ===\n");
    printf("=================================\n");
    printf("---------------------------------\n");

    printf("\nDigite o que gostaria de fazer:\n\n");

    printf("[1] - Cadastrar um produto\n[2] - Listar os produtos cadastrados\n[3] - Adicionar produtos ao carrinho\n[4] - Visualizar o carrinho\n[5] - Finalizar o pedido\n[6] - Verificar a presença de um produto no carrinho\n[7] - Pegar um produto por código\n[8] - Fechar o programa\n\n>> ");
    scanf("%d", &escolhaMenu);
    
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