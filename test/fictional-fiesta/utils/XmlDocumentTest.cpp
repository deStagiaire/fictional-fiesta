#include "catch/catch.hpp"

#include "fictional-fiesta/utils/itf/Exception.h"
#include "fictional-fiesta/utils/itf/XmlDocument.h"

#include "test/test_utils/itf/BenchmarkFiles.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace fictionalfiesta;
using namespace testutils;

static const fs::path input_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/utils/input");
static const fs::path result_directory = fs::path(TEST_BINARY_DIRECTORY)
    / fs::path("fictional-fiesta/utils/result");
static const fs::path benchmark_directory = fs::path(TEST_SOURCE_DIRECTORY)
    / fs::path("fictional-fiesta/utils/benchmark");

TEST_CASE("Test loading a XML document", "[XmlDocumentTest][TestConstruction]")
{
  {
    const fs::path input_file = input_directory / fs::path("example_0.xml");
    REQUIRE_NOTHROW(XmlDocument{input_file});
  }

  {
    const fs::path input_file = input_directory / fs::path("no_example_0.xml");
    REQUIRE_THROWS_AS(XmlDocument{input_file}, Exception);
  }
}

TEST_CASE("Test loading and saving a XML document", "[XmlDocumentTest][TestSave]")
{
  const fs::path input_file = input_directory / fs::path("example_0.xml");
  const XmlDocument document{input_file};

  // Save pretty print (default).
  {
    const fs::path result_file = result_directory / fs::path("example_0.xml");
    REQUIRE_NOTHROW(document.save(result_file));

    const fs::path benchmark_file = benchmark_directory / fs::path("example_0.xml");
    benchmarkFiles(benchmark_file, result_file, result_directory);
  }

  // Save raw.
  {
    const fs::path result_file = result_directory / fs::path("example_0_raw.xml");
    REQUIRE_NOTHROW(document.save(result_file, false));

    const fs::path benchmark_file = benchmark_directory / fs::path("example_0_raw.xml");
    benchmarkFiles(benchmark_file, result_file, result_directory);
  }
}
