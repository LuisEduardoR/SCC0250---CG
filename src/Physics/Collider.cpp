/*
 * Copyright 2018 Amanda de Moura Peres
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "Collider.hpp"
//#include "RectCollider.hpp"
#include "CircleCollider.hpp"
#include "../Components/Moveable.hpp"
#include "../Components/Transform.hpp"
#include "../Time/Time.hpp"

#include <algorithm>
#include <iostream>

using namespace Adven;

std::forward_list<Collider*> Collider::colliders;
/*
    Static methods
*/
void Collider::Register(Collider& collider)
{
    colliders.push_front(&collider);
}
void Collider::Unregister(Collider& collider)
{
    colliders.remove(&collider);
}
void Collider::Update()
{
    for (auto i = colliders.begin(); i != colliders.end(); ++i)
    {
        for (auto j = ++colliders.begin(); j != colliders.end(); ++j)
        {
            if (i == j) continue;

            auto* colliderI = *i;
            auto* colliderJ = *j;

            if (CheckCollision(*colliderI, *colliderJ))
            {
                std::cout << "Trigger\n";
                colliderI->onCollision.Raise(colliderI, colliderJ);
                colliderJ->onCollision.Raise(colliderJ, colliderI);
                
                if (!colliderJ->isTrigger && !colliderI->isTrigger)
                {
                    std::cout << "Collision\n";
                    Moveable* mc = colliderI->GetGameObject()->GetComponent<Moveable>();
                    Transform* tc = colliderI->GetGameObject()->GetComponent<Transform>();
                    if (mc)
                    {
                        tc->localPosition -= mc->speed * Time::DeltaTime;
                        mc->speed = Vector3();
                    }

                    Moveable* ml = colliderJ->GetGameObject()->GetComponent<Moveable>();
                    Transform* tl = colliderJ->GetGameObject()->GetComponent<Transform>();
                    if (ml)
                    {
                        tl->localPosition -= ml->speed * Time::DeltaTime;
                        ml->speed = Vector3();
                    }
                }
            }
        }
    }
}
bool Collider::CheckCollision(const Collider& a, const Collider& b)
{
    //if (typeid(a) == typeid(RectCollider) && typeid(b) == typeid(RectCollider))
    //    return RectCollider::CheckCollision(reinterpret_cast<const RectCollider&>(a), reinterpret_cast<const RectCollider&>(b));
    if (typeid(a) == typeid(CircleCollider) && typeid(b) == typeid(CircleCollider))
        return CircleCollider::CheckCollision(reinterpret_cast<const CircleCollider&>(a), reinterpret_cast<const CircleCollider&>(b));
    else
    {
        //Debug::Error("Collider::CheckCollision failed to identify collider type");
        return false;
    }
}


Collider::Collider(bool isTrigger) : isTrigger(isTrigger) {}

Event<void(Collider*, Collider*)>& Collider::OnCollision()
{
    return onCollision;    
}
