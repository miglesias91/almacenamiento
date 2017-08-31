#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

// wrapper rocksdb
#include <WrapperRocksDB/include/EstadoDB.h>
#include <WrapperRocksDB/include/WrapperRocksDB.h>

using namespace almacenamiento;

AdministradorAlmacenamientoLocal::AdministradorAlmacenamientoLocal(std::string directorio)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir(directorio);
}

AdministradorAlmacenamientoLocal::~AdministradorAlmacenamientoLocal()
{
	almacenamiento::WrapperRocksDB::RocksDB::cerrar();
}

// GETTERS

// SETTERS

// METODOS

bool AdministradorAlmacenamientoLocal::almacenar(IAlmacenableClaveValor* valor_a_almacenar)
{
	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::almacenar(valor_a_almacenar);

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(std::string clave_a_recuperar, IAlmacenableClaveValor* valor_recuperado)
{
	return true;
}

bool AdministradorAlmacenamientoLocal::modificar(std::string clave_a_modificar, IAlmacenableClaveValor* valor_modificado)
{
	return true;
}

bool AdministradorAlmacenamientoLocal::eliminar(std::string clave_a_eliminar)
{
	return true;
}

// CONSULTA

bool AdministradorAlmacenamientoLocal::existe(std::string clave_a_chequear)
{
	return true;
}

// METODOS INTERNOS

