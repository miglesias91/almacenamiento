// gtest
#include <gtest/gtest.h>

// Wrapper
#include <WrapperRocksDB/include/WrapperRocksDB.h>
#include <WrapperRocksDB/include/EstadoDB.h>

TEST(WrapperRocksDB, AlmacenarRecuperarEliminarCorrectamente)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	std::string clave = "id1";
	std::string valor = "valor2";
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave, valor);

	std::string valor_a_recuperar_1 = "";
	almacenamiento::WrapperRocksDB::RocksDB::recuperar(clave, valor_a_recuperar_1);

	almacenamiento::WrapperRocksDB::RocksDB::eliminar("id1");

	std::string valor_a_recuperar_2 = "";
	almacenamiento::WrapperRocksDB::RocksDB::recuperar("id1", valor_a_recuperar_2);

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_STREQ("valor2", valor_a_recuperar_1.c_str());
	ASSERT_STREQ("", valor_a_recuperar_2.c_str());
}

TEST(WrapperRocksDB, AlmacenarClaveExistenteConDistintoValor)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");
	
	std::string clave = "id2";
	std::string valor = "valor2";
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave, valor);

	std::string valor_2 = "valor2_2";
	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave, valor_2);

	std::string clave_valor_a_recuperar = "";
	almacenamiento::WrapperRocksDB::RocksDB::recuperar("id2", clave_valor_a_recuperar);

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_EQ(true, estado.ok());
	ASSERT_STREQ("valor2_2", clave_valor_a_recuperar.c_str());
}

TEST(WrapperRocksDB, RecuperarClaveInexistente)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	std::string clave_valor_a_recuperar = "";
	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::recuperar("knascjonaw", clave_valor_a_recuperar);

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_NE(true, estado.ok());
	ASSERT_STREQ("", clave_valor_a_recuperar.c_str());
}

TEST(WrapperRocksDB, EliminarClaveInexistente)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");

	almacenamiento::WrapperRocksDB::EstadoDB estado = almacenamiento::WrapperRocksDB::RocksDB::eliminar("oicvonmcqw");

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_EQ(true, estado.ok());
}

TEST(WrapperRocksDB, AlmacenarYRecuperarVariasClaves)
{
	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");
	std::string clave1 = "idA";
	std::string clave2 = "idB";
	std::string clave3 = "idC";
	std::string clave4 = "idD";
	std::string clave5 = "idE";

	std::string valor1 = "valorA";
	std::string valor2 = "valorB";
	std::string valor3 = "valorC";
	std::string valor4 = "valorD";
	std::string valor5 = "valorE";

	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave1, valor1);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave2, valor2);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave3, valor3);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave4, valor4);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave5, valor5);
	
	std::string valor_recuperado1 = "";
	std::string valor_recuperado2 = "";
	std::string valor_recuperado3 = "";
	almacenamiento::WrapperRocksDB::RocksDB::recuperar(clave2, valor_recuperado1);
	almacenamiento::WrapperRocksDB::RocksDB::recuperar(clave3, valor_recuperado2);
	almacenamiento::WrapperRocksDB::RocksDB::recuperar(clave4, valor_recuperado3);

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	ASSERT_STREQ("valorB", valor_recuperado1.c_str());
	ASSERT_STREQ("valorC", valor_recuperado2.c_str());
	ASSERT_STREQ("valorD", valor_recuperado3.c_str());
}

TEST(WrapperRocksDB, RecuperarPorPrefijo)
{// suponemos un prefijo habilitado y de tamanio = 3.
	std::string clave1 = "terHola";
	std::string clave2 = "terComo";
	std::string clave3 = "terEstas";
	std::string clave4 = "terChau";

	std::string valor1 = "hola!!!";
	std::string valor2 = "como_estas??";
	std::string valor3 = "todo_bien??";
	std::string valor4 = "chau!!";

	almacenamiento::WrapperRocksDB::RocksDB::abrir("C:/temp/test_rocksdb");
	
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave1, valor1);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave2, valor2);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave3, valor3);
	almacenamiento::WrapperRocksDB::RocksDB::almacenar(clave4, valor4);

	std::vector<std::pair<std::string, std::string>> claves_valores_recuperadas;

	almacenamiento::WrapperRocksDB::RocksDB::recuperarGrupoPrefijo("ter", claves_valores_recuperadas);

	almacenamiento::WrapperRocksDB::RocksDB::cerrar();

	// tienen este orden porque INTERNAMENTE estan ordenados alfabeticamente segun la clave.
	ASSERT_STREQ("terChau", claves_valores_recuperadas[0].first.c_str());
	ASSERT_STREQ("terComo", claves_valores_recuperadas[1].first.c_str());
	ASSERT_STREQ("terEstas", claves_valores_recuperadas[2].first.c_str());
	ASSERT_STREQ("terHola", claves_valores_recuperadas[3].first.c_str());

	ASSERT_STREQ("chau!!", claves_valores_recuperadas[0].second.c_str());
	ASSERT_STREQ("como_estas??", claves_valores_recuperadas[1].second.c_str());
	ASSERT_STREQ("todo_bien??", claves_valores_recuperadas[2].second.c_str());
	ASSERT_STREQ("hola!!!", claves_valores_recuperadas[3].second.c_str());
}
