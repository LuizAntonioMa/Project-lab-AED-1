#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define XMAX getmaxwidth()
#define YMAX getmaxheight()

typedef struct
{
    char n[40];
    int v;
    char j[40];
} candidato;

int left1 = XMAX/16, top1 = YMAX/16, primeirax2 = 3*XMAX/16, primeiray2 = (YMAX/16)+(22*XMAX/128);
int left2 = 4*XMAX/16, top2 = YMAX/16, segundax2 = 6*XMAX/16, segunday2 = (YMAX/16)+(22*XMAX/128);
int left3 = 7*XMAX/16, top3 = YMAX/16, terceirax2 = 9*XMAX/16, terceiray2 = (YMAX/16)+(22*XMAX/128);
int left4 = 10*XMAX/16, top4 = YMAX/16, quartax2 = 12*XMAX/16, quartay2 = (YMAX/16)+(22*XMAX/128);
int left5 = 13*XMAX/16, top5 = YMAX/16, quintax2 = 15*XMAX/16, quintay2 = (YMAX/16)+(22*XMAX/128);

int estado=-1, tela=1, vencedorF, vencedorP;
int pizzaF[6];
int pizzaP[6];
float porcentagemF[6];
float porcentagemP[6];
int i=0;
int graus=360;
int c=0;
int grausF=0;
int grausP=0;
int contador= 0;
float brancoP=0, brancoF=0;
float total=0;

candidato f[5] = {"Harry Potter e a Ordem da Fenix", 0, "Harry Potter e a Ordem da Fenix.jpg",
                  "Gente Grande 2", 0, "Gente Grande 2.jpg",
                  "Harry Potter e a pedra filosofal", 0, "Harry Potter e a pedra filosofal.jpg",
                  "Exemplo4", 0, "",
                  "Exemplo5", 0, ""};

candidato g[5] = {"personagem1", 0,"",
                  "personagem2", 0,"",
                  "personagem3", 0,"",
                  "personagem4", 0,"",
                  "personagem5", 0,""};

void imagem(int top, int left, char arquivo[50]);
void clique(int *e, float *t, int *s, int *v, int *contador, float *branco);
int apuracao(candidato f[], int tamanho);
void apagapalavra();
void botao(int x1, int y1, int cor, char nome[15]);
void simular(int *f1, int *f2, int *f3, int *f4, int *f5, float *fb, int *p1, int *p2, int *p3, int *p4, int *p5, float *pb, float *soma);
void titulo(char titulo[40], int left, int top);
void texto(char texto[80]);

main()
{

  setlocale(LC_ALL,"portuguese");

  initwindow (XMAX,YMAX,"Project Lab AED-1",0,0);
  setbkcolor(15);

    while(tela!=3)
  {
    if(tela == 1){
        cleardevice();
        //readimagefile("Harry Potter e a Ordem da Fenix.jpg", primeirax1, primeiray1, primeirax2, primeiray2);
        //readimagefile("Gente Grande 2.jpg", segundax1, segunday1, segundax2, segunday2);
        //readimagefile("Harry Potter e a pedra filosofal.jpg", terceirax1, terceiray1, terceirax2, terceiray2);
        //readimagefile("Exemplo4.jpg", quartax1, quartay1, quartax2, quartay2);
        //readimagefile("Exemplo5.jpg", quintax1, quintay1, quintax2, quintay2);
        setfillstyle(1, 8);
        bar(left1, top1, primeirax2, primeiray2);
        bar(left2, top2, segundax2, segunday2);
        bar(left3, top3, terceirax2, terceiray2);
        bar(left4, top4, quartax2, quartay2);
        bar(left5, top5, quintax2, quintay2);

        setcolor(0);
        //outtextxy(left1, top1, "personagem1");
        titulo(g[0].n, left1, top1);
        titulo(g[1].n, left2, top2);
        titulo(g[2].n, left3, top3);
        titulo(g[3].n, left4, top4);
        titulo(g[4].n, left5, top5);

        botao(7*XMAX/16, 22*YMAX/32, 10, "Confirma");
        botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
        botao(13*XMAX/16, 14*YMAX/16, 12, "Resultado");
        botao(1*XMAX/16, 14*YMAX/16, 9, "Simular");

        outtextxy((XMAX/2)-80, YMAX/32, "Escolha seu preferido:");

        while(tela==1)
        {
          if (ismouseclick(WM_LBUTTONDOWN))
          {
            clique(&estado, &total, &tela, &g[estado].v, &contador, &brancoP);
            clearmouseclick(WM_LBUTTONDOWN);
          }
        }
    }
    if(tela==2)
    {

      cleardevice();
      imagem(left1, top1, f[0].j);
      imagem(left2, top2, f[1].j);
      imagem(left3, top3, f[2].j);
      imagem(left4, top4, f[3].j);
      imagem(left5, top5, f[4].j);

      setcolor(0);
      titulo(f[0].n, left1, top1);
      titulo(f[1].n, left2, top2);
      titulo(f[2].n, left3, top3);
      titulo(f[3].n, left4, top4);
      titulo(f[4].n, left5, top5);

      botao(7*XMAX/16, 22*YMAX/32, 10, "Confirma");
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");

      outtextxy((XMAX/2)-80, YMAX/32, "Escolha seu preferido:");
        while(tela==2)
        {
          if (ismouseclick(WM_LBUTTONDOWN))
          {
            clique(&estado, &total, &tela, &f[estado].v, &contador, &brancoF);
            clearmouseclick(WM_LBUTTONDOWN);
          }
        }
    }
  }
    if(tela == 3){
      cleardevice();
      vencedorF = apuracao(f, 5);
      vencedorP = apuracao(g, 5);

      setcolor(0);
      rectangle(0, -1, XMAX/2, YMAX);

      outtextxy((XMAX/4)-180, YMAX/16, "O vencedor dos personagens é:");
      outtextxy((XMAX/4)-180, 15*YMAX/32, g[vencedorP].n);
      imagem(3*XMAX/16, 2*YMAX/16, g[vencedorP].j);

      outtextxy((3*XMAX/4)-90, YMAX/16, "O vencedor dos filmes é:");
      outtextxy((3*XMAX/4)-90, 15*YMAX/32, f[vencedorF].n);
      imagem(11*XMAX/16, 2*YMAX/16, f[vencedorF].j);

      botao(7*XMAX/16, 12*YMAX/16, 12, "Estatísticas");
    }
      while(tela==3)
      {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
          clique(&estado, &total, &tela, &f[estado].v, &contador, &brancoP);
          clearmouseclick(WM_LBUTTONDOWN);
        }
      }
    if( tela == 4){
      for(i=0; i < 5; i++)
      {
        porcentagemF[i] = (100*f[i].v)/total;
        porcentagemP[i] = (100*g[i].v)/total;
        printf("%d %f\n", i, porcentagemF[i]);
        printf("%d %f\n\n", i, porcentagemP[i]);
      }
      for(i=0; i<5; i++)
      {
        pizzaF[i] = floor((360*porcentagemF[i])/100);
        pizzaP[i] = floor((360*porcentagemP[i])/100);
        printf("%d %d\n", i, pizzaF[i]);
        printf("%d %d\n\n", i, pizzaP[i]);
      }
      brancoP = ceil((100*brancoP)/total);
      printf("brancoP %f\n", brancoP);
      brancoP = ceil((360*brancoP)/100);

      brancoF = ceil((100*brancoF)/total);
      printf("brancoF %f\n\n", brancoF);
      brancoF = ceil((360*brancoF)/100);

      printf("\n%d\n", total);

      cleardevice();
      setfillstyle(1,9);
      pieslice(XMAX/4, 5*YMAX/16, 0, pizzaP[0], 100);
      pieslice(3*XMAX/4, 5*YMAX/16, 0, pizzaF[0], 100);

      for(i=1, c=10;i<5;i++, c++)
        {
          setfillstyle(1, c);
          if(pizzaF[i] != 0)
          {
            pieslice(3*XMAX/4, 5*YMAX/16, grausF + pizzaF[i-1], grausF + pizzaF[i-1] + pizzaF[i], 100);
            grausF = grausF + pizzaF[i-1];
          }
          if(pizzaP[i] != 0)
          {
            pieslice(XMAX/4, 5*YMAX/16, grausP + pizzaP[i-1], grausP + pizzaP[i-1] + pizzaP[i], 100);
            grausP = grausP + pizzaP[i-1];
          }

        }

      setfillstyle(1, 15);
      if(brancoP != 0)
        pieslice(XMAX/4, 5*YMAX/16, grausP + pizzaP[4], 0, 100);
    printf("\n\ngrausP %d\n\n", grausP);
      if(brancoF != 0)
        pieslice(3*XMAX/4, 5*YMAX/16, grausF + pizzaF[4], 0, 100);

      setcolor(0);
      setfillstyle(1, 9);
      bar(2*XMAX/64, 34*YMAX/64, 7*XMAX/128, 36*YMAX/64);
      rectangle(2*XMAX/64, 34*YMAX/64, 7*XMAX/128, 36*YMAX/64);
      bar(34*XMAX/64, 34*YMAX/64, 71*XMAX/128, 36*YMAX/64);
      rectangle(34*XMAX/64, 34*YMAX/64, 71*XMAX/128, 36*YMAX/64);
      setfillstyle(1, 10);
      bar(2*XMAX/64, 37*YMAX/64, 7*XMAX/128, 39*YMAX/64);
      rectangle(2*XMAX/64, 37*YMAX/64, 7*XMAX/128, 39*YMAX/64);
      bar(34*XMAX/64, 37*YMAX/64, 71*XMAX/128, 39*YMAX/64);
      rectangle(34*XMAX/64, 37*YMAX/64, 71*XMAX/128, 39*YMAX/64);
      setfillstyle(1, 11);
      bar(2*XMAX/64, 40*YMAX/64, 7*XMAX/128, 42*YMAX/64);
      rectangle(2*XMAX/64, 40*YMAX/64, 7*XMAX/128, 42*YMAX/64);
      bar(34*XMAX/64, 40*YMAX/64, 71*XMAX/128, 42*YMAX/64);
      rectangle(34*XMAX/64, 40*YMAX/64, 71*XMAX/128, 42*YMAX/64);
      setfillstyle(1, 12);
      bar(2*XMAX/64, 43*YMAX/64, 7*XMAX/128, 45*YMAX/64);
      rectangle(2*XMAX/64, 43*YMAX/64, 7*XMAX/128, 45*YMAX/64);
      bar(34*XMAX/64, 43*YMAX/64, 71*XMAX/128, 45*YMAX/64);
      rectangle(34*XMAX/64, 43*YMAX/64, 71*XMAX/128, 45*YMAX/64);
      setfillstyle(1, 13);
      bar(2*XMAX/64, 46*YMAX/64,7*XMAX/128, 48*YMAX/64);
      rectangle(2*XMAX/64, 46*YMAX/64, 7*XMAX/128, 48*YMAX/64);
      bar(34*XMAX/64, 46*YMAX/64, 71*XMAX/128, 48*YMAX/64);
      rectangle(34*XMAX/64, 46*YMAX/64, 71*XMAX/128, 48*YMAX/64);
      setfillstyle(1, 15);
      rectangle(2*XMAX/64, 49*YMAX/64, 7*XMAX/128, 51*YMAX/64);
      rectangle(34*XMAX/64, 49*YMAX/64, 71*XMAX/128, 51*YMAX/64);

      outtextxy(8*XMAX/128, 69*YMAX/128, g[0].n);
      outtextxy(8*XMAX/128, 75*YMAX/128, g[1].n);
      outtextxy(8*XMAX/128, 81*YMAX/128, g[2].n);
      outtextxy(8*XMAX/128, 87*YMAX/128, g[3].n);
      outtextxy(8*XMAX/128, 93*YMAX/128, g[4].n);
      outtextxy(8*XMAX/128, 99*YMAX/128, "Votos em branco");

      outtextxy(72*XMAX/128, 69*YMAX/128, f[0].n);
      outtextxy(72*XMAX/128, 75*YMAX/128, f[1].n);
      outtextxy(72*XMAX/128, 81*YMAX/128, f[2].n);
      outtextxy(72*XMAX/128, 87*YMAX/128, f[3].n);
      outtextxy(72*XMAX/128, 93*YMAX/128, f[4].n);
      outtextxy(72*XMAX/128, 99*YMAX/128, "Votos em branco");

      setcolor(0);
      rectangle(0, -1, XMAX/2, YMAX);

      settextstyle(10, HORIZ_DIR, 5);
      outtextxy(2*XMAX/16, YMAX/16, "Personagens");
      outtextxy(11*XMAX/16, YMAX/16, "Filmes");


      getchar();
      closegraph();
    }
}

void clique(int *e, float *t, int *s, int *v, int *contador, float *branco)
{
  if(tela==1)
    {
    if(mousex() > left1 && mousex() < primeirax2 && mousey() > top1 && mousey() < primeiray2)
    {
      *e = 0;
      apagapalavra();
      texto("Você escolheu personagem1. Confirmar?");
    }
    if(mousex() > left2 && mousex() < segundax2 && mousey() > top2 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      texto("Você escolheu personagem2. Confirmar?");
    }
    if(mousex() > left3 && mousex() < terceirax2 && mousey() > top3 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        texto("Você escolheu personagem3. Confirmar?");
    }
    if(mousex() > left4 && mousex() < quartax2 && mousey() > top4 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      texto("Você escolheu personagem4. Confirmar?");
    }
    if(mousex() > left5 && mousex() < quintax2 && mousey() > top5 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      texto("Você escolheu personagem5. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < (7*XMAX/16)+(2*XMAX/16) && mousey() > 25*YMAX/32 && mousey() < 27*YMAX/32)
    {
      *e = 5;
      apagapalavra();
      texto("Você escolheu votar em branco. Confirmar?");
      botao(7*XMAX/16, 25*YMAX/32, 8, "Branco");
      delay(200);
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 22*YMAX/32 && mousey() < 24*YMAX/32 && estado != -1)
    {
      if(estado == 5)
      {
        *e = -1;
        *branco += 1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
      }
      if(estado != -1)
      {
        *v += 1;
        *e = -1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
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
      texto("Você escolheu Harry Potter e a Ordem da Fenix. Confirmar?");
    }
    if(mousex() > left2 && mousex() < segundax2 && mousey() > top2 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      texto("Você escolheuGente Grande 2. Confirmar?");
    }
    if(mousex() > left3 && mousex() < terceirax2 && mousey() > top3 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        texto("Você escolheu Harry Potter e a pedra filosofal. Confirmar?");
    }
    if(mousex() > left4 && mousex() < quartax2 && mousey() > top4 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      texto("Você escolheu Exemplo4. Confirmar?");
    }
    if(mousex() > left5 && mousex() < quintax2 && mousey() > top5 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      texto("Você escolheu Exemplo5. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < (7*XMAX/16)+(2*XMAX/16) && mousey() > 25*YMAX/32 && mousey() < 27*YMAX/32)
    {
      *e = 5;
      apagapalavra();
      texto("Você escolheu votar em branco. Confirmar?");
      botao(7*XMAX/16, 25*YMAX/32, 8, "Branco");
      delay(200);
      botao(7*XMAX/16, 25*YMAX/32, 15, "Branco");
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
      }
      if(estado != -1)
      {
        *v += 1;
        *e = -1;
        *t = total +1;
        botao(7*XMAX/16, 22*YMAX/32, 2, "Confirma");
        delay(200);
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
    readimagefile(arquivo, left, top, left+(XMAX/8), top+(22*XMAX/128));
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
    srand(12);
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
