#pragma once
#include "BankField.h"

class GoField : public BankField {
public:
    GoField(String name, FieldType type);
    void applyEffect(Player& p) override;
};