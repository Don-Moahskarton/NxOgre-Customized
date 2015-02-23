/** 
    
    This file is part of NxOgre.
    
    Copyright (c) 2009 Robin Southern, http://www.nxogre.org
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
    
*/

                                                                                       

#include "NxOgreStable.h"
#include "NxOgreCommon.h"
#include "NxOgrePrincipalScene.h"

#include "NxOgreSceneLink.h"

                                                                                       

namespace NxOgre
{

                                                                                       

 
PrincipalScene::PrincipalScene(const SceneDescription& scene_description, NxPhysicsSDK* sdk)
: Scene(scene_description, sdk)
{
}

PrincipalScene::~PrincipalScene()
{
}

Enums::SceneType PrincipalScene::getType() const
{
 return Enums::SceneType_Prinicipal;
}

void PrincipalScene::addPrincipalDynamic(RigidBody* rbody)
{
 mPrincipalDynamics.push_back(rbody);
}

void PrincipalScene::removePrincipalDynamic(RigidBody* rbody)
{
 mPrincipalDynamics.remove(mPrincipalDynamics.index(rbody));
}

PrincipalScene::PrincipalDynamicIterator PrincipalScene::getPrincipalDynamics()
{
 return mPrincipalDynamics.elements();
}

                                                                                       

} // namespace NxOgre

                                                                                       
