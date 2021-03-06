#ifndef INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H
#define INCLUDE_FICTIONAL_FIESTA_WORLD_SOURCE_H

#include "fictional-fiesta/utils/itf/Descriptable.h"

#include <limits>
#include <memory>
#include <string>

namespace fictionalfiesta
{

class XmlNode;

/// @brief Class that represents a source that generates a given resource.
class Source : public Descriptable
{
  public:

    /// @brief Constructor from the resource name.
    /// @param resourceId Resource identifier.
    /// @param initialUnitCount Inital number of units of the resource available.
    Source(const std::string& resourceId, unsigned int initialUnitCount);

    /// @brief Constructor from an XmlNode and a number of initial units.
    /// @param node XmlNode with the class contents.
    /// @param initialUnitCount Inital number of units of the resource available.
    Source(const XmlNode& node, unsigned int initialUnitCount);

    /// @brief Default destructor.
    virtual ~Source() = default;

    /// @brief Clone this Source.
    /// @return Owning pointer to the cloned Source.
    std::unique_ptr<Source> clone() const;

    /// @brief Get the resource identifier.
    /// @return Resource identifier.
    const std::string& getResourceId() const;

    /// @brief Get the number of units of resource available.
    /// @return Current number of units of the resource.
    const unsigned int getCurrentUnitCount() const noexcept;

    /// @brief Check whether the source is empty or not.
    /// @return @e true if the source is empty (no more units), @e false otherwise
    bool empty() const noexcept;

    /// @brief Consume a given number of units of the resource.
    /// It is not possible to consume more units than available.
    /// @param requiredUnits Units of the resource required.
    /// @return Effective number if units consumed.
    virtual unsigned int consume(const unsigned int requiredUnits);

    /// @brief Regenerates the number of units of the resource.
    virtual void regenerate() = 0;

    /// @brief Save this Source instance in a XmlNode.
    /// @note This class uses NVI-idiom to call the specific saves of the derived classes.
    /// @param node node where the Source instance will be saved.
    void save(XmlNode node) const;

    /// Representation of an infinity number of units.
    static constexpr unsigned int INFINITY_UNITS{std::numeric_limits<unsigned int>::max()};

    // XML node and attribute variables:
    /// Name of the source main node.
    static constexpr char XML_MAIN_NODE_NAME[]{"Source"};
    /// Name of the source type node.
    static constexpr char XML_SOURCE_TYPE_ATTRIBUTE_NAME[]{"Type"};

  protected:

    /// @brief Set the number of units of the resource.
    /// @param currentUnitCount Number of units to be set.
    void setCurrentUnitCount(unsigned int currentUnitCount);

    /// @brief Converts the units to a string representation.
    /// @param units Number of units to be stringyfied.
    /// @return string representing the units.
    static std::string unitsToString(unsigned int units);

  private:

    virtual Source* doClone() const = 0;

    virtual void doSave(XmlNode& node) const = 0;

    std::string _resourceId;

    unsigned int _currentUnitCount;
};

} // namespace fictionalfiesta

#endif
