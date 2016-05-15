/**
 * @file VolumeDataImporter.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_VOLUME_DATA_IMPORTER_HPP
#define MI_VOLUME_DATA_IMPORTER_HPP 1
#include <string>
#include <mi/VolumeData.hpp>
#include <mi/Importer.hpp>
#include <memory>
namespace mi
{
        /**
         * @class VolumeDataImporter
         * @brief Importer for raw file.
         */
        template <typename T>
        class VolumeDataImporter : public Importer
        {
        public:
                explicit VolumeDataImporter ( VolumeData<T>& data, const size_t header_size = 0 );
		~VolumeDataImporter( void ) ;
		
        protected:
		bool readHeader ( std::ifstream& fin );
                bool readBody ( std::ifstream& fin );
                std::string toString ( void ) const;
        private:
		class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_VOLUME_DATA_IMPORTER_HPP
