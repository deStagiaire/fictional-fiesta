#ifndef INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H
#define INCLUDE_FICTIONAL_FIESTA_UTILS_XML_NODE_H

#include "fictional-fiesta/utils/itf/Pimpl.h"

#include <sstream>
#include <string>
#include <vector>

namespace fictionalfiesta
{

class XmlNodeImpl;

/// @brief Class to represent a node in an XML document.
class XmlNode
{
  public:

    /// @brief Constructor from a node implementation class instance.
    /// @details Since the XmlNodeImpl class is not visible from outside, this constructor
    /// can only be used internally.
    /// @param node Node implementation from which to construct this instance.
    explicit XmlNode(const XmlNodeImpl& node);

    /// @brief Move Constructor
    XmlNode(XmlNode&&);

    /// @brief Default destructor.
    ~XmlNode();

    /// @brief Get the name of the node.
    /// @return String with the name of the node.
    std::string getName() const;

    /// @brief Checks whether the node has an specific attribute or not.
    /// @param attributeName Name of the attribute to be checked.
    /// @return true if the node has an attribute with the passed name, false otherwise.
    bool hasAttribute(const std::string& attributeName) const;

    /// @brief Get the attribute with the passed name.
    /// @param attributeName Name of the attribute to be retrieved.
    /// @return String with the name of the node.
    /// @throw Exception if there is no attribute with the given name.
    std::string getAttribute(const std::string& attributeName) const;

    /// @brief Get the optional attribute with the passed name.
    /// @details Return the default value if there is no attribute with the passed name.
    /// @param attributeName Name of the attribute to be retrieved.
    /// @param defaultValue Value to be returned when there is no such an attribute.
    /// @return Attribute value or defaultValue if the attribute is not present.
    std::string getOptionalAttribute(const std::string& attributeName,
        const std::string& defaultValue) const;

    /// @brief Get the attribute of the node and parse it into @p T type.
    /// @tparam T Type into which the attribute needs to be parsed.
    /// @param attributeName Name of the attribute to be retrieved.
    /// @return value resulting of the parsing.
    /// @throw Exception if the attribute is not present.
    template <typename T>
    T getAttributeAs(const std::string& attributeName) const;

    /// @brief Get the optional attribute of the node and parse it into @p T type.
    /// @tparam T Type into which the attribute needs to be parsed.
    /// @param attributeName Name of the attribute to be retrieved.
    /// @param defaultValue Value to be returned when there is no such an attribute.
    /// @return Attribute value or defaultValue if the attribute is not present.
    template <typename T>
    T getOptionalAttributeAs(const std::string& attributeName, const T& defaultValue) const;

    /// @brief Checks whether the node has any child node.
    /// Note that only element nodes are cosidered for this method.
    /// @return true if the current node has at least one element child node.
    bool hasChildNode() const;

    /// @brief Checks whether the node has at least a child node with the given @p name.
    /// @note Only element nodes are cosidered for this method.
    /// @param name name of the child node.
    /// @return true if the current node has at least one element child node with the given @p name.
    bool hasChildNode(const std::string& name) const;

    /// @brief Get the first child node of the current node.
    /// @return First child node of the current node.
    /// @throw Exception if the node has no children.
    XmlNode getChildNode() const;

    /// @brief Get the first child node of the current node with the given @p name.
    /// @param name name of the child node.
    /// @return First child node of the current node with the given @p name .
    /// @throw Exception if the node has no children with the given name.
    XmlNode getChildNode(const std::string& name) const;

    /// @brief Get all the child nodes.
    /// @return All the child nodes of the current node.
    std::vector<XmlNode> getChildNodes() const;

    /// @brief Get all the child nodes with a given @p name.
    /// @param name name of the child nodes to retrieve.
    /// @return All the child nodes with the given name.
    std::vector<XmlNode> getChildNodes(const std::string& name) const;

    /// @brief Get the text of the node.
    /// @return String with the text contents of the node.
    /// @throw Exception if the node has no text.
    std::string getText() const;

    /// @brief Get the text of the node or return the default value if there is no text.
    /// @param defaultValue Value to be returned if there's no text.
    /// @return String with the text contents of the node.
    std::string getOptionalText(const std::string& defaultValue) const;

    /// @brief Get the text of the child node.
    /// @return text of the child node.
    /// @throw Exception if the node has no child or the child has no text.
    std::string getChildNodeText() const;

    /// @brief Get the text of the child node with a given name.
    /// @param name name of the child node.
    /// @return text of the child node with the given name.
    /// @throw Exception if the node has no such a child or the child has no text.
    std::string getChildNodeText(const std::string& name) const;

    /// @brief Get the text of the child node or @p default if there is no child node.
    /// @param defaultValue value to return by default.
    /// @return text of the child node or @p defaultValue if there is no text.
    std::string getOptionalChildNodeText(const std::string& defaultValue = "") const;

    /// @brief Get the text of the node and parse it into @p T type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no text.
    template <typename T>
    T getTextAs() const;

    /// @brief Get the text of the node and parse it into @p T type.
    /// @details If there is no text, return the default value.
    /// @tparam T Type into which the text needs to be parsed.
    /// @param defaultValue Value returned if there is no text in the node.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no text.
    template <typename T>
    T getOptionalTextAs(const T& defaultValue) const;

    /// @brief Get the text of the child node and parse it into @p type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no child or the child has no text.
    template <typename T>
    T getChildNodeTextAs() const;

    /// @brief Get the text of the child node with and parse it into @p type.
    /// @details  Return the default value if there's no child or no text.
    /// @tparam T Type into which the text needs to be parsed.
    /// @param defaultValue Value returned if there is no child node text in it.
    /// @return value resulting of the parsing.
    template <typename T>
    T getOptionalChildNodeTextAs(const T& defaultValue) const;

    /// @brief Get the text of the child node with a given name and parse it into @p type.
    /// @tparam T Type into which the text needs to be parsed.
    /// @param name name of the child node.
    /// @return value resulting of the parsing.
    /// @throw Exception if the node has no such a child or the child has no text.
    template <typename T>
    T getChildNodeTextAs(const std::string& name) const;

    /// @brief Get the text of the child node with a given name and parse it into @p type.
    /// @details Return the default value if there's no child or no text.
    /// @tparam T Type into which the text needs to be parsed.
    /// @param name Name of the node.
    /// @param defaultValue Value returned if there is no child node text in it.
    /// @return value resulting of the parsing.
    template <typename T>
    T getOptionalChildNodeTextAs(const std::string& name, const T& defaultValue) const;

    /// @brief Sets the value for the attribute with the passed test and creates it if it
    ///   does not exist.
    /// @param name Name of the attribute to be set.
    /// @param value Value to be set for the attribute.
    void setAttribute(const std::string& name, const std::string& value);

    /// @brief Dump the current @p content to a string and set it as the node attribute.
    /// @param name NAme of the attribute to be set.
    /// @param content Content to be set as attribute in the node.
    template <typename T>
    void setAttribute(const std::string& name, const T& content);

    /// @brief Dump the current @p content to a string and set it as the node text.
    /// @param content Content to be set as text in the node.
    template <typename T>
    void setText(const T& content);

    /// @brief Append a new name with the name passed.
    /// @param name Name for the new node appended.
    /// @return Node appended.
    XmlNode appendChildNode(const std::string& name);

  private:

    /// @brief Set the text of the node.
    /// @param text Text to be set in the node.
    void setNodeText(const std::string& text);

    /// Pointer to the node implementation.
    /// We use PIMPL to avoid exposing the XML dependecies.
    Pimpl<XmlNodeImpl> _pimpl;
};

template <typename T>
void XmlNode::setText(const T& content)
{
  std::stringstream ss;
  ss << std::boolalpha << content;
  setNodeText(ss.str());
}

template <typename T>
void XmlNode::setAttribute(const std::string& name, const T& content)
{
  std::stringstream ss;
  ss << std::boolalpha << content;
  setAttribute(name, ss.str());
}

} // namespace fictional-fiesta

#endif
