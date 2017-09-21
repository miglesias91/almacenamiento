#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

// wrapper rocksdb
#include <WrapperRocksDB/include/EstadoDB.h>
#include <WrapperRocksDB/include/WrapperRocksDB.h>

using namespace almacenamiento;

AdministradorAlmacenamientoLocal::AdministradorAlmacenamientoLocal(std::string directorio)
{
}

AdministradorAlmacenamientoLocal::~AdministradorAlmacenamientoLocal()
{
}

// GETTERS

// SETTERS

// METODOS

bool AdministradorAlmacenamientoLocal::almacenar(IAlmacenableClaveValor* valor_a_almacenar)
{
	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::almacenar(valor_a_almacenar->getClaveConPrefijo(), valor_a_almacenar->getValor());

	WrapperRocksDB::RocksDB::cerrar();

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(IAlmacenableClaveValor* clave_valor_recuperado)
{
	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	std::string valor_recuperado = "";
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

	WrapperRocksDB::RocksDB::cerrar();

	clave_valor_recuperado->setValor(valor_recuperado);

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	WrapperRocksDB::EstadoDB estado;

	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	for (std::vector<IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
	{
		IAlmacenableClaveValor* clave_valor_recuperado = *it;
		std::string valor_recuperado = "";
		estado = WrapperRocksDB::RocksDB::recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

		clave_valor_recuperado->setValor(valor_recuperado);

		if (false == estado.ok())
		{
			WrapperRocksDB::RocksDB::cerrar();
			return estado.ok();
		}
	}

	WrapperRocksDB::RocksDB::cerrar();
	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	std::vector<std::pair<std::string, std::string>> claves_valores_recuperados;

	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperarGrupoPrefijo(prefijo_grupo, claves_valores_recuperados);

	if ( false == estado.ok())
	{
		WrapperRocksDB::RocksDB::cerrar();
		return estado.ok();
	}

	WrapperRocksDB::RocksDB::cerrar();

	for (std::vector<std::pair<std::string, std::string>>::iterator it = claves_valores_recuperados.begin(); it != claves_valores_recuperados.end(); it++)
	{
		std::string clave = (*it).first;
		clave.erase(clave.begin(), clave.begin() + ConfiguracionAlmacenamiento::prefijoTamanio()); // le borro el prefijo.

		std::string valor = (*it).second;
		valores_recuperados.push_back(new IAlmacenableClaveValor(clave, prefijo_grupo, valor));
	}

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::modificar(IAlmacenableClaveValor* nuevo_valor)
{
	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::almacenar(nuevo_valor->getClaveConPrefijo(), nuevo_valor->getValor());

	WrapperRocksDB::RocksDB::cerrar();

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::eliminar(IAlmacenableClaveValor* clave_a_eliminar)
{
	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::eliminar(clave_a_eliminar->getClaveConPrefijo());

	WrapperRocksDB::RocksDB::cerrar();
	
	return estado.ok();
}

// CONSULTA

bool AdministradorAlmacenamientoLocal::existe(IAlmacenableClaveValor* clave_a_chequear)
{
	WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	std::string valor_recuperado = "";
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperar(clave_a_chequear->getClaveConPrefijo(), valor_recuperado);

	WrapperRocksDB::RocksDB::cerrar();

	if (valor_recuperado.empty())
	{
		return false;
	}
	return true;
}

// METODOS INTERNOS

