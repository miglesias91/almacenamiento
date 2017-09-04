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

	static bool prefijoHabilitado();
	static std::string prefijoConcepto();
	static std::string prefijoTermino();
	static std::string prefijoConsulta();
	static std::string prefijoGrafico();
	static std::string prefijoSeccion();

	// TAGS

	static std::string tagPathDB();
	static std::string tagAlmacenamientoLocal();
	static std::string tagAlmacenamientoDistribuido();

	static std::string tagPrefijoHabilitado();
	static std::string tagPrefijoConcepto();
	static std::string tagPrefijoTermino();
	static std::string tagPrefijoConsulta();
	static std::string tagPrefijoGrafico();
	static std::string tagPrefijoSeccion();

private:
	ConfiguracionAlmacenamiento();
	virtual ~ConfiguracionAlmacenamiento();

	static std::string path_db;
	static bool almacenamiento_local;
	static bool almacenamiento_distribuido;

	static bool prefijo_habilitado;
	static std::string prefijo_concepto;
	static std::string prefijo_termino;
	static std::string prefijo_consulta;
	static std::string prefijo_grafico;
	static std::string prefijo_seccion;
};
};
