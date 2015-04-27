/**
* @file  VoxelType.hpp
* @author Takashi Michikawa <michikawa@acm.org>
*/
#ifndef MI_VOXEL_TYPE_HPP
#define MI_VOXEL_TYPE_HPP 1
namespace mi
{
        /**
         * @enum VoxelType "VoxelType.hpp" "mi/VoxelType.hpp#
         * @section Reference
         * @li [Malandain1993] Malandain, G., Betrand, G., and Ayache, N.
         * Topological segmentation of discrete surfaces. Int. J. Comput. Vision 10, 2, 183-197, 1993
         * http://www.springerlink.com/content/jgt7166k24286hx7/
         */
        enum VoxelType {
                Invalid,
                Background,
                InteriorPoint,
                IsolatePoint,
                BorderPoint,
                CurvePoint,
                SurfacePoint,
                CurvesJunction,
                SurfaceCurveJunction,
                SurfacesJunction,
                SurfacesCurvesJunction
        };
};
#endif//MI_VOXEL_TYPE_HPP
