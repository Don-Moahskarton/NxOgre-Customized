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
#include "NxOgreActor.h"

#include "NxOgreScene.h"
#include "NxOgreShape.h"
#include "NxOgreRigidBodyFunctions.h"

#include "NxActor.h"
#include "NxScene.h"

#include <iostream>

                                                                                       

namespace NxOgre
{

                                                                                       

Actor::Actor(Scene* scene)
: RigidBody(scene)
{
}

Actor::Actor(const ShapeDescription& shape, const Matrix44& pose, const RigidBodyDescription& description, Scene* scene)
: RigidBody(scene)
{
 mName = description.mName;
 mNameHash = Strings::hash(mName);

 _createDynamic(pose, description, scene, shape);
}

Actor::Actor(const ShapeDescriptions& shapes, const Matrix44& pose, const RigidBodyDescription& description, Scene* scene)
: RigidBody(scene)
{
 mName = description.mName;
 mNameHash = Strings::hash(mName);

 _createDynamic(pose, description, scene, shapes);
}

Actor::~Actor()
{
 _destroy();
}

void Actor::createDynamic(const Matrix44& matrix_pose, const RigidBodyDescription& description, const ShapeDescription& shape)
{
 _createDynamic(matrix_pose, description, mScene, shape);
}

void Actor::createDynamic(const Matrix44& matrix_pose, const RigidBodyDescription& description, const ShapeDescriptions& shapes)
{
 _createDynamic(matrix_pose, description, mScene, shapes);
}

bool Actor::isActorBased() const
{
 return true;
}

void Actor::raiseDynamicFlag(DynamicRigidbodyFlags::Flags flag)
{
 mActor->raiseBodyFlag((NxBodyFlag) (int) flag);
}

void Actor::clearDynamicFlag(DynamicRigidbodyFlags::Flags flag)
{
 mActor->clearBodyFlag((NxBodyFlag) (int) flag);
}

bool Actor::hasDynamicFlag(DynamicRigidbodyFlags::Flags flag) const
{
 return mActor->readBodyFlag((NxBodyFlag) (int) flag);
}

unsigned int Actor::getRigidBodyType() const
{
 return ::NxOgre::Classes::_Actor;
}

void Actor::setGroup(GroupIdentifier actorGroup)
{
 mActor->setGroup(actorGroup);
}

GroupIdentifier Actor::getGroup() const
{
 return mActor->getGroup();
}

void Actor::setDominanceGroup(GroupIdentifier dominanceGroup)
{
 mActor->setGroup(dominanceGroup);
}

GroupIdentifier Actor::getDominanceGroup() const
{
 return mActor->getDominanceGroup();
}

void Actor::resetPairFiltering()
{
 mActor->resetUserActorPairFiltering();
}

Real Actor::computeKineticEnergy() const
{
 return mActor->computeKineticEnergy();
}

void Actor::setSolverIterationCount(unsigned int iterCount)
{
 mActor->setSolverIterationCount(iterCount);
}

unsigned int Actor::getSolverIterationCount() const
{
 return mActor->getSolverIterationCount();
}

Real Actor::getContactReportThreshold() const
{
 return mActor->getContactReportThreshold();
}

void Actor::setContactReportThreshold(Real threshold)
{
 mActor->setContactReportThreshold(threshold);
}

unsigned int Actor::getContactReportFlags() const
{
 return mActor->getContactReportFlags();
}

void Actor::setContactReportFlags(unsigned int flags)
{
 mActor->setContactReportFlags(flags);
}

unsigned short Actor::getForceFieldMaterial() const
{
 return mActor->getForceFieldMaterial();
}

void Actor::setForceFieldMaterial(unsigned short ffm)
{
 mActor->setForceFieldMaterial(ffm);
}

void Actor::setGlobalPose(const Matrix44& matrix)
{
 NxMat34 global_pose;
 global_pose.setRowMajor44(matrix.ptr());
 mActor->setGlobalPose(global_pose);
}

void Actor::setGlobalPosition(const Vec3& vec)
{
 mActor->setGlobalPosition(vec.as<NxVec3>());
}

void Actor::setGlobalOrientation(const Matrix33& mat)
{
 NxMat33 matrix;
 matrix.setRowMajor(mat.ptr());
 mActor->setGlobalOrientation(matrix);
}

void Actor::setGlobalOrientationQuat(const Quat& quat)
{
 mActor->setGlobalOrientationQuat(quat.as<NxQuat>());
}

Matrix44 Actor::getGlobalPose() const
{
 Matrix44 matrix;
 mActor->getGlobalPose().getRowMajor44(matrix.ptr());
 return matrix;
}

Vec3 Actor::getGlobalPosition() const
{
 return Vec3(mActor->getGlobalPosition());
}

Matrix33 Actor::getGlobalOrientation() const
{
 Matrix33 matrix;
 mActor->getGlobalOrientation().getRowMajor(matrix.ptr());
 return matrix;
}

Quat Actor::getGlobalOrientationQuat() const
{
 return Quat(mActor->getGlobalOrientationQuat());
}

void Actor::setCMassOffsetLocalPose(const Matrix44& matrix)
{

 NxMat34 global_pose;
 global_pose.setRowMajor44(matrix.ptr());
 mActor->setCMassOffsetLocalPose(global_pose);

}

void Actor::setCMassOffsetLocalPosition(const Vec3& vec)
{
 mActor->setCMassOffsetLocalPosition(vec.as<NxVec3>());
}

void Actor::setCMassOffsetLocalOrientation(const Matrix33& matrix)
{
 NxMat34 global_pose;
 global_pose.setRowMajor44(matrix.ptr());
 mActor->setCMassOffsetGlobalPose(global_pose);
}

void Actor::setCMassOffsetGlobalPose(const Matrix44& matrix)
{
 NxMat34 global_pose;
 global_pose.setRowMajor44(matrix.ptr());
 mActor->setCMassOffsetGlobalPose(global_pose);
}

void Actor::setCMassOffsetGlobalPosition(const Vec3& vec)
{
 mActor->setCMassOffsetGlobalPosition(vec.as<NxVec3>());
}

void Actor::setCMassOffsetGlobalOrientation(const Matrix33& r33)
{
 NxMat33 global_orientation;
 global_orientation.setRowMajor(r33.ptr());
 mActor->setCMassOffsetGlobalOrientation(global_orientation);
}

void Actor::setCMassGlobalPose(const Matrix44& matrix)
{
 NxMat34 global_pose;
 global_pose.setRowMajor44(matrix.ptr());
 mActor->setCMassGlobalPose(global_pose);
}

void Actor::setCMassGlobalPosition(const Vec3& vec)
{
 mActor->setCMassGlobalPosition(vec.as<NxVec3>());
}

void Actor::setCMassGlobalOrientation(const Matrix33& r33)
{
 NxMat33 global_orientation;
 global_orientation.setRowMajor(r33.ptr());
 mActor->setCMassGlobalOrientation(global_orientation);
}

Matrix44 Actor::getCMassLocalPose() const
{
 Matrix44 global_pose;
 mActor->getCMassLocalPose().getRowMajor44(global_pose.ptr());
 return global_pose;
}

Vec3 Actor::getCMassLocalPosition() const
{
 return Vec3(mActor->getCMassLocalPosition());
}

Matrix33 Actor::getCMassLocalOrientation() const
{
 Matrix33 global_orientation;
 mActor->getCMassLocalOrientation().getRowMajor(global_orientation.ptr());
 return global_orientation;
}

Matrix44 Actor::getCMassGlobalPose() const
{
 Matrix44 global_pose;
 mActor->getCMassGlobalPose().getRowMajor44(global_pose.ptr());
 return global_pose;
}

Vec3 Actor::getCMassGlobalPosition() const
{
 return Vec3(mActor->getCMassGlobalPosition());
}

Matrix33 Actor::getCMassGlobalOrientation() const
{
 Matrix33 global_orientation;
 mActor->getCMassGlobalOrientation().getRowMajor(global_orientation.ptr());
 return global_orientation;
}

void Actor::setMass(Real mass)
{
 mActor->setMass(mass);
}

Real Actor::getMass() const
{
 return mActor->getMass();
}

void Actor::setMassSpaceInertiaTensor(const Vec3& vec)
{
 mActor->setMassSpaceInertiaTensor(vec.as<NxVec3>());
}

Vec3 Actor::getMassSpaceInertiaTensor() const
{
 return Vec3(mActor->getMassSpaceInertiaTensor());
}

Matrix33 Actor::getGlobalInertiaTensor() const
{
 Matrix33 matrix33;
 mActor->getGlobalInertiaTensor().getRowMajor(matrix33.ptr());
 return matrix33;
}

Matrix33 Actor::getGlobalInertiaTensorInverse() const
{
 Matrix33 matrix33;
 mActor->getGlobalInertiaTensorInverse().getRowMajor(matrix33.ptr());
 return matrix33;
}

bool Actor::updateMassFromShapes(Real density, Real totalMass) const
{
 return mActor->updateMassFromShapes(density, totalMass);
}

void Actor::setLinearDamping(Real linDamp)
{
 mActor->setLinearDamping(linDamp);
}

Real Actor::getLinearDamping() const
{
 return mActor->getLinearDamping();
}

void Actor::setAngularDamping(Real angDamp)
{
 mActor->setAngularDamping(angDamp);
}

Real Actor::getAngularDamping() const
{
 return mActor->getAngularDamping();
}

void Actor::setLinearVelocity(const Vec3& linVel)
{
 mActor->setLinearVelocity(linVel.as<NxVec3>());
}

void Actor::setAngularVelocity(const Vec3& angVel)
{
 mActor->setAngularVelocity(angVel.as<NxVec3>());
}

Vec3 Actor::getLinearVelocity() const
{
 return Vec3(mActor->getLinearVelocity());
}

Vec3 Actor::getAngularVelocity () const
{
 return Vec3(mActor->getAngularVelocity());
}

void Actor::setMaxAngularVelocity(Real maxAngVel)
{
 mActor->setMaxAngularVelocity(maxAngVel);
}

Real Actor::getMaxAngularVelocity() const
{
 return mActor->getMaxAngularVelocity();
}

void Actor::setCCDMotionThreshold(Real thresh)
{
 mActor->setCCDMotionThreshold(thresh);
}

Real Actor::getCCDMotionThreshold() const
{
 return mActor->getCCDMotionThreshold();
}

void Actor::setLinearMomentum(const Vec3& linMoment)
{
 mActor->setLinearMomentum(linMoment.as<NxVec3>());
}

void Actor::setAngularMomentum(const Vec3& angMoment)
{
 mActor->setAngularMomentum(angMoment.as<NxVec3>());
}

Vec3 Actor::getLinearMomentum() const
{
 return Vec3(mActor->getLinearMomentum());
}

Vec3 Actor::getAngularMomentum() const
{
 return Vec3(mActor->getAngularMomentum());
}

void Actor::addForceAtPos(const Vec3& force, const Vec3& pos, Enums::ForceMode mode, bool wakeup)
{
 mActor->addForceAtPos(force.as<NxVec3>(), pos.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addForceAtLocalPos(const Vec3& force, const Vec3& pos, Enums::ForceMode mode, bool wakeup)
{
 mActor->addForceAtLocalPos(force.as<NxVec3>(), pos.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addLocalForceAtPos(const Vec3& force, const Vec3& pos, Enums::ForceMode mode, bool wakeup)
{
 mActor->addLocalForceAtPos(force.as<NxVec3>(), pos.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addLocalForceAtLocalPos(const Vec3& force, const Vec3& pos, Enums::ForceMode mode, bool wakeup)
{
 mActor->addLocalForceAtLocalPos(force.as<NxVec3>(), pos.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addForce(const Vec3& force, Enums::ForceMode mode, bool wakeup)
{
 mActor->addForce(force.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addLocalForce(const Vec3& force, Enums::ForceMode mode, bool wakeup)
{
 mActor->addLocalForce(force.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addTorque(const Vec3& torque, Enums::ForceMode mode, bool wakeup)
{
 mActor->addTorque(torque.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

void Actor::addLocalTorque(const Vec3& torque, Enums::ForceMode mode, bool wakeup)
{
 mActor->addLocalTorque(torque.as<NxVec3>(), NxForceMode(int(mode)), wakeup);
}

Vec3 Actor::getPointVelocity(const Vec3& point) const
{
 return Vec3(mActor->getPointVelocity(point.as<NxVec3>()));
}

Vec3 Actor::getLocalPointVelocity(const Vec3& point) const
{
 return Vec3(mActor->getLocalPointVelocity(point.as<NxVec3>()));
}

bool Actor::isGroupSleeping() const
{
 return mActor->isGroupSleeping();
}

bool Actor::isSleeping() const
{
 return mActor->isSleeping();
}

Real Actor::getSleepLinearVelocity() const
{
 return mActor->getSleepLinearVelocity();
}

void Actor::setSleepLinearVelocity(Real threshold)
{
 mActor->setSleepLinearVelocity(threshold);
}

Real Actor::getSleepAngularVelocity() const
{
 return mActor->getSleepAngularVelocity();
}

void Actor::setSleepAngularVelocity(Real threshold)
{
 mActor->setSleepAngularVelocity(threshold);
}

Real Actor::getSleepEnergyThreshold() const
{
 return mActor->getSleepEnergyThreshold();
}

void Actor::setSleepEnergyThreshold(Real threshold)
{
 mActor->setSleepEnergyThreshold(threshold);
}

void Actor::wakeUp(Real wakeCounterValue)
{
 mActor->wakeUp(wakeCounterValue);
}

void Actor::putToSleep()
{
 mActor->putToSleep();
}

Compartment* Actor::getCompartment()
{
 return mScene->getCompartment(mActor->getCompartment());
}

unsigned int Actor::linearSweep(const Vec3& motion, unsigned int sweep_flags, unsigned int size, SweepQueryHits& hits, SweepCache* cache)
{

 NxSweepQueryHit* query_hits = (NxSweepQueryHit*) malloc(sizeof(NxSweepQueryHit) * size);

 unsigned int count = mActor->linearSweep(motion.as<NxVec3>(), sweep_flags, 0, size, query_hits, 0, cache->getCache());
 Functions::SweepFunctions::NxSweepQueryHitsToBuffer(query_hits, count, hits);

 free(query_hits);

 return count;
}

String Actor::to_s() const
{
 return String("Actor") ;
}


void Actor::setGlobalPosition(Real x, Real y, Real z)
{
 mActor->setGlobalPosition(NxVec3(x,y,z));
}

void Actor::setGlobalOrientationQuat(Real w, Real x, Real y, Real z)
{
 NxQuat q;
 q.setWXYZ(w,x,y,z);
 mActor->setGlobalOrientationQuat(q);
}

void Actor::setCMassOffsetLocalPosition(Real x, Real y, Real z)
{
 mActor->setCMassOffsetLocalPosition(NxVec3(x,y,z));
}

void Actor::setCMassOffsetGlobalPosition(Real x, Real y, Real z)
{
 mActor->setCMassOffsetGlobalPosition(NxVec3(x,y,z));
}

void Actor::setCMassGlobalPosition(Real x, Real y, Real z)
{
 mActor->setCMassGlobalPosition(NxVec3(x,y,z));
}

void Actor::setLinearVelocity(Real x, Real y, Real z)
{
 mActor->setLinearVelocity(NxVec3(x,y,z));
}

void Actor::setAngularVelocity(Real x, Real y, Real z)
{
 mActor->setAngularVelocity(NxVec3(x,y,z));
}

void Actor::setLinearMomentum(Real x, Real y, Real z)
{
 mActor->setLinearMomentum(NxVec3(x,y,z));
}

void Actor::setAngularMomentum(Real x, Real y, Real z)
{
 mActor->setAngularMomentum(NxVec3(x,y,z));
}

                                                                                       

} // namespace NxOgre

                                                                                       

