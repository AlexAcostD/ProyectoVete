#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

struct VacunaAplicada
{
    char codigoMascota[10];
    char nombreVacuna[30];
    char fechaAplicacion[11];
};

int aplicarVacuna(
    const char codMascota[],
    const char nombreVacuna[],
    int edadMascota,
    float pesoMascota
)
{
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

    // Edad mínima
    if (edadMascota < 1)
    {
        return 0;
    }

    // Peso mínimo
    if (pesoMascota < 1.0)
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