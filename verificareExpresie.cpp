#include <fstream>
#include <cstring>
#define LGMAX 202
using namespace std;
ifstream fin("vexp.in");
ofstream fout("vexp.out");
char e[LGMAX], op[] = "0123456789abcdefghijklmnopqrstuvwxyz";
int lg, i, ND;
int ValidareExpresie();
int ValidareTermen();
int ValidareFactor();
int main()
{
	fin.getline(e, LGMAX);
	fin.close();
	// transform majusculele in minuscule si determin lungimea
	for (lg = 0; e[lg]; lg++)
	{
		if (e[lg] >= 'A' && e[lg] <= 'Z')
		{
			e[lg] = e[lg]-'A'+'a';
		}
	}
	if (ValidareExpresie())
	{
		fout << "Expresia este sintactic corecta!\n";
	}
	fout.close();
	return 0;
}
int ValidareFactor()
{
	int r = 1;
	if (e[i] == '(') // factorul e o expresie intre paranteze
	{
		ND++; // numar o paranteza deschisa care nu e inchisa
		i++; // trec peste (
		r = ValidareExpresie(); // validez expresia din paranteza
		if (!r)
		{
			return r;
		}
		if (e[i] != ')') // paranteza nu este inchisa corect
		{
			fout << "Eroare! Pe pozitia " << i << " este necesara )";
			r = 0;
		}
		else
		{
			i++; // trc peste )
			ND--; // scad numarul de paranteze ramase deschise
		}
	}
	else 
	{
		// verific daca factorul este o litera sau o cifra
		if (!strchr(op, e[i]))
		{
			fout << "Eroare! Pe pozitia " << i << " trebuie operand";
			r = 0;
		}
		else
		{
			i++; // trec peste factor
		}
	}
	return r;
}
int ValidareTermen()
{
	int r = ValidareFactor(); // validez primul factor din termen
	while (r && i < lg && e[i] == '*') // mai urmeaza factori
	{
		i++; // trec peste *
		r = ValidareFactor();
	}
	return r;
}
int ValidareExpresie()
{
	int r = ValidareTermen(); // validez primul termen
	while (r && i < lg && e[i] == '+') // mai urmeaza termeni
	{
		i++; // trec peste +
		r = ValidareTermen();
	}
	if (r && i < lg)
	{
		if (e[i] != ')' || e[i] == ')' && !ND)
		{
			fout << "Eroare!";
			r = 0;
		}
	}
	return r;
}
