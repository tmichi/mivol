#include <mi/Range.hpp>
namespace mi
{
        class Range::Impl
        {
        public:
                Impl ( void ) : _bmin ( Point3i ( 0, 0, 0 ) ), _bmax ( Point3i ( 0, 0, 0 ) )
                {
                        return;
                }

                ~Impl ( void )
                {
                        return;
                }

                void init ( const Point3i& bmin, const Point3i& bmax )
                {
                        this->_bmin = bmin;
                        this->_bmax = bmax;

                        if ( bmin.x() > bmax.x() ) {
                                this->_bmin.x() = bmax.x();
                                this->_bmax.x() = bmin.x();
                        }

                        if ( bmin.y() > bmax.y() ) {
                                this->_bmin.y() = bmax.y();
                                this->_bmax.y() = bmin.y();
                        }

                        if ( bmin.z() > bmax.z() ) {
                                this->_bmin.z() = bmax.z();
                                this->_bmax.z() = bmin.z();
                        }

                        return;
                }

                Point3i min ( void ) const
                {
                        return this->_bmin;
                }

                Point3i max ( void ) const
                {
                        return this->_bmax;
                }
        private:
                Point3i _bmin;
                Point3i _bmax;
        };

        Range::Range ( const Point3i& bmin, const Point3i& bmax ) : _impl ( new Impl () )
        {
                this->_impl->init ( bmin, bmax );
                return;
        }

        Range::Range ( const Range& that ) : _impl ( new Impl () )
        {
                this->_impl->init ( that.getMin(), that.getMax() ) ;
                return;
        }

        Range::~Range ( void )
        {
                return;
        }

        Range&
        Range::operator = ( const Range& that )
        {
                this->_impl->init ( that.getMin(), that.getMax() ) ;
                return *this;
        }

        bool
        Range::isValid ( const Point3i& p ) const
        {
                const Point3i& bmin = this->getMin();
                const Point3i& bmax = this->getMax();
                return ( bmin.x() <= p.x() && p.x() <= bmax.x() &&
                         bmin.y() <= p.y() && p.y() <= bmax.y() &&
                         bmin.z() <= p.z() && p.z() <= bmax.z() );
        }

        Point3i
        Range::getMin ( void ) const
        {
                return this->_impl->min();
        }

        Point3i
        Range::getMax ( void ) const
        {
                return this->_impl->max();
        }

        Range::iterator
        Range::begin ( void )
        {
                Range::iterator iter;
                iter.init ( this, true );
                return iter;
        }

        Range::iterator
        Range::end ( void )
        {
                Range::iterator iter;
                iter.init ( this, false );
                return iter;
        }
}

