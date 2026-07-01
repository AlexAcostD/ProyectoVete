#include <iostream>
#include <fstream>
#include <cstring>

#include "propietarios.h"

using namespace std;

bool existePropietario(const char dni[])
{
    ifstream archivo("propietarios.dat", ios::binary);
    if (!archivo)
    {
        return false;}

    Propietario propietario;

    while (archivo.read(
        reinterpret_cast<char*>(&propietario),
        sizeof(Propietario)))
    {
        if (strcmp(propietario.dni, dni) == 0)
        {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

int registrarPropietario(
    Propietario *nuevoPropietario,
    const char dni[],
    const char nombres[],
    const char direccion[],
    const char telefono[],
    const char correo[]
)
{
    if (nuevoPropietario == NULL)
    {
        return 0;
    }

    if (strlen(dni) != 8)
    {
        return 0;
    }

    for (int i = 0; i < 8; i++)
    {
        if (dni[i] < '0' || dni[i] > '9')
        {
            return 0;
        }
    }

    if (existePropietario(dni))
    {
        return 0;
    }

    strcpy(nuevoPropietario->dni, dni);
    strcpy(nuevoPropietario->nombres, nombres);
    strcpy(nuevoPropietario->direccion, direccion);
    strcpy(nuevoPropietario->telefono, telefono);
    strcpy(nuevoPropietario->correo, correo);

 
    ofstream archivo(
        "propietarios.dat",
        ios::binary | ios::app
    );

    if (nuevoPropietario == NULL)
        return 0;

    if (strlen(dni) != 8)
        return 0;

    if (existePropietario(dni))
        return 0;

    if (!archivo)
        return 0;

    archivo.write(
        reinterpret_cast<char*>(nuevoPropietario),
        sizeof(Propietario)
    );

    archivo.close();

    return 1;
}



void listarPropietarios()
{
    ifstream archivo("propietarios.dat", ios::binary);

    if (!archivo)
    {
        cout << "No existe el archivo de propietarios." << endl;
        return;
    }

    Propietario propietario;

    cout << "\n===== LISTA DE PROPIETARIOS =====\n" << endl;

    while (archivo.read(
        reinterpret_cast<char*>(&propietario),
        sizeof(Propietario)))
    {
        cout << "DNI: " << propietario.dni << endl;
        cout << "Nombres: " << propietario.nombres << endl;
        cout << "Direccion: " << propietario.direccion << endl;
        cout << "Telefono: " << propietario.telefono << endl;
        cout << "Correo: " << propietario.correo << endl;
        cout << "----------------------------------" << endl;
    }

    archivo.close();
}