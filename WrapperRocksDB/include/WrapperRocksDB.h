/// IAlmacenableClaveValor.h
/// 2017-04-15

#pragma once

// rocksdb
#include <rocksdb/db.h>
#include <rocksdb/utilities/checkpoint.h>

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

        EstadoDB abrir(const std::string & directorio, bool solo_lectura = false);

        EstadoDB cerrar();

        bool borrar();

        // GETTERS

        // SETTERS

        // METODOS

        EstadoDB checkpoint(const std::string & path);

        EstadoDB almacenar(std::string clave, std::string valor);

        EstadoDB recuperar(std::string clave, std::string & valor_a_recuperar);

        EstadoDB recuperarGrupoPrefijo(std::string prefijo, std::vector<std::pair<std::string, std::string>> & valores_a_recuperar);

        EstadoDB eliminar(std::string clave);

        // CONSULTA

        bool estaAbierta();

	private:
        // METODOS INTERNOS

        // ATRIBUTOS

        rocksdb::DB* db;
        rocksdb::Checkpoint * checkpoint_db;
        rocksdb::WriteOptions opciones_escritura;
        rocksdb::ReadOptions opciones_lectura;
        std::string directorio;
        bool abierta;

};
};
};

