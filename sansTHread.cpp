#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <thread>
#include <semaphore.h> 
#include <pthread.h> 
#include <sys/time.h>
using namespace std;
using namespace cv;
Mat mtrc;
 
 #define V 4
 #define ITER 300
 #define HEIGHT 600
 #define WIDTH 500
RNG rng( 0xFFFFFFFF );
double R=100;
double G=80;
double B=150;
 int i;



std::complex<long double> c(  -0.772691322542185 ,0.124281466072787);

/*fonction qui permet recuperer l'image à l'ecran */
int main( int argc, char** argv )
{
struct timeval temps_avant, temps_apres;
  gettimeofday (&temps_avant, NULL);
 
  mtrc=cv::Mat(WIDTH, HEIGHT, CV_8UC3);
   		 clr();
  gettimeofday (&temps_apres, NULL);
  printf("temps en us: %ld us\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) -          temps_avant.tv_usec);
     while( true )
     {
       
     imshow("julia frame", mtrc ); 
 if(cvWaitKey(5) > 0){
  
     }

}
  return 0;

}


