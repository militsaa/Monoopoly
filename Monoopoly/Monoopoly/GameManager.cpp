#include "GameManager.h"

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
