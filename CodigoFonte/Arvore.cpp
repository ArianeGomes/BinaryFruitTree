#include <iostream>
#include "Arvore.h"

void CriaArvore(TipoArvore *A){
    *A = NULL;
}

void CriaRaiz(TipoArvore *A, TipoItem I){
    //Aloca dinamicamente o n�
    *A = (TipoArvore)malloc(sizeof(TipoNo));

    (*A)->Info = I;
    (*A)->Dir = NULL;
    (*A)->Esq = NULL;
}

void visita(TipoArvore A){
	printf("%d ", A->Info.Chave);
}

void emOrdem(TipoArvore A){
	if (A == NULL)
        return;
	emOrdem(A->Esq);
	visita(A);
	emOrdem(A->Dir);
}

TipoChave Pesquisa(TipoArvore *A, TipoChave C) {
    TipoItem I;

    if ((*A) == NULL) { //nao achou
        I.Chave = -1;
        I.Posicao = -1;
        return I.Chave;
    }

    // ACHOU!
    if (C == (*A)->Info.Chave)
        return (*A)->Info.Chave;


    if (C > (*A)->Info.Chave) { // direita
        return Pesquisa(&(*A)->Dir, C);
    } else { // esquerda
        return Pesquisa(&(*A)->Esq, C);
    }
}

TipoArvore RotacaoSimplesDireita(TipoArvore *A){
    TipoArvore B = (*A)->Esq;
    (*A)->Esq = B->Dir;
    B->Dir = (*A);
    return B;
}

TipoArvore RotacaoSimplesEsquerda(TipoArvore *A){
    TipoArvore B = (*A)->Dir;
    (*A)->Dir = B->Esq;
    B->Esq = (*A);
    return B;
}

int AlturaArvore(TipoArvore *A){
    if((*A) == NULL){
        return -1;
    }else{
        int altEsq, altDir;
        altEsq = AlturaArvore(&(*A)->Esq);
        altDir = AlturaArvore(&(*A)->Dir);
        if(altEsq > altDir){
            return altEsq + 1;
        }else{
            return altDir + 1;
        }
    }
}

int FatorBalanceamento(TipoArvore *A){
    //Fator de Balanceamento = Altura da sub-arvore direita - Altura da sub-arvore esquerda.
    return AlturaArvore(&(*A)->Dir) - AlturaArvore(&(*A)->Esq);
}

TipoArvore VerificaBalanceamento(TipoArvore *A, int *Rotacao){
    int fb;
    fb = FatorBalanceamento(&(*A)); //Ap�s inserir o n� para esq ou dir, verificar Fator de bal.
    if(fb < -1){
        if(FatorBalanceamento(&(*A)->Esq) > 0){      //Rota��o dupla a direita.
            (*A)->Esq = RotacaoSimplesEsquerda(&(*A)->Esq);
            (*A) = RotacaoSimplesDireita(&(*A));
            (*Rotacao) = 1;
        }else{
            (*A) = RotacaoSimplesDireita(&(*A));  //Rota��o simples a esquerda.
            (*Rotacao) = 0;
        }
    }else if(fb > 1){
        if(FatorBalanceamento(&(*A)->Dir) < 0){      //Rota��o dupla a esquerda.
            (*A)->Dir = RotacaoSimplesDireita(&(*A)->Dir);
            (*A) = RotacaoSimplesEsquerda(&(*A));
            (*Rotacao) = 3;
        }else{
            (*A) = RotacaoSimplesEsquerda(&(*A)); //Rota��o simples a direita.
            (*Rotacao) = 2;
        }
    }
    return (*A);
}

TipoArvore VerificaBalanceamento(TipoArvore *A){
    int fb;
    fb = FatorBalanceamento(&(*A)); //Ap�s inserir o n� para esq ou dir, verificar Fator de bal.
    if(fb < -1){
        if(FatorBalanceamento(&(*A)->Esq) > 0){      //Rota��o dupla a direita.
            (*A)->Esq = RotacaoSimplesEsquerda(&(*A)->Esq);
        }
        (*A) = RotacaoSimplesDireita(&(*A));             //Rota��o simples a esquerda.
    }else if(fb > 1){
        if(FatorBalanceamento(&(*A)->Dir) < 0){      //Rota��o dupla a esquerda.
            (*A)->Dir = RotacaoSimplesDireita(&(*A)->Dir);
        }
        (*A) = RotacaoSimplesEsquerda(&(*A));            //Rota��o simples a direita.
    }
    return (*A);
}

TipoArvore InsereArvore(TipoArvore *A, TipoItem I, int *Rotacao){
    if((*A) == NULL){
        //Se a �rvore estiver vazia, inserir o n�.
        CriaRaiz(&(*A), I);
    }
    else{
                        //Se a �rvore n�o estiver vazia, verificar se num � menor que n.
        if(I.Chave < (*A)->Info.Chave){   //Se for menor, inserir a esquerda.
            (*A)->Esq = InsereArvore(&(*A)->Esq, I, &(*Rotacao));
        }
        else{              //Sen�o, inserir a direita.
            (*A)->Dir = InsereArvore(&(*A)->Dir, I, &(*Rotacao));
        }
        (*A) = VerificaBalanceamento(&(*A), &(*Rotacao)); //Retorna a arvore balanceada
        //Verificar balanceamento da �rvore.
    }
    return (*A);
}

//Fun��es que retorna o endere�o do menor n� da �rvore.
TipoArvore MenorNoArvore(TipoArvore *A){
    TipoArvore aux = (*A);
    while(aux->Esq != NULL) {  //Procurar o n� mais a esquerda (menor n� da �rvore).
        aux = aux->Esq;
    }
    return aux;                 //Retornar o endere�o do menor n� da �rvore.
}

//Fun��o que remove um n� que � folha (n�o possui filhos).
TipoArvore RemoverFolha(TipoArvore *A){
    free(A);
    return NULL;
}

TipoArvore Remover1FilhoEsquerda(TipoArvore *A){
    TipoArvore aux = (*A)->Esq;
    free(A);
    return aux;
}

TipoArvore Remover1FilhoDireita(TipoArvore *A){
    TipoArvore aux = (*A)->Dir;
    free(A);
    return aux;
}

TipoArvore Remover2Filhos(TipoArvore *A){
    TipoArvore aux;
    TipoItem I;
    aux = MenorNoArvore(&(*A)->Dir);  //auxiliar recebe o endere�o do menor n� da �rvore.
    I.Chave = aux->Info.Chave;                     //guardar o valor do auxiliar em uma vari�vel x.
    (*A) = RemoverNoArvore(&(*A)->Dir, I);     //remover da �rvore o n� que substituir� o n� com 2 filhos.

    (*A)->Info.Chave = I.Chave;                       //substituir o valor do n� com 2 filhos.
    return (*A);
}

//Fun��o para verificar o tipo de n� que ser� removido.
TipoArvore RemoverNo(TipoArvore *A){
    //Verificar se o n� � uma folha (N�o possui filhos).
    if((*A)->Dir == NULL && (*A)->Esq == NULL){
        (*A) = RemoverFolha(&(*A));
    }
    else{
        if((*A)->Dir == NULL){
            (*A) = Remover1FilhoEsquerda(&(*A));
        }
        else{
            if((*A)->Esq == NULL){
                (*A) = Remover1FilhoDireita(&(*A));
            }
            else{
                (*A) = Remover2Filhos(&(*A));
            }
        }
    }
    return (*A);
}

TipoArvore RemoverNoArvore(TipoArvore *A, TipoItem I){
    //Verificar se a �rvore n�o est� vazia.
    if((*A) != NULL){
        //Se a �rvore n�o est� vazia, buscar o elemento x.
        if((*A)->Info.Chave == I.Chave){    //1 - Verificar se o elemento x est� na raiz.
            (*A) = RemoverNo(&(*A));  //Chamar a fun��o para remover o n�.
        }
        else{
            //Se x n�o est� na raiz, verificar para qual lado x est�.
            if(I.Chave < (*A)->Info.Chave){
                //Fazer chamada recursiva para a esquerda.
                (*A)->Esq = RemoverNoArvore(&(*A)->Esq, I);
            }
            else{
                //Fazer chamada recursiva para a direita.
                (*A)->Dir = RemoverNoArvore(&(*A)->Dir, I);
            }
            (*A) = VerificaBalanceamento(&(*A));
            //Verificar balanceamento da �rvore.
        }
    }
    return (*A);
}

void RemoverArvore(TipoArvore *A){
    if ((*A) == NULL) {
        return;
    }

	RemoverArvore(&(*A)->Esq);
	RemoverArvore(&(*A)->Dir);
	RemoverNo(&(*A));
}

//Insere de acordo com a barraca que est� colidindo
bool InsereJogador(TipoArvore *A, TipoItem I, int SpriteColidida){
    if(SpriteColidida == 0){
        CriaRaiz(A, I);
        return true;
    }
    else if(SpriteColidida == 1 && (*A) != NULL){
        InsereJogador(&(*A)->Esq, I, 0);
    }
    else if(SpriteColidida == 3 && (*A) != NULL && (*A)->Esq != NULL){
        InsereJogador(&(*A)->Esq->Esq, I, 0);
    }
    else if(SpriteColidida == 4 && (*A) != NULL && (*A)->Esq != NULL){
        InsereJogador(&(*A)->Esq->Dir, I, 0);
    }
    else if(SpriteColidida == 2 && (*A) != NULL){
        InsereJogador(&(*A)->Dir, I, 0);
    }
    else if(SpriteColidida == 6 && (*A) != NULL && (*A)->Dir != NULL){
        InsereJogador(&(*A)->Dir->Dir, I, 0);
    }
    else if(SpriteColidida == 5 && (*A) != NULL && (*A)->Dir != NULL){
        InsereJogador(&(*A)->Dir->Esq, I, 0);
    }

    return false;
}

//Para verificar se as arvores s�o iguais
bool SaoIguais(TipoArvore A, TipoArvore B){
    if(A == NULL && B == NULL)
        return true;
    else if(A != NULL && B != NULL && A->Info.Chave == B->Info.Chave && SaoIguais(A->Esq, B->Esq) && SaoIguais(A->Dir, B->Dir))
        return true;
    else
        return false;
}

void CopiaArvore(TipoArvore *A, TipoArvore *B){
	if((*A) != NULL) {
        CriaRaiz(&(*B), (*A)->Info);
        CopiaArvore(&(*A)->Esq, &(*B)->Esq);
        CopiaArvore(&(*A)->Dir, &(*B)->Dir);
    }
}
