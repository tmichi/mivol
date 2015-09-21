ADD_LIBRARY( mivol STATIC
Range.cpp
RangeIterator.cpp
VolumeInfo.cpp
VolumeInfoIterator.cpp
VolumeData.cpp
VolumeDataImporter.cpp
VolumeDataExporter.cpp
Neighbor.cpp
)
INSTALL(TARGETS mivol ARCHIVE DESTINATION lib)
