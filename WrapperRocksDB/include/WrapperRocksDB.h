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

		static EstadoDB abrir(std::string directorio);

		static EstadoDB abrirConColumnas(std::string directorio);

		static EstadoDB abrirConFamilias(std::string directorio, std::vector<rocksdb::ColumnFamilyDescriptor> descriptores_columnas);

		static EstadoDB cerrar();

		// GETTERS

		// SETTERS

		// METODOS

		static EstadoDB almacenar(std::string clave, std::string valor);

		static EstadoDB recuperar(std::string clave, std::string & valor_a_recuperar);

		static EstadoDB recuperarGrupoPrefijo(std::string prefijo, std::vector<std::pair<std::string, std::string>> & valores_a_recuperar);

		static EstadoDB eliminar(std::string clave);

		// CONSULTA

	private:
		// METODOS INTERNOS

		RocksDB();
		virtual ~RocksDB();

		static rocksdb::ColumnFamilyHandle* obtenerOCrearHandlerDeFamilia(std::string familia);

		static rocksdb::ColumnFamilyHandle* crearHandlerDeFamilia(std::string familia);

		static rocksdb::ColumnFamilyHandle* obtenerHandlerDeFamilia(std::string familia);

		static std::vector<rocksdb::ColumnFamilyDescriptor> obtenerDescriptoresDeFamilias(std::string directorio);

		static void completarMapaDeHandlers(std::vector<rocksdb::ColumnFamilyHandle*> handlers);
		// ATRIBUTOS

		static rocksdb::DB* db;
		static rocksdb::WriteOptions opciones_escritura;
		static rocksdb::ReadOptions opciones_lectura;

		static std::string directorio;

		static std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*> mapa_familia_columnas;
};
};
};

