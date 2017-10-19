
// gtest
#include <gtest/gtest.h>

// vld
#include <vld.h>

// almacenamiento
#include <almacenamiento/include/IAdministradorAlmacenamiento.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	almacenamiento::IAdministradorAlmacenamiento::iniciar("configuracion_almacenamiento.json");

	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->abrir();

	int result = RUN_ALL_TESTS();
	
	almacenamiento::IAdministradorAlmacenamiento::getInstancia()->cerrar();

	almacenamiento::IAdministradorAlmacenamiento::liberar();

	std::getchar();

	return result;
}