#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>

using namespace std;

class Player
{
public:
    int x,y; //Position on map
    Player(int width) {x = width / 2; y = 0;} //Width is width of the map and it is necessary to point the starting position of the player
};

class Lane
{
  private:
    deque<bool> cars; //If true, then there is a car in the position, false no car
    bool right;

  public:
    Lane(int width)
    {
        for(int i = 0; i < width; i++)
            cars.push_front(true);
        right = rand() % 2; //Generates values or 0 or 1 (true or false), when right is true then a lane will be generated from left to right, otherwise opposite direction
    }
    //Shift car in array (X-axis)
    void MoveCar()
    {
        if(right)
        {
            if(rand() % 10 == 1) //This is meant to randomize how often cars will come thru one lane, increases probability, but does not guarantee that cars will be adjacent
                cars.push_front(true); 
            else
                cars.push_front(false);
    
            cars.pop_back(); //car will go out of the lane        
        }
        else 
        {
            if(rand() % 10 == 1) 
                cars.push_back(true); 
            else
                cars.push_back(false);
    
            cars.pop_front(); //car will go out of the lane        
            
            
        }
    }
    bool CheckPos(int pos) { return cars[pos]; } //This returns whether or not there is a car in that position, where pos is index of deque
};

class Game
{
private:
    bool quit;
    int num_lanes;
    int width;
    int score;
    Player *player;
    vector<Lane*> street; //Collection of lanes (lane is a deque)
    
public:
    
  Game(int w = 20, int h = 20)
  {
      num_lanes = h;
      width = w;
      quit = false;
      score = 0;
      
      for(int i = 0; i < num_lanes; i++)
      {
          street.push_back(new Lane(width));
      }
      player = new Player(width);
  }
  void Draw()
  {
      system("cls"); //clears the screen
      
      for(int i = 0; i < num_lanes; i++) // y-axis
      {
          for(int j = 0; j < width; j++) // x-axis
          {
                if(street[i]->CheckPos(j) && i != 0 && i != num_lanes - 1) // If a true value of deque is at a width position, then...
                    cout << "#"; // Print car
                else if(player->x == j && player->y == i) // If position of player in x-y coordinate is equals to i and j, then...
                    cout << "v"; // Print player
                else
                    cout << " "; // If not player or not cars, then it is the empty street
          }
          cout << endl;
      }
      cout << "Score: " << score << endl;
  }  
  void Input()
  {
      if(_kbhit())
      {
          char current = _getch();
          if(current == 'a')
              player->x--;
            
          if(current == 'd')
              player->x++;
           
          if(current == 'w')
              player->y--;
          
          if(current == 's')
              player->y++;
            
          if(current == 'q')
              quit = true;
      }  
  }
  void Logic()
  {
      for(int i = 1; i < num_lanes - 1; i++)
      {
          if(rand() % 10 == 1)
              street[i]->MoveCar();
          if(street[i]->CheckPos(player->x) && player->y == i)
          {
              quit = true;
              cout << "\x07"; //This makes the windowns' error-message sound.
          }
        
      }
      
      if(player->y == num_lanes -1)
      {
          score++;
          player->y = 0;
      }
  }
  void Run()
  { 
      //Game loop
      while(!quit)
      {
          Draw();
          Input();
          Logic();
      }
      
  }
  ~Game()
  {
      delete player;
      for(auto lanes : street)
          delete lanes;
  }
};


int main() {
    
    srand(time(NULL)); // Seeding the random generator with time (consider the best way)
    
    Game my_game(50,10);
    my_game.Run();
    
    cout << "Game over!" << endl;
    return 0;
    }