#pragma once

// stl
#include <string>

namespace almacenamiento
{
class ConfiguracionAlmacenamiento
{
public:

	static void leerConfiguracion(std::string path_archivo_configuracion);

	// CONFIGURACIONES

	static std::string pathDB();
	static bool almacenamientoLocal();
	static bool almacenamientoDistribuido();

	// TAGS

	static std::string tagPathDB();
	static std::string tagAlmacenamientoLocal();
	static std::string tagAlmacenamientoDistribuido();

private:
	ConfiguracionAlmacenamiento();
	virtual ~ConfiguracionAlmacenamiento();

	static std::string path_db;
	static bool almacenamiento_local;
	static bool almacenamiento_distribuido;
};
};
