#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
int exitX;
int exitY;
int counter = 0;
vector<string> labyrinth;
vector<string> answerLabyrinth;
char wall = '*';

void printVector(const vector<string> &arr){
    if(arr.size() > 0){
        for(int  i = 0; i < arr.size(); i++)
            cout << arr[i] << endl;
        cout << endl;
    }
}

int itc_len(string str){
    int kol = 0;
    for(int i = 0; str[i] != '\0'; i++){
        kol++;
    }
    return kol;
}

int itc_toInt(string s){
    long long num = 0;
    for(long long i = 0; i < itc_len(s); i++){
        num += s[i] - 48;
        num *= 10;
    }
    num /= 10;
    return num;
}

bool readFromFile(ifstream &inputFromFile, int &posX, int &posY){
    string foo;
    vector<string> fileContent;
    for(getline(inputFromFile, foo); !inputFromFile.eof(); getline(inputFromFile, foo))
        fileContent.push_back(foo);
    fileContent.push_back(foo);
    for(int y = 0; y < fileContent.size() - 2; y++){
        for(int x = 0; x < fileContent[y].size(); x++){
            if(fileContent[y][x] != ' ' && fileContent[y][x] != '*'){
                inputFromFile.close();
                return false;
            }
        }
    }
    for(int i = 0; i < fileContent.size() - 2; i++){
        labyrinth.push_back(fileContent[i]);
        answerLabyrinth.push_back(fileContent[i]);
    }
    posX = itc_toInt(fileContent[fileContent.size() - 1]);
    posY = itc_toInt(fileContent[fileContent.size() - 2]);
    inputFromFile.close();
    return true;
}

bool findPath(int posX, int posY, int direction){
    printVector(labyrinth);
    counter++;

    if(labyrinth[posY][posX] != '*' && labyrinth[posY][posX] != '0'){
        labyrinth[posY][posX] = '0';
        cout << "X:" << posX << endl << "Y:" << posY << endl << "Direction: " << direction << endl;
        if(posX == 0 || posX == itc_len(labyrinth[0]) - 1 || posY == 0 || posY == labyrinth.size() - 1){
            cout << "exit is at:\nX:" << posX << endl << "Y:" << posY << endl;
            answerLabyrinth[posY][posX] = 'E';
            return true;
        }
        for(int i = 0; i < 4; i++){
            cout << "iteration: " << i << endl;
            if(i == 0 && direction != 2){
                if(findPath(posX - 1, posY, 0)){
                    answerLabyrinth[posY][posX] = '0';
                    return true;
                }
            }
            else if(i == 1 && direction != 3){
                if(findPath(posX, posY - 1, 1)){
                    answerLabyrinth[posY][posX] = '0';
                    return true;
                }
            }
            else if(i == 2 && direction != 0){
                if(findPath(posX + 1, posY, 2)){
                    answerLabyrinth[posY][posX] = '0';
                    return true;
                }
            }
            else if(i == 3 && direction != 1){
                if(findPath(posX, posY + 1, 3)){
                    answerLabyrinth[posY][posX] = '0';
                    return true;
                }
            }
        }
    }
    else
        cout << "There is a wall! " << posX << " " << posY << " " << counter << endl << endl;
    return false;
}

int main(int argc, char* args[])
{
    int posX, posY;
    ifstream inputFromFile("Levels\\L1.txt");
    if(!readFromFile(inputFromFile, posX, posY)){
        cout << "ERROR: Labyrinth has forbidden symbols!";
        return 0;
    }
    if(posY > labyrinth.size() - 1 || posX > labyrinth[0].size() - 1){
        cout << "ERROR: There are no such coordinates in the labyrinth!";
        return 0;
    }
    if(labyrinth[posY][posX] != '*'){
        labyrinth[posY][posX] = 'X';
        findPath(posX, posY, -1);
        answerLabyrinth[posY][posX] = 'X';
        printVector(answerLabyrinth);
    }
    else
        cout << "ERROR: Turtle is in the wall!";
    return 0;
}
