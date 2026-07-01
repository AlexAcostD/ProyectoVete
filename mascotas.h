#ifndef MASCOTAS_H
#define MASCOTAS_H

#include "estructuras.h"

int registrarMascota(
    struct Mascota *nuevaMascota,
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
);

bool existeMascota(const char codigo[]);
void listarMascotas();
#endif