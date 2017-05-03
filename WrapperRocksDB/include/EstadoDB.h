/// EstadoDB.h
/// 2017-04-15

#pragma once

// rocksdb
#include <rocksdb/status.h>

namespace almacenamiento
{

namespace WrapperRocksDB
{

class EstadoDB
{
	public:
		EstadoDB();
		
		EstadoDB(rocksdb::Status estado);
		
		virtual ~EstadoDB();

		// GETTERS

		// SETTERS

		// METODOS

		std::string mensaje();

		// CONSULTA

		bool ok();

	private:
		// METODOS INTERNOS

		// ATRIBUTOS
		rocksdb::Status estado_rocksdb;
};
};
};