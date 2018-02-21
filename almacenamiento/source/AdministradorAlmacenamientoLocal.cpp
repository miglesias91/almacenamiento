#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

// stl
#include <experimental/filesystem>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>

using namespace almacenamiento;

AdministradorAlmacenamientoLocal::AdministradorAlmacenamientoLocal(ConfiguracionAlmacenamiento * configuracion) : IAdministradorAlmacenamiento(configuracion)
{
    this->directorio = configuracion->pathDB();
}

AdministradorAlmacenamientoLocal::~AdministradorAlmacenamientoLocal()
{
}

// GETTERS

// SETTERS

// METODOS

bool AdministradorAlmacenamientoLocal::abrir()
{
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.abrir(this->directorio);

    if (estado.ok())
    {
        abierto = true;
    }
    else
    {
        abierto = false;
    }

    return estado.ok();
}

bool AdministradorAlmacenamientoLocal::cerrar()
{
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.cerrar();

    if (estado.ok())
    {
        abierto = false;
    }
    else
    {
        abierto = true;
    }

    return estado.ok();
}

bool AdministradorAlmacenamientoLocal::borrar()
{
    return rocksdb_instancia.borrar();
}

bool AdministradorAlmacenamientoLocal::almacenar(IAlmacenableClaveValor* valor_a_almacenar)
{
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.almacenar(valor_a_almacenar->getClaveConPrefijo(), valor_a_almacenar->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(IAlmacenableClaveValor* clave_valor_recuperado)
{
	std::string valor_recuperado = "";

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

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

        estado = rocksdb_instancia.recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

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

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperarGrupoPrefijo(prefijo_grupo, claves_valores_recuperados);

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
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.almacenar(nuevo_valor->getClaveConPrefijo(), nuevo_valor->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::eliminar(IAlmacenableClaveValor* clave_a_eliminar)
{
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.eliminar(clave_a_eliminar->getClaveConPrefijo());
	
	return estado.ok();
}

// CONSULTA

bool AdministradorAlmacenamientoLocal::existe(IAlmacenableClaveValor* clave_a_chequear)
{
	std::string valor_recuperado = "";

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperar(clave_a_chequear->getClaveConPrefijo(), valor_recuperado);

	if (valor_recuperado.empty())
	{
		return false;
	}
	return true;
}

bool AdministradorAlmacenamientoLocal::bdAbierta()
{
    return abierto;
}

// METODOS INTERNOS

