
#ifndef AVPROGRAM_COLOR_MORPH_H
#define AVPROGRAM_COLOR_MORPH_H

#include "AVL.h"
#include "STD.h"
#include "System/GlobalParameterContainer.h"
#include <atomic>

struct __ConvertLabToMonoState
{
	avl::Image image1;
	avl::Image image2;
	avs::AvsFilters_ImagePointTransformsState powerImageState1;
	avl::Image image3;
};

struct __CropSample_LeftState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	avl::Path path1;
	avl::Path path2;
	avl::Image image2;
};

struct __CropSample_RightState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	avl::Path path1;
	avl::Path path2;
	avl::Image image2;
};

struct _MeasureGlobalScaleState
{
	atl::Array< atl::Conditional< avl::Point2D > > point2DArray1;
	atl::Array< atl::Conditional< avl::Point2D > > point2DArray2;
	avl::Image image1;
	atl::Conditional< avl::EdgeModel2 > edgeModel21;
	avl::Region region1;
	atl::Array< avl::Point2D > point2DArray3;
	atl::Array< avl::Point2D > point2DArray4;
	atl::Array< avl::Point2D > point2DArray5;
	atl::Array< avl::Point2D > point2DArray6;
	atl::Conditional< atl::Array< avl::Point2D > > point2DArray7;
};

struct _Shear_calculateState
{
	avl::Path path1;
	avl::Path path2;
	avl::Path path3;
	avl::Path path4;
};

struct _ApplyGlobalScaleState
{
	avl::Image image1;
	avl::Image image2;
	avl::Image image3;
};

struct __FindCorrelationDeltaState
{
	atl::Conditional< avl::EdgeModel2 > edgeModel21;
	atl::Array< avl::Point2D > point2DArray1;
	atl::Conditional< avl::EdgeModel2 > edgeModel22;
};

struct _MeasureLocalDisplState
{
	avl::Image image1;
	avl::Image image2;
	__FindCorrelationDeltaState ___FindCorrelationDeltaState1;
	atl::Conditional< atl::Array< avl::Path > > pathArray1;
	atl::Conditional< atl::Array< avl::Path > > pathArray2;
	atl::Conditional< atl::Array< avl::Path > > pathArray3;
};

struct __GenerateDeltaMapState
{
	atl::Array< avl::Point2D > point2DArray1;
	atl::Array< avl::Pixel > pixelArray1;
	avl::Image image1;
	atl::Array< avl::Location > locationArray1;
	avl::Region region1;
	avl::Image image2;
	avl::Image image3;
	avl::Image image4;
	avl::Region region2;
	avl::Region region3;
	avl::Image image5;
	avl::Image image6;
};

struct __AvgDisplMapState
{
	avl::Image image1;
};

struct _CorrectDisplMapState
{
	__GenerateDeltaMapState ___GenerateDeltaMapState1;
	avl::Image image1;
	atl::Conditional< avl::Image > image2;
	atl::Conditional< avl::Image > image3;
	__AvgDisplMapState ___AvgDisplMapState1;
	atl::Conditional< avl::Image > image4;
};

struct _ApplyDisplMapState
{
	avl::Image image1;
};

struct _FindFeaturesState
{
	avl::Image image1;
	atl::Array< avl::Point2D > point2DArray1;
	avl::Image image2;
	atl::Array< atl::Conditional< avl::Point2D > > point2DArray2;
	avl::Region region1;
	atl::Array< avl::Region > regionArray1;
	atl::Array< int > integerArray1;
	atl::Array< float > realArray1;
	atl::Conditional< avl::Region > region2;
	atl::Conditional< avl::Region > region3;
	atl::Conditional< avl::Region > region4;
	atl::Conditional< avl::Region > region5;
	atl::Conditional< avl::Region > region6;
	atl::Conditional< avl::Region > region7;
	atl::Conditional< avl::Region > region8;
	atl::Conditional< avl::Region > region9;
};

struct _UpdateOneSideState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	__ConvertLabToMonoState ___ConvertLabToMonoState2;
	avl::Image image2;
	_MeasureGlobalScaleState __MeasureGlobalScaleState1;
	_Shear_calculateState __Shear_calculateState1;
	_ApplyGlobalScaleState __ApplyGlobalScaleState1;
	avl::Image image3;
	__ConvertLabToMonoState ___ConvertLabToMonoState3;
	avl::Image image4;
	_MeasureLocalDisplState __MeasureLocalDisplState1;
	atl::Array< avl::Point2D > point2DArray1;
	atl::Array< atl::Conditional< avl::Vector2D > > vector2DArray1;
	_CorrectDisplMapState __CorrectDisplMapState1;
	_ApplyDisplMapState __ApplyDisplMapState1;
	avl::Image image5;
	atl::Array< float > realArrayState1;
	_FindFeaturesState __FindFeaturesState1;
};

struct _PrepareLRSearchTilesState
{
	atl::Array< avl::Point2D > point2DArray1;
	atl::Array< avl::Image > imageArray1;
	atl::Array< avl::Point2D > point2DArray2;
	atl::Array< avl::Image > imageArray2;
};

struct _1_UpdateState
{
	__CropSample_LeftState ___CropSample_LeftState1;
	atl::Conditional< avl::Image > image1;
	__CropSample_RightState ___CropSample_RightState1;
	atl::Conditional< avl::Image > image2;
	atl::Conditional< avl::Image > image3;
	atl::Conditional< avl::Image > image4;
	atl::Conditional< atl::Array< avl::Point2D > > point2DArray1;
	_UpdateOneSideState __UpdateOneSideState1;
	atl::Conditional< avl::Image > image5;
	_UpdateOneSideState __UpdateOneSideState2;
	avl::Image image6;
	atl::Array< avl::Point2D > point2DArray2;
	_PrepareLRSearchTilesState __PrepareLRSearchTilesState1;
	atl::Conditional< avl::Image > image7;
	avl::Image image8;
};

struct _X_CropBleedsState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	atl::Conditional< avl::Image > image2;
};

struct _CropTemplState
{
	avl::Image image1;
	avl::Image image2;
	avl::Image image3;
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image4;
};

struct _PrepareLRTemplatesState
{
	avl::Path path1;
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	atl::Array< avl::Edge1D > edge1DArray1;
	atl::Array< avl::Gap1D > gap1DArray1;
	atl::Array< avl::Point2D > point2DArray1;
	__ConvertLabToMonoState ___ConvertLabToMonoState2;
	avl::Image image2;
	__ConvertLabToMonoState ___ConvertLabToMonoState3;
	avl::Image image3;
};

struct _0_InitState
{
	avl::GrayModel grayModel1;
	avl::GrayModel grayModel2;
	_CropTemplState __CropTemplState1;
	atl::Conditional< avl::Image > image1;
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image2;
	avl::Image image3;
	_PrepareLRTemplatesState __PrepareLRTemplatesState1;
	atl::Conditional< avl::Image > image4;
	atl::Conditional< avl::Image > image5;
	atl::Conditional< atl::Array< avl::Point2D > > point2DArray1;
	__ConvertLabToMonoState ___ConvertLabToMonoState2;
	avl::Image image6;
	_FindFeaturesState __FindFeaturesState1;
	__ConvertLabToMonoState ___ConvertLabToMonoState3;
	avl::Image image7;
	_FindFeaturesState __FindFeaturesState2;
	atl::Array< avl::Point2D > point2DArray2;
	_PrepareLRSearchTilesState __PrepareLRSearchTilesState1;
};

struct __CheckEntireSampl_LeftState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	avl::Profile profile1;
	avl::Profile profile2;
	avl::Profile profile3;
	atl::Array< avl::ProfileEdge > profileEdgeArray1;
	atl::Array< int > integerArray1;
	avl::Region region1;
	avl::Region region2;
	atl::Array< avl::Object2D > object2DArray1;
};

struct __CheckEntireSampl_RightState
{
	__ConvertLabToMonoState ___ConvertLabToMonoState1;
	avl::Image image1;
	avl::Profile profile1;
	avl::Profile profile2;
	avl::Profile profile3;
	atl::Array< avl::ProfileEdge > profileEdgeArray1;
	atl::Array< int > integerArray1;
	avl::Region region1;
	avl::Region region2;
	atl::Array< avl::Object2D > object2DArray1;
};

struct _1_GetEntireSamplesPairState
{
	__CheckEntireSampl_LeftState ___CheckEntireSampl_LeftState1;
	atl::Conditional< avl::Image > image1;
	__CheckEntireSampl_RightState ___CheckEntireSampl_RightState1;
	atl::Conditional< avl::Image > image2;
};

extern atl::Array< avl::Point2D > FeatLoc;
extern avs::GlobalParameterContainer<avl::Image> Templ;
extern avs::GlobalParameterContainer<avl::GrayModel> StripeModel;
extern avl::Point2D Prescaler;
extern int MarginUp;
extern int MarginDown;
extern avl::Image DisplMap;
extern atl::String X_GCdir;
extern atl::String X_OSdir;
extern std::atomic<avl::Point2D> TemplStripeLoc;
extern std::atomic<int> SearchSize;
extern std::atomic<int> RefSize;
extern std::atomic<int> ResultSize;
extern avs::GlobalParameterContainer<avl::Image> Templ_Left;
extern avs::GlobalParameterContainer<atl::Array< avl::Point2D >> FeatLoc_Left;
extern avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints;
extern avs::GlobalParameterContainer<avl::Image> Templ_Right;
extern avs::GlobalParameterContainer<atl::Array< avl::Point2D >> FeatLoc_Right;
extern std::atomic<avl::Point2D> TemplStripeLoc_Left;
extern std::atomic<avl::Point2D> TemplStripeLoc_Right;
extern avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints_Left;
extern avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints_Rigth;
extern avs::GlobalParameterContainer<atl::Array< avl::Image >> SearchTiles_Left;
extern avs::GlobalParameterContainer<atl::Array< avl::Image >> SearchTiles_Right;
extern avs::GlobalParameterContainer<avl::GrayModel> StripeModel_SingleCam;
extern std::atomic<int> ProcessIterator;
extern int MergedSamplGenerationInterval;
extern avs::GlobalParameterContainer<avl::Image> Sampl_Left;
extern avs::GlobalParameterContainer<avl::Image> Sampl_Right;
extern avl::Image MergedSample;
extern avs::GlobalParameterContainer<avl::Image> DisplMap_Left;
extern avs::GlobalParameterContainer<avl::Image> DisplMap_Right;
extern std::atomic<float> ShearLeft;
extern std::atomic<float> ShearRight;
extern std::atomic<bool> SamplLeftReady;
extern std::atomic<bool> SamplRightReady;

void __ConvertLabToMono( __ConvertLabToMonoState& state, const avl::Image& inImg, avl::Image& outMonoImg );
void __CropSample_Left( __CropSample_LeftState& state, const avl::Image& inSampl, const avl::GrayModel& inStripeModel, const avl::Point2D& inTemplStripeLoc, const avl::Image& inTempl_left, atl::Conditional< avl::Image >& outSampl );
void __CropSample_Right( __CropSample_RightState& state, const avl::Image& inSampl, const avl::GrayModel& inStripeModel, const avl::Point2D& inTemplStripeLoc, const avl::Image& inTempl, atl::Conditional< avl::Image >& outSampl );
void _MeasureGlobalScale( _MeasureGlobalScaleState& state, const avl::Image& inRef, const avl::Image& inSampl, const atl::Array< avl::Point2D >& inFeatureLoc, avl::Point2D& outScale, float& outShear, float& outTranslationX );
void _Shear_calculate( _Shear_calculateState& state, const avl::Image& inSampl, const avl::Point2D& inTemplStripeLoc, float inShear, atl::Conditional< float >& outShearUpdate, atl::Conditional< float >& outShearAbsolute );
void _ApplyGlobalScale( _ApplyGlobalScaleState& state, const avl::Point2D& inScale, float inShear, float inTranslationX, const avl::Image& inTempl, avl::Image& outTempl );
void __DefineResultsPoints( int inResultSize, int inSearchSize, int inImageRefWidth, int inImageRefHeight, atl::Array< avl::Point2D >& outResultsPoints );
void __CropTiles( const avl::Point2D& inPoint, int inRefSize, int inSearchSize, const avl::Image& inImage, const avl::Image& inRefImage, avl::InterpolationMethod::Type inInterpolation, avl::Image& outRefTiles, avl::Image& outSearchTiles );
void __FindCorrelationDelta( __FindCorrelationDeltaState& state, int inSearchSize, int inRefSize, const avl::Image& inSearchTile, const avl::Image& inRefTile, atl::Conditional< avl::Vector2D >& outDelta, atl::Conditional< atl::Array< avl::Path > >& outEdges, atl::Conditional< avl::Rectangle2D >& outObjectMatch, atl::Conditional< atl::Array< avl::Path > >& outObjMatchEdges, atl::Conditional< atl::Array< avl::Path > >& outEnhObjMatchEdges );
void _MeasureLocalDispl( _MeasureLocalDisplState& state, const avl::Image& inRef, const avl::Image& inSampl, atl::Array< avl::Point2D >& outDisplLoc, atl::Array< atl::Conditional< avl::Vector2D > >& outDispl );
void __GenerateDeltaMap( __GenerateDeltaMapState& state, const atl::Array< atl::Conditional< avl::Vector2D > >& inDelta, const atl::Array< avl::Point2D >& inResultsPoints, int inResultSize, int inRefWidth, int inRefHeight, avl::Image& outDeltaMap );
void __AvgDisplMap( __AvgDisplMapState& state, int inDisplMapWidth, int inDisplMapHeight, int inDeltaMapWidth, int inDeltaMapHeight, const avl::Image& inImage, const avl::Image& inImage2, avl::Image& outImage );
void _CorrectDisplMap( _CorrectDisplMapState& state, const atl::Array< atl::Conditional< avl::Vector2D > >& inDispl, const atl::Array< avl::Point2D >& inDisplLoc, const avl::Image& inDisplMap, avl::Image& outDisplMap );
void _ApplyDisplMap( _ApplyDisplMapState& state, const avl::Image& inDisplMap, const avl::Image& inTempl, avl::Image& outTempl );
void _FindFeatures( _FindFeaturesState& state, const avl::Image& inTempl, atl::Array< avl::Point2D >& outFeatureLoc );
void _UpdateOneSide( _UpdateOneSideState& state, const avl::Image& inRef, const avl::Image& inSampl, const atl::Array< avl::Point2D >& inFeatureLoc, const avl::Image& inDisplMap, const avl::Point2D& inTemplStripeLoc, float inShear, avl::Image& outDisplMap, avl::Image& outTempl, atl::Conditional< float >& outShear, atl::Array< avl::Point2D >& outFeatureLoc );
void __CropSearchTiles( const avl::Point2D& inPoint, int inSearchSize, const avl::Image& inRefImage, avl::InterpolationMethod::Type inInterpolation, avl::Image& outSearchTiles );
void _PrepareLRSearchTiles( _PrepareLRSearchTilesState& state );
void _1_Update( _1_UpdateState& state, const avl::Image& inTempl, const avl::Image& inFrameLeft, const avl::Image& inFrameRight, avl::Image& outTempl );
void _X_CropBleeds( _X_CropBleedsState& state, const avl::Image& inTempl, avl::Image& outTempl );
void _PrepareStripeModel( avl::GrayModel& outStripeModel, avl::GrayModel& outStripeModel_single_camera );
void _CropTempl( _CropTemplState& state, const avl::Image& inTemplLab, const avl::Point2D& inPrescaler, int inMarginUp, int inMarginDown, const avl::GrayModel& inStripeModel, atl::Conditional< avl::Point2D >& outTemplStripeLoc, atl::Conditional< avl::Image >& outTemplLab );
void _PrepareLRTemplates( _PrepareLRTemplatesState& state, atl::Conditional< avl::Image >& outTempl_Left, atl::Conditional< avl::Image >& outTempl_Right );
void _0_Init( _0_InitState& state, const avl::Image& inTempl );
void Main( void );
void __CheckEntireSampl_Left( __CheckEntireSampl_LeftState& state, const avl::Image& inFrameLeft, bool& outHasEntireSampl, atl::Conditional< avl::Image >& outSampl );
void __CheckEntireSampl_Right( __CheckEntireSampl_RightState& state, const avl::Image& inFrameRight, bool& outHasEntireSampl, atl::Conditional< avl::Image >& outSampl );
void _1_GetEntireSamplesPair( _1_GetEntireSamplesPairState& state, const avl::Image& inFrameLeft, const avl::Image& inFrameRight, bool& outPairReady, atl::Conditional< avl::Image >& outSamplLeft, atl::Conditional< avl::Image >& outSamplRight );
void Init( void );

#endif // AVPROGRAM_COLOR_MORPH_H
