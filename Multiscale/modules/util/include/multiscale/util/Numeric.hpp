#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include <algorithm>
#include <cfenv>
#include <cmath>
#include <limits>

using namespace std;


namespace multiscale {

    //! Functor representing an addition operation
    class AdditionOperation {

        public:

            //! Add the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 + operand2);
            }

    };

    //! Functor representing a division operation
    class DivisionOperation {

        public:

            //! Divide the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 / operand2);
            }

    };

    //! Functor representing a multiplication operation
    class MultiplicationOperation {

        public:

            //! Multiply the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 * operand2);
            }

    };

    //! Functor representing a subtraction operation
    class SubtractionOperation {

        public:

            //! Subtrace the two operands
            /*!
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operand>
            Operand operator()(Operand operand1, Operand operand2) const {
                return (operand1 - operand2);
            }

    };


    //! Class for manipulating numbers (shorts, ints, floats, doubles etc.)
    class Numeric {

        private:

            static double epsilon;  /*!< Value of epsilon used to compare two real numbers */

        public:

            //! Check if the first number is greater than or equal to the second number
            /*!
             * \param number1 The first number
             * \param number2 The second number
             */
            static bool greaterOrEqual(double number1, double number2);

            //! Check if the first number is less than or equal to the second number
            /*!
             * \param number1 The first number
             * \param number2 The second number
             */
            static bool lessOrEqual(double number1, double number2);

            //! Check if the two numbers are equal (almost)
            /*!
             * The expression for determining if two real numbers are equal is:
             * if (Abs(x - y) <= EPSILON * Max(1.0f, Abs(x), Abs(y))).
             *
             * \param number1 First number
             * \param number2 Second number
             */
            static bool almostEqual(double number1, double number2);

            //! Return the average (arithmetic mean) of the provided numbers
            /*!
             * \f$ average = \frac{1}{n} \sum\limits^{n}_{i = 1}{x_{i}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double average(const std::vector<double> &numbers);

            //! Return the covariance for the provided collections of values
            /*!
             * \param values1   The first collection of values
             * \param values2   The second collection of values
             */
            static double covariance(const std::vector<double> &values1, const std::vector<double> &values2);

            //! Return the geometric mean of the provided numbers
            /*!
             * \f$ geometricMean = e ^ {\frac{1}{n} \sum\limits_{i = 1}^{n}{log(x_{i})}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double geometricMean(const std::vector<double> &numbers);

            //! Return the harmonic mean of the provided numbers
            /*!
             *  \f$ harmonicMean = \frac{n}{\sum\limits_{i = 1}^{n}{\frac{1}{x_{i}}}} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double harmonicMean(const std::vector<double> &numbers);

            //! Return the kurtosis of the provided numbers
            /*!
             * \f$ kurtosis = \frac{n (n + 1)}{(n - 1)(n - 2)(n - 3)} \left( \sum\limits_{i=1}^{n}{(\frac{x_i - mean}{stdev})^{4}} \right) - \frac{3 (n - 1)^{2}} {(n - 2) (n - 3)} \f$
             *
             * \param numbers   The collection of numbers
             */
            static double kurtosis(const std::vector<double> &numbers);

            //! Return the logarithm of a number considering the given base
            /*!
             * The conditions imposed on the number and base are:
             *     - number: a positive real number
             *     - base:   a positive real number different from 1
             *
             *  \param number   The considered number
             *  \param base     The considered base
             */
            static double log(double number, double base);

            //! Return the maximum of the provided numbers
            /*!
             * \param number1 The first number
             * \param number2 The second number
             * \param number3 The third number
             */
            static double maximum(double number1, double number2, double number3);

            //! Return the maximum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double maximum(const std::vector<double> &numbers);

            //! Return the median of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double median(const std::vector<double> &numbers);

            //! Return the mode of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double mode(const std::vector<double> &numbers);

            //! Return the minimum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double minimum(const std::vector<double> &numbers);

            //! Return the p-th percentile of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double percentile(const std::vector<double> &numbers, double percentile);

            //! Return the product of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double product(const std::vector<double> &numbers);

            //! Return the q-th quartile of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double quartile(const std::vector<double> &numbers, double quartile);

            //! Return the skew of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double skew(const std::vector<double> &numbers);

            //! Return the sign of the number
            /*!
             * The sign function returns:
             *  -1, if number < 0
             *  +1, if number > 0
             *  0, otherwise
             *
             *  \param number The considered number
             */
            static int sign(double number);

            //! Return the standard deviation of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double standardDeviation(const std::vector<double> &numbers);

            //! Return the sum of the provided numbers
            /*!
             * \param numbers   The collection of numbers
             */
            static double sum(const std::vector<double> &numbers);

            //! Return the variance of the provided set of values
            /*!
             * \param numbers   The collection of values
             */
            static double variance(const std::vector<double> &numbers);

        private:

            //! Compute the kurtosis first term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisFirstTerm(int nrOfValues);

            //! Compute the kurtosis middle term considering the given values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double computeKurtosisMiddleTerm(const std::vector<double> &values, int nrOfValues);

            //! Compute the kurtosis last term considering the given number of values
            /*!
             * \param nrOfValues The number of values
             */
            static double computeKurtosisLastTerm(int nrOfValues);

            //! Compute the quartile for the given collection of values
            /*!
             * \param quartile  The quartile
             * \param values    The collection of values
             * \param nrOfValue The number of values in the collection
             */
            static double computeQuartileValue(double quartile, const std::vector<double> &values, int nrOfValues);

            //! Return the skew first term considering the given values
            /*!
             * \param numbers   The collection of numbers
             */
            static double computeSkewFirstTerm(int nrOfValues);

            //! Return the skew last term considering the given values
            /*!
             * \param numbers   The collection of numbers
             */
            static double computeSkewLastTerm(const std::vector<double> &numbers, int nrOfValues);

            //! Compute the mode for the provided values
            /*!
             * \param values        The values
             * \param nrOfValues    The number of values
             */
            static double mode(const std::vector<double> &values, int nrOfValues);

            //! Apply the operation on the given operands and throw an exception in case of overflow
            /*!
             * \param operation The operation
             * \param operand1  The first operand
             * \param operand2  The second operand
             */
            template <typename Operation, typename Operand>
            static Operand applyOperation(Operation operation, Operand operand1, Operand operand2) {
                resetOverflowUnderflowFlags();

                Operand result = operation(operand1, operand2);

                if (areOverflowUnderflowFlagsSet()) {

                }

                return result;
            }

            //! Reset the overflow and underflow flags
            static void resetOverflowUnderflowFlags();

            //! Reset the overflow and underflow flags
            static bool areOverflowUnderflowFlagsSet();

            //! Check if the number and the base are positive real numbers, and the base is additionally different from 1
            /*!
             * \param number    The considered number
             * \param base      The considered base
             */
            static void validateLogNumberAndBase(double number, double base);

            //! Check if the number is a positive real number
            /*!
             * \param number    The considered number
             */
            static void validateLogNumber(double number);

            //! Check if the base is a positive real number different from 1
            /*!
             * \param base      The considered base
             */
            static void validateLogBase(double base);

            //! Check if the value of the percentile is between 0 and 100
            /*!
             * \param percentile    The percentile value
             */
            static void validatePercentile(double percentile);

            //! Check if the value of the quartile is either 25, 50 or 75
            /*!
             * \param quartile    The quartile value
             */
            static void validateQuartile(double quartile);

            //! Check if the given number is positive
            /*!
             * \param number The given number
             */
            template <typename T>
            static bool isPositive(T number) {
                return (number > 0);
            }


            // Constants
            static const std::string ERR_LOG_BASE_START;
            static const std::string ERR_LOG_BASE_END;
            static const std::string ERR_LOG_NUMBER_START;
            static const std::string ERR_LOG_NUMBER_END;

            static const std::string ERR_OVERFLOW_UNDERFLOW;

            static const std::string ERR_PERCENTILE_VALUE_START;
            static const std::string ERR_PERCENTILE_VALUE_END;

            static const std::string ERR_QUARTILE_VALUE_START;
            static const std::string ERR_QUARTILE_VALUE_END;

    };

};

#endif
