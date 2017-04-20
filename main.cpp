/**
 * \file main.cpp
 * \brief Programme de tests.
 * \author saimi lamine
 * \version 0.1
 * \date 01-04-2017
 *
 * Programme pour generé la fractal de julia
 *
 */



#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <thread>
#include <semaphore.h>
#include <chrono>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <fstream>
/
using namespace std;
using namespace cv;
Mat image;

 #define ITERATIONMAX 400
 #define V 4
 #define HEIGHT 500
 #define WIDTH 500
#define Nb_Thread 10


long double r=0.400,i=-0.192;
double H = 0;
double W = 0;

void *Julia(void *arg);



void hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v);
/**
 * \fn int main( int argc, char** argv )
 * \brief Entrée du programme.
 *  \brief recation des thread pour generé la fractal
 * \return 0
 */
int main( int argc, char** argv )
{
pthread_t thread[Nb_Thread];
  image = cv::Mat(WIDTH, HEIGHT, CV_8UC3);
 auto t1 = Clock::now();
refresh:
for(int i=0;i<Nb_Thread;i++)
{
pthread_create(&thread[i], NULL, Julia, (void*)NULL);
}
 auto t2 = Clock::now();
    std::cout << "temps de calcul: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds -> " <<(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10,-9)<<" secondes"<< std::endl;




 while(char key = cvWaitKey(66)) {
    switch(key){
      case 'a':



      r = r + 0.1;
      goto refresh;
      break;
      case 'z':

      r = r - 0.1;
      goto refresh;
      break;
      case 'o':

      i = i + 0.1;
      goto refresh;
      break;
      case 'p':

      i = i - 0.05;
      goto refresh;
      break;


      case 'd':

      H -= 100;
      W -= 100;
      goto refresh;
      break;
      case 's':

      H += 100;
      W += 100;
      goto refresh;
      break;

      default:
      break;
    }
    if (key == 'q')
    break;
    imshow("fractale",image );
  }
  cvDestroyWindow("fractale");


  return 0;
}
/**
 * \fn  *Julia(void *arg);
 * \brief Fonction de creation de la fractal
 *
 * \param elle a pas de parametre
 * \return pas de retour
 */


 void *Julia(void *arg){
std::complex<long double> c(r, i);
  for(int x=0;x<WIDTH;x++){
      for(int y=0;y<HEIGHT;y++){
        long double newX=((long double)((long double)x-((long double)((WIDTH)-H)/2))/((long double)((WIDTH)-H)/2));
        long double newY=((long double)((long double)y-((long double)((HEIGHT)-W)/2))/((long double)((HEIGHT)-W)/2));
        std::complex<long double> point(newX,newY);
        int iteration=0;
        long double norm = std::norm(point);
        while(iteration<ITERATIONMAX && norm<V){
          point=(point*point)+c;
          norm = std::norm(point);
          iteration++;
        }
        if(iteration==ITERATIONMAX && norm<V){
          image.at<Vec3b>(x,y)[0]=0;
          image.at<Vec3b>(x,y)[1]=0;
          image.at<Vec3b>(x,y)[2]=0;
        }
        else{
          unsigned char couleur=(int)((float)iteration/(float)ITERATIONMAX*360);
          unsigned char r,g,b;
	  hsvtorgb( &r,&g,&b,couleur,150,150);
	  image.at<Vec3b>(x,y)[0]=b;
          image.at<Vec3b>(x,y)[1]=g;
          image.at<Vec3b>(x,y)[2]=r;
      }
    }
  }
return NULL;
 }

/**
 * \fn hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v)
 * \brief fonction de calcule des couleur rgb
 *
 * \param r g b h s v des degrer de couleur
 * \return un code coleur rgb .
 */


void
hsvtorgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v)
{
    unsigned char region, fpart, p, q, t;

    if(s == 0) {

        *r = *g = *b = v;
        return;
    }


    region = h / 43;

    fpart = (h - (region * 43)) * 6;

    /
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * fpart) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;


    switch(region) {
        case 0:
            *r = v; *g = t; *b = p; break;
        case 1:
            *r = q; *g = v; *b = p; break;
        case 2:
            *r = p; *g = v; *b = t; break;
        case 3:
            *r = p; *g = q; *b = v; break;
        case 4:
            *r = t; *g = p; *b = v; break;
        default:
            *r = v; *g = p; *b = q; break;
    }

    return;
}
