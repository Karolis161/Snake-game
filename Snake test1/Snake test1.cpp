#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool ZaidimasBaigtas;
const int Plotis = 20, Aukstis = 20;
int X, Y, VaisiusX, VaisiusY, Taskai, GalasX[100], GalasY[100], GalasN;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

void Setup()
{
	ZaidimasBaigtas = false;
	dir = STOP;
	X = Plotis / 2;
	Y = Aukstis / 2;
	VaisiusX = rand() % Plotis;
	VaisiusY = rand() % Aukstis;
	Taskai = 0;
}

void Spausdinimas()
{
	system("cls");
	for (int i = 0; i < Plotis + 2; i++)
		cout << "_";
	cout << endl;

	for (int i = 0; i < Aukstis; i++)
	{
		for (int j = 0; j < Plotis; j++)
		{
			if (j == 0)
				cout << "|";
			if (i == Y && j == X)
				cout << "B";
			else if (i == VaisiusY && j == VaisiusX)
				cout << "O";
			else
			{
				bool Spausdinti = false;
				for (int k = 0; k < GalasN; k++)
				{
					if (GalasX[k] == j && GalasY[k] == i)
					{
						cout << "o";
						Spausdinti = true;
					}
				}
				if (!Spausdinti)
					cout << " ";
			}
			if (j == Plotis - 1)
				cout << "|";
		}
		cout << endl;
	}

	for (int i = 0; i < Plotis + 2; i++)
	cout << "-";
	cout << endl;
	cout << "Taskai:" << Taskai << endl;
}

void Klavisai()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		}
	}
}

void Zaidimas()
{
	int prevX = GalasX[0];
	int prevY = GalasY[0];
	int prev2X, prev2Y;
	GalasX[0] = X;
	GalasY[0] = Y;
	for (int i = 1; i < GalasN; i++)
	{
		prev2X = GalasX[i];
		prev2Y = GalasY[i];
		GalasX[i] = prevX;
		GalasY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		X--;
		break;
	case RIGHT:
		X++;
		break;
	case UP:
		Y--;
		break;
	case DOWN:
		Y++;
		break;
	default:
		break;
	}
    if (X > Plotis || X < 0 || Y > Aukstis || Y < 0)
	ZaidimasBaigtas = true;
	if (X >= Plotis) X = 0; else if (X < 0) X = Plotis - 1;
	if (Y >= Aukstis) Y = 0; else if (Y < 0) Y = Aukstis - 1;

	for (int i = 0; i < GalasN; i++)
		if (GalasX[i] == X && GalasY[i] == Y)
			ZaidimasBaigtas = true;

	if (X == VaisiusX && Y == VaisiusY)
	{
		Taskai += 10;
		VaisiusX = rand() % Plotis;
		VaisiusY = rand() % Aukstis;
		GalasN++;
	}
}

int main()
{
	Setup();
	while (!ZaidimasBaigtas)
	{
		Spausdinimas();
		Klavisai();
		Zaidimas();
		Sleep(70);
	}
	return 0;
}