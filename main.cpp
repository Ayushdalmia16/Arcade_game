// Including headers for each game here
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h> //for console handling
#include <dos.h>
#include <time.h> //for generating random numbers
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
using namespace std;
//car game
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//framework for holding coordinates
COORD CursorPosition;
//coordinates
int enemyY[3]; //position for car to avoid
int enemyX[3];
int enemyFlag[3];
char car[4][4] = { ' ','±','±',' ',
'±','±','±','±',
' ','±','±',' ',
'±','±','±','±' };
int carPos = WIN_WIDTH/2;
int score = 0;
//to place cursor at specific position
void gotoxy(int x, int y){
CursorPosition.X = x;
CursorPosition.Y = y;
SetConsoleCursorPosition(console, CursorPosition);
}//moving pointer on screen
void setcursor(bool visible, DWORD size) {
if(size == 0)
size = 20;
CONSOLE_CURSOR_INFO lpCursor;
lpCursor.bVisible = visible;
lpCursor.dwSize = size;
SetConsoleCursorInfo(console,&lpCursor);
}
//drawing border for game
void drawBorder(){
for(int i=0; i<SCREEN_HEIGHT; i++){
for(int j=0; j<17; j++){
gotoxy(0+j,i); cout<<"±";
gotoxy(WIN_WIDTH-j,i); cout<<"±";
}
}
for(int i=0; i<SCREEN_HEIGHT; i++){
gotoxy(SCREEN_WIDTH,i); cout<<"±";
}
}
//generating random x coordinate for enemy
void genEnemy(int ind){
enemyX[ind] = 17 + rand()%(33);
}
//draws enemy at current position
void drawEnemy(int ind){
if( enemyFlag[ind] == true ){
gotoxy(enemyX[ind], enemyY[ind]); cout<<"";
gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** ";
gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"";
gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";
}
}
//erases enemy at current position
void eraseEnemy(int ind){
if( enemyFlag[ind] == true ){
gotoxy(enemyX[ind], enemyY[ind]); cout<<" ";
gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ";
gotoxy(enemyX[ind], enemyY[ind]+2); cout<<" ";
gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ";
}
}
//resets enemy to initial position and generates new random x-coordinate.
void resetEnemy(int ind){
eraseEnemy(ind);
enemyY[ind] = 1;
genEnemy(ind);
}
//draws the car at its current position
void drawCar(){
for(int i=0; i<4; i++){
for(int j=0; j<4; j++){
gotoxy(j+carPos, i+22); cout<<car[i][j];
}
}
}
//erases the car at its current position
void eraseCar(){
for(int i=0; i<4; i++){
for(int j=0; j<4; j++){
gotoxy(j+carPos, i+22); cout<<" ";
}
}
}
//checks if the car has collided with an enemy
int collision(){
if( enemyY[0]+4 >= 23 ){
if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9 ){
return 1;
}
}
return 0;
}
//displays the game over screen and waits for user input to exit
void gameover(){
system("cls");
cout<<endl;
cout<<"\t\t--------------------------"<<endl;
cout<<"\t\t-------- Game Over -------"<<endl;
cout<<"\t\t--------------------------"<<endl<<endl;
cout<<"\t\tPress any key to go back to menu.";
getch();
}
//updates the player's score on the screen
void updateScore(){
gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}
//displays the game instructions on the screen
void instructions(){
system("cls");
cout<<"Instructions";
cout<<"\n----------------";
cout<<"\n Avoid Cars by moving left or right. ";
cout<<"\n\n Press 'a' to move left";
cout<<"\n Press 'd' to move right";
cout<<"\n Press 'escape' to exit";
cout<<"\n\nPress any key to go back to menu";
getch();
}
//display the game border,score,instructions
void play(){
carPos = -1 + WIN_WIDTH/2;
score = 0;
enemyFlag[0] = 1;
enemyFlag[1] = 0;
enemyY[0] = enemyY[1] = 1;
system("cls");
drawBorder();
updateScore();
genEnemy(0);
genEnemy(1);
gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
gotoxy(18, 5);cout<<"Press any key to start";
getch();
gotoxy(18, 5);cout<<" ";
while(1){ //handling user input
if(kbhit()){
char ch = getch();
if( ch=='a' || ch=='A' ){
if( carPos > 18 )
carPos -= 4;
}
if( ch=='d' || ch=='D' ){
if( carPos < 50 )
carPos += 4;
}
if(ch==27){
break;
}
}
drawCar();
drawEnemy(0);
drawEnemy(1);
if( collision() == 1 ){
gameover();
return;
}
Sleep(50);
eraseCar();
eraseEnemy(0);
eraseEnemy(1);
if( enemyY[0] == 10 )
if( enemyFlag[1] == 0 )
enemyFlag[1] = 1;
if( enemyFlag[0] == 1 )
enemyY[0] += 1;
if( enemyFlag[1] == 1 )
enemyY[1] += 1;
if( enemyY[0] > SCREEN_HEIGHT-4 ){
resetEnemy(0);
score++;
updateScore();
}
if( enemyY[1] > SCREEN_HEIGHT-4 ){
resetEnemy(1);
score++;
updateScore();
}
}
}
//TIC TAE TOE
//represent player's mark
char square[10] = {'o','1','2','3','4','5','6','7','8','9'};
//3X3 grid
void board()
{
system("cls"); //clearing console screen
cout << "\n\n\tTic Tac Toe\n\n";
cout << "Player 1 (X) - Player 2 (O)" << endl << endl;
cout << endl;
cout << " | | " << endl;
cout << " " << square[1] << " | " << square[2] << " | " << square[3] << endl;
cout << "||_" << endl;
cout << " | | " << endl;
cout << " " << square[4] << " | " << square[5] << " | " << square[6] << endl;
cout << "||_" << endl;
cout << " | | " << endl;
cout << " " << square[7] << " | " << square[8] << " | " << square[9] << endl;
cout << " | | " << endl << endl;
}
//checks who wins
int checkwin()
{
if (square[1] == square[2] && square[2] == square[3])
return 1;
else if (square[4] == square[5] && square[5] == square[6])
return 1;
else if (square[7] == square[8] && square[8] == square[9])
return 1;
else if (square[1] == square[4] && square[4] == square[7])
return 1;
else if (square[2] == square[5] && square[5] == square[8])
return 1;
else if (square[3] == square[6] && square[6] == square[9])
return 1;
else if (square[1] == square[5] && square[5] == square[9])
return 1;
else if (square[3] == square[5] && square[5] == square[7])
return 1;
else if (square[1] != '1' && square[2] != '2' && square[3] != '3'
&& square[4] != '4' && square[5] != '5' && square[6] != '6'
&& square[7] != '7' && square[8] != '8' && square[9] != '9')
return 0;
else
return -1;
}
//SNAKE GAME
// height and width of the boundary
const int width = 80;
const int height = 20;
// Snake head coordinates of snake (x-axis, y-axis)
int x, y;
// Food coordinates
int fruitCordX, fruitCordY;
// variable to store the score of he player
int playerScore;
// Array to store the coordinates of snake tail (x-axis, y-axis)
int snakeTailX[100], snakeTailY[100];
// variable to store the length of the sanke's tail
int snakeTailLen;
// for storing snake's moving snakesDirection
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
// snakesDirection variable
snakesDirection sDir;
// boolean variable for checking game is over or not
bool isGameOver;
// Function to initialize game variables
void GameInit()
{
isGameOver = false;
sDir = STOP;
x = width / 2;
y = height / 2;
fruitCordX = rand() % width;
fruitCordY = rand() % height;
playerScore = 0;
}
// Function for creating the game board & rendering
void GameRender(string playerName)
{
system("cls"); // Clear the console
// Creating top walls with '-
'
for (int i = 0; i < width + 2; i++)
cout << "-";
cout << endl;
for (int i = 0; i < height; i++) {
for (int j = 0; j <= width; j++) {
// Creating side walls with '|'
if (j == 0 || j == width)
cout << "|";
// Creating snake's head with 'O'
if (i == y && j == x)
cout << "O";
// Creating the snake's food with '#'
else if (i == fruitCordY && j == fruitCordX)
cout << "#";
// Creating snake's head with 'O'
else {
bool prTail = false;
for (int k = 0; k < snakeTailLen; k++) {
if (snakeTailX[k] == j
&& snakeTailY[k] == i) {
cout << "o";
prTail = true;
}
}
if (!prTail)
cout << " ";
}
}
cout << endl;
}
// Creating bottom walls with '-
'
for (int i = 0; i < width + 2; i++)
cout << "-";
cout << endl;
// Display player's score
cout << playerName << "'s Score: " << playerScore
<< endl;
}
// Function for updating score and length of snake
void UpdateGame()
{
int prevX = snakeTailX[0];
int prevY = snakeTailY[0];
int prev2X, prev2Y;
snakeTailX[0] = x;
snakeTailY[0] = y;
for (int i = 1; i < snakeTailLen; i++) {
prev2X = snakeTailX[i];
prev2Y = snakeTailY[i];
snakeTailX[i] = prevX;
snakeTailY[i] = prevY;
prevX = prev2X;
prevY = prev2Y;
}
switch (sDir) {
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
}
// Checks for snake's collision with the wall (|)
if (x >= width || x < 0 || y >= height || y < 0)
isGameOver = true;
// Checks for collision with the tail (o)
for (int i = 0; i < snakeTailLen; i++) {
if (snakeTailX[i] == x && snakeTailY[i] == y)
isGameOver = true;
}
// Checks for snake's collision with the food (#)
if (x == fruitCordX && y == fruitCordY) {
playerScore += 10;
fruitCordX = rand() % width;
fruitCordY = rand() % height;
snakeTailLen++;
}
}
// Function to set the game difficulty level
int SetDifficulty()
{
int dfc, choice;
cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
"\nNOTE: if not chosen or pressed any other "
"key, the difficulty will be automatically set "
"to medium\nChoose difficulty level: ";
cin >> choice;
switch (choice) {
case '1':
dfc = 50;
break;
case '2':
dfc = 100;
break;
case '3':
dfc = 150;
break;
default:
dfc = 100;
}
return dfc;
}
// Function to handle user UserInput
void UserInput()
{
// Checks if a key is pressed or not
if (_kbhit()) {
// Getting the pressed key
switch (_getch()) {
case 'a':
sDir = LEFT;
break;
case 'd':
sDir = RIGHT;
break;
case 'w':
sDir = UP;
break;
case 's':
sDir = DOWN;
break;
case 'm':
isGameOver = true;
break;
}
}
}
//PACMAN
char tmp_map[18][32]; //2d array
char map[18][32] = {
"+#############################+",
"| |",
"| |",
"|## ########### ## #########|",
"| | |",
"| | |### | | | |",
"| | | | |### | | | |",
"| | #####| | | ## | |",
"| | |### | | |",
"| |##### ### ## |",
"| ###### ####### ###|",
"| |",
"|# ### #### ### #######|",
"| |",
"| |",
"| |",
"| |",
"+#############################+"};
//displays current state of game map on console
void ShowMap()
{
for (int i = 0; i < 18; i++)
{
printf("%s\n", map[i]);
}
}
//moves the console cursor to a specified position
void gotoxy(short x, short y)
{
HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD position = {x, y};
SetConsoleCursorPosition(hStdout, position);
}
//class declaration for movable objects eg. h;hero moving
class entity
{
public:
entity(int x, int y)
{
this->x = x;
this->y = y;
}
void move_x(int p)
{
if (map[y][x + p] == ' ')
x += p;
}
void move_y(int p)
{
if (map[y + p][x] == ' ')
y += p;
}
void move(int p, int q)
{
x += p;
y += q;
}
int get_x() { return x; }
int get_y() { return y; }
void draw(char p)
{
map[x][y] = p;
gotoxy(x, y);
printf("%c", p);
}
private:
int x;
int y;
};
struct walk
{
short walk_count;
short x;
short y;
short back;
};
struct target
{
short x;
short y;
};
//use of vector
vector<target> walk_queue; //store coordinates
vector<walk> BFSArray; // Breadth first search algorithm
//to find shortest path for pac-man to move
//adds node to bfs array
void AddArray(int x, int y, int wc, int back)
{
if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.')
{
tmp_map[y][x] = '#';
walk tmp;
tmp.x = x;
tmp.y = y;
tmp.walk_count = wc;
tmp.back = back;
BFSArray.push_back(tmp);
}
}
//find shortest path from current position
void FindPath(int sx, int sy, int x, int y)
{
memcpy(tmp_map, map, sizeof(map));
BFSArray.clear();
walk tmp;
tmp.x = sx;
tmp.y = sy;
tmp.walk_count = 0;
tmp.back = -1;
BFSArray.push_back(tmp);
int i = 0;
while (i < BFSArray.size())
{
if (BFSArray[i].x == x && BFSArray[i].y == y)
{
walk_queue.clear();
target tmp2;
while (BFSArray[i].walk_count != 0)
{
tmp2.x = BFSArray[i].x;
tmp2.y = BFSArray[i].y;
walk_queue.push_back(tmp2);
i = BFSArray[i].back;
}
break;
}
AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);
i++;
}
BFSArray.clear();
}
//Main section for choices of Games
int main()
{
int choice;
while(true)
{
//Home page for Game Arcade
system("cls");
cout << "------------------- Game Menu -------------------" << endl;
cout << "1. Car Game" << endl;
cout << "2. Tic Tac Toe" << endl;
cout << "3. Pacman" << endl;
cout << "4. Snake" << endl;
cout << "5. Exit" << endl;
cout << "Enter your choice: ";
cin >> choice;
switch(choice)
{
//For Car GAme
case 1:
{setcursor(0,0);
srand( (unsigned)time(NULL));
do{
system("cls");
gotoxy(10,5); cout<<" -------------------------- ";
gotoxy(10,6); cout<<" | Car Game | ";
gotoxy(10,7); cout<<" --------------------------";
gotoxy(10,9); cout<<"1. Start Game";
gotoxy(10,10); cout<<"2. Instructions";
gotoxy(10,11); cout<<"3. Quit";
gotoxy(10,13); cout<<"Select option: ";
char op = getche();
if( op=='1') play();
else if( op=='2') instructions();
else if( op=='3') exit(0);
}
while(1);
break;
}
//For Tic Tae Toe GAme
case 2:
{
int player = 1,i,choice;
char mark;
do
{
board();
player=(player%2)?1:2;
cout << "Player " << player << ", enter a number: ";
cin >> choice;
mark=(player == 1) ? 'X' : 'O';
if (choice == 1 && square[1] == '1')
square[1] = mark;
else if (choice == 2 && square[2] == '2')
square[2] = mark;
else if (choice == 3 && square[3] == '3')
square[3] = mark;
else if (choice == 4 && square[4] == '4')
square[4] = mark;
else if (choice == 5 && square[5] == '5')
square[5] = mark;
else if (choice == 6 && square[6] == '6')
square[6] = mark;
else if (choice == 7 && square[7] == '7')
square[7] = mark;
else if (choice == 8 && square[8] == '8')
square[8] = mark;
else if (choice == 9 && square[9] == '9')
square[9] = mark;
else
{
cout<<"Invalid move ";
player--;
cin.ignore();
cin.get();
}
i=checkwin();
player++;
}
while(i==-1);
board();
if(i==1)
cout<<"==>\aPlayer "<<--player<<" win ";
else
cout<<"==>\aGame draw";
cin.ignore();
cin.get();
break;}
case 3:
//For Pac Man
{
bool running = true;
int x = 15; // hero x
int y = 16; // hero y
int old_x;
int old_y;
int ex = 1;
int ey = 1;
int pts = 0;
printf("Instruction:\n1. Arrow Keys to move your hero\n2. Eat the dots produced by the Eater to gain poins\n3. Don't
get caught by the Eater\n\n");
printf("H -> Hard\nN -> Normal\nE -> Easy\n\nInput : ");
char diffi;
int speedmod = 3;
cin >> diffi;
if (diffi == 'N')
{
}
{
}
speedmod = 2;
else if (diffi == 'H')
speedmod = 1;
system("cls");
ShowMap();
gotoxy(x, y);
cout << "H";
int frame = 0;
FindPath(ex, ey, x, y);
while (running)
{
gotoxy(x, y);
cout << " ";
old_x = x;
old_y = y;
if (GetAsyncKeyState(VK_UP))
{
{
y--;
pts++;
}
if (map[y - 1][x] == '.')
else if (map[y - 1][x] == ' ')
y--;
}
{
{
y++;
pts++;
}
y++;
}
{
{
x--;
pts++;
}
x--;
}
{
{
x++;
pts++;
}
x++;
}
if (GetAsyncKeyState(VK_DOWN))
if (map[y + 1][x] == '.')
else if (map[y + 1][x] == ' ')
if (GetAsyncKeyState(VK_LEFT))
if (map[y][x - 1] == '.')
else if (map[y][x - 1] == ' ')
if (GetAsyncKeyState(VK_RIGHT))
if (map[y][x + 1] == '.')
else if (map[y][x + 1] == ' ')
if (old_x != x || old_y != y)
{
}
FindPath(ex, ey, x, y);
gotoxy(x, y);
cout << "H";
map[ey][ex] = '.';
gotoxy(ex, ey);
cout << ".";
if (frame % speedmod == 0 && walk_queue.size() != 0)
{
ex = walk_queue.back().x;
ey = walk_queue.back().y;
walk_queue.pop_back();
}
gotoxy(ex, ey);
cout << "E";
if (ex == x && ey == y)
{
break;
}
gotoxy(32, 18);
gotoxy(32, 1);
cout << pts;
Sleep(100);
frame++;
}
system("cls");
printf("You Lose and your score is : %i", pts);
cin.get();
cin.get();
cin.get();
cin.get();
cin.get();
cin.get();
cin.get();
cin.get();
break;
}
//For Snake Game
case 4:
{
string playerName;
cout << "enter your name: ";
cin >> playerName;
int dfc = SetDifficulty();
GameInit();
while (!isGameOver)
{
GameRender(playerName);
UserInput();
UpdateGame();
// creating a delay for according to the chosen difficulty
Sleep(dfc);
}
break;
}
//For Invalid Input
case 5:
exit(0);
default:
cout << "Invalid choice. Please try again." << endl;
}
system("pause");
}
return 0;
}
