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

bool ConfiguracionAlmacenamiento::prefijo_habilitado;
std::string ConfiguracionAlmacenamiento::prefijo_concepto;
std::string ConfiguracionAlmacenamiento::prefijo_termino;
std::string ConfiguracionAlmacenamiento::prefijo_consulta;
std::string ConfiguracionAlmacenamiento::prefijo_grafico;
std::string ConfiguracionAlmacenamiento::prefijo_seccion;

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

	prefijo_habilitado = config_json[ConfiguracionAlmacenamiento::tagPrefijoHabilitado().c_str()].GetBool();
	prefijo_concepto = config_json[ConfiguracionAlmacenamiento::tagPrefijoConcepto().c_str()].GetString();
	prefijo_termino = config_json[ConfiguracionAlmacenamiento::tagPrefijoTermino().c_str()].GetString();
	prefijo_consulta = config_json[ConfiguracionAlmacenamiento::tagPrefijoConsulta().c_str()].GetString();
	prefijo_grafico = config_json[ConfiguracionAlmacenamiento::tagPrefijoGrafico().c_str()].GetString();
	prefijo_seccion = config_json[ConfiguracionAlmacenamiento::tagPrefijoSeccion().c_str()].GetString();
}

bool ConfiguracionAlmacenamiento::almacenamientoLocal()
{
	return almacenamiento_local;
}

bool ConfiguracionAlmacenamiento::almacenamientoDistribuido()
{
	return almacenamiento_distribuido;
}

bool ConfiguracionAlmacenamiento::prefijoHabilitado()
{
	return prefijo_habilitado;
}

std::string ConfiguracionAlmacenamiento::prefijoConcepto()
{
	return prefijo_concepto;
}

std::string ConfiguracionAlmacenamiento::prefijoTermino()
{
	return prefijo_termino;
}

std::string ConfiguracionAlmacenamiento::prefijoConsulta()
{
	return prefijo_consulta;
}

std::string ConfiguracionAlmacenamiento::prefijoGrafico()
{
	return prefijo_grafico;
}

std::string ConfiguracionAlmacenamiento::prefijoSeccion()
{
	return prefijo_seccion;
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

std::string ConfiguracionAlmacenamiento::tagPrefijoHabilitado()
{
	return "prefijo_habilitado";
}

std::string almacenamiento::ConfiguracionAlmacenamiento::tagPrefijoConcepto()
{
	return "prefijo_concepto";
}

std::string almacenamiento::ConfiguracionAlmacenamiento::tagPrefijoTermino()
{
	return "prefijo_termino";
}

std::string almacenamiento::ConfiguracionAlmacenamiento::tagPrefijoConsulta()
{
	return "prefijo_consulta";
}

std::string almacenamiento::ConfiguracionAlmacenamiento::tagPrefijoGrafico()
{
	return "prefijo_grafico";
}

std::string almacenamiento::ConfiguracionAlmacenamiento::tagPrefijoSeccion()
{
	return "prefijo_seccion";
}

ConfiguracionAlmacenamiento::ConfiguracionAlmacenamiento()
{
}

ConfiguracionAlmacenamiento::~ConfiguracionAlmacenamiento()
{
}
