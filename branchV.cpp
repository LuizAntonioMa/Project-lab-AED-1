#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>

#define XMAX getmaxwidth()
#define YMAX getmaxheight()

typedef struct
{
    char n[40];
    int  v;
} candidato;

  int primeirax1 = XMAX/16, primeiray1 = YMAX/16, primeirax2 = 3*XMAX/16, primeiray2 = 4*YMAX/16;
  int segundax1 = 4*XMAX/16, segunday1 = YMAX/16, segundax2 = 6*XMAX/16, segunday2 = 4*YMAX/16;
  int terceirax1 = 7*XMAX/16, terceiray1 = YMAX/16, terceirax2 = 9*XMAX/16, terceiray2 = 4*YMAX/16;
  int quartax1 = 10*XMAX/16, quartay1 = YMAX/16, quartax2 = 12*XMAX/16, quartay2 = 4*YMAX/16;
  int quintax1 = 13*XMAX/16, quintay1 = YMAX/16, quintax2 = 15*XMAX/16, quintay2 = 4*YMAX/16;

int estado=-1, total=0, tela=1, vencedor;

void clique(int *e, int *t, int *s, candidato f[]);
int apuracao(int f[], int tamanho);

int main()
{

  candidato f[5] = {"Harry Potter e a Ordem da Fenix", 0, "Gente Grande 2", 0, "Exemplo3", 0, "Exemplo4", 0, "Exemplo5", 0};
  
  setbkcolor(15);
  initwindow (XMAX,YMAX,"Project Lab AED-1",0,0);
  readimagefile("Harry Potter e a Ordem da Fenix.jpg", primeirax1, primeiray1, primeirax2, primeiray2);
  readimagefile("Gente Grande 2.jpg", segundax1, segunday1, segundax2, segunday2);
  readimagefile("Exemplo3.jpg", terceirax1, terceiray1, terceirax2, terceiray2);
  readimagefile("Exemplo4.jpg", quartax1, quartay1, quartax2, quartay2);
  readimagefile("Exemplo5.jpg", quintax1, quintay1, quintax2, quintay2);
  
  outtextxy(primeirax1, (YMAX/16)+primeiray2, "Harry Potter e a Ordem da Fenix");
  outtextxy(primeirax1, (YMAX/16)+segunday2, "Gente Grande 2");
  outtextxy(primeirax1, (YMAX/16)+terceiray2, "Exemplo3");
  outtextxy(primeirax1, (YMAX/16)+quartay2, "Exemplo4");
  outtextxy(primeirax1, (YMAX/16)+quintay2, "Exemplo5");

  setcolor(2);
  bar(7*XMAX/16, 7*YMAX/16, 9*XMAX/16, 8*YMAX/16):
  outtextxy(15*XMAX/32, 15*YMAX/32, "Confirmar");

  setcolor(0);
  rectangle(7*XMAX/16, 9*YMAX/16, 9*XMAX/16, 10*YMAX/16);
  outtextxy(15*XMAX/32, 19*YMAX/32, "Branco");

  outtextxy(XMAX/32, YMAX/32, "Escolha seu preferido:");

  setcolor(4);
  bar(29*XMAX/32, 29*YMAX/32, 31*XMAX/32, 30*YMAX/32);
  outtextxy(59*XMAX/64, 59*YMAX/64, "Resultado");
  
  while(tela==1)
  {
    if (ismouseclick(WM_LBUTTONDOWN))
    {
      clique(&estado, &total, &tela, f.v[]);
      clearmouseclick(WM_LBUTTONDOWN);
    }

  //não sei se é necessário um while aqui, provavelmente na versão final terá, porque os resultados estarão melhor analisados e mais complexos
  cleardevice();
  vencedor = apuracao(f.v[], 5);
  outtextxy(XMAX/2, YMAX/2, "O vencedor é:");
  outtextxy(XMAX/2, 17*YMAX/32, v.n[vencedor]);

  getchar();
  closegraph();
}

void clique(int *e, int *t, int *s, candidato f[])
{
  if(mousex() > primeirax1 && mousex() < primeirax2 && mousey() > primeiray1 && mousey() < primeiray2 && tela==1)
  {
    *e = 0;
    outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Harry Potter e a Ordem da Fenix. Confirmar?");
  }
  if(mousex() > segundax1 && mousex() < segundax2 && mousey() > segunday1 && mousey() < segunday2 && tela==1)
  {
    *e = 1;
    outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Gente Grande 2. Confirmar?"); 
  }
  if(mousex() > terceirax1 && mousex() < terceirax2 && mousey() > terceiray1 && mousey() < terceiray2 && tela==1)
  {
    *e = 2;
      outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo3. Confirmar?");
  }
  if(mousex() > quartax1 && mousex() < quartax2 && mousey() > quartay1 && mousey() < quartay2 && tela==1)
  {
    *e = 3;
    outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo4. Confirmar?");
  }
  if(mousex() > quintax1 && mousex() < quintax2 && mousey() > quintay1 && mousey() < quintay2 && tela==1)
  {
    *e = 4;
    outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu Exemplo5. Confirmar?");
  }
  if(mousex() > 7*XMAX/16 && mousex() < 9*YMAX/16 && mousey() > 9*XMAX/16 && mousey() < 10*YMAX/16 && tela==1)
  {
    *e = 5;
    outtextxy(XMAX/2,3*YMAX/4,"Voce escolheu votar em branco. Confirmar?");
  }
  if(mousex() > 7*XMAX/16 && mousex() < 9*XMAX/16 && mousey() > 7*YMAX/16 && mousey() < 8*YMAX/16 && estado != -1 && tela==1)
  {
    if(estado == 5)
    {
      *e = -1;
      *t = total +1;
    }
    else
    {
      *f[estado] = f.v[estado] + 1;
      *e = -1;
      *t = total +1;
    }
  }
  if(mousex() > 29*XMAX/32 && mousex() < 31*XMAX/36 && mousey() > 29*YMAX/32 && mousey() < 30*YMAX/32 && tela==1)
    {
      *s = 2;
    }
}

int apuracao(int f[], int tamanho)
{
    int maior, indice, i;
    maior = f[0];
    indice = 0;
    for (i=1; i < tamanho; i++)
    {
        if (f[i] > maior)
        {
            maior = f[i];
            indice = i;
        }
    }
    return indice;
}