#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#include "consultas.h"

using namespace std;

Consulta registrarConsultaMedica(
    const char codMascota[],
    const char codVeterinario[],
    const char motivo[],
    const char diagnostico[],
    RecetaMedica receta,
    const char observaciones[]
)
{
    Consulta consulta;

    strcpy(consulta.codigoMascota, codMascota);

    strcpy(
        consulta.codigoVeterinario,
        codVeterinario
    );

    strcpy(consulta.motivo, motivo);

    strcpy(
        consulta.diagnostico,
        diagnostico
    );

    consulta.receta = receta;

    strcpy(
        consulta.observaciones,
        observaciones
    );

    // Fecha actual del sistema

    time_t t = time(NULL);

    tm *fechaActual = localtime(&t);

    sprintf(
        consulta.fechaAtencion,
        "%02d/%02d/%04d",
        fechaActual->tm_mday,
        fechaActual->tm_mon + 1,
        fechaActual->tm_year + 1900
    );

    // Guardar en archivo

    ofstream archivo(
        "consultas.dat",
        ios::binary | ios::app
    );

    if (archivo)
    {
        archivo.write(
            reinterpret_cast<char*>(&consulta),
            sizeof(Consulta)
        );

        archivo.close();
    }

    return consulta;
}