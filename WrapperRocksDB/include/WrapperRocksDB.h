/// IAlmacenableClaveValor.h
/// 2017-04-15

#pragma once

// rocksdb
#include <rocksdb/db.h>

// WrapperRocksDB
#include <WrapperRocksDB/include/EstadoDB.h>

namespace almacenamiento
{

namespace WrapperRocksDB
{

class RocksDB
{
	public:

        RocksDB();
        virtual ~RocksDB();

		EstadoDB abrir(std::string directorio);

		EstadoDB cerrar();

        EstadoDB borrar();

		// GETTERS

		// SETTERS

		// METODOS

		EstadoDB almacenar(std::string clave, std::string valor);

		EstadoDB recuperar(std::string clave, std::string & valor_a_recuperar);

		EstadoDB recuperarGrupoPrefijo(std::string prefijo, std::vector<std::pair<std::string, std::string>> & valores_a_recuperar);

		EstadoDB eliminar(std::string clave);

		// CONSULTA

	private:
		// METODOS INTERNOS

		// ATRIBUTOS

		//static rocksdb::DB* db;
        //static rocksdb::WriteOptions opciones_escritura;
        //static rocksdb::ReadOptions opciones_lectura;
        //static std::string directorio;
        rocksdb::DB* db;
        rocksdb::WriteOptions opciones_escritura;
        rocksdb::ReadOptions opciones_lectura;
        std::string directorio;

};
};
};

