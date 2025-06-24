#pragma once
#include "BankField.h"

class GoField : public BankField {
public:
    GoField(String name, FieldType type, int amount, String description);
    int applyEffect(Player& p) override;
    GoField* clone() const override;
};