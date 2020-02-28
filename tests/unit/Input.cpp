#include <ivex/Input.hpp>
#include <catch2/catch.hpp>
#include <CLI/CLI.hpp>

using namespace ivex;

TEST_CASE("Input")
{
    SECTION("Print Help Menu"){
        const char *argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-h")
        };
        int argc = sizeof(argv)/sizeof(argv[0]);
        ivex_vars ivars;

        REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
            == 0 );
    }

    SECTION("Data file") {
        SECTION("Missing data file argument") {
            const char *argv[] = {
                static_cast<const char *>("ivex"),
                static_cast<const char *>("-d"),
                static_cast<const char *>("-m"),
                static_cast<const char *>("model.model"),
                static_cast<const char *>("output.csv")
            };
            int argc = sizeof(argv)/sizeof(argv[0]);
            ivex_vars ivars;

            REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
                == static_cast<int>(CLI::ExitCodes::ValidationError) );
        }

        SECTION("Missing data file at specified location") {
            const char *argv[] = {
                static_cast<const char *>("ivex"),
                static_cast<const char *>("-d"),
                static_cast<const char *>("data.iv"),
                static_cast<const char *>("-m"),
                static_cast<const char *>("model.model"),
                static_cast<const char *>("output.csv")
            };
            int argc = sizeof(argv)/sizeof(argv[0]);
            ivex_vars ivars;

            REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
                == static_cast<int>(CLI::ExitCodes::ValidationError) );
        }
    }

    SECTION("Model file") { 
        SECTION("Missing model file at specified location") {
            const char *argv[] = {
                static_cast<const char *>("ivex"),
                static_cast<const char *>("-d"),
                static_cast<const char *>("./tests/test_files/data.iv"),
                static_cast<const char *>("-m"),
                static_cast<const char *>("model.model"),
                static_cast<const char *>("output.csv")
            };
            int argc = sizeof(argv)/sizeof(argv[0]);
            ivex_vars ivars;

            REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
                == static_cast<int>(CLI::ExitCodes::ValidationError) );
        }   

        SECTION("Missing model file argument") {
            const char *argv[] = {
                static_cast<const char *>("ivex"),
                static_cast<const char *>("-d"),
                static_cast<const char *>("./tests/test_files/data.iv"),
                static_cast<const char *>("-m"),
                static_cast<const char *>("output.csv")
            };
            int argc = sizeof(argv)/sizeof(argv[0]);
            ivex_vars ivars;

            REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
                == static_cast<int>(CLI::ExitCodes::ValidationError) );
        }

         SECTION("Model file and model string specified") {
            const char *argv[] = {
                static_cast<const char *>("ivex"),
                static_cast<const char *>("-d"),
                static_cast<const char *>("./tests/test_files/data.iv"),
                static_cast<const char *>("-m"),
                static_cast<const char *>("./tests/test_files/model.model"),
                static_cast<const char *>("-s"),
                static_cast<const char *>("\".model jj jj()\""),
                static_cast<const char *>("output.csv")
            };
            int argc = sizeof(argv)/sizeof(argv[0]);
            ivex_vars ivars;

            REQUIRE( input_parse(argc, static_cast<const char **>(argv), ivars) 
                == static_cast<int>(CLI::ExitCodes::RequiredError) );
        } 
    }
}
