/// AdministradorAlmacenamientoLocal.h
/// 02-05-2017

#pragma once

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

// wrapper rocksdb
#include <WrapperRocksDB/include/EstadoDB.h>
#include <WrapperRocksDB/include/WrapperRocksDB.h>

namespace almacenamiento
{

class AdministradorAlmacenamientoLocal : public IAdministradorAlmacenamiento
{
	public:
		AdministradorAlmacenamientoLocal(std::string directorio = "");
		virtual ~AdministradorAlmacenamientoLocal();

		// GETTERS

		// SETTERS

		// METODOS

		virtual bool abrir();

		virtual bool cerrar();

        virtual bool borrar();

		virtual bool almacenar(IAlmacenableClaveValor* valor_a_almacenar);

		virtual bool recuperar(IAlmacenableClaveValor* valor_recuperado);

		virtual bool recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados);

		virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados);

		virtual bool modificar(IAlmacenableClaveValor* nuevo_valor);

		virtual bool eliminar(IAlmacenableClaveValor* clave_a_eliminar);

		// CONSULTA

		virtual bool existe(IAlmacenableClaveValor* clave_a_chequear);

        virtual bool bdAbierta();

	private:
		// METODOS INTERNOS

		// ATRIBUTOS
        WrapperRocksDB::RocksDB rocksdb_instancia;

        std::string directorio;

        bool abierto;
};
};