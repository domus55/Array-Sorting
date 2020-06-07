#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

void BubbleSort();
void InsertSort();
void SelectionSort();
void QuickSort(int *tablica, int lewy, int prawy);
void Render(int tab[]);

sf::RenderWindow window;

int numberAmount = 100000;
const int highestNumber = 1000;
const int frameRate = 30;

int main()
{
	window.create(sf::VideoMode(800, 800, 32), "Sorting", sf::Style::Close);

	cout << "Which sorting method do you choose: \n";
	cout << "1. bubble sort \n";
	cout << "2. insert sort \n";
	cout << "3. selection sort \n";
	cout << "4. quick sort \n";

	int odp;

	cin >> odp;
	cout << "How many numbers to sort: "; cin >> numberAmount;

	while (window.isOpen())
	{
		if (odp == 1) BubbleSort();
		if (odp == 2) InsertSort();
		if (odp == 3) SelectionSort();
		if (odp == 4)
		{
			int *tab;
			tab = new int[numberAmount];

			//loading random numbers to the array
			for (int i = 0; i < numberAmount; i++)
			{
				tab[i] = rand() % highestNumber;
			}

			QuickSort(tab, 0, numberAmount - 1);
		}
	}

	return 0;
}

void BubbleSort()
{
	int * tab = new int[numberAmount];

	for (int i = 0; i < numberAmount; i++)
	{
		tab[i] = rand() % highestNumber;
	}

	for (int i = 0; i < numberAmount; i++)
	{
		for (int j = 0; j < numberAmount - i - 1; j++)
		{
			if (tab[j] > tab[j + 1])
			{
				int c = tab[j];
				int d = tab[j + 1];

				tab[j] = d;
				tab[j + 1] = c;
			}
		}

		Render(tab);
	}
}

void InsertSort()
{
	int maksymalna = 0;
	int maksymalnaId = 0;
	int * tab = new int[numberAmount];
	int * tab2 = new int[numberAmount];

	for (int i = 0; i < numberAmount; i++)
	{
		tab[i] = rand() % highestNumber;
		tab2[i] = rand() % highestNumber;
	}

	for (int i = 0; i < numberAmount; i++)
	{
		maksymalna = 0;
		maksymalnaId = 0;

		for (int j = 0; j < numberAmount; j++)
		{
			if (tab[j] > maksymalna)
			{
				maksymalna = tab[j];
				maksymalnaId = j;
			}
		}

		tab2[numberAmount - i - 1] = maksymalna;
		tab[maksymalnaId] = -1;

		Render(tab2);
	}
}

void SelectionSort()
{
	int maksymalna = 0;
	int maksymalnaId = 0;
	int * tab = new int[numberAmount];

	for (int i = 0; i < numberAmount; i++)
	{
		tab[i] = rand() % highestNumber;
	}

	for (int i = 0; i < numberAmount; i++)
	{
		maksymalna = 0;
		maksymalnaId = 0;

		for (int j = 0; j < numberAmount - i; j++)
		{
			if (tab[j] > maksymalna)
			{
				maksymalna = tab[j];
				maksymalnaId = j;
			}
		}
		int c = tab[numberAmount - i - 1];
		tab[numberAmount - i - 1] = maksymalna;
		tab[maksymalnaId] = c;

		Render(tab);
	}
}

void QuickSort(int *tablica, int lewy, int prawy)
{
	int v = tablica[(lewy + prawy) / 2];
	int i, j, x;
	i = lewy;
	j = prawy;
	do
	{
		while (tablica[i] < v) i++;
		while (tablica[j] > v) j--;
		if (i <= j)
		{
			x = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = x;
			i++;
			j--;

			Render(tablica);
		}
	} while (i <= j);
	if (j > lewy) QuickSort(tablica, lewy, j);
	if (i < prawy) QuickSort(tablica, i, prawy);

	
}

void Render(int tab[])
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	

	static int prevTime = 0;

	if (clock() - prevTime > 1000 / frameRate)
	{
		window.clear();

		int c;

		if (numberAmount <= 1000) c = 1;
		else c = numberAmount / 10000;

		for (int i = 0; i < numberAmount; i += c)
		{
			sf::CircleShape point(1);

			point.setFillColor(sf::Color(255, tab[i] / (float)highestNumber * 255, 0));
			point.setPosition(((800.0 / numberAmount * i) - 800) * -1, 800.0 / highestNumber * tab[i]);


			window.draw(point);
		}

		prevTime = clock();
		window.display();
	}
}