// gtest
#include <gtest/gtest.h>

// Wrapper
#include <WrapperRocksDB/include/WrapperRocksDB.h>
#include <WrapperRocksDB/include/EstadoDB.h>

// almacenamiento
#include <almacenamiento/include/IAlmacenableClaveValor.h>

std::string directorio_bbdd_tmp = "";

class ObjetoClaveValor : public almacenamiento::IAlmacenableClaveValor
{
public:
	ObjetoClaveValor(std::string clave, std::string valor, std::string familia) : IAlmacenableClaveValor(clave, valor, familia) {}

	ObjetoClaveValor() {};

	virtual ~ObjetoClaveValor() {};
};

TEST(WrapperRocksDB, almacenarRecuperarEliminarCorrectamente)
{
	almacenamiento::IAlmacenableClaveValor* clave_valor_a_almacenar = new ObjetoClaveValor("id1", "crisis", "");

	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave_valor_a_almacenar);

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new ObjetoClaveValor();

	almacenamiento::WrapperRocksDB::RocksDB::recuperar("id1", clave_valor_a_recuperar);

	ASSERT_STREQ("id1", clave_valor_a_recuperar->getClave().c_str());
	ASSERT_STREQ("crisis", clave_valor_a_recuperar->getValor().c_str());

	almacenamiento::WrapperRocksDB::RocksDB::eliminar("id1");

	almacenamiento::WrapperRocksDB::RocksDB::recuperar("id1", clave_valor_a_recuperar);

	ASSERT_STREQ("id1", clave_valor_a_recuperar->getClave().c_str());
	ASSERT_STREQ("", clave_valor_a_recuperar->getValor().c_str());	

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();
}

TEST(WrapperRocksDB, RecuperarClaveInexistente)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new ObjetoClaveValor();

	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::recuperar("knascjonaw", clave_valor_a_recuperar);

	ASSERT_NE(true, estado.ok());
	ASSERT_STREQ("knascjonaw", clave_valor_a_recuperar->getClave().c_str());
	ASSERT_STREQ("", clave_valor_a_recuperar->getValor().c_str());

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();
}

TEST(WrapperRocksDB, EliminarClaveInexistente)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new ObjetoClaveValor();

	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::eliminar("oicvonmcqw");

	ASSERT_EQ(true, estado.ok());

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();
}

/*
TEST(WrapperRocksDB, almacenarYRecuperarConFamiliasCorrectamente)
{
	almacenamiento::IAlmacenableClaveValor* clave_valor_a_almacenar = new ObjetoClaveValor("id2", "conflicto", "");

	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave_valor_a_almacenar, "conceptos");

	almacenamiento::IAlmacenableClaveValor* clave_valor_a_recuperar = new ObjetoClaveValor();

	almacenamiento::WrapperRocksDB::RocksDB::recuperar("id2", clave_valor_a_recuperar, "conceptos");

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_STREQ("id2", clave_valor_a_recuperar->getClave().c_str());
	ASSERT_STREQ("conflicto", clave_valor_a_recuperar->getValor().c_str());
}
*/