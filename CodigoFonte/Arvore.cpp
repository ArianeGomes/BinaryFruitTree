#include <iostream>
#include "Arvore.h"

void CriaArvore(TipoArvore *A){
    *A = NULL;
}

void CriaRaiz(TipoArvore *A, TipoItem I){
    //Aloca dinamicamente o nó
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
    fb = FatorBalanceamento(&(*A)); //Após inserir o nó para esq ou dir, verificar Fator de bal.
    if(fb < -1){
        if(FatorBalanceamento(&(*A)->Esq) > 0){      //Rotação dupla a direita.
            (*A)->Esq = RotacaoSimplesEsquerda(&(*A)->Esq);
            (*A) = RotacaoSimplesDireita(&(*A));
            (*Rotacao) = 1;
        }else{
            (*A) = RotacaoSimplesDireita(&(*A));  //Rotação simples a esquerda.
            (*Rotacao) = 0;
        }
    }else if(fb > 1){
        if(FatorBalanceamento(&(*A)->Dir) < 0){      //Rotação dupla a esquerda.
            (*A)->Dir = RotacaoSimplesDireita(&(*A)->Dir);
            (*A) = RotacaoSimplesEsquerda(&(*A));
            (*Rotacao) = 3;
        }else{
            (*A) = RotacaoSimplesEsquerda(&(*A)); //Rotação simples a direita.
            (*Rotacao) = 2;
        }
    }
    return (*A);
}

TipoArvore VerificaBalanceamento(TipoArvore *A){
    int fb;
    fb = FatorBalanceamento(&(*A)); //Após inserir o nó para esq ou dir, verificar Fator de bal.
    if(fb < -1){
        if(FatorBalanceamento(&(*A)->Esq) > 0){      //Rotação dupla a direita.
            (*A)->Esq = RotacaoSimplesEsquerda(&(*A)->Esq);
        }
        (*A) = RotacaoSimplesDireita(&(*A));             //Rotação simples a esquerda.
    }else if(fb > 1){
        if(FatorBalanceamento(&(*A)->Dir) < 0){      //Rotação dupla a esquerda.
            (*A)->Dir = RotacaoSimplesDireita(&(*A)->Dir);
        }
        (*A) = RotacaoSimplesEsquerda(&(*A));            //Rotação simples a direita.
    }
    return (*A);
}

TipoArvore InsereArvore(TipoArvore *A, TipoItem I, int *Rotacao){
    if((*A) == NULL){
        //Se a árvore estiver vazia, inserir o nó.
        CriaRaiz(&(*A), I);
    }
    else{
                        //Se a árvore não estiver vazia, verificar se num é menor que n.
        if(I.Chave < (*A)->Info.Chave){   //Se for menor, inserir a esquerda.
            (*A)->Esq = InsereArvore(&(*A)->Esq, I, &(*Rotacao));
        }
        else{              //Senão, inserir a direita.
            (*A)->Dir = InsereArvore(&(*A)->Dir, I, &(*Rotacao));
        }
        (*A) = VerificaBalanceamento(&(*A), &(*Rotacao)); //Retorna a arvore balanceada
        //Verificar balanceamento da árvore.
    }
    return (*A);
}

//Funçães que retorna o endereço do menor nó da árvore.
TipoArvore MenorNoArvore(TipoArvore *A){
    TipoArvore aux = (*A);
    while(aux->Esq != NULL) {  //Procurar o nó mais a esquerda (menor nó da árvore).
        aux = aux->Esq;
    }
    return aux;                 //Retornar o endereço do menor nó da árvore.
}

//Função que remove um nó que é folha (não possui filhos).
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
    aux = MenorNoArvore(&(*A)->Dir);  //auxiliar recebe o endereço do menor nó da árvore.
    I.Chave = aux->Info.Chave;                     //guardar o valor do auxiliar em uma variável x.
    (*A) = RemoverNoArvore(&(*A)->Dir, I);     //remover da árvore o nó que substituirá o nó com 2 filhos.

    (*A)->Info.Chave = I.Chave;                       //substituir o valor do nó com 2 filhos.
    return (*A);
}

//Função para verificar o tipo de nó que será removido.
TipoArvore RemoverNo(TipoArvore *A){
    //Verificar se o nó é uma folha (Não possui filhos).
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
    //Verificar se a árvore não está vazia.
    if((*A) != NULL){
        //Se a árvore não está vazia, buscar o elemento x.
        if((*A)->Info.Chave == I.Chave){    //1 - Verificar se o elemento x está na raiz.
            (*A) = RemoverNo(&(*A));  //Chamar a função para remover o nó.
        }
        else{
            //Se x não está na raiz, verificar para qual lado x está.
            if(I.Chave < (*A)->Info.Chave){
                //Fazer chamada recursiva para a esquerda.
                (*A)->Esq = RemoverNoArvore(&(*A)->Esq, I);
            }
            else{
                //Fazer chamada recursiva para a direita.
                (*A)->Dir = RemoverNoArvore(&(*A)->Dir, I);
            }
            (*A) = VerificaBalanceamento(&(*A));
            //Verificar balanceamento da árvore.
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

//Insere de acordo com a barraca que está colidindo
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

//Para verificar se as arvores são iguais
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
