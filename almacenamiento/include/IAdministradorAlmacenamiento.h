/// IAdministradorAlmacenamiento.h
/// 02-05-2017

#pragma once

// stl
#include <vector>
#include <unordered_map>

// log
#include <log/include/AdministradorLog.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>
#include <almacenamiento/include/IAlmacenableClaveValor.h>

namespace almacenamiento
{

    class IAdministradorAlmacenamiento
    {
    public:

        IAdministradorAlmacenamiento(ConfiguracionAlmacenamiento * configuracion);
        virtual ~IAdministradorAlmacenamiento();

        static uintmax_t iniciarNuevo(const ConfiguracionAlmacenamiento & configuracion);
        static uintmax_t iniciarNuevo(const std::string & path_configuracion);

        static void liberarTodos();

        static void liberar(uintmax_t handler);

        static void crearAdministradorAlmacenamientoLocal(uintmax_t handler, ConfiguracionAlmacenamiento * configuracion);

        static void crearAdministradorAlmacenamientoDistribuido(uintmax_t handler, ConfiguracionAlmacenamiento * configuracion);

        static bool administradorIniciado(uintmax_t handler);

        // GETTERS

        static IAdministradorAlmacenamiento* getInstancia(uintmax_t handler);

        static IAdministradorAlmacenamiento* getInstancia(std::string path_db);

        herramientas::log::Logger * log;

        virtual ConfiguracionAlmacenamiento * config();

        // SETTERS

        // METODOS

        virtual bool abrir() = 0;

        virtual bool cerrar() = 0;

        virtual bool borrar() = 0;

        virtual bool checkpoint(const std::string & path) = 0;

		virtual bool almacenar(IAlmacenableClaveValor* valor_a_almacenar) = 0;

		virtual bool recuperar(IAlmacenableClaveValor* valor_recuperado) = 0;

		virtual bool recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados) = 0;

		virtual bool modificar(IAlmacenableClaveValor* nuevo_valor) = 0;

		virtual bool eliminar(IAlmacenableClaveValor* clave_a_eliminar) = 0;

		// CONSULTA

		virtual bool existe(IAlmacenableClaveValor* clave_a_chequear) = 0;

        virtual bool bdAbierta() = 0;

    protected:

        ConfiguracionAlmacenamiento * configuracion;

	private:
		// METODOS INTERNOS

		// ATRIBUTOS

        static std::unordered_map<uintmax_t, IAdministradorAlmacenamiento*> mapa_administradores;
};
};