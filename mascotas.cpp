#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include "mascotas.h"
#include "propietarios.h"

using namespace std;

bool soloNumeros(const char cadena[])
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (!isdigit(cadena[i]))
            return false;
    }
    return true;
}

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
    if (nuevaMascota == NULL)
        return 0;


    if (strlen(codigo) == 0 || !soloNumeros(codigo))
        return 0;

    if (existeMascota(codigo))
        return 0;


    if (strlen(dniProp) != 8 || !soloNumeros(dniProp))
        return 0;

    if (!existePropietario(dniProp))
        return 0;


    if (sexo != 'M' && sexo != 'H')
        return 0;


    if (edad < 0 || edad > 40)
        return 0;


    if (peso <= 0 || peso > 150)
        return 0;

    if (strlen(nombre) == 0 ||
        strlen(especie) == 0 ||
        strlen(raza) == 0 ||
        strlen(color) == 0 ||
        strlen(fechaNac) == 0)
        return 0;

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

    ofstream archivo("mascotas.dat", ios::binary | ios::app);

    if (!archivo)
        return 0;

    archivo.write(reinterpret_cast<char*>(nuevaMascota), sizeof(Mascota));
    archivo.close();

    return 1;
}

void listarMascotas()
{
    ifstream archivo("mascotas.dat", ios::binary);

    if (!archivo)
    {
        cout << "No existe el archivo de mascotas." << endl;
        return;
    }

    Mascota mascota;

    cout << "\n===== LISTA DE MASCOTAS =====\n" << endl;

    while (archivo.read(
        reinterpret_cast<char*>(&mascota),
        sizeof(Mascota)))
    {
        cout << "Codigo: " << mascota.codigo << endl;
        cout << "Nombre: " << mascota.nombre << endl;
        cout << "Especie: " << mascota.especie << endl;
        cout << "Raza: " << mascota.raza << endl;
        cout << "Sexo: " << mascota.sexo << endl;
        cout << "Edad: " << mascota.edad << endl;
        cout << "Peso: " << mascota.peso << endl;
        cout << "Color: " << mascota.color << endl;
        cout << "Fecha de Nacimiento: " << mascota.fechaNacimiento << endl;
        cout << "DNI del Propietario: " << mascota.dniPropietario << endl;
        cout << "----------------------------------" << endl;
    }

    archivo.close();
}