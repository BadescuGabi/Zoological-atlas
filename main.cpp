#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include <vector>
#include <typeinfo>
#include <iomanip>
#include<math.h>

using namespace std;
//PS: as prefera daca ati putea va rog ca fiecare data pe care o introduceti sa
// aiba prima litera "Mare" si restu normale
/*
 *                                      AtlasZoologic(template)
 *
 *                                    Regn(abstracta)
 *                                 /                \
 *                                /                  \
 *                  (abstracta) Vertebrata           Nevertebrata
 *                 /      |         |       \
 *               /        |         |        \
 *            Pesti    Pasari      Reptile    Mamifere
 */
class Regn {
protected:
    int longevitate;
    string nume;
    bool vertebre;
    string culoare;
public:
    Regn();

    Regn(int);

    Regn(const Regn &Regn);

    virtual void afisare(ostream &os);

    virtual void actiune() = 0;

    virtual void citire(istream &in);

    friend std::istream &operator>>(std::istream &in, Regn &Regn);

    friend ostream &operator<<(ostream &os, Regn &Regn);

    Regn &operator=(const Regn &);

    virtual ~Regn();
};


Regn::Regn() : vertebre(true), nume(nume), culoare(culoare), longevitate(longevitate) {}

Regn::Regn(const Regn &Regn) : vertebre(Regn.vertebre), nume(Regn.nume), longevitate(Regn.longevitate),
                               culoare(Regn.culoare) {}

Regn::Regn(int a) {
    this->vertebre = false;
    this->longevitate = 0;
    this->culoare = "";
    this->nume = "";
}

Regn::~Regn() {
    nume = "";
    culoare = "";
    longevitate = 0;
    vertebre = false;
}

istream &operator>>(istream &in, Regn &Regn) {
    Regn.citire(in);
    return in;
}

ostream &operator<<(ostream &os, Regn &Regn) {
    Regn.afisare(os);
    return os;
}

Regn &Regn::operator=(const Regn &Regn) {
    if (this != &Regn) {
        nume = Regn.nume;
        vertebre = Regn.vertebre;
        culoare = Regn.culoare;
        longevitate = Regn.longevitate;
    }
    return *this;

}

void Regn::citire(istream &in) {
    cout << "Numele animalului: ";
    in >> nume;
    //poate faci si tu ceva de exceptii aici zic
    cout << "Durata sa de viata este : ";
    in.exceptions(std::istream::failbit);
    try {
        in >>longevitate;
    }
    catch (const std::ios_base::failure&) {
        in.clear();
        in.ignore(9999999, '\n');
        std::cout << "Numar invalid\n";
    }
    cout << "Culoare animalului este: ";
    cin.get();
    getline(in, culoare);
}

void Regn::afisare(ostream &os) {
    os << endl;
    os << "Numele animalului  este: ";
    os << nume;
    os << endl;
    if (vertebre == true)
        os << "Animalul este vertebrat";
    else
        os << "Animalul nu este vertebrat";
    os << '\n';
    os << "Culoarea animalului este: " << culoare << '\n';
    os << "Animalul traieste in medie " << longevitate << " ani" << '\n';
}

class Nevertebrate : public Regn {
private:
    int nr_picioare;
public:

    Nevertebrate();

    Nevertebrate(const Nevertebrate &);

    virtual ~Nevertebrate();

    void citire(istream &in);

    inline void actiune() {}

    void afisare(ostream &os);

    friend ostream &operator<<(ostream &os, Nevertebrate &nevertebrate);

    friend std::istream &operator>>(std::istream &in, Nevertebrate &nevertebrate);

    Nevertebrate &operator=(const Nevertebrate &);

};

Nevertebrate::Nevertebrate() :
        Regn(1),
        nr_picioare(nr_picioare) {}

Nevertebrate::~Nevertebrate() {
    nr_picioare = 0;
}

Nevertebrate::Nevertebrate(const Nevertebrate &nevertebrate) : Regn(nevertebrate),
                                                               nr_picioare(nevertebrate.nr_picioare) {}

void Nevertebrate::citire(istream &in) {
    Regn::citire(in);
    if (vertebre == true) {}                            //try catch boule
    cout << "Introduceti nr_picioare:";
    in >> nr_picioare;
}

void Nevertebrate::afisare(ostream &os) {
    Regn::afisare(os);
    //aici faci try catch cu vertebre
    cout << "Nevertebratul are: ";
    os << nr_picioare << " picioare"<<endl;
}

ostream &operator<<(ostream &os, Nevertebrate &nevertebrate) {
    nevertebrate.afisare(os);
    return os;
}

istream &operator>>(std::istream &in, Nevertebrate &nevertebrate) {
    nevertebrate.citire(in);
    return in;
}

Nevertebrate &Nevertebrate::operator=(const Nevertebrate &nevertebrate) {
    if (this != &nevertebrate) {
        nr_picioare = nevertebrate.nr_picioare;
    }
    return *this;
}

class Vertebrate : public Regn {

protected:
    int nr_vertebre;
    string marime;
public:

    Vertebrate();

    Vertebrate(int nrVertebre, const string &marime);

    Vertebrate(const Vertebrate &vertebrate);

    virtual ~Vertebrate();

    void afisare(ostream &os);

    void citire(istream &in);

    friend istream &operator>>(istream &in, Nevertebrate &vertebrate);

    friend ostream &operator<<(ostream &os, Vertebrate &vertebrate);

    Vertebrate &operator=(const Vertebrate &);
};

Vertebrate::Vertebrate() : Regn(2) {
    this->vertebre = 0;
    this->marime = "";
}

Vertebrate::Vertebrate(int nrVertebre, const string &marime) :
        Regn(2),
        nr_vertebre(nrVertebre),
        marime(marime) {}

Vertebrate::Vertebrate(const Vertebrate &vertebrate) : Regn(vertebrate), marime(vertebrate.marime),
                                                       nr_vertebre(vertebrate.nr_vertebre) {}

Vertebrate::~Vertebrate() {
    nr_vertebre = 0;
    marime = "";
}

void Vertebrate::citire(istream &in) {
    Regn::citire(in);
    if (vertebre == false) {}                      //try catch boule
    cout << "Numarul de vertebre pe care il are animalul: ";
    in >> nr_vertebre;
    cout << "Marimea animalului: ";
    in >> marime;
}

void Vertebrate::afisare(ostream &os) {
    Regn::afisare(os);
    os << "Marimea animalului este: " << marime << '\n';
    os << "Animalul are " << nr_vertebre << " vertebre" << '\n';
}

istream &operator>>(istream &in, Vertebrate &vertebrate) {
    vertebrate.citire(in);
    return in;
}

ostream &operator<<(ostream &os, Vertebrate &vertebrate) {
    vertebrate.afisare(os);
    return os;
}

Vertebrate &Vertebrate::operator=(const Vertebrate &vertebrate) {
    if (this != &vertebrate) {
        nr_vertebre = vertebrate.nr_vertebre;
        marime = vertebrate.marime;
    }
    return *this;
}

class Pasari : public Vertebrate {
private:
    bool zburatoare;
    bool inotatoare;
public:

    Pasari();

    Pasari(int nrVertebre, const string &marime, bool zburatoare, bool inotatoare);

    Pasari(const Pasari &);

    ~Pasari();

    void actiune();

    void citire(istream &in);

    void afisare(ostream &os);

    friend ostream &operator<<(ostream &os, Pasari &pasari);

    friend istream &operator>>(istream &in, Pasari &pasari);

    Pasari &operator=(const Pasari &);
};

Pasari::Pasari() : Vertebrate() {
    zburatoare = false;
    inotatoare = false;
}

Pasari::Pasari(int nrVertebre, const string &marime, bool zburatoare, bool inotatoare) : Vertebrate(),
                                                                                         zburatoare(zburatoare),
                                                                                         inotatoare(inotatoare) {}

Pasari::Pasari(const Pasari &pasari) : Vertebrate(pasari), zburatoare(pasari.zburatoare),
                                       inotatoare(pasari.inotatoare) {}

Pasari::~Pasari() {
    zburatoare = NULL;
    inotatoare = NULL;
}

void Pasari::citire(istream &in) {
    Vertebrate::citire(in);
    cout << "Pasarea creata zboara?(Da/Nu):";
    string var;
    cin >> var;
    if (var == "Da" or var == "da")
        zburatoare = true;
    else
        zburatoare = false;
    cout << "Pasarea creata inoata?(Da/Nu):";
    string var2;
    cin >> var2;
    if (var2 == "Da" or var2 == "da")
        inotatoare = true;
    else
        inotatoare = false;                                           //try catch si aici si sus
}

void Pasari::afisare(ostream &os) {
    Vertebrate::afisare(os);
    if (zburatoare == true)
        cout << "Pasarea este zburatoare";
    if (inotatoare == true)
        cout << "Pasarea este inotatoare";
    Pasari::actiune();
}

void Pasari::actiune() {
    if (nume == "Gaina" or nume == "gaina") {
        cout << endl;
        cout << "Gaina face cucuriguu"<<endl;
    }
    if (nume == "Rata" or nume == "rata") {
        cout << endl;
        cout << "Rata face mac mac"<<endl;
    }
    if (nume == "Porumbel" or nume == "Porumbel") {
        cout << endl;
        cout << "Porumbel gru gru"<<endl;
    }
}

istream &operator>>(istream &in, Pasari &pasari) {
    pasari.citire(in);
    return in;
}

ostream &operator<<(ostream &os, Pasari &pasari) {
    pasari.afisare(os);
    return os;
}

Pasari &Pasari::operator=(const Pasari &pasari) {
    if (this != &pasari) {
        zburatoare = pasari.zburatoare;
        inotatoare = pasari.inotatoare;
    }
    return *this;
}

class Reptile : public Vertebrate {
private:
    bool taratoare;
public:
    Reptile();

    Reptile(const Reptile &);

    virtual ~Reptile();

    void citire(istream &in);

    void afisare(ostream &os);

    void actiune();

    friend istream &operator>>(istream &in, Reptile &reptile);

    friend ostream &operator<<(ostream &os, Reptile &reptile);

    Reptile &operator=(const Reptile &);
};

Reptile::Reptile() : Vertebrate(), taratoare(taratoare) {}

Reptile::Reptile(const Reptile &reptile) : Vertebrate(reptile), taratoare(reptile.taratoare) {}

Reptile::~Reptile() {
    taratoare = NULL;
}

void Reptile::citire(istream &in) {
    Vertebrate::citire(in);
    string var;
    cout << "Reptila este taratoare?(Da/Nu)";
    in >> var;
    if (var == "Da" or var == "da")
        taratoare = true;
    else
        taratoare = false;
}

void Reptile::afisare(ostream &os) {
    Vertebrate::afisare(os);
    if (taratoare == true)
        cout << "Reptila este taratoare"<<endl;
    else
        cout << "Reptila nu este taratoare"<<endl;
    Reptile::actiune();
}

void Reptile::actiune() {
    if (nume == "sarpe" or nume == "Sarpe") {
        cout << endl;
        cout << "Sarpele face ssss"<<endl;
    }
}

istream &operator>>(istream &in, Reptile &reptile) {
    reptile.citire(in);
    return in;
}

ostream &operator<<(ostream &os, Reptile &reptile) {
    reptile.afisare(os);
    return os;
}

Reptile &Reptile::operator=(const Reptile &reptile) {
    if (this != &reptile)
        taratoare = reptile.taratoare;
    return *this;
}

class Mamifere : public Vertebrate {
private:
    int greutate;
    bool carnivor;

public:
    Mamifere();

    Mamifere(const Mamifere &);

    ~Mamifere();

    void citire(istream &in);

    void afisare(ostream &os);

    void actiune();

    friend ostream &operator<<(ostream &os, Mamifere &mamifere);

    friend istream &operator>>(istream &in, Mamifere &mamifere);

    Mamifere &operator=(const Mamifere &);
};


Mamifere::Mamifere() : Vertebrate(), greutate(greutate), carnivor(carnivor) {}

Mamifere::Mamifere(const Mamifere &mamifer) : Vertebrate(mamifer), greutate(mamifer.greutate),
                                              carnivor(mamifer.carnivor) {}

Mamifere::~Mamifere() {
    carnivor = NULL;
    greutate = 0;
}

void Mamifere::citire(istream &in) {
    Vertebrate::citire(in);
    cout << "\n" << "Greutatea mamiferului este: ";
    in >> greutate;
    cout << "\n";
    cout << "Mamiferul este carnivor?(Da/Nu)";
    string var;
    cin >> var;
    if (var == "Da" or var == "da")
        carnivor = true;
    else
        carnivor = false;
}

void Mamifere::afisare(ostream &os) {
    Vertebrate::afisare(os);
    os << "Greutatea mamiferului este: " << greutate << " kg"<<endl;
    if (carnivor == true)
        os << "Mamiferul este carnivor"<<endl;
    else
        os << "Mamiferul este ierbivor"<<endl;
    Mamifere::actiune();
}

void Mamifere::actiune() {
    if (nume == "Pisica" or nume == "pisica")
        cout << "\n" << "Pisica face miau"<<endl;
    if (nume == "Caine" or nume == "caine")
        cout << "\n" << "Cainele face ham"<<endl;
    if (nume == "vaca" or nume == "Vaca")
        cout << "\n" << "Vaca face muuu"<<endl;
    if (nume == "oaie" or nume == "Oaie")
        cout << "\n" << "Oaia face meee"<<endl;
    if (nume == "capra" or nume == "Capra")
        cout << "\n" << "Capra face beee"<<endl;
    if (nume == "Urs" or nume == "urs")
        cout << "\n" << "Ursul face mooor"<<endl;
    //poate mai adaug cateva
}

ostream &operator<<(ostream &os, Mamifere &mamifere) {
    mamifere.afisare(os);
    return os;
}

istream &operator>>(istream &in, Mamifere &mamifere) {
    mamifere.citire(in);
    return in;
}

Mamifere &Mamifere::operator=(const Mamifere &mamifere) {
    if (this != &mamifere) {
        carnivor = mamifere.carnivor;
        greutate = mamifere.greutate;
    }
    return *this;
}

class Pesti : public Vertebrate {
private:
    int numar_branhii;
    int viteza_inot;
    bool rapitori;
    int lungime;
public:
    Pesti();

    Pesti(const Pesti &);

    ~Pesti();

    void citire(istream &in);

    void afisare(ostream &os);

    void actiune();

    friend ostream &operator<<(ostream &os, Pesti &pesti);

    friend istream &operator>>(istream &in, Pesti &pesti);

    int getLungime() const;

    Pesti &operator=(const Pesti &);

    bool isRapitori() const;

};


Pesti::Pesti() : Vertebrate(), numar_branhii(numar_branhii), viteza_inot(viteza_inot), lungime(lungime),
                 rapitori(rapitori) {}

Pesti::Pesti(const Pesti &pesti) : Vertebrate(pesti), numar_branhii(pesti.numar_branhii),
                                   viteza_inot(pesti.viteza_inot), rapitori(pesti.rapitori), lungime(pesti.lungime) {}

Pesti::~Pesti() {
    numar_branhii = 0;
    viteza_inot = 0;
    rapitori = NULL;
    lungime = 0;
}

void Pesti::actiune() {
    cout << '\n' << "Pestii inoata";
}

void Pesti::citire(istream &in) {
    Vertebrate::citire(in);
    cout << "Introduceti numarul de branhii al pestelui: ";
    in >> numar_branhii;
    cout << "Introduceti viteza cu care inoata pestele: ";
    in >> viteza_inot;
    cout << "Pestele citit este rapitor?(Da/Nu)";
    string var;
    in >> var;
    if (var == "Da" or var == "da")
        rapitori = true;
    else
        rapitori = false;
    cout << "Lungimea pestelui este: ";
    in >> lungime;
}


void Pesti::afisare(ostream &os) {
    Vertebrate::afisare(os);
    os << "Pestele are " << numar_branhii << " branhii" << "\n";
    os << "Viteza de inot a pestelui este de " << viteza_inot << " km/h" << '\n';
    if (rapitori == true)
        os << "Pestele este rapitor";
    else
        os << "Pestele nu este rapitor";
    os << '\n' << "Lungimea pestelui este de: " << lungime << "metri" << '\n';
}

istream &operator>>(istream &in, Pesti &pesti) {
    pesti.citire(in);
    return in;
}

ostream &operator<<(ostream &os, Pesti &pesti) {
    pesti.afisare(os);
    return os;
}

Pesti &Pesti::operator=(const Pesti &pesti) {
    if (this != &pesti) {
        numar_branhii = pesti.numar_branhii;
        viteza_inot = pesti.viteza_inot;
        rapitori = pesti.rapitori;
        lungime = pesti.lungime;
    }
    return *this;
}

bool Pesti::isRapitori() const {
    return rapitori;
}

int Pesti::getLungime() const {
    return lungime;
}

template<typename T>
class AtlasZoologic {
    list<T> Atlas;
    static int numar_animale;
public:
    static int getNumarAnimale();

public:
    AtlasZoologic() {
        Atlas.resize(0);
    }

    AtlasZoologic(const AtlasZoologic<T> &);

    T &operator+=(T &ob);

    template<typename U>
    friend ostream &operator<<(ostream &os, AtlasZoologic<U> &carte);

    //nu am mai supraincarcat si >> ca nu ii vedeam rostul
    AtlasZoologic &operator=(const AtlasZoologic &);

    ~AtlasZoologic();
};


template<typename T>
int AtlasZoologic<T>::numar_animale = 0;

template<typename T>
T &AtlasZoologic<T>::operator+=(T &ob) {
    numar_animale++;
    cout << endl;
    cin >> *ob;
    Atlas.push_back(ob);
}

template<typename T>

AtlasZoologic<T> &AtlasZoologic<T>::operator=(const AtlasZoologic<T> &carte) {
    if (this != &carte) {
        Atlas = carte.Atlas;
    }
    return *this;
}

template<typename T>
AtlasZoologic<T>::AtlasZoologic(const AtlasZoologic<T> &carte) {
    if (this != &carte) {
        Atlas = carte.Atlas;
    }
}


template<typename U>
ostream &operator<<(ostream &os, AtlasZoologic<U> &carte) {
    for (auto it = carte.Atlas.begin(); it != carte.Atlas.end(); it++) {
        if (Pesti *p = dynamic_cast<Pesti *>(*it)) {
            cout << "Peste: ";
            cout << **it;
        }
        if (Pasari *p = dynamic_cast<Pasari *>(*it)) {
            cout << "Pasare ";
            cout << **it;
        }
        if (Reptile *p = dynamic_cast<Reptile *>(*it)) {
            cout << "Reptila ";
            cout << **it;
        }
        if (Mamifere *p = dynamic_cast<Mamifere *>(*it)) {
            cout << "Mamifer ";
            cout << **it;
        }
        if (Nevertebrate *p = dynamic_cast<Nevertebrate *>(*it)) {
            cout << "Nevertebrata";
            cout << **it;
        }
    }

    return os;
}

template<typename T>
AtlasZoologic<T>::~AtlasZoologic() {
    Atlas.clear();
}

template<typename T>
 int AtlasZoologic<T>::getNumarAnimale() {
    return numar_animale;
}


template<>
class AtlasZoologic<Pesti> {
    list<Pesti> Atlas_p;
    static int nr_pesti;
public:
    static int getNrPesti();

    static int getNrPestiConditie();

private:
    static int nr_pesti_conditie;
public:
    AtlasZoologic() {
        Atlas_p.clear();
    }

    AtlasZoologic(const AtlasZoologic<Pesti> &peste) {
        if (this != &peste) {
            Atlas_p = peste.Atlas_p;
        }
    }

    AtlasZoologic &operator=(const AtlasZoologic<Pesti> &peste) {
        if (this != &peste) {
            Atlas_p = peste.Atlas_p;
        }
        return *this;
    }

    Pesti &operator+=(Pesti &ob) {
        nr_pesti++;
        cout << endl;
        cin >> ob;
        Atlas_p.push_back(ob);
        if (ob.getLungime() > 1 and ob.isRapitori() == true)
            nr_pesti_conditie++;
    }

    friend ostream &operator<<(ostream &os, AtlasZoologic<Pesti> &carte) {
        for (auto it = carte.Atlas_p.begin(); it != carte.Atlas_p.end(); it++)
            cout << *it;
        os << "\n";
    }
};

int AtlasZoologic<Pesti>::nr_pesti = 0;
int AtlasZoologic<Pesti>::nr_pesti_conditie = 0;

int AtlasZoologic<Pesti>::getNrPesti() {
    return nr_pesti;
}

int AtlasZoologic<Pesti>::getNrPestiConditie() {
    return nr_pesti_conditie;
}

void menu() {
    static int ok1 = 0, ok2 = 0;
    cout << setw(50);
    cout << "Bine ati venit!" << '\n';
    cout<<"Va rog sa introduceti datele asa cum este precizat in paranteza ";
    string optiune, optiune4 = "Da";
    while (optiune4 == "Da") {
        cout << "Va rog sa selectati una din cele 3 optiuni de mai jos:" << '\n';
        cout << "Optiunea 1: doriti sa creeam un atlas de animale?" << '\n';
        cout << "Optiunea 2: doriti sa creeam un atlas de pesti?" << '\n';
        cout << "Optiunea 3: doriti sa citim n atlase cu animale?" << '\n';
        cin >> optiune;
        AtlasZoologic<Regn *> Atlas;
        AtlasZoologic<Pesti> Atlas2;
        if (optiune == "1") {
            ok1 = 1;
            string optiune2 = "Da";
            while (optiune2 == "Da") {
                string optiune3;
                cout << "Ce tip de animal doriti sa adaugati in atlas: (Peste/Pasare/Reptila/Mamifer/Nevertebrat)";
                cin >> optiune3;
                if (optiune3 == "Peste") {
                    Regn *animal = new Pesti;
                    Atlas += animal;
                }
                if (optiune3 == "Pasare") {
                    Regn *animal = new Pasari;
                    Atlas += animal;
                }
                if (optiune3 == "Reptila") {
                    Regn *animal = new Reptile;
                    Atlas += animal;
                }
                if (optiune3 == "Mamifer") {
                    Regn *animal = new Mamifere;
                    Atlas += animal;
                }
                if (optiune3 == "Nevertebrat") {
                    Regn *animal = new Nevertebrate;
                    Atlas += animal;
                }
                cout << "Doriti sa mai adaugati animale in atlas?";
                cin >> optiune2;
                if (optiune2 == "Nu")
                    break;
            }
            cout << Atlas;
        }
        if (optiune == "2") {
            ok2 = 1;
            string optiune2 = "Da";
            while (optiune2 == "Da") {
                Pesti animal;
                Atlas2 += animal;
                cout<<"Doriti sa mai adaugati pesti in atlas?";
                cin >> optiune2;
                if (optiune2 == "Nu")
                    break;
            }
            cout << Atlas2;
        }
        if (optiune == "3") {
            ok1=1;
            vector<AtlasZoologic<Regn *>> atlas;
            string optiune2 = "Da";
            string citire_atlas = "Da";
            while (citire_atlas == "Da") {
                AtlasZoologic<Regn*> a;
                Atlas=a;
                while (optiune2 == "Da") {
                    string optiune3;
                    cout << "Ce tip de animal doriti sa adaugati in atlas: (Peste/Pasare/Reptila/Mamifer/Nevertebrat)";
                    cin >> optiune3;
                    if (optiune3 == "Peste") {
                        Regn *animal = new Pesti;
                        Atlas += animal;
                    }
                    if (optiune3 == "Pasare") {
                        Regn *animal = new Pasari;
                        Atlas += animal;
                    }
                    if (optiune3 == "Reptila") {
                        Regn *animal = new Reptile;
                        Atlas += animal;
                    }
                    if (optiune3 == "Mamifer") {
                        Regn *animal = new Mamifere;
                        Atlas += animal;
                    }
                    if (optiune3 == "Nevertebrat") {
                        Regn *animal = new Nevertebrate;
                        Atlas += animal;
                    }
                    cout << "Doriti sa mai adaugati animale in atlas?";
                    cin >> optiune2;
                    if (optiune2 == "Nu")
                        break;
                }
                try {
                    atlas.push_back(Atlas);
                }
                catch(const std::bad_alloc &) {
                    cerr<<"Memorie insuficienta";
                    exit(1);
                }

            cout<<"Doriti sa mai citit un atlas?(Da/Nu)";
            cin>>citire_atlas;
            optiune2="Da";
            if (citire_atlas=="Nu")
            break;

            }
            int i=1;
            for(auto it=atlas.begin();it!=atlas.end();it++){
                cout<<"Atlasul "<<i<<" contine"<<'\n';
                i++;
                cout<<*it;
            }
            }
            cout << "Doriti sa reveniti la meniu? (Da/Nu)";
            cin >> optiune4;
            for (int i=0;i<15;++i)
                cout<<"\n";
            if (optiune4 == "Nu" and ok1 == 1) {
                cout << "In atlasul/le cu animale au fost inregistrate: " << Atlas.getNumarAnimale() << " animale"<<endl;
            }
            if (optiune4 == "Nu" and ok2 == 1) {
                cout << "In atlasul/le cu pesti au fost inregistrati " << Atlas2.getNrPesti() << " pesti"<<endl;
                cout << " dintre care " << Atlas2.getNrPestiConditie()
                     << " pesti rapitori cu lungimea mai mare de un metru.";
            }
        }
    }

    int main() {

        menu();
        return 0;
    }
