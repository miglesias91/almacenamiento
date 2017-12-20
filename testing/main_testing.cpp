
// gtest
#include <gtest/gtest.h>

#ifdef DEBUG | _DEBUG
// vld
#include <vld.h>
#endif

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	almacenamiento::IAdministradorAlmacenamiento::iniciar("config_testing.json");

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->abrir();

	int result = RUN_ALL_TESTS();
	
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->cerrar();

	almacenamiento::IAdministradorAlmacenamiento::liberar();

	std::getchar();

	return result;
}