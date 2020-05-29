#ifndef CAR_EXAMPLE_MANAGER_H
#define CAR_EXAMPLE_MANAGER_H

#include <vector>
#include <string>
#include "sCars.h"
#include "GameObject.h"
#include "Creator.h"

class Manager {
protected:
    std::vector<Creator*> carTypes;
    std::vector<GameObject*> gameObjects;

public:

    void Update() {
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive) gameObject->UpdateObject();
        }
    }

    void Draw() {
        for (auto& gameObject : gameObjects) {
            if (gameObject->isActive) gameObject->Draw();
        }
    }

    template <typename T1, typename T2>
    void RegisterCarType(T2 arg) {
        T1 *car = new T1();
        //Manipulation on type
        car->SetTextures(arg);
        //Store in manager array
        carTypes.emplace_back(car);
    }

    void SpawnCar() {
        if (!carTypes.size()) return;

        std::srand(std::time(nullptr));
        auto n = std::rand() % carTypes.size();
        auto *car = carTypes[n]->GetObject();
        //Manipulation on car
        car->transform.x = 50;
        car->transform.y = 50;
        car->transform.width = 70;
        car->transform.height = 165;
        car->transform.direction = eDirection::DOWN;
        car->Refill(20);
        //Store in manager array
        gameObjects.emplace_back(car);
    }

    void SpawnCar(int n) {
        for (int i = 0; i < n; i++) SpawnCar();
    }

};


#endif //CAR_EXAMPLE_MANAGER_H
