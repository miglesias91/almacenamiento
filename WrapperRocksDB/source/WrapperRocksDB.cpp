#include <WrapperRocksDB/include/WrapperRocksDB.h>

using namespace almacenamiento::WrapperRocksDB;

rocksdb::DB* RocksDB::db;
rocksdb::WriteOptions RocksDB::opciones_escritura;
rocksdb::ReadOptions RocksDB::opciones_lectura;
std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*> RocksDB::mapa_familia_columnas;

EstadoDB RocksDB::abrir(std::string directorio)
{
	rocksdb::Options options;
	options.create_if_missing = true;

	rocksdb::Status estado_rocksdb = rocksdb::DB::Open(options, directorio, &db);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::abrirConColumnas(std::string directorio)
{
	rocksdb::Options options;
	options.create_if_missing = true;

	// la DB tiene que abrirse con la lista de handler de columnas que estan creados en la BD. para eso uso la función: DB::ListColumnFamilies.
	std::vector<rocksdb::ColumnFamilyDescriptor> descriptores_columnas = obtenerDescriptoresDeFamilias(directorio);

	rocksdb::Status estado_rocksdb;
	if (0 == descriptores_columnas.size())
	{
		estado_rocksdb = rocksdb::DB::Open(options, directorio, &db);
	}
	else
	{
		return abrirConFamilias(directorio, descriptores_columnas);
	}

	EstadoDB estado(estado_rocksdb);
	return estado;
}


EstadoDB RocksDB::abrirConFamilias(std::string directorio, std::vector<rocksdb::ColumnFamilyDescriptor> descriptores_columnas)
{
	rocksdb::Options options;
	options.create_if_missing = true;

	// abro la DB con las columnas ya creadas.
	std::vector<rocksdb::ColumnFamilyHandle*> handlers;
	rocksdb::Status estado_rocksdb = rocksdb::DB::Open(options, directorio, descriptores_columnas, &handlers, &db);

	// completo el mapa de handlers.
	completarMapaDeHandlers(handlers);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

void RocksDB::cerrar()
{
	for (std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*>::iterator it = mapa_familia_columnas.begin(); it != mapa_familia_columnas.end(); it++)
	{
		rocksdb::ColumnFamilyHandle* familia = it->second;

		db->DropColumnFamily(familia);
		delete familia;
	}
	delete db;
}

// GETTERS

// SETTERS

// METODOS

EstadoDB RocksDB::almacenar(almacenamiento::IAlmacenableClaveValor* valor_a_almacenar)
{
	std::string string_clave = valor_a_almacenar->getClave();
	std::string string_valor = valor_a_almacenar->getValor();

	rocksdb::Slice clave(string_clave);
	rocksdb::Slice valor(string_valor);

	rocksdb::Status estado_rocksdb = db->Put(opciones_escritura, clave, valor);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::almacenar(almacenamiento::IAlmacenableClaveValor* valor_a_almacenar, std::string familia)
{
	std::string string_clave = valor_a_almacenar->getClave();
	std::string string_valor = valor_a_almacenar->getValor();

	rocksdb::Slice clave(string_clave);
	rocksdb::Slice valor(string_valor);

	rocksdb::ColumnFamilyHandle* handler_columna = obtenerOCrearHandlerDeFamilia(familia);

	rocksdb::Status estado_rocksdb = db->Put(opciones_escritura, handler_columna, clave, valor);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::recuperar(std::string string_clave, almacenamiento::IAlmacenableClaveValor* valor_a_recuperar)
{
	rocksdb::Slice clave(string_clave);

	std::string valor_recuperado;
	rocksdb::Status estado_rocksdb = db->Get(opciones_lectura, clave, &valor_recuperado);

	valor_a_recuperar->setClave(string_clave);
	valor_a_recuperar->setValor(valor_recuperado);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::recuperar(std::string string_clave, almacenamiento::IAlmacenableClaveValor* valor_a_recuperar, std::string familia)
{
	rocksdb::Slice clave(string_clave);

	rocksdb::ColumnFamilyHandle* handler_columna = obtenerHandlerDeFamilia(familia);

	std::string valor_recuperado;
	rocksdb::Status estado_rocksdb = db->Get(opciones_lectura, handler_columna, clave, &valor_recuperado);

	valor_a_recuperar->setClave(string_clave);
	valor_a_recuperar->setValor(valor_recuperado);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::eliminar(std::string clave)
{
	rocksdb::Slice clave_a_eliminar(clave);

	rocksdb::Status estado_rocksdb = db->Delete(opciones_escritura, clave_a_eliminar);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

// CONSULTA

// METODOS INTERNOS

RocksDB::RocksDB()
{
}

RocksDB::~RocksDB()
{
}

rocksdb::ColumnFamilyHandle* RocksDB::obtenerOCrearHandlerDeFamilia(std::string familia)
{
	rocksdb::ColumnFamilyHandle* handler = obtenerHandlerDeFamilia(familia);
	if ( NULL == handler )
	{
		handler = crearHandlerDeFamilia(familia);
	}

	return handler;
}

rocksdb::ColumnFamilyHandle* RocksDB::obtenerHandlerDeFamilia(std::string familia)
{
	std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*>::const_iterator iterador = mapa_familia_columnas.find(familia);
	if (mapa_familia_columnas.end() == iterador)
	{
		return NULL;
	}
	return iterador->second;
}

rocksdb::ColumnFamilyHandle* RocksDB::crearHandlerDeFamilia(std::string familia)
{
	rocksdb::ColumnFamilyHandle* handler_nuevo = NULL;
	rocksdb::Status estado = db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), familia, &handler_nuevo);
	if ( estado.ok() )
	{
		mapa_familia_columnas.insert(std::make_pair(familia, handler_nuevo));
	}
	else
	{
		throw std::exception(estado.ToString().c_str());
	}

	return handler_nuevo;
}

std::vector<rocksdb::ColumnFamilyDescriptor> RocksDB::obtenerDescriptoresDeFamilias(std::string directorio)
{
	std::vector<std::string> nombres_columnas;
	rocksdb::DB::ListColumnFamilies(rocksdb::DBOptions(), directorio, &nombres_columnas);

	std::vector<rocksdb::ColumnFamilyDescriptor> descriptores_columnas;
	for (std::vector<std::string>::iterator it = nombres_columnas.begin(); it != nombres_columnas.end(); it++)
	{
		rocksdb::ColumnFamilyDescriptor descriptor;
		descriptor.name = (*it);
		descriptor.options = rocksdb::ColumnFamilyOptions();
		descriptores_columnas.push_back(descriptor);
	}

	return descriptores_columnas;
}

void RocksDB::completarMapaDeHandlers(std::vector<rocksdb::ColumnFamilyHandle*> handlers)
{
	for (std::vector<rocksdb::ColumnFamilyHandle*>::iterator it = handlers.begin(); it != handlers.end(); it++)
	{
		mapa_familia_columnas.insert(std::make_pair((*it)->GetName(), (*it)));
	}
}
