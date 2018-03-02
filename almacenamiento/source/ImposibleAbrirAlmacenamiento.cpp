#include <almacenamiento/include/ImposibleAbrirAlmacenamiento.h>

using namespace almacenamiento::excepciones;

ImposibleAbrirAlmacenamiento::ImposibleAbrirAlmacenamiento(std::string nombre_db) : Excepcion("almacenamiento{ path_db = '" + nombre_db + "'}: imposible abrir.")
{
}

ImposibleAbrirAlmacenamiento::~ImposibleAbrirAlmacenamiento()
{
}
