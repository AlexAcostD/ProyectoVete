#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct Propietario {
    char dni [9];
    char nombres [50];
    char direccion [100];
    char telefono [15];
    char correo [50];
    };
struct Mascota {
    char codigo [10];
    char nombre [30];
    char especie [20];
    char raza [30];
    char sexo ;
    int edad ;
    float peso ;
    char color [20];
    char fechaNacimiento [11];
    char dniPropietario [9];
    };

struct Veterinario {
    char codigo [10];
    char nombres [50];
    };

struct RecetaMedica {
    char medicamento [50];
    char dosis [30];
    char frecuencia [50];
    int duracionDias ;
    char indicaciones [100];
    };
struct Consulta {
    char codigoMascota [10];
    char codigoVeterinario [10];
    char fechaAtencion [11];
    char motivo [100];
    char diagnostico [100];
    struct RecetaMedica receta ;
    char observaciones [150];
    };
struct ComprobantePago {
    char numeroComprobante [12];
    char fecha [11];
    char dniCliente [9];
    char detalleServicio [100];
    float montoTotal ;
    };

struct VacunaAplicada {
    char codigoMascota[10];
    char nombreVacuna[30];
    char fechaAplicacion[11];
};
#endif