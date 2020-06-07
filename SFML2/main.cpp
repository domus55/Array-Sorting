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
void sortowaniePrzezScalanie();
int wczytaj();
void render(int tab[]);

sf::RenderWindow window;

int a = 100000;
int b = 1000;

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
	cout << "Ile liczb posortowac: "; cin >> a;
	//odp = 5;

	while (window.isOpen())
	{
		if (odp == 1) sortowanieBomblekowe();
		if (odp == 2) sortowaniePrzezWstawianie();
		if (odp == 3) sortowaniePrzezWybieranie();
		if (odp == 4)
		{
			int *tab;
			tab = new int[a];

			//wczytywanie losowych liczb do tablicy
			for (int i = 0; i < a; i++)
			{
				tab[i] = rand() % b;
			}

			quicksort(tab, 0, a - 1);
		}
		if (odp == 5) sortowaniePrzezScalanie();
	}

	return 0;
}

void sortowanieBomblekowe()
{
	int * tab = new int[a];

	for (int i = 0; i < a; i++)
	{
		tab[i] = rand() % b;
	}

	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < a - i - 1; j++)
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
	int * tab = new int[a];
	int * tab2 = new int[a];

	for (int i = 0; i < a; i++)
	{
		tab[i] = rand() % b;
		tab2[i] = rand() % b;
	}

	for (int i = 0; i < a; i++)
	{
		maksymalna = 0;
		maksymalnaId = 0;

		for (int j = 0; j < a; j++)
		{
			if (tab[j] > maksymalna)
			{
				maksymalna = tab[j];
				maksymalnaId = j;
			}
		}

		tab2[a - i - 1] = maksymalna;
		tab[maksymalnaId] = -1;

		render(tab2);
	}
}

void sortowaniePrzezWybieranie()
{
	int maksymalna = 0;
	int maksymalnaId = 0;
	int * tab = new int[a];

	for (int i = 0; i < a; i++)
	{
		tab[i] = rand() % b;
	}

	for (int i = 0; i < a; i++)
	{
		maksymalna = 0;
		maksymalnaId = 0;

		for (int j = 0; j < a - i; j++)
		{
			if (tab[j] > maksymalna)
			{
				maksymalna = tab[j];
				maksymalnaId = j;
			}
		}
		int c = tab[a - i - 1];
		tab[a - i - 1] = maksymalna;
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

void sortowaniePrzezScalanie()
{
	int * tab = new int[a];
	int * tab2 = new int[a];
	int leftTab2 = 0;
	int left = 0;
	int right = 1;

	for (int i = 0; i < a; i++)
	{
		tab[i] = rand() % b;
	}

	int i = 1;

	for (;;)
	{
		left = 0;
		right = pow(2, i) - 1;

		for (;;)
		{
			int left2 = left;
			int right2 = right;

			for (;;)
			{
				//cout << leftTab2 << endl;
				if (tab[left2] > tab[right2])
				{
					tab2[leftTab2] = tab[right2];
					right2++;
					leftTab2++;
				}
				else
				{
					if (tab[left2] == tab[right2])
					{
						tab2[leftTab2] = tab[left2];
						tab2[leftTab2 + 1] = tab[left2];
						left2++;
						right2++;
						leftTab2 += 2;
					}
					else
					{
						tab2[leftTab2] = tab[left2];
						left2++;
						leftTab2++;
					}
				}

				if (left2 >= left + pow(2, i))
				{
					for (;;)
					{
						if (right2 >= right + pow(2, i)) goto next;
						tab2[leftTab2] = tab[right2];
						right2++;
						leftTab2++;
					}
				}
				if (right2 >= right + pow(2, i))
				{
					for (;;)
					{
						if (left2 >= left + pow(2, i)) goto next;
						tab2[leftTab2] = tab[left2];
						left2++;
						leftTab2++;
					}
				}
			}
			
			next:;

			leftTab2 = 0;

			left += pow(2, i);
			right += pow(2, i);


			if (right >= a) break;
		}
		
		i++;

		//tab = tab2;

		//cout << "a";

		render(tab2);

		if (pow(2, i) - 1 > a) break;
	}
	cout << "a";
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

	if (clock() - prevTime > 33)
	{
		window.clear();

		int c;

		if (a <= 1000) c = 1;
		else c = a / 10000;

		for (int i = 0; i < a; i += c)
		{
			sf::CircleShape point(1);

			point.setFillColor(sf::Color(255, tab[i] / (float)b * 255, 0));
			point.setPosition(((800.0 / a * i) - 800) * -1, 800.0 / b * tab[i]);


			window.draw(point);
		}

		prevTime = clock();
		window.display();
	}
}

int wczytaj()
{
	std::fstream plik;
	plik.open("options.txt", std::ios::in);

	int x;

	plik >> x;

	plik.close();

	return x;
}