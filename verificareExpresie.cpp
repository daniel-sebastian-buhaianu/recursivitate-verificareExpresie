#include <iostream>
#include <cstring>
#define LGMAX 202
using namespace std;
// variabile globale
char e[LGMAX];
int lg, i, ND;
// functii ajutatoare
bool litera(char);
bool cifra(char);
bool valideazaFactor();
bool valideazaTermen();
bool valideazaExpresie();
void transformaMajusculeInMinuscule();
void citesteExpresie();
// functia principala
int main()
{
	citesteExpresie();
	transformaMajusculeInMinuscule();
	if (valideazaExpresie())
	{
		cout << "DA";
	}
	return 0;
}
bool litera (char c)
{
	return c >= 'a' && c <= 'z';
}
bool cifra(char c)
{
	return c >= '0' && c <= '9';
}
bool valideazaFactor()
{
	bool r = 1;
	if (e[i] == '(') // factorul e o expresie intre paranteze
	{
		ND++; // numar o paranteza deschisa care nu e inchisa
		i++; // trec peste (
		r = valideazaExpresie(); // validez expresia din paranteza
		if (!r) return r; // expresie incorecta
		if (e[i] != ')') // paranteza este inchisa corect?
		{
			cout << "Eroare! Pe pozitia " << i << " este necesara )";
			r = 0;
		}
		else
		{
			i++; // trec peste )
			ND--; // scad numarul de paranteze ramase deschise
		}
	}
	else // verific daca factorul este o litera sau o cifra
	{
		if (!cifra(e[i]) && !litera(e[i]))
		{
			cout << "Eroare! Pe pozitia " << i << " trebuie operand";
			r = 0;
		}
		else
		{
			i++; // trec peste factor
		}
	}
	return r;
}
bool valideazaTermen()
{
	bool r = valideazaFactor(); // validez primul factor din termen
	while (r && i < lg && e[i] == '*') // mai urmeaza factori
	{
		i++; // trec peste *
		r = valideazaFactor();
	}
	return r;
}
bool valideazaExpresie()
{
	bool r = valideazaTermen(); // validez primul termen
	while (r && i < lg && e[i] == '+') // mai urmeaza termeni
	{
		i++; // trec peste +
		r = valideazaTermen();
	}
	if (r && i < lg)
	{
		if (e[i] != ')' || e[i] == ')' && !ND)
		{
			cout << "Eroare!";
			r = 0;
		}
	}
	return r;
}
void transformaMajusculeInMinuscule()
{
	for (lg = 0; e[lg]; lg++)
	{
		if (e[lg] >= 'A' && e[lg] <= 'Z')
		{
			e[lg] = e[lg]-'A'+'a';
		}
	}
}
void citesteExpresie()
{
	cout << "Introduceti expresia: ";
	cin.getline(e, LGMAX);
}
