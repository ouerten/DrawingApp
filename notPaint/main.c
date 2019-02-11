#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"
#include <il.h>
#include <ilu.h>
#include <ilut.h>


const char name[30];
const int W_genislik=1920;
const int W_yukseklik=1000;
int secenek;
GLsizei mouseX, mouseY;

void ekran_depo(void);
void bastan_ciz(void);
void display(void);

GLubyte renk[3]={0,0,0};
GLubyte depo[1920][1000][3];


void isimverme (const char* isim){


printf("Dosyanin isimini giriniz: ");
gets(isim);

}

void ac(const char* screenshotFile){


    ILuint ImgId = 0;
    ilGenImages(1, &ImgId);
    ilBindImage(ImgId);
    ilLoadImage(screenshotFile);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilEnable(IL_ORIGIN_SET);
    ilEnable(IL_FILE_OVERWRITE);
   ilBindImage(ImgId);
    ilGetData();
    ilDeleteImage(ImgId);

    printf("Screenshot opened to: %s\n", screenshotFile);
}
void kaydet(const char* screenshotFile)
{

    ILuint imageID = ilGenImage();
    ilBindImage(imageID);
    ilutGLScreen();
    ilEnable(IL_FILE_OVERWRITE);
    ilSaveImage(screenshotFile);
    ilDeleteImage(imageID);
    printf("Screenshot saved to: %s\n", screenshotFile);
}



void ekran_depo()
{
      glReadPixels(0,0, W_genislik, W_yukseklik, GL_RGB, GL_UNSIGNED_BYTE, depo);
}

void bastan_ciz()
{
      glRasterPos2i(0, W_yukseklik);
      glDrawPixels(W_genislik, W_yukseklik, GL_RGB, GL_UNSIGNED_BYTE, depo);
      glFlush();
}

void ciz(int x, int y)
{

      float deger = (x-mouseX)*(x-mouseX) + (y-mouseY)*(y-mouseY);
      float derece= sqrt(deger);

      float xderece;
      float yderece;
      float xmerkez;
      float ymerkez;
          int p;


      if (secenek!= 6 && secenek!=7 && secenek!=8)
      {
            glClear(GL_COLOR_BUFFER_BIT);

            bastan_ciz();
      }




     switch(secenek){


     case 1:
         if (x<79)
            x=85;
      glutSetCursor(GLUT_CURSOR_CROSSHAIR);
      glBegin(GL_LINES);
      glColor3ub(renk[0], renk[1], renk[2]);
      glVertex2i(mouseX, mouseY);
      glVertex2i(x, y);
      glEnd();
      glFlush();


      break;

    case 2:
       if (x<79)
            x=85;
      glutSetCursor(GLUT_CURSOR_CROSSHAIR);
      glColor3ub(renk[0], renk[1], renk[2]);
      glBegin(GL_LINE_LOOP);
      int a;
      for (a=0 ; a<=360 ; a++)
      {
         float rad= a*3.14159265/180;
         glVertex2i(mouseX + cos(rad)*derece, mouseY + sin(rad)*derece);
      }
      glEnd();
      glFlush();
      break;


    case 3:
        if (x<79)
            x=85;
       xderece = (x-mouseX)/2;
       yderece = (y-mouseY)/2;
       xmerkez = (x+mouseX)/2;
       ymerkez = (y+mouseY)/2;
       glutSetCursor(GLUT_CURSOR_CROSSHAIR);
       glColor3ub(renk[0], renk[1], renk[2]);

       glBegin(GL_LINE_LOOP);
       int i;
       for (i=0 ; i <=360 ; i++)
       {
             float rad= i*3.14159265/180;
             glVertex2i(xmerkez + cos(rad)*xderece, ymerkez + sin(rad)*yderece);
       }
       glEnd();
       glFlush();
         break;

    case 4:
            if (x<79)
            x=85;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            glColor3ub(renk[0], renk[1], renk[2]);
            glBegin(GL_LINE_LOOP);
            glVertex2i(mouseX,mouseY);
            glVertex2i(mouseX,y);
            glVertex2i(x,y);
            glVertex2i(x,mouseY);
            glEnd();
            glFlush();

      break;

    case 5:
           if (x<79)
            x=85;
            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            glColor3ub(renk[0], renk[1], renk[2]);
            glBegin(GL_LINE_LOOP);
            glVertex2i(mouseX,mouseY);
            glVertex2i(mouseX,y);
            glVertex2i(x,y);
            glEnd();
            glFlush();
     break;

    case 6:
            if (x<79)
            x=85;
          glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
          glColor3ub(renk[0], renk[1], renk[2]);
          glBegin(GL_POINTS);
          glVertex2i(x,y);
          glGetFloatv(GL_POINT_SIZE, 1000);
          glGetFloatv(GL_POINT_SIZE_GRANULARITY, 1000);
          glGetFloatv(GL_POINT_SIZE_RANGE,1000);
          glEnd();
          glFlush();
      break;

    case 7:
           if (x<79)
            x=85;
          glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
          glColor3ub(renk[0], renk[1], renk[2]);
          glBegin(GL_POLYGON);
          glVertex2i(x-4,y-4);
          glVertex2i(x-4,y+4);
          glVertex2i(x+4,y+4);
          glVertex2i(x+4,y-4);
          glEnd();
          glFlush();
      break;

    case 8:

           if (x<79)
            x=85;
          glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
          glColor3ub(255,255,255);
          glBegin(GL_POLYGON);
          glVertex2i(x-5,y-5);
          glVertex2i(x-5,y+5);
          glVertex2i(x+5,y+5);
          glVertex2i(x+5,y-5);
          glEnd();
          glFlush();
      break;


}
}

void mouse(int btn, int belirt, int x, int y)


{
      if(btn==GLUT_LEFT_BUTTON && belirt==GLUT_DOWN)
      {
            mouseX=x;
            mouseY=y;

             if (x>5 && x<50 && y>5 && y<70)
                  secenek=1;
            if (x>5 && x<74 && y>75 && y<140)
                  secenek=2;
            if (x>5 && x<74 && y>145 && y<210)
                  secenek=3;
            if (x>5 && x<74 && y>215 && y<280)
                  secenek=4;
            if (x>5 && x<74 && y>285 && y<350)
                  secenek=5;
            if (x>5 && x<74 && y>355 && y<420)
                  secenek=6;
            if (x>5 && x<74 && y>425 && y<490)
                  secenek=7;
            if (x>5 && x<74 && y>495 && y<560)
                  secenek=8;


            if (x>5 && x<74 && y>565&& y<785)
            {
                  glReadPixels(x,W_yukseklik-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,renk);

            }

            if(x>5 && x<74 && y>790 && y<855)
            {
                 display();
                 secenek=7;
            }
            if(x>5 && x<74 && y>860 && y<925)
            {

                secenek=9;
                isimverme(name);
                kaydet(name);
            }
            if(x>5 && x<74 && y>930 && y<995)
            {
                secenek=10;
                isimverme(name);
                ac(name);
            }

      }

      if(btn==GLUT_LEFT_BUTTON && belirt==GLUT_UP )
      {
                     ekran_depo();

      }

}
void display()
{
    glClearColor(0.9,0.9,0.9,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 5);
        glVertex2i(5, 70);    //cizgi
        glVertex2i(74, 70);
        glVertex2i(74, 5);
    glEnd();
  glBegin(GL_LINE_LOOP);
        glColor3ub(255, 0, 0);
        glVertex2i(66, 66);
        glVertex2i(10, 10);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 75);
        glVertex2i(5, 140);      //cember
        glVertex2i(74, 140);
        glVertex2i(74, 75);
    glEnd();
     glColor3f(255.0f, 0.0f, 0.0f);


          int i;
            float deger = 600;
            float yaricap = sqrt(deger);
            glBegin(GL_LINE_LOOP);
            for (i=0; i <= 360; i++)
            {
               float derece = i*3.14159/180;
               glVertex2i(40 + cos(derece)*yaricap,110+ sin(derece)*yaricap);
            }
   glEnd();

   glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 145);
        glVertex2i(5, 210);
        glVertex2i(74, 210);
        glVertex2i(74, 145);
    glEnd();
  glBegin(GL_LINE_LOOP);

         glColor3f(255.0f, 0.0f, 0.0f);
            for (i =0; i <= 360; i++)
            {
               float derece = i*3.14159/180;
               glVertex2i(  39+cos(derece)*24,25 + 153+sin(derece)*18);
            }
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 215);
        glVertex2i(5, 280);
        glVertex2i(74, 280);
        glVertex2i(74, 215);
    glEnd();

   glColor3ub(255, 0, 0);
   glRasterPos3f(20,385,0);
   yazi_yaz("Kalem");
   glRasterPos3f(20,400,0);
   yazi_yaz("Cizimi");

   glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 285);
        glVertex2i(5, 350);
        glVertex2i(74, 350);
        glVertex2i(74, 285);
    glEnd();


  glColor3ub(255, 0, 0);
    glRasterPos3f(24,530,0);
   yazi_yaz("Silgi");
  glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 355);
        glVertex2i(5, 420);
        glVertex2i(74, 420);
        glVertex2i(74, 355);
    glEnd();



    glColor3ub(255,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(22,227);
    glVertex2i(22,270);
    glVertex2i(56,270);
    glVertex2i(56,227);
    glEnd();
    glFlush();
    glDisable(GL_LINE_STIPPLE);

 glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5,425);
        glVertex2i(5,490);
        glVertex2i(74,490);
        glVertex2i(74,425);
    glEnd();
    glColor3ub(255, 0, 0);
    glRasterPos3f(22,460,0);
    yazi_yaz("Firca");

     glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5,495);
        glVertex2i(5,560);
        glVertex2i(74,560);
        glVertex2i(74,495);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3ub(255, 0, 0);
        glVertex2i(39, 295);
        glVertex2i(63, 340);
        glVertex2i(15, 340);

    glEnd();
 glBegin(GL_POLYGON);            //renk
        glColor3ub(255, 0, 0);
        glVertex2i(74, 565);
        glColor3ub(0, 255, 0);
        glVertex2i(5, 565);
        glColor3ub(0, 0, 255);
        glVertex2i(5, 785);
        glColor3ub(0, 0, 0);
        glVertex2i(74,785);
    glEnd();

       glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 565);
        glVertex2i(5, 785);
        glVertex2i(74, 785);
        glVertex2i(74, 565);
      glEnd();

      glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 855);
        glVertex2i(5, 790);
        glVertex2i(74, 790);
        glVertex2i(74, 855);
    glEnd();

    glColor3ub(0, 0, 255);
    glRasterPos3f(18,827,0);
    yazi_yaz("  Yeni ");

    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 925);
        glVertex2i(5, 860);
        glVertex2i(74, 860);
        glVertex2i(74, 925);
    glEnd();
    glColor3ub(0, 0, 255);
    glRasterPos3f(10,895,0);
    yazi_yaz("  Kaydet          ");

    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(5, 995);
        glVertex2i(5, 930);
        glVertex2i(74, 930);
        glVertex2i(74, 995);
    glEnd();
    glColor3ub(0, 0, 255);
    glRasterPos3f(22,965,0);
    yazi_yaz("  Ac ");

   glBegin(GL_LINE_LOOP);
        glColor3ub(0, 0, 0);
        glVertex2i(79, 5);
        glVertex2i(79, 995);
        glVertex2i(1911, 995);
        glVertex2i(1911, 5);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2i(80, 6);
        glVertex2i(80, 994);
        glVertex2i(1910, 994);
        glVertex2i(1910, 6);
    glEnd();


    ekran_depo();
    glFlush();
}

void yazi_yaz(char *yazi)
{
      char* harf;
 for(harf=yazi; *harf != '\0'; harf++)
   {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*harf);
   }
}

int main(int argc, char** argv)
{
 glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1920,1000);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Paint");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1920,1000,0,0,1);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(ciz);
    ilInit();
    ilutInit();
    iluInit();


 glutMainLoop();

}
