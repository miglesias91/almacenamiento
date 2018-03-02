#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace almacenamiento
{
namespace excepciones
{

class AlmacenamientoNoInicializado : public herramientas::utiles::excepciones::Excepcion
{
public:
    AlmacenamientoNoInicializado(unsigned long long int handler = 0);
    AlmacenamientoNoInicializado(std::string path_db = "");
    virtual ~AlmacenamientoNoInicializado();
};

};
};

