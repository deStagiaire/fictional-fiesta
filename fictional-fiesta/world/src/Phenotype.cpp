/// @file Phenotype.cpp Implementation of the Phenotype class.

#include "fictional-fiesta/world/itf/Phenotype.h"

#include "fictional-fiesta/utils/itf/XmlNode.h"

#include <sstream>

namespace fictionalfiesta
{

namespace
{
  constexpr char XML_ENERGY_NAME[]{"Energy"};
} // anonymous namespace

Phenotype::Phenotype(double initialEnergy):
  _energy(initialEnergy)
{
}

Phenotype::Phenotype(const XmlNode& node):
  _energy(node.getChildNodeTextAs<double>(XML_ENERGY_NAME))
{
}

void Phenotype::save(XmlNode node) const
{
  auto energy_node = node.appendChildNode(XML_ENERGY_NAME);
  energy_node.setText(_energy);
}

double Phenotype::getEnergy() const
{
  return _energy;
}

void Phenotype::feed(unsigned int resourceUnits, const Genotype& genotype)
{
  // Currently the phenotype is just energy, so we just increase it in the same ammount than the
  // resource units aquired.
  _energy += resourceUnits;
}

Phenotype Phenotype::split(const Genotype& genotype)
{
  _energy *= 0.5;
  return Phenotype{_energy};
}

std::string Phenotype::str(unsigned int indentLevel) const
{
  std::stringstream result;
  result <<
      indent(indentLevel) << "Energy: " << _energy << "\n";

  return result.str();
}

} // namespace fictionalfiesta
