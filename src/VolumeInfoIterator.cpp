#include <mi/VolumeInfo.hpp>
namespace mi
{
        class VolumeInfo::iterator::Impl
        {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl( void )
                {
                        return;
                }

                ~Impl( void )
                {
                        return;
                }

                void init( VolumeInfo* info, const bool isBegin )
                {
                        this->_info = info;
                        this->_pos = this->_info->getMin();
                        if( !isBegin ) this->_pos.z() = this->_info->getMax().z() + 1;
                        return;
                }

                void copy ( Impl& that )
                {
                        this->_info = that._info;
                        this->_pos  = that._pos;
                        return;
                }

                void stepForward( void )
                {
                        const Point3i& size = this->_info->getSize();
                        if( this->_pos.z() >= size.z() ) return;

                        this->_pos.x() += 1;
                        if( this->_pos.x() < size.x() ) return;
                        this->_pos.x() = 0;

                        this->_pos.y() += 1;
                        if( this->_pos.y() < size.y() ) return;
                        this->_pos.y() = 0;

                        this->_pos.z() += 1;

                        return;
                }

                bool isSame ( const Point3i& that )
                {
                        return this->_pos == that;
                }

                Point3i& getPosition( void ) const
                {
                        return const_cast<Impl*>( this )->_pos;
                }
        private:
                VolumeInfo* _info; ///< A pointer to the information of the volume data..
                Point3i _pos; ///< Position where the iterator indicates.
        };


        VolumeInfo::iterator::iterator( VolumeInfo* info, const bool isBegin ) : _impl( new VolumeInfo::iterator::Impl () )
        {
                this->_impl->init( info, isBegin );
                return;
        }

        VolumeInfo::iterator::iterator( const iterator& that ) : _impl( new VolumeInfo::iterator::Impl () )
        {
                this->_impl->copy ( *( that._impl ) );
                return;
        }

        VolumeInfo::iterator&
        VolumeInfo::iterator::operator = ( const iterator& that )
        {
                this->_impl->copy ( *( that._impl ) );
                return *this;
        }

        VolumeInfo::iterator::~iterator ( void )
        {
                delete _impl;
                return;
        }

        VolumeInfo::iterator&
        VolumeInfo::iterator::operator++()
        {
                this->_impl->stepForward();
                return *this;
        }

        /**
         * @brief ++ operator ( iter++ ).
         *
         * Proceed the position of the volume data.
         * @return Instance of iterator of next position.
         */
        VolumeInfo::iterator
        VolumeInfo::iterator::operator++( int )
        {
                iterator tmp ( *this );
                ++tmp;
                return tmp;
        }

        /**
         * @brief == operator.
         *
         * @retval true Two iterators indicate the same position.
         * @retval false Two iterators indicate the different  position.
         */

        bool
        VolumeInfo::iterator::operator==( const VolumeInfo::iterator& rhs )
        {
                return this->_impl->isSame( *rhs );
        }

        /**
         * @brief != operator.
         *
         * @retval true Two iterators indicate the different  position.
         * @retval false Two iterators indicate the same position.
         */
        bool
        VolumeInfo::iterator::operator!=( const iterator& rhs )
        {
                return ! this->_impl->isSame( *rhs );
        }

        /**
         * @brief "+" operator
         * @param [in] n The number of iterations.
         * @return The instance.
         */
        VolumeInfo::iterator
        VolumeInfo::iterator::operator + ( const int n )
        {
                VolumeInfo::iterator tmp( *this );
                tmp.operator += ( n );
                return tmp;
        }

        /**
         * @brief += iterator.
         * @param [in] n The number of iteratos.
         * @return Reference of the instance ( No instance is created.).
         */
        VolumeInfo::iterator&
        VolumeInfo::iterator::operator += ( const int n )
        {
                VolumeInfo::iterator& iter = *this;
                for( int i = 0 ; i < n ; ++i ) ++iter;
                return *this;
        }

        /**
         * @brief *operator.
         * @return Position where the iterator indicates.
         */
        Point3i&
        VolumeInfo::iterator::operator*( void ) const
        {

                return this->_impl->getPosition();
        }
}
