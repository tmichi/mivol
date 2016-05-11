#include <mi/Range.hpp>
#include <iostream>
namespace mi
{
        class Range::iterator::Impl
        {
        public:
                Impl ( void ) 
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                void copy ( const Impl& that )
		{
                        this->_range = that._range;
                        this->_pos   = that._pos;
                }

                void init ( Range* range, const bool isBegining = true )
		{
			this->_range = range;
                        this->_pos = range->getMin();

                        if ( !isBegining ) {
                                this->_pos.z() = range->getMax().z() + 1;
                        }

                        return;
                }

                void stepForward ( void )
                {
                        const Point3i& bmin = this->_range->getMin();
                        const Point3i& bmax = this->_range->getMax();

                        Point3i& pos = this->_pos;
			if ( bmax.z() < pos.z() ) {
				pos.x() = bmin.x();
				pos.y() = bmin.y();
				pos.z() = bmax.z() + 1;
				return;
			}
			else {
				pos.x() += 1;
				if ( bmax.x() < pos.x() ) {
					pos.x() = bmin.x();
					pos.y() += 1;
					
					if ( bmax.y() < pos.y() ) {
						pos.y() = bmin.y();
						pos.z() += 1;
					}
				}
				return;
			}
                }

                Point3i& getPosition ( void )
                {
                        return this->_pos;
                }
        private:
                Range*  _range; // Pointer to the range.
                Point3i _pos;   // Current position.
        };

        Range::iterator::iterator ( void ) : _impl ( new Impl() )
        {
                return;
        }

        Range::iterator::iterator ( const iterator& that ) :  _impl ( new Impl () )
        {
                this->_impl->copy ( * ( that._impl ) );
                return;
        }

        Range::iterator&
        Range::iterator::operator = ( const iterator& that )
        {
                this->_impl->copy ( * ( that._impl ) );
                return *this;
        }

        Range::iterator::~iterator ( void )
        {
                delete this->_impl;
                return;
        }

        Range::iterator&
        Range::iterator::init ( Range* range, const bool isBeginning )
        {
                this->_impl->init ( range, isBeginning );
                return *this;
        }

        Range::iterator&
        Range::iterator::operator++()
        {
                this->_impl->stepForward();
                return *this;
        }

        Range::iterator
        Range::iterator::operator++ ( int )
        {
                Range::iterator tmp ( *this );
                ++tmp;
                return tmp;
        }

        bool
        Range::iterator::operator== ( const iterator& that )
        {
                return this->_impl->getPosition() == that._impl->getPosition();
        }

        bool
        Range::iterator::operator != ( const iterator& that )
        {
                return this->_impl->getPosition() != that._impl->getPosition();
        }

        Range::iterator
        Range::iterator::operator + ( const int n )
        {
                Range::iterator tmp ( *this );
                tmp.operator += ( n );
                return tmp;
        }

        Range::iterator&
        Range::iterator::operator += ( const int n )
        {
                iterator& iter = *this;

                for ( int i = 0 ; i < n ; ++i ) {
                        ++iter;
                }

                return *this;
        }

        Point3i&
        Range::iterator::operator * ( void )
        {
                return this->_impl->getPosition();
        }
}

