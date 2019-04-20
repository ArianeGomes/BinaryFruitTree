#include "Game.h"

Game::Game(){
    //Delay
    delay = sf::milliseconds(100);

    //Telas
    TelaMenu = 1;
    TelaInstrucoes = 0;
    TelaJogo = 0;

    //Atualiza imagem do personagem
    AtualizaPersonagem.x = 0;
    AtualizaPersonagem.y = 1;

    //Velocidade de movimento da personagem
    VelocidadePersonagemEixoY.x = 0;
    VelocidadePersonagemEixoY.y = 180;
    VelocidadePersonagemEixoX.x = 180;
    VelocidadePersonagemEixoX.y = 0;

    //Posição das frutas iniciais
    PosicaoFrutaInicio[0] = -100;
    PosicaoFrutaInicio[1] = -200;
    PosicaoFrutaInicio[2] = -300;
    PosicaoFrutaInicio[3] = -400;
    PosicaoFrutaInicio[4] = -500;
    PosicaoFrutaInicio[5] = -600;

    //Fruta que está caindo no momento
    for(int i=0; i<6; i++)
        FrutaCaindo[i] = -1;

    //Colisao com que fruta
    for(int i=0; i<6; i++)
        colisao[i] = 0;

    //Auxiliares
    DeltaFruta = 0;
    DeltaPersonagem = 0;
    Inicio = 1;
    Colidiu = false;
    FrutaAtual.Chave = -1;
    PosicaoInsereArvore = -1;
    BotaoInserirArvore = false;
    Rotacao = -1;
    Jogar = true;
    Perdeu = 0;
    Ganhou = 0;
    Reset = 0;
    VerificaTempo = 0;

    //Para saber em que posicao ja inseriu
    for(int i=0; i<7; i++)
        JaInseriu[i] = 0;

    //Para saber qual fruta inseriu e printar
    for(int i=0; i<7; i++)
        FrutaInserida[i] = -1;

    //Arvore, usada pra verificar com a posicao em q ele coloca nas barracas
    CriaArvore(&ArvoreCerta);
    CriaArvore(&ArvoreJogador);
}

void Game::Reseta(){
    for(int i = 0; i < QuantidadeDeFrutas; i++) {
        FrutaSprite[i].setPosition(-30,0);
        FrutaArvoreSprite[i].setPosition(-30,0);
        FrutaAtualSprite[i].setPosition(367, 11);
    }

    //Telas
    TelaMenu = 1;
    TelaInstrucoes = 0;
    TelaJogo = 0;

    //Atualiza imagem do personagem
    AtualizaPersonagem.x = 0;
    AtualizaPersonagem.y = 1;

    //Velocidade de movimento da personagem
    VelocidadePersonagemEixoY.x = 0;
    VelocidadePersonagemEixoY.y = 180;
    VelocidadePersonagemEixoX.x = 180;
    VelocidadePersonagemEixoX.y = 0;

    //Posição das frutas iniciais
    PosicaoFrutaInicio[0] = -100;
    PosicaoFrutaInicio[1] = -200;
    PosicaoFrutaInicio[2] = -300;
    PosicaoFrutaInicio[3] = -400;
    PosicaoFrutaInicio[4] = -500;
    PosicaoFrutaInicio[5] = -600;

    //Fruta que está caindo no momento
    for(int i=0; i<6; i++)
        FrutaCaindo[i] = -1;

    //Colisao com que fruta
    for(int i=0; i<6; i++)
        colisao[i] = 0;

    //Auxiliares
    DeltaFruta = 0;
    DeltaPersonagem = 0;
    Inicio = 1;
    Colidiu = false;
    FrutaAtual.Chave = -1;
    PosicaoInsereArvore = -1;
    BotaoInserirArvore = false;
    Rotacao = -1;
    Jogar = true;
    Perdeu = 0;
    Ganhou = 0;
    Reset = 0;
    VerificaTempo = 0;

    //Para saber em que posicao ja inseriu
    for(int i=0; i<7; i++)
        JaInseriu[i] = 0;

    //Para saber qual fruta inseriu e printar
    for(int i=0; i<7; i++)
        FrutaInserida[i] = -1;

    //Arvore, usada pra verificar com a posicao em q ele coloca nas barracas
    CriaArvore(&ArvoreCerta);
    CriaArvore(&ArvoreJogador);

    //Seta a posição da personagem
    PersonagemSprite.setPosition(105,400);
}

bool Game::VerificaBotao(Sprite Sprite){
    //Pega a posição do mouse atual para verificar se pressionou os botões
    position = Mouse::getPosition(window);

    //Verifica posição
    int width = Sprite.getGlobalBounds().width;
    int height = Sprite.getGlobalBounds().height;

    if (position.x>Sprite.getPosition().x && position.x<(Sprite.getPosition().x + width)){
        if (position.y>Sprite.getPosition().y && position.y<(Sprite.getPosition().y + height)){
            return true;
        }
    }
    return false;
}

bool Game::AtualizaBotao(Sprite &Sprite){
    //Corta a imagem do botão
    rectSourceSprite = IntRect(0, 0, 201, 71);

    int flag = 0;

    if (Event.type == Event::MouseButtonPressed){
        if (Event.mouseButton.button == Mouse::Left){
            if(VerificaBotao(Sprite)){
                rectSourceSprite.top = 142;
                Sprite.setTextureRect(rectSourceSprite);
                flag = 1;
                return 1;
            }
        }
    }else if (Event.type == Event::MouseButtonReleased){
        if (Event.mouseButton.button == Mouse::Left){
            flag = 0;
            if(VerificaBotao(Sprite))
                rectSourceSprite.top = 74;
            else
                rectSourceSprite.top = 0;
        }
    }else if (Event.type == Event::MouseMoved){
        if(flag == 0){
            if(VerificaBotao(Sprite))
                rectSourceSprite.top = 74;
            else
                rectSourceSprite.top = 0;
        }
    }
    Sprite.setTextureRect(rectSourceSprite);
    return 0;
}

bool Game::AtualizaBotaoMenor(Sprite &Sprite){
    //Corta a imagem do botão
    rectSourceSprite2 = IntRect(0, 0, 102, 39);

    int flag = 0;

    if (Event.type == Event::MouseButtonPressed){
        if (Event.mouseButton.button == Mouse::Left){
            if(VerificaBotao(Sprite)){
                rectSourceSprite2.top = 78;
                Sprite.setTextureRect(rectSourceSprite2);
                flag = 1;
                return 1;
            }
        }
    }else if (Event.type == Event::MouseButtonReleased){
        if (Event.mouseButton.button == Mouse::Left){
            flag = 0;
            if(VerificaBotao(Sprite))
                rectSourceSprite2.top = 39;
            else
                rectSourceSprite2.top = 0;
        }
    }else if (Event.type == Event::MouseMoved){
        if(flag == 0){
            if(VerificaBotao(Sprite))
                rectSourceSprite2.top = 39;
            else
                rectSourceSprite2.top = 0;
        }
    }
    Sprite.setTextureRect(rectSourceSprite2);
    return 0;
}

void Game::CarregaImagens(){
    //*******************************Tela Menu
    //Cenario Menu
    CenarioMenuTexture.loadFromFile("Imagens/TelaMenu.png");
    CenarioMenuSprite.setTexture(CenarioMenuTexture);

    //Botão Jogar
    BotaoJogarTexture.loadFromFile("Imagens/BotaoJogar.png");
    BotaoJogarSprite = Sprite(BotaoJogarTexture, rectSourceSprite);
    BotaoJogarSprite.setPosition(20, 90);

    //Botão Instruções
    BotaoInstrucoesTexture.loadFromFile("Imagens/BotaoInstrucoes.png");
    BotaoInstrucoesSprite = Sprite(BotaoInstrucoesTexture, rectSourceSprite);
    BotaoInstrucoesSprite.setPosition(20, 170);

    //Botão Sair
    BotaoSairTexture.loadFromFile("Imagens/BotaoSair.png");
    BotaoSairSprite = Sprite(BotaoSairTexture, rectSourceSprite);
    BotaoSairSprite.setPosition(20, 250);

    //*******************************Tela Instruções
    //Cenário Instruções
    CenarioInstrucoesTexture.loadFromFile("Imagens/Instrucoes.png");
    CenarioInstrucoesSprite.setTexture(CenarioInstrucoesTexture);

    //Botão Voltar
    BotaoVoltarTexture.loadFromFile("Imagens/BotaoVoltar.png");
    BotaoVoltarSprite = Sprite(BotaoVoltarTexture, rectSourceSprite);
    BotaoVoltarSprite.setPosition(150, 515);

    //*******************************Tela Jogo
    //Cenário Jogo
    CenarioJogoTexture.loadFromFile("Imagens/TelaJogo.png");
    CenarioJogoSprite.setTexture(CenarioJogoTexture);

    //Personagem
    PersonagemTexture.loadFromFile("Imagens/Personagem.png");
    PersonagemSprite.setTexture(PersonagemTexture);
    PersonagemSprite.setScale(EscalaPersonagem, EscalaPersonagem);
    PersonagemSprite.setPosition(105,400);

    //Frutas
    //Auxiliares
    int j = 0;
    FrutaTexture.loadFromFile("Imagens/Frutas.png");
    for(int i=0; i<QuantidadeDeFrutas; i++){
        if(i < 10){
            rectSourceSpriteFruta = IntRect(64*i, 0, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
        }else if(i < 20){
            rectSourceSpriteFruta = IntRect(64*j, 64, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 30){
            if(i == 20)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 128, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 40){
            if(i == 30)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 192, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 50){
            if(i == 40)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 256, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 60){
            if(i == 50)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 320, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 70){
            if(i == 60)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 384, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 80){
            if(i == 70)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 448, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 90){
            if(i == 80)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 512, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }else if(i < 100){
            if(i == 90)
                j = 0;
            rectSourceSpriteFruta = IntRect(64*j, 576, 64, 64);
            FrutaSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaArvoreSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            FrutaAtualSprite[i] = Sprite(FrutaTexture, rectSourceSpriteFruta);
            j++;
        }
        FrutaSprite[i].setPosition(-30,0);
        FrutaArvoreSprite[i].setPosition(-30,0);
        FrutaAtualSprite[i].setPosition(367, 11);
        FrutaSprite[i].setScale(EscalaFruta, EscalaFruta);
        FrutaArvoreSprite[i].setScale(EscalaFruta, EscalaFruta);
    }

    //Lixeira
    LixeiraTexture.loadFromFile("Imagens/LixeiraInvisivel.png");
    LixeiraSprite.setTexture(LixeiraTexture);
    LixeiraSprite.setPosition(385, 125);

    //Barracas da árvore
    BarracaInvisivelTexture.loadFromFile("Imagens/BarracaInvisivel.png");
    for(int i = 0; i < 7; i++){
        switch(i){
        case 0:
            BarracaTexture[i].loadFromFile("Imagens/Barraca0.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(493, 130);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(508, 130);
            break;
        case 1:
            BarracaTexture[i].loadFromFile("Imagens/Barraca1.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(366, 270);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(381, 270);
            break;
        case 2:
            BarracaTexture[i].loadFromFile("Imagens/Barraca2.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(626, 270);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(641, 270);
            break;
        case 3:
            BarracaTexture[i].loadFromFile("Imagens/Barraca3.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(297, 442);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(312, 442);
            break;
        case 4:
            BarracaTexture[i].loadFromFile("Imagens/Barraca4.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(431, 442);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(446, 442);
            break;
        case 5:
            BarracaTexture[i].loadFromFile("Imagens/Barraca5.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(563, 442);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(578, 442);
            break;
        case 6:
            BarracaTexture[i].loadFromFile("Imagens/Barraca6.png");
            BarracaSprite[i].setTexture(BarracaTexture[i]);
            BarracaSprite[i].setPosition(695, 442);

            BarracaInvisivelSprite[i].setTexture(BarracaInvisivelTexture);
            BarracaInvisivelSprite[i].setPosition(710, 442);
            break;
        }
    }

    //Botão do aviso para inserir na árvore
    BotaoAvisoBarracaTexture.loadFromFile("Imagens/BotaoInserirFruta.png");
    BotaoAvisoBarracaSprite = Sprite(BotaoAvisoBarracaTexture, rectSourceSprite);

    //*******************************Situação Rotação
    //Aviso para rotacionar
    AvisoRotacaoTexture.loadFromFile("Imagens/AvisoRotacao.png");
    AvisoRotacaoSprite.setTexture(AvisoRotacaoTexture);
    AvisoRotacaoSprite.setPosition(0, 0);

    //Botão para rotacionar simples direita
    BotaoRotacaoDireitaTexture.loadFromFile("Imagens/BotaoRotacaoDireita.png");
    BotaoRotacaoDireitaSprite = Sprite(BotaoRotacaoDireitaTexture, rectSourceSprite);
    BotaoRotacaoDireitaSprite.setPosition(34, 258);

    //Botão para rotacionar dupla direita
    BotaoRotacaoDuplaDireitaTexture.loadFromFile("Imagens/BotaoRotacaoDuplaDireita.png");
    BotaoRotacaoDuplaDireitaSprite = Sprite(BotaoRotacaoDuplaDireitaTexture, rectSourceSprite);
    BotaoRotacaoDuplaDireitaSprite.setPosition(34, 338);

    //Botão para rotacionar simples esquerda
    BotaoRotacaoEsquerdaTexture.loadFromFile("Imagens/BotaoRotacaoEsquerda.png");
    BotaoRotacaoEsquerdaSprite = Sprite(BotaoRotacaoEsquerdaTexture, rectSourceSprite);
    BotaoRotacaoEsquerdaSprite.setPosition(34, 418);

    //Botão para rotacionar dupla esquerda
    BotaoRotacaoDuplaEsquerdaTexture.loadFromFile("Imagens/BotaoRotacaoDuplaEsquerda.png");
    BotaoRotacaoDuplaEsquerdaSprite = Sprite(BotaoRotacaoDuplaEsquerdaTexture, rectSourceSprite);
    BotaoRotacaoDuplaEsquerdaSprite.setPosition(34, 498);

    //*******************************Situação Game Over
    //Perdeu por inserir na posicao errada
    PerdeuPosicaoTexture.loadFromFile("Imagens/PerdeuPosicao.png");
    PerdeuPosicaoSprite.setTexture(PerdeuPosicaoTexture);

    //Perdeu por realizar rotacao errada
    PerdeuRotacaoTexture.loadFromFile("Imagens/PerdeuRotacao.png");
    PerdeuRotacaoSprite.setTexture(PerdeuRotacaoTexture);

    //Perdeu por inserir chave duplicada
    PerdeuChaveTexture.loadFromFile("Imagens/PerdeuChave.png");
    PerdeuChaveSprite.setTexture(PerdeuChaveTexture);

    //Perdeu por tempo limite
    PerdeuTempoTexture.loadFromFile("Imagens/PerdeuTempo.png");
    PerdeuTempoSprite.setTexture(PerdeuTempoTexture);

    //*******************************Situação Vitória
    //Ganhou inserindo todos os elementos da arvore corretamente
    GanhouTexture.loadFromFile("Imagens/Ganhou.png");
    GanhouSprite.setTexture(GanhouTexture);

    //Botão Jogar Novamente
    BotaoJogarNovamenteTexture.loadFromFile("Imagens/BotaoJogarNovamente.png");
    BotaoJogarNovamenteSprite.setTexture(BotaoJogarNovamenteTexture);
    BotaoJogarNovamenteSprite.setPosition(299, 319);
    AtualizaBotao(BotaoJogarNovamenteSprite);

    //*******************************Tempo
    TempoTexture.loadFromFile("Imagens/Tempo.png");

    int aux = 0;
    for(int j=0; j<10; j++){
        for(int i=0; i<10; i++){
            if(aux <=90){
                rectSourceSpriteTempo = IntRect(79*i, 64*j, 79, 64); //Corta a imagem
                TempoSprite[aux] = Sprite(TempoTexture, rectSourceSpriteTempo);
                TempoSprite[aux].setPosition(466,15);
                aux++;
            }
        }
    }

    //Som
    SomTexture.loadFromFile("Imagens/Som.png");
    SomSprite.setTexture(SomTexture);
    SomSprite.setPosition(735,13);
}

void Game::CarregaMusicas(){
    //Pegar Fruta
    PegarFrutaBuffer.loadFromFile("Sons/PegarFruta.wav");
    PegarFrutaSound.setBuffer(PegarFrutaBuffer);
    PegarFrutaSound.setVolume(100);

    //Colocar na árvore
    ColocaArvoreBuffer.loadFromFile("Sons/ColocaArvore.wav");
    ColocaArvoreSound.setBuffer(ColocaArvoreBuffer);
    ColocaArvoreSound.setVolume(100);

    //Jogar no lixo
    JogarLixoBuffer.loadFromFile("Sons/JogarLixo.wav");
    JogarLixoSound.setBuffer(JogarLixoBuffer);
    JogarLixoSound.setVolume(100);

    //Música de fundo
    FundoMusic.openFromFile("Sons/Jogo.wav");
    FundoMusic.setVolume(400);

    //Perdeu
    PerdeuBuffer.loadFromFile("Sons/Perdeu.wav");
    PerdeuSound.setBuffer(PerdeuBuffer);
    PerdeuSound.setVolume(100);

    //Ganhou
    GanhouBuffer.loadFromFile("Sons/Ganhou.wav");
    GanhouSound.setBuffer(GanhouBuffer);
    GanhouSound.setVolume(100);
}

void Game::JanelaEventos(){
    while (window.pollEvent(Event)){
        //Fecha a janela pelo X
        if(Event.type == Event::Closed){
            RemoverArvore(&ArvoreCerta);
            RemoverArvore(&ArvoreJogador);
            window.close();
        }
        //Fecha a janela pelo ESC
        if((Event.type == Event::KeyPressed) && (Event.key.code == Keyboard::Escape)){
            RemoverArvore(&ArvoreCerta);
            RemoverArvore(&ArvoreJogador);
            window.close();
        }
    }
}

void Game::MostraTempo(){
    int i = Tempo.asSeconds();

    if(Perdeu == 0 && Ganhou == 0){
        //Mostra imagem do tempo ao contrário
        VerificaTempo = i;
        if(i <= QuantidadeTempo){
            window.draw(TempoSprite[QuantidadeTempo-i]);
        }

        if(i == QuantidadeTempo){
            Perdeu = 4;
            FundoMusic.stop();
            PerdeuSound.play();
        }
    }else
        window.draw(TempoSprite[QuantidadeTempo-VerificaTempo]);
}

void Game::SorteiaFrutas(int Fruta){
    if(Inicio){
        do{
            FrutaCaindo[0] = rand() % QuantidadeDeFrutas;
            FrutaCaindo[1] = rand() % QuantidadeDeFrutas;
            FrutaCaindo[2] = rand() % QuantidadeDeFrutas;
            FrutaCaindo[3] = rand() % QuantidadeDeFrutas;
            FrutaCaindo[4] = rand() % QuantidadeDeFrutas;
            FrutaCaindo[5] = rand() % QuantidadeDeFrutas;
        }while(FrutaCaindo[0] == FrutaCaindo[1] || FrutaCaindo[0] == FrutaCaindo[2] || FrutaCaindo[0] == FrutaCaindo[3]
                || FrutaCaindo[0] == FrutaCaindo[4] || FrutaCaindo[0] == FrutaCaindo[5] || FrutaCaindo[1] == FrutaCaindo[2]
                || FrutaCaindo[1] == FrutaCaindo[3] || FrutaCaindo[1] == FrutaCaindo[4] || FrutaCaindo[1] == FrutaCaindo[5]
                || FrutaCaindo[2] == FrutaCaindo[3] || FrutaCaindo[2] == FrutaCaindo[4] || FrutaCaindo[2] == FrutaCaindo[5]
                || FrutaCaindo[3] == FrutaCaindo[4] || FrutaCaindo[3] == FrutaCaindo[5] || FrutaCaindo[4] == FrutaCaindo[5]);
    }else if (FrutaSprite[FrutaCaindo[Fruta]].getPosition().y >= AlturaTela){
        do{
            FrutaCaindo[Fruta] = rand() % QuantidadeDeFrutas;
        }while(FrutaCaindo[0] == FrutaCaindo[1] || FrutaCaindo[0] == FrutaCaindo[2] || FrutaCaindo[0] == FrutaCaindo[3]
                || FrutaCaindo[0] == FrutaCaindo[4] || FrutaCaindo[0] == FrutaCaindo[5] || FrutaCaindo[1] == FrutaCaindo[2]
                || FrutaCaindo[1] == FrutaCaindo[3] || FrutaCaindo[1] == FrutaCaindo[4] || FrutaCaindo[1] == FrutaCaindo[5]
                || FrutaCaindo[2] == FrutaCaindo[3] || FrutaCaindo[2] == FrutaCaindo[4] || FrutaCaindo[2] == FrutaCaindo[5]
                || FrutaCaindo[3] == FrutaCaindo[4] || FrutaCaindo[3] == FrutaCaindo[5] || FrutaCaindo[4] == FrutaCaindo[5]);
    }
}

void Game::CairFrutas(Sprite Sprite, int Fruta){
    //Quando for cair uma nova fruta
    if ((Sprite.getPosition().y >= AlturaTela) || Inicio){
        //Volta a printar a fruta na tela
        colisao[Fruta] = 0;

        //Começa mais em cima para dar para ver a peça caindo
        if(Inicio){
            PosicaoFruta[Fruta].y = PosicaoFrutaInicio[Fruta];
        }else
            PosicaoFruta[Fruta].y = 0;

        //Gera posição X da fruta
        PosicaoFruta[Fruta].x = rand() % (210);
    }
    PosicaoFruta[Fruta].y += VelocidadeSprite;
}

void Game::MovimentoPersonagem(){
    DeltaPersonagem = clockPersonagem.restart().asSeconds();

    //Movimenta para a esquerda
    if(Keyboard::isKeyPressed(Keyboard::Left)){
        //Verifica se a personagem está no fim da tela
        if(PersonagemSprite.getPosition().x > 0) {
            AtualizaPersonagem.y = 2;
            PersonagemSprite.move(-VelocidadePersonagemEixoX.x*DeltaPersonagem,VelocidadePersonagemEixoX.y);
        }
    }
    //Movimenta para a direita
    else if (Keyboard::isKeyPressed(Keyboard::Right)){
        //Verifica se não está no fim da tela
        if(PersonagemSprite.getPosition().x < LarguraTela - LarguraPersonagem) {
            AtualizaPersonagem.y = 1;
            PersonagemSprite.move(+VelocidadePersonagemEixoX.x*DeltaPersonagem,VelocidadePersonagemEixoX.y);
        }
    }
    //Movimenta para cima
    else if(Keyboard::isKeyPressed(Keyboard::Up)){
        //Verifica se não está no fim da tela
        if(PersonagemSprite.getPosition().y >= 161 - AlturaPersonagem){
            AtualizaPersonagem.y = 0;
            PersonagemSprite.move(VelocidadePersonagemEixoY.x,-VelocidadePersonagemEixoY.y*DeltaPersonagem);
        }
    }
    //Movimenta para baixo
    else if(Keyboard::isKeyPressed(Keyboard::Down)){
        //Verifica se não está no fim da tela
        if(PersonagemSprite.getPosition().y < AlturaTela - AlturaPersonagem){
            AtualizaPersonagem.y = 3;
            PersonagemSprite.move(VelocidadePersonagemEixoY.x,+VelocidadePersonagemEixoY.y*DeltaPersonagem);
        }
    }

    //Verifica se e qual botão do movimento da personagem está sendo pressionada para que altere sua imagem
    if((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right) ||
       Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Up))){
        //Atualiza as imagens do eixo x
        AtualizaPersonagem.x++;
        //Verifica se as imagens do eixo x acabaram
        if(AtualizaPersonagem.x*LarguraPersonagem >= LarguraPersonagem*3)
            AtualizaPersonagem.x = 0;
    }else
        AtualizaPersonagem.x = 0;

    //Realiza a alteração da imagem da personagem dependendo do lado para qual está indo
    PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*LarguraPersonagem, AtualizaPersonagem.y*AlturaPersonagem, LarguraPersonagem, AlturaPersonagem));
}

//Verifica se colidiu
int Game::Colisao(Sprite Sprite){
    if(PersonagemSprite.getGlobalBounds().intersects(Sprite.getGlobalBounds())){
        return 1;
    }else
        return 0;
}

//Para a personagem para não ultrapassar objetos
void Game::ColisaoObjeto(Sprite Sprite){
    if(Colisao(Sprite)){
        //Seta a posicao do personagem
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            PersonagemSprite.move(+VelocidadePersonagemEixoX.x*DeltaPersonagem,VelocidadePersonagemEixoX.y);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            PersonagemSprite.move(-VelocidadePersonagemEixoX.x*DeltaPersonagem,VelocidadePersonagemEixoX.y);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            PersonagemSprite.move(VelocidadePersonagemEixoY.x,+VelocidadePersonagemEixoY.y*DeltaPersonagem);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            PersonagemSprite.move(VelocidadePersonagemEixoY.x,-VelocidadePersonagemEixoY.y*DeltaPersonagem);
    }
}

//Joga a fruta atual fora
void Game::ColisaoLixeira(){
    if(Colisao(LixeiraSprite)){ //Verifica se colidiu
        ColisaoObjeto(LixeiraSprite); //Para não passar por cima
        if(FrutaAtual.Chave != -1){ //Atualiza as variaveis para pegar fruta
            JogarLixoSound.play();
            FrutaAtual.Chave = -1;
            Colidiu = false;
        }
    }
}

void Game::AtualizaArvoreJogador(){
    RemoverArvore(&ArvoreJogador);
    CopiaArvore(&ArvoreCerta, &ArvoreJogador);
    Rotacao = -1;
    VelocidadePersonagemEixoX.x = 180;
    VelocidadePersonagemEixoY.y = 180;
}

void Game::ComparaArvore(){
    if(SaoIguais(ArvoreCerta, ArvoreJogador)){
        if(FrutaInserida[0] != -1 && FrutaInserida[1] != -1 && FrutaInserida[2] != -1 && FrutaInserida[3] != -1 &&
           FrutaInserida[4] != -1 && FrutaInserida[5] != -1 && FrutaInserida[6] != -1){
                if (!Ganhou){
                    FundoMusic.stop();
                    GanhouSound.play();
                }
                Ganhou = 1;
           }
    }
    //Terceiro caso: Precisa realizar qualquer tipo de rotação
    else if(Rotacao != -1){
        //Faz com que a personagem não ande mais
        Jogar = false;

        //Faz com que a personagem fica virada para frente
        //Atualiza imagem do personagem
        AtualizaPersonagem.x = 0;
        AtualizaPersonagem.y = 1;
        //Realiza a alteração da imagem da personagem dependendo do lado para qual está indo
        PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*LarguraPersonagem, AtualizaPersonagem.y*AlturaPersonagem, LarguraPersonagem, AlturaPersonagem));

        if(AtualizaBotao(BotaoRotacaoDireitaSprite)){
            //Rotação 0: Rotação Simples Direita
            if(Rotacao == 0){
                ColocaArvoreSound.play();
                //Seta a imagem da fruta de acordo com a rotação
                AtualizaArvoreJogador();
                FrutaInserida[2] = FrutaInserida[0];
                FrutaInserida[0] = FrutaInserida[1];
                FrutaInserida[1] = FrutaInserida[3];
                FrutaInserida[3] = -1;
                JaInseriu[3] = 0;
                JaInseriu[2] = 1;
                Jogar = true;
            }else{
                Rotacao = -1;
                Perdeu = 2;
                FundoMusic.stop();
                PerdeuSound.play();
            }
        }


        if(AtualizaBotao(BotaoRotacaoDuplaDireitaSprite)){
            //Rotação 1: Rotação Dupla Direita
            if(Rotacao == 1){
                ColocaArvoreSound.play();
                //Seta a imagem da fruta de acordo com a rotação
                AtualizaArvoreJogador();
                FrutaInserida[2] = FrutaInserida[0];
                FrutaInserida[0] = FrutaInserida[4];
                FrutaInserida[4] = -1;
                JaInseriu[4] = 0;
                JaInseriu[2] = 1;
                Jogar = true;
            }else{
                Rotacao = -1;
                Perdeu = 2;
                FundoMusic.stop();
                PerdeuSound.play();
            }
        }

        if(AtualizaBotao(BotaoRotacaoEsquerdaSprite)){
            //Rotação 2: Rotação Simples Esquerda
            if(Rotacao == 2){
                ColocaArvoreSound.play();
                //Seta a imagem da fruta de acordo com a rotação
                AtualizaArvoreJogador();
                FrutaInserida[1] = FrutaInserida[0];
                FrutaInserida[0] = FrutaInserida[2];
                FrutaInserida[2] = FrutaInserida[6];
                FrutaInserida[6] = -1;
                JaInseriu[6] = 0;
                JaInseriu[1] = 1;
                Jogar = true;
            }else{
                Rotacao = -1;
                Perdeu = 2;
                FundoMusic.stop();
                PerdeuSound.play();
            }
        }

        if(AtualizaBotao(BotaoRotacaoDuplaEsquerdaSprite)){
            //Rotação 3: Rotação Dupla Esquerda
            if(Rotacao == 3){
                ColocaArvoreSound.play();
                //Seta a imagem da fruta de acordo com a rotação
                AtualizaArvoreJogador();
                FrutaInserida[1] = FrutaInserida[0];
                FrutaInserida[0] = FrutaInserida[5];
                FrutaInserida[5] = -1;
                JaInseriu[5] = 0;
                JaInseriu[1] = 1;
                Jogar = true;
            }else{
                Rotacao = -1;
                Perdeu = 2;
                FundoMusic.stop();
                PerdeuSound.play();
            }
        }
    }else if(!Perdeu){
        Perdeu = 1;
        FundoMusic.stop();
        PerdeuSound.play();
    }
}

void Game::ColisaoArvore(){
    for(int i = 0; i < 7; i++){
        if(Colisao(BarracaInvisivelSprite[i])) //Verifica se colidiu
            ColisaoObjeto(BarracaInvisivelSprite[i]); //Para não passar por cima

        //Para inserir na arvore
        if(Colisao(BarracaSprite[i])){
            //Verifica se o botão para inserir foi pressionado, se sim atualiza realiza a insercao na arvore
            if(BotaoInserirArvore && FrutaAtual.Chave != -1){ //Só entra quando o botao de inserir for pressionado
                //Atualiza as variaveis auxiliares de colisão
                colisao[FrutaPosicaoAtual] = 0;
                Colidiu = false;

                //Tem que realizar a inserção na árvore e comparar se é uma inserção válida
                //Insere da forma correta na arvore para usar como comparação
                //Primeiro caso: já tem uma fruta com o a mesma chave na arvore
                if(Pesquisa(&ArvoreCerta, FrutaAtual.Chave) != -1){
                    FrutaAtual.Chave = -1;
                    Perdeu = 3; //Perdeu por chave
                    FundoMusic.stop();
                    PerdeuSound.play();
                }
                //Se não, insere na arvore
                else{//Segundo caso: Posicao errada, se inseriu, verifica se está na posicao certa
                    InsereArvore(&ArvoreCerta, FrutaAtual, &Rotacao);
                    InsereJogador(&ArvoreJogador, FrutaAtual, PosicaoInsereArvore);
                    FrutaAtual.Chave = -1;
                }
            }
        }
    }
}

void Game::DesenhaArvore(){
    //Verifica se o botão de inserir na arvore foi pressionado
    if(AtualizaBotaoMenor(BotaoAvisoBarracaSprite) && FrutaAtual.Chave != -1){
        BotaoInserirArvore = true;
        ColocaArvoreSound.play();

        //Seta a posição da fruta de acordo com a barraca em que desejou inserir
        switch(PosicaoInsereArvore){
            case 0:
                JaInseriu[0] = 1;
                FrutaInserida[0] = FrutaAtual.Chave;
                break;
            case 1:
                JaInseriu[1] = 1;
                FrutaInserida[1] = FrutaAtual.Chave;
                break;
            case 2:
                JaInseriu[2] = 1;
                FrutaInserida[2] = FrutaAtual.Chave;
                break;
            case 3:
                JaInseriu[3] = 1;
                FrutaInserida[3] = FrutaAtual.Chave;
                break;
            case 4:
                JaInseriu[4] = 1;
                FrutaInserida[4] = FrutaAtual.Chave;
                break;
            case 5:
                JaInseriu[5] = 1;
                FrutaInserida[5] = FrutaAtual.Chave;
                break;
            case 6:
                JaInseriu[6] = 1;
                FrutaInserida[6] = FrutaAtual.Chave;
                break;
        }
    }else
        BotaoInserirArvore = false;

    for(int i=0; i<7; i++){
        if(JaInseriu[i]){
            if(i == 0){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(516, 153);
            }else if(i == 1){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(389, 293);
            }else if(i == 2){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(649, 293);
            }else if(i == 3){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(320, 465);
            }else if(i == 4){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(454, 465);
            }else if(i == 5){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(586, 465);
            }else if(i == 6){
                FrutaArvoreSprite[FrutaInserida[i]].setPosition(718, 465);
            }

            window.draw(FrutaArvoreSprite[FrutaInserida[i]]);
        }
    }
}

void Game::FimDeJogo(){
    Reset = AtualizaBotao(BotaoJogarNovamenteSprite);

    //Faz com q a personagem não ande
    Jogar = false;

    //Faz com que a personagem fica virada para frente
    //Atualiza imagem do personagem
    AtualizaPersonagem.x = 0;
    AtualizaPersonagem.y = 1;
    //Realiza a alteração da imagem da personagem dependendo do lado para qual está indo
    PersonagemSprite.setTextureRect(sf::IntRect(AtualizaPersonagem.x*LarguraPersonagem, AtualizaPersonagem.y*AlturaPersonagem, LarguraPersonagem, AlturaPersonagem));

    window.draw(BotaoJogarNovamenteSprite);
}

void Game::CenarioMenu(){
    //Verifica Botão
    if(AtualizaBotao(BotaoJogarSprite)){
        TelaMenu = 0;
        TelaJogo = 1;
    }else if(AtualizaBotao(BotaoInstrucoesSprite)){
        TelaMenu = 0;
        TelaInstrucoes = 1;
    }else if(AtualizaBotao(BotaoSairSprite)){
        window.close();
    }

    window.clear();
    window.draw(CenarioMenuSprite);
    window.draw(BotaoJogarSprite);
    window.draw(BotaoInstrucoesSprite);
    window.draw(BotaoSairSprite);
    window.display();

    //Delay para aparecer a imagem do botão pressionado
    sleep(delay);
}

void Game::CenarioInstrucoes(){
    if(AtualizaBotao(BotaoVoltarSprite)){
        TelaInstrucoes = 0;
        TelaMenu = 1;
    }

    window.clear();
    window.draw(CenarioInstrucoesSprite);
    window.draw(BotaoVoltarSprite);
    window.display();

    //Delay para aparecer a imagem do botão pressionado
    sleep(delay);
}

void Game::CenarioJogo(){
    if(!FundoMusic.getStatus() && !Ganhou && !Perdeu)
        FundoMusic.play();

    if(Inicio)
        Relogio.restart();

    Tempo = Relogio.getElapsedTime();

    //Faz com que caia continuamente 6 frutas
    for(int i = 0; i < 6; i++){
        SorteiaFrutas(i);
        CairFrutas(FrutaSprite[FrutaCaindo[i]], i);
        FrutaSprite[FrutaCaindo[i]].setPosition(PosicaoFruta[i].x, PosicaoFruta[i].y);
    }

    if(Jogar)
        MovimentoPersonagem();
    ColisaoLixeira();
    ColisaoArvore();

    window.clear();
    window.draw(CenarioJogoSprite);

    for(int i = 0; i < 7; i++)
        window.draw(BarracaSprite[i]);

    window.draw(PersonagemSprite);
    window.draw(LixeiraSprite);

    for(int i = 0; i < 6; i++){
        if(!Colisao(FrutaSprite[FrutaCaindo[i]])){
            if(colisao[i] == 0)
                window.draw(FrutaSprite[FrutaCaindo[i]]);
        }else{
            if(Colidiu == false){
                PegarFrutaSound.play();
                colisao[i] = 1;
                Colidiu = true;
                FrutaAtual.Chave = FrutaCaindo[i];
                FrutaPosicaoAtual = i;
            }else if(colisao[i] == 0)
                window.draw(FrutaSprite[FrutaCaindo[i]]);
        }
    }

    //Aparece a imagem da fruta que está segurando atualmente
    if(Colidiu){
        window.draw(FrutaAtualSprite[FrutaAtual.Chave]);
    }

    //Mostra uma mensagem para verificar se quer colocar a fruta na árvore
    for(int i = 0; i < 7; i++){
        if(Colisao(BarracaSprite[i]) && !JaInseriu[i]){ //Verifica se colidiu e se nao está inserido nessa posição
            if(i == 0){
                BotaoAvisoBarracaSprite.setPosition(482, 89);
            }else if(i == 1){
                BotaoAvisoBarracaSprite.setPosition(355, 228);
            }else if(i == 2){
                BotaoAvisoBarracaSprite.setPosition(614, 228);
            }else if(i == 3){
                BotaoAvisoBarracaSprite.setPosition(283, 400);
            }else if(i == 4){
                BotaoAvisoBarracaSprite.setPosition(420, 400);
            }else if(i == 5){
                BotaoAvisoBarracaSprite.setPosition(551, 400);
            }else if(i == 6){
                BotaoAvisoBarracaSprite.setPosition(682, 400);
            }

            window.draw(BotaoAvisoBarracaSprite);
            PosicaoInsereArvore = i;
        }
    }

    //Se tiver que rotacionar, mostra os botões para selecionar a rotacao
    if(Rotacao != -1){
        window.draw(AvisoRotacaoSprite);
        window.draw(BotaoRotacaoDireitaSprite);
        window.draw(BotaoRotacaoDuplaDireitaSprite);
        window.draw(BotaoRotacaoEsquerdaSprite);
        window.draw(BotaoRotacaoDuplaEsquerdaSprite);
    }

    //Verifica se as arvores são iguais e realiza as rotações necessárias
    ComparaArvore();

    //Depois do botão para já verificar se o botão foi pressionado
    DesenhaArvore();

    MostraTempo();

    // window.draw(SomSprite);

    //Verifica se perdeu ou ganhou
    if(Ganhou){
        window.draw(GanhouSprite);
        FimDeJogo();
    }else if(Perdeu == 1){
        window.draw(PerdeuPosicaoSprite);
        FimDeJogo();
    }else if(Perdeu == 2){
        window.draw(PerdeuRotacaoSprite);
        FimDeJogo();
    }else if(Perdeu == 3){
        window.draw(PerdeuChaveSprite);
        FimDeJogo();
    }else if(Perdeu == 4){
        window.draw(PerdeuTempoSprite);
        FimDeJogo();
    }

    window.display();

    Inicio = 0;
}

void Game::Controle(){
    srand(time(NULL));
    //Abre a janela .exe 800x600
    window.create(VideoMode(LarguraTela, AlturaTela), "Jogo", Style::None);
    window.setFramerateLimit(60); //Setar velocidade para qualquer computador

    //Carrega imagens
    CarregaImagens();
    CarregaMusicas();

    while(window.isOpen()){
        JanelaEventos();

        if(Reset){
            //Delay para aparecer a imagem do botão pressionado
            sleep(delay);
            RemoverArvore(&ArvoreCerta);
            RemoverArvore(&ArvoreJogador);
            Reseta();
        }else if(TelaMenu)
            CenarioMenu();
        else if(TelaInstrucoes)
            CenarioInstrucoes();
        else if(TelaJogo)
            CenarioJogo();
    }
}
