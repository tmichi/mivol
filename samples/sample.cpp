#include <mi/VolumeData.hpp>
#include <iostream>
int main ( int argc, char** argv ) {
	mi::VolumeData<unsigned char> volume(100, 100, 100);

	volume.at(10,10,10) = 10;
	
	std::cerr<<(int)volume.at(10,10,10)<<std::endl;
	
	return 0;
}
