# Copyright (c) 2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

import os
import re

from conan import ConanFile
from conan.tools.files import load
from conan.tools.scm import Git


class AstreaConan(ConanFile):
    """Astrea's own dependencies, plus an editable-package view of its install tree.

    Consume it locally with `conan editable add <astrea checkout>`; Conan then resolves
    `astrea` to install/<compiler>/<compiler>-<major>-<std>/<build_type> (produced by
    `make`) instead of a cached package. There is no build()/package() step, so
    `conan create` is not supported.
    """

    name = "astrea"
    package_type = "shared-library"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    default_options = {  # noqa: RUF012
        # Default to OpenSSL; macOS is overridden to DarwinSSL in configure().
        "cpr/*:with_ssl": "openssl",
    }

    def set_version(self):
        self.version = Git(self, self.recipe_folder).run("describe --tags --abbrev=0")

    def layout(self):
        # Directory names mirror the Makefile: the std is Astrea's own (hardcoded in
        # CMakeLists.txt), not the consumer's.
        cmake_lists = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        std = re.search(r"set\(CMAKE_CXX_STANDARD (\d+)\)", cmake_lists).group(1)
        compiler = str(self.settings.compiler)
        major = str(self.settings.compiler.version).split(".")[0]
        tag = f"{compiler}/{compiler}-{major}-{std}/{self.settings.build_type}"

        self.folders.build = f"install/{tag}"
        self.folders.generators = f"build/{tag}"
        self.cpp.build.includedirs = ["include"]
        self.cpp.build.libdirs = ["lib"]
        self.cpp.build.builddirs = [""]

    def package_info(self):
        # The install tree ships its own astreaConfig.cmake; use it as-is instead of
        # letting CMakeDeps generate a competing one.
        self.cpp_info.set_property("cmake_find_mode", "none")

    def configure(self):
        if str(self.settings.os) == "Macos":
            self.options["cpr/*"].with_ssl = "darwinssl"
        elif str(self.settings.os) == "Windows":
            self.options["cpr/*"].with_ssl = "winssl"
            self.options["libcurl/*"].with_ssl = "schannel"
        else:
            self.options["cpr/*"].with_ssl = "openssl"

    def requirements(self):
        # Astrea's public headers include these, so consumers need them too.
        self.requires("nlohmann_json/3.12.0", transitive_headers=True)
        self.requires("sqlite3/3.47.2", transitive_headers=True)
        self.requires("cpr/1.11.0", transitive_headers=True, transitive_libs=True)
        self.requires("gsl-lite/1.1.0", transitive_headers=True)

    def build_requirements(self):
        self.test_requires("gtest/1.17.0")
        self.test_requires("benchmark/1.9.5")
