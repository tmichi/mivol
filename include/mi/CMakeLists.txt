SET ( include_files VolumeInfo.hpp VolumeData.hpp VolumeDataImporter.hpp VolumeDataExporter.hpp Neighbor.hpp Range.hpp volmath.hpp
    )
INSTALL ( FILES ${include_files}
          DESTINATION include/mi
          PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )

