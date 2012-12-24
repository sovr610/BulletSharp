#include "StdAfx.h"

#include "BroadphaseInterface.h"
#include "CollisionConfiguration.h"
#include "CollisionWorld.h"
#include "DiscreteDynamicsWorld.h"
#include "Dispatcher.h"
#include "RigidBody.h"
#ifndef DISABLE_UNCOMMON
#include "SimulationIslandManager.h"
#endif
#ifndef DISABLE_CONSTRAINTS
#include "TypedConstraint.h"
#include "ConstraintSolver.h"
#endif

#define Native static_cast<btDiscreteDynamicsWorld*>(_native)

DiscreteDynamicsWorld::DiscreteDynamicsWorld(btDiscreteDynamicsWorld* world)
: DynamicsWorld(world)
{
}

DiscreteDynamicsWorld::DiscreteDynamicsWorld(BulletSharp::Dispatcher^ dispatcher,
	BroadphaseInterface^ pairCache,
	#ifndef DISABLE_CONSTRAINTS
	BulletSharp::ConstraintSolver^ constraintSolver,
	#endif
	CollisionConfiguration^ collisionConfiguration)
: DynamicsWorld(new btDiscreteDynamicsWorld(dispatcher->UnmanagedPointer,
	pairCache->_native,
	#ifndef DISABLE_CONSTRAINTS
	GetUnmanagedNullable(constraintSolver),
	#else
	0,
	#endif
	collisionConfiguration->_native))
{
	_collisionConfiguration = collisionConfiguration;
	_dispatcher = dispatcher;
	_broadphase = pairCache;
}

void DiscreteDynamicsWorld::ApplyGravity()
{
	Native->applyGravity();
}

#if !defined(DISABLE_CONSTRAINTS) && !defined (DISABLE_DEBUGDRAW)
void DiscreteDynamicsWorld::DebugDrawConstraint(TypedConstraint^ constraint)
{
	Native->debugDrawConstraint(constraint->UnmanagedPointer);
}
#endif

bool DiscreteDynamicsWorld::ApplySpeculativeContactRestitution::get()
{
	return Native->getApplySpeculativeContactRestitution();
}
void DiscreteDynamicsWorld::ApplySpeculativeContactRestitution::set(bool value)
{
	return Native->setApplySpeculativeContactRestitution(value);
}

CollisionWorld^ DiscreteDynamicsWorld::CollisionWorld::get()
{
	return gcnew BulletSharp::CollisionWorld(Native->getCollisionWorld());
}

#ifndef DISABLE_UNCOMMON
SimulationIslandManager^ DiscreteDynamicsWorld::SimulationIslandManager::get()
{
	return gcnew BulletSharp::SimulationIslandManager(Native->getSimulationIslandManager());
}
#endif

void DiscreteDynamicsWorld::SetNumTasks(int numTasks)
{
	Native->setNumTasks(numTasks);
}

bool DiscreteDynamicsWorld::SynchronizeAllMotionStates::get()
{
	return Native->getSynchronizeAllMotionStates();
}
void DiscreteDynamicsWorld::SynchronizeAllMotionStates::set(bool value)
{
	return Native->setSynchronizeAllMotionStates(value);
}

void DiscreteDynamicsWorld::SynchronizeSingleMotionState(RigidBody^ body)
{
	Native->synchronizeSingleMotionState((btRigidBody*)body->_native);
}
