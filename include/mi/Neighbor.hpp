#ifndef MI_NEIGHBOR_HPP
#define MI_NEIGHBOR_HPP 1
#include <vector>
#include <mi/math.hpp>

namespace mi
{
        /**
         * @class Neighbor Neighbor.hpp <mi/Neighbor.hpp>
         * @brief Vector to neighboring voxels.
         */
        class Neighbor
        {
        private:
                Neighbor( const Neighbor& that );
                void operator = ( const Neighbor& that );
        public:
                typedef std::vector<Point3i>::iterator iterator;
        public:
                static std::vector< Point3i >& getNeighbor( void );
                static iterator begin( void );
                static iterator end ( const int n = 26 );
                static iterator end6 ( void );
                static iterator end18 ( void );
                static iterator end26 ( void );
        };
}
#endif //MI_NEIGHBOR_HPP
