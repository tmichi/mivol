#include "BinarizeCommand.hpp"
#include <mi/VolumeData.hpp>
#include <mi/VolumeDataImporter.hpp>
#include <mi/VolumeDataExporter.hpp>
template<typename T>
BinarizeCommand<T>::BinarizeCommand ( void ) : mi::CommandTemplate()
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        attrSet.createTripleNumericAttribute<int>( "-size", this->_size.x(), this->_size.y(), this->_size.z() ).setMin( 1,1,1 ).setMandatory();
        attrSet.createNumericAttribute<int>( "-h", this->_header_size ).setMin( 0 );
        attrSet.createNumericAttribute<T  >( "-t", this->_threshold );
        attrSet.createNumericAttribute<int>( "-g", this->_grain_size ).setDefaultValue( 100000 ).setMin( 0 );
        attrSet.createStringAttribute( "-i", this->_input_file ).setMandatory();
        attrSet.createStringAttribute( "-o", this->_output_file ).setMandatory();
        return;
}
template<typename T>
BinarizeCommand<T>::~BinarizeCommand ( void )
{
        return;
}

template<typename T>
bool
BinarizeCommand<T>::init ( const mi::Argument& arg )
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        if( !attrSet.parse( arg ) ) {
                attrSet.printError();
                return false;
        }
        return true;
}

template<typename T>
bool
BinarizeCommand<T>::run ( void )
{
        mi::VolumeData<T> inData( this->_size );
        mi::VolumeData<char> outData( this->_size );
        if( !mi::VolumeDataImporter<T>( inData ).read( this->_input_file ) ) return false;
        for( int z = 0 ; z < this->_size.z() ; ++z ) {
                for( int y = 0 ; y < this->_size.y() ; ++y ) {
                        for( int x = 0 ; x < this->_size.x() ; ++x ) {
                                char value = inData.get( x,y,z ) < this->_threshold ? char( 0 ) : char( 1 );
                                outData.set( x,y,z, value );
                        }
                }
        }
        if( !mi::VolumeDataExporter<char>( outData ).write( this->_output_file ) ) return false;
        return true;
}

template<typename T>
bool
BinarizeCommand<T>::term ( void )
{
        return true;
}

template class BinarizeCommand<char>;
template class BinarizeCommand<unsigned char>;
template class BinarizeCommand<short>;
template class BinarizeCommand<unsigned short>;
template class BinarizeCommand<int>;
template class BinarizeCommand<unsigned int>;
template class BinarizeCommand<float>;
template class BinarizeCommand<double>;
