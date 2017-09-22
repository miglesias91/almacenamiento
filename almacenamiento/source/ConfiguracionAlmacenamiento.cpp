#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

using namespace almacenamiento;

// stl
#include <fstream>
#include <sstream>

// rapidjson
#include <rapidjson/document.h>

std::string ConfiguracionAlmacenamiento::path_db;
bool ConfiguracionAlmacenamiento::almacenamiento_local;
bool ConfiguracionAlmacenamiento::almacenamiento_distribuido;

void ConfiguracionAlmacenamiento::leerConfiguracion(std::string path_archivo_configuracion)
{
	std::ifstream archivo(path_archivo_configuracion);

	if (false == archivo.good())
	{
		throw - 1;
	}

	std::ostringstream sstream;
	sstream << archivo.rdbuf();
	const std::string string_config(sstream.str());

	rapidjson::Document config_json;
	config_json.Parse(string_config.c_str());

	path_db = config_json[ConfiguracionAlmacenamiento::tagPathDB().c_str()].GetString();
	almacenamiento_local = config_json[ConfiguracionAlmacenamiento::tagAlmacenamientoLocal().c_str()].GetBool();
	almacenamiento_distribuido = config_json[ConfiguracionAlmacenamiento::tagAlmacenamientoDistribuido().c_str()].GetBool();
}

bool ConfiguracionAlmacenamiento::almacenamientoLocal()
{
	return almacenamiento_local;
}

bool ConfiguracionAlmacenamiento::almacenamientoDistribuido()
{
	return almacenamiento_distribuido;
}

std::string ConfiguracionAlmacenamiento::pathDB()
{
	return path_db;
}

std::string ConfiguracionAlmacenamiento::tagPathDB()
{
	return "path_db";
}

std::string ConfiguracionAlmacenamiento::tagAlmacenamientoLocal()
{
	return "almacenamiento_local";
}

std::string ConfiguracionAlmacenamiento::tagAlmacenamientoDistribuido()
{
	return "almacenamiento_distribuido";
}

ConfiguracionAlmacenamiento::ConfiguracionAlmacenamiento()
{
}

ConfiguracionAlmacenamiento::~ConfiguracionAlmacenamiento()
{
}
