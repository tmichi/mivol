ADD_EXECUTABLE(mivoltest VolumeInfoTest.cpp mivoltest.cpp)
TARGET_LINK_LIBRARIES(mivoltest mibase mivol)
ADD_TEST(mivoltest mivoltest) #for CTest
	





