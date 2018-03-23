#include "catch/catch.hpp"

#include "fictional-fiesta/world/itf/Individual.h"

#include "fictional-fiesta/utils/itf/Exception.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/input");
static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/world/result");
static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/world/benchmark");

// Important note: Some of these tests force the seed of the RNG to allow testability.
// Changing the RNG or the order of the statements will probably cause this test to fail.

TEST_CASE("Test genotype constructor and getters", "[IndividualTest][TestConstructor]")
{
  {
    const Individual::Genotype genotype{43, 0.5, 0.66};
    REQUIRE(genotype.getReproductionEnergyThreshold() == 43);
    REQUIRE(genotype.getReproductionProbability() == 0.5);
    REQUIRE(genotype.getMutabilityRatio() == 0.66);
  }

  {
    const Individual::Genotype genotype{0, 0.001, 0};
    REQUIRE(genotype.getReproductionEnergyThreshold() == 0);
    REQUIRE(genotype.getReproductionProbability() == 0.001);
    REQUIRE(genotype.getMutabilityRatio() == 0);
  }
}

TEST_CASE("Test genotype willReproduce method", "[IndividualTest][TestWillReproduce]")
{
  {
    auto rng{FSM::createRng(0)};

    const Individual::Genotype genotype{10, 1, 0.1};

    // Energy lower than the reproduction threshold (should be always false).
    REQUIRE(!genotype.willReproduce(Individual::Phenotype{5}, rng));
    REQUIRE(!genotype.willReproduce(Individual::Phenotype{9.99}, rng));
    REQUIRE(!genotype.willReproduce(Individual::Phenotype{0}, rng));
  }

  {
    auto rng{FSM::createRng(1)};

    const Individual::Genotype genotype{10, 1, 0.1};

    // Energy greater or equal than the reproduction threshold and probability 1
    // (should be always true).
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10}, rng));
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10}, rng));
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10.1}, rng));
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10}, rng));
  }

  {
    auto rng{FSM::createRng(2)};

    const Individual::Genotype genotype{10, 0.5, 0.1};

    // Energy greater or equal than the reproduction threshold and probability 0.5
    // (some true, some false).
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10}, rng));
    REQUIRE(!genotype.willReproduce(Individual::Phenotype{10}, rng));
    REQUIRE(!genotype.willReproduce(Individual::Phenotype{10.1}, rng));
    REQUIRE(genotype.willReproduce(Individual::Phenotype{10}, rng));
  }
}
