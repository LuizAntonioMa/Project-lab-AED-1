#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <stdlib.h>


int main()
{
    initwindow (getmaxheight(),getmaxwidth(),"Project Lab AED-1",0,0);
    readimagefile("Harry Potter e a Ordem da Fenix.jpg",0,0,301,430);
    readimagefile("Gente Grande 2.jpg",346,0,690,440);

      while(!kbhit())
      {
        if (ismouseclick(WM_LBUTTONDOWN)&& mousex() > 346 && mousex() < 690
            && mousey() > 0 && mousey() < 440)
            {
                outtextxy(468,10,"Gente Grande 2");
                break;
            }
        clearmouseclick(WM_LBUTTONDOWN);
      }
       while(!kbhit())
      {
        if (ismouseclick(WM_LBUTTONDOWN)&& mousex() > 0 && mousex() < 300
            && mousey() > 0 && mousey() < 430)
            {
                outtextxy(50,10,"Harry Potter e a Ordem da Fenix");
                break;
            }
        clearmouseclick(WM_LBUTTONDOWN);
         //while(!kbhit())
      //{
        //if (ismouseclick(WM_LBUTTONDOWN)&& mousex() > 0 && mousex() < 300
            //&& mousey() > 0 && mousey() < 430)
            //{
              //  outtextxy(50,10,"Harry Potter e a Ordem da Fenix");
                //break;
            //}
        clearmouseclick(WM_LBUTTONDOWN); //essa parte � outra na qual colocar�amos mais uma foto
      }
    // N�o deixe de partir do pressuposto que esse � s� uma base bem r�stica

    getchar();
    closegraph();
}
