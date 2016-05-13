/**
 * @file VolumeDataImporter.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/VolumeDataImporter.hpp>
namespace mi
{
        template <typename T>
        class VolumeDataImporter<T>::Impl
        {
        private:
                VolumeData<T>& _data; ///< Data.
                const size_t   _header; ///< Header size ( byte ).
        public:
                Impl ( VolumeData<T>& data, const size_t header ) : _data ( data ), _header ( header )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                VolumeData<T>& data ( void )
                {
                        return this->_data;
                }

                size_t header_size ( void ) const
                {
                        return this->_header;
                }
        };

        template <typename T>
        VolumeDataImporter<T>::VolumeDataImporter ( VolumeData<T>& data, const size_t header_size )
                : Importer ( true ), _impl ( new Impl ( data,  header_size ) )
        {
                return;
        }

        template <typename T>
        VolumeDataImporter<T>::~VolumeDataImporter ( void )
        {
		return;
        }

        template <typename T>
        bool
        VolumeDataImporter<T>::readHeader ( std::ifstream& fin )
        {
                fin.seekg ( this->_impl->header_size() ).good();
                return fin.good();
        }


        template <typename T>
        bool
        VolumeDataImporter<T>::readBody ( std::ifstream& fin )
        {
                VolumeData<T>& data = this->_impl->data();

                if ( !data.isReadable() ) {
                        std::cerr << "error : volume data cannot be read. memory space is not allocated yet." << std::endl;
                        return false;
                }

                const Point3i& size = data.getInfo().getSize ();
                std::vector<T> buffer ( size.x() * size.y(), T() );
                const size_t bufSize = sizeof ( T ) * buffer.size();

                for ( int z = 0 ; z < size.z() ; ++z ) {
                        if ( !fin.read ( ( char* ) & ( buffer[0] ), bufSize ) ) {
                                std::cerr << "reading data failed." << std::endl;
                                return false;
                        }

                        for ( int y = 0 ; y < size.y() ; ++y ) {
                                for ( int x = 0 ; x < size.x() ; ++x ) {
                                        data.at ( x, y, z ) = buffer[ x +  y * size.x() ];
                                }
                        }
                }

                return true;
        }

        /**
         * @brief Get string.
         * @retval String.
         */
        template <typename T>
        std::string
        VolumeDataImporter<T>::toString ( void ) const
        {
                return std::string ( "raw" );
        }
#define VOLUME_DATA_IMPORTER(TYPE) template class VolumeDataImporter<TYPE>;
        VOLUME_DATA_IMPORTER ( unsigned char );
        VOLUME_DATA_IMPORTER ( char );
        VOLUME_DATA_IMPORTER ( unsigned short );
        VOLUME_DATA_IMPORTER ( short );
        VOLUME_DATA_IMPORTER ( unsigned int );
        VOLUME_DATA_IMPORTER ( int );
        VOLUME_DATA_IMPORTER ( float );
        VOLUME_DATA_IMPORTER ( double );
}

