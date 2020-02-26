#include <ivex/Input.hpp>

#include <catch2/catch.hpp>

using namespace ivex;

TEST_CASE("Input")
{
    SECTION("Fail due to lack of arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-k")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Show help menu through arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-h")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Data file switch alone") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-d")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments, double dash") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments, double dash") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--k")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Show help menu through arguments, double dash") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--h")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Data file switch alone, double dash") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--d")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to missing model and output file name") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-d"),
            static_cast<const char *>("file.iv")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to missing data file and output file name") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-d"),
            static_cast<const char *>("\".model jjiv jj(icrt=0.1mA, cap=0.02pF, rn=16, r0=160, vg=2.5mv)")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to missing output file name") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-d"),
            static_cast<const char *>("file.iv")
            static_cast<const char *>("\".model jjiv jj(icrt=0.1mA, cap=0.02pF, rn=16, r0=160, vg=2.5mv)")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("No fail 1") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("\".model jjiv jj(icrt=0.1mA, cap=0.02pF, rn=16, r0=160, vg=2.5mv)"),
            static_cast<const char *>("output.csv")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("No fail 2") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("\".model jjiv jj(icrt=0.1mA, cap=0.02pF, rn=16, r0=160, vg=2.5mv)"),
            static_cast<const char *>("output.csv")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }
}
