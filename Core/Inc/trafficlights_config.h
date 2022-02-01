/*
 * trafficlights_config.h
 *
 *  Created on: Feb 1, 2022
 *      Author: mabecker
 */

#ifndef INC_TRAFFICLIGHTS_CONFIG_H_
#define INC_TRAFFICLIGHTS_CONFIG_H_

#include "trafficlights.h"

tl_pedestrian_signal_t pedestrian_west = {
	{2, 3},
	{2, 4},
	{2, 5}
};

tl_pedestrian_signal_t pedestrian_north = {
	{1, 3},
	{1, 4},
	{1, 5}
};

tl_car_signal_t street_north = {
	{0, 3},
	{0, 4},
	{0, 5}
};

tl_car_signal_t street_south = {
	{1, 0},
	{1, 1},
	{1, 2}
};

tl_car_signal_t street_east = {
	{0, 0},
	{0, 1},
	{0, 2}
};

tl_car_signal_t street_west = {
	{2, 0},
	{2, 1},
	{2, 2}
};

tl_street_t crossing[] = {
	{
		NORTH,
		&street_north,
		&pedestrian_north
	},{
		SOUTH,
		&street_south,
		NULL
	},{
		WEST,
		&street_west,
		&pedestrian_west
	},{
		EAST,
		&street_east,
		NULL
	}
};

#endif /* INC_TRAFFICLIGHTS_CONFIG_H_ */
