/*
 * Info.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef INFO_HPP_
#define INFO_HPP_

class Info
{
  public:
    virtual bool update() { return true; };
    virtual ~Info() { }
};



#endif /* INFO_HPP_ */
