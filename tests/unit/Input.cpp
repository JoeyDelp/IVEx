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

    SECTION("Data file switch") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("-d")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Fail due to bad arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--k")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_THROWS(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Show help menu through arguments") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--h")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }

    SECTION("Data file switch") {
        const char* argv[] = {
            static_cast<const char *>("ivex"),
            static_cast<const char *>("--d")
            };
        int argc = sizeof(argv)/sizeof(argv[0]);

        ivex_vars ivars;

        REQUIRE_NOTHROW(input_parse(argc, static_cast<const char **>(argv), ivars));
    }
}
