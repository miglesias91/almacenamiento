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
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::almacenar(valor_a_almacenar->getClaveConPrefijo(), valor_a_almacenar->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(IAlmacenableClaveValor* clave_valor_recuperado)
{
	std::string valor_recuperado = "";
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

	clave_valor_recuperado->setValor(valor_recuperado);

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	WrapperRocksDB::EstadoDB estado;

	for (std::vector<IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
	{
		IAlmacenableClaveValor* clave_valor_recuperado = *it;
		std::string valor_recuperado = "";
		estado = WrapperRocksDB::RocksDB::recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

		clave_valor_recuperado->setValor(valor_recuperado);

		if (false == estado.ok())
		{
			return estado.ok();
		}
	}

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	std::vector<std::pair<std::string, std::string>> claves_valores_recuperados;

	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperarGrupoPrefijo(prefijo_grupo, claves_valores_recuperados);

	if ( false == estado.ok())
	{
		return estado.ok();
	}

	for (std::vector<std::pair<std::string, std::string>>::iterator it = claves_valores_recuperados.begin(); it != claves_valores_recuperados.end(); it++)
	{
		std::string clave = (*it).first;
		clave.erase(clave.begin(), clave.begin() + prefijo_grupo.size()); // le borro el prefijo.

		std::string valor = (*it).second;
		valores_recuperados.push_back(new IAlmacenableClaveValor(clave, prefijo_grupo, valor));
	}

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::modificar(IAlmacenableClaveValor* nuevo_valor)
{
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::almacenar(nuevo_valor->getClaveConPrefijo(), nuevo_valor->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::eliminar(IAlmacenableClaveValor* clave_a_eliminar)
{
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::eliminar(clave_a_eliminar->getClaveConPrefijo());
	
	return estado.ok();
}

// CONSULTA

bool AdministradorAlmacenamientoLocal::existe(IAlmacenableClaveValor* clave_a_chequear)
{
	std::string valor_recuperado = "";
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::recuperar(clave_a_chequear->getClaveConPrefijo(), valor_recuperado);

	if (valor_recuperado.empty())
	{
		return false;
	}
	return true;
}

bool AdministradorAlmacenamientoLocal::abrir()
{
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::abrir(ConfiguracionAlmacenamiento::pathDB());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::cerrar()
{
	WrapperRocksDB::EstadoDB estado = WrapperRocksDB::RocksDB::cerrar();
	
	return estado.ok();
}

// METODOS INTERNOS

