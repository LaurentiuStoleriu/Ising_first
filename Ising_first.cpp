#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>

using namespace std;

void generare_matrice(/*int M[101][101]*/vector<vector<int>> &M, int n) //genereaza matricea bordata cu 0 si cu elemente +/-1 in interior. n= nr de linii pr-zise, fara bordare
{
	int i, j, val;

	//srand(time(NULL));
	random_device rd;
	mt19937 genereaza(rd());				// pentru rezultate repetabile se inlocuieste rd() cu un numar oarecare
	uniform_int_distribution<> dist(0, 1);

	for (i = 0; i <= n + 1; i++) {
		if (i == 0 || i == n + 1) {
			for (j = 0; j <= n + 1; j++) {
				M[i][j] = 0;
				M[j][0] = 0;
				M[j][n + 1] = 0;
			}
		}
		else
			for (j = 0; j <= n + 1; j++) {
				//val = rand() % 2;
				val = dist(genereaza);
				if (val == 0)
					val = -1;
				M[i][j] = val;
			}
	}
}

void afisare_matrice(/*int M[101][101]*/vector<vector<int>> &M, int n)
{
	int i, j;
	for (i = 0; i <= n + 1; i++) {
		for (j = 0; j <= n + 1; j++)
			printf("%2d ", M[i][j]);
		cout << "\n";
	}
	cout << endl;
}


double dif_energie(int x1, int y1, int x2, int y2, /*int M[101][101]*/vector<vector<int>> &M, double dE) //am incercat sa folosesc o formula pentru diferenta de energie a unui sistem de 2 particule
{
	int S1, S2;

	S1 = M[x1 - 1][y1] + M[x1 + 1][y1] + M[x1][y1 - 1] + M[x1][y1 + 1];
	S2 = M[x2 - 1][y2] + M[x2 + 1][y2] + M[x2][y2 - 1] + M[x2][y2 + 1];
	dE = 2 * dE * (S1 * M[x1][y1] + S2 * M[x2][y2]);
	return dE;
}


void schimba(int x1, int y1, int x2, int y2, /*int M[101][101]*/vector<vector<int>> &M, double dE, int& contor) // aceasta functie schimba 2 dipoli
{
	if (M[x1][y1] != -M[x2][y2]) //daca dipolii au acceasi valoare iese din program
		return;
	else if (((x2 - x1) * (y2 - y1) != 0 || abs(x2 - x1 + y2 - y1) != 1)) // daca dipolii nu sunt adiacenti iese din program
		return;
	else
		if (dif_energie(x1, y1, x2, y2, M, dE) < 0)
		{
			int aux;
			aux = M[x1][y1];
			M[x1][y1] = M[x2][y2];
			M[x2][y2] = aux;
			contor++;
		}
}


int suma_matrice(/*int M[101][101]*/vector<vector<int>> &M, int n) //aceasta functie o folosim pentru a verifica daca dipolul total ramane constant
{
	int i, j, suma = 0;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			suma = suma + M[i][j];
	return suma;
}


int main()
{
	int /*M[101][101],*/ n, i, j, contor = 0;
	double dE, J;

	//cout << "Introdu marimea matricii: ";
	//cin >> n;
	//cout << "Introdu valoarea parametrului J: ";
	//cin >> J;
	n = 20;
	J = 1;
	vector<vector<int>> M(n+2, vector<int>(n+2, 0));

	generare_matrice(M, n);
	afisare_matrice(M, n);
	cout << suma_matrice(M, n);
	cout << endl;
	dE = J;
	for (i = 1; i <= n - 1; i++)
		for (j = 1; j <= n; j++)
		{
			schimba(i, j, i + 1, j, M, dE, contor); //schimba mai intai pe orizontala
			schimba(i, j, i, j + 1, M, dE, contor); // apoi pe verticala
		}
	afisare_matrice(M, n);
	cout << suma_matrice(M, n);
	cout << endl;
	cout << "Nr de schimbari produse: " << contor; // nr de schimbari produse
	return 0;
}