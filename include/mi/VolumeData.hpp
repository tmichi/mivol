/**
 * @file VolumeData.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_VOLUME_DATA_HPP
#define MI_VOLUME_DATA_HPP 1
#include "VolumeInfo.hpp"
namespace mi
{
        /**
         * @class VolumeData VolumeData.hpp <mi/VolumeData.hpp>
         */
        template <typename T>
        class VolumeData
        {


        private:
                VolumeData( const VolumeData<T>& that );
                void operator = ( const VolumeData<T>& that );
        public:
                explicit VolumeData ( void );
                explicit VolumeData ( const int x, const int y, const int z , const bool allocateMemory = true );
                explicit VolumeData ( const Point3i& size, const bool allocateMemory = true );
                explicit VolumeData ( const VolumeInfo& info, const bool allocateMemory = true );
                virtual ~VolumeData ( void );
                VolumeData& init ( const Point3i& size, const bool allocateMemory = true );
                VolumeData& init ( const VolumeInfo& info, const bool allocateMemory = true );
                VolumeData& fill ( const T& value );
		VolumeInfo& getInfo ( void );
		Point3i getSize ( void );
		T get ( const Point3i& p ) const;
		T get ( const int x, const int y, const int z ) const;
		void set ( const Point3i& p, const T v );
		void set ( const int x, const int y, const int z , const T v );
		T at ( const Point3i& p ) const;
		T& at ( const Point3i& p );
		T at ( const int x, const int y, const int z ) const;
		T& at ( const int x, const int y, const int z );
                void clear( void );
                bool clone( const VolumeData<T>& that );
                bool allocate ( void );
                bool deallocate ( void );
		bool isReadable ( void ) const;
                bool check ( void );
//                iterator begin( void );
//                iterator end( void );

                std::string createFileName( const std::string& name, const std::string& ext = std::string( "raw" ) );
        private:
		class Impl;
		Impl* _impl;
        };
};
#endif// MI_VOLUME_DATA_HPP

