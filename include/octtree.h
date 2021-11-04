#ifndef OCTTREE_H
#define OCTTREE_H

#include "ISpatialStructure.h"
#include "Vector.h"

#include <list>

namespace Spatial
{
    class OctreeNode;
    
    class Octree : public structureSpatial
    {
        public:
            
            Octree(const Vector& refCenter, float f32HalfWidth, int i32Rebuild = 0);
            ~Octree();
            
        public:
        
            void                                    Preallocate(int i32Depth);
            
        public:
            
            void                                    VAddObjects(const std::vector<ISpatialObject*>& refObjects);
            void                                    VUpdate();
            
        
        protected:
        
            static int                              s_i32MaxDepth;
            static float                            s_f32MaxObjectNodeRatio;
            
            
        protected:
        
            OctreeNode*                             m_pRootNode;
            int                                     m_i32Rebuild;
            float                                   m_f32HalfWidth;
            
            std::vector<ISpatialObject*>            m_vecObjects;
            
            

    };
    
    
    
    class OctreeNode : public ISpatialCell
    {      
        friend class Octree;
        
        public:
        
            OctreeNode(OctreeNode* pParent, const Vector& refCenter, float f32HalfWidth, int i32Depth);
            ~OctreeNode();
            
        public:
        
            int                             CheckContains(ISpatialObject* pObject);
            
            void                            AddObject(ISpatialObject* pObject);
            void                            AddObjects(ISpatialObject* pObjects, int i32ObjectCount);
                                    
            bool                            IsLeaf() const;
            
            void                            Preallocate(int i32Depth);
            void                            Rebuild();
            
            void                            CheckCollisions(std::vector<OctreeNode*>& refAncestors);
            
            void                            CheckMutualCollisions(ISpatialObject* pObject);
            
            void                            Free();
                 
                        
        protected:
        
            static int                      s_i32MinSplitCount;
                               
                                             
        protected:
        
            OctreeNode*                     m_pParent;
        
            // [rad] Children of this node
            OctreeNode*                     m_pChildren[8];
            
            // [rad] All objects stored at this node (single link list)
            ISpatialObject*                 m_pObjects;
            
            
            int                             m_i32ObjectCount;
            
                    
            // [rad] Center of this node
            Vector                         m_vec3Center;
                    
            // [rad] Half Width of this node
            float                           m_f32HalfWidth;
            
            // [rad] Depth of this node
            int                             m_i32Depth;
            
            
    };

}


#endif