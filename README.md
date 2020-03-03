# Barcode Panorama Stitch
The sample code demonstrates how to use [Dynamsoft Panorama SDK ](https://www.dynamsoft.com/Products/barcode-inventory-system.aspx) to create a simple barcode reader app used to recognize and stitch barcode images from webcam or video files on Windows.

## Installation

- [Dynamsoft Panorama SDK 1.0](https://www.dynamsoft.com/Downloads/Dynamic-Barcode-Reader-Download.aspx?edition=panorama)
- [OpenCV 3.4.7](https://github.com/opencv/opencv/archive/3.4.7.zip)
- [Visual Studio 2017](https://www.visualstudio.com/downloads/)  
- [cmake-3.15.2-win64-x64.msi](https://github.com/Kitware/CMake/releases/download/v3.15.2/cmake-3.15.2-win64-x64.msi)

## Usage

Get a valid trial license from the installer of Dynamsoft Panorama SDK or the online [portal](https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx). Then set the license in `BarcodeReader.cxx`:

```c++
int ret = panoramaStitcher->InitLicense("LICENSE-KEY");
```

Build the project with CMake:

```
mkdir build
cd build
cmake -G"Visual Studio 15 2017 Win64" ..
cmake --build . 
```

Run the app in `cmd.exe`.

**Webcam**

```
.\Debug\BarcodeReader.exe 
```

**Video File**

```
.\Debug\BarcodeReader.exe <video-file>
```


