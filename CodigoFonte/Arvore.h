#ifndef ARVORE_H
#define ARVORE_H

//Implementação da árvore AVL
typedef int TipoChave;

typedef struct TipoItem{
	TipoChave Chave;
	//Posicao é um inteiro para poder associar com as sprites
	int Posicao;
}TipoItem;

typedef struct TipoNo{
    TipoItem Info; //Informação contida no nó
    struct TipoNo *Esq; //Ponteiro da esquerda
    struct TipoNo *Dir; //Ponteiro da direita
}TipoNo;

typedef struct TipoNo *TipoApontador;
typedef TipoApontador TipoArvore;

//Funções essenciais para criação da árvore
void CriaArvore(TipoArvore *A);
void CriaRaiz(TipoArvore *A, TipoItem I);
void visita(TipoArvore A);
void emOrdem(TipoArvore A);
//Verifica se já possui uma chave na arvore
TipoChave Pesquisa(TipoArvore *A, TipoChave C);
//Rotações da arvore avl para manter balanceada
TipoArvore RotacaoSimplesDireita(TipoArvore *A);
TipoArvore RotacaoSimplesEsquerda(TipoArvore *A);
//Funções auxiliares para verificar o balanceamento na inserção e remoção
int AlturaArvore(TipoArvore *A);
int FatorBalanceamento(TipoArvore *A);
TipoArvore VerificaBalanceamento(TipoArvore *A, int *Rotacao);
TipoArvore VerificaBalanceamento(TipoArvore *A);
TipoArvore InsereArvore(TipoArvore *A, TipoItem I, int *Rotacao);
//Funções auxiliares para remover da arvore
TipoArvore MenorNoArvore(TipoArvore *A);
TipoArvore RemoverFolha(TipoArvore *A);
TipoArvore Remover1FilhoEsquerda(TipoArvore *A);
TipoArvore Remover1FilhoDireita(TipoArvore *A);
TipoArvore Remover2Filhos(TipoArvore *A);
TipoArvore RemoverNo(TipoArvore *A);
TipoArvore RemoverNoArvore(TipoArvore *A, TipoItem I);
void RemoverArvore(TipoArvore *A);
//Insere errado de acordo com a posição que o jogador escolher
bool InsereJogador(TipoArvore *A, TipoItem I, int SpriteColidida);
//Verifica se as duas arvores são iguais
bool SaoIguais(TipoArvore A, TipoArvore B);
//Copia a árvore certa para a arvore jogador
void CopiaArvore(TipoArvore *A, TipoArvore *B);

#endif // ARVORE_H
