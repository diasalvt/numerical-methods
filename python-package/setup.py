from setuptools import setup, find_packages
import os
import subprocess

curr_path = os.path.dirname(os.path.abspath(os.path.expanduser(__file__)))
lib_path = os.path.join(curr_path, 'libcpp/', 'libnumericalmethods.so')

subprocess.call(['make', '-C', '../'])

setup(
    name='numerical_methods',
    version='0.1',
    description="Numerical Methods Package",
    author="Thomas Dias-Alves",
    install_requires=[
        "numpy"
    ],
    packages=find_packages(),
    data_files=[('libcpp',[lib_path])],
    zip_safe=False
)
