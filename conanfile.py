from conans import ConanFile, CMake
from conans.tools import Git


def get_version():
    """ Determine project version from git """
    git = Git()
    try:
        # Return the git commit hash
        return git.get_revision()
    except:
        # Return None if it's not a git repo
        return None

class IVExConan(ConanFile):
    """ Conan file for ivex"""

    name = "IVEx"
    version = get_version()
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = ("include/*", "src/*", "tests/*", "CMakeLists.txt")
    generators = "cmake"
    no_copy_source = True

    def _cmake_configure(self):
        """ Shared CMake configure """
        print(self)
        cmake = CMake(self)

        cmake.definitions["BUILD_TESTS"] = "ON"
        cmake.definitions["BUILD_DOCS"] = "OFF"

        cmake.configure()

        return cmake

    def build(self):
        """ Build by building and testing with CMake """
        cmake = self._cmake_configure()
        cmake.build()
        cmake.test(output_on_failure=True)

    def package(self):
        """ Package by installing with CMake """

        # Call CMake install
        cmake = self._cmake_configure()
        cmake.install()

    def package_info(self):
        """ Set library """
        self.cpp_info.libs = ["ivex"]

    def build_requirements(self):
        """ Build dependencies """


    def requirements(self):
        """ Interface dependencies """
        self.requires("JoSIM/2.4@joeydelp/release")
        self.requires("CLI11/1.9.0@cliutils/stable")
        self.requires("Catch2/2.11.1@catchorg/stable")
