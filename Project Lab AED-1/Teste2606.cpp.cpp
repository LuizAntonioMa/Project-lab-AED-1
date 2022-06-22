#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define XMAX getmaxwidth()
#define YMAX getmaxheight()

typedef struct
{
    char n[40];
    int v;
    char j[40];
} candidato;

  int primeirax1 = XMAX/16, primeiray1 = YMAX/16, primeirax2 = 3*XMAX/16, primeiray2 = 4*YMAX/16;
  int segundax1 = 4*XMAX/16, segunday1 = YMAX/16, segundax2 = 6*XMAX/16, segunday2 = 4*YMAX/16;
  int terceirax1 = 7*XMAX/16, terceiray1 = YMAX/16, terceirax2 = 9*XMAX/16, terceiray2 = 4*YMAX/16;
  int quartax1 = 10*XMAX/16, quartay1 = YMAX/16, quartax2 = 12*XMAX/16, quartay2 = 4*YMAX/16;
  int quintax1 = 13*XMAX/16, quintay1 = YMAX/16, quintax2 = 15*XMAX/16, quintay2 = 4*YMAX/16;

int estado=-1, total=0, tela=1, vencedorF, vencedorP;
int pizzaF[6];
int pizzaP[6];
int porcentagemF[6];
int porcentagemP[6];
int i=0;
int graus=360;
int c=0;

void clique(int *e, int *t, int *s, int *v, int *contador);
int apuracao(candidato f[], int tamanho);
void apagapalavra();
int antibug();
int contador= 0;

int main()
{

  candidato f[5] = {"Harry Potter e a Ordem da Fenix", 0, "Harry Potter e a Ordem da Fenix.jpg",
                    "Gente Grande 2", 0, "Gente Grande 2.jpg",
                    "Exemplo3", 0, "Harry Potter e a pedra filosofal.jpg",
                    "Exemplo4", 0,
                    "Exemplo5", 0};

  candidato g[5] = {"personagem1", 0,"",
                    "personagem2", 0,"",
                    "personagem3", 0,"",
                    "personagem4", 0,"",
                    "personagem5", 0,""};


  initwindow (XMAX,YMAX,"Project Lab AED-1",0,0);
  setbkcolor(15);

  while(tela!=5)
  {
    cleardevice();
    while(tela==1)
    {

  //readimagefile("Harry Potter e a Ordem da Fenix.jpg", primeirax1, primeiray1, primeirax2, primeiray2);
  //readimagefile("Gente Grande 2.jpg", segundax1, segunday1, segundax2, segunday2);
  //readimagefile("Harry Potter e a pedra filosofal.jpg", terceirax1, terceiray1, terceirax2, terceiray2);
  //readimagefile("Exemplo4.jpg", quartax1, quartay1, quartax2, quartay2);
  //readimagefile("Exemplo5.jpg", quintax1, quintay1, quintax2, quintay2);
      setfillstyle(1, 8);
      bar(primeirax1, primeiray1, primeirax2, primeiray2);
      bar(segundax1, segunday1, segundax2, segunday2);
      bar(terceirax1, terceiray1, terceirax2, terceiray2);
      bar(quartax1, quartay1, quartax2, quartay2);
      bar(quintax1, quintay1, quintax2, quintay2);

      setcolor(0);
      outtextxy(primeirax1, primeiray1, "personagem1");
      outtextxy(segundax1, primeiray1, "personagem2");
      outtextxy(terceirax1, primeiray1, "personagem3");
      outtextxy(quartax1, primeiray1, "personagem4");
      outtextxy(quintax1, primeiray1, "personagem5");

      setfillstyle(1,10);
      setbkcolor(10);
      bar(7*XMAX/16, 7*YMAX/16, 9*XMAX/16, 8*YMAX/16);
      setcolor(0);
      outtextxy(15*XMAX/31, 15*YMAX/32, "Confirmar");
      setbkcolor(15);

      setcolor(0);
      rectangle(7*XMAX/16, 9*YMAX/16, 9*XMAX/16, 10*YMAX/16);
      outtextxy(15*XMAX/32, 19*YMAX/32, "Branco");

      outtextxy(XMAX/2, YMAX/32, "Escolha seu preferido:");

      setfillstyle(1,12);
      setbkcolor(12);
      bar(29*XMAX/32, 29*YMAX/32, 31*XMAX/32, 30*YMAX/32);
      outtextxy(59*XMAX/64, 117*YMAX/128, "Resultado");
      setbkcolor(15);
      if (ismouseclick(WM_LBUTTONDOWN))
      {
        clique(&estado, &total, &tela, &g[estado].v, &contador);
        clearmouseclick(WM_LBUTTONDOWN);
      }
    }

    cleardevice();
    while(tela==2)
    {
      readimagefile("Harry Potter e a Ordem da Fenix.jpg", primeirax1, primeiray1, primeirax2, primeiray2);
      readimagefile("Gente Grande 2.jpg", segundax1, segunday1, segundax2, segunday2);
      readimagefile("Harry Potter e a pedra filosofal.jpg", terceirax1, terceiray1, terceirax2, terceiray2);
      readimagefile("Exemplo4.jpg", quartax1, quartay1, quartax2, quartay2);
      readimagefile("Exemplo5.jpg", quintax1, quintay1, quintax2, quintay2);

      setcolor(0);
      outtextxy(primeirax1, primeiray1, "Harry Potter e a Ordem da Fenix");
      outtextxy(segundax1, primeiray1, "Gente Grande 2");
      outtextxy(terceirax1, primeiray1, "Harry Potter e a Pedra Filosofal");
      outtextxy(quartax1, primeiray1, "Exemplo4");
      outtextxy(quintax1, primeiray1, "Exemplo5");

      setfillstyle(1,10);
      setbkcolor(10);
      bar(7*XMAX/16, 7*YMAX/16, 9*XMAX/16, 8*YMAX/16);
      setcolor(0);
      outtextxy(15*XMAX/31, 15*YMAX/32, "Confirmar");
      setbkcolor(15);

      setcolor(0);
      rectangle(7*XMAX/16, 9*YMAX/16, 9*XMAX/16, 10*YMAX/16);
      outtextxy(15*XMAX/32, 19*YMAX/32, "Branco");

      outtextxy(XMAX/2, YMAX/32, "Escolha seu preferido:");

      if (ismouseclick(WM_LBUTTONDOWN))
      {
        clique(&estado, &total, &tela, &f[estado].v, &contador);
        clearmouseclick(WM_LBUTTONDOWN);
      }
    }
    cleardevice();
    while(tela==3)
    {
      cleardevice();
      vencedorF = apuracao(f, 5);
      vencedorP = apuracao(g, 5);

      outtextxy(XMAX/4, YMAX/2, "O vencedor dos personagens é:");
      outtextxy(XMAX/4, 17*YMAX/32, g[vencedorP].n);
      readimagefile(g[vencedorP].j, XMAX/4, 20*YMAX/32, 3*XMAX/8, 27*YMAX/32);

      outtextxy(3*XMAX/4, YMAX/2, "O vencedor dos filmes é:");
      outtextxy(3*XMAX/4, 17*YMAX/32, f[vencedorF].n);
      readimagefile(f[vencedorF].j, 3*XMAX/4, 20*YMAX/32, 7*XMAX/8, 27*YMAX/32);

      setfillstyle(1,12);
      setbkcolor(12);
      bar(29*XMAX/32, 29*YMAX/32, 31*XMAX/32, 30*YMAX/32);
      outtextxy(59*XMAX/64, 117*YMAX/128, "Estatisticas");
      setbkcolor(15);
    }
    for(i=0; i < 6; i++)
    {
      porcentagemF[i] = ceil((100*f[i].v)/total);
      porcentagemP[i] = ceil((100*g[i].v)/total);
    }
    for(i=0; i<6; i++)
    {
      pizzaF[i] = ceil((360*porcentagemF[i])/100);
      pizzaP[i] = ceil((360*porcentagemP[i])/100);
    }
    cleardevice();
    while(tela==4)
    {
      cleardevice();
      setfillstyle(1,0);
      pieslice(XMAX/4, YMAX/2, 0, pizzaF[0], 100);
      pieslice(3*XMAX/4, YMAX/2, 0, pizzaP[0], 100);
      for(i=1, c=1;i<6;i++, c++)
        {
          setfillstyle(1, c);
          pieslice(XMAX/4, YMAX/2, pizzaF[i-1], pizzaF[i], 100);
          pieslice(3*XMAX/4, YMAX/2, pizzaP[i-1], pizzaP[i], 100);
        }
    }
  }

  getchar();
  closegraph();

}

void clique(int *e, int *t, int *s, int *v, int *contador)
{
  if(tela==1)
    {
    if(mousex() > primeirax1 && mousex() < primeirax2 && mousey() > primeiray1 && mousey() < primeiray2)
    {
      *e = 0;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu personagem1. Confirmar?");
    }
    if(mousex() > segundax1 && mousex() < segundax2 && mousey() > segunday1 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu personagem2. Confirmar?");
    }
    if(mousex() > terceirax1 && mousex() < terceirax2 && mousey() > terceiray1 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu personagem3. Confirmar?");
    }
    if(mousex() > quartax1 && mousex() < quartax2 && mousey() > quartay1 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu personagem4. Confirmar?");
    }
    if(mousex() > quintax1 && mousex() < quintax2 && mousey() > quintay1 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu personagem5. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*YMAX/16 && mousey() > 9*XMAX/16 && mousey() < 10*YMAX/16)
    {
      *e = 5;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu votar em branco. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 7*YMAX/16 && mousey() < 8*YMAX/16 && estado != -1)
    {
      if(estado == 5)
      {
        *e = -1;
      }
      else
      {
        *v += 1;
        *e = -1;
      }
      apagapalavra();
      *s = 2;
    }
    if(mousex() > 29*XMAX/32 && mousex() < 31*XMAX/32 && mousey() > 29*YMAX/32 && mousey() < 30*YMAX/32)
      {
        *s = 3;
      }
  }
  if(tela==2)
  {
    if(mousex() > primeirax1 && mousex() < primeirax2 && mousey() > primeiray1 && mousey() < primeiray2)
    {
      *e = 0;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Harry Potter e a Ordem da Fenix. Confirmar?");
    }
    if(mousex() > segundax1 && mousex() < segundax2 && mousey() > segunday1 && mousey() < segunday2)
    {
      *e = 1;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Gente Grande 2. Confirmar?");
    }
    if(mousex() > terceirax1 && mousex() < terceirax2 && mousey() > terceiray1 && mousey() < terceiray2)
    {
      *e = 2;
        apagapalavra();
        outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo3. Confirmar?");
    }
    if(mousex() > quartax1 && mousex() < quartax2 && mousey() > quartay1 && mousey() < quartay2)
    {
      *e = 3;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo4. Confirmar?");
    }
    if(mousex() > quintax1 && mousex() < quintax2 && mousey() > quintay1 && mousey() < quintay2)
    {
      *e = 4;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo5. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*YMAX/16 && mousey() > 9*XMAX/16 && mousey() < 10*YMAX/16)
    {
      *e = 5;
      apagapalavra();
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu votar em branco. Confirmar?");
    }
    if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 7*YMAX/16 && mousey() < 8*YMAX/16 && estado != -1)
    {
      if(estado == 5)
      {
        *e = -1;
        *t = total +1;
      }
      else
      {
        *v += 1;
        *e = -1;
        *t = total +1;
      }
      apagapalavra();
      *s = 1;
    }
  }
  if(tela==3)
  {
    if(mousex() > 29*XMAX/32 && mousex() < 31*XMAX/32 && mousey() > 29*YMAX/32 && mousey() < 30*YMAX/32)
    {
      *s = 4;
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
    bar(XMAX/2,3*YMAX/4,(XMAX/2)+480, (3*YMAX/4)+16);
}

int antibug()
{
    if(contador==0)
    {
        cleardevice();
    }
    return 1;
}
