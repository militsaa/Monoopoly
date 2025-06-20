#include "GameManager.h"
#include "Property.h"

//void GameManager::buildCottage(int index)
//{
//	/*if (board.getFields()[index]->getType() == FieldType::PROPERTY &&)
//	{
//
//	}*/
//}

GameManager::GameManager()
{
    //TO DO?
}

bool GameManager::canBuild(int fieldInd, Property& prop) const
{
    if (!prop.isBought() || !prop.isOwnedBy(*players[currPlayer]) ||
        prop.getHasCastle() || prop.getCottageCount() != 4)
        return false;

    Vector<Property*> neighb;
    collectNeighbour(neighb, fieldInd);
    

    for (size_t i = 0; i < neighb.getSize(); ++i)
        if (!neighb[i]->isOwnedBy(*players[currPlayer]) || neighb[i]->getHasCastle() ||
            neighb[i]->getCottageCount() != 4)
            return false;

    return true;
}

void GameManager::collectNeighbour(Vector<Property*>& nb, int fieldInd)
{
    Field* baseF = board.getFields()[fieldInd];
    Property* base = static_cast<Property*>(baseF);
    Neighbourhood colour = base->getNeighbourhood();

    nb.push_back(base);
    //TO DO DOWN LOGIC
    const int left = idxBase >= 2 ? idxBase - 2 : 0;
    const int right = idxBase + 2 < FIELDS_COUNT ? idxBase + 2
        : FIELDS_COUNT - 1;

    int curr = fieldInd;
    for (int i = -3; i <= 3; ++i) {
        //out of range dont check it
        if () continue;

        Field* f = board.getFields()[i];
        if (f->getType() == FieldType::PROPERTY) {
            Property* p = static_cast<Property*>(f);
            if (p->getNeighbourhood() == col)
                out.push_back(p);
        }
    }
}


GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

Vector<Player*> GameManager::getPlayers() const
{
    return players;
}

Vector<Field*> GameManager::getFields() const
{
    return board.getFields();
}

bool GameManager::buildCottage(Player& player, int idx)
{
    Property* prop = static_cast<Property*>(board.getFields()[idx]);

    if (prop->getHasCastle() || prop->getCottageCount() == 4 || !prop->isOwnedBy(player) || player.getBalance() < prop->getCottagePrice()) {
        return false;
    }

    Vector<Property*> same;
    collectSameColourProps(same, idx);

    if (!ownsWholeSet(p, same))                                    return false;
    if (!evenBuildRuleRespected(*prop, same))                      return false;

    prop->addCottage();
    return true;
}



