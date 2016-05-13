/**
 * @file VolumeDataExporter.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_VOLUME_DATA_EXPORTER_HPP
#define MI_VOLUME_DATA_EXPORTER_HPP 1
#include <mi/Exporter.hpp>
#include <mi/VolumeData.hpp>
#include <memory>
namespace mi
{
        /**
         * @class VolumeDataExporter VolumeDataExporter.hpp <mi/VolumeDataExporter.hpp>
         * @brief Exporter for VolumeData<T> class.
         */
        template <typename T>
        class VolumeDataExporter : public Exporter
        {
        public:
                explicit VolumeDataExporter ( VolumeData<T>& data );
		~VolumeDataExporter(void ) ;
        protected:
                bool writeBody ( std::ofstream& fout );
                std::string toString ( void ) const;
        private:
		class Impl;
		std::unique_ptr<Impl> _impl;
        };
}
#endif// MI_VOLUME_DATA_EXPORTER_HPP

