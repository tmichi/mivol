#include <mi/TestCase.hpp>
#include <mi/VolumeInfo.hpp>
class VolumeInfoTest : public mi::TestCase
{
private:
        void init ( void )
        {
                this->add ( VolumeInfoTest::test_constructor0   );
                this->add ( VolumeInfoTest::test_constructor1   );
                return;
        }

        static void test_constructor0( void )
        {
                mi::VolumeInfo info( mi::Point3i( 100, 100, 100 ) );

                const mi::Point3i& bmin = info.getMin();
                ASSERT_EQUALS( 0, bmin.x() );
                ASSERT_EQUALS( 0, bmin.y() );
                ASSERT_EQUALS( 0, bmin.z() );
                const mi::Point3i& bmax = info.getMax();
                ASSERT_EQUALS( 99, bmax.x() );
                ASSERT_EQUALS( 99, bmax.y() );
                ASSERT_EQUALS( 99, bmax.z() );
                const mi::Point3i& gsize = info.getSize();
                ASSERT_EQUALS( 100, gsize.x() );
                ASSERT_EQUALS( 100, gsize.y() );
                ASSERT_EQUALS( 100, gsize.z() );

                const mi::Point3d& pitch = info.getPitch();
                ASSERT_EPSILON_EQUALS( 1.0, pitch.x(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 1.0, pitch.y(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 1.0, pitch.z(), 1.0e-7 );

                //@bug Memory issue happens here when using Eigen.
                mi::Point3d origin = info.getOrigin();
                ASSERT_EPSILON_EQUALS( 0.0, origin.x(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 0.0, origin.y(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 0.0, origin.z(), 1.0e-7 );
                return;
        }
        static void test_constructor1( void ) {
		
                mi::VolumeInfo info( mi::Point3i( 100, 100, 100 ) );
                mi::VolumeInfo info1(info);
		
                const mi::Point3i& bmin = info1.getMin();
                ASSERT_EQUALS( 0, bmin.x() );
                ASSERT_EQUALS( 0, bmin.y() );
                ASSERT_EQUALS( 0, bmin.z() );
                const mi::Point3i& bmax = info1.getMax();
                ASSERT_EQUALS( 99, bmax.x() );
                ASSERT_EQUALS( 99, bmax.y() );
                ASSERT_EQUALS( 99, bmax.z() );
                const mi::Point3i& gsize = info1.getSize();
                ASSERT_EQUALS( 100, gsize.x() );
                ASSERT_EQUALS( 100, gsize.y() );
                ASSERT_EQUALS( 100, gsize.z() );

                const mi::Point3d& pitch = info1.getPitch();
                ASSERT_EPSILON_EQUALS( 1.0, pitch.x(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 1.0, pitch.y(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 1.0, pitch.z(), 1.0e-7 );

                //@bug Memory issue happens here when using Eigen.
                mi::Point3d origin = info1.getOrigin();
                ASSERT_EPSILON_EQUALS( 0.0, origin.x(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 0.0, origin.y(), 1.0e-7 );
                ASSERT_EPSILON_EQUALS( 0.0, origin.z(), 1.0e-7 );
		
		return;
	}
};
INIT_TEST ( VolumeInfoTest );

