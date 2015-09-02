#include <mi/TestSuite.hpp>
int main ( int argc, char** argv )
{
        const std::string testName ( "mivoltest" );
        return mi::TestSuite::getInstance().run ( testName );
}

