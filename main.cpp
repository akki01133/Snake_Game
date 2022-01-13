#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
#include<ctime>
#include<windows.h>
#include<math.h>


using namespace std;
//grid rows and collums
#define gr 30  
#define gc 77  

char grid[gr][gc];
vector<pair<int,int>> V;  //vector to store snake position
pair<int,int> temp;       //to store the position of tail.
int len;    //length of snake
int dx,dy;  //velocity of snake
int fx,fy;  //food co-ordinate
char KbCh;  //keyboard char hit
bool gameOver; //check whether a key is pressed or not
int highscore=0; // store the highscore ever made!


#define row 6
#define col 20
char g[row][col];
string status="up";
int start=0;
int i=0;
string str1="New Game",str2="Load Game";
int savedORdied = -1;

//generate food
void foodGen()
{
    srand(time(0));
    fx=rand()%76;
    while(fx%2==0)
      fx=rand()%76;

    fy=rand()%30;
    while(!fy || fy==gr-1)
      fy=rand()%30;
    
}

//initial setup
void initials()
{   //setting four bourder corners!
    grid[0][0]=(char)218; grid[0][gc-1]=(char)191;grid[gr-1][0]=(char)192; grid[gr-1][gc-1]=(char)217;
    
    //creating bordr lines!
    for(int c=1;c<gc-1;c++)
       {grid[0][c]=(char)196;
       grid[gr-1][c]=(char)196;}
     for(int r=1;r<gr-1;r++)
       {grid[r][0]=(char)179;
       grid[r][gc-1]=(char)179;}

    
    //snake moves in x-direction at beginig
    dx=2;dy=0;

    //initailly stopped
    KbCh='p';

    //gameover
     gameOver=0;
}

//start a new game
void initials_new()
{    //define the initial snake!
    len=4;
    V.clear();
     for(int i=2*len-1;i>=1;i-=2)
        V.push_back(make_pair(gr/2,i));

    //snake moves in x-direction at beginig
    dx=2;dy=0;

    //generate food!
    foodGen();
}

// load the saved game
void initials_load()
{  
    V.clear();
    fstream saved;
    int a,b;
    saved.open("saved.txt",ios::in);
    saved>>a;
    fx=a;
    saved>>a;
    fy=a;
    saved>>a;
    len=a;
    for(int j=0;j<len;j++)
      {saved>>a;
       saved>>b;
       V.push_back(make_pair(a,b));
      } 
    saved.close();  
    
    //snake moves in x-direction at beginig
    dx=2;dy=0;
}
//user key press actions
 void keyEnter()
{
    char ch;
    fstream save;      //save the game
    if(kbhit())
     { ch=getch();
       if(ch=='a' || ch=='s' || ch=='d' || ch=='w' ||ch=='p' || ch=='r' || ch=='g')  
          KbCh=ch;
     }

       switch(KbCh)
       {
           case 'a'://move left
                    if(dx==2)
                       {KbCh='d';break;}
                    else 
                      { dx=-2;dy=0;
                        temp=V[len-1];
                        for(int i=V.size()-1;i>=1;i--)
                            V[i]=V[i-1];
                        V[0].second+=dx;
                        if(V[0].second==-1) 
                            gameOver=1;
                       }
                    break;
                    
                      
           case 'd'://right
                    if(dx==-2)
                      {KbCh='w';break;}
                    else 
                      { dx=2;dy=0;
                        temp=V[len-1];
                        for(int i=V.size()-1;i>=1;i--)
                            V[i]=V[i-1];
                        V[0].second+=dx;
                        if(V[0].second==gc)
                            gameOver=1;
                       }
                     break;
                      
           case 'w'://move up
                    if(dy==1)
                      {KbCh='s';break;}
                    else 
                      { dy=-1;dx=0;
                        temp=V[len-1];
                      for(int i=V.size()-1;i>=1;i--)
                            V[i]=V[i-1];
                       V[0].first+=dy;
                       if(V[0].first==0)
                          gameOver=1;
                       }
                      break;
           case 's'://move down
                    if(dy==-1)
                      {KbCh='w';break;}
                    else 
                      { dy=1;dx=0;
                        temp=V[len-1];
                      for(int i=V.size()-1;i>=1;i--)
                            V[i]=V[i-1];
                       V[0].first+=dy;
                       if(V[0].first==gr-1)
                          gameOver=1;
                       }
                      break;
                      
            case 'p'://pause the game
                     break;
            case 'r'://reload the game 
                     initials();
                      break;
            case 'g'://save the game
                     save.open("saved.txt",ios::out|ios::trunc);
                       if(save.is_open())
                       {
                         save<<fx<<endl;
                         save<<fy<<endl;
                         save<<len<<endl;
                         for(int j=0;j<len;j++)
                         {
                           save<<V[j].first<<endl;
                           save<<V[j].second<<endl;
                         }

                       }
                     gameOver=1;  //save the game and quit
                     save.close();
                     break;
       }
       for(int i=1;i<len;i++)
       {
         if(V[i]==V[0])
           gameOver=1;
       }
    
}

void printgrid(char grid[][gc])
{   system("cls");

    //set the fielrempty with spaces
    for(int r=1;r<gr-1;r++)
      {for(int c=1;c<gc-1;c++)
          grid[r][c]=' ';
      }
    //food 
    grid[fy][fx]='0';
    keyEnter();
    //set snake!
    for(auto it: V)
    {
        grid[it.first][it.second]=(char)254;
    }

    

    printf("Score:%d\t\t\t\t\t\t\tHighscore: %d\n",len-4,highscore);
    for(int r=0;r<gr;r++)
    {
        for(int c=0;c<gc;c++)
              printf("%c",grid[r][c]);

        printf("\n");
    }
    //fooed eating action
    if(V[0].first==fy && V[0].second==fx)
        {foodGen();
         len++;
         V.push_back(temp);
         }
}

int highScoreRead()
{
   fstream score;
   int line;
   int i=0,size;
   score.open("highscore.txt",ios :: in);
   score>>line;
   score.close();
   highscore=line;
   return highscore;
}

void highScoreWrite()
{
  fstream score;
   score.open("highscore.txt",ios :: out | ios:: trunc);
   score<<len-5;
   score.close();
}
//initail game dispalay
void newORload_Keypress()
{char ch; 
  
  ch=getch();
  
    switch(ch)
    {
      case 'w': if(status!="up")
                   i=0;
                status="up";
              break;
      case 's': if(status!="down")
                   i=3;
                   status="down";
                   break;
      

      case 13 ://hit enter to select option
               if(status=="up")
                  start=1;
               else
                  start=2;
                break;
    }
  
  
}

void newORloadGrid(int i)
{   system("cls");
    for(int r=0;r<row;r++)
    {  for(int c=0;c<col;c++)
          g[r][c]=' ';
    }

    for(int c=0;str1[c];c++)
          g[1][c+6]=str1[c];
    for(int c=0;str2[c];c++)
          g[4][c+6]=str2[c];
    
    g[i][0]=(char)218; g[i][col-1]=(char)191;g[i+2][0]=(char)192; g[i+2][col-1]=(char)217;

    for(int c=1;c<col-1;c++)
     {g[i][c]=(char)196;
      g[i+2][c]=(char)196;}
  
     g[i+1][0]=(char)179;
     g[i+1][col-1]=(char)179;

     printf("\n\n\n\n\n\n\n\n\t\t\t\t");
     for(int r=0;r<row;r++)
     {
        for(int c=0;c<col;c++)
              printf("%c",g[r][c]);

        printf("\n\t\t\t\t");
     }
    cout<<endl;
    //enter user
    newORload_Keypress();
}

void startinDisplay()
{   HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    string str="Hit any keys to start$!";
    printf("\n\n\n\n\n\n\n\n\t\t\t\t");
    for(int i=0;str[i];i++)
    { printf("%c",str[i]);
      if(i==11 || i==21)
      {  usleep(300000);
         cout<<(char)8;  //backspace
      }
      usleep(90000);
      if(str[i]==' ')
        usleep(100000);
    }
    getch();
    system("cls");

    //new or load game
    while(!start){
     newORloadGrid(i);
  }
}

void GameOverScreen(){
    for(int i=0;i<(gr/2) -4;i++){
      cout<<"\n";
    }
    cout<<"\t\t\t\tGameOver\n";
    cout<<"\t\t\t\tScore:"<<len-4<<"\n";
    cout<<"\t\t\t\tHighScore:"<<highScoreRead();
    for(int i=0;i<(gr/2) +4;i++){
      cout<<"\n";
    }
}
int main()
{   system("cls"); 
    //read highscore from file
    highScoreRead();
    
    //display crazy struff;
    startinDisplay();

    //setup initials!
    initials();
    if(start==1)
      initials_new();
    else if(start==2)
      initials_load();
      

    //main program starts here
     while(!gameOver)      
     {   
         printgrid(grid);
         usleep(120000);
     }
     sleep(1);
     system("cls");
     GameOverScreen();
     //updating highscore file
     if(highscore<(len-5))
       highScoreWrite();
   
    return 0;
}
