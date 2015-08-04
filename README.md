
Maya Plug-in Samples (Windows)
====

Simple Maya plug-in samples to test build environments on Windows.

* **NoiseCmd** : Simple noise command (command plug-in).
* **NoiseDeformer**: Simple noise node (deformer plug-in).
* **LaplacianSmoother**: Laplacian smoothing node (deformer plug-in).

## Result
*Status*: Under construction.

## Installation

*Note*: This program was only tested on **Windows** with **Maya2014, 2015**.
**Linux** and **Mac OS** are not officially supported,
but the following instructions might be helpful for installing on those environments.

### Dependencies.
* Maya: Please install Maya on your Windows PC.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page): I used Eigen for linear algebra in **LaplacianSmoother** plug-in.
    - Recommended to lactate Eigen include directory in $ENV{EXT\_LIB\_ROOT}/Eigen/${EIGEN\_VERSION}/include.

Installed libraries will be used for CMake build process.

### Directory structure

Root directory:

* build: CMake will generate Visual Studio solutions in this directory.
* cmake: CMake modules.
* **NoiseCmd**: NoiseCmd project directory.
* **NoiseDeformer**: NoiseCmd project directory.
* **LaplacianSmoother**: NoiseCmd project directory.

Each project:

* build: CMake will generate Visual Studio solutions in this directory.
* plugins: Plug-in file **${PROJECT\_NAME}${MAYA\_VERSION}.mll** (e.g. NoiseDeformer2015.mll) will be built in this directory.
* src: Project source directory.
* doxygen: doxygen setting for API document.

### Build plug-ins

Each project can be easily build with CMake (version 3.0.0 or higher).

#### 1.External libraries.
* Maya: [cmake/FindMaya.cmake](cmake/FindMaya.cmake) will find the Maya include and library directories.
    - *Note*: Assume default installation path. (e.g. C:/Program Files/Autodesk/Maya${version})
* Eigen: [cmake/FindEigen.cmake](cmake/FindEigen.cmake)
    - *Note*: Assume an installation path $ENV{EXT\_LIB\_ROOT}/Eigen/${EIGEN\_VERSION}/include.

#### 2.Generate a Visual Studio solution with the following command.

``` bash
  # See also cmake_generate.bat
  > cd build
  > cmake .. -G "Visual Studio 11 Win64"
  > cd ..
```

You can specify a version and target platform with **-G** (generator) option.

|Product name  |Version number | Target platform | Generator option |
|--------------|---------------|-----------------|-----------------|
|Visual Studio 2008| 9.0       | 32-bit     | "Visual Studio 9" |
|Visual Studio 2008| 9.0       | 64-bit     | "Visual Studio 9 Win64"|
|Visual Studio 2010| 10.0       | 32-bit     | "Visual Studio 10" |
|Visual Studio 2010| 10.0       | 64-bit     | "Visual Studio 10 Win64"|
|Visual Studio 2012| 11.0       | 32-bit     | "Visual Studio 11" |
|Visual Studio 2012| 11.0       | 64-bit     | "Visual Studio 11 Win64"|
|Visual Studio 2013| 12.0       | 32-bit     | "Visual Studio 12" |
|Visual Studio 2013| 12.0       | 64-bit     | "Visual Studio 12 Win64"|

Please also check the Visual Studio version used in your Maya.
Using the same version is highly recommended for stable running.

|Maya version |Visual Studio version |
|--------------|---------------|
|Maya2011      | "Visual Studio 9"|
|Maya2012      | "Visual Studio 9"|
|Maya2013      | "Visual Studio 10"|
|Maya2014      | "Visual Studio 10|
|Maya2015      | "Visual Studio 11"|
|Maya2016      | "Visual Studio 11"|

#### 3.Build a plug-in file with the following command.

``` bash
  # See also cmake_build.bat
  > cmake --build ./build --config Release
```

**${PROJECT\_NAME}${MAYA\_VERSION}.mll** will be build in the plugins directory.

#### 4.Build all plug-in files.

You can also generate a solution file for all plug-ins and build them at once.
I also provide the same CMake mechanism for the root directory.

*Note*: See **cmake\_generate.bat**, **cmake\_build.bat** in the root directory.


## License

The MIT License 2015 (c) tody