/*
*	@file DynamsoftPanorama.h
*	
*	Dynamsoft Panorama 1.0.0 C/C++ API header file.
*	Copyright 2020 Dynamsoft Corporation. All rights reserved.
*	
*	@version 1.0.0
*	@author Dynamsoft
*	@date 02/11/2020
*/

#ifndef __DYNAMESOFT_IMAGE_STITCHER_H__
#define __DYNAMESOFT_IMAGE_STITCHER_H__

#if !defined(_WIN32) && !defined(_WIN64)
#define DPS_API __attribute__((visibility("default")))
#ifdef __APPLE__
#else
typedef signed char BOOL;
#endif
typedef void* HANDLE;
#include <stddef.h>
#else
#ifdef DPS_EXPORTS
#define DPS_API __declspec(dllexport)
#else
#define DPS_API 
#endif
#include <windows.h>
#endif

/**
* @defgroup CandCPlus C/C++ APIs
* @{
* Dynamsoft Image Stitcher 1.0.0 - C/C++ APIs Description.
*/
#define DPS_VERSION                  "1.0.0.0000"

#pragma region ErrorCode
/**
 * @defgroup ErrorCode ErrorCode
 * @{
 */

 /**Successful. */
#define DPS_OK									 0 

 /**Unknown error. */
#define DPSERR_UNKNOWN						-10000 

 /**Not enough memory to perform the operation. */
#define DPSERR_NO_MEMORY					-10001 

 /**The license is invalid. */
#define DPSERR_LICENSE_INVALID				-10003 

 /**The license has expired. */
#define DPSERR_LICENSE_EXPIRED				-10004 

 /**The file is not found. */
#define DPSERR_FILE_NOT_FOUND				-10005 

 /**The License DLL is missing. */
#define	DPSERR_LICENSE_DLL_MISSING		    -10042

 /**The license key does not match the license content. */
#define DPSERR_LICENSEKEY_NOT_MATCHED       -10043

 /**Failed to request the license content. */
#define DPSERR_REQUESTED_FAILED             -10044

 /**Failed to init the license. */
#define DPSERR_LICENSE_INIT_FAILED          -10045

 /**The license content is invalid. */
#define DPSERR_LICENSE_CONTENT_INVALID      -10052

 /**The license key is invalid. */
#define DPSERR_LICENSE_KEY_INVALID			-10053

 /**The device number in the license key runs out. */
#define DPSERR_LICENSE_DEVICE_RUNS_OUT      -10054

 /**The Intermediate Result Types license is invalid. */
#define DPSERR_IRT_LICENSE_INVALID			-10056


 /**Null pointer. */
#define DPSERR_DBR_NULL_POINTER					-10002 

 /**The file type is not supported. */
#define DPSERR_DBR_FILETYPE_NOT_SUPPORTED		-10006 

 /**The BPP (Bits Per Pixel) is not supported. */
#define DPSERR_DBR_BPP_NOT_SUPPORTED			-10007 

 /**The DIB (Device-Independent Bitmaps) buffer is invalid. */
#define DPSERR_DBR_DIB_BUFFER_INVALID			-10018

 /**Recognition timeout. */
#define DPSERR_DBR_RECOGNITION_TIMEOUT			-10026

 /**Failed to parse JSON string. */
#define DPSERR_DBR_JSON_PARSE_FAILED			-10030

 /**The value type is invalid. */
#define DPSERR_DBR_JSON_TYPE_INVALID			-10031

 /**The key is invalid. */
#define DPSERR_DBR_JSON_KEY_INVALID				-10032

 /**The value is invalid or out of range. */
#define DPSERR_DBR_JSON_VALUE_INVALID			-10033

 /**The mandatory key "Name" is missing. */
#define DPSERR_DBR_JSON_NAME_KEY_MISSING		-10034

 /**The value of the key "Name" is duplicated. */
#define DPSERR_DBR_JSON_NAME_VALUE_DUPLICATED	-10035

 /**The template name is invalid. */
#define DPSERR_DBR_TEMPLATE_NAME_INVALID		-10036

 /**The name reference is invalid. */
#define DPSERR_DBR_JSON_NAME_REFERENCE_INVALID	-10037

 /**The parameter value is invalid or out of range. */
#define DPSERR_DBR_PARAMETER_VALUE_INVALID      -10038

 /**The domain of your current site does not match the domain bound in the current product key. */
#define DPSERR_DBR_DOMAIN_NOT_MATCHED           -10039

 /**The reserved info does not match the reserved info bound in the current product key. */
#define DPSERR_DBR_RESERVEDINFO_NOT_MATCHED     -10040 

/**Failed to read the image. */
#define DPSERR_DBR_IMAGE_READ_FAILED			-11001

/**Some barcode licenses are invalid. */
#define DPSERR_DBR_SOME_BARCODE_LICENSE_INVALID	-11002

/**An error occurs in the DBR JSON settings. */
#define DPSERR_DBR_JSON_FAILED					-11003



/**Errorcode call-back function already exists. */
#define DPSERR_ERROR_CALLBACK_EXISTS        -20001

/**Result call-back function already exists. */
#define DPSERR_RESULT_CALLBACK_EXISTS       -20002

/**NULL input pointer in Panorama. */
#define DPSERR_INPUT_NULL_POINTER			-20003

/**The DBR Version is invalid. */
#define DPSERR_DBR_VERSION_INVALID			-20004

/**Panorama has been started. */
#define DPSERR_PANORAMA_ALREADY_STARTED     -20006

/**Panorama is not started before appending frames. */
#define DPSERR_PANORAMA_NOT_STARTED			-20007

/**Panorama is not stopped before getting final results. */
#define DPSERR_PANORAMA_NOT_STOP			 -20008

/**Panorama is already started by file. */
#define DPSERR_PANORAMA_STARTED_BY_FILE		 -20009

/**Panorama is already started by buffer. */
#define DPSERR_PANORAMA_STARTED_BY_BUFFER	 -20010

/**No stitched images exist. */
#define DPSERR_STITCHED_IMAGE_NOT_EXISTS     -20013

/**The overlap region is invalid. */
#define DPSERR_OVERLAP_REGION_INVALID		-20030
 
/**The frames can not continue to be stitched in overlap mode. */
#define DPSERR_OVERLAP_MODE_STITCH_STOPED	-21001

/**
 * @}defgroup ErrorCode
 */

#pragma endregion

#pragma region Enum
 /**
 * @defgroup Enum Enumerations
 * @{
 */

 /**
 * @enum DPS_BarcodeFormat
 *
 * Describes the barcode types in BarcodeFormat group 1. All the formats can be combined, such as DPS_BF_CODE_39 | DPS_BF_CODE_128.\n
 * Note: The barcode format our library will search for is composed of [BarcodeFormat group 1](@ref DPS_BarcodeFormat) and [BarcodeFormat group 2](@ref DPS_BarcodeFormat_2), so you need to specify the barcode format in group 1 and group 2 individually.
 */
typedef enum
{
	/**All supported formats in BarcodeFormat group 1*/
#if defined(_WIN32) || defined(_WIN64)
	DPS_BF_ALL = 0xFE0FFFFF,
#else
	DPS_BF_ALL = -32505857,
#endif

	/**Combined value of DPS_BF_CODABAR, DPS_BF_CODE_128, DPS_BF_CODE_39, DPS_BF_CODE_39_Extended, DPS_BF_CODE_93, DPS_BF_EAN_13, DPS_BF_EAN_8, INDUSTRIAL_25, DPS_BF_ITF, DPS_BF_UPC_A, DPS_BF_UPC_E; */
	DPS_BF_ONED = 0x000007FF,

	/**Combined value of DPS_BF_GS1_DATABAR_OMNIDIRECTIONAL, DPS_BF_GS1_DATABAR_TRUNCATED, DPS_BF_GS1_DATABAR_STACKED, DPS_BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL, DPS_BF_GS1_DATABAR_EXPANDED, DPS_BF_GS1_DATABAR_EXPANDED_STACKED, DPS_BF_GS1_DATABAR_LIMITED*/
	DPS_BF_GS1_DATABAR = 0x0003F800,

	/**Code 39 */
	DPS_BF_CODE_39 = 0x1,

	/**Code 128 */
	DPS_BF_CODE_128 = 0x2,

	/**Code 93 */
	DPS_BF_CODE_93 = 0x4,

	/**Codabar */
	DPS_BF_CODABAR = 0x8,

	/**ITF */
	DPS_BF_ITF = 0x10,

	/**EAN-13 */
	DPS_BF_EAN_13 = 0x20,

	/**EAN-8 */
	DPS_BF_EAN_8 = 0x40,

	/**UPC-A */
	DPS_BF_UPC_A = 0x80,

	/**UPC-E */
	DPS_BF_UPC_E = 0x100,

	/**Industrial 2 of 5 */
	DPS_BF_INDUSTRIAL_25 = 0x200,

	/**CODE39 Extended */
	DPS_BF_CODE_39_EXTENDED = 0x400,

	/**GS1 Databar Omnidirectional*/
	DPS_BF_GS1_DATABAR_OMNIDIRECTIONAL = 0x800,

	/**GS1 Databar Truncated*/
	DPS_BF_GS1_DATABAR_TRUNCATED = 0x1000,

	/**GS1 Databar Stacked*/
	DPS_BF_GS1_DATABAR_STACKED = 0x2000,

	/**GS1 Databar Stacked Omnidirectional*/
	DPS_BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL = 0x4000,

	/**GS1 Databar Expanded*/
	DPS_BF_GS1_DATABAR_EXPANDED = 0x8000,

	/**GS1 Databar Expaned Stacked*/
	DPS_BF_GS1_DATABAR_EXPANDED_STACKED = 0x10000,

	/**GS1 Databar Limited*/
	DPS_BF_GS1_DATABAR_LIMITED = 0x20000,

	/**Patch code. */
	DPS_BF_PATCHCODE = 0x00040000,

	/**PDF417 */
	DPS_BF_PDF417 = 0x02000000,

	/**QRCode */
	DPS_BF_QR_CODE = 0x04000000,

	/**DataMatrix */
	DPS_BF_DATAMATRIX = 0x08000000,

	/**AZTEC */
	DPS_BF_AZTEC = 0x10000000,

	/**MAXICODE */
	DPS_BF_MAXICODE = 0x20000000,

	/**Micro QR Code*/
	DPS_BF_MICRO_QR = 0x40000000,

	/**Micro PDF417*/
	DPS_BF_MICRO_PDF417 = 0x00080000,

	/**GS1 Composite Code*/
#if defined(_WIN32) || defined(_WIN64)
	DPS_BF_GS1_COMPOSITE = 0x80000000,
#else
	DPS_BF_GS1_COMPOSITE = -2147483648,
#endif

	/**No barcode format in BarcodeFormat group 1*/
	DPS_BF_NULL = 0x00


}DPS_BarcodeFormat;

/**
* @enum DPS_BarcodeFormat_2
*
* Describes the barcode types in BarcodeFormat group 2.\n
* Note: The barcode format our library will search for is composed of [BarcodeFormat group 1](@ref DPS_BarcodeFormat) and [BarcodeFormat group 2](@ref DPS_BarcodeFormat_2), so you need to specify the barcode format in group 1 and group 2 individually.
*/
typedef enum
{
	/**No barcode format in BarcodeFormat group 2*/
	DPS_BF2_NULL = 0x00,

	/**Combined value of DPS_BF2_USPSINTELLIGENTMAIL, DPS_BF2_POSTNET, DPS_BF2_PLANET, DPS_BF2_AUSTRALIANPOST, DPS_BF2_RM4SCC. */
	DPS_BF2_POSTALCODE = 0x01F00000,

	/**Non-standard barcode */
	DPS_BF2_NONSTANDARD_BARCODE = 0x01,

	/**USPS Intelligent Mail. */
	DPS_BF2_USPSINTELLIGENTMAIL = 0x00100000,

	/**Postnet. */
	DPS_BF2_POSTNET = 0x00200000,

	/**Planet. */
	DPS_BF2_PLANET = 0x00400000,

	/**Australian Post. */
	DPS_BF2_AUSTRALIANPOST = 0x00800000,

	/**Royal Mail 4-State Customer Barcode. */
	DPS_BF2_RM4SCC = 0x01000000
}DPS_BarcodeFormat_2;

/**
* @enum DPS_ImagePixelFormat
*
* Describes the image pixel format.
*/
typedef enum
{
	/**0:Black, 1:White */
	DPS_IPF_BINARY,

	/**0:White, 1:Black */
	DPS_IPF_BINARYINVERTED,

	/**8bit gray */
	DPS_IPF_GRAYSCALED,

	/**NV21 */
	DPS_IPF_NV21,

	/**16bit */
	DPS_IPF_RGB_565,

	/**16bit */
	DPS_IPF_RGB_555,

	/**24bit */
	DPS_IPF_RGB_888,

	/**32bit */
	DPS_IPF_ARGB_8888,

	/**48bit */
	DPS_IPF_RGB_161616,

	/**64bit */
	DPS_IPF_ARGB_16161616

}DPS_ImagePixelFormat;

/**
* @} defgroup Enum Enumerations
*/

#pragma endregion

#pragma region Struct
//---------------------------------------------------------------------------
// Structures
//---------------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

/**
* @defgroup Struct Struct
* @{
*/

/**
* @defgroup DPS_RuntimeSettings DPS_RuntimeSettings
* @{
*/
/**
* Defines a struct to configure the panorama settings.
* These settings control the panorama stitching process such as the scale ratio of preview images.
*/
struct DPS_RuntimeSettings
{
	/**Sets the formats of the barcode in BarcodeFormat group 1 to be read. Barcode formats in BarcodeFormat group 1 can be combined.
	*
	* @par Value range:
	* 	    A combined value of DPS_BarcodeFormat Enumeration items
	* @par Default value:
	* 	    DPS_BF_ALL
	* @par Remarks:
	*	    If the barcode type(s) are certain, specifying the barcode type(s) to be read will speed up the recognition process.
	*		The barcode format our library search for is composed of [BarcodeFormat group 1](@ref DPS_BarcodeFormat) and [BarcodeFormat group 2](@ref DPS_BarcodeFormat_2), so you need to specify the barcode format in group 1 and group 2 individually.
	* @sa DPS_BarcodeFormat, DPS_BarcodeFormat_2
	*/
	int barcodeFormatIds;

	/**Sets the formats of the barcode in BarcodeFormat group 2 to be read. Barcode formats in BarcodeFormat group 2 can be combined.
	*
	* @par Value range:
	* 	    A combined value of DPS_BarcodeFormat_2 Enumeration items
	* @par Default value:
	* 	    DPS_BF2_NULL
	* @par Remarks:
	*	    If the barcode type(s) are certain, specifying the barcode type(s) to be read will speed up the recognition process.
	*		The barcode format our library search for is composed of [BarcodeFormat group 1](@ref DPS_BarcodeFormat) and [BarcodeFormat group 2](@ref DPS_BarcodeFormat_2), so you need to specify the barcode format in group 1 and group 2 individually.
	* @sa DPS_BarcodeFormat, DPS_BarcodeFormat_2
	*/
	int barcodeFormatIds_2;

	/**Sets the functional mode to Panorama mode(0) or Overlap mode(1).
	*
	* @par Value range:
	* 	    0 or 1
	* @par Default value:
	* 	    0
	* @par Remarks:
	*	    0: Panorama mode.
	*	    1: Overlap mode.
	*
	*/
	int functionalMode;

	/**Sets the scale ratio of preview images.
	*
	* @par Value range:
	* 	    (0, 1]
	* @par Default value:
	* 	    0.5
	* @par Remarks:
	*		When result call back function is not setted and resultImgScaleRatio is more than 0, 
	*		this parameter will be covered by resultImgScaleRatio in the start function.\n
	*		The value is fixed at 1 in Overlap mode.
	*
	*/
	float previewImgScaleRatio;

	/**Sets the scale ratio of result images.
	*
	* @par Value range:
	* 	    [0, 1]
	* @par Default value:
	* 	    0
	* @par Remarks:
	*		When you call the function GetFinalResults(DPS_GetFinalResults) with the default value 0,
	*		the scale ratio of final result image is equal to preview image.\n
	*		The value is fixed at 0 in Overlap mode.
	*
	*/
	float resultImgScaleRatio;

	/**Sets the stitching accuracy level to precise(9) level or standard(0) level.Not supported yet.
	*
	* @par Value range:
	* 	    [0, 9]
	* @par Default value:
	* 	    5
	* @par Remarks:
	*		0: standard level. 9: precise level. 
	*		Higher level result in higher stitching success rate and more accurate in stitching results.\n
	*		This parameter is not supported in this version.
	*
	*/
	int stitchingAccuracyLevel;

	/**Sets whether duplicate codes exist.
	*
	* @par Value range:
	* 	    0 or 1
	* @par Default value:
	* 	    1
	*
	*/
	int ifExistDuplicateCode;

	/**Sets the max number of thread used for the panorama program.
	*
	* @par Value range:
	* 	    (0, 30]
	* @par Default value:
	* 	    15
	* @par Remarks:
	*		To keep a balance between speed and quality, the library concurrently runs fifteen independent threads for Panorama by default. 
	*
	*/
	int maxThreadNumber;

	/**Sets the frame buffer size stored in the panorama program.
	*
	* @par Value range:
	* 	    [20, 10000]
	* @par Default value:
	* 	    100
	* @par Remarks:
	*		To control the momery usage, the max number of frame buffer storage is concurrently limited to one hundred by default.
	*
	*/
	int frameBufferSize;

	/**Sets the max memory size used by the Panorama program.
	*
	* @par Value range:
	* 	    (0, 0x7fffffff]
	* @par Default value:
	* 	    1024
	* @par Remarks:
	*		To avoid memory overflow, the max memory size is limited to 1024 MB by default.
	*
	*/
	int maxMemorySize;

	/**Sets the incoming way of frames when appending.
	*
	* @par Value range:
	* 	    0 or 1
	* @par Default value:
	* 	    1
	* @par Remarks:
	*		0:input frames from files.
	*		1:input frames from video streams.\n
	*		The value is fixed at 0 in Overlap mode.
	*
	*/
	int inputSourceMode;

	/**Sets the camera moving route. 0 means moving the camera in one way or an "L" way, 1 means moving the camera in a circle.
	*
	* @par Value range:
	* 	    0 or 1
	* @par Default value:
	* 	    0
	* @par Remarks:
	*		The value is fixed at 0 in Overlap mode.
	*
	*/
	int scanPathMode;

	/**Sets the overlap region of the previous frame.
	*
	* @par Value range:
	* 	    [0, 7fffffff]
	* @par Default value:
	* 	    {0, 0, 0, 0 ,0 ,0 ,0 ,0}
	* @par Remarks:
	*		Used with nextFrameOverlapRegion to set the overlap region of two adjacent frames.\n
	*		This parameter is invalid in Overlap mode.
	*
	*/
	int previousFrameOverlapRegion[8];

	/**Sets the overlap region of next frame.
	*
	* @par Value range:
	* 	    [0, 7fffffff]
	* @par Default value:
	* 	    {0, 0, 0, 0 ,0 ,0 ,0 ,0}
	* @par Remarks:
	*		Used with previousFrameOverlapRegion to set the overlap region of two adjacent frames.\n
	*		This parameter is invalid in Overlap mode.
	*
	*/
	int nextFrameOverlapRegion[8];

	/**Reserved memory for struct. The length of this array indicates the size of the memory reserved for this struct.	*/
	char reserved[64];
};

/**
* @} defgroup DPS_RuntimeSettings
*/

/**
* @defgroup DMBitmap DMBitmap
* @{
*/
/**
* Stores the image data.
*
*/
struct DMBitmap
{
	/**The width of the image in pixels */
	int iWidth;

	/**The height of the image in pixels */
	int iHeight;

	/**The number of bits per pixel */
	int iBitCount;

	/**The number of colour indices in the colour table that are actually used by the bitmap */
	int iClrUsed;

	/**The block of bytes(a table) listing the colours available for use*/
	unsigned char *pPalette;

	/**The size image in bytes */
	int iImageSize;

	/**The data of the image */
	unsigned char *pImageData;

};

/**
* @} defgroup DMBitmap
*/

/**
* @defgroup BarcodeInfo BarcodeInfo
* @{
*/
/**
* Stores the information of the barcode.
*
*/
typedef struct BarcodeInfo
{
	/**Barcode type in BarcodeFormat group 1 */
	DPS_BarcodeFormat barcodeFormat;

	/**Barcode type in BarcodeFormat group 1 as string */
	const char* barcodeFormatString;

	/**Barcode type in BarcodeFormat group 2*/
	DPS_BarcodeFormat_2 barcodeFormat_2;

	/**Barcode type in BarcodeFormat group 2 as string */
	const char* barcodeFormatString_2;
	
	/**The barcode text, ends by '\0' */
	const char* barcodeText;

	/**The barcode content in a byte array */
	unsigned char* barcodeBytes;

	/**The length of the byte array */
	int barcodeBytesLength;

	/**The confidence score of barcode */
	int confidence;

	/**The X coordinate of the first point */
	int x1;

	/**The Y coordinate of the first point */
	int y1;

	/**The X coordinate of the second point in a clockwise direction */
	int x2;

	/**The Y coordinate of the second point in a clockwise direction */
	int y2;

	/**The X coordinate of the third point in a clockwise direction */
	int x3;

	/**The Y coordinate of the third point in a clockwise direction */
	int y3;

	/**The X coordinate of the fourth point in a clockwise direction */
	int x4;

	/**The Y coordinate of the fourth point in a clockwise direction */
	int y4;

	/**Reserved memory for struct. The length of this array indicates the size of the memory reserved for this struct.	*/
	char reserved[64];
}*pBarcodeInfo;

/**
* @} defgroup BarcodeInfo
*/

/**
* @defgroup PanoramaResult PanoramaResult
* @{
*/
/**
* Stores stitched images and barcodes.
*
*/
typedef struct PanoramaResult
{
	/**The number of the barcode */
	int barcodeNumber;

	/**The array of the barcode info */
	pBarcodeInfo* barcodes;

	/**The stitched image */
	DMBitmap* resultImg;

	/**The number of stitched images in a result image */
	int stitchedImgsNumber;

	/**The index of the firstly stitched image in a result image */
	int indexOfFirstFrameInResultImg;

	/**The index of the lastly stitched image in a result image */
	int indexOfLastFrameInResultImg;

	/**Reserved memory for struct. The length of this array indicates the size of the memory reserved for this struct.	*/
	char reserved[64];

}*pPanoramaResult;

/**
* @} defgroup PanoramaResult
*/

/**
* @defgroup PanoramaResultArray PanoramaResultArray
* @{
*/
/**
* Stores the array of Panorama result.
*
*/
struct PanoramaResultArray
{
	/**The count of Panorama results */
	int resultCount;

	/**The Panorama result array */
	pPanoramaResult* panoramaResult;
};

/**
* @} defgroup PanoramaResultArray
*/

/**
* @defgroup RunningState RunningState
* @{
*/
/**
* Stores running state of the Panorama stitcher.
*
*/
struct RunningState
{
	/**The mean value of all overlap rates of two adjacent images in last one second */
	float overlapAreaRate;

	/**The number of images which are stitched in last one second */
	int stitchRate;

	/**The total number of decoded frames since started appending frame */
	int totalDecodedFrameCount;

	/**Reserved memory for struct. The length of this array indicates the size of the memory reserved for this struct.	*/
	char reserved[64];
};

/**
* @} defgroup RunningState
* @}defgroup Struct Struct
*/

#pragma pack(pop)

#pragma endregion

#pragma region FunctionPointer
/**
* @defgroup FunctionPointer Function Pointer
* @{
*/
/**
* Represents the method that will handle the stitched image and panorama result returned by the SDK.
*
* @param pResult The panorama result array.
* @param pUser Customized arguments passed to your function.
*
* @sa PanoramaResult
*/
typedef void(*CB_PanoramaResult)(PanoramaResultArray** pResult, void* pUser);

/**
* Represents the method that will handle the error code returned by the SDK.
*
* @param errorCode Error Code generated when stitching frames.
* @param pUser Customized arguments passed to your function.
*
* @sa ErrorCode
*/
typedef void(*CB_PanoramaErrorCode)(int errorCode, void* pUser);

/**
* @}defgroup Function Pointer
*/

#pragma endregion

#pragma region C/C++ Function
//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------


#ifdef __cplusplus
/** . */
extern "C" {
#endif // endif of __cplusplus.

	/**
	* @defgroup CFunctions C Functions
	* @{
	*/

	/**
	* @defgroup CGeneral General Functions
	* @{
	*   APIs for getting global info.
	*/

	/**
	* Returns the error info string.
	*
	* @param [in] errorCode The error code.
	*
	* @return The error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		const char* errorString = DPS_GetErrorString(ret);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	*/
	DPS_API const char* DPS_GetErrorString(int errorCode);

	/**
	* Returns the version info of the SDK.
	*
	* @return The version info string.
	*
	* @par Code Snippet:
	* @code
		const char* versionInfo = DPS_GetVersion();
	* @endcode
	*/
	DPS_API const char* DPS_GetVersion();

	/**
	* @}defgroup CGeneral
	*/

	/**
	* @defgroup CInitialization Initialization Functions
	* @{
	*   APIs for Dynamsoft Panorama SDK initialization.
	*/

	/**
	* Creates an instance of Dynamsoft Panorama.
	*
	* @return Returns an instance of Dynamsoft Panorama. If failed, it returns NULL.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_DestroyInstance(panorama);
	* @endcode
	*/
	DPS_API void* DPS_CreateInstance();

	/**
	* Destroys an instance of Dynamsoft Panorama.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_DestroyInstance(panorama);
	* @endcode
	*/
	DPS_API void DPS_DestroyInstance(void* hStitcher);

	/**
	* Reads the product key and activates the SDK.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pLicense The product key.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		DPS_DestroyInstance(panorama);
	* @endcode
	*/
	DPS_API int DPS_InitLicense(void* hStitcher, const char* pLicense);

	/**
	* Initializes Panorama license and connects to the specified server for online verification.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pLicenseServer The name/IP of the license server.
	* @param [in] pLicenseKey The license key.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	*/
	DPS_API int DPS_InitLicenseFromServer(void* hStitcher, const char* pLicenseServer, const char* pLicenseKey);

	/**
	* Initializes Panorama license from the license content on the client machine for offline verification.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pLicenseKey The license key.
	* @param [in] pLicenseContent An encrypted string which represents the license content (quota, expiration date, barcode type, etc.) obtained from the method DPS_OutputLicenseToString().
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	*/
	DPS_API int DPS_InitLicenseFromLicenseContent(void* hStitcher, const char* pLicenseKey, const char* pLicenseContent);

	/**
	* Outputs the license content as an encrypted string from the license server to be used for offline license verification.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in, out] content The output string which stores the content of the license.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	* @par Remarks:
	*	    You need to call DPS_InitLicenseFromServer() prior to DPS_OutputLicenseToStringPtr() method.
	*/
	DPS_API int DPS_OutputLicenseToStringPtr(void* hStitcher, char** content);

	/**
	*Frees memory allocated for the license string.
	*
	* @param [in] content The output string which stores the content of license.
	*
	* @par Remarks:
	*		If you used DPS_OutputLicenseToStringPtr() method, you will need to call this DPS_FreeLicenseString() method to release memory.
	*/
	DPS_API void DPS_FreeLicenseString(char** content);

	/**
	* @}defgroup CInitialization
	*/

	/**
	* @defgroup CBasicSetting Basic Setting Functions
	* @{
	*   Basic APIs used for customizing runtime settings
	*/

	/**
	* Gets current settings and saves them into a struct.
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in,out] pSettings The struct of template settings.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		DPS_RuntimeSettings settings;
		int ret = DPS_GetRuntimeSettings(panorama, &settings);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_GetRuntimeSettings(void* hStitcher, DPS_RuntimeSettings* pSettings);

	/**
	* Updates runtime settings with a given struct.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pSettings The struct of template settings.
	* @param [in,out] error The buffer is allocated by caller and the recommended length
	* 				   is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	*		  DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		DPS_RuntimeSettings settings;
		int ret = DPS_GetRuntimeSettings(panorama, &settings);
		settings.stitchingAccuracyLevel = 0;
		char error[256];
		int ret0 = DPS_UpdateRuntimeSettings(panorama, &settings, error, 256);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_UpdateRuntimeSettings(void* hStitcher, DPS_RuntimeSettings* pSettings, char error[], int errorMsgBufferLen);

	/**
	* @}defgroup CBasicSetting
	*/

	
	/**
	* @defgroup CAdvancedSettings Advanced Setting Functions
	* @{
	*   Advanced APIs for customizing scanning parameters with a template file to fit specified scenarios.
	*/

	/**
	* Initializes Panorama settings with the parameters obtained from a JSON string.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pJsonSetting A JSON string that represents the content of the settings.
	* @param [in,out] error The buffer is allocated by the caller. The recommended
	* 				  length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		char error[256];
		int ret = DPS_InitRuntimeSettingsWithString(panorama, "{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_InitRuntimeSettingsWithString(void* hStitcher, const char* pJsonSetting, char error[], int errorMsgBufferLen);

	/**
	* Outputs runtime settings to a string.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in,out] content The output string which stores the contents of current settings.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		char error[256];
		int ret = DPS_InitRuntimeSettingsWithString(panorama, "{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		char* pContent = NULL;
		DPS_OutputSettingsToStringPtr(panorama, &pContent);
		DPS_FreeSettingsString(&pContent);
		DPS_DestroyInstance(panorama);
	* @endcode
	* @par Remarks:
	*	Changing the parameter value in the output string and calling DPS_InitRuntimeSettingsWithString is also one of ways to init runtime settings.
	*
	*/
	DPS_API int DPS_OutputSettingsToStringPtr(void* hStitcher, char** content);

	/**
	* Frees memory allocated for runtime settings string.
	*
	* @param [in] content The runtime settings string.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		char error[256];
		int ret = DPS_InitRuntimeSettingsWithString(panorama, "{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		char* pContent = NULL;
		DPS_OutputSettingsToStringPtr(panorama, &pContent);
		DPS_FreeSettingsString(&pContent);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	*/
	DPS_API void DPS_FreeSettingsString(char** content);

	/**
	* @}defgroup CAdvancedSettings
	*/

	/**
	* @defgroup CStitching Stitching Functions
	* @{
	*   APIs for panorama stitching.
	*/

	/**
	* Starts threads to manage images reading from file.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_ALREADY_STARTED;
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByFile(panorama);
		DPS_AppendNewFrameByFile(panorama, "C:\\Users\\*****\\1.jpg");
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_StartPanoramaStitchingByFile(void* hStitcher);

	/**
	* Starts threads to manage images reading from buffer.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] iWidth The width of the frame image in pixels.
	* @param [in] iHeight The height of the frame image in pixels.
	* @param [in] iStride The stride (or scan width) of the frame image.
	* @param [in] format The image pixel format used in the image byte array.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_ALREADY_STARTED;
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_StartPanoramaStitchingByBuffer(void* hStitcher,int iWidth, int iHeight, int iStride, DPS_ImagePixelFormat format);

	/**
	* Appends a new frame from a file to the inner frame queue.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pFileName A string defining the file name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_NOT_STARTED;
	* 		  DPSERR_PANORAMA_STARTED_BY_BUFFER;
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByFile(panorama);
		DPS_AppendNewFrameByFile(panorama, "C:\\Users\\*****\\1.jpg");
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	* @par Remarks:
	*	    DPS_StartPanoramaStitchingByFile() has to be successfully called before calling this method.
	* @sa CFunctions
	*/
	DPS_API int DPS_AppendNewFrameByFile(void* hStitcher, const char* pFileName);

	/**
	* Appends a new frame image buffer from a file to the inner frame queue.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] pBuffer The array of bytes which contain the image data.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_NOT_STARTED;
	* 		  DPSERR_PANORAMA_STARTED_BY_FILE;
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	* @par Remarks:
	*	    DPS_StartPanoramaStitchingByBuffer() has to be successfully called before calling this method.
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_AppendNewFrameByBuffer(void* hStitcher, const unsigned char* pBuffer);
	
	/**
	* Waits for finish stitching all frames in the inner frame queue.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_WaitForFinishStitching(panorama);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API void DPS_WaitForFinishStitching(void* hStitcher);

	/**
	* Stops stitching immediately, will not stitch the remaining frames in the inner frame queue.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API void DPS_StopPanoramaStitching(void* hStitcher);

	/**
	* @}defgroup CStitching
	*/
	
	/**
	* @defgroup CResults Results Functions
	* @{
	*   APIs for operating results.
	*/

	/**
	* Gets the result image and barcodes.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in,out] pResult The output panorama result array.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_StopPanoramaStitching(panorama);
		PanoramaResultArray* pResult = new PanoramaResultArray();
		DPS_GetFinalResults(panorama, &pResult);
		DPS_FreePanoramaResults(&pResult);
		DPS_DestroyInstance(panorama);
	* @endcode
	* @par Remarks:
	*	    DPS_StopPanoramaStitching() has to be successfully called before calling this method.
	* @sa CFunctions
	*/
	DPS_API int DPS_GetFinalResults(void* hStitcher, PanoramaResultArray** pResult);
	
	/**
	* Gets running state of Panorama program.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in,out] pRunningState The struct of running state.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_INPUT_NULL_POINTER;
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		RunningState pRunningState;
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_GetRunningState(panorama, &pRunningState);
		DPS_StopPanoramaStitching(panorama);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_GetRunningState(void* hStitcher, RunningState* pRunningState);

	/**
	* Frees memory allocated for stitched image and panorama result.
	*
	* @param [in] pPresult The struct of panorama result array.
	*
	* @par Code Snippet:
	* @code
		void* panorama = DPS_CreateInstance();
		DPS_InitLicense(panorama, "t0260NwAAAHV***************");
		int ret = DPS_StartPanoramaStitchingByBuffer(panorama, 1080, 1920, 3240, DPS_IPF_RGB_888);
		DPS_AppendNewFrameByBuffer(panorama, pBuffer);
		DPS_StopPanoramaStitching(panorama);
		PanoramaResultArray* pResult = new PanoramaResultArray();
		DPS_GetFinalResults(panorama, &pResult);
		DPS_FreePanoramaResults(&pResult);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API void DPS_FreePanoramaResults(PanoramaResultArray** pPresult);

	/**
	* @}defgroup CResults
	*/

	/**
	* @defgroup CCallback Callback Functions
	* @{
	*   APIs for setting callback functions.
	*/

	/**
	* Sets callback function to process panorama result, including stitched image and barcodes.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] cbFunction Callback function.
	* @param [in] pUser Customized arguments passed to your function.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message. Possible returns are:
	* 		   DPS_OK;
	* 		   DPSERR_RESULT_CALLBACK_EXISTS;
	*
	* @par Code Snippet:
	* @code
	void ResultFunction(PanoramaResultArray** pResult, void * pUser)
	{
		//TODO add your code for using panorama result
	}
		void* panorama = DPS_CreateInstance();
		DPS_SetResultCallback(panorama, ResultFunction, NULL);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions
	*/
	DPS_API int DPS_SetResultCallback(void* hStitcher, CB_PanoramaResult cbFunction, void * pUser);

	/**
	* Sets callback function to process errors generated during image stitching.
	*
	* @param [in] hStitcher Handle of the Panorama instance.
	* @param [in] cbFunction Callback function.
	* @param [in] pUser Customized arguments passed to your function.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DPS_GetErrorString() to get detailed error message. Possible returns are:
	* 		   DPS_OK;
	* 		   DPSERR_ERROR_CALLBACK_EXISTS;
	*
	* @par Code Snippet:
	* @code
	void ErrorFunction(int errorCode, void * pUser)
	{
		//TODO add your code for using error code
	}
		void* panorama = DPS_CreateInstance();
		DPS_SetErrorCodeCallback(panorama, ErrorFunction, NULL);
		DPS_DestroyInstance(panorama);
	* @endcode
	*
	* @sa CFunctions ErrorCode
	*/
	DPS_API int DPS_SetErrorCodeCallback(void* hStitcher, CB_PanoramaErrorCode cbFunction, void* pUser);

	/**
	* @}defgroup CCallback
	*/


	/**
	* @}defgroup CFunctions
	*/

#ifdef __cplusplus
}
#endif // endif of __cplusplus.


#ifdef __cplusplus
class DM_Panorama;

//---------------------------------------------------------------------------
// Class
//---------------------------------------------------------------------------


/**
*
* @defgroup CPanoramaStitcherClass CPanoramaStitcher Class
* @{
*
*/

/**
* Defines a class that provides functions for working with image stitching and barcode data extracting.
* @class CPanoramaStitcher
*
*/

class DPS_API CPanoramaStitcher
{
protected:
	/** The internal panorama stitcher. */
	DM_Panorama *m_pStitcher;
public:
	/**
	* @{
	*
	* Default constructor
	*
	*/

	CPanoramaStitcher();

	/**
	* Destructor
	*
	*/

	~CPanoramaStitcher();
	/**
	* @}
	*
	*/

	/**
	* @name General Functions
	* @{
	*/

	/**
	* Returns the error info string.
	*
	* @param [in] iErrorCode The error code.
	*
	* @return The error message.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int errorCode = panorama->StartPanoramaStitchingByFile();
		const char* errorString = CPanoramaStitcher::GetErrorString(errorCode);
		delete panorama;
	* @endcode
	*
	*/
	static const char* GetErrorString(const int iErrorCode);

	/**
	* Returns the version info of the SDK.
	*
	* @return The version info string.
	*
	* @par Code Snippet:
	* @code
		const char* versionInfo = CPanoramaStitcher::GetVersion();
	* @endcode
	*

	*/
	static const char* GetVersion();

	/**
	* @}
	*/


	/**
	* @name Initialization Functions
	* @{
	*/

	/**
	* Reads product key and activates the SDK.
	*
	* @param [in] pLicense The product keys.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		delete panorama;
	* @endcode
	*/
	int InitLicense(const char* pLicense);

	/**
	* Initializes the license and connections to the specified server for online verification.
	*
	* @param [in] pLicenseServer The URL of the license server.
	* @param [in] pLicenseKey The license key.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*/
	int InitLicenseFromServer(const char* pLicenseServer, const char* pLicenseKey);

	/**
	* Initializes the license from the license content on the client-side for offline verification.
	*
	* @param [in] pLicenseKey The license key.
	* @param [in] pLicenseContent An encrypted string representing the license content (quota, expiration date, barcode type, etc.) obtained from the method OutputLicenseToStringPtr().
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*/
	int InitLicenseFromLicenseContent(const char* pLicenseKey, const char* pLicenseContent);


	/**
	* Outputs the license content as an encrypted string from the license server to be used for offline license verification.
	*
	* @param [in, out] content The output string which stores the content of license.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	* @par Remarks:
	*	    InitLicenseFromServer() has to be successfully called before calling this method.
	*/
	int OutputLicenseToStringPtr(char** content);

	/**
	*Frees memory allocated for the license string.
	*
	* @param [in] content The output string which stores the content of license.
	*
	* @par Remarks:
	*		OutputLicenseToStringPtr() has to be successfully called before calling this method.
	*/
	void FreeLicenseString(char** content);

	/**
	* @}
	*/

	/**
	* @name Stitching Functions
	* @{
	*/

	/**
	* Starts threads to manage images reading from file, this function should be used with AppendNewFrameByFile Function.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_ALREADY_STARTED;
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByFile();
		panorama->AppendNewFrameByFile("C:\\Users\\*****\\1.jpg");
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	*/
	int StartPanoramaStitchingByFile();
	
	/**
	* Starts threads to manage images reading from buffer, this function should be used with AppendNewFrameByBuffer Function.
	*
	* @param [in] iWidth The width of the frame image in pixels.
	* @param [in] iHeight The height of the frame image in pixels.
	* @param [in] iStride The stride (or scan width) of the frame image.
	* @param [in] format The image pixel format used in the image byte array.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_ALREADY_STARTED;
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	*/
	int StartPanoramaStitchingByBuffer(int iWidth, int iHeight, int iStride, DPS_ImagePixelFormat format);

	/**
	* Appends a new frame from a file to the inner frame queue.
	*
	* @param [in] pFileName A string defining the file name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_NOT_STARTED;
	* 		  DPSERR_PANORAMA_STARTED_BY_BUFFER;
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByFile();
		panorama->AppendNewFrameByFile("C:\\Users\\*****\\1.jpg");
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	* @par Remarks:
	*	    StartPanoramaStitchingByFile() has to be successfully called before calling this method.
	*/
	int AppendNewFrameByFile(const char* pFileName);

	/**
	* Appends a new frame image buffer from a file to the inner frame queue.
	*
	* @param [in] pBuffer The array of bytes which contain the image data.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_PANORAMA_NOT_STARTED;
	* 		  DPSERR_PANORAMA_STARTED_BY_FILE;
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	* @par Remarks:
	*	    StartPanoramaStitchingByBuffer() has to be successfully called before calling this method.
	*/
	int AppendNewFrameByBuffer(const unsigned char* pBuffer);

	/**
	* Waits for finishing stitching all frames in the inner frame queue.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->WaitForFinishStitching();
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	*/
	void WaitForFinishStitching();

	/**
	* Stops stitching immediately, avoid stitching the remaining frames in the inner frame queue.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->StopPanoramaStitching();
		delete panorama;
	* @endcode
	*/
	void StopPanoramaStitching();

	/**
	* @}
	*/

	/**
	* @name Basic Setting Functions
	* @{
	*/

	/**
	* Gets current settings and saves them into a struct.
	* @param [in,out] pSettings The struct of template settings.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
	CPanoramaStitcher* panorama = new CPanoramaStitcher();
	panorama->InitLicense("t0260NwAAAHV***************");
	DPS_RuntimeSettings* pSettings = new DPS_RuntimeSettings()
	panorama->GetRuntimeSettings(pSettings);
	delete pSettings;
	delete panorama;
	* @endcode
	*/
	int GetRuntimeSettings(DPS_RuntimeSettings* pSettings);

	/**
	* Updates runtime settings with a given struct.
	*
	* @param [in] pSettings The struct of template settings.
	* @param [in,out] error The buffer is allocated by caller and the recommended length
	* 				   is 256.The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	*		  GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
	CPanoramaStitcher* panorama = new CPanoramaStitcher();
	panorama->InitLicense("t0260NwAAAHV***************");
	DPS_RuntimeSettings* pSettings = new DPS_RuntimeSettings()
	panorama->GetRuntimeSettings(pSettings);
	pSettings->stitchingAccuracyLevel = 0;
	char error[256];
	panorama->UpdateRuntimeSettings(pSettings, error, 256)
	delete pSettings;
	delete panorama;
	* @endcode
	*/
	int UpdateRuntimeSettings(DPS_RuntimeSettings* pSettings, char error[], int errorMsgBufferLen);

	/**
	* @}
	*/


	/**
	* @name Advanced Setting Functions
	* @{
	*/

	/**
	* Initializes Panorama settings with the parameters obtained from a JSON string.
	*
	* @param [in] pJsonSetting A JSON string that represents the content of the settings.
	* @param [in,out] error The buffer is allocated by caller and the recommending
	* 				  length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		char error[256];
		panorama->InitRuntimeSettingsWithString("{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		delete panorama;
	* @endcode
	*/

	int InitRuntimeSettingsWithString(const char* pJsonSetting, char error[], int errorMsgBufferLen);

	/**
	* Outputs runtime settings to a string.
	*
	* @param [in,out] content The output string which stores the contents of current settings.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		char error[256];
		panorama->InitRuntimeSettingsWithString("{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		char* pContent = NULL;
		panorama->OutputSettingsToStringPtr(&pContent);
		panorama->FreeSettingsString(&pContent);
		delete panorama;
	* @endcode
	* @par Remarks:
	*	Changing the parameter value in the output string and calling InitRuntimeSettingsWithString is also one of ways to init runtime settings.
	*
	*/
	int OutputSettingsToStringPtr(char** content);

	/**
	* Frees memory allocated for runtime settings string.
	*
	* @param [in] content The runtime settings string.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		char error[256];
		panorama->InitRuntimeSettingsWithString("{\"PreviewImgScaleRatio\": 0.25, \"ResultImgScaleRatio\":1}", error, 256);
		char* pContent = NULL;
		panorama->OutputSettingsToStringPtr(&pContent);
		panorama->FreeSettingsString(&pContent);
		delete panorama;
	* @endcode
	*
	*/
	void FreeSettingsString(char** content);


	/**
	* @}
	*/

	/**
	* @name Result Functions
	* @{
	*/

	/**
	* Gets the image and barcodes results.
	*
	* @param [in,out] pResult The output panorama result array.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  GetErrorString() to get detailed error message.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->StopPanoramaStitching();
		PanoramaResultArray* pResult = new PanoramaResultArray();
		panorama->GetFinalResults(&pResult);
		CPanoramaStitcher::FreePanoramaResults(&pResult);
		delete panorama;
	* @endcode
	* @par Remarks:
	*	    StopPanoramaStitching() has to be successfully called before calling this method.
	*/
	int GetFinalResults(PanoramaResultArray** pResult);

	/**
	* Gets running state of Panorama program.
	*
	* @param [in,out] pRunningState The struct of running state.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DPS_GetErrorString() to get detailed error message.Possible returns are:
	* 		  DPS_OK;
	* 		  DPSERR_INPUT_NULL_POINTER;
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		RunningState* pRunningState = new RunningState();
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->GetRunningState(pRunningState);
		panorama->StopPanoramaStitching();
		delete pRunningState;
		delete panorama;
	* @endcode
	*/
	int GetRunningState(RunningState* pRunningState);

	/**
	* Frees memory allocated for stitched image and panorama result.
	*
	* @param [in] pPresults The struct of Panorama result array.
	*
	* @par Code Snippet:
	* @code
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->InitLicense("t0260NwAAAHV***************");
		int ret = panorama->StartPanoramaStitchingByBuffer(1080, 1920, 3240, DPS_IPF_RGB_888);
		panorama->AppendNewFrameByBuffer(pBuffer);
		panorama->StopPanoramaStitching();
		PanoramaResultArray* pResult = new PanoramaResultArray();
		panorama->GetFinalResults(&pResult);
		CPanoramaStitcher::FreePanoramaResults(&pResult);
		delete panorama;
	* @endcode
	*/
	static void FreePanoramaResults(PanoramaResultArray** pPresults);
	
	/**
	* @}
	*/

	/**
	* @name Callback Functions
	* @{
	*/

	/**
	* Sets callback function to process panorama result, including stitched image and barcodes.
	*
	* @param [in] cbFunction Callback function.
	* @param [in] pUser Customized arguments passed to your function.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message. Possible returns are:
	* 		   DPS_OK;
	* 		   DPSERR_RESULT_CALLBACK_EXISTS;
	*
	* @par Code Snippet:
	* @code
	void ResultFunction(PanoramaResultArray** pResult, void * pUser)
	{
		//TODO add your code for using panorama result
	}
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->SetResultCallback(ResultFunction, NULL);
		delete panorama;
	* @endcode
	*/
	int SetResultCallback(CB_PanoramaResult cbFunction, void * pUser);

	/**
	* Sets callback function to process errors generated during image stitching.
	*
	* @param [in] cbFunction Callback function.
	* @param [in] pUser Customized arguments passed to your function.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message. Possible returns are:
	* 		   DPS_OK;
	* 		   DPSERR_ERROR_CALLBACK_EXISTS;
	*
	* @par Code Snippet:
	* @code
	void ErrorFunction(int errorCode, void * pUser)
	{
		//TODO add your code for using error code
	}
		CPanoramaStitcher* panorama = new CPanoramaStitcher();
		panorama->SetErrorCodeCallback(ErrorFunction, NULL);
		delete panorama;
	* @endcode
	*/
	int SetErrorCodeCallback(CB_PanoramaErrorCode cbFunction, void* pUser);

	/**
	* @}
	*/
};

/**
* @}defgroup CPanoramaStitcherClass
* @}defgroup CandCPlus
*
*/
#endif // endif of __cplusplus.

#pragma endregion

#endif
