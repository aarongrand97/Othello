#include "othelloBackEnd.cpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(othellolib)
{
    def("makeMove", makeMove);      
}


