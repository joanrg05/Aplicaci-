#include <iostream>
#include <string>
using namespace std;

class SessioUsuari {
private:
    string nomUsuari;
    int tempsLlimitSegons;
    bool activa;

    void tancarSessio() { activa = false; }

public:
    SessioUsuari() : SessioUsuari("convidat", 300) {}

    explicit SessioUsuari(string nom) : SessioUsuari(nom, 600) {}

    SessioUsuari(string nom, int temps)
        : nomUsuari(nom), tempsLlimitSegons(temps > 0 ? temps : 60), activa(true) {
    }

    string getNomUsuari() const { return nomUsuari; }
    bool isActiva() const { return activa; }

    void ampliarTemps(int segons) {
        if (segons > 0) tempsLlimitSegons += segons;
    }

    ~SessioUsuari() {
        if (activa) {
            tancarSessio();
            cout << "[AUDITORIA] La sessió de '" << nomUsuari
                << "' s'ha tancat automàticament en sortir de l'àmbit." << endl;
        }
    }
};

int main() {
    {
        SessioUsuari s1;
        SessioUsuari s2("Alex");
        SessioUsuari s3("David", 0);
        s3.ampliarTemps(30);
        s3.ampliarTemps(-5);

        cout << "Dins de l'àmbit..." << endl;
    }
    cout << "Fora de l'àmbit." << endl;
    return 0;
}