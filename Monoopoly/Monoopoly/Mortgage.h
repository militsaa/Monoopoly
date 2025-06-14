#pragma once

class Mortgage {
	double factor;
	int count = 0;
	int price;

public:
	Mortgage(double factor, int price);
	~Mortgage() = default;
	double getFactor() const;
	int getCount() const;
	int getPrice() const;
	virtual void add()=0;
};