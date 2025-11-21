#include <iostream>
#include <cmath> 
#include <string>

using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

void SetWinnerScreenColor(enWinner Winner)
{

    switch (Winner)
    {

    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}


int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

enGameChoice ReadPlayerChoice()
{
    short Choice;

    do
    {
        cout << "Your choice [1]:Rock , [2]:Paper , [3]:Scissors ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice >3);

    return (enGameChoice)Choice;


}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Rock:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Rock)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
        return enWinner::Player;
    else if (PlayerWinTimes < ComputerWinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;

}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "YOU", "Computer", "Draw" };

    return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Rock", "Paper", "Scissors" };

    return arrGameChoices[Choice - 1];
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (int i = 0; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{

    cout << "----------Round[" << RoundInfo.RoundNumber << "]----------\n\n";
    cout << "Your Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: [" << RoundInfo.WinnerName << "]\n";
    cout << "--------------------------------------------------------\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short whoManyRounds)
{
    stRoundInfo RoundInfo;

    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= whoManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins: \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(whoManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "--------------------------------------------------------------\n\n";
    cout << Tabs(2) << "                      +++ GAME OVER +++\n                         ";
    cout << Tabs(2) << "--------------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "-------------------------[Game Results]-----------------------------\n\n";
    cout << Tabs(2) << "Game rounds: " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player won times: " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times: " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times: " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner: " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "--------------------------------------------------------------------\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);

}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How many rounds from 1 to 10? ";
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds>10);

    return GameRounds;
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again (Y/N) ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}




int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
