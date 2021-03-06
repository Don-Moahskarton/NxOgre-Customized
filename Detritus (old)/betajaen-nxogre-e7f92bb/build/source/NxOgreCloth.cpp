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
#include "NxOgreCloth.h"
#include "NxOgreClothDescription.h"
#include "NxOgreMesh.h"
#include "NxOgrePrototypeFunctions.h"
#include "NxOgreScene.h"
#include "NxOgreReason.h"
#include "NxOgreMeshRenderable.h"
#include "NxOgreRenderable.h"
#include "NxOgreShape.h"
#include "NxOgreRaycastHit.h"
#include "NxOgreRigidBody.h"
#include "NxOgreRay.h"

#include "NxPhysics.h"



namespace NxOgre
{



Cloth::Cloth(const ClothDescription& description, Renderable* renderable, Enums::Priority priority, Scene* scene)
: mName(description.mName),
  mMesh(description.mMesh),
  mScene(scene),
  mMeshRenderable(0),
  mRenderable(renderable),
  mPriority(priority),
  mDrawnAtLeastOnce(false)
{

 mNameHash = Strings::hash(mName);

 NxClothDesc desc;
 ::NxOgre::Functions::PrototypeFunctions::ClothDescriptionToNxClothDesc(description, desc);
 
 mMeshRenderable = GC::safe_new2<MeshRenderable>(mMesh, desc.tearFactor, NXOGRE_GC_THIS);
 mMeshRenderable->getPhysXMeshData(desc.meshData);

 if (desc.isValid() == false)
 {
  NxOgre_ThrowException(DescriptionInvalidException, Reason::Exceptionise(desc), Classes::_Cloth);
  return;
 }

 mCloth = mScene->getScene()->createCloth(desc);
// TimeController::getSingleton()->addTimeListener(this, mPriority);
 mScene->addRenderListener(this, mPriority);

}

Cloth::~Cloth()
{
 //TimeController::getSingleton()->removeTimeListener(this, mPriority);
 mScene->removeRenderListener(this, mPriority);
 GC::safe_delete(mMeshRenderable, NXOGRE_GC_THIS);
}


bool Cloth::advance(float, const Enums::Priority&, const Enums::SceneFunction&)
{

 if (mRenderable && mMeshRenderable)
 {
  NxBounds3 bounds;
  mCloth->getWorldBounds(bounds);

  /*if (mDrawnAtLeastOnce)
  {
   mRenderable->drawClothFast(mMeshRenderable, Bounds3::from(bounds));
  }
  else
  {*/
   mRenderable->drawCloth(mMeshRenderable, Bounds3::from(bounds));
  // mDrawnAtLeastOnce = true;
  //}
 }

 return true;
}

Renderable*  Cloth::getRenderable()
{
 return mRenderable;
}

Mesh*  Cloth::getMesh()
{
 return mMesh;
}

NxCloth*  Cloth::getPhysXCloth()
{
 return mCloth;
}

MeshRenderable*  Cloth::getMeshRenderable()
{
 return mMeshRenderable;
}

String Cloth::getName() const
{
 return mName;
}

StringHash Cloth::getNameHash() const
{
 return mNameHash;
}

void Cloth::setBendingStiffness(Real stiffness)
{
 mCloth->setBendingStiffness(stiffness);
}

Real Cloth::getBendingStiffness() const
{
 return mCloth->getBendingStiffness();
}

void Cloth::setStretchingStiffness(Real stiffness)
{
 mCloth->setStretchingStiffness(stiffness);
}

Real Cloth::getStretchingStiffness() const
{
 return mCloth->getStretchingStiffness();
}

void Cloth::setDampingCoefficient(Real damping)
{
 mCloth->setDampingCoefficient(damping);
}

Real Cloth::getDampingCoefficient() const
{
 return mCloth->getDampingCoefficient();
}

void Cloth::setFriction(Real friction)
{
 mCloth->setFriction(friction);
}

Real Cloth::getFriction() const
{
 return mCloth->getFriction();
}

void Cloth::setPressure(Real pressure)
{
 mCloth->setPressure(pressure);
}

Real Cloth::getPressure() const
{
 return mCloth->getPressure();
}

void Cloth::setTearFactor(Real factor)
{
 mCloth->setTearFactor(factor);
}

Real Cloth::getTearFactor() const
{
 return mCloth->getTearFactor();
}

void Cloth::setAttachmentTearFactor(Real factor)
{
 mCloth->setAttachmentTearFactor(factor);
}

Real Cloth::getAttachmentTearFactor() const
{
 return mCloth->getAttachmentTearFactor();
}

void Cloth::setThickness(Real thickness)
{
 mCloth->setAttachmentTearFactor(thickness);
}

Real Cloth::getThickness() const
{
 return mCloth->getThickness();
}

Real Cloth::getDensity() const
{
 return mCloth->getDensity();
}

Real Cloth::getRelativeGridSpacing() const
{
 return mCloth->getRelativeGridSpacing();
}

unsigned int Cloth::getSolverIterations() const
{
 return mCloth->getSolverIterations();
}

void Cloth::setSolverIterations(unsigned int solverIterations)
{
 mCloth->setSolverIterations(solverIterations);
}

Bounds3 Cloth::getWorldBounds() const
{
 NxBounds3 bounds;
 mCloth->getWorldBounds(bounds);
 return Bounds3::from(bounds);
}

void Cloth::attachToShape(Shape* shape, unsigned int attachmentFlags)
{
 mCloth->attachToShape(shape->getAbstractShape(), attachmentFlags);
}

void Cloth::attachToCollidingShapes(unsigned int attachmentFlags)
{
 mCloth->attachToCollidingShapes(attachmentFlags);
}

void Cloth::attachVertexToShape(unsigned int vertexId, Shape* shape, const Vec3& localPos, unsigned int attachmentFlags)
{
 mCloth->attachVertexToShape(vertexId, shape->getAbstractShape(), localPos.as<NxVec3>(), attachmentFlags);
}

void Cloth::attachVertexToGlobalPosition(unsigned int vertexId, const Vec3& globalPos)
{
 mCloth->attachVertexToGlobalPosition(vertexId, globalPos.as<NxVec3>());
}

void Cloth::detachFromShape(Shape* shape)
{
 mCloth->detachFromShape(shape->getAbstractShape());
}

void Cloth::freeVertex(unsigned int vertexId)
{
 mCloth->freeVertex(vertexId);
}

void Cloth::dominateVertex(unsigned int vertexId, Real expirationTime, Real dominanceWeight)
{
 mCloth->dominateVertex(vertexId, expirationTime, dominanceWeight);
}

Enums::ClothVertexAttachmentStatus Cloth::getVertexAttachmentStatus(unsigned int vertexId) const
{
 return Enums::ClothVertexAttachmentStatus((int) mCloth->getVertexAttachmentStatus(vertexId));
}

Shape* Cloth::getVertexAttachmentShape(unsigned int vertexId) const
{
 NxShape* nx_shape = mCloth->getVertexAttachmentShape(vertexId);
 if (nx_shape == 0)
  return 0;

 return pointer_cast(nx_shape->userData)->get<Shape>();
}

Vec3   Cloth::getVertexAttachmentPosition(unsigned int vertexId) const
{
 return Vec3(mCloth->getVertexAttachmentPosition(vertexId));
}

void   Cloth::attachToCore(RigidBody* rigidbody, Real impulseThreshold, Real penetrationDepth, Real maxDeformationDistance)
{
 return mCloth->attachToCore(rigidbody->getNxActor(), impulseThreshold, penetrationDepth, maxDeformationDistance);
}

bool   Cloth::tearVertex(const unsigned int vertexId, const Vec3& normal)
{
 return mCloth->tearVertex(vertexId, normal.as<NxVec3>());
}

ClothRaycastHit Cloth::raycast(const Ray& ray)
{
 ClothRaycastHit hit;
 NxRay world_ray;
 world_ray.dir = ray.mDirection.as<NxVec3>();
 world_ray.orig = ray.mOrigin.as<NxVec3>();
 NxVec3 world;
 hit.mDidHit = mCloth->raycast(world_ray, world, hit.mVertexId);
 hit.mWorldPosition = world;
 return hit;
}

unsigned short Cloth::getGroup()
{
 return mCloth->getGroup();
}

void Cloth::setGroupsMask(const int4& m)
{
 NxGroupsMask mask;
 mask.bits0 = m.w;
 mask.bits1 = m.x;
 mask.bits2 = m.y;
 mask.bits3 = m.z;
 return mCloth->setGroupsMask(mask);
}

int4 Cloth::getGroupsMask() const
{
 int4 mask;
 const NxGroupsMask m = mCloth->getGroupsMask();
 mask.w = m.bits0;
 mask.x = m.bits1;
 mask.y = m.bits2;
 mask.z = m.bits3;
 return mask;
}

void Cloth::setValidBounds(const Bounds3& bounds)
{
 NxBounds3 b;
 b.min = bounds.min.as<NxVec3>();
 b.max = bounds.max.as<NxVec3>();
 mCloth->setValidBounds(b);
}

Bounds3 Cloth::getValidBounds() const
{
 NxBounds3 bounds;
 mCloth->getValidBounds(bounds);
 return Bounds3::from(bounds);
}

void Cloth::setPosition(const Vec3& position, unsigned int vertexId)
{
 mCloth->setPosition(position.as<NxVec3>(), vertexId);
}

void Cloth::setPositions(buffer<Vec3>& positions)
{
 mCloth->setPositions(positions.first(), sizeof(Vec3));
}

Vec3 Cloth::getPosition(unsigned int vertexId)
{
 return Vec3(mCloth->getPosition(vertexId));
}

void Cloth::getPositions(buffer<Vec3>& positions)
{
 mCloth->getPositions(positions.first(), sizeof(Vec3));
}

void Cloth::setVelocity(const Vec3& v, unsigned int vertexId)
{
 mCloth->setVelocity(v.as<NxVec3>(), vertexId);
}

void Cloth::setVelocities(buffer<Vec3>& v)
{
 mCloth->setVelocities(v.first(), sizeof(Vec3));
}

Vec3 Cloth::getVelocity(unsigned int vertexId)
{
 return Vec3(mCloth->getVelocity(vertexId));
}

void Cloth::getVelocities(buffer<Vec3>& v)
{
 mCloth->getVelocities(v.first(), sizeof(Vec3));
}

unsigned int Cloth::getNumberOfParticles()
{
 return mCloth->getNumberOfParticles();
}

void Cloth::setCollisionResponseCoefficient(Real coefficient)
{
 mCloth->setCollisionResponseCoefficient(coefficient);
}

Real Cloth::getCollisionResponseCoefficient() const
{
 return mCloth->getCollisionResponseCoefficient();
}

void Cloth::setAttachmentResponseCoefficient(Real coefficient)
{
 mCloth->setAttachmentResponseCoefficient(coefficient);
}

Real Cloth::getAttachmentResponseCoefficient() const
{
 return mCloth->getAttachmentResponseCoefficient();
}

void Cloth::setFromFluidResponseCoefficient(Real coefficient)
{
 mCloth->setFromFluidResponseCoefficient(coefficient);
}

Real Cloth::getFromFluidResponseCoefficient() const
{
 return mCloth->getFromFluidResponseCoefficient();
}

void Cloth::setToFluidResponseCoefficient(Real coefficient)
{
 mCloth->setToFluidResponseCoefficient(coefficient);
}

Real Cloth::getToFluidResponseCoefficient() const
{
 return mCloth->getToFluidResponseCoefficient();
}

void Cloth::setExternalAcceleration(const Vec3& acceleration)
{
 mCloth->setExternalAcceleration(acceleration.as<NxVec3>());
}

Vec3 Cloth::getExternalAcceleration() const
{
 return mCloth->getExternalAcceleration();
}

void Cloth::setMinAdhereVelocity(Real velocity)
{
 mCloth->setMinAdhereVelocity(velocity);
}

Real Cloth::getMinAdhereVelocity() const
{
 return mCloth->getMinAdhereVelocity();
}

void Cloth::setWindAcceleration(const Vec3& acceleration)
{
 mCloth->setWindAcceleration(acceleration.as<NxVec3>());
}

Vec3 Cloth::getWindAcceleration() const
{
 return Vec3(mCloth->getWindAcceleration());
}

bool Cloth::isSleeping() const
{
 return mCloth->isSleeping();
}

Real Cloth::getSleepLinearVelocity() const
{
 return mCloth->getSleepLinearVelocity();
}

void Cloth::setSleepLinearVelocity(Real threshold)
{
 mCloth->setSleepLinearVelocity(threshold);
}

void Cloth::wakeUp(Real wakeCounterValue)
{
 mCloth->wakeUp(wakeCounterValue);
}

void Cloth::putToSleep()
{
 mCloth->putToSleep();
}

void Cloth::setFlags(unsigned int flags)
{
 mCloth->setFlags(flags);
}

unsigned int Cloth::getFlags() const
{
 return mCloth->getFlags();
}

void Cloth::setName(const String& name)
{
 mName = name;
 mCloth->setName(mName.c_str());
}

void Cloth::addForceAtVertex(const Vec3& force, unsigned int vertexId, Enums::ForceMode mode)
{
 mCloth->addForceAtVertex(force.as<NxVec3>(), vertexId, (NxForceMode) (int) mode);
}

void Cloth::addForceAtPos(const Vec3& position, Real magnitude, Real radius, Enums::ForceMode mode)
{
 mCloth->addForceAtPos(position.as<NxVec3>(), magnitude, radius,(NxForceMode) (int) mode);
}

void Cloth::addDirectedForceAtPos(const Vec3& position, const Vec3& force, Real radius, Enums::ForceMode mode)
{
 mCloth->addDirectedForceAtPos(position.as<NxVec3>(), force.as<NxVec3>(), radius,(NxForceMode) (int) mode);
}

bool Cloth::overlapAABBTriangles(const Bounds3& bounds, unsigned int& nbIndices, const unsigned int*& indices) const
{
 NxBounds3 b;
 b.min = bounds.min.as<NxVec3>();
 b.max = bounds.max.as<NxVec3>();

 return mCloth->overlapAABBTriangles(b, nbIndices, indices);
}

Scene* Cloth::getScene()
{
 return mScene;
}

unsigned int Cloth::getPPUTime() const
{
 return mCloth->getPPUTime();
}

MaterialIdentifier Cloth::getForceFieldMaterial() const
{
 return mCloth->getForceFieldMaterial();
}

void Cloth::setForceFieldMaterial(MaterialIdentifier mi)
{
 mCloth->setForceFieldMaterial(mi);
}

String Cloth::to_s() const
{
 return NxOgre::to_s((void*)this, (mName.length() ? String("'" + mName + "'") : String("Cloth") ));
}



} // namespace NxOgre


