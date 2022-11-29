#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<map>
using namespace std;

// Polje (redosljed) aminokiselina
const char kAminoKiseline[] = {'G', 'P', 'A', 'V', 'L', 
							   'I', 'M', 'C', 'F', 'Y', 
							   'W', 'H', 'K', 'R', 'Q', 
							   'N', 'E', 'S', 'D', 'T', 
							   'B', 'U', 'X', 'Z', '-'};

// Broj Aminokiselina
const int brojAKiselina = 25;


// Korisnik upisuje ime datoteke. 
// Putanju treba navesti samo ako se datoteka ne nalazi 
// u istom direktoriju kao i program.
string UpisiImeDatoteke()
{
	string ime;
	
	cout << "Upisite ime datoteke: ";
	cin >> ime;
	
	return ime;
}

// Vraca string s velikim slovima
string UVelikaSlova(string ulazni)
{
	string izlazni;
	for(int i = 0; i < int(ulazni.size()); i++)
		izlazni.push_back(toupper(ulazni[i]));

	return izlazni;
}

// Cita datoteku red po red.
// Svaki procitani red koji ne pocinje znakom '>' 
// dodaje na kraj stringa. 
// Mala slova postaju velika.
string ProcitajDatoteku(const char* imeDatoteke)
{
	string redak, relPodaci;
	ifstream datoteka;
	
	datoteka.open(imeDatoteke);
	if(!datoteka.is_open()) {
		cout << "Greska pri otvaranju datoteke" << endl;
		exit(1);
		}
	
	while(getline(datoteka, redak)) {
		if(redak[0] == '>')
			continue;
		relPodaci += UVelikaSlova(redak);
		}

	return relPodaci;
}

// Formira mapu znakova citanjem ulaznog stringa.
map<char, int> PrebrojiElemente(string podaci)
{
	map<char, int > mapaElemenata;
	for(int i = 0; i < int(podaci.size()); i++)
		mapaElemenata[podaci[i]]++;

	return mapaElemenata;
}

// Ispituje je li znak predstavlja aminokiselinu
bool JesteAminokiselina(char k)
{
	for(int i = 0; i < 25; i++)
		if(k == kAminoKiseline[i])
			return true;
	
	return false;
}

// Formira mapu znakova unaprijed zadanim redom.
// Prebrojava elemente na osnovu ulaznog stringa.
map<char, int> PrebrojiAminokiseline(string podaci)
{
	map<char, int> mapaElemenata;
	for(int i = 0; i < brojAKiselina; i++)
		mapaElemenata[kAminoKiseline[i]]=0;
	
	for(int i = 0; i < int(podaci.size()); i++)
		if(JesteAminokiselina(podaci[i]))
			mapaElemenata[podaci[i]]++;
		else
			cout << "!!!Neidentificirani znak \"" << podaci[i] << 
					"\" na mjestu " << i << " ulaznog stringa!!!\n"<<endl ;

	return mapaElemenata;
}

// Ispisuje mapu
void IspisiMapuCharInt(map<char, int> mapa)
{
	map<char, int>::iterator it;
	for(it = mapa.begin(); it != mapa.end(); ++it)
		cout << it->first << " -> " << it->second << endl;
	cout << endl;
}

// Ispisuje mapu aminokiselina
void IspisiMapuAminokiselina(map<char, int> mapa)
{
	for(int i = 0; i < brojAKiselina; i++)
		cout << kAminoKiseline[i] << " -> " << setw(5) << 
				mapa[kAminoKiseline[i]] << endl;
	cout << endl;
}

// Vraca ukupan zbroj vrijednosti svih clanova
int UkupanZbroj(map<char, int> mapa)
{
	int br = 0;
	map<char, int>::iterator it;
	for(it = mapa.begin(); it != mapa.end(); ++it)
		br += it->second;
	
	return br;
}

// GLAVNA FUNKCIJA
int main()
{
	string imeDatoteke = UpisiImeDatoteke();
	string podaci = ProcitajDatoteku(imeDatoteke.c_str());
	map <char, int> mapaAK = PrebrojiAminokiseline(podaci);

	IspisiMapuAminokiselina(mapaAK);

	cout << "Broj ulaznih podataka: " << int(podaci.size()) << endl;
	cout << "Broj prebrojenih podataka: " << UkupanZbroj(mapaAK);
	cout << endl;
}