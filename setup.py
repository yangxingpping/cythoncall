from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

setup(
  name = 'embedded',
  ext_modules=cythonize([
    Extension("embedded", ["embedded.pyx", "embedded_main.c"]),
    ]),
)
