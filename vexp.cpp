#include <fstream>
#include <cstring>
#define LGMAX 202
using namespace std;
// fisiere intrare/iesire
ifstream fin("vexp.in");
ofstream fout("vexp.out");
// variabile globale
char e[LGMAX];
int lg, poz, ND;
// functii ajutatoare
bool cifra(char);
bool litera(char);
bool valideazaExpresie(void);
bool valideazaTermen(void);
bool valideazaFactor(void);
void citesteExpresie(void);
// functia principala
int main(void)
{
	citesteExpresie();
	if (valideazaExpresie())
	{
		fout << "Expresia este sintactic corecta!\n";
	}
	fout.close();
	return 0;
}
void citesteExpresie(void)
{
	fin.getline(e, LGMAX);
	fin.close();
	// transform majusculele in minuscule
	// elimin toate spatiile si determin lungimea sirului
	char aux[LGMAX], *c;
	for (lg = 0, c = e; *c; c++)
	{
		if (*c >= 'A' && *c <= 'Z')
		{
			*c = *c-'A'+'a';
		}
		if (*c != ' ')
		{
			aux[lg++] = *c;
		}
	}
	aux[lg] = 0;
	strcpy(e, aux);
}
bool valideazaFactor(void)
{
	bool ok;
	if (e[poz] == '(') // factorul e o expresie intre paranteze
	{
		ND++; // numar o paranteza deschisa care nu e inchisa
		poz++; // trec peste (
		if (!valideazaExpresie()) return 0;
		if (e[poz] != ')') // paranteza nu este inchisa corect
		{
			fout << "Eroare! Pe pozitia " << poz << " este necesara )";
			return 0;
		}
		poz++; // trc peste )
		ND--; // scad numarul de paranteze ramase deschise
	}
	else
	{
		if (!cifra(e[poz]) && !litera(e[poz]))
		{
			fout << "Eroare! Pe pozitia " << poz << " trebuie operand";
			return 0;
		}
		ok = 1;
		if (cifra(e[poz]))
		{
			while (cifra(e[poz])) poz++;
			if (litera(e[poz])) ok = 0;
		}
		else
		{
			while (litera(e[poz])) poz++;
			if (cifra(e[poz])) ok = 0;
		}
		if (!ok)
		{
			fout << "Eroare! Pe pozitia " << poz << " trebuie operator";
			return 0;

		}
	}
	return 1;
}
bool valideazaTermen(void)
{
	bool r = valideazaFactor(); // validez primul factor din termen
	while (r && poz < lg && e[poz] == '*') // mai urmeaza factori
	{
		poz++; // trec peste *
		r = valideazaFactor();
	}
	return r;
}
bool valideazaExpresie(void)
{
	bool r = valideazaTermen(); // validez primul termen
	while (r && poz < lg && e[poz] == '+') // mai urmeaza termeni
	{
		poz++; // trec peste +
		r = valideazaTermen();
	}
	if (r && poz < lg)
	{
		if (e[poz] != ')' || e[poz] == ')' && !ND)
		{
			fout << "Eroare!";
			r = 0;
		}
	}
	return r;
}
bool litera(char c)
{
	return c >= 'a' && c <= 'z';
}
bool cifra(char c)
{
	return c >= '0' && c <= '9';
}
