﻿#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Lesson 1

template <typename T>
class Pair1
{
private:
	T m_first;
	T m_second;
public:
	Pair1(const T& first, const T& second) : m_first(first), m_second(second) { }

	const T& first() const;
	const T& second() const;
};

template <typename T>
const T& Pair1<T>::first() const
{
	return m_first;
}

template <typename T>
const T& Pair1<T>::second() const
{
	return m_second;
}


// lesson 2

template <typename T1, typename T2>
class Pair
{
private:
	T1 m_first;
	T2 m_second;
public:
	Pair(const T1& first, const T2& second) : m_first(first), m_second(second) { }

	const T1& first() const;
	const T2& second() const;
};

template <typename T1, typename T2>
const T1& Pair<T1, T2>::first() const
{
	return m_first;
}

template <typename T1, typename T2>
const T2& Pair<T1, T2>::second() const
{
	return m_second;
}

// lesson 3

template <typename T2>
class StringValuePair : public Pair<std::string, T2>
{
public:
	StringValuePair(const std::string& first, const T2& second) :
		Pair<std::string, T2>(first, second) {}
};

// lesson 4

class Card
{
public:
	enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

	Card(rank r, suit s, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }

	int GetValue() const
	{
		int value = 0;
		if (m_IsFaceUp)
		{
			value = m_Rank;
			if (value > 10)
				value = 10;
		}
		return value;
	}

	void Flip()
	{
		m_IsFaceUp = !m_IsFaceUp;
	}

	friend std::ostream& operator<<(std::ostream& s, const Card& aCard);

private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};

class Hand
{
public:
	Hand()
	{
		m_Cards.reserve(7);
	}

	virtual ~Hand()
	{
		Clear();
	}

	void Add(Card* pCard)
	{
		m_Cards.push_back(pCard);
	}

	void Clear()
	{
		std::vector<Card*>::iterator iter = m_Cards.begin();
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
		{
			delete* iter;
			*iter = nullptr;
		}

		m_Cards.clear();
	}

	int GetTotal() const
	{
		if (m_Cards.empty() || m_Cards[0]->GetValue() == 0)
			return 0;

		int total = 0;
		std::vector<Card*>::const_iterator iter;

		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
			total += (*iter)->GetValue();

		bool containsAce = false;
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
			if ((*iter)->GetValue() == Card::ACE)
				containsAce = true;

		if (containsAce && total <= 11) total += 10;

		return total;
	}

protected:
	std::vector<Card*> m_Cards;
};

class GenericPlayer : public Hand
{
private:
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
protected:
	string m_Name;
public:
	GenericPlayer(const string& name = "") : m_Name(name) { }

	virtual ~GenericPlayer();

	virtual bool IsHitting() const = 0;

	bool IsBusted() const
	{
		return (GetTotal() > 21);
	}

	void Bust() const
	{
		cout << m_Name << " перебор.\n";
	}
};


void les_1();
void les_2();
void les_3();

int main()
{
	les_1();
	les_2();
	les_3();

	return 0;
}

void les_1()
{
	Pair1<int> p1(6, 9);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2(3.4, 7.8);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

void les_2()
{
	Pair<int, double> p1(6, 7.8);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2(3.4, 5);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

void les_3()
{
	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}