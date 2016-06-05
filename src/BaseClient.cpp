/**
 * @brief This module implements simulator of exchange
 * @file BaseClient.cpp
 *
 */


#include "BaseClient.hpp"
#include "Constants.hpp"
#include "Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
BaseClient::BaseClient( const std::string& name_, const boost::python::object& transport_ ):
      name( name_ )
    , transport( transport_ )
{

}


/**
 * @brief Destructor
 *
 */
BaseClient::~BaseClient()
{

}


/**
 * @brief Get string representation of BaseClient
 * @return string
 *
 */
std::string BaseClient::toString( void ) const
{
    return name;
}


/**
 * @brief FIXME
 *
 */
void BaseClient::writeString( const std::string& data )
{
    transport.attr( attr::write )( data );
    transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void BaseClient::writeData( const boost::python::object& data )
{
    transport.attr( attr::write )( json::dumps<const std::string>( data ) );
    transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void BaseClient::disconnect( void )
{
    transport.attr( attr::loseConnection )();
}


} /* namespace pyxchange */



/* EOF */

