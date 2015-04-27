/**
 * @file VolumeData.cpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/VolumeData.hpp>
namespace mi
{
        template <typename T>
        class VolumeData<T>::Impl
        {
	public:
		Impl ( void ) : _isReadable (false) {
			return;
		}
		
		~Impl ( void ) {
			return;
		}
		
		VolumeInfo& info ( void ) {
			return this->_info;
		}
		
		T& at ( const int x, const int y, const int z ) {
			return this->_data.at(z).at(y).at(x);
		}

		bool allocate ( void ) {
                        if ( ! this->isReadable() ) {
                                const Point3i& size = this->_info.getSize ();
                                this->_isReadable = false;
                                this->_data.assign( size.z() , std::vector<std::vector<T> >( size.y(), std::vector<T>( size.x(), T() ) ) );
                                if ( this->_data.size() != static_cast<size_t>( size.z() ) ) return false;
                                this->_isReadable = true;
                        }
                        return true;			
		}

		bool deallocate ( void ) {
                        this->_data.erase( this->_data.begin(), this->_data.end() );
                        this->_isReadable = false;
                        return true;
		}
		
		bool isReadable (void ) const {
			return this->_isReadable;
		}
	private:
		VolumeInfo _info;
                std::vector<std::vector<std::vector<T> > > _data;
                bool _isReadable;
	};

        template <typename T>
	VolumeData<T>::VolumeData ( void ) : _impl ( new VolumeData<T>::Impl() ) {
		return;
	}
	
	template <typename T>
	VolumeData<T>::VolumeData ( const int x, const int y, const int z , const bool allocateMemory) : _impl ( new VolumeData<T>::Impl() ) {
		const Point3i size ( x,y,z );
		const VolumeInfo info ( size );
		this->init ( info, allocateMemory );
		return;
	}
	
	template <typename T>
	VolumeData<T>::VolumeData ( const Point3i& size, const bool allocateMemory ) : _impl ( new VolumeData<T>::Impl() ) {
		const VolumeInfo info( size );
		this->init ( info, allocateMemory );
		return;
	}

        template <typename T>
	VolumeData<T>::VolumeData ( const VolumeInfo& info, const bool allocateMemory ) : _impl ( new VolumeData<T>::Impl() ) {
		this->init ( info, allocateMemory );
		return;
	}

	template <typename T>
	VolumeData<T>::~VolumeData ( void ) {
		delete this->_impl;
		return;
	}
	
	template <typename T>
	VolumeData<T>& 
	VolumeData<T>::init ( const Point3i& size, const bool allocateMemory ) {
		const VolumeInfo info( size );
		return this->init ( info, allocateMemory );
	}

        template <typename T>
	VolumeData<T>& 
	VolumeData<T>::init ( const VolumeInfo& info, const bool allocateMemory ) {
		this->deallocate();
		this->getInfo().init( info.getSize(), info.getPitch(), info.getOrigin() );
		if ( allocateMemory ) this->allocate();
		return *this;
	}

        template <typename T>
	VolumeData<T>&
	VolumeData<T>::fill ( const T& value ) {
		const Point3i& size = this->getInfo().getSize();
		for ( int z = 0 ; z < size.z() ; ++z ) {
			for ( int y = 0 ; y < size.y() ; ++y  ) {
				for ( int x = 0 ; x < size.x() ; ++x ) {
					this->set(Point3i(x,y,z), value);
				}
			}
		}
		return *this;
	}

        template <typename T>	
	VolumeInfo& 
	VolumeData<T>::getInfo ( void ) {
		return this->_impl->info();
	}
	
	template <typename T>
	Point3i 
	VolumeData<T>::getSize ( void ) {
		return this->getInfo().getSize();
	}
	
	template <typename T>
	T 
	VolumeData<T>::get ( const Point3i& p ) const {
		return this->get ( p.x(), p.y(), p.z()  );
	}
	
	template <typename T>
	T
	VolumeData<T>::get ( const int x, const int y, const int z ) const {
		return this->at( x, y, z );
	}
	
	template <typename T>
	void 
	VolumeData<T>::set ( const Point3i& p, const T v ) {
		this->set ( p.x(), p.y(), p.z(), v);
		return;
	}
	
	template <typename T>
	void 
	VolumeData<T>::set ( const int x, const int y, const int z , const T v ) {
		this->at( x, y, z ) = v;
		return;
	}

	template <typename T>
	T 
	VolumeData<T>::at ( const Point3i& p ) const {
		return this->at ( p.x(), p.y(), p.z() );
	}
	
        template <typename T>
	T& 
	VolumeData<T>::at ( const Point3i& p ) {
		return this->at ( p.x(), p.y(), p.z() );
	}

	template <typename T>
	T 
	VolumeData<T>::at ( const int x, const int y, const int z ) const {
		return this->_impl->at(x,y,z);
	}
	
	template <typename T>
	T& 
	VolumeData<T>::at ( const int x, const int y, const int z ) {
		return this->_impl->at(x,y,z);
	}
	
        template <typename T>
	void
	VolumeData<T>::clear( void ) {
		this->fill(T());
		return;
	}
        template <typename T>
	bool 
	VolumeData<T>::clone( VolumeData<T>& that ) {
		if ( that.getSize() != this->getSize() ) return false;
		const Point3i& size = this->getSize();
		for( int z = 0 ; z < size.z() ; ++z ) {
			for( int y = 0 ; y < size.y() ; ++y ) {
				for( int x = 0 ; x < size.x() ; ++x ) {
					this->set( x,y,z,that.get( x,y,z ) );
				}
			}
		}
		return true;
	}
	
	template <typename T>
	bool
	VolumeData<T>::allocate ( void ) {
		return this->_impl->allocate();
	}

	template <typename T>
	bool
	VolumeData<T>::deallocate ( void ) {
		this->_impl->deallocate();
		return true;
	}
	
	template <typename T>
	bool
	VolumeData<T>::isReadable ( void ) const {
		return this->_impl->isReadable();
	}
	
/*	template <typename T>
	VolumeData<T>::iterator
	VolumeData<T>::begin( void ) {
		return VolumeData<T>::iterator( &( this->_data ), true );
	}
	
	template <typename T>
	VolumeData<T>::iterator
	VolumeData<T>::end( void ) {
		return VolumeData<T>::iterator( &( this->_data ), false );
	}
*/
	template <typename T>
	std::string
	VolumeData<T>::createFileName( const std::string& name, const std::string& ext ) {
		const Point3i& size  = this->getInfo().getSize();
		const Point3d& pitch = this->getInfo().getPitch();
		std::stringstream ss;
		ss<<name<<"-"<<size.x()<<"x"<<size.y()<<"x"<<size.z()<<"-"<<pitch.x()<<"x"<<pitch.y()<<"x"<<pitch.z()<<"."<<ext;
		return ss.str();
	}

#define VOLUME_DATA(TYPE) template class VolumeData<TYPE>;
	VOLUME_DATA(unsigned char);
	VOLUME_DATA(char);
	VOLUME_DATA(unsigned short);
	VOLUME_DATA(short);
	VOLUME_DATA(unsigned int);
	VOLUME_DATA(int);
	VOLUME_DATA(float);
	VOLUME_DATA(double);


}
