#include <iostream>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include "RGB.h"
#include <fstream>
#include <mutex> 
//------------------------------------------initialisation---------------------------------------------------------
#define WIDTH  800
#define HEIGHT 800
#define THREAD 3  

double X = -1;
double Y = 1;

#define convertx(x) ((x)*(Y*2)/WIDTH - Y) 
#define converty(y) ((y)*(X*2)/HEIGHT - X)

long double reel = -0.772691322542185 , imagi = 0.124281466072787;
int iteration = 300;
double H;
double S=69;
double V=255;

std::mutex mtx;
cv::Mat newImg(WIDTH, HEIGHT, CV_8UC3); 
cv::Vec3b black(0,0,0);

//----------------------------------------------Calcul de la fractale----------------------------------------
void* Calculjulia(void* arg) 
{
    long double x, y, tmp;
    int z;

  for (int i = 0 ; i < HEIGHT ; i++){
      for (int j = 0 ; j < WIDTH ; j++){
        x = convertx(i);
        y = converty(j);
        z = 0;

        while (x*x + y*y < 4 && z < iteration)
        {
          tmp = (x * x - y * y) + reel;
          y = (x * y + x * y) + imagi;
          x = tmp;
          z++;
        }
        H = (z*360)/iteration;
        HSV data = HSV(H,S,V);
        RGB value = HSVToRGB(data);
        cv::Vec3b color(value.R, value.G, value.B);
        if(z!=iteration)
        {
          newImg.at<cv::Vec3b>(cv::Point(i, j)) = color;
        }
        else
        {
          newImg.at<cv::Vec3b>(cv::Point(i, j)) = black;
        }
      }
    
  }
  return NULL;
}

//------------------------------------------main----------------------------------------------------------

int main(int argc, char* argv[])
{
  pthread_t Tab[THREAD]; 
  int julia_id[THREAD];   


  Init:  

  struct timeval temps_avant, temps_apres;
  gettimeofday (&temps_avant, NULL);
        mtx.lock();
  for (int i = 0 ; i < THREAD ; i++) {
    julia_id[i] = i;
    pthread_create(&Tab[i], NULL, Calculjulia, (void*) &julia_id[i]); 
  }
        mtx.unlock();
  gettimeofday (&temps_apres, NULL); 
  double TmpEx=((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec)-temps_avant.tv_usec;
 

//-----------------------------------------------exriture des données dans un fichier text-----------------------
string const nomFichier("TTHREAD.dat"); 
  ofstream monFlux("THREAD.dat", ios::app);

       if(monFlux)    
             {
              time_t temps;
              struct tm datetime;
              char  format[32];
              time(&temps);
              datetime = *localtime(&temps);
 
              strftime(format, 32, "%Y-%m-%d ", &datetime);
 
              monFlux << "\n#Fichier test: sauvegarde des résultats." << endl;
              monFlux << "#Date " << format << "." << endl;
              monFlux <<"#premier colonne nombre de thread  \n "<<"#Deuxième colonne est temps d'execution en ms"<<endl;
              monFlux << THREAD <<" "<< TmpEx <<endl;                
monFlux.close();
               }
        else
            {
              cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
            } 


//-----------------------------------------------interaction avec utilisateur--------------------------------------
        cout<< "Vous pouvez changer votre fractale comme suite:\n"<<"\n"<< "Touche: 'a' et 'z' pour augmenter et reduire la partie réelle de votre fractale \n"<<"Touche: 's' et 'd' pour le zoom \n"<<"Touche: 'o' et 'p' pour réduire et augmenter la partie imaginaire\n"<< endl;
         cout<<"------------------------------Temps d'execution--------------------------------- \n"<<" avec un nombre de thread    "<< THREAD<<"  :temps en us: "<< TmpEx <<".\n"; 


while(char key = cvWaitKey(2)) {
   switch(key){

      case 'a':
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
  
       }
      reel = reel + 0.01;
      goto Init; 
      break;
      
      case 'z':
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
      }
      reel = reel - 0.01;
      goto Init;
      break;
       
      case 'o':
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
      }
      imagi = imagi + 0.01;
      goto Init;
      break;
      
      case 'p':
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
      }
      imagi = imagi - 0.01;
      goto Init;
      break;

      
      case 'd':
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
      }
      X += 0.01;
      Y -= 0.01;
      goto Init;
      break;
 
      case 's': 
      for (int i = 0 ; i < THREAD ; i++) {
      pthread_cancel(Tab[i]);
      }
      X -= 0.01;
      Y += 0.01;
      goto Init;
      break;

      default:
      break;
    }
    if (key == 'q')
    break;
    imshow("Fractal de Julia", newImg);
  }
  cvDestroyWindow("image"); 



  return 0;
}
