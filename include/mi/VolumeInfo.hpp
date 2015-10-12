/**
 * @file  VolumeInfo.hpp
 * @author Takashi Michikawa <michiawa@acm.org>
 */
#ifndef MI_VOLUME_INFO_HPP
#define MI_VOLUME_INFO_HPP 1

#include <cstdlib>
#include <cstring>
#include <iterator>
#include <vector>

#include "volmath.hpp"


namespace mi
{
        class VolumeInfo
        {
        private:
                void operator = ( const VolumeInfo& that );
        public:
                class iterator :  public std::iterator<std::input_iterator_tag, Point3i>
                {
                public:
                        explicit iterator( VolumeInfo* info, const bool isBegin = true );
                        iterator( const iterator& that );
                        ~iterator ( void );
                        iterator& operator =  ( const iterator& that );
                        iterator& operator ++ ( void );
                        iterator  operator ++ ( int );
			bool      operator == ( const iterator& rhs );                               
                        bool      operator != ( const iterator& rhs );
                        iterator  operator +  ( const int n );
                        iterator& operator += ( const int n );
                        Point3i&  operator *  ( void ) const;
                private:
			class Impl;
			Impl *_impl;
                };
        private:
		class Impl;
		Impl *_impl;
        public:
                explicit VolumeInfo ( const Point3i& size   = Point3i( 0,0,0 ), 
				      const Point3d& pitch  = Point3d( 1,1,1 ), 
				      const Point3d& origin = Point3d( 0,0,0 ) );
                explicit VolumeInfo ( const VolumeInfo& that );
		~VolumeInfo( void ) ;

                VolumeInfo& setSize  ( const Point3i& size );
                VolumeInfo& setPitch ( const Point3d& pitch );
                VolumeInfo& setOrigin( const Point3d& origin );
                VolumeInfo& init     ( const Point3i& size, const Point3d& pitch,  const Point3d& origin );
		/**
		 * @brief Initialize by bounding box.
		 * @param [in] bmin Bounding box ( minimum )
		 * @param [in] bmax Bounding box ( maximum )
		 * @param [in] pitch Voxel pitch 
		 * @param [in] offset Offset value.
		 * @return Reference to itself. 
		 */
                VolumeInfo& initByBoundingBox ( const Vector3d& bmin, const Vector3d& bmax,  const Point3d& pitch, const double offset = 1.0e-6 );

                Point3i getMin    ( void ) const;
                Point3i getMax    ( void ) const;
                Point3i getSize   ( void ) const;
                Point3d getPitch  ( void ) const;
                Point3d getOrigin ( void ) const;
		
                Point3d  getPointInSpace  ( const Point3i& p  ) const;
                Point3i  getPointInVoxel  ( const Point3d& p  ) const;
                Vector3d getVectorInSpace ( const Vector3s& p ) const;
		
                bool isValid  ( const Point3i& p ) const;
                bool isCorner ( const Point3i& p ) const;
                Point3i clamp ( const Point3i& p ) const;
		
                int toIndex ( const  Point3i& p ) const;
                Point3i fromIndex ( const int idx ) const;

                float getLength( const mi::Point3i& v ) const;
                float getLengthSquared( const mi::Point3i& v ) const;

                iterator begin( void );
                iterator end( void );

                std::string getSizeString( void ) const;
		std::string getPitchString( void ) const;

	private:
		int clamp_int ( const int v, const int minv, const int maxv ) const;
        };
}
#endif//
