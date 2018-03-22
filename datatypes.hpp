/*******************************************************************************************************************//**
 *	@file		datatypes.hpp
 *  @brief		This file holds the needed definitions of custom datatypes used
 *              in this project
 *  @version 	V1.0
 *  @date		22.03.2018
 *	@author		Henry He (Student @ TUM)
 **********************************************************************************************************************/

#ifndef DATATYPES_HPP
#define DATATYPES_HPP

/********************************************//**
 * Includes
 ***********************************************/
#include <vector>
#include <utility>

#include <QObject>

/**
 * @brief   The coordinates datatype is a pair of integers
 *
 * The first integer resembles the x coordinate
 * and the second the y coordinate.
 */
using coordinates = std::pair <int, int>;

/**
 * @brief   The matrix datatype resembles the matchboard
 *
 * It is implemented as a two dimensional vector. The first vector
 * holds the colums while the second holds the rows.
 */
using matrix = std::vector< std::vector<int> >;

/**
 * @brief   The position datatype holds every coordinate where a ship is located
 *
 * It is implemented as a vector of a pair of integers.
 */
using position = std::vector< std::pair<int, int> >;

#endif // DATATYPES_HPP

