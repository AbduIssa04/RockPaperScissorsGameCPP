#include<iostream>
#include<cstdlib>
using namespace std;

int ReadRoundNum()
{
	int N = 0;
	do
	{
		cout << "How many rounds do you want to play(1 to 10): " << endl;
		cin >> N;
	} while (1 > N || N > 10);
	return N;
}
enum enChoices { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
	short RoundNumber = 0;
	enChoices PlayerChoice;
	enChoices ComputerChoice;
	enWinner RoundWinner;
	string Winner;
};
struct stGameResultsInfo
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes;
	enWinner Win;
	string FinalWinner;
};
int RandomNumberGenerator(int From, int To)
{
	int result = rand() % (To - From + 1) + From;
	return result;
}
enChoices ReadUserChoice()
{
	int N = 0;
	do
	{
		cout << "Your Choice: [1]:Rock, [2]:Paper, [3]:Scissors: ";
		cin >> N;
	} while (1 > N || N > 3);
	return ((enChoices)N);
}
enChoices GetComputerChoice()
{
	int Choice = RandomNumberGenerator(1, 3);
	return (enChoices)Choice;
}
enWinner WhoWonGame(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enChoices::Rock:
	{
		if (RoundInfo.ComputerChoice == enChoices::Paper)
		{
			return enWinner::Computer;
		}
		break;
	}

	
	case enChoices::Paper:
	{

		if (RoundInfo.ComputerChoice == enChoices::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	}
		
	
	case enChoices::Scissors:
	{
		if (RoundInfo.ComputerChoice == enChoices::Rock)
		{
			return enWinner::Computer;
		}
		break;
	}
	
	}

	return enWinner::Player;
}
string WinnerName(enWinner Winner)
{
	string PossibleWinners[3] = { "Player", "Computer", "Draw" };
	return PossibleWinners[Winner - 1];
}
string ChoiceToString(enChoices choice)
{
	string PossibleChoices[3] = { "Rock", "Paper", "Scissors" };
	return PossibleChoices[choice - 1];
}
void PrintRoundInfoResults(stRoundInfo RoundInfo)
{
	cout << "____________Round[" << RoundInfo.RoundNumber << "]____________\n";
	cout << "Player Choice: " << ChoiceToString(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceToString(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner: " << RoundInfo.Winner << endl;
	cout << "________________________________\n\n";
}
enWinner FinalWinner(short PlayerWins, short ComputerWins)
{
	if (PlayerWins > ComputerWins)
		return enWinner::Player;
	else if (ComputerWins > PlayerWins)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResultsInfo GameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short Draws, string Winner)
{
	stGameResultsInfo FinalGameResult;
	FinalGameResult.GameRounds = GameRounds;
	FinalGameResult.PlayerWinTimes = PlayerWinTimes;
	FinalGameResult.ComputerWinTimes = ComputerWinTimes;
	FinalGameResult.DrawTimes = Draws;
	FinalGameResult.FinalWinner = Winner;

	return FinalGameResult;
}
void PrintGameResults(stGameResultsInfo GameResult)
{
	cout << "\t\t\____________________[Game Results]____________________\n";
	cout << "\t\tGame Rounds\t  : " << GameResult.GameRounds << endl;
	cout << "\t\tPlayer Won Times  : " << GameResult.PlayerWinTimes << endl;
	cout << "\t\tComputer Won Times: " << GameResult.ComputerWinTimes << endl;
	cout << "\t\tDraw Times\t  : " << GameResult.DrawTimes << endl;
	cout << "\t\tFinal Winner\t  : " << GameResult.FinalWinner << endl;
	cout << "______________________________________________________\n";
}
stGameResultsInfo PlayGame(int NumOfRounds)
{
	short PlayerWinTimes = 0, ComputerWinTimes = 0, Draws = 0;
	stRoundInfo RoundInfo;
	for (int CurrentRound = 1; NumOfRounds >= CurrentRound; CurrentRound++)
	{
		cout << "\nRound [" << CurrentRound << "] begins:\n";
		RoundInfo.RoundNumber = CurrentRound;
		RoundInfo.PlayerChoice = ReadUserChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWonGame(RoundInfo);
		RoundInfo.Winner = WinnerName(RoundInfo.RoundWinner);

		if (WhoWonGame(RoundInfo) == enWinner::Player)
		{
			PlayerWinTimes++;
			system("color 2F");
		}
		else if (WhoWonGame(RoundInfo) == enWinner::Computer)
		{
			ComputerWinTimes++;
			system("color 4F");
			cout << "\a";
		}
		else
		{
			Draws++;
			system("color 6F");
		}

		PrintRoundInfoResults(RoundInfo);
	}
	string GameFinalWinner = WinnerName(FinalWinner(PlayerWinTimes, ComputerWinTimes));
	return GameResults(NumOfRounds, PlayerWinTimes, ComputerWinTimes, Draws, GameFinalWinner);

}
void ResetScreen()
{
	system("cls && color 0F");
}
void GameOverScreen()
{
	cout << "\t\t______________________________________________________\n";
	cout << "\t\t\t\t +++ G A M E  O V E R +++\n";
	cout << "\t\t______________________________________________________\n";
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResultsInfo GameResult = PlayGame(ReadRoundNum());
		GameOverScreen();
		PrintGameResults(GameResult);
		cout << "Do you want to play again? Y/N\n";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}




int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	return 0;
}