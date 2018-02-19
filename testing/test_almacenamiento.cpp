// gtest
#include <gtest/gtest.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>
#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

std::string path_db;
std::string path_db_2;

TEST(almacenamiento, ConfigurarCorrectamente)
{
    almacenamiento::ConfiguracionAlmacenamiento config("config_testing.json");

    path_db = config.pathDB();

    almacenamiento::ConfiguracionAlmacenamiento config_2("config_testing_2.json");

    path_db_2 = config_2.pathDB();

    ASSERT_STREQ("C:/temp/db_almacenamiento--testing--debug", path_db.c_str());

    ASSERT_STREQ("C:/temp/db_almacenamiento_2--testing--debug", path_db_2.c_str());

	ASSERT_EQ(true, config.almacenamientoLocal());

	ASSERT_EQ(false, config.almacenamientoDistribuido());
}

TEST(almacenamiento, AlmacenarYRecuperarCorrectamente)
{
    std::string clave = "id_uno";
    std::string valor = "valor_uno";
    std::string grupo = "abc";

    // opero en la db 1

    almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->almacenar(clave_valor);
    delete clave_valor;

    almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperar(clave_valor_recuperado);

    ASSERT_STREQ(clave.c_str(), clave_valor_recuperado->getClave().c_str());
    ASSERT_STREQ(valor.c_str(), clave_valor_recuperado->getValor().c_str());
    ASSERT_STREQ((grupo + clave).c_str(), clave_valor_recuperado->getClaveConPrefijo().c_str());
    delete clave_valor_recuperado;

    // opero en la db 2

    clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->almacenar(clave_valor);
    delete clave_valor;

    clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperar(clave_valor_recuperado);

    ASSERT_STREQ(clave.c_str(), clave_valor_recuperado->getClave().c_str());
    ASSERT_STREQ(valor.c_str(), clave_valor_recuperado->getValor().c_str());
    ASSERT_STREQ((grupo + clave).c_str(), clave_valor_recuperado->getClaveConPrefijo().c_str());
    delete clave_valor_recuperado;
}

TEST(almacenamiento, AlmacenarYEliminarCorrectamente)
{
	std::string clave = "id_dos";
	std::string valor = "valor_dos";
	std::string grupo = "abc";

    // opero en la db 1

    almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->almacenar(clave_valor);
	delete clave_valor;

	almacenamiento::IAlmacenableClaveValor* clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
	almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_correcto = clave_valor_recuperado->getValor();

	almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->eliminar(clave_valor_recuperado);

	almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperar(clave_valor_recuperado);

	std::string valor_recuperado_eliminado = clave_valor_recuperado->getValor();
	delete clave_valor_recuperado;

	ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
	ASSERT_STREQ("", valor_recuperado_eliminado.c_str());

    // opero en la db 2

    clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->almacenar(clave_valor);
    delete clave_valor;

    clave_valor_recuperado = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperar(clave_valor_recuperado);

    valor_recuperado_correcto = clave_valor_recuperado->getValor();

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->eliminar(clave_valor_recuperado);

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperar(clave_valor_recuperado);

    valor_recuperado_eliminado = clave_valor_recuperado->getValor();
    delete clave_valor_recuperado;

    ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
    ASSERT_STREQ("", valor_recuperado_eliminado.c_str());
}

TEST(almacenamiento, AlmacenarYModificarCorrectamente)
{
    std::string clave = "id_tres";
    std::string valor = "valor_tres";
    std::string grupo = "abc";

    // opero en la db 1

    almacenamiento::IAlmacenableClaveValor* clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->almacenar(clave_valor);
    delete clave_valor;

    almacenamiento::IAlmacenableClaveValor* clave_valor_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperar(clave_valor_a_modificar);

    std::string valor_recuperado_correcto = clave_valor_a_modificar->getValor();

    std::string valor_modificado = "valor_modif_tres";
    clave_valor_a_modificar->setValor(valor_modificado);

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->modificar(clave_valor_a_modificar);

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperar(clave_valor_a_modificar);
    std::string valor_modificado_correcto = clave_valor_a_modificar->getValor();
    delete clave_valor_a_modificar;

    ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
    ASSERT_STREQ(valor_modificado.c_str(), valor_modificado_correcto.c_str());

    // opero en la db 2

    clave_valor = new almacenamiento::IAlmacenableClaveValor(clave, grupo, valor);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->almacenar(clave_valor);
    delete clave_valor;

    clave_valor_a_modificar = new almacenamiento::IAlmacenableClaveValor(clave, grupo);
    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperar(clave_valor_a_modificar);

    valor_recuperado_correcto = clave_valor_a_modificar->getValor();

    valor_modificado = "valor_modif_tres";
    clave_valor_a_modificar->setValor(valor_modificado);

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->modificar(clave_valor_a_modificar);

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperar(clave_valor_a_modificar);
    valor_modificado_correcto = clave_valor_a_modificar->getValor();
    delete clave_valor_a_modificar;

    ASSERT_STREQ(valor.c_str(), valor_recuperado_correcto.c_str());
    ASSERT_STREQ(valor_modificado.c_str(), valor_modificado_correcto.c_str());
}

TEST(almacenamiento, RecuperarGrupoCorrectamente)
{
	std::string grupo = "abc";
	std::vector<almacenamiento::IAlmacenableClaveValor*> valores_recuperados;

    // opero en la db 1

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db)->recuperarGrupo(grupo, valores_recuperados);

	ASSERT_EQ(2, valores_recuperados.size());

	ASSERT_STREQ("id_tres", valores_recuperados[0]->getClave().c_str());
	ASSERT_STREQ("valor_modif_tres", valores_recuperados[0]->getValor().c_str());
	ASSERT_STREQ("abc", valores_recuperados[0]->getGrupo().c_str());
	ASSERT_STREQ("abcid_tres", valores_recuperados[0]->getClaveConPrefijo().c_str());

	ASSERT_STREQ("id_uno", valores_recuperados[1]->getClave().c_str());
	ASSERT_STREQ("valor_uno", valores_recuperados[1]->getValor().c_str());
	ASSERT_STREQ("abc", valores_recuperados[1]->getGrupo().c_str());
	ASSERT_STREQ("abcid_uno", valores_recuperados[1]->getClaveConPrefijo().c_str());

	for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
	{
		delete (*it);
	}
	valores_recuperados.clear();

    // opero en la db 2

    almacenamiento::IAdministradorAlmacenamiento::getInstancia(path_db_2)->recuperarGrupo(grupo, valores_recuperados);

    ASSERT_EQ(2, valores_recuperados.size());

    ASSERT_STREQ("id_tres", valores_recuperados[0]->getClave().c_str());
    ASSERT_STREQ("valor_modif_tres", valores_recuperados[0]->getValor().c_str());
    ASSERT_STREQ("abc", valores_recuperados[0]->getGrupo().c_str());
    ASSERT_STREQ("abcid_tres", valores_recuperados[0]->getClaveConPrefijo().c_str());

    ASSERT_STREQ("id_uno", valores_recuperados[1]->getClave().c_str());
    ASSERT_STREQ("valor_uno", valores_recuperados[1]->getValor().c_str());
    ASSERT_STREQ("abc", valores_recuperados[1]->getGrupo().c_str());
    ASSERT_STREQ("abcid_uno", valores_recuperados[1]->getClaveConPrefijo().c_str());

    for (std::vector<almacenamiento::IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
    {
        delete (*it);
    }
    valores_recuperados.clear();
}

TEST(almacenamiento, AbrirYBorrarBDLocalCorrectamente)
{
    almacenamiento::ConfiguracionAlmacenamiento * config = new almacenamiento::ConfiguracionAlmacenamiento();

    config->pathDB("C:/temp/db_almacenamiento--testing--debug_PARA_BORRAR");

    almacenamiento::AdministradorAlmacenamientoLocal admin_local(config);

    admin_local.abrir();

    bool borrado_error = !admin_local.borrar();

    admin_local.cerrar();

    bool borrado_ok = admin_local.borrar();

    ASSERT_EQ(true, borrado_error);
    ASSERT_EQ(true, borrado_ok);
}