#pragma once
#include "BankField.h"

class GoField : public BankField {
public:
    GoField(String name, FieldType type, int amount);
    void applyEffect(Player& p) override;
    GoField* clone() const override;
};