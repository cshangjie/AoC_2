#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int process_line(const string &line, int maxRed, int maxGreen, int maxBlue)
{
    size_t colonPos = line.find(':') - 4;
    string gameInfo = line.substr(colonPos + 4 + 2);
    string gameID = line.substr(4, colonPos);

    int currRed, currGreen, currBlue;
    currRed = currGreen = currBlue = 0;
    stringstream ss(gameInfo);
    string turn;
    while (getline(ss, turn, ';'))
    {
        stringstream turn_ss(turn);
        int value;
        string color;

        while (getline(turn_ss, color, ','))
        {
            istringstream iss(color);
            iss >> value;

            if (color.find("red") != string::npos)
            {
                currRed = max(currRed, value);
            }
            else if (color.find("green") != string::npos)
            {
                currGreen = max(currGreen, value);
            }
            else if (color.find("blue") != string::npos)
            {
                currBlue = max(currBlue, value);
            }
        }
    }
    cout << "Game: " << gameID << endl;
    cout << gameInfo << endl;
    cout << "Max Red: " << currRed << " Max Green: " << currGreen << " Max Blue: " << currBlue << endl;
    if (currRed <= maxRed && currGreen <= maxGreen && currBlue <= maxBlue)
    {
        return stoi(gameID);
    }
    else
    {
        return 0;
    }
}

int main()
{
    int maxRed = 12;
    int maxGreen = 13;
    int maxBlue = 14;
    string line;
    ifstream file("input.txt");
    int valid_game_sum = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            valid_game_sum += process_line(line, maxRed, maxGreen, maxBlue);
            cout << "GAME SUM: " << valid_game_sum << endl;
        }
        file.close();
    }
    cout << valid_game_sum << endl;
    return 0;
}