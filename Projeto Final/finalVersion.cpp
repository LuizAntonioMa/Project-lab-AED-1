#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <time.h>

// define getmaxwidth() como XMAX
#define XMAX getmaxwidth()
// define getmaxheight() como YMAX
#define YMAX getmaxheight()

typedef struct // cria tipo candidato - variave�s nome, votos e arquivo foto
{
    char n[40];
    int v;
    char j[40];
} candidato;



//coordenadas das fotos
//primeira foto
int left1 = XMAX/16, top1 = YMAX/16, primeirax2 = 3*XMAX/16, primeiray2 = (YMAX/16)+(22*XMAX/128);
//segunda foto
int left2 = 4*XMAX/16, top2 = YMAX/16, segundax2 = 6*XMAX/16, segunday2 = (YMAX/16)+(22*XMAX/128);
//terceira foto
int left3 = 7*XMAX/16, top3 = YMAX/16, terceirax2 = 9*XMAX/16, terceiray2 = (YMAX/16)+(22*XMAX/128);
//quarta foto
int left4 = 10*XMAX/16, top4 = YMAX/16, quartax2 = 12*XMAX/16, quartay2 = (YMAX/16)+(22*XMAX/128);
//quinta foto
int left5 = 13*XMAX/16, top5 = YMAX/16, quintax2 = 15*XMAX/16, quintay2 = (YMAX/16)+(22*XMAX/128);

// estado = qual candidado voce clicou, tela que esta que esta, vencedores P = empresas e F = jogos
int estado=-1, tela=1, vencedorF, vencedorP;
// grau de cada candidato jogo no grafico pizza
int pizzaF[6];
// grau de cada candidato empresa no grafico pizza
int pizzaP[6];
// porcentagem de cada candidato jogo no total de votos
float porcentagemF[6];
// porcentagem de cada candidato empresa no total de votos
float porcentagemP[6];
int i=0;
int graus=360;
//cor do grafico de pizza
int c=0;
//para guardar quantos graus foram usados para o grafico de pizza jogo
int grausF=0;
//para guardar quantos graus foram usados para o grafico de pizza empresa
int grausP=0;
// branco para vota��o de jogos e empresas
float brancoP=0, brancoF=0;
// total de votos
float total=0;
// vetores de strings e strings para receber os graus de float para string, dos graus do vetor de jogos, empresas e os brancos dos jogos e empresas
char porcentoF[5][6] , porcentoP[5][6], brancoPorcentoF[6], brancoPorcentoP[6];
float radianoCentral, seno, cosseno;
int x, y;
int clicado=0;
int aumentado;

// cria os candidatos jogo
candidato f[5] = {"Skyrim", 0, "Skyrim.jpeg",
                  "God of War Ragnarok", 0, "God of War Ragnarok.jpeg",
                  "Halo Infinite", 0, "halo infinite.jpg",
                  "Forza Horizon 5", 0, "Forza Horizon 5.jpeg",
                  "Assassin's Creed Valhalla", 0, "Assassin's Creed Valhalla.jpeg"};

// cria os candidatos empresa
candidato g[5] = {"Bethesda", 0,"bethesda.jpg",
                  "Santa Monica Studio", 0,"santa monica.jpg",
                  "343 Industries", 0,"343.jfif",
                  "Playground Games", 0,"Playground Games.jpeg",
                  "Ubisoft", 0,"Ubisoft.jpeg"};

//cria uma fun��o imagem, que recebe as coordenadas x e y, e o nome do arquivo
void imagem(int top, int left, char arquivo[50]);
//fun��o clique coordena todas as intera��es na tela, recebe estado, total, tela, voto e votos branco
void clique(int *e, float *t, int *s, int *v, int *clicado, float *branco);
// apura��o dos votos do vetor de candidadtos e seu tamanho
int apuracao(candidato f[], int tamanho);
// fun��o para apagar palavra ap�s o clique da imagem
void apagapalavra();
// fun��o que cria um bot�o, recebe as coordenadas(x, y), a cor e o nome dentro do bot�o
void botao(int x1, int y1, int cor, char nome[15]);
// fun��o para simular a vota��o
void simular(int *f1, int *f2, int *f3, int *f4, int *f5, float *fb, int *p1, int *p2, int *p3, int *p4, int *p5, float *pb, float *soma);
// fun��o que coloca o titulo da foto
void titulo(char titulo[40], int left, int top);
// fun��o para imprimir o texto centralizado no texto
void texto(char texto[80]);
void imagemEmpresa(int left, int top, char arquivo[50]);
void apagarImagem(int left, int top);
void diminuirAumentar();

main()
{

  // padroniza o portugu�s como l�ngua usada no c�digo
  setlocale(LC_ALL,"portuguese");

  // iniciar a janela do projeto
  initwindow (XMAX,YMAX,"Project Lab AED-1",0,0);
  // configura a cor do fundo em branco da janela
  setbkcolor(15);

  // enquanto a tela for diferente de 3, continua o loop
  while(tela!=3)
  {
    // se estiver na tela 1, executa as instru��es abaixo, tela 1 = tela de jogos
    if(tela == 1){
        // limpa a tela quando inicia a tels
        cleardevice();

        imagemEmpresa(left1, top1+(YMAX/8), g[0].j);
        imagemEmpresa(left2, top2+(YMAX/8), g[1].j);
        imagemEmpresa(left3, top3+(YMAX/8), g[2].j);
        imagemEmpresa(left4, top4+(YMAX/8), g[3].j);
        imagemEmpresa(left5, top5+(YMAX/8), g[4].j);

        // configura uma cor padr�o para as palavras
        setcolor(0);

        // titulo da foto 1
        titulo(g[0].n, left1, top1-(YMAX/32));
        // titulo da foto 2
        titulo(g[1].n, left2, top2-(YMAX/32));
        // titulo da foto 3
        titulo(g[2].n, left3, top3-(YMAX/32));
        // titulo da foto 4
        titulo(g[3].n, left4, top4-(YMAX/32));
        // titulo da foto 5
        titulo(g[4].n, left5, top5-(YMAX/32));

        // cria o bot�o confirmar o voto
        botao(7*XMAX/16, 22*YMAX/32, 10, "Confirma");
        // cria o bot�o de voto em branco
        botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
        // cria o bot�o de resultado da vota��o, indo para a tela 3
        botao(13*XMAX/16, 14*YMAX/16, 12, "Resultado");
        // cria o bot�o simular a vota��o
        botao(1*XMAX/16, 14*YMAX/16, 9, "Simular");

        // titulo no topo da janela para o usu�rio escolher o candidato
        outtextxy((XMAX/2)-140, YMAX/32, "Escolha sua empresa de jogos preferida:");

        // cria um loop na tela 1 para as instru��es a seguir
        while(tela==1)
        {
          // se voce clicar com o mouse, entra na condi��o
          if (ismouseclick(WM_LBUTTONDOWN))
          {
            // verifica onde o clique do mouse aconteceu, recebe a tela, o candidato que clicou, os votos do candidato e os votos em branco
            clique(&estado, &total, &tela, &g[estado].v, &clicado, &brancoP);
            // limpa o clique do mouse
            clearmouseclick(WM_LBUTTONDOWN);
          }
        }
    } //  fecha a condi��o de estar na tela 1
    // condi��o para entra na tela 2 = tela de empresas
    if(tela==2)
    {
      // limpa a tela da janela
      cleardevice();

      // configura a foto 1 na tela
      imagem(left1, top1, f[0].j);
      // configura a foto 2 na tela
      imagem(left2, top2, f[1].j);
      // configura a foto 3 na tela
      imagem(left3, top3, f[2].j);
      // configura a foto 4 na tela
      imagem(left4, top4, f[3].j);
      // configura a foto 5 na tela
      imagem(left5, top5, f[4].j);

      // configuar a cor dos textos
      setcolor(0);

      // cria a legenda do texto da foto 1
      titulo(f[0].n, left1, top1);
      // cria a legenda do texto da foto 2
      titulo(f[1].n, left2, top2);
      // cria a legenda do texto da foto 3
      titulo(f[2].n, left3, top3);
      // cria a legenda do texto da foto 4
      titulo(f[3].n, left4, top4);
      // cria a legenda do texto da foto 5
      titulo(f[4].n, left5, top5);

      // cria o bot�o para confirmar o voto
      botao(7*XMAX/16, 22*YMAX/32, 10, "Confirma");
      // bota� para voto em branc0
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");

      // texto para o usu�rio escolher o seu candidato
      outtextxy((XMAX/2)-80, YMAX/32, "Escolha seu jogo preferido:");

        // cria um loop na tela 2 para as instru��es a seguir
      while(tela==2)
      {
        // se voce clicar com o mouse, entra na condi��o
        if (ismouseclick(WM_LBUTTONDOWN))
        {
          // verifica onde o clique do mouse aconteceu, recebe a tela, o candidato que clicou, os votos do candidato e os votos em branco
          clique(&estado, &total, &tela, &f[estado].v, &clicado, &brancoF);
          // limpa o clique o mouse
          clearmouseclick(WM_LBUTTONDOWN);
        }
      } // fecha o while( tela = 2)
    } // fecha a condi��o da tela 2
  }// fecha o loop do while( tela != 3)
    // condi��o para entrar na tela 3 = tela de resultado
    if(tela == 3){
      // limpa a janela
      cleardevice();

      // vencedor dos jogos recebe o indice do vencedor dos jogos
      vencedorF = apuracao(f, 5);
      // vencedor das empresas recebe o indice do vencedor das empresas
      vencedorP = apuracao(g, 5);

      // configuar a cor dos textos
      setcolor(0);
      // cria um retangulo para dividir a tela, -1 para n�o aparecer na tela
      rectangle(0, -1, XMAX/2, YMAX);

      //cria um texto para apresentar o vencedor dos jogos
      outtextxy((XMAX/4)-180, YMAX/16, "A empresa vencedora é:");
      // apresenta o nome do jogo vencedor
      titulo(g[vencedorP].n, 3*XMAX/16, 2*YMAX/16);
      // apresenta a imagem do jogo vencedor
      imagemEmpresa(3*XMAX/16, 4*YMAX/16, g[vencedorP].j);

      //cria um texto para apresentar o vencedor das empresas
      outtextxy((3*XMAX/4)-90, YMAX/16, "O jogo vencedor é:");
      // apresenta o nome da empresa vencedor
      titulo(f[vencedorF].n, 11*XMAX/16, 2*YMAX/16);
      // apresenta a imagem da empresa vencedor
      imagem(11*XMAX/16, 2*YMAX/16, f[vencedorF].j);

      // cria o bot�o para a apresentar as estatisticas do votos em um grafico na tela 4
      botao(7*XMAX/16, 12*YMAX/16, 12, "Estatísticas");
    }
      while(tela==3)
      {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
          clique(&estado, &total, &tela, &f[estado].v, &clicado, &brancoP);
          clearmouseclick(WM_LBUTTONDOWN);
        }
      }
    // condi��o para ir a tela 4, tela 4 = tela das estatisticas
    if( tela == 4){
      // loop para configurar a porcentagem dos votos de cada candidato de acordo com o total de votos
      for(i=0; i < 5; i++)
      {
        // recebe o calculo da porcentagem pela quantidade de votos do candidato jogo na posi��o i * 100 e dividi pelo total de votos dos jogos, atribuindo ao
        // valor na posi��o i do vetor de porcentagens para jogos
        porcentagemF[i] = (100*f[i].v)/total;
        // recebe o calculo da porcentagem pela quantidade de votos do candidato empresa na posi��o i * 100 e dividi pelo total de votos da empresa, atribuindo ao
        // valor na posi��o i do vetor de porcentagens para empresas
        porcentagemP[i] = (100*g[i].v)/total;
        // apresenta na sa�da padr�o o indice i e a porcentagen do valor na posi��o i no vetor de jogos
        printf("%d %f\n", i, porcentagemF[i]);
        // apresenta na sa�da padr�o o indice i e a porcentagen do valor na posi��o i no vetor de empresas
        printf("%d %f\n\n", i, porcentagemP[i]);
      }
      // loop para criar os graficos de pizzas dos jogos e empresas baseado nas porcentagens de cada candidato
      for(i=0; i<5; i++)
      {
        // recebe os graus na posi��o i pelo calculo para descobrir os graus usando a porcentagem do candidato jogo
        pizzaF[i] = floor((360*porcentagemF[i])/100);
        // recebe os graus na posi��o i pelo calculo para descobrir os graus usando a porcentagem do candidato empresa
        pizzaP[i] = floor((360*porcentagemP[i])/100);
        // apresenta na sa�da padr�o o indice i e os graus do valor na posi��o i no vetor de jogos
        printf("%d %d\n", i, pizzaF[i]);
        // apresenta na sa�da padr�o o indice i e os graus do valor na posi��o i no vetor de empresas
        printf("%d %d\n\n", i, pizzaP[i]);
      }

      // atribui a porcentagem arredondada para cima pela regra de tr�s entre a quantidade votos do branco de jogos com o total
      brancoP = ceil((100*brancoP)/total);
      // apresenta na sa�da de padr�o a porcentagem de votos do branco de jogos
      printf("brancoP = %f\n", brancoP);
      // atribui os graus ao votos em branco de jogos arredondando para cima usando a porcentagem
      brancoP = ceil((360*brancoP)/100);

      // atribui a porcentagem arredondada para cima pela regra de tr�s entre a quantidade votos do branco de empresas com o total
      brancoF = ceil((100*brancoF)/total);
      // apresenta na sa�da de padr�o a porcentagem de votos do branco de empresas
      printf("brancoF = %f\n\n", brancoF);
      // atribui os graus ao votos em branco de empresas arredondando para cima usando a porcentagem
      brancoF = ceil((360*brancoF)/100);

      // apresnta na sa�da padr�o o total de votos
      printf("\n%d\n", total);

      // limpa a tela da janela
      cleardevice();
      // configura um estilo padr�o e a cor
      setfillstyle(1,9);
      // desenhar o pimeiro peda�o do grafico pizza do primeiro valor do vetor de graus dos candidatos de jogos, em que se inicia no 0 e vai at� os graus do valor na 1� posi��o
      if(porcentagemP[0] != 0)
      pieslice(XMAX/4, 5*YMAX/16, 0, pizzaP[0], 100);
      // desenhar o pimeiro peda�o do grafico pizza do primeiro valor do vetor de graus dos candidatos de empresas, em que se inicia no 0 e vai at� os graus do valor na 1� posi��o
      if(porcentagemF[0] != 0)
      pieslice(3*XMAX/4, 5*YMAX/16, 0, pizzaF[0], 100);

      // loop para desenhar o resto das por��es nos graficos dos candidatos jogos e empresas
      for(i=1, c=10;i<5;i++, c++)
        {
          // paroniza um estilo e cor
          setfillstyle(1, c);
          // condi��o para desenhar a por��o no grafico de pizza dos jogos, caso se os graus na posi��o i for diferente de 0, entra na condi��o
          if(porcentagemF[i] != 0)
          {
            // desenha a por��o da pizzados jogos do candidato na posi��o i a partir da pos 1, em que a partir de 1, os graus iram do grau anterior i -1 at� o o grau i
            pieslice(3*XMAX/4, 5*YMAX/16, grausF + pizzaF[i-1], grausF + pizzaF[i-1] + pizzaF[i], 100);
            // soma os graus dos valores nas posi��es i - 1 para depois apresentar para o grafico de jogos
            grausF = grausF + pizzaF[i-1];
          }
          // condi��o para desenhar a por��o no grafico de pizza das empresas, caso se os graus na posi��o i for diferente de 0, entra na condi��o
          if(porcentagemP[i] != 0)
          {
            // desenha a por��o da pizza das empresas do candidato na posi��o i a partir da pos 1, em que a partir de 1, os graus iram do grau anterior i -1 at� o o grau i
            pieslice(XMAX/4, 5*YMAX/16, grausP + pizzaP[i-1], grausP + pizzaP[i-1] + pizzaP[i], 100);
            // soma os graus dos valores nas posi��es i - 1 para depois apresentar para o grafico de empresas
            grausP = grausP + pizzaP[i-1];
          }
        }

      setfillstyle(1, 15);
      // condi��o para criar a por��o do gr�fico de empresas dos votos em branco
      if(brancoP != 0)
        // apresenta a por��o usando o grau do ultimo candidato at� o inicio da pizza
        pieslice(XMAX/4, 5*YMAX/16, grausP + pizzaP[4], 0, 100);
        // apresenta na sa�da padr�o o valor do ultimo grau
        printf("\n\ngrausP = %d\n\n", grausP + pizzaP[4]);
      // condi��o para criar a por��o do gr�fico de jogos dos votos em branco
      if(brancoF != 0)
        // apresenta a por��o usando o grau do ultimo candidato at� o inicio da pizza
        pieslice(3*XMAX/4, 5*YMAX/16, grausF + pizzaF[4], 0, 100);

      sprintf(porcentoF[0], "%2.1f", porcentagemF[0]);
      sprintf(porcentoP[0], "%2.1f", porcentagemP[0]);
      if(strlen(porcentoF[0]) < 4){
            porcentoF[0][4] = '\%';
            porcentoF[0][5] = '\0';
        }
      else if(strlen(porcentoF[0]) >= 4){
            porcentoF[0][5] = '\%';
            porcentoF[0][6] = '\0';
        }
        if(strlen(porcentoP[0]) < 4){
            porcentoP[0][4] = '\%';
            porcentoF[0][5] = '\0';
        } else if(strlen(porcentoP[0]) >= 4){
            porcentoP[0][5] = '\%';
            porcentoF[0][6] = '\0';
        }
        radianoCentral = (pizzaF[0]/2)*M_PI/180;
        seno = sin(radianoCentral);
        cosseno = cos(radianoCentral);
        x = (3*XMAX/4) + (120*cosseno);
        y = (5*YMAX/16) - (120*seno);
        outtextxy(x, y, porcentoF[0]);
        printf("\nporcentoF %s \n", porcentoF[0]);
        printf("\nporcentagemF %f \n", porcentagemF[0]);

        radianoCentral = (pizzaP[0]/2)*M_PI/180;
        seno = sin(radianoCentral);
        cosseno = cos(radianoCentral);
        outtextxy(XMAX/4 + 120*cosseno, 5*YMAX/16 - 120*seno, porcentoP[0]);



      for(i = 0; i < 5; i++){
        sprintf( porcentoF[i], "%2.1f", porcentagemF[i]);
        sprintf( porcentoP[i], "%2.1f", porcentagemP[i]);
        if(strlen(porcentoF[i]) < 4){
            porcentoF[i][4] = '%%';
            porcentoF[i][5] = '/0';
        } else if(strlen(porcentoF[i]) >= 4){
            porcentoF[i][5] = '%%';
            porcentoF[i][6] = '/0';
        }
        if(strlen(porcentoP[i]) < 4){
            porcentoP[i][4] = '%%';
            porcentoF[i][5] = '/0';
        } else if(strlen(porcentoP[i]) >= 4){
            porcentoP[i][5] = '%%';
            porcentoF[i][6] = '/0';
        }
      }

      for(i=1, grausF = 0, grausP = 0; i < 5; i++)
      {
        radianoCentral = (pizzaF[i]/2 + grausF + pizzaF[i-1])*M_PI/180;
        seno = sin(radianoCentral);
        cosseno = cos(radianoCentral);
        printf("\n%d %d\n", XMAX, YMAX);
        printf("seno e cosseno %f %f", seno, cosseno);
        char grausDebug[3];
        sprintf(grausDebug, "%3.0f", radianoCentral);
        printf("\n\nx y%f %f\n", 3*XMAX/4 + 100*cosseno, 5*YMAX/16 - 100*seno);
        outtextxy(3*XMAX/4 + 120*cosseno - 10, 5*YMAX/16 - 120*seno - 10, porcentoF[i]);
        //outtextxy(3*XMAX/4 + 100*cosseno, 5*YMAX/16 - 100*seno, porcentoF[i]);
        grausF += pizzaF[i-1];
        printf("\n\n%d %f\n", i, radianoCentral);

        radianoCentral = (pizzaP[i]/2 + grausP + pizzaP[i-1])*M_PI/180;
        seno = sin(radianoCentral);
        cosseno = cos(radianoCentral);
        outtextxy(XMAX/4 + 120*cosseno - 10, 5*YMAX/16 - 120*seno - 10, porcentoP[i]);
        grausP += pizzaP[i-1];
        printf("%d %f", i, radianoCentral);

      }

      // padroniza a cor do texto
      setcolor(0);
      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 9);
      //cria um quadrado preenchido de uma certa cor para o lado dos jogos
      bar(2*XMAX/64, 34*YMAX/64, 7*XMAX/128, 36*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 34*YMAX/64, 7*XMAX/128, 36*YMAX/64);
      //cria um quadrado preenchido de uma certa cor para o lado das empresas
      bar(34*XMAX/64, 34*YMAX/64, 71*XMAX/128, 36*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 34*YMAX/64, 71*XMAX/128, 36*YMAX/64);

      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 10);
      //cria um quadrado preenchido de uma certa cor para o lado dos jogos
      bar(2*XMAX/64, 37*YMAX/64, 7*XMAX/128, 39*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 37*YMAX/64, 7*XMAX/128, 39*YMAX/64);
      //cria um quadrado preenchido de uma certa cor para o lado das empresas
      bar(34*XMAX/64, 37*YMAX/64, 71*XMAX/128, 39*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 37*YMAX/64, 71*XMAX/128, 39*YMAX/64);

      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 11);
      //cria um quadrado preenchido de uma certa cor para o lado dos jogos
      bar(2*XMAX/64, 40*YMAX/64, 7*XMAX/128, 42*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 40*YMAX/64, 7*XMAX/128, 42*YMAX/64);
      //cria um quadrado preenchido de uma certa cor para o lado das empresas
      bar(34*XMAX/64, 40*YMAX/64, 71*XMAX/128, 42*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 40*YMAX/64, 71*XMAX/128, 42*YMAX/64);

      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 12);
      //cria um quadrado preenchido de uma certa cor para o lado dos jogos
      bar(2*XMAX/64, 43*YMAX/64, 7*XMAX/128, 45*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 43*YMAX/64, 7*XMAX/128, 45*YMAX/64);
      //cria um quadrado preenchido de uma certa cor para o lado das empresas
      bar(34*XMAX/64, 43*YMAX/64, 71*XMAX/128, 45*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 43*YMAX/64, 71*XMAX/128, 45*YMAX/64);

      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 13);
      //cria um quadrado preenchido de uma certa cor para o lado dos jogos
      bar(2*XMAX/64, 46*YMAX/64,7*XMAX/128, 48*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 46*YMAX/64, 7*XMAX/128, 48*YMAX/64);
      //cria um quadrado preenchido de uma certa cor para o lado das empresas
      bar(34*XMAX/64, 46*YMAX/64, 71*XMAX/128, 48*YMAX/64);
      //cria um retangulo em volta do quadradro, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 46*YMAX/64, 71*XMAX/128, 48*YMAX/64);

      // padroniza o estilo e cor para os elementos abaixo
      setfillstyle(1, 15);
      //cria um retangulo com fundo branco, como uma borda para o lado dos jogos
      rectangle(2*XMAX/64, 49*YMAX/64, 7*XMAX/128, 51*YMAX/64);
      //cria um retangulo com fundo branco, como uma borda para o lado das empresas
      rectangle(34*XMAX/64, 49*YMAX/64, 71*XMAX/128, 51*YMAX/64);

      // apresenta o nome do candidato 1 jogos
      outtextxy(8*XMAX/128, 69*YMAX/128, g[0].n);
      // apresenta o nome do candidato 2 para jogos
      outtextxy(8*XMAX/128, 75*YMAX/128, g[1].n);
      // apresenta o nome do candidato 3 para jogos
      outtextxy(8*XMAX/128, 81*YMAX/128, g[2].n);
      // apresenta o nome do candidato 4 para jogos
      outtextxy(8*XMAX/128, 87*YMAX/128, g[3].n);
      // apresenta o nome do candidato 5 para jogos
      outtextxy(8*XMAX/128, 93*YMAX/128, g[4].n);
      // apresenta Votos em branco para jogos
      outtextxy(8*XMAX/128, 99*YMAX/128, "Votos em branco");

      // apresenta o nome do candidato 1 empresas
      outtextxy(72*XMAX/128, 69*YMAX/128, f[0].n);
      // apresenta o nome do candidato 2 empresas
      outtextxy(72*XMAX/128, 75*YMAX/128, f[1].n);
      // apresenta o nome do candidato 3 empresas
      outtextxy(72*XMAX/128, 81*YMAX/128, f[2].n);
      // apresenta o nome do candidato 4 empresas
      outtextxy(72*XMAX/128, 87*YMAX/128, f[3].n);
      // apresenta o nome do candidato 5 empresas
      outtextxy(72*XMAX/128, 93*YMAX/128, f[4].n);
      // apresenta Votos em branco para empresas
      outtextxy(72*XMAX/128, 99*YMAX/128, "Votos em branco");

      // padroniza a cor do texto
      setcolor(0);
      // retangulo para separar os lados de jogos e empresas
      rectangle(0, -1, XMAX/2, YMAX);

      // padroniza o texto
      settextstyle(10, HORIZ_DIR, 5);
      // apresenta um texto de Jogos acima do grafico
      outtextxy(9*XMAX/64, YMAX/16, "Empresas");
      // apresenta um texto de Empresa de jogos acima do grafico
      outtextxy(11*XMAX/16, YMAX/16, "Jogos");

      getchar();
      //fecha a janela gr�fica
      closegraph();
    }
}

void clique(int *e, float *t, int *s, int *v, int *clicado, float *branco)
{
  if(tela==1)
    {
    if(mousex() > left1 && mousex() < primeirax2 && mousey() > top1 && mousey() < primeiray2)
    {
      *e = 0;
      apagapalavra();
      texto("Voc� escolheu Bethesda. Confirmar?");
      *clicado=1;
    }
    if(mousex() > left2 && mousex() < segundax2 && mousey() > top2 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      texto("Voc� escolheu Santa Monica Studio. Confirmar?");
      *clicado=1;
    }
    if(mousex() > left3 && mousex() < terceirax2 && mousey() > top3 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        texto("Voc� escolheu 343 Industries. Confirmar?");
        *clicado=1;
    }
    if(mousex() > left4 && mousex() < quartax2 && mousey() > top4 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      texto("Voc� escolheu Playground Games. Confirmar?");
      *clicado=1;
    }
    if(mousex() > left5 && mousex() < quintax2 && mousey() > top5 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      texto("Voc� escolheu Ubisoft. Confirmar?");
      *clicado=1;
    }
    if(mousex() > 7*XMAX/16 && mousex() < (7*XMAX/16)+(2*XMAX/16) && mousey() > 25*YMAX/32 && mousey() < 27*YMAX/32)
    {
      *e = 5;
      apagapalavra();
      texto("Voc� escolheu votar em branco. Confirmar?");
      botao(7*XMAX/16, 25*YMAX/32, 8, "Branco");
      delay(200);
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
      *clicado=2;
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 22*YMAX/32 && mousey() < 24*YMAX/32 && estado != -1)
    {
      if(estado == 5)
      {
        *e = -1;
        *branco += 1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
        *clicado=0;
      }
      else if(estado != -1)
      {
        *v += 1;
        *e = -1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
        *clicado=0;
      }
      apagapalavra();
      *s = 2;
    }
    if(mousex() > 13*XMAX/16 && mousex() < (13*XMAX/16)+(XMAX/8) && mousey() > 14*YMAX/16 && mousey() < (14*YMAX/16)+(YMAX/16))
    {
      *s = 3;
      botao(13*XMAX/16, 14*YMAX/16, 4, "Resultado");
      delay(200);
    }
    if(mousex() > XMAX/16 && mousex() < (XMAX/16)+(XMAX/8) && mousey() > 14*YMAX/16 && mousey() < (14*YMAX/16)+(YMAX/16))
    {
        simular(&f[0].v, &f[1].v, &f[2].v, &f[3].v, &f[4].v, &brancoF, &g[0].v, &g[1].v, &g[2].v, &g[3].v, &g[4].v, &brancoP, &total);
        botao(1*XMAX/16, 14*YMAX/16, 1, "Simular");
        delay(200);
        botao(1*XMAX/16, 14*YMAX/16, 9, "Simular");
    }
  }
  if(tela==2)
  {
    if(mousex() > left1 && mousex() < primeirax2 && mousey() > top1 && mousey() < primeiray2)
    {
      *e = 0;
      apagapalavra();
      texto("Voc� escolheu Skyrim. Confirmar?");
      diminuirAumentar();
      *clicado=1;
    }
    if(mousex() > left2 && mousex() < segundax2 && mousey() > top2 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      texto("Voc� escolheu God of War Ragnarok. Confirmar?");
      diminuirAumentar();
      *clicado=1;
    }
    if(mousex() > left3 && mousex() < terceirax2 && mousey() > top3 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        texto("Voc� escolheu Halo Infinte. Confirmar?");
        diminuirAumentar();
        *clicado=1;
    }
    if(mousex() > left4 && mousex() < quartax2 && mousey() > top4 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      texto("Voc� escolheu Forza Horizon 5. Confirmar?");
      diminuirAumentar();
      *clicado=1;
    }
    if(mousex() > left5 && mousex() < quintax2 && mousey() > top5 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      texto("Voc� escolheu Assassin's Creed Valhalla. Confirmar?");
      diminuirAumentar();
      *clicado=1;
    }
    if(mousex() > 7*XMAX/16 && mousex() < (7*XMAX/16)+(2*XMAX/16) && mousey() > 25*YMAX/32 && mousey() < 27*YMAX/32)
    {
      *e = 5;
      apagapalavra();
      texto("Voc� escolheu votar em branco. Confirmar?");
      botao(7*XMAX/16, 25*YMAX/32, 8, "Branco");
      delay(200);
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
      diminuirAumentar();
      *clicado=2;
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 22*YMAX/32 && mousey() < 24*YMAX/32 && estado != -1)
    {
      if(estado == 5)
      {
        *e = -1;
        *branco += 1;
        *t = total +1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
        *clicado=0;
      }
      else if(estado != -1)
      {
        *v += 1;
        *e = -1;
        *t = total +1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
        *clicado=0;
      }
      apagapalavra();
      *s = 1;
    }
  }
  if(tela==3)
  {
    if(mousex() > 7*XMAX/16 && mousex() < (7*XMAX/16)+(XMAX/8) && mousey() > 12*YMAX/16 && mousey() < (12*YMAX/16)+(YMAX/16))
    {
      *s = 4;
      botao(7*XMAX/16, 12*YMAX/16, 4, "Estatísticas");
      delay(200);
    }
  }
}

int apuracao(candidato f[], int tamanho)
{
    int maior, indice, i;
    maior = f[0].v;
    indice = 0;
    for (i=1; i < tamanho; i++)
    {
        if (f[i].v > maior)
        {
            maior = f[i].v;
            indice = i;
        }
    }
    return indice;
}

void apagapalavra()
{
    setfillstyle(1,15);
    bar(XMAX/4, 15*YMAX/32,(XMAX/4)+960, 17*YMAX/32);
}

void imagem(int left, int top, char arquivo[50])
{
    readimagefile(arquivo, left, top, left+(XMAX/8), top+(21*XMAX/128));
}

void botao(int x1, int y1, int cor, char nome[15])
{
  int x2 = x1+(2*XMAX/16), y2 = y1+(YMAX/16);
  int nomeBotao = strlen(nome)*8;

  setcolor(0);
  setfillstyle(1, cor);
  setbkcolor(cor);
  bar(x1, y1, x2, y2);
  rectangle(x1, y1, x2, y2);
  outtextxy(x1+((x2-x1)/2)-(nomeBotao/2),(y2-y1)/2+y1-4, nome);

  setbkcolor(15);
}

void simular(int *f1, int *f2, int *f3, int *f4, int *f5, float *fb, int *p1, int *p2, int *p3, int *p4, int *p5, float *pb, float *soma)
{
    int total = 0;
    srand(time(NULL));
    *f1 = rand()%100;
    printf("%d\n", f[0].v);
    total = total + f[0].v;
    printf("total %d\n", total);
    *f2 = rand()%100;
    printf("%d\n", f[1].v);
    total = total + f[1].v;
    printf("total %d\n", total);
    *f3 = rand()%100;
    printf("%d\n", f[2].v);
    total = total + f[2].v;
    printf("total %d\n", total);
    *f4 = rand()%100;
    printf("%d\n", f[3].v);
    total = total + f[3].v;
    printf("total %d\n", total);
    *f5 = rand()%100;
    printf("%d\n", f[4].v);
    total = total + f[4].v;
    printf("total %d\n", total);
    *fb = rand()%100;
    printf("%f\n", brancoF);
    total = total + brancoF;
    printf("total %d\n", total);
    *soma = total;

    *p1 = rand()%100;
    printf("%d\n", g[0].v);
    total = total - g[0].v;
    *p2 = rand()%100;
    printf("%d\n", g[1].v);
    total = total - g[1].v;
    *p3 = rand()%100;
    printf("%d\n", g[2].v);
    total = total - g[2].v;
    *p4 = rand()%total;
    printf("%d\n", g[3].v);
    total = total - g[3].v;
    *p5 = rand()%total;
    printf("%d\n", g[4].v);
    total = total - g[4].v;
    *pb = total;
    printf("%f\n", brancoP);
}

void titulo(char titulo[40], int left, int top)
{
    int right = left +(XMAX/8);
    int center = left + (XMAX/16);
    int tamanhoTitulo;

    if(strlen(titulo)>30)
        tamanhoTitulo = strlen(titulo)*6;
    else
        tamanhoTitulo = strlen(titulo)*8;

    setcolor(0);
    outtextxy(center-(tamanhoTitulo/2), top+(24*XMAX/128), titulo);
}

void texto(char texto[80])
{
    int tamanhoTexto, center=XMAX/2;

    tamanhoTexto = strlen(texto)*8;

    outtextxy(center-(tamanhoTexto/2),YMAX/2, texto);
}

void imagemEmpresa(int left, int top, char arquivo[50])
{
    readimagefile(arquivo, left, top, left+(XMAX/8), top+(9*XMAX/128));
}

void diminuirAumentar()
{
    if(tela==2)
    {
        printf("%d",estado);
        if(clicado==0)
        {
            aumentado = estado;
            if(estado==0)
            {
                readimagefile(f[0].j, left1 - (XMAX/128), top1 - (XMAX/128), left1+(XMAX/8)+(XMAX/128), top1+(21*XMAX/128)+(XMAX/128));
                apagarImagem(left2, top2);
                apagarImagem(left3, top3);
                apagarImagem(left4, top4);
                apagarImagem(left5, top5);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top1, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[4].j, (XMAX/128)+left5, (XMAX/128)+top5, left5+(XMAX/8)-(XMAX/128), top5+(21*XMAX/128)-(XMAX/128));
                printf("Skyrim");
            }
            if(estado==1)
            {
                readimagefile(f[1].j, left2 - (XMAX/128), top2 - (XMAX/128), left2+(XMAX/8)+(XMAX/128), top2+(21*XMAX/128)+(XMAX/128));
                apagarImagem(left1, top1);
                apagarImagem(left3, top3);
                apagarImagem(left4, top4);
                apagarImagem(left5, top5);
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left1+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[4].j, (XMAX/128)+left5, (XMAX/128)+top5, left5+(XMAX/8)-(XMAX/128), top5+(21*XMAX/128)-(XMAX/128));
                printf("Teste");
            }
            if(estado==2)
            {
                readimagefile(f[2].j, left3 - (XMAX/128), top3 - (XMAX/128), left3+(XMAX/8)+(XMAX/128), top3+(21*XMAX/128)+(XMAX/128));
                apagarImagem(left2, top2);
                apagarImagem(left1, top1);
                apagarImagem(left4, top4);
                apagarImagem(left5, top5);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top2, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left1+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[4].j, (XMAX/128)+left5, (XMAX/128)+top5, left5+(XMAX/8)-(XMAX/128), top5+(21*XMAX/128)-(XMAX/128));
            }
            if(estado==3)
            {
                readimagefile(f[3].j, left4 - (XMAX/128), top4 - (XMAX/128), left4+(XMAX/8)+(XMAX/128), top4+(21*XMAX/128)+(XMAX/128));
                apagarImagem(left2, top2);
                apagarImagem(left3, top3);
                apagarImagem(left1, top1);
                apagarImagem(left5, top5);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top2, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left4+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[4].j, (XMAX/128)+left5, (XMAX/128)+top5, left5+(XMAX/8)-(XMAX/128), top5+(21*XMAX/128)-(XMAX/128));
            }
            if(estado==4)
            {
                readimagefile(f[4].j, left5 - (XMAX/128), top5 - (XMAX/128), left5+(XMAX/8)+(XMAX/128), top5+(21*XMAX/128)+(XMAX/128));
                apagarImagem(left2, top2);
                apagarImagem(left3, top3);
                apagarImagem(left4, top4);
                apagarImagem(left1, top1);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top1, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left1+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
            }
        }
        printf("\naumentado %d\n", aumentado);
        if(clicado==1 && estado != aumentado)
        {

            if(aumentado==0)
            {
                setfillstyle(1,15);
                bar(left1 - (XMAX/128), top1 - (XMAX/128), left1+(XMAX/8)+(XMAX/128), top1+(21*XMAX/128)+(XMAX/128));
                imagem(left1, top1, f[0].j);
                apagarImagem(left1, top1);
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left1+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
                printf("Skyrim2");
            }
            if(aumentado==1)
            {
                setfillstyle(1,15);
                bar(left2 - (XMAX/128), top2 - (XMAX/128), left2+(XMAX/8)+(XMAX/128), top2+(21*XMAX/128)+(XMAX/128));
                imagem(left2, top2, f[1].j);
                apagarImagem(left2, top2);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top1, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==2)
            {
                setfillstyle(1,15);
                bar(left3 - (XMAX/128), top3 - (XMAX/128), left3+(XMAX/8)+(XMAX/128), top3+(21*XMAX/128)+(XMAX/128));
                imagem(left3, top3, f[2].j);
                apagarImagem(left3, top3);
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==3)
            {
                setfillstyle(1,15);
                bar(left4 - (XMAX/128), top4 - (XMAX/128), left4+(XMAX/8)+(XMAX/128), top4+(21*XMAX/128)+(XMAX/128));
                imagem(left4, top4, f[3].j);
                apagarImagem(left4, top4);
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==4)
            {
                setfillstyle(1,15);
                bar(left5 - (XMAX/128), top5 - (XMAX/128), left5+(XMAX/8)+(XMAX/128), top5+(21*XMAX/128)+(XMAX/128));
                imagem(left5, top5, f[4].j);
                apagarImagem(left5, top5);
            }
            if(estado==0)
            {
                imagem(left1, top1, f[0].j);
                readimagefile(f[0].j, left1 - (XMAX/128), top1 - (XMAX/128), left1+(XMAX/8)+(XMAX/128), top1+(21*XMAX/128)+(XMAX/128));
            }
            if(estado==1)
            {
                imagem(left2, top2, f[1].j);
                readimagefile(f[1].j, left2 - (XMAX/128), top2 - (XMAX/128), left2+(XMAX/8)+(XMAX/128), top2+(21*XMAX/128)+(XMAX/128));
            }
            if(estado==2)
            {
                imagem(left3, top3, f[2].j);
                readimagefile(f[2].j, left3 - (XMAX/128), top3 - (XMAX/128), left3+(XMAX/8)+(XMAX/128), top3+(21*XMAX/128)+(XMAX/128));
            }
            if(estado==3)
            {
                imagem(left4, top4, f[3].j);
                readimagefile(f[3].j, left4 - (XMAX/128), top4 - (XMAX/128), left4+(XMAX/8)+(XMAX/128), top4+(21*XMAX/128)+(XMAX/128));
            }
            if(estado==4)
            {
                imagem(left5, top5, f[4].j);
                readimagefile(f[4].j, left5 - (XMAX/128), top5 - (XMAX/128), left5+(XMAX/8)+(XMAX/128), top5+(21*XMAX/128)+(XMAX/128));
            }
            aumentado = estado;
        }
        if(clicado == 2)
        {
            if(aumentado==0)
            {
                setfillstyle(1,15);
                bar(left1 - (XMAX/128), top1 - (XMAX/128), left1+(XMAX/8)+(XMAX/128), top1+(21*XMAX/128)+(XMAX/128));
                imagem(left1, top1, f[0].j);
                apagarImagem(left1, top1);
                readimagefile(f[0].j, (XMAX/128)+left1, (XMAX/128)+top1, left1+(XMAX/8)-(XMAX/128), top1+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==1)
            {
                setfillstyle(1,15);
                bar(left2 - (XMAX/128), top2 - (XMAX/128), left2+(XMAX/8)+(XMAX/128), top2+(21*XMAX/128)+(XMAX/128));
                imagem(left2, top2, f[1].j);
                apagarImagem(left2, top2);
                readimagefile(f[1].j, (XMAX/128)+left2, (XMAX/128)+top1, left2+(XMAX/8)-(XMAX/128), top2+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==2)
            {
                setfillstyle(1,15);
                bar(left3 - (XMAX/128), top3 - (XMAX/128), left3+(XMAX/8)+(XMAX/128), top3+(21*XMAX/128)+(XMAX/128));
                imagem(left3, top3, f[2].j);
                apagarImagem(left3, top3);
                readimagefile(f[2].j, (XMAX/128)+left3, (XMAX/128)+top3, left3+(XMAX/8)-(XMAX/128), top3+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==3)
            {
                setfillstyle(1,15);
                bar(left4 - (XMAX/128), top4 - (XMAX/128), left4+(XMAX/8)+(XMAX/128), top4+(21*XMAX/128)+(XMAX/128));
                imagem(left4, top4, f[3].j);
                apagarImagem(left4, top4);
                readimagefile(f[3].j, (XMAX/128)+left4, (XMAX/128)+top4, left4+(XMAX/8)-(XMAX/128), top4+(21*XMAX/128)-(XMAX/128));
            }
            if(aumentado==4)
            {
                setfillstyle(1,15);
                bar(left5 - (XMAX/128), top5 - (XMAX/128), left5+(XMAX/8)+(XMAX/128), top5+(21*XMAX/128)+(XMAX/128));
                imagem(left5, top5, f[4].j);
                apagarImagem(left5, top5);
            }

            aumentado = -1;

        }

    }
}

void apagarImagem(int left, int top)
{
    setfillstyle(1,15);
    bar(left, top, left+(XMAX/8)+(XMAX/256), top+(21*XMAX/128)+(XMAX/256));
}
