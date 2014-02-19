#ifndef PARSERGRAMMAR_HPP
#define PARSERGRAMMAR_HPP

#include "multiscale/verification/spatial-temporal/attribute/SynthesizedAttribute.hpp"
#include "multiscale/verification/spatial-temporal/handler/ProbabilityErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/handler/UnexpectedTokenErrorHandler.hpp"
#include "multiscale/verification/spatial-temporal/parsing/SymbolTables.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/qi_and_predicate.hpp>

#include <string>


namespace multiscale {

    namespace verification {

        // Namespace aliases
        namespace phoenix = boost::phoenix;
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;

        // Create a lazy error handler function
        phoenix::function<UnexpectedTokenErrorHandler> const    handleUnexpectedTokenError     = UnexpectedTokenErrorHandler();
        phoenix::function<ProbabilityErrorHandler> const        handleProbabilityError         = ProbabilityErrorHandler();


        //! The grammar for parsing (P)BLSTL spatial-temporal logical queries
        template <typename Iterator>
        class ParserGrammar : public qi::grammar<Iterator, ProbabilisticLogicPropertyAttribute(), ascii::space_type> {

            private:

                // Rules

                qi::rule<Iterator, ProbabilisticLogicPropertyAttribute(), ascii::space_type>        probabilisticLogicPropertyRule;         /*!< The rule for parsing a probabilistic logic property */
                qi::rule<Iterator, double(), ascii::space_type>                                     probabilityRule;                        /*!< The rule for parsing a probability */
                qi::rule<Iterator, LogicPropertyAttribute(), ascii::space_type>                     logicPropertyRule;                      /*!< The rule for parsing a logic property */

                qi::rule<Iterator, PrimaryLogicPropertyAttribute(), ascii::space_type>              primaryLogicPropertyRule;               /*!< The rule for parsing a primary logic property */
                qi::rule<Iterator, DifferenceAttribute(), ascii::space_type>                        differenceRule;                         /*!< The rule for parsing a difference attribute */
                qi::rule<Iterator, NumericNumericComparisonAttribute(), ascii::space_type>          numericNumericComparisonRule;           /*!< The rule for parsing a numeric numeric comparison */
                qi::rule<Iterator, NumericSpatialNumericComparisonAttribute(), ascii::space_type>   numericSpatialNumericComparisonRule;    /*!< The rule for parsing a numeric spatial numeric comparison */
                qi::rule<Iterator, NotLogicPropertyAttribute(), ascii::space_type>                  notLogicPropertyRule;                   /*!< The rule for parsing a "not" logic property */
                qi::rule<Iterator, FutureLogicPropertyAttribute(), ascii::space_type>               futureLogicPropertyRule;                /*!< The rule for parsing a "future" logic property */
                qi::rule<Iterator, GlobalLogicPropertyAttribute(), ascii::space_type>               globalLogicPropertyRule;                /*!< The rule for parsing a "global" logic property */
                qi::rule<Iterator, NextLogicPropertyAttribute(), ascii::space_type>                 nextLogicPropertyRule;                  /*!< The rule for parsing an "next" logic property */
                qi::rule<Iterator, NextKLogicPropertyAttribute(), ascii::space_type>                nextKLogicPropertyRule;                 /*!< The rule for parsing an "next K" logic property */

                qi::rule<Iterator, AndLogicPropertyAttribute(), ascii::space_type>                  andLogicPropertyRule;                   /*!< The rule for parsing an "and" logic property */
                qi::rule<Iterator, OrLogicPropertyAttribute(), ascii::space_type>                   orLogicPropertyRule;                    /*!< The rule for parsing an "or" logic property */
                qi::rule<Iterator, ImplicationLogicPropertyAttribute(), ascii::space_type>          implicationLogicPropertyRule;           /*!< The rule for parsing an "implication" logic property */
                qi::rule<Iterator, EquivalenceLogicPropertyAttribute(), ascii::space_type>          equivalenceLogicPropertyRule;           /*!< The rule for parsing an "equivalence" logic property */
                qi::rule<Iterator, UntilLogicPropertyAttribute(), ascii::space_type>                untilLogicPropertyRule;                 /*!< The rule for parsing an "until" logic property */

                qi::rule<Iterator, NumericMeasureAttribute(), ascii::space_type>                    numericMeasureRule;                     /*!< The rule for parsing a numeric measure */
                qi::rule<Iterator, UnaryNumericNumericAttribute(), ascii::space_type>               unaryNumericNumericRule;                /*!< The rule for parsing a unary numeric numeric attribute */
                qi::rule<Iterator, BinaryNumericNumericAttribute(), ascii::space_type>              binaryNumericNumericRule;               /*!< The rule for parsing a binary numeric numeric attribute */

                qi::rule<Iterator, NumericSpatialAttribute(), ascii::space_type>                    numericSpatialRule;                     /*!< The rule for parsing a numeric spatial measure */
                qi::rule<Iterator, UnarySubsetAttribute(), ascii::space_type>                       unarySubsetRule;                        /*!< The rule for parsing a unary subset */
                qi::rule<Iterator, BinarySubsetAttribute(), ascii::space_type>                      binarySubsetRule;                       /*!< The rule for parsing a binary subset */
                qi::rule<Iterator, TernarySubsetAttribute(), ascii::space_type>                     ternarySubsetRule;                      /*!< The rule for parsing a ternary subset */
                qi::rule<Iterator, QuaternarySubsetAttribute(), ascii::space_type>                  quaternarySubsetRule;                   /*!< The rule for parsing a quaternary subset */

                qi::rule<Iterator, UnarySubsetMeasureAttribute(), ascii::space_type>                unarySubsetMeasureRule;                 /*!< The rule for parsing a unary subset measure */
                qi::rule<Iterator, BinarySubsetMeasureAttribute(), ascii::space_type>               binarySubsetMeasureRule;                /*!< The rule for parsing a binary subset measure */
                qi::rule<Iterator, TernarySubsetMeasureAttribute(), ascii::space_type>              ternarySubsetMeasureRule;               /*!< The rule for parsing a ternary subset measure */
                qi::rule<Iterator, QuaternarySubsetMeasureAttribute(), ascii::space_type>           quaternarySubsetMeasureRule;            /*!< The rule for parsing a quaternary subset measure */

                qi::rule<Iterator, UnaryNumericMeasureAttribute(), ascii::space_type>               unaryNumericMeasureRule;                /*!< The rule for parsing a unary numeric measure */
                qi::rule<Iterator, BinaryNumericMeasureAttribute(), ascii::space_type>              binaryNumericMeasureRule;               /*!< The rule for parsing a binary numeric measure */

                qi::rule<Iterator, SubsetAttribute(), ascii::space_type>                            subsetRule;                             /*!< The rule for parsing a subset */
                qi::rule<Iterator, FilterSubsetAttribute(), ascii::space_type>                      filterSubsetRule;                       /*!< The rule for parsing a subset filter */
                qi::rule<Iterator, SubsetSpecificAttribute(), ascii::space_type>                    subsetSpecificRule;                     /*!< The rule for parsing a specific subset */

                qi::rule<Iterator, ConstraintAttribute(), ascii::space_type>                        constraintRule;                         /*!< The rule for parsing a constraint */

                qi::rule<Iterator, PrimaryConstraintAttribute(), ascii::space_type>                 primaryConstraintRule;                  /*!< The rule for parsing a primary constraint */
                qi::rule<Iterator, NotConstraintAttribute(), ascii::space_type>                     notConstraintRule;                      /*!< The rule for parsing a "not" constraint */
                qi::rule<Iterator, UnaryConstraintAttribute(), ascii::space_type>                   unaryConstraintRule;                    /*!< The rule for parsing a unary constraint */

                qi::rule<Iterator, AndConstraintAttribute(), ascii::space_type>                     andConstraintRule;                      /*!< The rule for parsing an "and" constraint */
                qi::rule<Iterator, OrConstraintAttribute(), ascii::space_type>                      orConstraintRule;                       /*!< The rule for parsing an "or" constraint */
                qi::rule<Iterator, ImplicationConstraintAttribute(), ascii::space_type>             implicationConstraintRule;              /*!< The rule for parsing an "implication" constraint */
                qi::rule<Iterator, EquivalenceConstraintAttribute(), ascii::space_type>             equivalenceConstraintRule;              /*!< The rule for parsing an "equivalence" constraint */

                qi::rule<Iterator, SpatialMeasureAttribute(), ascii::space_type>                    spatialMeasureRule;                     /*!< The rule for parsing a spatial measure */

                qi::rule<Iterator, ComparatorAttribute(), ascii::space_type>                        comparatorRule;                         /*!< The rule for parsing a comparator */

                qi::rule<Iterator, NumericStateVariableAttribute(), ascii::space_type>              numericStateVariableRule;               /*!< The rule for parsing a numeric state variable */
                qi::rule<Iterator, StateVariableAttribute(), ascii::space_type>                     stateVariableRule;                      /*!< The rule for parsing a state variable */
                qi::rule<Iterator, std::string(), ascii::space_type>                                stateVariableNameRule;                  /*!< The rule for parsing the name of a state variable without escaping white space */

                // Enumeration parsers

                UnarySubsetMeasureTypeParser        unarySubsetMeasureTypeParser;       /*!< The unary subset measure type parser */
                BinarySubsetMeasureTypeParser       binarySubsetMeasureTypeParser;      /*!< The binary subset measure type parser */
                TernarySubsetMeasureTypeParser      ternarySubsetMeasureTypeParser;     /*!< The ternary subset measure type parser */
                QuaternarySubsetMeasureTypeParser   quaternarySubsetMeasureTypeParser;  /*!< The quaternary subset measure type parser */

                UnaryNumericMeasureTypeParser       unaryNumericMeasureTypeParser;      /*!< The unary numeric measure type parser */
                BinaryNumericMeasureTypeParser      binaryNumericMeasureTypeParser;     /*!< The binary numeric measure type parser */

                SubsetSpecificTypeParser            subsetSpecificTypeParser;           /*!< The subset specific type parser */

                SpatialMeasureTypeParser            spatialMeasureTypeParser;           /*!< The spatial measure type parser */

                ComparatorTypeParser                comparatorTypeParser;               /*!< The comparator type parser */

            public:

                ParserGrammar() : ParserGrammar::base_type(probabilisticLogicPropertyRule) {
                    initialise();
                }

            private:

                //! Initialisation function
                void initialise() {
                    initialiseGrammar();
                    initialiseDebugSupport();
                    initialiseErrorHandlingSupport();
                }

                //! Initialise the grammar
                void initialiseGrammar() {
                    initialiseLogicPropertiesRules();
                    initialiseNumericMeasureRule();
                    initialiseNumericSpatialMeasureRule();
                    initialiseNumericSpatialSubsetMeasureRule();
                    initialiseNaryNumericMeasureRule();
                    initialiseSubsetRule();
                    initialiseConstraintsRules();
                    initialiseSpatialMeasureRule();
                    initialiseComparatorRule();
                    initialiseNumericStateVariableRule();
                }

                //! Initialise the logic properties rules
                void initialiseLogicPropertiesRules() {
                    initialiseProbabilisticLogicPropertyRule();
                    initialiseLogicPropertyRule();
                    initialisePrimaryLogicPropertyRule();
                    initialiseComposedLogicPropertyRule();
                }

                //! Initialise the constraints rules
                void initialiseConstraintsRules() {
                    initialiseConstraintRule();
                    initialisePrimaryConstraintRule();
                    initialiseComposedConstraintRule();
                }

                //! Initialise the probabilistic logic property rule
                void initialiseProbabilisticLogicPropertyRule() {
                    probabilisticLogicPropertyRule
                        =    'P'
                            > (comparatorRule
                            > probabilityRule
                            > '['
                            > logicPropertyRule
                            > ']');

                    probabilityRule
                        %=     qi::eps
                            > qi::double_ [qi::_pass = (qi::_1 >= 0) && (qi::_1 <= 1)];
                }

                //! Initialise the logic property rule
                void initialiseLogicPropertyRule() {
                    logicPropertyRule
                        =    primaryLogicPropertyRule
                            >>    *(
                                    andLogicPropertyRule
                                |     orLogicPropertyRule
                                |     implicationLogicPropertyRule
                                |     equivalenceLogicPropertyRule
                                |     untilLogicPropertyRule
                                );
                }

                //! Initialise the primary logic property rule
                void initialisePrimaryLogicPropertyRule() {
                    primaryLogicPropertyRule
                        =     numericSpatialNumericComparisonRule
                        |     numericNumericComparisonRule
                        |     differenceRule
                        |     notLogicPropertyRule
                        |     futureLogicPropertyRule
                        |     globalLogicPropertyRule
                        |     ('X' > (nextLogicPropertyRule | nextKLogicPropertyRule))
                        |     ('(' > logicPropertyRule > ')');

                    differenceRule
                        =     (
                                qi::lit("d")
                                > '('
                                > numericMeasureRule
                                > ')'
                                > comparatorRule
                                > numericMeasureRule
                            );

                    numericSpatialNumericComparisonRule
                        =     (
                                numericSpatialRule
                                > comparatorRule
                                > numericMeasureRule
                            );

                    numericNumericComparisonRule
                        =     (
                                numericStateVariableRule
                                > comparatorRule
                                > numericMeasureRule
                            );

                    notLogicPropertyRule
                        =     ('~' > logicPropertyRule);

                    futureLogicPropertyRule
                        =     (
                                qi::lit('F')
                                > '['
                                > qi::ulong_
                                > ','
                                > (
                                    qi::ulong_
                                    > ']'
                                    > logicPropertyRule
                                )
                            );

                    globalLogicPropertyRule
                        =     (
                                qi::lit('G')
                                > '['
                                > qi::ulong_
                                > ','
                                > (
                                    qi::ulong_
                                    > ']'
                                    > logicPropertyRule
                                )
                            );

                    nextLogicPropertyRule
                        =     logicPropertyRule;

                    nextKLogicPropertyRule
                        =     (
                                '['
                                > qi::ulong_
                                > ']'
                                > logicPropertyRule
                            );
                }

                //! Initialise the composed logic property rule
                void initialiseComposedLogicPropertyRule() {
                    andLogicPropertyRule
                        =     ('^' > logicPropertyRule);

                    orLogicPropertyRule
                        =     ('V' > logicPropertyRule);

                    implicationLogicPropertyRule
                        =     ("=>" > logicPropertyRule);

                    equivalenceLogicPropertyRule
                        =     ("<=>" > logicPropertyRule);

                    untilLogicPropertyRule
                        =     (
                                qi::lit('U')
                                > '['
                                > qi::ulong_
                                > ','
                                > (
                                    qi::ulong_
                                    > ']'
                                    > logicPropertyRule
                                )
                            );
                }

                //! Initialise the numeric measure rule
                void initialiseNumericMeasureRule() {
                    numericMeasureRule
                        =     numericSpatialRule
                        |     qi::double_
                        |     numericStateVariableRule
                        |     unaryNumericNumericRule
                        |     binaryNumericNumericRule;

                    unaryNumericNumericRule
                        =     (
                                unaryNumericMeasureRule
                                > '('
                                > numericMeasureRule
                                > ')'
                            );

                    binaryNumericNumericRule
                        =     (
                                binaryNumericMeasureRule
                                > '('
                                > numericMeasureRule
                                > ','
                                > numericMeasureRule
                                > ')'
                            );
                }

                //! Initialise the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRule() {
                    numericSpatialRule
                        =     unarySubsetRule
                        |     binarySubsetRule
                        |     ternarySubsetRule
                        |     quaternarySubsetRule;

                    unarySubsetRule
                        =     (
                                unarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ')'
                            );

                    binarySubsetRule
                        =     (
                                binarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ')'
                            );

                    ternarySubsetRule
                        =     (
                                ternarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ','
                                > qi::double_
                                > ')'
                            );

                    quaternarySubsetRule
                        =     (
                                quaternarySubsetMeasureRule
                                > '('
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ','
                                > subsetRule
                                > ','
                                > spatialMeasureRule
                                > ')'
                            );
                }

                //! Initialise the numeric spatial subset measure rule
                void initialiseNumericSpatialSubsetMeasureRule() {
                    unarySubsetMeasureRule
                        =     unarySubsetMeasureTypeParser;

                    binarySubsetMeasureRule
                        =     binarySubsetMeasureTypeParser;

                    ternarySubsetMeasureRule
                        =     ternarySubsetMeasureTypeParser;

                    quaternarySubsetMeasureRule
                        =     quaternarySubsetMeasureTypeParser;
                }

                //! Initialise the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRule() {
                    unaryNumericMeasureRule
                        =     unaryNumericMeasureTypeParser;

                    binaryNumericMeasureRule
                        =     binaryNumericMeasureTypeParser;
                }

                //! Initialise the subset rule
                void initialiseSubsetRule() {
                    subsetRule
                        =     subsetSpecificRule
                        |     filterSubsetRule;

                    filterSubsetRule
                        =     (
                                qi::lit("filter")
                                > '('
                                > subsetSpecificRule
                                > ','
                                > constraintRule
                                > ')'
                            );

                    subsetSpecificRule
                        =     subsetSpecificTypeParser;
                }

                //! Initialise the constraint rule
                void initialiseConstraintRule() {
                    constraintRule
                        =     primaryConstraintRule
                            >> *(
                                    (orConstraintRule)
                                |     (andConstraintRule)
                                |     (implicationConstraintRule)
                                |     (equivalenceConstraintRule)
                            );
                }

                //! Initialise the primary constraint rule
                void initialisePrimaryConstraintRule() {
                    primaryConstraintRule
                        =     notConstraintRule
                        |     unaryConstraintRule
                        |     ('(' > constraintRule > ')');

                    notConstraintRule
                        =     ('~' > constraintRule);

                    unaryConstraintRule
                        =     spatialMeasureRule
                            > comparatorRule
                            > numericMeasureRule;
                }

                //! Initialise the composed constraint rule
                void initialiseComposedConstraintRule() {
                    andConstraintRule
                        =     ('^' > constraintRule);

                    orConstraintRule
                        =     ('V' > constraintRule);

                    implicationConstraintRule
                        =     ("=>" > constraintRule);

                    equivalenceConstraintRule
                        =     ("<=>" > constraintRule);
                }

                //! Initialise the spatial measure rule
                void initialiseSpatialMeasureRule() {
                    spatialMeasureRule
                        =     spatialMeasureTypeParser;
                }

                //! Initialise the comparator rule
                void initialiseComparatorRule() {
                    comparatorRule
                        =     comparatorTypeParser;
                }

                //! Initialise the numeric state variable rule
                void initialiseNumericStateVariableRule() {
                    numericStateVariableRule
                        =     stateVariableRule;

                    stateVariableRule
                        =     ('{' > stateVariableNameRule > '}');

                    stateVariableNameRule
                        =     +(qi::char_ - qi::char_("{}"));
                }

                //! Initialise debug support
                void initialiseDebugSupport() {
                    assignNamesToRules();

                    // TODO: Uncomment this function call in case of debugging
                    // initialiseRulesDebugging();
                }

                //! Assign names to the rules
                void assignNamesToRules() {
                    assignNamesToLogicPropertiesRules();
                    assignNamesToNumericMeasureRules();
                    assignNamesToNumericSpatialMeasureRules();
                    assignNamesToNumericSpatialSubsetMeasureRules();
                    assignNamesToNaryNumericMeasureRules();
                    assignNamesToSubsetRules();
                    assignNamesToConstraintsRules();
                    assignNamesToSpatialMeasureRules();
                    assignNamesToComparatorRules();
                    assignNamesToNumericStateVariableRules();
                }

                //! Assign names to logic properties rules
                void assignNamesToLogicPropertiesRules() {
                    assignNamesToProbabilisticLogicPropertyRules();
                    assignNamesToLogicPropertyRules();
                    assignNamesToPrimaryLogicPropertyRules();
                    assignNamesToComposedLogicPropertyRules();
                }

                //! Assign names to constraints rules
                void assignNamesToConstraintsRules() {
                    assignNamesToConstraintRules();
                    assignNamesToPrimaryConstraintRules();
                    assignNamesToComposedConstraintRules();
                }

                //! Assign names to the probabilistic logic property rules
                void assignNamesToProbabilisticLogicPropertyRules() {
                    probabilisticLogicPropertyRule  .name("probabilisticLogicPropertyRules");
                    probabilityRule                 .name("probabilityRules");
                }

                //! Assign names to the logic property rules
                void assignNamesToLogicPropertyRules() {
                    logicPropertyRule.name("logicPropertyRules");
                }

                //! Assign names to the primary logic property rules
                void assignNamesToPrimaryLogicPropertyRules() {
                    primaryLogicPropertyRule            .name("primaryLogicPropertyRules");
                    differenceRule                      .name("differenceRules");
                    numericSpatialNumericComparisonRule .name("numericSpatialNumericComparisonRules");
                    numericNumericComparisonRule        .name("numericNumericComparisonRules");
                    notLogicPropertyRule                .name("notLogicPropertyRules");
                    futureLogicPropertyRule             .name("futureLogicPropertyRules");
                    globalLogicPropertyRule             .name("globalLogicPropertyRules");
                    nextLogicPropertyRule               .name("nextLogicPropertyRules");
                    nextKLogicPropertyRule              .name("nextKLogicPropertyRules");
                }

                //! Assign names to the composed logic property rules
                void assignNamesToComposedLogicPropertyRules() {
                    andLogicPropertyRule            .name("andLogicPropertyRules");
                    orLogicPropertyRule             .name("orLogicPropertyRules");
                    implicationLogicPropertyRule    .name("implicationLogicPropertyRules");
                    equivalenceLogicPropertyRule    .name("equivalenceLogicPropertyRules");
                    untilLogicPropertyRule          .name("untilLogicPropertyRules");
                }

                //! Assign names to the numeric measure rules
                void assignNamesToNumericMeasureRules() {
                    numericMeasureRule          .name("numericMeasureRules");
                    unaryNumericNumericRule     .name("unaryNumericNumericRules");
                    binaryNumericNumericRule    .name("binaryNumericNumericRules");
                }

                //! Assign names to the numeric spatial measure rules
                void assignNamesToNumericSpatialMeasureRules() {
                    numericSpatialRule      .name("numericSpatialRules");
                    unarySubsetRule         .name("unarySubsetRules");
                    binarySubsetRule        .name("binarySubsetRules");
                    ternarySubsetRule       .name("ternarySubsetRules");
                    quaternarySubsetRule    .name("quaternarySubsetRules");
                }

                //! Assign names to the numeric spatial subset measure rules
                void assignNamesToNumericSpatialSubsetMeasureRules() {
                    unarySubsetMeasureRule      .name("unarySubsetMeasureRules");
                    binarySubsetMeasureRule     .name("binarySubsetMeasureRules");
                    ternarySubsetMeasureRule    .name("ternarySubsetMeasureRules");
                    quaternarySubsetMeasureRule .name("quaternarySubsetMeasureRules");
                }

                //! Assign names to the nary numeric measure rules
                void assignNamesToNaryNumericMeasureRules() {
                    unaryNumericMeasureRule     .name("unaryNumericMeasureRules");
                    binaryNumericMeasureRule    .name("binaryNumericMeasureRules");
                }

                //! Assign names to the subset rules
                void assignNamesToSubsetRules() {
                    subsetRule          .name("subsetRules");
                    filterSubsetRule    .name("filterSubsetRules");
                    subsetSpecificRule  .name("subsetSpecificRules");
                }

                //! Assign names to the constraint rules
                void assignNamesToConstraintRules() {
                    constraintRule.name("constraintRules");
                }

                //! Assign names to the primary constraint rules
                void assignNamesToPrimaryConstraintRules() {
                    primaryConstraintRule   .name("primaryConstraintRules");
                    notConstraintRule       .name("notConstraintRules");
                    unaryConstraintRule     .name("unaryConstraintRules");
                }

                //! Assign names to the composed constraint rules
                void assignNamesToComposedConstraintRules() {
                    andConstraintRule           .name("andConstraintRules");
                    orConstraintRule            .name("orConstraintRules");
                    implicationConstraintRule   .name("implicationConstraintRules");
                    equivalenceConstraintRule   .name("equivalenceConstraintRules");
                }

                //! Assign names to the spatial measure rules
                void assignNamesToSpatialMeasureRules() {
                    spatialMeasureRule.name("spatialMeasureRules");
                }

                //! Assign names to the comparator rules
                void assignNamesToComparatorRules() {
                    comparatorRule.name("comparatorRules");
                }

                //! Assign names to the numeric state variable rules
                void assignNamesToNumericStateVariableRules() {
                    numericStateVariableRule    .name("numericStateVariableRules");
                    stateVariableRule           .name("stateVariableRules");
                    stateVariableNameRule       .name("stateVariableNameRules");
                }

                //! Initialise the debugging of rules
                void initialiseRulesDebugging() {
                    initialiseLogicPropertiesRulesDebugging();
                    initialiseNumericMeasureRuleDebugging();
                    initialiseNumericSpatialMeasureRuleDebugging();
                    initialiseSpatialSubsetMeasureRuleDebugging();
                    initialiseNaryNumericMeasureRuleDebugging();
                    initialiseSubsetRuleDebugging();
                    initialiseConstraintsRulesDebugging();
                    initialiseSpatialMeasureRuleDebugging();
                    initialiseComparatorRuleDebugging();
                    initialiseNumericStateVariableRuleDebugging();
                }

                //! Initialise the debugging of the logic properties rules
                void initialiseLogicPropertiesRulesDebugging() {
                    initialiseProbabilisticLogicPropertyRuleDebugging();
                    initialiseLogicPropertyRuleDebugging();
                    initialisePrimaryLogicPropertyRuleDebugging();
                    initialiseComposedLogicPropertyRuleDebugging();
                }

                //! initialise the debugging of the constraints rules
                void initialiseConstraintsRulesDebugging() {
                    initialiseConstraintRuleDebugging();
                    initialisePrimaryConstraintRuleDebugging();
                    initialiseComposedConstraintRuleDebugging();
                }

                //! Initialise debugging for the probabilistic logic property rule
                void initialiseProbabilisticLogicPropertyRuleDebugging() {
                    debug(probabilisticLogicPropertyRule);
                    debug(probabilityRule);
                }

                //! Initialise debugging for the logic property rule
                void initialiseLogicPropertyRuleDebugging() {
                    debug(logicPropertyRule);
                }

                //! Initialise debugging for the primary logic property rule
                void initialisePrimaryLogicPropertyRuleDebugging() {
                    debug(primaryLogicPropertyRule);
                    debug(differenceRule);
                    debug(numericSpatialNumericComparisonRule);
                    debug(numericNumericComparisonRule);
                    debug(notLogicPropertyRule);
                    debug(futureLogicPropertyRule);
                    debug(globalLogicPropertyRule);
                    debug(nextLogicPropertyRule);
                    debug(nextKLogicPropertyRule);
                }

                //! Initialise debugging for the composed logic property rule
                void initialiseComposedLogicPropertyRuleDebugging() {
                    debug(andLogicPropertyRule);
                    debug(orLogicPropertyRule);
                    debug(implicationLogicPropertyRule);
                    debug(equivalenceLogicPropertyRule);
                    debug(untilLogicPropertyRule);
                }

                //! Initialise debugging for the numeric measure rule
                void initialiseNumericMeasureRuleDebugging() {
                    debug(numericMeasureRule);
                    debug(unaryNumericNumericRule);
                    debug(binaryNumericNumericRule);
                }

                //! Initialise debugging for the numeric spatial measure rule
                void initialiseNumericSpatialMeasureRuleDebugging() {
                    debug(numericSpatialRule);
                    debug(unarySubsetRule);
                    debug(binarySubsetRule);
                    debug(ternarySubsetRule);
                    debug(quaternarySubsetRule);
                }

                //! Initialise debugging for the spatial subset measure rule
                void initialiseSpatialSubsetMeasureRuleDebugging() {
                    debug(unarySubsetMeasureRule);
                    debug(binarySubsetMeasureRule);
                    debug(ternarySubsetMeasureRule);
                    debug(quaternarySubsetMeasureRule);
                }

                //! Initialise debugging for the n-ary numeric measure rule
                void initialiseNaryNumericMeasureRuleDebugging() {
                    debug(unaryNumericMeasureRule);
                    debug(binaryNumericMeasureRule);
                }

                //! Initialise debugging for the subset rule
                void initialiseSubsetRuleDebugging() {
                    debug(subsetRule);
                    debug(filterSubsetRule);
                    debug(subsetSpecificRule);
                }

                //! Initialise debugging for the constraint rule
                void initialiseConstraintRuleDebugging() {
                    debug(constraintRule);
                }

                //! Initialise debugging for the primary constraint rule
                void initialisePrimaryConstraintRuleDebugging() {
                    debug(primaryConstraintRule);
                    debug(notConstraintRule);
                    debug(unaryConstraintRule);
                }

                //! Initialise debugging for the composed constraint rule
                void initialiseComposedConstraintRuleDebugging() {
                    debug(andConstraintRule);
                    debug(orConstraintRule);
                    debug(implicationConstraintRule);
                    debug(equivalenceConstraintRule);
                }

                //! Initialise debugging for the spatial measure rule
                void initialiseSpatialMeasureRuleDebugging() {
                    debug(spatialMeasureRule);
                }

                //! Initialise debugging for the comparator rule
                void initialiseComparatorRuleDebugging() {
                    debug(comparatorRule);
                }

                //! Initialise debugging for the state variable rule
                void initialiseNumericStateVariableRuleDebugging() {
                    debug(numericStateVariableRule);
                    debug(stateVariableRule);
                    debug(stateVariableNameRule);
                }

                //! Initialise the error handling routines
                void initialiseErrorHandlingSupport() {
                    initialiseLogicPropertiesErrorHandlingSupport();
                    initialiseNumericMeasureErrorHandlingSupport();
                    initialiseNumericSpatialMeasureErrorHandlingSupport();
                    initialiseSubsetErrorHandlingSupport();
                    initialiseConstraintsErrorHandlingSupport();
                    initialiseStateVariableErrorHandlingSupport();
                }

                //! Initialise the logic properties error handling support
                void initialiseLogicPropertiesErrorHandlingSupport() {
                    initialiseProbabilisticLogicPropertyErrorHandlingSupport();
                    initialisePrimaryLogicPropertyErrorHandlingSupport();
                    initialiseComposedLogicPropertyErrorHandlingSupport();
                }

                //! Initialise the constraints error handling support
                void initialiseConstraintsErrorHandlingSupport() {
                    initialisePrimaryConstraintErrorHandlingSupport();
                    initialiseComposedConstraintErrorHandlingSupport();
                }

                //! Initialise the probabilistic logic property error handling support
                void initialiseProbabilisticLogicPropertyErrorHandlingSupport() {
                    qi::on_error<qi::fail>(probabilisticLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(probabilityRule, multiscale::verification::handleProbabilityError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the primary logic property error handling support
                void initialisePrimaryLogicPropertyErrorHandlingSupport() {
                    qi::on_error<qi::fail>(primaryLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(differenceRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(numericSpatialNumericComparisonRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(numericNumericComparisonRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(notLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(futureLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(globalLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(nextLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(nextKLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the compose logic property error handling support
                void initialiseComposedLogicPropertyErrorHandlingSupport() {
                    qi::on_error<qi::fail>(andLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(orLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(implicationLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(equivalenceLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(untilLogicPropertyRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the numeric measure error handling support
                void initialiseNumericMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(unaryNumericNumericRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(binaryNumericNumericRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the numeric spatial measure error handling support
                void initialiseNumericSpatialMeasureErrorHandlingSupport() {
                    qi::on_error<qi::fail>(unarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(binarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(ternarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(quaternarySubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the subset error handling support
                void initialiseSubsetErrorHandlingSupport() {
                    qi::on_error<qi::fail>(filterSubsetRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the primary constraint error handling support
                void initialisePrimaryConstraintErrorHandlingSupport() {
                    qi::on_error<qi::fail>(primaryConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(notConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(unaryConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the composed constraint error handling support
                void initialiseComposedConstraintErrorHandlingSupport() {
                    qi::on_error<qi::fail>(andConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(orConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(implicationConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                    qi::on_error<qi::fail>(equivalenceConstraintRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

                //! Initialise the state variable error handling support
                void initialiseStateVariableErrorHandlingSupport() {
                    qi::on_error<qi::fail>(stateVariableNameRule, multiscale::verification::handleUnexpectedTokenError(qi::_4, qi::_3, qi::_2));
                }

        };

    };

};

#endif
