#include <almacenamiento/include/AlmacenamientoNoInicializado.h>

using namespace almacenamiento::excepciones;

AlmacenamientoNoInicializado::AlmacenamientoNoInicializado(uintmax_t handler) : Excepcion("almacenamiento{ handler = '" + std::to_string(handler) + "'}: no inicializado.")
{
}

AlmacenamientoNoInicializado::AlmacenamientoNoInicializado(std::string path_db) : Excepcion("almacenamiento{ path_db = '" + path_db + "'}: no inicializado.")
{
}

AlmacenamientoNoInicializado::~AlmacenamientoNoInicializado()
{
}
