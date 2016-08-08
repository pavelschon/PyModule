/**
 * @file PyModule.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#include <boost/python.hpp>

#include <iostream>


void greet()
{
    std::cout << "greet from pymodule" << std::endl;
}


BOOST_PYTHON_MODULE( pymodule )
{
    using namespace ::boost::python;

    def( "greet", &greet );
}

