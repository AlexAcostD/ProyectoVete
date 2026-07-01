#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "mascotas.h"
using namespace std;
bool buscarMascota(const char codigo[], Mascota *mascota)
{
    ifstream archivo("mascotas.dat", ios::binary);

    if (!archivo)
        return false;

    Mascota aux;

    while (archivo.read(reinterpret_cast<char*>(&aux), sizeof(Mascota)))
    {
        if (strcmp(aux.codigo, codigo) == 0)
        {
            *mascota = aux;
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

int aplicarVacuna(
    const char codMascota[],
    const char nombreVacuna[]
)
{

Mascota mascota;

if (!buscarMascota(codMascota, &mascota))
{
    return 0;   // La mascota no existe
}

cout << "\n===== DATOS DE LA MASCOTA =====\n";
cout << "Codigo : " << mascota.codigo << endl;
cout << "Nombre : " << mascota.nombre << endl;
cout << "Especie: " << mascota.especie << endl;
cout << "Raza   : " << mascota.raza << endl;
cout << "Edad   : " << mascota.edad << endl;
cout << "Peso   : " << mascota.peso << endl;
cout << "Color  : " << mascota.color << endl;
cout << "===============================\n";

    bool vacunaValida = false;

    if (
        strcmp(nombreVacuna, "Antirrabica") == 0 ||
        strcmp(nombreVacuna, "Triple Felina") == 0 ||
        strcmp(nombreVacuna, "Parvovirus") == 0
    )
    {
        vacunaValida = true;
    }

    if (!vacunaValida)
    {
        return 0;
    }


    VacunaAplicada vacuna;

    strcpy(vacuna.codigoMascota, codMascota);

    strcpy(
        vacuna.nombreVacuna,
        nombreVacuna
    );

    time_t t = time(NULL);

    tm *fechaActual = localtime(&t);

    sprintf(
        vacuna.fechaAplicacion,
        "%02d/%02d/%04d",
        fechaActual->tm_mday,
        fechaActual->tm_mon + 1,
        fechaActual->tm_year + 1900
    );

    ofstream archivo(
        "vacunas.dat",
        ios::binary | ios::app
    );

    if (!archivo)
    {
        return 0;
    }

    archivo.write(
        reinterpret_cast<char*>(&vacuna),
        sizeof(VacunaAplicada)
    );

    archivo.close();

    return 1;
}