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

//funcao de busca
/*

int buscar(no* raiz){
    """
    lê uma chave x e realiza sua busca na árvore B, 
    informando se ela foi encontrada e,
    quando aplicável, a posição onde se encontra.
    
    Entrada:

    Saída:

    Compara a chave x com a(s) chave(s) do no
    raiz. Se a chave nao estiver no raiz, a busca
    deve prosseguir em um certo filho dessa
    página.
    – Escolhe-se qual filho explorar de forma
    parecida com a pesquisa realizada na
    árvore binária de pesquisa

    implementacao do livro:

    procedimento buscaB(x, pt, f, g)
        p := ptraiz; pt := λ; f := 0
        enquanto p ≠ λ faça
        i := g := 1; pt := p
        enquanto i≤ m faça
            se x > p ↑. s[i] então i := g := i + 1
            senão se x = p ↑. s[i] então
                p := λ % chave encontrada
                f := 1
            senão p := p ↑. pont[i – 1] % mudança de página
            i := m + 2
        se i = m + 1 então p := p ↑. pont[m]
        
    """

};


arvoreB *criaArvore(int ordem) {

    arvoreB *arvore = malloc(sizeof(arvoreB));

    arvore->ordem = ordem;

    arvore->raiz = criaNo(ordem, 1);

    return arvore;
}

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

int main() {
    
    int opcao = 0, ordem_arvore;

    printf("Qual será a ordem da árvore?\n" );
    scanf("%d", &ordem_arvore);
    while (ordem_arvore < 2){
        printf("A ordem da árvore deve ser maior ou igual a 2. Insira novamente:\n");
        scanf("%d", &ordem_arvore);
    }

    arvoreB *arvore = criaArvore(ordem_arvore);

    loadFile(arvore->raiz, ordem_arvore);

    printf("\nPokemons carregados:\n");

    for (int i = 0; i < arvore->raiz->numChaves; i++) {
        printf("%s\n", arvore->raiz->chaves[i]);
    }
/*
    """
    Cria a árvore aqui fora, tem que pegar o arquivo "pokemon_names.txt" e povoar a arvore

    (i) a raiz é uma folha ou possui no mínimo dois filhos; --> se tiver menos, na hora de inserir, barrar a ação e pedir outro dado
    (ii) cada nó interno (exceto a raiz) possui no mínimo d + 1 filhos;
    (iii) cada nó possui no máximo 2d + 1 filhos;
    (iv) todas as folhas estão no mesmo nível.

    
    [   Cada nó de uma árvore B, também chamado de página, armazena um conjunto ordenado
        de chaves e ponteiros para seus filhos.
        Se um nó possui k filhos, então ele contém k − 1 chaves.
        Consequentemente, cada nó interno possui entre d e 2d chaves.    ]

    [link do slide para implementação:]
    https://docente.ifrn.edu.br/robinsonalves/disciplinas/estruturas-de-dados-nao-lineares/ArvBrl.pdf
        
    """
*/    
    while (opcao != 9){

        printf("// ----- // ----- // ÁRVORE B // ----- // ----- //\n");
        printf("[1] - Buscar\n");
        printf("[2] - Inserir\n");
        printf("[9] - Finalizar\n");

        scanf("%d", &opcao);
        
        if (opcao == 1){
            printf("Digite o nome do pokémon que deseja buscar: \n");
            

        }

        else if (opcao == 2){


        }

        else if (opcao == 9){
            break;

        }

        else {
            printf("\nResposta inválida!\nInsira novamente: ");
        }

    }

    printf("\n// ----- Programa finalizado ! ----- //\n");

    return 0;
}
