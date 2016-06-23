#include "Zip_File_Missing.hpp"

#define InicializarVariables unsigned long long Buffer = 0; unsigned long long Posicion = 22;unsigned int N = 0;unsigned char Tamanyo_Archivo; char Leer[256] = {0};

unsigned int Zip_File_Mising::ListarArchivos(string &Resultado)
{
    // Empezamos la parafernaria. Lo primero es verificar que el archivo de Lectura esta abierto

    if (ComprobarArchivoNoAbierto(Lectura))
        throw Excepcion("No hay ningun fichero abierto",ARCHIVO_NO_ABIERTO);

    // Lo segundo, es declarar las variables de control

    Variable_Progueso
    Variable_Tamanyo(Tamanyo_Nombre)

    MoverA(Lectura,22)

    InicializarVariables

    do
    {
        Read(Lectura,Leer,1)
        Posicion++;
        // 41
        if (ComprobarFirmaNombre(Leer))
        {

            Posicion += 41;

            MoverA(Lectura,Posicion)
            Read(Lectura,Leer,1)

            if ((*Leer != 0 && Modo == 0) || (*Leer == 0 && Modo == 1))
            {
                char Buffers = *Leer;
                cout<<Posicion<<endl;

                Archivo.push_back(Posicion);
                stringstream Buff; // Variable auxiliar
                Buff<<N+1<<": "; // Para pasar de numero a char
                string bufff = Buff.str();
                Resultado += bufff; // Escribimos el numero

                N++;

                Resultado += Buffers;

                do
                {
                    Read(Lectura,Leer,1)
                    Resultado += *Leer;
                }while(*Leer != 10);

                Resultado += '\n';

                Posicion = ObtenerPosicion(Lectura)
            }

        }


    }while(Posicion < Tamanyo);

    MoverA(Lectura,0)

    return N; // Devolvemos el string con los ficheros

}
bool Zip_File_Mising::ComprobarFirmaNombre(const char* Leer)
{
    static short Aciertos = 0;

    if (Aciertos == 4)
    {
        Aciertos = 0;
        if (*Leer == 31)
            return true;

    }
    if (Aciertos == 3)
    {
        if (*Leer == 2)
            Aciertos++;
        else
            Aciertos = 0;
    }

    else
    if (Aciertos == 2)
            if (*Leer == 1)
						Aciertos++;
            else
						Aciertos = 0;
    else
    if (Aciertos == 1)
            if (*Leer == 'K')
						Aciertos++;
            else
						Aciertos = 0;

    else
    if (*Leer == 'P' && Aciertos == 0)
                Aciertos++;

    return false;
}

void Zip_File_Mising::Generar(vector<unsigned int> Numero)
{
    if (Archivo.size() == 0)
        throw Excepcion("Error, no se ha creado ninguna lista de archivos o no existen archivos.",SIN_ARCHIVOS);

    AbrirArchivo(Escritura,Nombre.c_str(),Modo_Escritura)

    if (ComprobarArchivoNoAbierto(Escritura))
        throw Excepcion("Error al crear el fichero",ERROR_DE_APERTURA);

    Variable_Progueso

    CerrarArchivo(Lectura)

    short Porcentaje = 0;
    unsigned long long Posicion = 0;
    unsigned long long Contador_Progueso = 0;
    unsigned long long Contador_Porcentaje = 0;
    unsigned long long Aumento_Porcentaje = Tamanyo/100;
    unsigned long long Tamanyo_Lectura;
    unsigned int j = 0;

    char Leer;

    if (Modo == 0)
    {
        Leer = 0;
    }
    else
        Leer = 't';

    OrdenarVector(Numero);

    do
    {
        MoverAEsc(Escritura,Archivo[Numero[j]])
        Write(Escritura,&Leer,1)

        j++;
    }
    while(j < Numero.size());

    CerrarArchivo(Escritura)

}
/*bool Zip_File_Mising::ComprobarFirmaNombre(const char Leer)
{
    static short Aciertos = 0;

    if (Aciertos == 2)
    {
        Aciertos = 0;

        if (Leer == 0)
            return true;
    }

    if (Leer == 0)
        Aciertos++;
    else
        Aciertos = 0;
    return false;
}
unsigned int Zip_File_Mising::GuardarDatosArchivo(unsigned long long Posicion,unsigned long long Buffer,string &Resultado,unsigned int &N)
{
    return 0;
}
*/
