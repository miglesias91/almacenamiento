#include <WrapperRocksDB/include/EstadoDB.h>

using namespace almacenamiento::WrapperRocksDB;

EstadoDB::EstadoDB()
{
}

EstadoDB::EstadoDB(rocksdb::Status estado_rocksdb) : estado_rocksdb(estado_rocksdb)
{
}

EstadoDB::~EstadoDB()
{
}

// GETTERS

// SETTERS

// METODOS

std::string EstadoDB::mensaje()
{
	return this->estado_rocksdb.ToString();
}

// CONSULTA

bool EstadoDB::ok()
{
	return this->estado_rocksdb.ok();
}

// METODOS INTERNOS