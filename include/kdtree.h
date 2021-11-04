#ifndef KDTREE_H
#define KDTREE_H

#include "structureSpatial.h"
#include "objectSpatial.h"
#include "vector.h"

namespace Spatial{
    class KDTreeNode;


    class KDTree : public structureSpatial
    {
        public:
        
            KDTree(Vector refCenter, float f32HalfWidth);
            ~KDTree();
            
        public:
        
            void                                VAddObjects(const std::vector<objectSpatial*>& refObjects);
            void                                VUpdate();
            
        protected:
        
            void                                Preallocate(int i32Depth);
            
            
        
        protected:
        
            static int                          s_i32MaxDepth;
            
            
            
        protected:
        
            KDTreeNode*                         m_pRootNode;
        
            Vector                             m_vec3Center;
            float                               m_f32HalfWidth;
            
            std::vector<objectSpatial*>        m_vecObjects;
    
    };



    class KDTreeNode : public cellSpatial
    {
        friend class KDTree;
        
        
        public:
        
            KDTreeNode(KDTreeNode* pParent, int i32SplitPane);
            ~KDTreeNode();
    
        public:
            
            
            void                                            Construct(objectSpatial* pObjectList,
                                                                        int i32ObjectCount,
                                                                        const Vector& refVectorMin,
                                                                        const Vector& refVectorMax);
            
            void                                            Preallocate(int i32Depth);
            
            int                                             CheckContains(objectSpatial* pObject);
            int                                             CheckStraddle(objectSpatial* pObject);
            
            void                                            AddObject(objectSpatial* pObject);
            void                                            RemoveObject(objectSpatial* pObject);
            
            void                                            CheckCollisions(objectSpatial* pObject);
            
            void                                            Rebuild();

            objectSpatial*                                 Invalidate();

            
        protected:
        
            static int                                      s_i32BinCount;
            
            static std::vector<std::pair<int, int> >        s_vecBins;
            static std::vector<std::pair<int, int> >        s_vecSums;
                        
            static float                                    s_f32AcceptableRatioLower;
            static float                                    s_f32AcceptableRatioUpper;
            
            
    
        protected:
        
            KDTreeNode*                                     m_pParent;
            KDTreeNode*                                     m_pChildLeft;
            KDTreeNode*                                     m_pChildRight;
            
            objectSpatial*                                 m_pObjects;
            
            int                                             m_i32ObjectCount;
            int                                             m_i32ObjectTotal;
            
            int                                             m_i32SplitPane;
            float                                           m_f32SplitPosition;
            
            Vector                                         m_vec3Min;
            Vector                                         m_vec3Max;
            
            
            
    
    
    };
}

#endif