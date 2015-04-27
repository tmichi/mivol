/**
 * @file VoxelTypeClassifier.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#ifndef MI_VOXEL_TYPE_CLASSIFIER_HPP
#define MI_VOXEL_TYPE_CLASSIFIER_HPP 1
#include <mi/VolumeData.hpp>
#include <mi/VoxelType.hpp>
namespace mi
{
        /**
         * @class VoxelTypeClassifier VoxelTypeClassifier.hpp "mi/VoxelTypeClassifier.hpp"
         */
        class VoxelTypeClassifier
        {
        private:
                enum NeighborType {
                        NEIGHBOR_NONE, // none
                        NEIGHBOR_26,
                        NEIGHBOR_18,
                        NEIGHBOR_6
                };
        private:
                VoxelTypeClassifier ( VoxelTypeClassifier &that );
                void operator =     ( VoxelTypeClassifier &that );
        private:
                VolumeData<char>& _voxel;
        public:
                VoxelTypeClassifier ( VolumeData<char>& voxel );
                ~VoxelTypeClassifier ( void );

                VoxelType get ( const Point3i& p );
		bool isSurface  ( const VoxelType type );
		bool isEdge     ( const VoxelType type );
		bool isJunction ( const VoxelType type );
        };
}
#endif // MI_VOXEL_TYPE_CLASSIFIER_HPP
