#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#include "propietarios.h"
#include "mascotas.h"
#include "consultas.h"
#include "vacunas.h"
#include "facturacion.h"
using namespace std;

int main()
{
    Propietario p;

    int resultado = registrarPropietario(
        &p,
        "12345678",
        "Juan Perez",
        "Av Peru 123",
        "999888777",
        "juan@gmail.com"
    );

    if(resultado)
    {
        cout << "Propietario registrado correctamente\n";
    }
    else
    {
        cout << "Error al registrar propietario\n";
    }

    Mascota m;

    int resultadoMascota = registrarMascota(
        &m,
        "M001",
        "Firulais",
        "Perro",
        "Labrador",
        'M',
        3,
        15.5,
        "Marron",
        "10/05/2023",
        "12345678"
    );

    if(resultadoMascota)
    {
        cout << "Mascota registrada correctamente\n";
    }
    else
    {
        cout << "Error al registrar mascota\n";
    }

    RecetaMedica receta;

strcpy(receta.medicamento, "Amoxicilina");
strcpy(receta.dosis, "1 tableta");
strcpy(receta.frecuencia, "Cada 12 horas");

receta.duracionDias = 7;

strcpy(
    receta.indicaciones,
    "Despues de las comidas"
);

Consulta consulta =
    registrarConsultaMedica(
        "M001",
        "V001",
        "Fiebre y decaimiento",
        "Infeccion respiratoria",
        receta,
        "Control en una semana"
    );

cout << "\nConsulta registrada\n";
cout << consulta.codigoMascota << endl;
cout << consulta.fechaAtencion << endl;
cout << consulta.diagnostico << endl;


int resultadoVacuna =
    aplicarVacuna(
        "M001",
        "Antirrabica",
        3,
        15.5
    );

if(resultadoVacuna)
{
    cout << "Vacuna aplicada correctamente\n";
}
else
{
    cout << "No se pudo aplicar la vacuna\n";
}


ComprobantePago comprobante =
    emitirComprobante(
        "B001-000001",
        "12345678",
        "Consulta medica + vacuna",
        85.50
    );
if(comprobante.montoTotal > 0)
{
    cout << "\nComprobante emitido\n";
    cout << "Numero: "
         << comprobante.numeroComprobante
         << endl;

    cout << "Fecha: "
         << comprobante.fecha
         << endl;

    cout << "Cliente: "
         << comprobante.dniCliente
         << endl;

    cout << "Monto: S/ "
         << comprobante.montoTotal
         << endl;
}
else
{
    cout << "\nError al emitir comprobante\n";
}
    return 0;
}