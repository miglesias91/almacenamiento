#pragma once

// utiles
#include <utiles/include/Excepcion.h>

namespace almacenamiento
{
namespace excepciones
{

class AlmacenamientoIniciadoPreviamente : public herramientas::utiles::excepciones::Excepcion
{
public:
    AlmacenamientoIniciadoPreviamente(std::string nombre_db = "");
    virtual ~AlmacenamientoIniciadoPreviamente();
};

};
};

