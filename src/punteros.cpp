#include <iostream>
#include <string>
#include <list>
using namespace std;

class Humano{
    private:
        string nombre;
        int edad;
    public:
        string LeerNommbre();
        int LeerEdad();
};

class Alumno: public Humano{
private:
    int registro;
public:
    int LeerRegistro();

};

class Empleado: public Humano{
private:
    long noEmpleado;
public:
    long LeerNumeroEmpleado();

}

int main(int argc, char const *argv[])
{
    Humano* humano = NULL;
    Alumno* alumno = new Alumno();
    Empleado* empleado = new Empleado();

    humano = alumno;

    humano->LeerEdad();
//Al empleado se le esta tratando como humano
    humano = empleado;

    humano->LeerEdad();

    list<Humano*> listaHumanos;
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Alumno());
    listaHumanos.emplace_back(new Empleado());
    listaHumanos.emplace_back(new Empleado());
    listaHumanos.emplace_back(new Empleado());
    listaHumanos.emplace_back(new Empleado());

    for (auto &&humano : listaHumanos)
    {
        cout << humano->LeerNommbre() << endl;
    }
    
    return 0;
}
