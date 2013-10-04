#ifndef EXCEPTIONHANDLER_HPP
#define EXCEPTIONHANDLER_HPP

#include "multiscale/core/Multiscale.hpp"

#include <iostream>
#include <string>

using namespace std;


namespace multiscale {

    //! Exception handler class
    class ExceptionHandler {

        public:

            //! Print the error message
            /*! The error message is printed using the ex.what() method
             *
             * \param ex Exception
             */
            static void printErrorMessage(const exception &ex) {
                cerr << endl << ERR_MSG << endl
                     << endl << ex.what()
                     << endl << endl;
            }

    };

};

#endif
