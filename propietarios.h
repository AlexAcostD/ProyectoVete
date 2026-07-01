#ifndef PROPIETARIOS_H
#define PROPIETARIOS_H

#include "estructuras.h"

int registrarPropietario(
    struct Propietario *nuevoPropietario,
    const char dni[],
    const char nombres[],
    const char direccion[],
    const char telefono[],
    const char correo[]
);

bool existePropietario(const char dni[]);
void listarPropietarios();
#endif