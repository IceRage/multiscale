#ifndef SPATIALTEMPORALDATAWRITER_HPP
#define SPATIALTEMPORALDATAWRITER_HPP

#include "multiscale/verification/spatial-temporal/model/SpatialTemporalTrace.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <memory>

namespace pt = boost::property_tree;


namespace multiscale {

    namespace verification {

        //! Class for writing spatial temporal traces to output files
        class SpatialTemporalDataWriter {

            public:

                //! Output the given spatial temporal trace in xml format to the specified file path
                /*!
                 * \param trace The provided spatial temporal trace
                 */
                static void
                outputTraceInXmlFormatToFile(const SpatialTemporalTrace &trace,
                                             const std::string &outputFilepath);

            private:

                //! Add a comment to the property tree indicating that the property tree was generated automatically
                /*!
                 * \param propertyTree  The property tree to which the comment will be added
                 */
                static void
                addAutoGeneratedCommentToPropertyTree(pt::ptree &propertyTree);

                //! Construct the property tree following the structure of the spatial temporal trace
                /*!
                 * \param trace         The provided spatial temporal trace
                 * \param propertyTree  The property tree which corresponds to the spatial temporal trace
                 */
                static void
                constructPropertyTreeFromTrace(const SpatialTemporalTrace &trace,
                                               pt::ptree &propertyTree);

                //! Add timepoints from the trace to the provided experiment property tree
                /*!
                 * \param trace                     The provided spatial temporal trace
                 * \param experimentPropertyTree    The experiment property tree which corresponds to the
                 *                                  experiment root xml element
                 */
                static void
                addTimepointsToExperimentPropertyTree(const SpatialTemporalTrace &trace,
                                                      pt::ptree &experimentPropertyTree);

                //! Construct the property tree corresponding to the provided timepoint
                /*!
                 * \param timepoint     The provided timepoint
                 */
                static pt::ptree
                constructPropertyTreeFromTimepoint(const TimePoint &timepoint);

                //! Add the timepoint value as an attribute to the timepoint tree
                /*!
                 * \param timepoint     The considered timepoint
                 * \param timepointTree The timepoint tree to which the value attribute is added
                 */
                static void
                addValueAttributeToTimepointTree(const TimePoint& timepoint,
                                                 pt::ptree &timepointTree);

                //! Add the spatial entities from the timepoint to the timepoint tree
                /*!
                 * \param timepoint     The considered timepoint
                 * \param timepointTree The timepoint tree to which the spatial entities are added
                 */
                static void
                addSpatialEntitiesToTimepointTree(const TimePoint &timepoint,
                                                  pt::ptree &timepointTree);

                //! Add the spatial entities of the specified type to the timepoint tree
                /*!
                 * \param spatialEntitiesType   The considered spatial entities type
                 * \param timepoint             The considered timepoint
                 * \param timepointTree         The timepoint tree to which the spatial entities are added
                 */
                static void
                addSpatialEntitiesOfSpecificTypeToTimepointTree(const std::size_t &spatialEntitiesType,
                                                                const TimePoint &timepoint,
                                                                pt::ptree &timepointTree);

                //! Add a spatial entity of the specified type to the timepoint tree
                /*!
                 * \param spatialEntityType The type of the spatial entity
                 * \param spatialEntity     The considered spatial entity
                 * \param timepointTree     The timepoint tree to which the spatial entity is added
                 */
                static void
                addSpatialEntityOfSpecificTypeToTimepointTree(const std::string &spatialEntityType,
                                                              const std::shared_ptr<SpatialEntity> &spatialEntity,
                                                              pt::ptree &timepointTree);

                //! Add the spatial measures values for the given spatial entity to the provided spatial entity tree
                /*!
                 * \param spatialEntity     The considered spatial entity
                 * \param spatialEntityTree The spatial entity tree to which the spatial measure values are added
                 */
                static void
                addSpatialMeasuresValuesToTree(const std::shared_ptr<SpatialEntity> &spatialEntity,
                                               pt::ptree &spatialEntityTree);

                //! Add the numeric state variables from the timepoint to the timepoint tree
                /*!
                 * \param timepoint     The considered timepoint
                 * \param timepointTree The timepoint tree to which the value attribute is added
                 */
                static void
                addNumericStateVariablesToTimepointTree(const TimePoint &timepoint,
                                                        pt::ptree &timepointTree);

                //! Construct the property tree corresponding to the provided numeric state variable
                /*!
                 * \param numericStateVariableId    The id of the numeric state variable to which the property
                 *                                  tree corresponds
                 *
                 * \param numericStateVariableValue The value of the numeric state variable to which the property
                 *                                  tree corresponds
                 */
                static pt::ptree
                constructPropertyTreeFromNumericStateVariable(const NumericStateVariableId &numericStateVariableId,
                                                              double numericStateVariableValue);

                //! Add the provided spatial type string as an attribute to the property tree
                /*!
                 * \param spatialType   The spatial type value provided as a string
                 * \param propertyTree  The property tree to which the spatial type attribute is added
                 */
                static void
                addSpatialTypeAttributeToTree(const std::string &spatialType,
                                              pt::ptree &propertyTree);

                //! Add the provided semantic type string as an attribute to the property tree
                /*!
                 * \param semanticType  The semantic type value provided as a string
                 * \param propertyTree  The property tree to which the semantic type attribute is added
                 */
                static void
                addSemanticTypeAttributeToTree(const std::string &semanticType,
                                               pt::ptree &propertyTree);

                //! Add the provided attribute to the property tree
                /*!
                 * \param attributeName     The name of the attribute
                 * \param attributeValue    The value of the attribute
                 * \param propertyTree      The property tree to which the attribute is added
                 */
                static void
                addAttributeToTree(const std::string &attributeName, const std::string &attributeValue,
                                   pt::ptree &propertyTree);

                //! Output the property tree in xml format to the specified path
                /*!
                 * \param propertyTree      The property tree which corresponds to the spatial temporal trace
                 * \param outputFilepath    The path to the file where the property tree will be writen
                 */
                static void
                outputPropertyTreeInXmlFormatToFile(const pt::ptree &propertyTree,
                                                    const std::string &outputFilepath);

                // Constants
                static const std::string LABEL_ATTRIBUTE;
                static const std::string LABEL_COMMENT;

                static const std::string LABEL_EXPERIMENT;
                static const std::string LABEL_TIMEPOINT;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE;
                static const std::string LABEL_SPATIAL_ENTITY;

                static const std::string LABEL_TIMEPOINT_VALUE_ATTRIBUTE;
                static const std::string LABEL_SPATIAL_TYPE_ATTRIBUTE;
                static const std::string LABEL_SEMANTIC_TYPE_ATTRIBUTE;

                static const std::string LABEL_NUMERIC_STATE_VARIABLE_NAME;
                static const std::string LABEL_NUMERIC_STATE_VARIABLE_VALUE;

                static const std::string CONTENTS_COMMENT_AUTO_GENERATED;

        };

    };

};


#endif
