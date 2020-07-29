#include<iostream>
#include<conio.h>
#include<windows.h>
#include<MMsystem.h>
using namespace std;

//declare boolean variable to continue game
bool gameOver;

//declare variables for map dimensions
const int width=50;
const int height=25;

//variables for head & fruit position co-ordinates
int x, y, fruitX, fruitY;

int score;

//to track direction of snake
enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir; //holds direction of snake

//to store x and y co-ordinates of tail:
int tailX[100];
int tailY[100];

//to specify length of tail:
int tail_length;

void setup()
{
    gameOver=false;
    dir=STOP; //snake won't move until we start moving it
    
    //set head position in middle of map:
    x=width/2;  
    y=height/2;
    
    //set fruit position at random position:
    fruitX= rand() % (width-1);
    fruitY= rand() % (height-1);
    
    score=0; //initially score is 0
}

void draw()
{
    system("cls"); //call windows command to clear screen
   cout<<endl<<endl<<endl<<"     ===== HAPPY NAGPANCHAMI MY SNAKE! ====="<<endl<<endl;
   //to print top wall of map
    for(int i=0;i<width+1;i++) 
        cout<<"=";
    cout<<endl;
        
   //to print map area (just like printing matrix)
   for(int i=0;i<height;i++)
   {
       for(int j=0;j<width;j++)
       {
           if(j==0 || j==width-1)
               cout<<"|";
           if(i==y && j==x) //to print snake's head
               cout<<"O";
           else if(i==fruitY && j==fruitX) //to print fruit's position
               cout<<"@";
           else 
           {
               bool print=false;
               for(int k=0;k<tail_length;k++)
               {
                   if(j==tailX[k] && i==tailY[k])
                   {
                        cout<<"o";
                        print=true; 
                   }
               }
               if(!print)
                   cout<<" ";
           }
       }
       cout<<endl;
   }
        
   //to print bottom wall of map
    for(int i=0;i<width+1;i++) 
        cout<<"=";
        
    cout<<endl<<endl;
    cout<<"SCORE:"<<score<<endl;
}

void input()
{
    if(_kbhit()) //returns true if keyboard key is pressed
    {
        switch(_getch()) //returns ASCII value of character that was pressed
        {
            case 'a': dir=LEFT;
                        break;
            case 'd': dir=RIGHT;
                        break;
            case 'w': dir=UP;
                        break;
            case 's': dir=DOWN;
                        break;
            case 'x': gameOver=true;
                        break;
        }
    }
}

void logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    
    //to follow head:
    tailX[0]=x;
    tailY[0]=y;
    
    for(int i=1;i<tail_length;i++) //i starts from 1 bcz we already store first subtail 
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    
    switch(dir) //to move in that direction
    {
        case LEFT: 
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    
    //if snake touches wall:
    //if(x>width || x<0 || y>height || y<0) 
        //gameOver=true;
    if(x>=width-1)
        x=0;
    else if(x<0)
        x=width-1;
        
    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;
        
    //to check if head touches tell:
    for(int i=0;i<tail_length;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
            gameOver=true;
    }
    
    //when fruit is eaten:
    if(x==fruitX && y==fruitY)
    {
        cout<<'\a'<<endl;
        score+=10;
        tail_length++; 
        
        //to print fruit at another location after it is eaten
         fruitX= rand() % (width-1);
         fruitY= rand() % (height-1);
    }
}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(5); //slows down game
    }
}