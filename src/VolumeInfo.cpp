/**
 * @file  VolumeInfo.cpp
 * @author Takashi Michikawa <michiawa@acm.org>
 */
#include <mi/VolumeInfo.hpp>
#include <cstdlib>
#include <cstring>

namespace mi
{
	class VolumeInfo::Impl {
	private:
                Point3i _size;   ///< Global bounding box.
                Point3d _pitch;  ///< Voxel pitch.
                Point3d _origin; ///< Origin point. Corresponding to global (0,0,0) in voxel space.
	private:
		Impl ( const Impl&);
		void operator = ( const Impl&);
	public:
		Impl ( void ) : _size(0, 0, 0), _pitch(1,1,1), _origin(0, 0, 0) {
			return;
		}
		
		~Impl ( void ) {
			return;
		}

		void copy ( const Impl& that ) {
			this->setSize   ( that.getSize()   );
			this->setPitch  ( that.getPitch()  );
			this->setOrigin ( that.getOrigin() );
			return;
		}

		Point3i getSize   ( void ) const {
			return this->_size;
		}

		Point3d getPitch  ( void ) const {
			return this->_pitch;
		}

		Point3d getOrigin ( void ) const {
			return this->_origin;
		}

		void setSize   ( const Point3i &size ) {
			this->_size = size;
			return;
		}

		void setPitch  ( const Point3d &pitch ) {
			this->_pitch = pitch;
			return;
		}

		void setOrigin ( const Point3d &origin ) {
			this->_origin = origin;
			return;
		}
	};

	VolumeInfo::VolumeInfo ( const Point3i& size , const Point3d& pitch, const Point3d& origin ) : _impl ( new VolumeInfo::Impl()) {
		this->setSize(size).setPitch(pitch).setOrigin(origin);
		return;
	}
	
	VolumeInfo::~VolumeInfo ( void ) {
		delete this->_impl;
		return;
	}
	
	VolumeInfo::VolumeInfo ( const VolumeInfo& that ) {
		this->_impl->copy ( *(that._impl) );
		return;
	}
	
	VolumeInfo& 
	VolumeInfo::setSize( const Point3i& size ) {
		this->_impl->setSize(size);
		return *this;
	}
	
	VolumeInfo& 
	VolumeInfo::setPitch( const Point3d& pitch ) {
		this->_impl->setPitch(pitch);
		return *this;
	}
	
	VolumeInfo&
	VolumeInfo::setOrigin( const Point3d& origin ) {
		this->_impl->setOrigin(origin);
		return *this;
	}
	
	Point3i 
	VolumeInfo::getMin ( void ) const {
		return Point3i( 0,0,0 );
	}
	
	Point3i 
	VolumeInfo::getMax ( void ) const {
		return this->getSize() - Point3i( 1,1,1 );
	}
	
	Point3i 
	VolumeInfo::getSize ( void ) const {
		return this->_impl->getSize();
	}
	
	Point3d 
	VolumeInfo::getPitch ( void ) const {
		return this->_impl->getPitch();
	}
	
	Point3d
	VolumeInfo:: getOrigin ( void ) const {
		return this->_impl->getOrigin();
	}
	
	Point3d 
	VolumeInfo::getPointInSpace ( const Point3i& p ) const {
		const Point3d& pitch  = this->getPitch();
		return Point3d ( pitch.x() * p.x(), pitch.y() * p.y(),	pitch.z() * p.z()) + this->getOrigin();
	}
	
	Point3i 
	VolumeInfo::getPointInVoxel ( const Point3d& p ) const {
		const Point3d& pitch  = this->getPitch();
		const Point3d v = p - this->getOrigin();
		return Point3i (
			static_cast<int>( v.x() / pitch.x() ),
			static_cast<int>( v.y() / pitch.y() ),
			static_cast<int>( v.z() / pitch.z() )
			);
	}
	
	Vector3d
	VolumeInfo::getVectorInSpace ( const Vector3s& p ) const {
		const Point3d& pitch  = this->getPitch();
		return Vector3d ( pitch.x() * p.x(), pitch.y() * p.y(),	pitch.z() * p.z() ) +  this->getOrigin();
	}
	
	int 
	VolumeInfo::toIndex ( const  Point3i& p ) const {
		if ( ! this->isValid ( p ) ) return -1;
		const Point3i& size = this->getSize();
		return p.x() + size.x() * ( p.y() + p.z() * size.y() ) ;
	}

	Point3i 
	VolumeInfo::fromIndex ( const int idx ) const {
		const Point3i& size = this->getSize ();
		return Point3i (
			static_cast<int>(   idx %   size.x() ),
			static_cast<int>( ( idx % ( size.x() * size.y() ) ) / size.x() ),
			static_cast<int>(   idx / ( size.x() * size.y() ) )
			);
	}
	
	bool 
	VolumeInfo::isValid ( const Point3i & p ) const {
		const Point3i& bmin = this->getMin ();
		const Point3i& bmax = this->getMax ();
		return ( bmin.x() <= p.x() && p.x() <= bmax.x() &&
			 bmin.y() <= p.y() && p.y() <= bmax.y() &&
			 bmin.z() <= p.z() && p.z() <= bmax.z() );
	}
	
	Point3i 
	VolumeInfo::clamp ( const Point3i& p ) const {
		const Point3i& bmin = this->getMin ();
		const Point3i& bmax = this->getMax ();
		const int x = this->clamp_int( p.x(), bmin.x(), bmax.x() );
		const int y = this->clamp_int( p.y(), bmin.y(), bmax.y() );
		const int z = this->clamp_int( p.z(), bmin.z(), bmax.z() );
		return Point3i (x,y,z);
	}
	
	float
	VolumeInfo::getLength( const mi::Point3i& v ) const {
		return static_cast<float>( std::sqrt( this->getLengthSquared( v ) ) );
	}
	
	float
	VolumeInfo::getLengthSquared( const mi::Point3i& v ) const {
		const mi::Point3d& p = this->getPitch();
		return static_cast<float>( v.x() * v.x() * p.x() * p.x() + v.y() * v.y() * p.y() * p.y() + v.z()*v.z()*p.z()*p.z() );
	}
	
	VolumeInfo::iterator 
	VolumeInfo::begin( void ) {
		return VolumeInfo::iterator ( this, true );
	}
	
	VolumeInfo::iterator 
	VolumeInfo::end( void ) {
		return VolumeInfo::iterator ( this, false );
	}
	
	VolumeInfo& 
	VolumeInfo::init( const Point3i& size, const Point3d& pitch,  const Point3d& origin ) {
		return this->setSize( size ).setPitch( pitch ).setOrigin( origin );
	}
	
	bool 
	VolumeInfo::isCorner ( const Point3i& p ) const {
		if (  ! this->isValid( p ) ) return false;
		const mi::Point3i& bmin = this->getMin();
		const mi::Point3i& bmax = this->getMax();

		if ( p.x() == bmin.x() ) return true;
		if ( p.y() == bmin.y() ) return true;
		if ( p.z() == bmin.z() ) return true;

		if ( p.x() == bmax.x() ) return true;
		if ( p.y() == bmax.y() ) return true;
		if ( p.z() == bmax.z() ) return true;
		return false;
	}

	int 
	VolumeInfo::clamp_int ( const int input, const int lower, const int upper ) const {
		int result = input;
		if ( result <  lower ) result = lower;
		if ( upper < result  ) result = upper;
		return result;
	}
};
