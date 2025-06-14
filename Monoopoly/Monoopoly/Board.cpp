#include "Board.h"
#include "DeadField.h"
#include "Property.h"
//#include ".h"

Board::Board()
{
	fields.push_back(new DeadField("Go", FieldType::GO, 200));
	fields.push_back(new Property("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 2));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Whitechapel Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 4));
	fields.push_back(new DeadField("INCOME TAX", FieldType::TAXFIELD, -200));
	fields.push_back(new Property("Marylebone Station", FieldType::PROPERTY, Neighbourhood::STATION, 200, 25));
	fields.push_back(new Property("The Angel Islington", FieldType::PROPERTY, Neighbourhood::BROWN, 100, 6));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Euston Road", FieldType::PROPERTY, Neighbourhood::BLUE, 100, 6));
	fields.push_back(new Property("Pentonville Road", FieldType::PROPERTY, Neighbourhood::BLUE, 120, 8));
	fields.push_back(new Field("In jail!", FieldType::JAIL));
	fields.push_back(new Property("Pall Mall", FieldType::PROPERTY, Neighbourhood::PINK, 140, 10));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Whitehall", FieldType::PROPERTY, Neighbourhood::PINK, 140, 10));
	fields.push_back(new Property("Northumberland Ave", FieldType::PROPERTY, Neighbourhood::PINK, 160, 12));
	fields.push_back(new Property("Fenchurch Street Stat.", FieldType::PROPERTY, Neighbourhood::STATION, 200, 25));
	fields.push_back(new Property("Bow Street", FieldType::PROPERTY, Neighbourhood::ORANGE, 180, 14));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Marlborough Street", FieldType::PROPERTY, Neighbourhood::ORANGE, 180, 14));
	fields.push_back(new Property("Vine Street", FieldType::PROPERTY, Neighbourhood::ORANGE, 200, 16));
	fields.push_back(new Field("PARKING!", FieldType::PARKING));
	fields.push_back(new Property("Strand", FieldType::PROPERTY, Neighbourhood::RED, 220, 18));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Fleet Street", FieldType::PROPERTY, Neighbourhood::RED, 220, 18));
	fields.push_back(new Property("Trafalgar Square", FieldType::PROPERTY, Neighbourhood::RED, 240, 20));
	fields.push_back(new Property("King's Cross Station", FieldType::PROPERTY, Neighbourhood::STATION, 200, 25));
	fields.push_back(new Property("Leicester Square", FieldType::PROPERTY, Neighbourhood::YELLOW, 260, 22));
	fields.push_back(new Property("Coventry Street", FieldType::PROPERTY, Neighbourhood::YELLOW, 260, 22));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Piccadilly", FieldType::PROPERTY, Neighbourhood::YELLOW, 280, 24));
	fields.push_back(new Field("GO TO JAIL!", FieldType::GOTOJAIL));
	fields.push_back(new Property("Regent Street", FieldType::PROPERTY, Neighbourhood::GREEN, 300, 26));
	fields.push_back(new Property("Oxford Street", FieldType::PROPERTY, Neighbourhood::GREEN, 300, 26));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Bond Street", FieldType::PROPERTY, Neighbourhood::GREEN, 320, 28));
	fields.push_back(new Property("Liverpool Street Stat.", FieldType::PROPERTY, Neighbourhood::STATION, 200, 25));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Park Lane", FieldType::PROPERTY, Neighbourhood::DARKBLUE, 350, 35));
	//fields.push_back(new DeadField("Old Kent Road", FieldType::PROPERTY, Neighbourhood::BROWN, 60, 0));
	fields.push_back(new Property("Mayfair", FieldType::PROPERTY, Neighbourhood::DARKBLUE, 400, 50));

}
