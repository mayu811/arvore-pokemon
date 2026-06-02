/*Integrantes do Grupo
- João VItor Costa Braga - RGA: 2024.1906.061-7
- Louise Mayumi Takigawa Pereia - RGA: 2024.1906.028-5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    /*
    Entrada:
        ordem - ordem da arvore B (número mínimo de chaves por nó)
        folha - flag indicando se o nó é folha (1) ou não (0)
    Saída:
        ponteiro para o nó criado
    Descrição:
        Cria um novo nó para a arvore B. Aloca memória para o nó, inicializa o número de chaves como 0, 
        define se é folha ou não, e aloca os arrays de chaves e filhos com os tamanhos máximos permitidos.
    */
    no *novoNo = malloc(sizeof(no));
    novoNo->numChaves = 0;
    novoNo->folha = folha;

    // Aloca array de chaves (máximo 2*ordem-1 chaves)
    novoNo->chaves = malloc((2 * ordem - 1) * sizeof(char*));
    for (int i = 0; i < 2 * ordem - 1; i++) {
        novoNo->chaves[i] = malloc(100 * sizeof(char));
        novoNo->chaves[i][0] = '\0';
    }

    // Aloca array de filhos (máximo 2*ordem filhos)
    novoNo->filhos = malloc((2 * ordem) * sizeof(no*));
    for (int i = 0; i < 2 * ordem; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}


arvoreB *criaArvore(int ordem) {
    /*
    Entrada:
        ordem - ordem da arvore B (número mínimo de chaves por nó)
    Saída:
        ponteiro para a arvore B criada
    Descrição:
        Cria uma nova arvore B com a ordem especificada. Inicializa a raiz como um nó folha vazio.
    */

    arvoreB *arvore = malloc(sizeof(arvoreB));

    arvore->ordem = ordem;
    arvore->raiz = criaNo(ordem, 1);

    return arvore;
}


/* ============================================================
 *  BUSCA
 * ============================================================ */

resultadoBusca buscarB(no *p, const char *chave){
    /*
    Entrada:
        p - ponteiro para o nó onde a busca deve começar (geralmente a raiz)
        chave - chave a ser buscada
    Saída:
        resultadoBusca - estrutura contendo:
            pt - ponteiro para o nó onde a chave foi encontrada ou onde deveria ser inserida
            f  - flag indicando se a chave foi encontrada (1) ou não (0)
            g  - índice da chave dentro do nó (se encontrada) ou índice do filho onde descer (se não encontrada)
    Descrição:
        Realiza a busca pela chave na arvore B. Percorre os nós comparando as chaves. 
        Se encontrar a chave, retorna o nó e o índice. Se não encontrar, retorna o nó onde a
        chave deveria ser inserida e o índice do filho para descer.    
    
    */
    resultadoBusca resultado;
    int i;
    int g;

    // arvore vazia 
    if (p == NULL) {
        resultado.pt = NULL;
        resultado.f  = 0;
        resultado.g  = 0;
        return resultado;
    }

    // percorre as paginas descendo pela arvore
    while (p != NULL) {

        // varre as chaves do no atual, atualizando g (indice do filho a explorar)
        i = 0;
        g = 0;
        while (i < p->numChaves) {
            if (strcmp(chave, p->chaves[i]) > 0) {
                // chave procurada e maior: avanca para a direita
                i++;
                g++;
            } else if (strcmp(chave, p->chaves[i]) == 0) {
                // chave encontrada neste no
                resultado.pt = p;
                resultado.f  = 1;
                resultado.g  = i;
                return resultado;
            } else {
                // chave procurada e menor: para de varrer, desce pelo filho g
                break;
            }
        }

        // chegou a uma folha sem encontrar: nao existe na arvore
        if (p->folha) {
            resultado.pt = p;
            resultado.f  = 0;
            resultado.g  = g;
            return resultado;
        }

        // desce para o filho indicado por g
        p = p->filhos[g];
    }

    // seguranca: nunca deve chegar aqui
    resultado.pt = NULL;
    resultado.f  = 0;
    resultado.g  = 0;
    return resultado;
}


/* ============================================================
 *  CISÃO DE PAGINA (DIVISAO OU SPLIT)
 * ============================================================ */
void cisaoPagina(no *pai, int posicao, no *filho, int ordem) {
    /*
    Entrada:
        pai - nó pai onde a divisão ocorrerá
        posicao - índice do filho que será dividido
        filho - nó que será dividido (filho de pai->filhos[posicao])
        ordem - ordem da arvore B
    Saída:
        nenhuma (modifica a arvore diretamente)
    Descrição:
        Divide o nó "filho" em dois nós, movendo a chave do meio para o "pai". 
        O "filho" original mantém as chaves da metade esquerda, e um novo nó é 
        criado para as chaves da metade direita. O pai é atualizado para incluir
         a nova chave e o novo filho.
    
    */
    int meio = ordem - 1;
    no *novoNo = criaNo(ordem, filho->folha);
    
    // Configura o novo no
    novoNo->numChaves = ordem - 1; 
    
    // Copia as chaves da metade direita para o novo no
    for (int i = 0; i < ordem - 1; i++) {
        strcpy(novoNo->chaves[i], filho->chaves[meio + 1 + i]);
    }
    
    // Se não for folha, copia os filhos da metade direita
    if (!filho->folha) {
        for (int i = 0; i < ordem; i++) {
            novoNo->filhos[i] = filho->filhos[meio + 1 + i];
        }
    }
    
    // Atualiza o número de chaves do filho original
    filho->numChaves = meio;  // Tem t-1 chaves
    
    // Desloca as chaves do pai para abrir espaço
    for (int i = pai->numChaves; i > posicao; i--) {
        strcpy(pai->chaves[i], pai->chaves[i-1]);
    }
    
    // Desloca os filhos do pai
    for (int i = pai->numChaves + 1; i > posicao + 1; i--) {
        pai->filhos[i] = pai->filhos[i-1];
    }
    
    // Sobe a chave do meio para o pai
    strcpy(pai->chaves[posicao], filho->chaves[meio]);
    pai->numChaves++;
    
    // Conecta o novo no como filho do pai
    pai->filhos[posicao + 1] = novoNo;
}

/* ============================================================
 *  INSERIR EM NO NAO CHEIO (FUNCAO AUXILIAR) 
 * ============================================================ */

 void inserirNoNaoCheio(no *noAtual, const char *chave, int ordem) {
    /*
        Entrada: 
            noAtual - nó onde a chave deve ser inserida (garantido que não está cheio)
            chave - chave a ser inserida
            ordem - ordem da arvore B
        Saída: 
            nenhuma (modifica a arvore diretamente)
        Descrição: 
            Insere a chave no nó não cheio. Se o nó for folha, 
            insere diretamente. Se for nó interno, encontra o filho apropriado e 
            insere recursivamente. Se o filho estiver cheio, divide o filho antes de descer.
    */
    int i = noAtual->numChaves - 1;
    
    // Se é no folha, insere diretamente
    if (noAtual->folha) {
        // Encontra a posicao correta para inserir
        while (i >= 0 && strcmp(chave, noAtual->chaves[i]) < 0) {
            strcpy(noAtual->chaves[i + 1], noAtual->chaves[i]);
            i--;
        }
        
        // Insere a nova chave
        strcpy(noAtual->chaves[i + 1], chave);
        noAtual->numChaves++;
    } 
    else {
        // Nó interno: encontra o filho apropriado
        while (i >= 0 && strcmp(chave, noAtual->chaves[i]) < 0) {
            i--;
        }
        i++;
        
        // Verifica se o filho está cheio
        if (noAtual->filhos[i]->numChaves == 2 * ordem - 1) {
            // Divide o filho
            cisaoPagina(noAtual, i, noAtual->filhos[i], ordem);
            
            // Decide qual dos dois filhos descer
            if (strcmp(chave, noAtual->chaves[i]) > 0) {
                i++;
            }
        }
        
        // Insere recursivamente no filho
        inserirNoNaoCheio(noAtual->filhos[i], chave, ordem);
    }
}

/* ============================================================
 *  INSERIR CHAVE NA ARVORE B
 * ============================================================ */
void inserir(arvoreB *arvore, const char *chave, int ordem) {
    /*
        Entrada: 
            arvore - ponteiro para a arvore B onde a chave deve ser inserida
            chave - chave a ser inserida
            ordem - ordem da arvore B
        Saída:
            nenhuma (modifica a arvore diretamente)
        Descrição:
            Insere a chave na arvore B. Verifica se a chave já existe. Se a raiz estiver cheia, 
            cria uma nova raiz e divide a antiga raiz. Depois insere a chave na raiz (que pode ser nova ou antiga).
    
    */
    no *raiz = arvore->raiz;
    
    // Verifica se a chave já existe
    resultadoBusca busca = buscarB(raiz, chave);
    if (busca.f == 1) {
        printf("Pokemon '%s' ja existe na arvore!\n", chave);
        return;
    }
    
    // Se a raiz está cheia, precisa crescer a arvore
    if (raiz->numChaves == 2 * ordem - 1) {
        // Cria uma nova raiz
        no *novaRaiz = criaNo(ordem, 0);
        novaRaiz->filhos[0] = raiz;
        arvore->raiz = novaRaiz;
        
        // Divide a antiga raiz
        cisaoPagina(novaRaiz, 0, raiz, ordem);
        
        // Insere a chave na nova raiz
        inserirNoNaoCheio(novaRaiz, chave, ordem);
    } 
    else {
        // Insere na raiz atual
        inserirNoNaoCheio(raiz, chave, ordem);
    }
}



/* ============================================================
 *  INSERCAO A PARTIR DO ARQUIVO .txt 
 * ============================================================ */
void loadFile(arvoreB *arvore, int ordem) {
    /*
        Entrada:
            arvore - ponteiro para a arvore B onde os Pokemons devem ser inseridos
            ordem - ordem da arvore B
        Saída:
            nenhuma (modifica a arvore diretamente)
        Descrição:
            Lê os nomes dos Pokemons do arquivo "pokemon_names.txt" e insere cada nome na arvore B.
    
    */
    char pokemon[100];
    int contador = 0;
    FILE *file = fopen("pokemon_names.txt", "r");
    


    if (!file) {
        printf("Erro ao abrir arquivo pokemon_names.txt\n");
        return;
    }
    
    printf("Lendo arquivo e inserindo Pokemons...\n");
    Sleep(2000);
    
    while (fgets(pokemon, sizeof(pokemon), file)) {
        // Remove o newline e carriage return
        pokemon[strcspn(pokemon, "\n")] = 0;
        pokemon[strcspn(pokemon, "\r")] = 0;
        
        // Pula linhas vazias
        if (strlen(pokemon) == 0) 
            continue;
        
        inserir(arvore, pokemon, ordem);
        contador++;
    }
    
    printf("\n========================================\n");
    printf("Total de Pokemons inseridos: %d\n", contador);
    printf("========================================\n");
    
    Sleep(1000); // Pausa para o usuário ler a mensagem;
    
    fclose(file);
}

/* ============================================================
 *  MAIN
 * ============================================================ */

int main() {
    int opcao = 0, ordemArvore;
    
    // Pega a ordem da arvore
    printf("========================================\n");
    printf("       ARVORE B - POKEMONS\n");
    printf("========================================\n");
    printf("Qual sera a ordem da arvore?\n");
    scanf("%d", &ordemArvore);
    
    while (ordemArvore < 2) {
        printf("A ordem da arvore deve ser >= 2. Insira novamente: ");
        scanf("%d", &ordemArvore);
    }
        
    // Criação da arvore
    arvoreB *arvore = criaArvore(ordemArvore);
    
    Sleep(1000); // Pausa para o usuário ler a mensagem;

    // Carrega os Pokemons do arquivo
    printf("\nCarregando Pokemons do arquivo...\n");
    loadFile(arvore, ordemArvore);
    
    printf("\nArvore carregada com sucesso!\n");

    Sleep(1000); // Pausa para o usuário ler a mensagem;
    
    // Menu principal
    while (opcao != 9) {
        printf("\n// ----- // ----- // ARVORE B // ----- // ----- //\n");
        printf("[1] - Buscar Pokemon\n");
        printf("[2] - Inserir Pokemon\n");
        printf("[9] - Finalizar Programa\n");
        printf("-------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer
        
        // [1] - Buscar
        if (opcao == 1){
            printf("Dica: Atente-se a pontuacoes no nome do pokemon, alem do nome comecar com letra maiuscula!\n");
            printf("Digite o nome do pokemon que deseja buscar: \n");
            
            char nomeProcurar[100];
            scanf(" %99[^\n]", nomeProcurar);
            resultadoBusca resultado = buscarB(arvore->raiz, nomeProcurar);
            if (resultado.f == 1) {
                printf("Pokemon '%s' ENCONTRADO na posicao %d do no!\n", nomeProcurar, resultado.g);
            } 
            else {
                printf("Pokemon '%s' NAO encontrado na arvore.\n", nomeProcurar);
            }
        }

        // [2] - Inserir
        else if (opcao == 2){
            char nomePokemon[100];
            scanf(" %99[^\n]", nomePokemon);
            inserir(arvore, nomePokemon, ordemArvore);
        }

        // [9] - Encerra execução
        else if (opcao == 9) {
            Sleep(1000); // Pausa para o usuário ler a mensagem

            printf("\n// ----- Programa finalizado ! ----- //\n\n\n\n");
            free(arvore);
        }
        // Opção inválida
        else {
            Sleep(1000); // Pausa para o usuário ler a mensagem
            printf("\nResposta invalida!\nInsira novamente: ");
        }
    }
    
    return 0;
}