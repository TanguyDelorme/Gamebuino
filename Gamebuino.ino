#include <Gamebuino-Meta.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>

int positionX = 32;
int speedX = 1;
int positionY = 32;
int speedY = 0;
int ballSize = 2;
int pauseX = 0;
int pauseY = 0;
int mange = 0;

//taille écran
int maxX = 80;
int maxY = 64;

//position du carré a manger
int newRandomX = 0;
int newRandomY = 0;

int coordsX[500];
int coordsY[500];
int previousCoordsX[500];
int previousCoordsY[500];
int previousPosX = 0;
int previousPosY = 0;

void randomSquare(){  
  gb.display.setColor(RED);
  gb.display.fillRect(newRandomX, newRandomY, ballSize, ballSize);
}

void randomNumber(){  
  newRandomX = rand()%(maxX);
  newRandomY = rand()%(maxY);
}

void isSquareHit(){
  if(newRandomX + 1 >= positionX and newRandomX +1 <= positionX + ballSize and newRandomY + 1 >= positionY and newRandomY + 1 <= positionY + ballSize){
    randomNumber();    
    growSnake();
    mange = mange + 1;
  }
  updateSnake();
}

void growSnake(){
  coordsX[mange] = previousPosX;
  coordsY[mange] = previousPosY + mange*ballSize;
}

void updateSnake(){
  for(int i = 0; i < mange; i++)
  {
    coordsX[i] = previousCoordsX[i];
    coordsY[i] = previousCoordsY[i] ;
  }
}

void copyCoord()
{
  for(int i = 0; i< mange ; i++){
    previousCoordsX[i] = coordsX[i];
    previousCoordsY[i] = coordsY[i];
  }
}

void setup() {
  gb.begin();
  randomNumber();
 }

void loop() {
  while (!gb.update());
  gb.display.clear();  
  previousPosX = positionX;
  previousPosY = positionY;
  copyCoord();
  
  //Affiche la proie du serpent
  randomSquare();  
  //collisions du serpent avec ses proies
  isSquareHit();
  //Mise a jour de la position du serpent selon l'orientation
  positionX = positionX + speedX;
  positionY = positionY + speedY;
  
  //collisions du serpent sur les bords
  if(positionX <= 0){
    speedX = 0;
  }
  if(positionX >= gb.display.width() - ballSize){
    speedX = 0;
  }
  if(positionY <= 0){
    //on part en bas
    speedY = 0;
  }
  if(positionY >= gb.display.height() - ballSize){
    //on part en haut
    speedY = 0;
  }

  gb.display.fillRect(previousPosX, previousPosY, ballSize, ballSize);
  gb.display.setColor(WHITE);
  gb.display.fillRect(positionX, positionY, ballSize, ballSize);
  for(int i = 0; i < mange; i++)
  {
    gb.display.fillRect(coordsX[i], coordsY[i], ballSize, ballSize);
  }

  
   //Orienter le serpent avec les bouttons
   if(gb.buttons.pressed(BUTTON_UP)){
    if(speedY != 1)
    {
      speedY = -1;
      speedX = 0;
    }    
  }
  if(gb.buttons.pressed(BUTTON_DOWN)){
    if(speedY != -1)
    {
    speedY = 1;
    speedX = 0;
    }
  }
  if(gb.buttons.pressed(BUTTON_LEFT)){
    if(speedX != 1)
    {
    speedX = -1;
    speedY = 0;
    }
  }
  if(gb.buttons.pressed(BUTTON_RIGHT)){
    if(speedX != -1)
    {
    speedX = 1;
    speedY = 0;
    }
  }

  //Pause, appuyer sur une fleche pour reprendre
  if(gb.buttons.pressed(BUTTON_A)){
    speedX = 0;
    speedY = 0;
  }
}



