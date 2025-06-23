#include "Station.h"
#include "Constants.h"
#include "GameManager.h"

Station::Station(String name, FieldType field, PropertyType type) : Property(name, field, type, STATION_PRICE), baseRent(STATION_BASE_RENT){}

Station* Station::clone() const
{
	return new Station(*this);
}

int Station::rent() const
{
	GameManager& gm = GameManager::getInstance();
	int cnt = 0;
	Station* curr;
	for (size_t i = 0; i < STATION_COUNT; i++)
	{
		curr = static_cast<Station*>(gm.getFields()[STATIONS_INDEXES[i]]);
		if (owner == curr->getOwner())
		{
			cnt++;
		}
	}
	return baseRent * cnt;
}
