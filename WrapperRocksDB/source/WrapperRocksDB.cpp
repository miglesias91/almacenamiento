#include <WrapperRocksDB/include/WrapperRocksDB.h>

using namespace almacenamiento::WrapperRocksDB;

// rocksdb
#include <rocksdb/slice_transform.h>

rocksdb::DB* RocksDB::db = NULL;
rocksdb::WriteOptions RocksDB::opciones_escritura;
rocksdb::ReadOptions RocksDB::opciones_lectura;

EstadoDB RocksDB::abrir(std::string directorio)
{
	rocksdb::Env* env = rocksdb::Env::Default();
	env->SetBackgroundThreads(2, rocksdb::Env::LOW);
	env->SetBackgroundThreads(1, rocksdb::Env::HIGH);
	
	rocksdb::Options options;
	options.env = env;
	options.IncreaseParallelism();
	options.create_if_missing = true;
	options.prefix_extractor.reset(rocksdb::NewFixedPrefixTransform(3));

	rocksdb::Status estado_rocksdb = rocksdb::DB::Open(options, directorio, &db);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::cerrar()
{
	if (NULL == db)
	{
		return rocksdb::Status::Corruption("No se creo ninguna instancia de la bd.");
	}

	delete db;
	db = NULL;

	EstadoDB estado(rocksdb::Status::OK());
	return estado;
}

// GETTERS

// SETTERS

// METODOS

EstadoDB RocksDB::almacenar(std::string clave, std::string valor)
{
	rocksdb::Slice slice_clave(clave);
	rocksdb::Slice slice_valor(valor);

	rocksdb::Status estado_rocksdb = db->Put(opciones_escritura, slice_clave, slice_valor);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::recuperar(std::string string_clave, std::string & valor_a_recuperar)
{
	rocksdb::Slice clave(string_clave);
	rocksdb::PinnableSlice valor(&valor_a_recuperar);

	rocksdb::Status estado_rocksdb = db->Get(opciones_lectura, db->DefaultColumnFamily(), clave, &valor);

	EstadoDB estado(estado_rocksdb);
	return estado;
}

EstadoDB RocksDB::recuperarGrupoPrefijo(std::string prefijo, std::vector<std::pair<std::string, std::string>> & valores_a_recuperar)
{
	rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
	for (it->Seek(prefijo); it->Valid() && it->key().starts_with(prefijo); it->Next())
	{
		std::pair<std::string, std::string> clave_valor = std::make_pair(it->key().ToString(), it->value().ToString());
		valores_a_recuperar.push_back(clave_valor);
	}

	EstadoDB estado(it->status());
	delete it;
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
