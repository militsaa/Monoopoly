#pragma once
#include "Field.h"
#include "Player.h"

class BankField : public Field {
protected:
    int amount;
public:
    BankField(String name, FieldType type, int amount);
    virtual void applyEffect(Player& player)=0;
};