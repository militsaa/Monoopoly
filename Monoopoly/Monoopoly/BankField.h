#pragma once
#include "Field.h"
#include "Player.h"

class BankField : public Field {
protected:
    int amount;
    String description;
public:
    BankField(String name, FieldType type, int amount, String description);
    int getAmount() const;
    String getDescription() const;
    virtual int applyEffect(Player& player)=0;
};