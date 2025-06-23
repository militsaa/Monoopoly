#include "Board.h"
#include "BuildableProperty.h"
#include "TaxField.h"
#include "GoField.h"
#include "DeadField.h"
#include "Station.h"
#include "CardField.h"

Board::Board()
{
	fields.push_back(new GoField("Go", FieldType::GO, 200));
	fields.push_back(new BuildableProperty("Old Kent Road", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 60,Neighbourhood::BROWN, 2));
	fields.push_back(new CardField("Community chest", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Whitechapel Road", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 60, Neighbourhood::BROWN, 4));
	fields.push_back(new TaxField("INCOME TAX", FieldType::TAXFIELD, 200));
	fields.push_back(new Station("Marylebone Station", FieldType::PROPERTY, PropertyType::STATION));
	fields.push_back(new BuildableProperty("The Angel Islington", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY,100, Neighbourhood::LIGTHBLUE, 6));
	fields.push_back(new CardField("Chance", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Euston Road", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 100, Neighbourhood::LIGTHBLUE, 6));
	fields.push_back(new BuildableProperty("Pentonville Road", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 120, Neighbourhood::LIGTHBLUE, 8));

	fields.push_back(new DeadField("In Jail \n Vising", FieldType::JAIL));
	fields.push_back(new BuildableProperty("Pall Mall", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 140, Neighbourhood::PINK, 10));
	fields.push_back(new Property("Electric Company", FieldType::PROPERTY, PropertyType::UTILITY, 150));
	fields.push_back(new BuildableProperty("Whitehall", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 140, Neighbourhood::PINK, 10));
	fields.push_back(new BuildableProperty("Northumberland Ave", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 160, Neighbourhood::PINK, 12));
	fields.push_back(new Station("Fenchurch Street Stat.", FieldType::PROPERTY, PropertyType::STATION));
	fields.push_back(new BuildableProperty("Bow Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 180, Neighbourhood::ORANGE, 14));
	fields.push_back(new CardField("Community chest", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Marlborough Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 180, Neighbourhood::ORANGE, 14));
	fields.push_back(new BuildableProperty("Vine Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 200, Neighbourhood::ORANGE, 16));

	fields.push_back(new DeadField("PARKING", FieldType::PARKING));
	fields.push_back(new BuildableProperty("Strand", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 220, Neighbourhood::RED, 18));
	fields.push_back(new CardField("Chance", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Fleet Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 220, Neighbourhood::RED, 18));
	fields.push_back(new BuildableProperty("Trafalgar Square", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 240, Neighbourhood::RED, 20));
	fields.push_back(new Station("King's Cross Station", FieldType::PROPERTY, PropertyType::STATION));
	fields.push_back(new BuildableProperty("Leicester Square", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 260, Neighbourhood::YELLOW, 22));
	fields.push_back(new BuildableProperty("Coventry Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 260, Neighbourhood::YELLOW, 22));
	fields.push_back(new Property("Water Works", FieldType::PROPERTY, PropertyType::UTILITY, 150));
	fields.push_back(new BuildableProperty("Piccadilly", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 280, Neighbourhood::YELLOW, 24));

	fields.push_back(new DeadField("GO TO JAIL!", FieldType::GOTOJAIL));
	fields.push_back(new BuildableProperty("Regent Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 300, Neighbourhood::GREEN, 26));
	fields.push_back(new BuildableProperty("Oxford Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 300, Neighbourhood::GREEN, 26));
	fields.push_back(new CardField("Community chest", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Bond Street", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 320, Neighbourhood::GREEN, 28));
	fields.push_back(new Station("Liverpool Street Stat.", FieldType::PROPERTY, PropertyType::STATION));
	fields.push_back(new CardField("Chance", FieldType::CARDFIELD));
	fields.push_back(new BuildableProperty("Park Lane", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 350, Neighbourhood::DARKBLUE, 35));
	fields.push_back(new TaxField("SUPER TAX", FieldType::TAXFIELD, 100));
	fields.push_back(new BuildableProperty("Mayfair", FieldType::PROPERTY, PropertyType::BUILDABLE_PROPERTY, 400, Neighbourhood::DARKBLUE, 50));
}

Board::~Board()
{
	for (size_t i = 0; i < fields.getSize(); i++)
	{
		delete fields[i];
	}

}

Board& Board::getInstance()
{
	static Board instance;
	return instance;
}

Vector<Field*> Board::getFields() const
{
	return fields;
}

