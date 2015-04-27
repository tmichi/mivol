ADD_LIBRARY( mivol SHARED
Range.cpp
RangeIterator.cpp
VolumeInfo.cpp
VolumeInfoIterator.cpp
VolumeData.cpp
VolumeDataImporter.cpp
VolumeDataExporter.cpp
Neighbor.cpp
)
TARGET_LINK_LIBRARIES(mivol mibase)
SET_TARGET_PROPERTIES(mivol PROPERTIES VERSION ${serial} SOVERSION ${soserial})
INSTALL(TARGETS mivol LIBRARY DESTINATION lib)
