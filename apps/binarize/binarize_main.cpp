#include "BinarizeCommand.hpp"


template<typename T>
static int executeBinarizeCommand ( mi::Argument &arg )
{
        BinarizeCommand<T> cmd;
        return mi::CommandTemplate::execute( cmd,arg );
}
int main ( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        if      ( arg.exist ( "-char" )   ) return executeBinarizeCommand<char> ( arg );
        else if ( arg.exist ( "-uchar" )  ) return executeBinarizeCommand<unsigned char> ( arg );
        else if ( arg.exist ( "-short" )  ) return executeBinarizeCommand<short> ( arg );
        else if ( arg.exist ( "-ushort" ) ) return executeBinarizeCommand<unsigned short> ( arg );
        else if ( arg.exist ( "-int" )    ) return executeBinarizeCommand<int> ( arg );
        else if ( arg.exist ( "-uint" )   ) return executeBinarizeCommand<unsigned int> ( arg );
        else if ( arg.exist ( "-float" )  ) return executeBinarizeCommand<float> ( arg );
        else if ( arg.exist ( "-double" ) ) return executeBinarizeCommand<double> ( arg );
        else  {
                std::cerr << "voxel type was not specified. short is selected as default."<<std::endl;
                return executeBinarizeCommand<short> ( arg );
        }

}
