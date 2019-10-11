#include "Map.h"


int MapDriver::RunMapDriver()
{
	cout << "Welcome to Command Line Risk! (comp345 - Assignment 1)" << endl << endl;

	// creation of a Map object
	Map map;

	// add the continents
	map.add_continents(1, "azio", 5);
	map.add_continents(2, "ameroki", 10);
	map.add_continents(3, "utropa", 10);
	map.add_continents(4, "amerpoll", 5);
	map.add_continents(5, "afrori", 5);
	map.add_continents(6, "ulstrailia", 5);

	// add the countries
	map.add_country(1, "siberia", 1);
	map.add_country(2, "worrick", 1);
	map.add_country(3, "yazteck", 1);
	map.add_country(4, "kongrolo", 1);
	map.add_country(5, "china", 1);
	map.add_country(6, "middle_east", 1);
	map.add_country(7, "sluci", 1);
	map.add_country(8, "afganistan", 1);
	map.add_country(9, "kancheria", 1);
	map.add_country(10, "india", 1);
	map.add_country(11, "japan", 1);
	map.add_country(12, "new_guinia", 6);
	map.add_country(13, "western_ulstrailia", 6);
	map.add_country(14, "eastern_ulstarilia", 6);
	map.add_country(15, "jacuncail", 6);
	map.add_country(16, "tungu", 5);
	map.add_country(17, "south_afrori", 5);
	map.add_country(18, "north_afrori", 5);
	map.add_country(19, "east_afrori", 5);
	map.add_country(20, "egypt", 5);
	map.add_country(21, "maganar", 5);
	map.add_country(22, "pero", 4);
	map.add_country(23, "heaurt", 4);
	map.add_country(24, "vagnagale", 4);
	map.add_country(25, "argentina", 4);
	map.add_country(26, "ireland", 3);
	map.add_country(27, "ihesia", 3);
	map.add_country(28, "western_utropa", 3);
	map.add_country(29, "souther_utropa", 3);
	map.add_country(30, "northern_utropa", 3);
	map.add_country(31, "senadlavin", 3);
	map.add_country(32, "great_britain", 3);
	map.add_country(33, "teramar", 2);
	map.add_country(34, "western_united_states", 2);
	map.add_country(35, "czeck", 2);
	map.add_country(36, "alberta", 2);
	map.add_country(37, "central_ameroki", 2);
	map.add_country(38, "albania", 2);
	map.add_country(39, "duiestie", 2);
	map.add_country(40, "Quebeck", 2);
	map.add_country(41, "vinenlant", 2);
	map.add_country(42, "heal", 1);

	// add the neighbors of each countries
	
	// Create iterator pointing to first element of the countries list
	list<Country>::iterator it = map.getCountries()->begin();
	it->add_edge("1 20 32 2");
	std::advance(it, 1);
	it->add_edge("2 1 10 35 3");
	std::advance(it, 1);
	it->add_edge("3 2 4 6 35");
	std::advance(it, 1);
	it->add_edge("4 3 35 5 6");
	std::advance(it, 1);
	it->add_edge("5 4 6 42 7 9");
	std::advance(it, 1);
	it->add_edge("6 3 5 9 4");
	std::advance(it, 1);
	it->add_edge("7 5 9 8");
	std::advance(it, 1);
	it->add_edge("8 9 7");
	std::advance(it, 1);
	it->add_edge("9 5 8 7 6 10");
	std::advance(it, 1);
	it->add_edge("10 11 2 9");
	std::advance(it, 1);
	it->add_edge("11 17 10");
	std::advance(it, 1);
	it->add_edge("12 15 13");
	std::advance(it, 1);
	it->add_edge("13 15 14 12");
	std::advance(it, 1);
	it->add_edge("14 15 13");
	std::advance(it, 1);
	it->add_edge("15 17 12 13 14");
	std::advance(it, 1);
	it->add_edge("16 18 17 19");
	std::advance(it, 1);
	it->add_edge("17 16 15 11");
	std::advance(it, 1);
	it->add_edge("18 20 19 16");
	std::advance(it, 1);
	it->add_edge("19 18 21 16");
	std::advance(it, 1);
	it->add_edge("20 23 1 18");
	std::advance(it, 1);
	it->add_edge("21 19 27");
	std::advance(it, 1);
	it->add_edge("22 24 23");
	std::advance(it, 1);
	it->add_edge("23 22 24 20");
	std::advance(it, 1);
	it->add_edge("24 25 22 23");
	std::advance(it, 1);
	it->add_edge("25 30 24");
	std::advance(it, 1);
	it->add_edge("26 27 31");
	std::advance(it, 1);
	it->add_edge("27 26 28 21 31");
	std::advance(it, 1);
	it->add_edge("28 27 31 29 32 30");
	std::advance(it, 1);
	it->add_edge("29 28 32 30");
	std::advance(it, 1);
	it->add_edge("30 28 25 29");
	std::advance(it, 1);
	it->add_edge("31 28 34 32 26 27");
	std::advance(it, 1);
	it->add_edge("32 28 1 34 29 31");
	std::advance(it, 1);
	it->add_edge("33 34 36");
	std::advance(it, 1);
	it->add_edge("34 38 35 33 36 37 31 32");
	std::advance(it, 1);
	it->add_edge("35 2 4 38 34 3");
	std::advance(it, 1);
	it->add_edge("36 34 37 41 33 39");
	std::advance(it, 1);
	it->add_edge("37 40 38 34 36 39");
	std::advance(it, 1);
	it->add_edge("38 40 35 34 37");
	std::advance(it, 1);
	it->add_edge("39 40 37 41 36");
	std::advance(it, 1);
	it->add_edge("40 42 39 37 38");
	std::advance(it, 1);
	it->add_edge("41 36 39");
	std::advance(it, 1);
	it->add_edge("42 5 40");

	list<Country>::iterator iter;
	for (iter = map.getCountries()->begin(); iter != map.getCountries()->end(); ++iter)
	{
		iter->printCountry();
		cout << endl;
	}

	cout << endl;
	map.ConnectedGraph();
	map.ConnectedSubgraph();
	
	// each country belongs to one and only one continent.
	for (iter = map.getCountries()->begin(); iter != map.getCountries()->end(); ++iter)
	{
		cout << "Country " << *iter->getCountryName() << " belongs to Continent " << *iter->getCountryContinent() << endl;
	}
	

	return 0;
}

