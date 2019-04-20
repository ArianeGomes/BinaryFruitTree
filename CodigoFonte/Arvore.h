#ifndef ARVORE_H
#define ARVORE_H

//Implementa��o da �rvore AVL
typedef int TipoChave;

typedef struct TipoItem{
	TipoChave Chave;
	//Posicao � um inteiro para poder associar com as sprites
	int Posicao;
}TipoItem;

typedef struct TipoNo{
    TipoItem Info; //Informa��o contida no n�
    struct TipoNo *Esq; //Ponteiro da esquerda
    struct TipoNo *Dir; //Ponteiro da direita
}TipoNo;

typedef struct TipoNo *TipoApontador;
typedef TipoApontador TipoArvore;

//Fun��es essenciais para cria��o da �rvore
void CriaArvore(TipoArvore *A);
void CriaRaiz(TipoArvore *A, TipoItem I);
void visita(TipoArvore A);
void emOrdem(TipoArvore A);
//Verifica se j� possui uma chave na arvore
TipoChave Pesquisa(TipoArvore *A, TipoChave C);
//Rota��es da arvore avl para manter balanceada
TipoArvore RotacaoSimplesDireita(TipoArvore *A);
TipoArvore RotacaoSimplesEsquerda(TipoArvore *A);
//Fun��es auxiliares para verificar o balanceamento na inser��o e remo��o
int AlturaArvore(TipoArvore *A);
int FatorBalanceamento(TipoArvore *A);
TipoArvore VerificaBalanceamento(TipoArvore *A, int *Rotacao);
TipoArvore VerificaBalanceamento(TipoArvore *A);
TipoArvore InsereArvore(TipoArvore *A, TipoItem I, int *Rotacao);
//Fun��es auxiliares para remover da arvore
TipoArvore MenorNoArvore(TipoArvore *A);
TipoArvore RemoverFolha(TipoArvore *A);
TipoArvore Remover1FilhoEsquerda(TipoArvore *A);
TipoArvore Remover1FilhoDireita(TipoArvore *A);
TipoArvore Remover2Filhos(TipoArvore *A);
TipoArvore RemoverNo(TipoArvore *A);
TipoArvore RemoverNoArvore(TipoArvore *A, TipoItem I);
void RemoverArvore(TipoArvore *A);
//Insere errado de acordo com a posi��o que o jogador escolher
bool InsereJogador(TipoArvore *A, TipoItem I, int SpriteColidida);
//Verifica se as duas arvores s�o iguais
bool SaoIguais(TipoArvore A, TipoArvore B);
//Copia a �rvore certa para a arvore jogador
void CopiaArvore(TipoArvore *A, TipoArvore *B);

#endif // ARVORE_H
