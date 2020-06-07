#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

using namespace std;

void sortowanieBomblekowe();
void sortowaniePrzezWstawianie();
void sortowaniePrzezWybieranie();
void quicksort(int *tablica, int lewy, int prawy);
void render(int tab[]);

sf::RenderWindow window;

int numberAmount = 100000;
const int highestNumber = 1000;
const int frameRate = 30;

int main()
{
	window.create(sf::VideoMode(800, 800, 32), "Sortowanie", sf::Style::Close);

	cout << "ktore sortowanie wybierasz: \n";
	cout << "1. bombelkowe \n";
	cout << "2. przez wstawianie \n";
	cout << "3. przez wybieranie \n";
	cout << "4. quick sort \n";

	int odp;

	cin >> odp;
	cout << "Ile liczb posortowac: "; cin >> numberAmount;

	while (window.isOpen())
	{
		if (odp == 1) sortowanieBomblekowe();
		if (odp == 2) sortowaniePrzezWstawianie();
		if (odp == 3) sortowaniePrzezWybieranie();
		if (odp == 4)
		{
			int *tab;
			tab = new int[numberAmount];

			//wczytywanie losowych liczb do tablicy
			for (int i = 0; i < numberAmount; i++)
			{
				tab[i] = rand() % highestNumber;
			}

			quicksort(tab, 0, numberAmount - 1);
		}
	}

	return 0;
}

void sortowanieBomblekowe()
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

		render(tab);
	}
}

void sortowaniePrzezWstawianie()
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

		render(tab2);
	}
}

void sortowaniePrzezWybieranie()
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

		render(tab);
	}
}

void quicksort(int *tablica, int lewy, int prawy)
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

			render(tablica);
		}
	} while (i <= j);
	if (j > lewy) quicksort(tablica, lewy, j);
	if (i < prawy) quicksort(tablica, i, prawy);

	
}

void render(int tab[])
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