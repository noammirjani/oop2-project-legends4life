#include "gameManage/CollisionListener.h"
#include "MovingObject/Player.h"


//------------------------------------------------------
void CollisionListener::BeginContact(b2Contact* contact)
{
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    auto objA = static_cast<GameObject*>(bodyUserDataA);

    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    auto objB = static_cast<GameObject*>(bodyUserDataB);
   
    if ((!objA || !objB)) return;

    CollisionHandler::getInstance().handleCollision(objA, objB);
}


//------------------------------------------------------
void CollisionListener::EndContact(b2Contact* contact)
{
    checkPlayerEndContactWithEnemy(contact);
}


//------------------------------------------------------
void CollisionListener::checkPlayerEndContactWithEnemy(b2Contact* contact)
{
    if (contact->GetFixtureA()->GetFilterData().categoryBits == playerBits && 
        contact->GetFixtureB()->GetFilterData().categoryBits == EnemyBits) {
        void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        auto player = static_cast<Player*>(bodyUserDataA);
        player->setCollideWithEnemy(false);
    }
    if (contact->GetFixtureA()->GetFilterData().categoryBits == EnemyBits &&
        contact->GetFixtureB()->GetFilterData().categoryBits == playerBits) {
        void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
        auto player = static_cast<Player*>(bodyUserDataB);
        player->setCollideWithEnemy(false);
    }
    
}
