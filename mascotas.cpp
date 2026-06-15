#include <iostream>
#include <fstream>
#include <cstring>

#include "mascotas.h"
#include "propietarios.h"

using namespace std;

bool existeMascota(const char codigo[])
{
    ifstream archivo("mascotas.dat", ios::binary);

    if (!archivo)
    {
        return false;
    }

    Mascota mascota;

    while (
        archivo.read(
            reinterpret_cast<char*>(&mascota),
            sizeof(Mascota)
        )
    )
    {
        if (strcmp(mascota.codigo, codigo) == 0)
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

int registrarMascota(
    Mascota *nuevaMascota,
    const char codigo[],
    const char nombre[],
    const char especie[],
    const char raza[],
    char sexo,
    int edad,
    float peso,
    const char color[],
    const char fechaNac[],
    const char dniProp[]
)
{
    // Validar puntero
    if (nuevaMascota == NULL)
    {
        return 0;
    }

    // Código duplicado
    if (existeMascota(codigo))
    {
        return 0;
    }

    // Propietario inexistente
    if (!existePropietario(dniProp))
    {
        return 0;
    }

    // Sexo válido
    if (sexo != 'M' && sexo != 'H')
    {
        return 0;
    }

    // Edad válida
    if (edad < 0)
    {
        return 0;
    }

    // Peso válido
    if (peso <= 0)
    {
        return 0;
    }

    // Llenar estructura
    strcpy(nuevaMascota->codigo, codigo);
    strcpy(nuevaMascota->nombre, nombre);
    strcpy(nuevaMascota->especie, especie);
    strcpy(nuevaMascota->raza, raza);

    nuevaMascota->sexo = sexo;
    nuevaMascota->edad = edad;
    nuevaMascota->peso = peso;

    strcpy(nuevaMascota->color, color);
    strcpy(nuevaMascota->fechaNacimiento, fechaNac);
    strcpy(nuevaMascota->dniPropietario, dniProp);

    // Guardar archivo
    ofstream archivo(
        "mascotas.dat",
        ios::binary | ios::app
    );

    if (!archivo)
    {
        return 0;
    }

    archivo.write(
        reinterpret_cast<char*>(nuevaMascota),
        sizeof(Mascota)
    );

    archivo.close();

    return 1;
}