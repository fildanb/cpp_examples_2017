#include "stdafx.h"
#include<iostream>

using namespace std;

class Apartament {
private:
	char* proprietar;
	char adresa[50];
	unsigned int an_constructie;
	char confort;
	int numar_camere;
	double* suprafete;

	const int id;
	static unsigned int numar_apartamente;

public:
	Apartament():id(Apartament::numar_apartamente) {
		this->proprietar = new char[strlen("Anonim") + 1];
		strcpy(this->proprietar, "Anonim");
		strcpy(this->adresa, "Necunoscuta");
		this->an_constructie = 2000;
		this->confort = '1';
		this->numar_camere = 0;
		this->suprafete = NULL;

		Apartament::numar_apartamente++;
	}
	Apartament(char* v_proprietar, char v_adresa[50],
		unsigned int v_an_constructie, char v_confort,
		int v_nr_camere, double* v_suprafete)
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->an_constructie = v_an_constructie;
		this->confort = v_confort;
		this->numar_camere = v_nr_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}

	}

	//constructor cu valori implicite pentru an
	Apartament(char* v_proprietar, char v_adresa[50],
		char v_confort, unsigned int v_an_constructie = 2017)
		:an_constructie(v_an_constructie),
		id(Apartament::numar_apartamente)
	{
		this->proprietar = new char[strlen(v_proprietar) + 1];
		strcpy(this->proprietar, v_proprietar);
		strcpy(this->adresa, v_adresa);
		this->confort = v_confort;
		this->numar_camere = 0;
		this->suprafete = NULL;
		Apartament::numar_apartamente += 1;
	}

	void afisare() {
		cout << "Id: " << this->id << endl;
		cout << "Proprietar: " << this->proprietar << endl;
		cout << "Adresa: " << this->adresa << endl;
		cout << "An constructie: " << this->an_constructie << endl;
		cout << "Confort: " << this->confort << endl;
		cout << "Numar camere: " << this->numar_camere << endl;
		for (int i = 0; i < this->numar_camere; i++) {
			cout << "Suprafata camerei " << i + 1 << " este:" << this->suprafete[i] << endl;
		}
	}

	//destructor
	~Apartament() {
		cout << "Destructor....." << endl;
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}

		Apartament::numar_apartamente -= 1;
	}


	//getteri si setteri
	char* getProprietar() {
		return this->proprietar;
	}

	void setProprietar(char* v_proprietar) {
		if (strlen(v_proprietar) < 5) {
			throw new exception("Nume prea scurt.");
		}
		else {
			//nu generez memory leak
			if (this->proprietar != NULL) {
				delete[] this->proprietar;
			}
			this->proprietar = new char[strlen(v_proprietar) + 1];
			strcpy(this->proprietar, v_proprietar);
		}
	}

	char* getAdresa() {
		return this->adresa;
	}

	double* getSuprafete() {
		return this->suprafete;
	}

	int getNumarCamere() {
		return this->numar_camere;
	}

	void setSuprafete(int v_nr_camere, double* v_suprafete) {
		this->numar_camere = v_nr_camere;
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->suprafete = new double[v_nr_camere];
		for (int i = 0; i < v_nr_camere; i++) {
			this->suprafete[i] = v_suprafete[i];
		}
	}

	//constructor de copiere
	Apartament(const Apartament& sursa)
	:id(Apartament::numar_apartamente++){
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->an_constructie = sursa.an_constructie;
		this->confort = sursa.confort;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}
	}

	//getter pentru atributul constant
	int getId() {
		return this->id;
	}

	//getter si setter pentru atributul static
	static unsigned int getNumarApartamente() {
		return Apartament::numar_apartamente;
	}

	static void setNumarApartamente(unsigned int nr) {
		Apartament::numar_apartamente = nr;
	}


	//operator=
	Apartament& operator=(const Apartament& sursa) {
		if (this->proprietar != NULL) {
			delete[] this->proprietar;
		}
		if (this->suprafete != NULL) {
			delete[] this->suprafete;
		}
		this->proprietar = new char[strlen(sursa.proprietar) + 1];
		strcpy(this->proprietar, sursa.proprietar);
		strcpy(this->adresa, sursa.adresa);
		this->an_constructie = sursa.an_constructie;
		this->confort = sursa.confort;
		this->numar_camere = sursa.numar_camere;
		this->suprafete = new double[this->numar_camere];
		for (int i = 0; i < this->numar_camere; i++) {
			this->suprafete[i] = sursa.suprafete[i];
		}

		return *this;
	}


	friend ostream& operator<<(ostream& out, Apartament& a) {
		out << "Id: " << a.id << endl;

		return out;
	}
};


//initializare atribut static
unsigned int Apartament::numar_apartamente = 0;


void main()
{
	Apartament::setNumarApartamente(1000);
	Apartament a1;
	a1.afisare();

	//un pointer la un obiect existent
	Apartament* pa1;
	pa1 = &a1;
	pa1->afisare();

	Apartament* pa2 = new Apartament();
	pa2->afisare();
	delete pa2;


	cout << "--------------------------------------" << endl;
	double v[2] = { 15.6,20.4 };
	Apartament a2("Enachescu Irina", "strada x", 2008, '2', 2, v);
	a2.afisare();

	Apartament* pa3 = new Apartament("Ion Popescu", "Bucuresti", 2010, '1', 2, v);
	pa3->afisare();

	Apartament a3("Ion Ion", "strada Apei", '2');
	a3.afisare();

	Apartament a4("Ion Ion Ion", "strada Apei 2", '1', 2001);
	a4.afisare();

	Apartament a5;

	//setteri
	a5.setProprietar("Irina");
	a5.setSuprafete(2, v);

	//getteri
	cout << "Proprietar: " << a5.getProprietar() << endl;
	cout << "Numar camere:" << a5.getNumarCamere() << endl;
	for (int i = 0; i < a5.getNumarCamere(); i++) {
		cout << a5.getSuprafete()[i] << endl;
	}

	Apartament a6 = a5;
	a6.afisare();

	cout << "Numarul total de apartamente este: " <<
		Apartament::getNumarApartamente() << endl;;

	//operatorul = 
	Apartament a7;
	a7 = a6;
	a7.afisare();

	cout << a7;
}

