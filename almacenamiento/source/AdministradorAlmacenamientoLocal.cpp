#include <almacenamiento/include/AdministradorAlmacenamientoLocal.h>

// stl
#include <experimental/filesystem>

// utiles
#include <utiles/include/FuncionesSistemaArchivos.h>

// almacenamiento
#include <almacenamiento/include/ConfiguracionAlmacenamiento.h>
#include <almacenamiento/include/ImposibleAbrirAlmacenamiento.h>
#include <almacenamiento/include/ImposibleCerrarAlmacenamiento.h>

using namespace almacenamiento;

AdministradorAlmacenamientoLocal::AdministradorAlmacenamientoLocal(ConfiguracionAlmacenamiento * configuracion) : IAdministradorAlmacenamiento(configuracion)
{
    this->directorio = this->configuracion->pathDB();

    this->log->info("nuevo almacenamiento local: '" + this->configuracion->pathDB() +"'.");
}

AdministradorAlmacenamientoLocal::~AdministradorAlmacenamientoLocal()
{
    this->log->info("liberando almacenamiento local: '" + this->configuracion->pathDB() + "'.");
}

// GETTERS

// SETTERS

// METODOS

bool AdministradorAlmacenamientoLocal::abrir()
{
    this->log->info("abriendo db '" + this->configuracion->pathDB() + "'.");

    bool solo_lectura = this->configuracion->soloLectura();
    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.abrir(this->directorio, solo_lectura);

    if (estado.ok())
    {
        this->log->info("db '" + this->configuracion->pathDB() + "' abierta OK.");
        abierto = true;
    }
    else
    {
        this->log->error("no se pudo abrir la db '" + this->configuracion->pathDB() + "'.");
        abierto = false;
        throw excepciones::ImposibleAbrirAlmacenamiento(this->configuracion->pathDB());
    }

    return estado.ok();
}

bool AdministradorAlmacenamientoLocal::cerrar()
{
    this->log->info("cerrando db '" + this->configuracion->pathDB() + "'.");

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.cerrar();

    if (estado.ok())
    {
        this->log->info("db '" + this->configuracion->pathDB() + "' cerrada OK.");
        abierto = false;
    }
    else
    {
        this->log->error("no se pudo cerrar la db '" + this->configuracion->pathDB() + "'.");
        abierto = true;
        throw excepciones::ImposibleCerrarAlmacenamiento(this->configuracion->pathDB());
    }

    return estado.ok();
}

bool AdministradorAlmacenamientoLocal::borrar()
{
    this->log->info("borrando db '" + this->configuracion->pathDB() + "'.");

    return rocksdb_instancia.borrar();
}

bool AdministradorAlmacenamientoLocal::checkpoint(const std::string & path) {

    if (true == std::experimental::filesystem::exists(path)) {
        return false;
    }

    this->log->debug("checkpoint{ path: '" + path + "' }");

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.checkpoint(path);

    return estado.ok();
}

bool AdministradorAlmacenamientoLocal::almacenar(IAlmacenableClaveValor* valor_a_almacenar)
{
    this->log->debug("almacenar{ grupo: '" + valor_a_almacenar->getGrupo() + "' - clave: '" + valor_a_almacenar->getClaveConPrefijo()  +"' - valor: '" + valor_a_almacenar->getValor() + "' }");

    if (this->existe(valor_a_almacenar)) {
        return false;
    }

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.almacenar(valor_a_almacenar->getClaveConPrefijo(), valor_a_almacenar->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(IAlmacenableClaveValor* clave_valor_recuperado)
{
	std::string valor_recuperado = "";

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

	clave_valor_recuperado->setValor(valor_recuperado);

    this->log->debug("recuperar{ grupo: '" + clave_valor_recuperado->getGrupo() + "' - clave: '" + clave_valor_recuperado->getClaveConPrefijo() + "' - valor recuperado: '" + clave_valor_recuperado->getValor() + "' }");

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperar(std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	WrapperRocksDB::EstadoDB estado;

	for (std::vector<IAlmacenableClaveValor*>::iterator it = valores_recuperados.begin(); it != valores_recuperados.end(); it++)
	{
		IAlmacenableClaveValor* clave_valor_recuperado = *it;
		std::string valor_recuperado = "";

        estado = rocksdb_instancia.recuperar(clave_valor_recuperado->getClaveConPrefijo(), valor_recuperado);

		clave_valor_recuperado->setValor(valor_recuperado);

        this->log->debug("recuperar_vector{ grupo: '" + clave_valor_recuperado->getGrupo() + "' - clave: '" + clave_valor_recuperado->getClaveConPrefijo() + "' - valor recuperado: '" + clave_valor_recuperado->getValor() + "' }");

		if (false == estado.ok())
		{
			return estado.ok();
		}
	}

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::recuperarGrupo(std::string prefijo_grupo, std::vector<IAlmacenableClaveValor*> & valores_recuperados)
{
	std::vector<std::pair<std::string, std::string>> claves_valores_recuperados;

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperarGrupoPrefijo(prefijo_grupo, claves_valores_recuperados);

	if ( false == estado.ok())
	{
		return estado.ok();
	}

    std::string lista_recuperados = "";
	for (std::vector<std::pair<std::string, std::string>>::iterator it = claves_valores_recuperados.begin(); it != claves_valores_recuperados.end(); it++)
	{
		std::string clave = (*it).first;
		clave.erase(clave.begin(), clave.begin() + prefijo_grupo.size()); // le borro el prefijo.

		std::string valor = (*it).second;
		valores_recuperados.push_back(new IAlmacenableClaveValor(clave, prefijo_grupo, valor));

        lista_recuperados = "grupo: '" + prefijo_grupo + "' - clave: '" + prefijo_grupo + clave + "' - valor  recuperado: '" + valor + "'\n";
	}

    this->log->debug("recuperarGrupo{\n" + lista_recuperados + "}");

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::modificar(IAlmacenableClaveValor* nuevo_valor)
{
    this->log->debug("modificar{ grupo: '" + nuevo_valor->getGrupo() + "' - clave: '" + nuevo_valor->getClaveConPrefijo() + "' - valor: '" + nuevo_valor->getValor() + "' }");

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.almacenar(nuevo_valor->getClaveConPrefijo(), nuevo_valor->getValor());

	return estado.ok();
}

bool AdministradorAlmacenamientoLocal::eliminar(IAlmacenableClaveValor* clave_a_eliminar)
{
    this->log->debug("eliminar{ grupo: '" + clave_a_eliminar->getGrupo() + "' - clave: '" + clave_a_eliminar->getClaveConPrefijo() + "' }");

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.eliminar(clave_a_eliminar->getClaveConPrefijo());
	
	return estado.ok();
}

// CONSULTA

bool AdministradorAlmacenamientoLocal::existe(IAlmacenableClaveValor* clave_a_chequear)
{
	std::string valor_recuperado = "";

    WrapperRocksDB::EstadoDB estado = rocksdb_instancia.recuperar(clave_a_chequear->getClaveConPrefijo(), valor_recuperado);

	if (valor_recuperado.empty())
	{
        this->log->debug("existe{ grupo: '" + clave_a_chequear->getGrupo() + "' - clave: '" + clave_a_chequear->getClaveConPrefijo() + "' - existe: false }");
        return false;
	}

    this->log->debug("existe{ grupo: '" + clave_a_chequear->getGrupo() + "' - clave: '" + clave_a_chequear->getClaveConPrefijo() + "' - existe: true }");
    return true;
}

bool AdministradorAlmacenamientoLocal::bdAbierta()
{
    return abierto;
}

// METODOS INTERNOS

