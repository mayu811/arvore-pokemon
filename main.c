#include <stdio.h>

typedef struct celula {
    #string conteudo;
    #no* esq, dir;
} no;
"""

= Nome dos integrantes do grupo ======================

- João VItor Costa Braga - RGA: 2024.1906.XXX-X
- Louise Mayumi Takigawa Pereia - RGA: 2024.1906.028-5

=====================================================

"""

}

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

no* inserir(no* raiz){
    """
    lê uma chave x e realiza sua inserção na árvore B.

    Entrada:

    Saída:
    """

};

void imprimir_arvore(no* raiz){

};

int main() {
    
    int opcao, ordem_arvore = 0;

    printf("Qual será a ordem da árvore?" );
    scanf("%s", &ordem_arvore);

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
    
    while (opcao != 9){

        printf("// ----- // ----- // ÁRVORE B // ----- // ----- //\n");
        printf("[1] - Buscar\n");
        printf("[2] - Inserir\n");
        printf("[3] - Visualizar\n");
        printf("[9] - Finalizar\n");

        scanf("%d", opcao);
        
        if (opcao == 1){


        }

        else if (opcao == 2){


        }

        else if (opcao == 3){


        }

        else {
            printf("\nResposta inválida!\nInsira novamente: ");
        }

    }

    printf("\n// ----- Programa finalizado ! ----- //\n");

    return 0;
}
