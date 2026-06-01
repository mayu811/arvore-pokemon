/*Integrantes do Grupo
- João VItor Costa Braga - RGA: 2024.1906.061-7
- Louise Mayumi Takigawa Pereia - RGA: 2024.1906.028-5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvoreB {
  int ordem;
  struct no *raiz;
} arvoreB;

typedef struct no {

    int numChaves;
    int folha;
    char **chaves;
    struct no **filhos;

} no;

typedef struct resultadoBusca{
    no* pt;
    int g;
    int f;
} resultadoBusca;

no *criaNo(int ordem, int folha) {

    no *novoNo = malloc(sizeof(no));

    novoNo->numChaves = 0;
    novoNo->folha = folha;

    novoNo->chaves = malloc((2 * ordem) * sizeof(char*));
    for (int i = 0; i < 2 * ordem; i++) {
        novoNo->chaves[i] = malloc(100 * sizeof(char)); // alocando espaço para as chaves
    }

    novoNo->filhos = malloc((2 * ordem + 1) * sizeof(no*));
    for (int i = 0; i < 2 * ordem + 1; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}


arvoreB *criaArvore(int ordem) {

    arvoreB *arvore = malloc(sizeof(arvoreB));

    arvore->ordem = ordem;
    arvore->raiz = criaNo(ordem, 1);

    return arvore;
}


/* ============================================================
 *  BUSCA
 *  
 * ============================================================ */

resultadoBusca buscarB(no *p, const char *chave)
{
    resultadoBusca resultado;
    int i;
    int g;

    /* arvore vazia */
    if (p == NULL) {
        resultado.pt = NULL;
        resultado.f  = 0;
        resultado.g  = 0;
        return resultado;
    }

    /* percorre as paginas descendo pela arvore */
    while (p != NULL) {

        /* varre as chaves do no atual, atualizando g (indice do filho a explorar) */
        i = 0;
        g = 0;
        while (i < p->numChaves) {
            if (strcmp(chave, p->chaves[i]) > 0) {
                /* chave procurada e maior: avanca para a direita */
                i++;
                g++;
            } else if (strcmp(chave, p->chaves[i]) == 0) {
                /* chave encontrada neste no */
                resultado.pt = p;
                resultado.f  = 1;
                resultado.g  = i;
                return resultado;
            } else {
                /* chave procurada e menor: para de varrer, desce pelo filho g */
                break;
            }
        }

        /* chegou a uma folha sem encontrar: nao existe na arvore */
        if (p->folha) {
            resultado.pt = p;
            resultado.f  = 0;
            resultado.g  = g;
            return resultado;
        }

        /* desce para o filho indicado por g */
        p = p->filhos[g];
    }

    /* seguranca: nunca deve chegar aqui */
    resultado.pt = NULL;
    resultado.f  = 0;
    resultado.g  = 0;
    return resultado;
}



/* ============================================================
 *  INSERIR
 *  
 * ============================================================ */
// funcao inserir em pagina nao cheia
no* inserir(no *raiz, char *chave, int ordem) {
    // Função de inserção na árvore B
    // Implementação a ser feita
    if (raiz->numChaves >= 2 * ordem) {
        printf("Pagina cheia! (teste)\n");
        return;
    }

    strcpy(raiz->chaves[raiz->numChaves], chave);

    raiz->numChaves++;
}

// função inserir para pagina cheia
/*
no* inserir(no* raiz){
    """
    lê uma chave x e realiza sua inserção na árvore B.

    Entrada:

    Saída:
    """

};
*/




/* ============================================================
 *  CISÃO DE PAGINA (DIVISAO OU SPLIT)
 *  
 * ============================================================ */
// funcao de cisao/split de paginas
void cisaoPagina(no *pai, int indice, no *filhoCheio, int ordem) {
    //Cria uma nova página
    no *novaPagina = criaNo(ordem, filhoCheio->folha);
    
    //Define o ponto de divisão
    int meio = ordem;
    
    //Move metade superior das chaves para a nova página
    for (int i = meio + 1; i < filhoCheio->numChaves; i++) {
        strcpy(novaPagina->chaves[i - (meio + 1)], filhoCheio->chaves[i]);
        novaPagina->numChaves++;
    }
    
    //Se não for folha, move também os filhos correspondentes
    if (!filhoCheio->folha) {
        for (int i = meio + 1; i <= filhoCheio->numChaves; i++) {
            novaPagina->filhos[i - (meio + 1)] = filhoCheio->filhos[i];
        }
    }

    //Salva a chave que vai subir para o pai
    char chaveSobe[100];
    strcpy(chaveSobe, filhoCheio->chaves[meio]);
    
    //Atualiza o número de chaves do filho cheio
    filhoCheio->numChaves = meio - 1;
    
    //Abre espaço no pai para inserir a nova chave e o novo filho
    //Desloca as chaves do pai para a direita
    for (int i = pai->numChaves; i > indice; i--) {
        strcpy(pai->chaves[i], pai->chaves[i-1]);
    }

    // Desloca os filhos do pai para a direita
    for (int i = pai->numChaves + 1; i > indice + 1; i--) {
        pai->filhos[i] = pai->filhos[i-1];
    }
    
    //Insere a chave que subiu no pai
    strcpy(pai->chaves[indice], chaveSobe);
    pai->numChaves++;
    
    //Insere a nova página como filho direito da chave que subiu
    pai->filhos[indice + 1] = novaPagina;
}



/* ============================================================
 *  INSERCAO A PARTIR DO ARQUIVO .txt
 *  
 * ============================================================ */
/*Função para carregar os nomes dos pokémons a partir de um arquivo*/
void loadFile(no *raiz, int ordem) {

    FILE *file = fopen("pokemon_names.txt", "r");

    if (!file) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    char pokemon[100];

    while (fgets(pokemon, sizeof(pokemon), file)) {
        pokemon[strcspn(pokemon, "\n")] = 0;
        inserir(raiz, pokemon, ordem);
    }

    fclose(file);
}



/* ============================================================
 *  MAIN
 *  
 * ============================================================ */
int main() {
    
    int opcao = 0, ordem_arvore;

    // Pega a ordem da arvore
    printf("Qual será a ordem da árvore?\n" );
    scanf("%d", &ordem_arvore);

    while (ordem_arvore < 2){
        printf("A ordem da árvore deve ser maior ou igual a 2. Insira novamente:\n");
        scanf("%d", &ordem_arvore);
    }

    // Criação da árvore
    arvoreB *arvore = criaArvore(ordem_arvore);
    loadFile(arvore->raiz, ordem_arvore);
    printf("\nPokemons carregados:\n");

    // Imprime os pokemons inseridos:
    for (int i = 0; i < arvore->raiz->numChaves; i++) {
        printf("%s\n", arvore->raiz->chaves[i]);
    }

    while (opcao != 9){

        printf("// ----- // ----- // ÁRVORE B // ----- // ----- //\n");
        printf("[1] - Buscar\n");
        printf("[2] - Inserir\n");
        printf("[9] - Finalizar\n");

        scanf("%d", &opcao);
        
        // [1] - Buscar
        if (opcao == 1){
            printf("Dica: Atente-se a pontuacoes no nome do pokemon, alem do nome comecar com letra maiuscula!\n");
            printf("Digite o nome do pokémon que deseja buscar: \n");
            
            char nomeProcurar[100];
            scanf("%d", nomeProcurar);
            //buscarB();
        }

        // [2] - Inserir
        else if (opcao == 2){
            char nomePokemon[100];
            scanf("%d, &nomePokemon");
            inserir(arvore, nomePokemon, ordem_arvore);
        }

        // [9] - Encerra execução  
        else if (opcao == 9){
            printf("\n// ----- Programa finalizado ! ----- //\n");
            break;
        }

        else {
            printf("\nResposta inválida!\nInsira novamente: ");
        }
    }
    return 0;
}
