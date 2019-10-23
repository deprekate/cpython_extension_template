import os
#from distutils.core import setup, Extension
from setuptools import setup, Extension

os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"
#os.environ["CPP"] = "g++"
#os.environ["LDSHARED"] = "g++"

compile_args = ["-O3", "-std=c++11"]
#compile_args = ["-O3", "-g"]
link_args    = ["-lstdc++"]

cpython_extension_template_module = Extension('cpython_extension_template',
                    language='g++',
                    extra_compile_args=compile_args,
                    extra_link_args=link_args,
                    include_dirs=[
                             '.',
                             '...',
                             os.path.join(os.getcwd(), 'include'),
                    ],
                    library_dirs = [os.getcwd(),],
                    sources = ['src/cpython_extension_template.cpp'])

with open("README.md", "r") as fh:
    long_desc = fh.read()


setup (
    name = 'cpython_extension_template',
    version = '1.5',
    author = "Katelyn McNair",
    author_email = "deprekate@gmail.com",
    description = 'A package for finding repeats in a DNA sequence',
    long_description = long_desc,
    long_description_content_type="text/markdown",
    url =  "https://github.com/deprekate/RepeatFinder",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)",
        "Operating System :: OS Independent",
    ],
    python_requires='>3.5.2',
    ext_modules = [cpython_extension_template_module]
)
