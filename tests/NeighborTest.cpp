#include <mi/TestCase.hpp>
#include <mi/Neighbor.hpp>
#include <vector>
class NeighborTest : public mi::TestCase
{
private:
        void init ( void )
        {
                this->add ( NeighborTest::test_nbr6  );
                this->add ( NeighborTest::test_nbr18  );
                this->add ( NeighborTest::test_nbr26  );
                return;
        }

        static void test_nbr6( void )
        {
		for ( mi::Neighbor::iterator iter = mi::Neighbor::begin() ; iter != mi::Neighbor::end(6) ; ++iter) {
			mi::Point3i p = *iter;
			std::cerr<<p.x()<<" "<<p.y()<<" "<<p.z()<<std::endl;
			//ASSERT_EQUALS( 100, gsize.y() );
		}
	}
        static void test_nbr18( void )
        {
		for ( mi::Neighbor::iterator iter = mi::Neighbor::begin() ; iter != mi::Neighbor::end(18) ; ++iter) {
			mi::Point3i p = *iter;
			std::cerr<<p.x()<<" "<<p.y()<<" "<<p.z()<<std::endl;
		}
	}
        static void test_nbr26( void )
        {
		for ( mi::Neighbor::iterator iter = mi::Neighbor::begin() ; iter != mi::Neighbor::end(26) ; ++iter) {
			mi::Point3i p = *iter;
			std::cerr<<p.x()<<" "<<p.y()<<" "<<p.z()<<std::endl;
		}
	}
};
INIT_TEST ( NeighborTest );

