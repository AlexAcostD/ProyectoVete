#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "estructuras.h"

Consulta registrarConsultaMedica(
    const char codMascota[],
    const char codVeterinario[],
    const char motivo[],
    const char diagnostico[],
    RecetaMedica receta,
    const char observaciones[]
);

#endif