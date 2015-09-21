/**
 * @file VolumeDataExporter.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/VolumeDataExporter.hpp>
namespace mi
{

        template <typename T>
        class VolumeDataExporter<T>::Impl
        {
        private:
                VolumeData<T>& _data; ///< Volume data.
        public:
                Impl ( VolumeData<T>& data ) : _data( data )
                {
                        return;
                }

                VolumeData<T>& getData()
                {
                        return this->_data;
                }
        };

        template <typename T>
        VolumeDataExporter<T>::VolumeDataExporter ( VolumeData<T>& data ) : Exporter ( true ), _impl ( new Impl ( data ) )
        {
                return;
        }

        template <typename T>
        VolumeDataExporter<T>::~VolumeDataExporter ( void )
        {
                delete this->_impl;
                return;
        }

        template <typename T>
        bool
        VolumeDataExporter<T>::writeBody ( std::ofstream& fout )
        {
                VolumeData<T>& data = this->_impl->getData();

                if ( ! data.isReadable() ) {
                        std::cerr << "volume data is not readable." << std::endl;
                        return false;
                }

                const Point3i& size = data.getInfo().getSize();
                const int numElem = size.x() * size.y();
                const size_t bufSize = sizeof ( T ) * numElem;

                std::vector<T> buf ( numElem, T() );
                for ( int z = 0 ; z < size.z() ; ++z ) {
                        for ( int y = 0 ; y < size.y() ; ++y ) {
                                for ( int x = 0 ; x < size.x() ; ++x )  {
                                        buf.at ( x + size.x() * y ) = data.at ( x, y, z );
                                }
                        }
                        if( !fout.write ( ( char* )( &buf[0] ), bufSize ) ) {
                                std::cerr << "writing data failed. " << std::endl;
                                return false;
                        }
                }
                return fout.good();
        }

        template <typename T>
        std::string
        VolumeDataExporter<T>::toString ( void ) const
        {
                return std::string ( "raw" );
        }

#define VOLUME_DATA_EXPORTER(TYPE) template class VolumeDataExporter<TYPE>
        VOLUME_DATA_EXPORTER( unsigned char );
        VOLUME_DATA_EXPORTER( char );
        VOLUME_DATA_EXPORTER( unsigned short );
        VOLUME_DATA_EXPORTER( short );
        VOLUME_DATA_EXPORTER( unsigned int );
        VOLUME_DATA_EXPORTER( int );
        VOLUME_DATA_EXPORTER( float );
        VOLUME_DATA_EXPORTER( double );
}


