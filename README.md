
Maya Plug-in Samples (C++, Windows)
====

Simple Maya plug-in samples to test build environments on Windows.

* [**NoiseCmd**](NoiseCmd) : Simple noise command (command plug-in).
* [**NoiseDeformer**](NoiseDeformer): Simple noise node (deformer plug-in).
* [**LaplacianSmoother**](LaplacianSmoother): Laplacian smoothing node (deformer plug-in).
    - *Required*: [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) library.
* [**OpenMeshCmd**](OpenMeshCmd): Simple command to test OpenMesh (command plug-in).
    - *Required*: [OpenMesh](http://www.openmesh.org/) library.

## Result
1. Load original mesh
2. Add noise to the mesh with NoiseDeformer
3. Smooth mesh with LaplacianSmoother

| ![LaplacianSmoother1] (LaplacianSmoother/results/laplacian_smoother.1.png) | ![LaplacianSmoother2] (LaplacianSmoother/results/laplacian_smoother.2.png) | ![LaplacianSmoother3] (LaplacianSmoother/results/laplacian_smoother.3.png) |![LaplacianSmoother4] (LaplacianSmoother/results/laplacian_smoother.4.png) |
|-------------------------|-----------------|-----------------|----------------|
| Original mesh   | NoiseDeformer  | LaplacianSmoother (weak smoothing)  |LaplacianSmoother (strong smoothing)  |

## Installation

*Note*: This program was mainly tested on **Windows** with **Maya2014, 2015**.
**Linux** and **Mac OS** are not officially supported,
but the following instructions might be helpful for installing on those environments.

### Dependencies.
For CMake build process:

* Maya (version 2010 or higher)
    - Please install Maya on your Windows PC.
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) (version 3.1 or higher)
    - Eigen is used in **LaplacianSmoother** plug-in.
    - Recommended to lactate Eigen directory in `$ENV{EXT_LIB_ROOT}/Eigen/${EIGEN_VERSION}`.
* [OpenMesh](http://www.openmesh.org/) (version 3.0 or higher)
    - OpenMesh is used in **OpenMeshCmd** plug-in.
    - Recommended to lactate OpenMesh directory in `$ENV{EXT_LIB_ROOT}/OpenMesh/${OPENMESH_VERSION}`.

For test batch generation:

* Python (version 2.7 or higher)

### Directory structure

Root directory:
* batch: Test batch files will be generated in this directory by `batch.py`.
* build: CMake will generate Visual Studio solutions in this directory.
* cmake: CMake modules.
* **NoiseCmd**: NoiseCmd project directory.
* **NoiseDeformer**: NoiseDeformer project directory.
* **LaplacianSmoother**: LaplacianSmoother project directory.
* **OpenMeshCmd**: OpenMeshCmd project directory.

Each project:

* build: CMake will generate Visual Studio solutions in this directory.
* plugins: Plug-in file **`${PROJECT_NAME}${MAYA_VERSION}.mll`** (e.g. `NoiseDeformer2015.mll`) will be built in this directory.
* src: Project source directory.
* doxygen: doxygen setting for API document.

### Build plug-ins

Each project can be easily build with CMake (version 3.0.0 or higher).

#### 1.External libraries.
Please check the external library locations:

* Maya: [`cmake/FindMaya.cmake`](cmake/FindMaya.cmake) will find the Maya include and library directories.
    - *Note*: Assume the default installation path. (e.g. `C:/Program Files/Autodesk/Maya${MAYA_VERSION}`)
* Eigen: [`cmake/FindEigen.cmake`](cmake/FindEigen.cmake)
    - *Note*: Assume `"$ENV{EXT_LIB_ROOT}/Eigen/${EIGEN_VERSION}"` for the installation path.
* OpenMesh: [`cmake/FindOpenMesh.cmake`](cmake/FindOpenMesh.cmake)
    - *Note*: Assume `"$ENV{EXT_LIB_ROOT}/OpenMesh/${OPENMESH_VERSION}"` for the installation path.

The directory structure for each library (e.g. OpenMesh 4.1):

* `"$ENV{EXT_LIB_ROOT}/OpenMesh/4.1"`: Package location.
    - `include`: Include directory.
    - `lib`: Library directory.
        - `x86`: 32-bit .lib .dll file.
        - `x64`: 64-bit .lib .dll file.

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

**`${PROJECT_NAME}${MAYA_VERSION}.mll`** will be built in the `plugins` directory.

#### 4.Build all plug-in files.

You can also generate a single solution file for all plug-ins and build them at once.
I also provide the same CMake mechanism from the root directory.

*Note*: See [`cmake_generate.bat`](./cmake_generate.bat), [`cmake_build.bat`](cmake_build.bat) in the root directory.

#### 5.Generate test batches.

From batch directory, please run `batch.py`.

``` bash
  > python batch.py
```

This module will generate test batch files (e.g. `Maya2015_EN.bat`) to configure built plug-in files in Maya environment variables.
Each bath set the following Maya environment variables for the projects before launching Maya.

* `MAYA_PLUG_IN_PATH`: `${PROJECT_NAME}/plugins`
* `MAYA_SCRIPT_PATH`: `${PROJECT_NAME}/scripts/mel`
* `PYTHONPATH`: `${PROJECT_NAME}/scripts/python`
* `XBMLANGPATH`: `${PROJECT_NAME}/scripts/icons`

Finally, the batch launches Maya with a target language setting.

``` bash
  > set MAYA_UI_LANGUAGE=en_US
  > "C:\Program Files\Autodesk\Maya2015\bin\maya.exe"
```

## Usage

1. Launch Maya from a batch file in the batch directory. e.g. `batch/Maya2015_EN.bat`.
2. Paste the command in the Maya **Python** script editor.

``` python
# Create tool UI for plug-ins.
import tool_ui
tool_ui.toolUI()
```

You can easily access the Load Plug-in command from the UI.
For more details of the usage about each plug-in,
please see the README in the project directory.

* [**NoiseCmd**](NoiseCmd).
* [**NoiseDeformer**](NoiseDeformer).
* [**LaplacianSmoother**](LaplacianSmoother).

## License

The MIT License 2015 (c) tody