#include <almacenamiento/include/AlmacenamientoIniciadoPreviamente.h>

using namespace almacenamiento::excepciones;

AlmacenamientoIniciadoPreviamente::AlmacenamientoIniciadoPreviamente(std::string nombre_db) : Excepcion("almacenamiento{ path_db = '" + nombre_db + "'} ya fue iniciado.")
{
}

AlmacenamientoIniciadoPreviamente::~AlmacenamientoIniciadoPreviamente()
{
}
