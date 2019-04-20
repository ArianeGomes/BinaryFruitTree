#ifndef GAME_H
#define GAME_H
#include "Arvore.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

//Definições
#define AlturaTela 600
#define LarguraTela 800
#define AlturaFruta 50
#define LarguraFruta 50
#define AlturaPersonagem 58
#define LarguraPersonagem 43
#define VelocidadeFruta 2.5
#define QuantidadeDeFrutas 100
#define VelocidadeSprite 3
#define EscalaPersonagem 1.1
#define EscalaFruta 0.6
#define QuantidadeTempo 90

using namespace std;
using namespace sf;

//Classe Game
class Game{
    public:
        Game();
        bool VerificaBotao(Sprite Sprite);
        void Reseta();
        bool AtualizaBotao(Sprite &Sprite);
        bool AtualizaBotaoMenor(Sprite &Sprite);
        void CarregaImagens();
        void CarregaMusicas();
        void JanelaEventos();
        void MostraTempo();
        void SorteiaFrutas(int Fruta);
        void CairFrutas(Sprite Sprite, int PosicaoInicio);
        void MovimentoPersonagem();
        int Colisao(Sprite Sprite); //Usado para verificar colisao com as frutas
        void ColisaoObjeto(Sprite Sprite); //Usado para verificar colisões em geral
        void ColisaoLixeira();
        void AtualizaArvoreJogador();
        void ComparaArvore();
        void ColisaoArvore();
        void DesenhaArvore();
        void FimDeJogo();
        void CenarioMenu();
        void CenarioInstrucoes();
        void CenarioJogo();
        void Controle();

    private:
        //SFML
        //Delay e tempo
        Time delay;
        Clock clock, clockPersonagem, clockImagemPersonagem;
        //Mouse e recorte de sprite
        Vector2i position, AtualizaPersonagem;
        IntRect rectSourceSprite, rectSourceSprite2, rectSourceSpriteFruta, rectSourceSpriteTempo;
        //Janela
        RenderWindow window;
        Event Event;
        //Tela Menu
        Texture CenarioMenuTexture, BotaoJogarTexture, BotaoInstrucoesTexture, BotaoSairTexture;
        Sprite CenarioMenuSprite, BotaoJogarSprite, BotaoInstrucoesSprite, BotaoSairSprite;
        //Tela Instruções
        Texture CenarioInstrucoesTexture, BotaoVoltarTexture;
        Sprite CenarioInstrucoesSprite, BotaoVoltarSprite;
        //Tela Jogo
        Texture CenarioJogoTexture, FrutaTexture, PersonagemTexture;
        Sprite CenarioJogoSprite, FrutaSprite[QuantidadeDeFrutas], FrutaArvoreSprite[QuantidadeDeFrutas], FrutaAtualSprite[QuantidadeDeFrutas], PersonagemSprite;
        Texture LixeiraTexture, LixeiraInvisivelTexture, BarracaTexture[7], BarracaInvisivelTexture, BotaoAvisoBarracaTexture;
        Sprite LixeiraSprite, LixeiraInvisivelSprite, BarracaSprite[7], BarracaInvisivelSprite[7], BotaoAvisoBarracaSprite;
        //Rotação da arvore
        Texture  AvisoRotacaoTexture, BotaoRotacaoDireitaTexture, BotaoRotacaoEsquerdaTexture, BotaoRotacaoDuplaEsquerdaTexture, BotaoRotacaoDuplaDireitaTexture;
        Sprite AvisoRotacaoSprite, BotaoRotacaoDireitaSprite, BotaoRotacaoEsquerdaSprite, BotaoRotacaoDuplaEsquerdaSprite, BotaoRotacaoDuplaDireitaSprite;
        Vector2f PosicaoFruta[6], VelocidadePersonagemEixoX, VelocidadePersonagemEixoY;
        //Tela Perdeu e Ganhou
        Texture GanhouTexture, PerdeuPosicaoTexture, PerdeuRotacaoTexture, PerdeuChaveTexture, BotaoJogarNovamenteTexture, PerdeuTempoTexture;
        Sprite GanhouSprite, PerdeuPosicaoSprite, PerdeuRotacaoSprite, PerdeuChaveSprite, BotaoJogarNovamenteSprite, PerdeuTempoSprite;
        //Tempo e Som
        Texture TempoTexture, SomTexture;
        Sprite TempoSprite[QuantidadeTempo+1], SomSprite;
        //Músicas
        Music FundoMusic;
        //Sons
        SoundBuffer PegarFrutaBuffer, ColocaArvoreBuffer, JogarLixoBuffer, PerdeuBuffer, GanhouBuffer;
        Sound PegarFrutaSound, ColocaArvoreSound, JogarLixoSound, PerdeuSound, GanhouSound;


        //Lógica
        //Telas
        bool TelaMenu, TelaInstrucoes, TelaJogo;
        //Controla a continuidade
        float DeltaFruta, DeltaPersonagem;
        //Controle das frutas que aparecerão na tela
        int FrutaCaindo[6], PosicaoFrutaInicio[6];

        //Auxiliares
        //Auxiliar para começar a cair frutas na tela quando inicia o programa
        bool Inicio;
        //Auxiliares para controle da colisao com as frutas
        bool Colidiu, colisao[6];
        int FrutaPosicaoAtual;
        //Auxiliares para inserção na arvore
        bool BotaoInserirArvore, JaInseriu[7];
        int PosicaoInsereArvore, cresceu, FrutaInserida[7];
        //Auxiliar para verificar o balanceamento
        int Rotacao;
        //Auxiliar para setar boneca quando perder, ganhar ou inserir fruta
        bool Jogar;
        int Perdeu, Ganhou, Reset, VerificaTempo;

        //Arvore
        TipoItem FrutaAtual;
        TipoArvore ArvoreCerta, ArvoreJogador;

        Clock Relogio;
        Time Tempo;
};

#endif // GAME_H
