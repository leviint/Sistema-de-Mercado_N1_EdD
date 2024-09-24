#include <stdio.h> //Biblioteca Input e Output
#include <stdlib.h> //Biblioteca Padrão
#include <string.h> //Biblioteca para funções relacionadas a strings
#include <locale.h> //Biblioteca que suporta configuração regional

//Structs - ============================================

typedef struct{
    
    int codigo;
    char nome[50];
    float preco;

}Produto;

typedef struct{
    
    Produto produto;
    int quantidade;

}ItemCarrinho;

//Variáveis Globais - ==================================

int proximoCodigo = 1;

//Atribuições para a lista de produtos
#define MAX_PRODUTOS 50
Produto* listaProdutos[MAX_PRODUTOS];
int numProdutos = 0;

//Atribuições para o carrinho
#define MAX_CARRINHO 50
ItemCarrinho carrinho[MAX_CARRINHO];
int numCarrinho = 0;
float valorTotalCarrinho = 0;

//Funções Auxiliares - =================================

Produto *criarProduto(char* nome, float preco){ //Cria um novo produto, de certa forma "simula" a orientação a objeto
    Produto *p = calloc(1, sizeof(Produto));
    strcpy(p->nome, nome);
    p->preco = preco;
    p->codigo = proximoCodigo++;

    return p;
}

void infoProduto(Produto *p){ //Exibição das informações do produto, evitar repetição de código
    if (p == NULL) {
        printf("Produto inválido!\n");
        return;
    }

    printf("\nInformações do Produto:\n");
    printf("Código: %d\n", p->codigo);
    printf("Nome: %s\n", p->nome);
    printf("Preço: R$ %.2f\n", p->preco);
}

int produtoExiste(char* nome){ //Verifica se um produto existe percorrendo por todos eles e retornando true ou false
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

    do { //Loop para garantir que o usuário entrou um input corretamente
        printf("Digite o preço do produto:\n>> ");
        verifyPreco = scanf("%f", &preco);

        if (verifyPreco != 1) {
            printf("\nErro: Entrada inválida. Digite um número válido para o preço.\n");

            while (getchar() != '\n'); //Limpa o buffer
        }

    } while (verifyPreco != 1); //Enquanto a variável for diferente de verdadeira
    Produto *p = criarProduto(nome, preco); //Cria um novo produto com os dados que o usuário inseriu

    infoProduto(p);

    if(numProdutos < MAX_PRODUTOS){ //Verifica se o máximo de produtos cadastrados foi atingido
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

    for (int i = 0; i < numProdutos; i++){ //Itera todos os produtos para exibi-los no terminal
        infoProduto(listaProdutos[i]);
    }

}

void comprarProduto(){
    printf("\nOpção selecionada: [(3)] - | Adicionar produtos ao carrinho |\n");

    char nome[50];
    int quantidade;

    getchar();

    printf("Digite o nome do produto que deseja adicionar ao carrinho:\n>> ");
    scanf("%[^\n]", nome);

    printf("Digite a quantidade que deseja adicionar ao carrinho:\n>> ");
    while(scanf("%d", &quantidade) != 1 || quantidade <= 0){ //Verifica se o input está sendo corretamente inserido (sendo um int e maior que 0)
        printf("\nErro: Entrada inválida. Insira um número válido\n");
        while(getchar() != '\n'); //limpa o buffer
        printf("Digite a quantidade que deseja adicionar ao carrinho:\n>> ");
    }

    for(int i = 0; i < numProdutos; i++){ //Itera por todos os produtos registrados para ver se o nome digitado está na lista
        if(strcasecmp(listaProdutos[i]->nome, nome) == 0){ //Compara o nome digitado com o produto da lista
            for (int j = 0; j < numCarrinho; j++) { //Itera por todos os produtos no carrinho
                if (strcmp(carrinho[j].produto.nome, listaProdutos[i]->nome) == 0) { //Compara o nome da lista identificado com o produto no carrinho para verificar se ele já está no carrinho
                    carrinho[j].quantidade += quantidade; //Aumenta a quantidade do produto já contido no carrinho
                    valorTotalCarrinho += listaProdutos[i]->preco * quantidade; //Adiciona o valor do produto e o multiplica pela quantidade inserida
                    printf("\nProduto '%s' agora tem %d unidades no carrinho!\n", listaProdutos[i]->nome, carrinho[j].quantidade);
                    return;
                }
            }


            if(numCarrinho < MAX_CARRINHO){ //Verifica se a quantidade de itens no carrinho é menor que a quantidade máxima de itens
                memcpy(&carrinho[numCarrinho].produto, listaProdutos[i], sizeof(Produto)); //Copia a memória do produto da lista para o carrinho
                carrinho[numCarrinho].quantidade = quantidade; //Define a quantidade de produtos no carrinho
                valorTotalCarrinho += listaProdutos[i]->preco; //Aumenta o valor total a pagar
                numCarrinho++; //Aumenta a quantidade de produto no carrinho
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

    for (int i = 0; i < numCarrinho; i++){ //Exibe as informações do produto, não foi possível o uso da função infoProduto devido ela não conter a quantidade do produto
        printf("\nInformações do Produto:\nCódigo: %d\nNome: %s x%d\nPreço: R$ %.2f\n", carrinho[i].produto.codigo, carrinho[i].produto.nome, carrinho[i].quantidade, carrinho[i].produto.preco * carrinho[i].quantidade);
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

    numCarrinho = 0; //Reseta o número de produtos do carrinho
    valorTotalCarrinho = 0; //Reseta o valor a se pagar do carrinho

    for(int i = 0; i < numCarrinho; i++){ //Limpa os produtos do array
        carrinho[i].quantidade = 0;
    }
}

void temNoCarrinho(){
    char nome[50];
    int encontrado = 0;

    getchar();

    printf("\nOpção selecionada: [(6)] - | Verificar a presença de um produto no carrinho |\n");
    printf("\nDigite o nome de um produto registrado para verificar se ele está no carrinho\n>> ");
    
    scanf("%[^\n]", nome);

    for (int i = 0; i < numCarrinho; i++){ //Itera todos os produtos do carrinho para verificar se o produto está contido nele
        if(strcasecmp(carrinho[i].produto.nome, nome) == 0){ //Compara o nome digitado com os produtos no carrinho
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
    infoProduto(listaProdutos[codigo - 1]); //Pega o produto diretamente pela indexação, -1 devido a indexação começar por 0
}

void removerDoCarrinho(){
    char nome[50];
    int qntRemover, encontrado = 0;

    getchar();

    printf("\nOpção selecionada: [(8)] - | Remover um produto do carrinho |\n");

    if(numCarrinho == 0){
            printf("\nErro: O carrinho está vazio. Não há nada para remover.\n");
            return;
        }

    printf("\nDigite o nome do produto que você gostaria de remover do seu carrinho:\n>> ");
    scanf("%[^\n]", nome);

    for (int i = 0; i < numCarrinho; i++){ //Itera todos os produtos do carrinho para verificar se o produto está contido nele
        if(strcasecmp(carrinho[i].produto.nome, nome) == 0){ //Compara o nome digitado com os produtos no carrinho
            encontrado = 1; //Confirma que o produto foi encontrado
            printf("\nDigite a quantidade que deseja remover (atual no carrinho: %d):\n>> ", carrinho[i].quantidade);
            scanf("%d", &qntRemover);

            if(qntRemover > carrinho[i].quantidade || qntRemover <= 0){ //Se a quantidade a remover for maior que a quantidade de produtos no carrinho OU se a quantidade a remover for menor ou igual a 0
                printf("\nErro: Quantidade inválida.\n");
                return;
            }

            carrinho[i].quantidade -= qntRemover; //Decrementa a quantidade de acordo com o valor de qntRemover
            
            if(carrinho[i].quantidade == 0){
                printf("Produto '%s' removido completamente do carrinho.\n", nome);
            }else{
                printf("\nQuantidade de '%s' removida: %d\nQuantidade restante no carrinho: %d\n", nome, qntRemover, carrinho[i].quantidade);
            }
            break;
        }    
    }

    if(!encontrado){
        printf("\nErro: Produto '%s' não encontrado no carrinho.\n", nome);
    }

}

void deletarProduto(){
    char nome[50];
    int encontrado = 0;

    getchar();

    printf("\nOpção selecionada: [(9)] - | Deletar um produto registrado |\n");

    if(numProdutos == 0){
            printf("\nErro: Não há produtos registrados para serem deletados.\n");
            return;
        }

    printf("\nDigite o nome do produto que você gostaria de remover do seu carrinho:\n>> ");
    scanf("%[^\n]", nome);

    for (int i = 0; i < numProdutos; i++){ //Itera todos os produtos registrados para verificar se o produto está contido nele
        if(strcasecmp(listaProdutos[i]->nome, nome) == 0){ //Compara o nome digitado com os produtos registrados
            encontrado = 1;

            for(int j = i; j < numProdutos - 1; j++){ //Reajusta o array para compensar a remoção do produto do registro
                listaProdutos[j] = listaProdutos[j + 1];
            }
            numProdutos--; //Decrementa o número de produtos
            listaProdutos[i]->codigo--; //Decrementa o código para que o espaço atribuído ao código do produto removido seja aberto novamente

            printf("\nProduto '%s' deletado do registro.\n", nome);

            for(int k = 0; k < numCarrinho; k++){
                if(strcasecmp(carrinho[k].produto.nome, nome) == 0){ //Verifica se o produto deletado está no carrinho
                    for (int l = k; l < numCarrinho - 1; l++) { //Reajusta os itens no carrinho
                        carrinho[l] = carrinho[l + 1]; // Move os itens no carrinho
                    }
                    numCarrinho--; // Diminui o contador do carrinho
                    break;
                    printf("\nProduto '%s' removido do carrinho devido a remoção do seu registro.\n", nome);
                }
            }
            break;
        }    
    }
}

void fecharPrograma(){
    printf("\nFinalizando programa...\nAté a próxima!");
}

void erro(){
    printf("\nOpção inválida, tente novamente.\n");
}

//Função Menu - ==========================================

void menu(){

    Produto produtos[50]; //Array estático, armazena até 50 produtos no total
    ItemCarrinho carrinho[50]; //Array estático, armazena até 50 produtos no carrinho

    int escolhaMenu;

    //Plaquinha bonitinha do mercado
    printf("---------------------------------\n");
    printf("=================================\n");
    printf("=== | Mercadinho da Esquina | ===\n");
    printf("=================================\n");
    printf("---------------------------------\n");
    
    do{ //Loop do menu enquanto o input for diferente de 8

        printf("\nDigite o que gostaria de fazer:\n\n");

        printf("[1] - Cadastrar um produto\n[2] - Listar os produtos cadastrados\n[3] - Adicionar produtos ao carrinho\n[4] - Visualizar o carrinho\n[5] - Finalizar o pedido\n[6] - Verificar a presença de um produto no carrinho\n[7] - Pegar um produto por código\n[8] - Remover um produto do carrinho\n[9] - Deletar um produto registrado\n[0] - Fechar o programa\n\n>> ");
         if(scanf("%d", &escolhaMenu) != 1){ //Garante que o usuário possa inserir um input correto
            printf("\nDigite um número válido.\n");

            while(getchar() != '\n'); //Limpa o buffer pela quadragésima vez
            continue;
        }

        switch(escolhaMenu){ //Switch case pro menu, cada caso com apenas o chamado de uma função
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
                removerDoCarrinho();
                break;
            case 9:
                deletarProduto();
                break;
            case 0:
                fecharPrograma();
                break;
            default:
                erro();
                break;
        }
    }while(escolhaMenu != 0);
}

//Main - ===============================================

int main(){
    setlocale(LC_ALL, "pt_BR.UTF8"); //Define a codificação do terminal para mostrar caracteres especiais
    
    //Arte ASCII da UCB!
    printf("  _    _       _                    _     _           _         _____      _    __  _ _                 _        ____                ___ _       \n");
    printf(" | |  | |     (_)                  (_)   | |         | |       / ____|    | |  /_/ | (_)               | |      |  _ \\              /_/ (_)      \n");
    printf(" | |  | |_ __  ___   _____ _ __ ___ _  __| | __ _  __| | ___  | |     __ _| |_ ___ | |_  ___ __ _    __| | ___  | |_) |_ __ __ _ ___ _| |_  __ _ \n");
    printf(" | |  | | '_ \\| \\ \\ / / _ \\ '__/ __| |/ _` |/ _` |/ _` |/ _ \\ | |    / _` | __/ _ \\| | |/ __/ _` |  / _` |/ _ \\ |  _ <| '__/ _` / __| | | |/ _` |\n");
    printf(" | |__| | | | | |\\ V /  __/ |  \\__ \\ | (_| | (_| | (_| |  __/ | |___| (_| | || (_) | | | (_| (_| | | (_| |  __/ | |_) | | | (_| \\__ \\ | | | (_| |\n");
    printf("  \\____/|_| |_|_| \\_/ \\___|_|  |___/_|\\__,_|\\__,_|\\__,_|\\___|  \\_____\\__,_|\\__\\___/|_|_|\\___\\__,_|  \\__,_|\\___| |____/|_|  \\__,_|___/_|_|_|\\__,_|\n\n");
  
    menu(); //Chamado mágico que faz tudo funcionar

    return 0;
}

//Arthur Lemos Bendini - UC24101142 - ================
