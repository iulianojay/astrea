# Copyright (c) 2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

from conan import ConanFile


class AstreaConan(ConanFile):
    name = "astrea"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    default_options = {
        # Disable C++ modules to avoid module-scan complexity with GCC
        "mp-units*:cxx_modules": False,
        # Use OpenSSL as the SSL backend for cpr on Linux
        "cpr*:with_ssl": "openssl",
    }

    def requirements(self):
        self.requires("mp-units/2.5.0")
        self.requires("nlohmann_json/3.12.0")
        self.requires("sqlite3/3.47.2")
        self.requires("cpr/1.11.0")
        self.requires("gtest/1.17.0")
        self.requires("benchmark/1.9.5")
