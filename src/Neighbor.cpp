#include <vector>
#include <algorithm>
#include <functional>
#include <mi/Neighbor.hpp>

namespace mi
{
        class l1dist : std::unary_function<Point3i, bool>
        {
        public:
                result_type  operator() ( const Point3i& lhs, const Point3i& rhs ) const
                {
                        return  lhs.x() * lhs.x() + lhs.y() * lhs.y() + lhs.z() * lhs.z() <
                                rhs.x() * rhs.x() + rhs.y() * rhs.y() + rhs.z() * rhs.z();
                }
        };


        std::vector< Point3i >&
        Neighbor::getNeighbor( void )
        {
                static std::vector< Point3i > dp;
                if( dp.size() == 0 ) {
                        dp.reserve( 26 );
                        for( int dz = -1 ; dz <= 1 ; ++dz ) {
                                for( int dy = -1 ; dy <= 1 ; ++dy ) {
                                        for( int dx = -1 ; dx <= 1 ; ++dx ) {
                                                if( dx == 0 && dy == 0 && dz == 0 ) continue;
                                                dp.push_back( Point3i( dx, dy, dz ) );
                                        }
                                }
                        }
                        std::sort( dp.begin(), dp.end(), l1dist() );
                }
                return dp;
        }

        Neighbor::iterator
        Neighbor::begin( void )
        {
                return Neighbor::getNeighbor().begin();
        }

        Neighbor::iterator
        Neighbor::end ( const int n )
        {
                const int nbr = ( n == 6 || n == 18 || n == 26 ) ? n : 26;
                return Neighbor::getNeighbor().begin() + nbr;
        }

        Neighbor::iterator
        Neighbor::end6 ( void )
        {
                return Neighbor::end( 6 );
        }

        Neighbor::iterator
        Neighbor::end18 ( void )
        {
                return Neighbor::end( 18 );
        }

        Neighbor::iterator
        Neighbor::end26 ( void )
        {
                return Neighbor::end( 26 );
        }
}
