#include <mi/VolumeData.hpp>
#include <mi/Range.hpp>
#include <iostream>
int main ( int argc, char** argv ) {
	mi::VolumeData<unsigned char> volume(100, 100, 100);

	volume.at(10,10,10) = 10;
	
	std::cerr<<(int)volume.at(10,10,10)<<std::endl;

	mi::Range range( mi::Point3i(5,5,5), mi::Point3i(8, 9, 10));
	for ( mi::Range::iterator iter = range.begin() ; iter != range.end() ; ++iter ) {
		std::cerr<< (*iter).transpose()<<std::endl;
	}
	return 0;
}
