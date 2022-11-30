#include "ATL/Error.h"
#include "ATL/Dummy.h"
#include "ATL/Optional.h"
#include "ExpressionsRuntime/ExpressionsRuntime.h"
#include "Serialization/Serialization.h"

#include "color_morph.h"

atl::Array< avl::Point2D > FeatLoc;
avs::GlobalParameterContainer<avl::Image> Templ;
avs::GlobalParameterContainer<avl::GrayModel> StripeModel;
avl::Point2D Prescaler;
int MarginUp;
int MarginDown;
avl::Image DisplMap;
atl::String X_GCdir;
atl::String X_OSdir;
std::atomic<avl::Point2D> TemplStripeLoc;
std::atomic<int> SearchSize;
std::atomic<int> RefSize;
std::atomic<int> ResultSize;
avs::GlobalParameterContainer<avl::Image> Templ_Left;
avs::GlobalParameterContainer<atl::Array< avl::Point2D >> FeatLoc_Left;
avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints;
avs::GlobalParameterContainer<avl::Image> Templ_Right;
avs::GlobalParameterContainer<atl::Array< avl::Point2D >> FeatLoc_Right;
std::atomic<avl::Point2D> TemplStripeLoc_Left;
std::atomic<avl::Point2D> TemplStripeLoc_Right;
avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints_Left;
avs::GlobalParameterContainer<atl::Array< avl::Point2D >> ResultPoints_Rigth;
avs::GlobalParameterContainer<atl::Array< avl::Image >> SearchTiles_Left;
avs::GlobalParameterContainer<atl::Array< avl::Image >> SearchTiles_Right;
avs::GlobalParameterContainer<avl::GrayModel> StripeModel_SingleCam;
std::atomic<int> ProcessIterator;
int MergedSamplGenerationInterval;
avs::GlobalParameterContainer<avl::Image> Sampl_Left;
avs::GlobalParameterContainer<avl::Image> Sampl_Right;
avl::Image MergedSample;
avs::GlobalParameterContainer<avl::Image> DisplMap_Left;
avs::GlobalParameterContainer<avl::Image> DisplMap_Right;
std::atomic<float> ShearLeft;
std::atomic<float> ShearRight;
std::atomic<bool> SamplLeftReady;
std::atomic<bool> SamplRightReady;
static avl::Path g_constData1;
static avl::Path g_constData2;
static avl::Image g_constData3;
static atl::String g_constData4;
static atl::String g_constData5;
static atl::String g_constData6;


void InitMainConsts( void )
{
	Prescaler = avl::Point2D(0.1775f, 0.1775f);
	
	MarginUp = 25;
	
	MarginDown = 25;
	
	X_GCdir = u"C:\\Users\\Gabriel Ceballos\\Nextcloud\\Industry\\2008_Walstead(D)\\AVS\\analiza kafelkowa\\zdjęcia";
	
	X_OSdir = u"C:\\Users\\Olga Skiermut\\Desktop\\walstead dataset\\mono\\09.02 OBI\\rightCameraPhotos";
	
	TemplStripeLoc = avl::Point2D(0.0f, 0.0f);
	
	SearchSize = 250;
	
	RefSize = 180;
	
	ResultSize = 100;
	
	TemplStripeLoc_Left = avl::Point2D(0.0f, 0.0f);
	
	TemplStripeLoc_Right = avl::Point2D(0.0f, 0.0f);
	
	ProcessIterator = 0;
	
	MergedSamplGenerationInterval = 500;
	
	ShearLeft = 0.0f;
	
	ShearRight = 0.0f;
	
	SamplLeftReady = false;
	
	SamplRightReady = false;
	
	avs::ReadDataFromFile( u"color_morph.d69ebdbe.avdata", u"Path", g_constData1 );
	
	avs::ReadDataFromFile( u"color_morph.bc811825.avdata", u"Path", g_constData2 );
	
	avs::ReadDataFromFile( u"color_morph.8132876a.avdata", u"Image", g_constData3 );
	
	g_constData4 = u"C:\\Users\\Gabriel Ceballos\\Desktop\\Walstead(D)\\Dataset\\kolor\\480586!480586 SIG-5_X01 F\\T\\template.tif";
	
	g_constData5 = u"C:\\Users\\Gabriel Ceballos\\Desktop\\Walstead(D)\\Dataset\\kolor\\480586!480586 SIG-5_X01 F\\L";
	
	g_constData6 = u"C:\\Users\\Gabriel Ceballos\\Desktop\\Walstead(D)\\Dataset\\kolor\\480586!480586 SIG-5_X01 F\\R";
}

void __ConvertLabToMono( __ConvertLabToMonoState& state, const avl::Image& inImg, avl::Image& outMonoImg )
{
	avl::SelectChannel( inImg, atl::NIL, 0, state.image1 );
	avl::ConvertPixelType( state.image1, atl::NIL, avl::PlainType::Real, 0, state.image2 );
	avl::DivideImage( state.image2, atl::NIL, 2.56f, state.image2 );
	avs::AvsFilter_PowerImage( state.powerImageState1, state.image2, atl::NIL, 2.0f, state.image3 );
	avl::RescalePixels( state.image3, atl::NIL, 0.026f, 0.0f, state.image3 );
	avl::RescalePixels( state.image2, atl::NIL, -0.299f, 6.639f, state.image2 );
	avl::AddImages( state.image3, state.image2, atl::NIL, 1.0f, state.image3 );
	avl::ConvertPixelType( state.image3, atl::NIL, avl::PlainType::UInt8, 0, outMonoImg );
}

void __CropSample_Left( __CropSample_LeftState& state, const avl::Image& inSampl, const avl::GrayModel& inStripeModel, const avl::Point2D& inTemplStripeLoc, const avl::Image& inTempl_left, atl::Conditional< avl::Image >& outSampl )
{
	int integer1;
	float real1;
	float real2;
	int integer2;
	int integer3;
	avl::Box box1;
	avl::ShapeRegion shapeRegion1;
	atl::Conditional< avl::Object2D > object2D1;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inSampl, state.image1 );
	integer1 = inSampl.Height();
	real1 = inTemplStripeLoc.X();
	real2 = inTemplStripeLoc.Y();
	integer2 = inSampl.Width();
	integer3 = inTempl_left.Height();
	box1 = avl::Box(static_cast<int>(real1), static_cast<int>(real2) - 100, 2048, integer1 - integer3 + 100);
	avl::BoxToShapeRegion( box1, shapeRegion1 );
	avl::LocateSingleObject_NCC( state.image1, shapeRegion1, atl::NIL, inStripeModel, 1, atl::NIL, false, 0.5f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		float real3;
		float real4;
		float real5;
		atl::Conditional< avl::Edge1D > edge1D1;
		
		real3 = object2D1.Get().Match().Origin().X();
		real4 = object2D1.Get().Match().Origin().Y();
		real5 = object2D1.Get().Match().Height();
		
		// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
		// 
		// do przemyślenia
		state.path1 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(0.0f, static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) + 60)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0))));
		avl::ScanSingleEdge_Direct( state.image1, state.path1, atl::NIL, 25, avl::SamplingParams(avl::InterpolationMethod::NearestNeighbour, 2.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 1.0f, 5.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Best, atl::NIL, edge1D1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
		
		if (edge1D1 != atl::NIL)
		{
			float real6;
			atl::Conditional< avl::Edge1D > edge1D2;
			
			real6 = object2D1.Get().Match().Width();
			
			// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
			// 
			// do przemyślenia
			state.path2 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) + static_cast<int>(real6) + 112)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) + static_cast<int>(real6) + 124)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0))));
			avl::ScanSingleEdge_Direct( state.image1, state.path2, atl::NIL, 15, avl::SamplingParams(avl::InterpolationMethod::NearestNeighbour, 1.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 2.0f, 5.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Best, atl::NIL, edge1D2, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
			
			if (edge1D2 != atl::NIL)
			{
				int integer4;
				float real7;
				float real8;
				float real9;
				avl::Box box2;
				
				outSampl.AssignNonNil();
				
				integer4 = inTempl_left.Width();
				real7 = edge1D1.Get().Point().X();
				real8 = edge1D2.Get().Point().X();
				real9 = static_cast<float>(static_cast<double>(real6) / (static_cast<double>(real8) - static_cast<double>(real7)));
				box2 = avl::Box(static_cast<int>(real7), static_cast<int>(real4) - static_cast<int>(real2), static_cast<int>(real8) - static_cast<int>(real7), integer3);
				avl::CropImage( inSampl, box2, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), state.image2 );
				avl::ResizeImage( state.image2, integer4, integer3, avl::ResizeMethod::Bilinear, outSampl.Get() );
			}
			else
			{
				outSampl = atl::NIL;
			}
		}
		else
		{
			outSampl = atl::NIL;
		}
	}
	else
	{
		outSampl = atl::NIL;
	}
}

void __CropSample_Right( __CropSample_RightState& state, const avl::Image& inSampl, const avl::GrayModel& inStripeModel, const avl::Point2D& inTemplStripeLoc, const avl::Image& inTempl, atl::Conditional< avl::Image >& outSampl )
{
	int integer1;
	float real1;
	float real2;
	int integer2;
	int integer3;
	avl::Box box1;
	avl::ShapeRegion shapeRegion1;
	atl::Conditional< avl::Object2D > object2D1;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inSampl, state.image1 );
	integer1 = inSampl.Height();
	real1 = inTemplStripeLoc.X();
	real2 = inTemplStripeLoc.Y();
	integer2 = inSampl.Width();
	integer3 = inTempl.Height();
	box1 = avl::Box(static_cast<int>(real1) + 100, static_cast<int>(real2) - 100, 2048, integer1 - integer3 + 100);
	avl::BoxToShapeRegion( box1, shapeRegion1 );
	avl::LocateSingleObject_NCC( state.image1, shapeRegion1, atl::NIL, inStripeModel, 1, atl::NIL, false, 0.2f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		float real3;
		float real4;
		float real5;
		float real6;
		atl::Conditional< avl::Edge1D > edge1D1;
		
		real3 = object2D1.Get().Match().Origin().X();
		real4 = object2D1.Get().Match().Origin().Y();
		real5 = object2D1.Get().Match().Width();
		real6 = object2D1.Get().Match().Height();
		
		// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
		// 
		// do przemyślenia
		state.path1 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) - 268)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real6)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) - 255)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real6)) / 2.0))));
		avl::ScanSingleEdge_Direct( state.image1, state.path1, atl::NIL, 15, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 2.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 1.0f, 5.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Last, atl::NIL, edge1D1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
		
		if (edge1D1 != atl::NIL)
		{
			atl::Conditional< avl::Edge1D > edge1D2;
			
			// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
			// 
			// do przemyślenia
			state.path2 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(integer2)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real6)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3)) + static_cast<double>(real5) + 60.0), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real6)) / 2.0))));
			avl::ScanSingleEdge_Direct( state.image1, state.path2, atl::NIL, 15, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 2.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 1.0f, 5.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Best, atl::NIL, edge1D2, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
			
			if (edge1D2 != atl::NIL)
			{
				int integer4;
				float real7;
				float real8;
				float real9;
				avl::Box box2;
				
				outSampl.AssignNonNil();
				
				integer4 = inTempl.Width();
				real7 = edge1D1.Get().Point().X();
				real8 = edge1D2.Get().Point().X();
				real9 = static_cast<float>(static_cast<double>(real5) / (static_cast<double>(real8) - static_cast<double>(real7)));
				box2 = avl::Box(static_cast<int>(real7), static_cast<int>(real4) - static_cast<int>(real2), static_cast<int>(real8) - static_cast<int>(real7), integer3);
				avl::CropImage( inSampl, box2, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), state.image2 );
				avl::ResizeImage( state.image2, integer4, integer3, avl::ResizeMethod::Bilinear, outSampl.Get() );
			}
			else
			{
				outSampl = atl::NIL;
			}
		}
		else
		{
			outSampl = atl::NIL;
		}
	}
	else
	{
		outSampl = atl::NIL;
	}
}

void _MeasureGlobalScale( _MeasureGlobalScaleState& state, const avl::Image& inRef, const avl::Image& inSampl, const atl::Array< avl::Point2D >& inFeatureLoc, avl::Point2D& outScale, float& outShear, float& outTranslationX )
{
	int integer1;
	int integer2;
	atl::Conditional< avl::CoordinateSystem2D > coordinateSystem2D1;
	atl::Conditional< float > real1;
	atl::Conditional< float > real2;
	atl::Conditional< float > real3;
	float real4;
	float real5;
	
	integer1 = inRef.Width();
	integer2 = inRef.Height();
	
	state.point2DArray1.Resize(inFeatureLoc.Size());
	state.point2DArray2.Resize(inFeatureLoc.Size());
	
	for( int i = 0; i < inFeatureLoc.Size(); ++i )
	{
		avl::Location location1;
		avl::Box box1;
		atl::Conditional< avl::Rectangle2D > rectangle2D1;
		
		avl::Point2DToLocation( inFeatureLoc[i], location1 );
		avl::CreateBox( location1, avl::Anchor2D::MiddleCenter, 150, 150, box1 );
		avl::CropImage( inSampl, box1, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), state.image1 );
		avl::CreateEdgeModel2( state.image1, atl::NIL, atl::NIL, 0, 2, 0.0f, 35.0f, 15.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, state.edgeModel21, atl::NIL, atl::NIL, atl::Dummy< atl::Conditional< atl::Array< avl::Image > > >().Get() );
		
		if (state.edgeModel21 != atl::NIL)
		{
			avl::ShapeRegion shapeRegion1;
			atl::Conditional< avl::Object2D > object2D1;
			
			avl::Circle2D circle2D1 = avl::Circle2D(inFeatureLoc[i], 50.0f);
			avl::CreateCircleRegion( circle2D1, atl::NIL, integer1, integer2, state.region1, atl::NIL );
			avl::RegionToShapeRegion( state.region1, shapeRegion1 );
			avl::LocateSingleObject_Edges2( inSampl, shapeRegion1, atl::NIL, state.edgeModel21.Get(), 2, atl::NIL, 10.0f, avl::EdgePolarityMode::MatchStrictly, avl::EdgeNoiseLevel::High, false, 0.4f, object2D1, atl::NIL, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
			
			if (object2D1 != atl::NIL)
			{
				rectangle2D1.AssignNonNil();
				state.point2DArray1[i].AssignNonNil();
				
				rectangle2D1.Get() = object2D1.Get().Match();
				avl::RectangleCenter( rectangle2D1.Get(), state.point2DArray1[i].Get() );
			}
			else
			{
				rectangle2D1 = atl::NIL;
				state.point2DArray1[i] = atl::NIL;
			}
		}
		else
		{
			rectangle2D1 = atl::NIL;
			state.point2DArray1[i] = atl::NIL;
		}
		
		state.point2DArray2[i] = rectangle2D1 == atl::NIL ? atl::Conditional< avl::Point2D >(atl::NIL) : atl::Conditional< avl::Point2D >(inFeatureLoc[i]);
	}
	
	avl::RemoveNils< avl::Point2D >( state.point2DArray2, state.point2DArray3, atl::NIL );
	avl::RemoveNils< avl::Point2D >( state.point2DArray1, state.point2DArray4, atl::NIL );
	avl::CropArraysToEqualSize< avl::Point2D >( state.point2DArray3, state.point2DArray4, state.point2DArray5, state.point2DArray6 );
	avl::AdjustPointArrays( state.point2DArray5, state.point2DArray6, true, false, 10, 0.75f, 10, state.point2DArray7, coordinateSystem2D1 );
	
	if (coordinateSystem2D1 != atl::NIL)
	{
		real1.AssignNonNil();
		real2.AssignNonNil();
		real3.AssignNonNil();
		
		real1.Get() = coordinateSystem2D1.Get().Origin().X();
		real2.Get() = coordinateSystem2D1.Get().Angle();
		real3.Get() = coordinateSystem2D1.Get().Scale();
	}
	else
	{
		real1 = atl::NIL;
		real2 = atl::NIL;
		real3 = atl::NIL;
	}
	
	avl::MergeDefault< float >( real1, 0.0f, outTranslationX );
	avl::MergeDefault< float >( real2, 0.0f, real4 );
	avl::MergeDefault< float >( real3, 1.0f, real5 );
	outScale = avl::Point2D(real5, real5);
	avl::Tangent( real4, outShear );
}

void _Shear_calculate( _Shear_calculateState& state, const avl::Image& inSampl, const avl::Point2D& inTemplStripeLoc, float inShear, atl::Conditional< float >& outShearUpdate, atl::Conditional< float >& outShearAbsolute )
{
	float real1;
	float real2;
	int integer1;
	int integer2;
	avl::Box box1;
	avl::ShapeRegion shapeRegion1;
	atl::Conditional< avl::Object2D > object2D1;
	
	real1 = inTemplStripeLoc.X();
	real2 = inTemplStripeLoc.Y();
	integer1 = inSampl.Width();
	integer2 = inSampl.Height();
	box1 = avl::Box(static_cast<int>(real1) - 200, static_cast<int>(real2) - 50, 3500, 140);
	avl::BoxToShapeRegion( box1, shapeRegion1 );
	avs::GlobalParameterRef<avl::GrayModel> StripeModel_SingleCamRef1(StripeModel_SingleCam);
	avl::LocateSingleObject_NCC( inSampl, shapeRegion1, atl::NIL, StripeModel_SingleCamRef1.Get(), 1, atl::NIL, false, 0.4f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		float real3;
		float real4;
		float real5;
		atl::Conditional< avl::Edge1D > edge1D1;
		
		real3 = object2D1.Get().Match().Origin().X();
		real4 = object2D1.Get().Match().Origin().Y();
		real5 = object2D1.Get().Match().Height();
		
		// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
		// 
		// do przemyślenia
		state.path1 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) - 50)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) + 60)), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0))));
		avl::ScanSingleEdge_Direct( inSampl, state.path1, atl::NIL, 10, avl::SamplingParams(avl::InterpolationMethod::NearestNeighbour, 2.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 1.0f, 20.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Best, atl::NIL, edge1D1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
		
		if (edge1D1 != atl::NIL)
		{
			float real6;
			float real7;
			atl::Conditional< avl::Stripe1D > stripe1D1;
			
			real6 = edge1D1.Get().Point().X();
			real7 = edge1D1.Get().Point().Y();
			
			// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
			// 
			// do przemyślenia
			state.path2 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real6) - 15)), static_cast<float>(static_cast<double>(static_cast<int>(real7) + static_cast<int>(real5)))), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real6) - 15)), static_cast<float>(static_cast<double>(static_cast<int>(real7) - static_cast<int>(real5))))));
			avl::ScanSingleStripe_Direct( inSampl, state.path2, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 1.0f, atl::NIL), avl::StripeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.6f, 5.0f, atl::NIL, avl::Polarity::Dark, 0.0f, atl::NIL), avl::Selection::Best, atl::NIL, stripe1D1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
			
			if (stripe1D1 != atl::NIL)
			{
				float real8;
				atl::Conditional< avl::Edge1D > edge1D2;
				
				real8 = object2D1.Get().Match().Width();
				
				// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
				// 
				// do przemyślenia
				state.path3 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) - 80 + static_cast<int>(real8))), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0)), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real3) + 80 + static_cast<int>(real8))), static_cast<float>(static_cast<double>(static_cast<int>(real4)) + static_cast<double>(static_cast<int>(real5)) / 2.0))));
				avl::ScanSingleEdge_Direct( inSampl, state.path3, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 1.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 1.0f, 5.0f, avl::EdgeTransition::DarkToBright), avl::Selection::Best, atl::NIL, edge1D2, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
				
				if (edge1D2 != atl::NIL)
				{
					float real9;
					float real10;
					atl::Conditional< avl::Stripe1D > stripe1D2;
					
					real9 = edge1D2.Get().Point().X();
					real10 = edge1D2.Get().Point().Y();
					
					// Formuła wymaga rozwinięcia - na razie uwzględnia istnienie tylko lewej części obrazu wstęgi - pytanie co z prawą? osobny wzorzec? można podać jakąś daną wejściową razem z klatką, bo wiemy z jakiej kamery pochodzi i dodać jakiś offset
					// 
					// do przemyślenia
					state.path4 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real9) - 15)), static_cast<float>(static_cast<double>(static_cast<int>(real10) + static_cast<int>(real5)))), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(real9) - 15)), static_cast<float>(static_cast<double>(static_cast<int>(real10) - static_cast<int>(real5))))));
					avl::ScanSingleStripe_Direct( inSampl, state.path4, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 1.0f, atl::NIL), avl::StripeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.6f, 5.0f, atl::NIL, avl::Polarity::Dark, 0.0f, atl::NIL), avl::Selection::Best, atl::NIL, stripe1D2, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
					
					if (stripe1D2 != atl::NIL)
					{
						float real11;
						float real12;
						float real13;
						float real14;
						
						outShearAbsolute.AssignNonNil();
						outShearUpdate.AssignNonNil();
						
						real11 = stripe1D1.Get().Center().Y();
						real12 = stripe1D1.Get().Center().X();
						real13 = stripe1D2.Get().Center().X();
						real14 = stripe1D2.Get().Center().Y();
						outShearAbsolute.Get() = static_cast<float>((static_cast<double>(real14) - static_cast<double>(real11)) / (static_cast<double>(real13) - static_cast<double>(real12)) - static_cast<double>(inShear));
						outShearUpdate.Get() = static_cast<float>((static_cast<double>(real14) - static_cast<double>(real11)) / (static_cast<double>(real13) - static_cast<double>(real12)));
					}
					else
					{
						outShearAbsolute = atl::NIL;
						outShearUpdate = atl::NIL;
					}
				}
				else
				{
					outShearAbsolute = atl::NIL;
					outShearUpdate = atl::NIL;
				}
			}
			else
			{
				outShearAbsolute = atl::NIL;
				outShearUpdate = atl::NIL;
			}
		}
		else
		{
			outShearAbsolute = atl::NIL;
			outShearUpdate = atl::NIL;
		}
	}
	else
	{
		outShearAbsolute = atl::NIL;
		outShearUpdate = atl::NIL;
	}
}

void _ApplyGlobalScale( _ApplyGlobalScaleState& state, const avl::Point2D& inScale, float inShear, float, const avl::Image& inTempl, avl::Image& outTempl )
{
	int integer1;
	int integer2;
	atl::Optional< int > integer3;
	atl::Optional< int > integer4;
	
	avl::TranslateImage( inTempl, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), 0, 0, false, state.image1 );
	avl::ShearImage( state.image1, inShear, avl::Axis::Y, avl::InterpolationMethod::Bilinear, state.image2 );
	integer1 = inTempl.Width();
	integer2 = inTempl.Height();
	integer3 = _avfml_st_opt< int >(static_cast<int>(static_cast<double>(inScale.X()) * static_cast<double>(integer1)));
	integer4 = _avfml_st_opt< int >(static_cast<int>(static_cast<double>(inScale.Y()) * static_cast<double>(integer2)));
	avl::ResizeImage( state.image2, integer3, integer4, avl::ResizeMethod::NearestNeighbour, state.image3 );
	avl::Box box1 = avl::Box(0, 0, integer1, integer2);
	avl::CropImage( state.image3, box1, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outTempl );
}

void __DefineResultsPoints( int inResultSize, int inSearchSize, int inImageRefWidth, int inImageRefHeight, atl::Array< avl::Point2D >& outResultsPoints )
{
	avl::Point2D point2D1;
	int integer1;
	int integer2;
	avl::Box box1;
	
	point2D1 = avl::Point2D(static_cast<float>(static_cast<double>(inResultSize) / 2.0), static_cast<float>(static_cast<double>(inResultSize) / 2.0));
	integer1 = static_cast<int>(static_cast<double>(inImageRefHeight) / static_cast<double>(inResultSize)) + 1;
	integer2 = static_cast<int>(static_cast<double>(inImageRefWidth) / static_cast<double>(inResultSize)) + 1;
	box1 = avl::Box(0, 0, inImageRefWidth, inImageRefHeight);
	avl::CreatePointGrid( point2D1, avl::Anchor2D::TopLeft, integer1, integer2, static_cast<float>(inResultSize), static_cast<float>(inResultSize), outResultsPoints );
	avl::TrimPointArray( outResultsPoints, box1, outResultsPoints );
}

void __CropTiles( const avl::Point2D& inPoint, int inRefSize, int inSearchSize, const avl::Image& inImage, const avl::Image& inRefImage, avl::InterpolationMethod::Type inInterpolation, avl::Image& outRefTiles, avl::Image& outSearchTiles )
{
	avl::Rectangle2D rectangle2D1;
	avl::Rectangle2D rectangle2D2;
	
	avl::CreateRectangle( inPoint, avl::Anchor2D::MiddleCenter, 0.0f, static_cast<float>(inRefSize), static_cast<float>(inRefSize), rectangle2D1 );
	avl::CreateRectangle( inPoint, avl::Anchor2D::MiddleCenter, 0.0f, static_cast<float>(inSearchSize), static_cast<float>(inSearchSize), rectangle2D2 );
	avl::CropImageToRectangle( inImage, rectangle2D1, atl::NIL, avl::CropScaleMode::InputScale, inInterpolation, 0.0f, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outRefTiles, atl::NIL, atl::NIL );
	avl::CropImageToRectangle( inRefImage, rectangle2D2, atl::NIL, avl::CropScaleMode::InputScale, inInterpolation, 0.0f, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outSearchTiles, atl::NIL, atl::NIL );
}

void __FindCorrelationDelta( __FindCorrelationDeltaState& state, int inSearchSize, int inRefSize, const avl::Image& inSearchTile, const avl::Image& inRefTile, atl::Conditional< avl::Vector2D >& outDelta, atl::Conditional< atl::Array< avl::Path > >& outEdges, atl::Conditional< avl::Rectangle2D >& outObjectMatch, atl::Conditional< atl::Array< avl::Path > >& outObjMatchEdges, atl::Conditional< atl::Array< avl::Path > >& outEnhObjMatchEdges )
{
	float real1;
	avl::Rectangle2D rectangle2D1;
	atl::Conditional< int > integer1;
	atl::Conditional< int > integer2;
	
	avl::DivideReals( static_cast<float>(inSearchSize), 2.0f, real1 );
	avl::Point2D point2D1 = avl::Point2D(real1, real1);
	avl::CreateRectangle( point2D1, avl::Anchor2D::MiddleCenter, 0.0f, static_cast<float>(inRefSize), static_cast<float>(inRefSize), atl::Dummy<avl::Rectangle2D>().Get() );
	avl::CreateRectangle( avl::Point2D(0.0f, 0.0f), avl::Anchor2D::TopLeft, 0.0f, static_cast<float>(inRefSize), static_cast<float>(inRefSize), rectangle2D1 );
	avl::CreateEdgeModel2( inRefTile, atl::NIL, rectangle2D1, 0, 2, 0.2f, 40.0f, 15.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, state.edgeModel21, atl::NIL, outEdges, atl::Dummy< atl::Conditional< atl::Array< avl::Image > > >().Get() );
	
	if (outEdges != atl::NIL)
	{
		atl::Conditional< avl::Box > box1;
		
		avl::PathArrayPoints( outEdges.Get(), state.point2DArray1 );
		avl::PointsBoundingBox_OrNil( state.point2DArray1, box1 );
		
		if (box1 != atl::NIL)
		{
			integer1.AssignNonNil();
			integer2.AssignNonNil();
			
			integer1.Get() = box1.Get().Width();
			integer2.Get() = box1.Get().Height();
		}
		else
		{
			integer1 = atl::NIL;
			integer2 = atl::NIL;
		}
	}
	else
	{
		integer1 = atl::NIL;
		integer2 = atl::NIL;
	}
	
	
	if (integer1 != atl::NIL && integer2 != atl::NIL)
	{
		state.edgeModel22 = integer1.Get() < 5 || integer2.Get() < 5 ? atl::Conditional< avl::EdgeModel2 >(atl::NIL) : state.edgeModel21;
	}
	else
	{
		state.edgeModel22 = atl::NIL;
	}
	
	if (state.edgeModel22 != atl::NIL)
	{
		avl::Rectangle2D rectangle2D2;
		avl::ShapeRegion shapeRegion1;
		atl::Conditional< avl::Object2D > object2D1;
		
		avl::Point2D point2D2 = avl::Point2D(real1, real1);
		avl::CreateRectangle( point2D2, avl::Anchor2D::MiddleCenter, 0.0f, 150.0f, 150.0f, rectangle2D2 );
		avl::Rectangle2DToShapeRegion( rectangle2D2, shapeRegion1 );
		avl::LocateSingleObject_Edges2( inSearchTile, shapeRegion1, atl::NIL, state.edgeModel22.Get(), 0, 2, 20.0f, avl::EdgePolarityMode::MatchStrictly, avl::EdgeNoiseLevel::High, false, 0.5f, object2D1, outObjMatchEdges, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
		
		if (object2D1 != atl::NIL && outObjMatchEdges != atl::NIL)
		{
			outEnhObjMatchEdges.AssignNonNil();
			
			avl::EnhanceSingleObjectMatch( inSearchTile, object2D1.Get(), outObjMatchEdges.Get(), false, atl::Dummy<avl::Object2D>().Get(), outEnhObjMatchEdges.Get() );
		}
		else
		{
			outEnhObjMatchEdges = atl::NIL;
		}
		
		if (object2D1 != atl::NIL)
		{
			avl::Point2D point2D3;
			float real2;
			float real3;
			float real4;
			float real5;
			
			outObjectMatch.AssignNonNil();
			outDelta.AssignNonNil();
			
			outObjectMatch.Get() = object2D1.Get().Match();
			avl::RectangleCenter( outObjectMatch.Get(), point2D3 );
			real2 = point2D3.X();
			avl::SubtractReals( real2, real1, real3 );
			real4 = point2D3.Y();
			avl::SubtractReals( real4, real1, real5 );
			outDelta.Get() = avl::Vector2D(real3, real5);
		}
		else
		{
			outObjectMatch = atl::NIL;
			outDelta = atl::NIL;
		}
	}
	else
	{
		outObjMatchEdges = atl::NIL;
		outEnhObjMatchEdges = atl::NIL;
		outObjectMatch = atl::NIL;
		outDelta = atl::NIL;
	}
}

void _MeasureLocalDispl( _MeasureLocalDisplState& state, const avl::Image& inRef, const avl::Image& inSampl, atl::Array< avl::Point2D >& outDisplLoc, atl::Array< atl::Conditional< avl::Vector2D > >& outDispl )
{
	int integer1;
	int integer2;
	int integer3;
	int integer4;
	int integer5;
	int integer6;
	
	integer1 = inRef.Width();
	integer2 = inRef.Height();
	
	// Define reference points based on "ResultSize" on which the cropped tiles will be created.
	__DefineResultsPoints( ResultSize.load(), SearchSize.load(), integer1, integer2, outDisplLoc );
	integer3 = RefSize.load();
	integer4 = SearchSize.load();
	integer5 = SearchSize.load();
	integer6 = RefSize.load();
	
	outDispl.Resize(outDisplLoc.Size());
	
	for( int i = 0; i < outDisplLoc.Size(); ++i )
	{
		// Crop tiles -> reference tiles to RefSize, search tiles to SearchSize
		__CropTiles( outDisplLoc[i], integer3, integer4, inSampl, inRef, avl::InterpolationMethod::Bilinear, state.image1, state.image2 );
		__FindCorrelationDelta( state.___FindCorrelationDeltaState1, integer5, integer6, state.image2, state.image1, outDispl[i], state.pathArray1, atl::Dummy< atl::Conditional< avl::Rectangle2D > >().Get(), state.pathArray2, state.pathArray3 );
	}
}

void __GenerateDeltaMap( __GenerateDeltaMapState& state, const atl::Array< atl::Conditional< avl::Vector2D > >& inDelta, const atl::Array< avl::Point2D >& inResultsPoints, int inResultSize, int inRefWidth, int inRefHeight, avl::Image& outDeltaMap )
{
	float real1;
	float real2;
	float real3;
	atl::Conditional< avl::Box > box1;
	atl::Conditional< int > integer1;
	atl::Conditional< int > integer2;
	int integer3;
	int integer4;
	
	real1 = static_cast<float>(1.0 / static_cast<double>(inResultSize));
	real2 = static_cast<float>(static_cast<double>(inRefWidth) / static_cast<double>(inResultSize));
	real3 = static_cast<float>(static_cast<double>(inRefHeight) / static_cast<double>(inResultSize));
	avl::RescalePointArray( inResultsPoints, avl::Point2D(0.0f, 0.0f), real1, false, state.point2DArray1 );
	avl::PointsBoundingBox_OrNil( state.point2DArray1, box1 );
	
	if (box1 != atl::NIL)
	{
		integer1.AssignNonNil();
		integer2.AssignNonNil();
		
		integer1.Get() = box1.Get().Width();
		integer2.Get() = box1.Get().Height();
	}
	else
	{
		integer1 = atl::NIL;
		integer2 = atl::NIL;
	}
	
	avl::MergeDefault< int >( integer1, static_cast<int>(real2), integer3 );
	avl::MergeDefault< int >( integer2, static_cast<int>(real3), integer4 );
	
	state.pixelArray1.Resize(inDelta.Size());
	
	for( int i = 0; i < inDelta.Size(); ++i )
	{
		avl::Vector2D vector2D1;
		float real4;
		float real5;
		
		avl::MergeDefault< avl::Vector2D >( inDelta[i], avl::Vector2D(-255.0f, -255.0f), vector2D1 );
		real4 = vector2D1.DeltaX();
		real5 = vector2D1.DeltaY();
		state.pixelArray1[i] = _avfml_pixel_ctor(static_cast<double>(real4), static_cast<double>(real5), 0.0, 0.0);
	}
	
	avl::EmptyImage( integer3, integer4, avl::Pixel(-255.0f, -255.0f, 0.0f, 0.0f), 2, avl::PlainType::Real, state.image1 );
	avl::Point2DArrayToLocationArray( state.point2DArray1, state.locationArray1 );
	avl::SetMultipleImagePixels( state.image1, state.locationArray1, state.pixelArray1 );
	avl::ThresholdToRegion( state.image1, atl::NIL, -254.0f, atl::NIL, 0.0f, state.region1 );
	avl::ExpaintImage_Bornemann( state.image1, state.region1, 20, 25, 2.0f, 0.0f, 3.0f, avl::LuminanceMode::YUV, state.image2 );
	avl::SmoothImage_Gauss( state.image2, atl::NIL, 15.0f, atl::NIL, 1.0f, state.image3, atl::Dummy<int>().Get(), atl::Dummy<int>().Get() );
	avl::DifferenceImage( state.image1, state.image3, state.region1, state.image3 );
	avl::AddChannels( state.image3, atl::NIL, state.image4 );
	avl::ThresholdToRegion( state.image4, atl::NIL, 40.0f, atl::NIL, 0.0f, state.region2 );
	avl::RegionDifference( state.region1, state.region2, state.region3 );
	avl::ExpaintImage_Bornemann( state.image1, state.region3, 10, 10, 2.0f, 3.0f, 35.0f, avl::LuminanceMode::YUV, state.image5 );
	avl::ComposeImages( state.image1, state.image5, state.region3, atl::NIL, state.image1 );
	avl::SmoothImage_Gauss( state.image1, atl::NIL, 2.0f, atl::NIL, 2.0f, state.image6, atl::Dummy<int>().Get(), atl::Dummy<int>().Get() );
	avl::ResizeImage( state.image6, inRefWidth, inRefHeight, avl::ResizeMethod::Bilinear, outDeltaMap );
}

void __AvgDisplMap( __AvgDisplMapState& state, int inDisplMapWidth, int inDisplMapHeight, int inDeltaMapWidth, int inDeltaMapHeight, const avl::Image& inImage, const avl::Image& inImage2, avl::Image& outImage )
{
	int integer1;
	int integer2;
	
	integer1 = inDeltaMapWidth > inDisplMapWidth ? inDeltaMapWidth : inDisplMapWidth;
	integer2 = inDeltaMapHeight > inDisplMapHeight ? inDeltaMapHeight : inDisplMapHeight;
	avl::ResizeImage( inImage, integer1, integer2, avl::ResizeMethod::NearestNeighbour, outImage );
	avl::ResizeImage( inImage2, integer1, atl::NIL, avl::ResizeMethod::NearestNeighbour, state.image1 );
	avl::AverageImages( outImage, state.image1, atl::NIL, outImage );
}

void _CorrectDisplMap( _CorrectDisplMapState& state, const atl::Array< atl::Conditional< avl::Vector2D > >& inDispl, const atl::Array< avl::Point2D >& inDisplLoc, const avl::Image& inDisplMap, avl::Image& outDisplMap )
{
	int integer1;
	int integer2;
	
	avs::GlobalParameterRef<avl::Image> Templ_LeftRef1(Templ_Left);
	integer1 = Templ_LeftRef1.Get().Width();
	integer2 = Templ_LeftRef1.Get().Height();
	__GenerateDeltaMap( state.___GenerateDeltaMapState1, inDispl, inDisplLoc, ResultSize.load(), integer1, integer2, state.image1 );
	state.image2 = inDisplMap.Height() == 0 && inDisplMap.Width() == 0 ? atl::Conditional< avl::Image >(atl::NIL) : atl::Conditional< avl::Image >(inDisplMap);
	
	if (state.image2 != atl::NIL)
	{
		int integer3;
		int integer4;
		int integer5;
		int integer6;
		
		state.image3.AssignNonNil();
		
		integer3 = state.image1.Height();
		integer4 = state.image1.Width();
		integer5 = inDisplMap.Width();
		integer6 = inDisplMap.Height();
		__AvgDisplMap( state.___AvgDisplMapState1, integer5, integer6, integer4, integer3, state.image2.Get(), state.image1, state.image3.Get() );
	}
	else
	{
		state.image3 = atl::NIL;
	}
	
	state.image4 = inDisplMap.Height() == 0 && inDisplMap.Width() == 0 ? atl::Conditional< avl::Image >(state.image1) : state.image3;
	avl::MergeDefault< avl::Image >( state.image4, state.image1, outDisplMap );
}

void _ApplyDisplMap( _ApplyDisplMapState& state, const avl::Image& inDisplMap, const avl::Image& inTempl, avl::Image& outTempl )
{
	int integer1;
	
	integer1 = inTempl.Width();
	avl::ResizeImage( inDisplMap, integer1, atl::NIL, avl::ResizeMethod::NearestNeighbour, state.image1 );
	avl::TranslatePixels( inTempl, state.image1, atl::NIL, avl::InterpolationMethod::Bilinear, outTempl );
}

void _FindFeatures( _FindFeaturesState& state, const avl::Image& inTempl, atl::Array< avl::Point2D >& outFeatureLoc )
{
	int integer1;
	int integer2;
	int integer3;
	int integer4;
	float real1;
	float real2;
	
	avl::ThresholdImage_Dynamic( inTempl, atl::NIL, atl::NIL, avl::ThresholdDynamicReferenceMethod::Middle, avl::KernelShape::Box, 5, atl::NIL, 25.0f, atl::NIL, 25.0f, state.image1, atl::Dummy<avl::Image>().Get() );
	integer1 = state.image1.Width();
	integer2 = state.image1.Height();
	integer3 = 10;
	integer4 = 10;
	real1 = static_cast<float>(static_cast<double>(integer2) / static_cast<double>(integer3));
	real2 = static_cast<float>(static_cast<double>(integer1) / static_cast<double>(integer4));
	avl::CreatePointGrid( avl::Point2D(0.0f, 0.0f), avl::Anchor2D::TopLeft, integer3, integer4, real1, real2, state.point2DArray1 );
	avl::SmoothImage_Gauss( state.image1, atl::NIL, 12.0f, atl::NIL, 2.0f, state.image2, atl::Dummy<int>().Get(), atl::Dummy<int>().Get() );
	
	state.point2DArray2.Resize(state.point2DArray1.Size());
	
	for( int i = 0; i < state.point2DArray1.Size(); ++i )
	{
		float real3;
		float real4;
		avl::ShapeRegion shapeRegion1;
		
		real3 = state.point2DArray1[i].X();
		real4 = state.point2DArray1[i].Y();
		avl::Box box1 = avl::Box(static_cast<int>(real3), static_cast<int>(real4), static_cast<int>(real2), static_cast<int>(real1));
		avl::CreateBoxRegion( box1, integer1, integer2, state.region1 );
		avl::RegionToShapeRegion( state.region1, shapeRegion1 );
		avl::ExtractBlobs_Intensity( state.image2, shapeRegion1, atl::NIL, avl::IntensityThresholdParams(60.0f, atl::NIL, 15.0f), avl::RegionProcessingParams(avl::KernelShape::Box, 0, 25), avl::BlobSplittingParams(avl::RegionConnectivity::EightDirections, 5000, atl::NIL, false), state.regionArray1, atl::Dummy< atl::Array< int > >().Get(), atl::Dummy<avl::Region>().Get() );
		state.integerArray1.Resize(state.regionArray1.Size());
		
		for( int j = 0; j < state.regionArray1.Size(); ++j )
		{
			avl::RegionArea( state.regionArray1[j], state.integerArray1[j] );
		}
		
		state.realArray1.Resize(state.integerArray1.Size());
		
		for( int j = 0; j < state.integerArray1.Size(); ++j )
		{
			state.realArray1[j] = static_cast<float>(state.integerArray1[j]);
		}
		
		avl::GetSortedElements< avl::Region >( state.regionArray1, state.realArray1, avl::SortingOrder::Ascending, atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), atl::Dummy< atl::Conditional< float > >().Get(), state.region2, state.region3, state.region4, state.region5, state.region6, state.region7, state.region8, state.region9 );
		
		if (state.region2 != atl::NIL)
		{
			avl::RegionMassCenter_OrNil( state.region2.Get(), state.point2DArray2[i], atl::NIL );
		}
		else
		{
			state.point2DArray2[i] = atl::NIL;
		}
	}
	
	avl::RemoveNils< avl::Point2D >( state.point2DArray2, outFeatureLoc, atl::NIL );
}

void _UpdateOneSide( _UpdateOneSideState& state, const avl::Image& inRef, const avl::Image& inSampl, const atl::Array< avl::Point2D >& inFeatureLoc, const avl::Image& inDisplMap, const avl::Point2D& inTemplStripeLoc, float inShear, avl::Image& outDisplMap, avl::Image& outTempl, atl::Conditional< float >& outShear, atl::Array< avl::Point2D >& outFeatureLoc )
{
	avl::Point2D point2D1;
	float real1;
	float real2;
	atl::Conditional< float > real3;
	float real4;
	int integer1;
	int integer2;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inRef, state.image1 );
	__ConvertLabToMono( state.___ConvertLabToMonoState2, inSampl, state.image2 );
	_MeasureGlobalScale( state.__MeasureGlobalScaleState1, state.image1, state.image2, inFeatureLoc, point2D1, real1, real2 );
	_Shear_calculate( state.__Shear_calculateState1, state.image2, inTemplStripeLoc, inShear, real3, outShear );
	avl::MergeDefault< float >( real3, real1, real4 );
	_ApplyGlobalScale( state.__ApplyGlobalScaleState1, point2D1, real4, real2, inRef, state.image3 );
	__ConvertLabToMono( state.___ConvertLabToMonoState3, state.image3, state.image4 );
	_MeasureLocalDispl( state.__MeasureLocalDisplState1, state.image4, state.image2, state.point2DArray1, state.vector2DArray1 );
	_CorrectDisplMap( state.__CorrectDisplMapState1, state.vector2DArray1, state.point2DArray1, inDisplMap, outDisplMap );
	_ApplyDisplMap( state.__ApplyDisplMapState1, outDisplMap, state.image3, outTempl );
	integer1 = outTempl.Width();
	integer2 = outTempl.Height();
	avl::Box box1 = avl::Box(0, 0, integer1, integer2);
	avl::CropImage( inSampl, box1, avl::Pixel(255.0f, 255.0f, 255.0f, 0.0f), state.image5 );
	avl::AccumulateElements< float >( real1, true, atl::NIL, false, state.realArrayState1 );
	_FindFeatures( state.__FindFeaturesState1, outTempl, outFeatureLoc );
}

void __CropSearchTiles( const avl::Point2D& inPoint, int inSearchSize, const avl::Image& inRefImage, avl::InterpolationMethod::Type inInterpolation, avl::Image& outSearchTiles )
{
	avl::Rectangle2D rectangle2D1;
	
	avl::CreateRectangle( inPoint, avl::Anchor2D::MiddleCenter, 0.0f, static_cast<float>(inSearchSize), static_cast<float>(inSearchSize), rectangle2D1 );
	avl::CropImageToRectangle( inRefImage, rectangle2D1, atl::NIL, avl::CropScaleMode::InputScale, inInterpolation, 0.0f, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outSearchTiles, atl::NIL, atl::NIL );
}

void _PrepareLRSearchTiles( _PrepareLRSearchTilesState& state )
{
	int integer1;
	int integer2;
	int integer3;
	int integer4;
	int integer5;
	int integer6;
	
	avs::GlobalParameterRef<avl::Image> Templ_LeftRef1(Templ_Left);
	integer1 = Templ_LeftRef1.Get().Width();
	integer2 = Templ_LeftRef1.Get().Height();
	
	// Should be enough to perform this only at the beginning. Result Points (grid map) should be the same - they are used as reference localization to cut samples into tiles.
	__DefineResultsPoints( ResultSize.load(), SearchSize.load(), integer1, integer2, state.point2DArray1 );
	integer3 = SearchSize.load();
	
	state.imageArray1.Resize(state.point2DArray1.Size());
	
	for( int i = 0; i < state.point2DArray1.Size(); ++i )
	{
		__CropSearchTiles( state.point2DArray1[i], integer3, Templ_LeftRef1.Get(), avl::InterpolationMethod::NearestNeighbour, state.imageArray1[i] );
	}
	
	avs::GlobalParameterRef<avl::Image> Templ_RightRef1(Templ_Right);
	integer4 = Templ_RightRef1.Get().Width();
	integer5 = Templ_RightRef1.Get().Height();
	
	// Should be enough to perform this only at the beginning. Result Points (grid map) should be the same - they are used as reference localization to cut samples into tiles.
	__DefineResultsPoints( ResultSize.load(), SearchSize.load(), integer4, integer5, state.point2DArray2 );
	integer6 = SearchSize.load();
	
	state.imageArray2.Resize(state.point2DArray2.Size());
	
	for( int i = 0; i < state.point2DArray2.Size(); ++i )
	{
		__CropSearchTiles( state.point2DArray2[i], integer6, Templ_RightRef1.Get(), avl::InterpolationMethod::NearestNeighbour, state.imageArray2[i] );
	}
	
	ResultPoints.SetValue(state.point2DArray1);
	SearchTiles_Left.SetValue(state.imageArray1);
	SearchTiles_Right.SetValue(state.imageArray2);
	ResultPoints_Left.SetValue(state.point2DArray1);
	ResultPoints_Rigth.SetValue(state.point2DArray2);
}

void _1_Update( _1_UpdateState& state, const avl::Image&, const avl::Image& inFrameLeft, const avl::Image& inFrameRight, avl::Image& outTempl )
{
	float real1;
	float real2;
	avl::Point2D point2D1;
	avl::Point2D point2D2;
	atl::Conditional< float > real3;
	atl::Conditional< float > real4;
	
	SearchSize.store(250);
	RefSize.store(180);
	ResultSize.store(100);
	avs::GlobalParameterRef<avl::Image> Templ_LeftRef1(Templ_Left);
	avs::GlobalParameterRef<atl::Array< avl::Point2D >> FeatLoc_LeftRef1(FeatLoc_Left);
	avs::GlobalParameterRef<atl::Array< avl::Point2D >> FeatLoc_RightRef1(FeatLoc_Right);
	avs::GlobalParameterRef<avl::Image> Templ_RightRef1(Templ_Right);
	avs::GlobalParameterRef<avl::Image> DisplMap_LeftRef1(DisplMap_Left);
	avs::GlobalParameterRef<avl::Image> DisplMap_RightRef1(DisplMap_Right);
	real1 = ShearRight.load();
	real2 = ShearLeft.load();
	avs::GlobalParameterRef<avl::GrayModel> StripeModel_SingleCamRef1(StripeModel_SingleCam);
	point2D1 = TemplStripeLoc_Left.load();
	point2D2 = TemplStripeLoc_Right.load();
	avs::GlobalParameterRef<avl::Image> TemplRef1(Templ);
	__CropSample_Left( state.___CropSample_LeftState1, inFrameLeft, StripeModel_SingleCamRef1.Get(), point2D1, Templ_LeftRef1.Get(), state.image1 );
	__CropSample_Right( state.___CropSample_RightState1, inFrameRight, StripeModel_SingleCamRef1.Get(), point2D2, Templ_RightRef1.Get(), state.image2 );
	
	if (state.image1 != atl::NIL)
	{
		state.image3.AssignNonNil();
		state.image4.AssignNonNil();
		state.point2DArray1.AssignNonNil();
		
		_UpdateOneSide( state.__UpdateOneSideState1, Templ_LeftRef1.Get(), state.image1.Get(), FeatLoc_LeftRef1.Get(), DisplMap_LeftRef1.Get(), TemplStripeLoc_Left.load(), real2, state.image3.Get(), state.image4.Get(), real3, state.point2DArray1.Get() );
	}
	else
	{
		state.image3 = atl::NIL;
		state.image4 = atl::NIL;
		state.point2DArray1 = atl::NIL;
		real3 = atl::NIL;
	}
	
	if (state.image2 != atl::NIL)
	{
		state.image5.AssignNonNil();
		
		_UpdateOneSide( state.__UpdateOneSideState2, Templ_RightRef1.Get(), state.image2.Get(), FeatLoc_RightRef1.Get(), DisplMap_RightRef1.Get(), TemplStripeLoc_Right.load(), real1, state.image6, state.image5.Get(), real4, state.point2DArray2 );
		
		if (state.image3 != atl::NIL && state.image4 != atl::NIL && state.point2DArray1 != atl::NIL)
		{
			DisplMap_Left.SetValue(state.image3.Get());
			DisplMap_Right.SetValue(state.image6);
			Templ_Left.SetValue(state.image4.Get());
			Templ_Right.SetValue(state.image5.Get());
			FeatLoc_Left.SetValue(state.point2DArray1.Get());
			FeatLoc_Right.SetValue(state.point2DArray2);
		}
	}
	else
	{
		state.image5 = atl::NIL;
		real4 = atl::NIL;
	}
	
	SearchSize.store(150);
	RefSize.store(150);
	ResultSize.store(50);
	_PrepareLRSearchTiles( state.__PrepareLRSearchTilesState1 );
	
	if (real3 != atl::NIL && real4 != atl::NIL)
	{
		ShearLeft.store(real3.Get());
		ShearRight.store(real4.Get());
	}
	
	if (state.image4 != atl::NIL && state.image5 != atl::NIL)
	{
		state.image7.AssignNonNil();
		
		avl::JoinImages( state.image4.Get(), state.image5.Get(), atl::NIL, atl::NIL, avl::JoinDirection::Horizontal, 0, state.image7.Get() );
	}
	else
	{
		state.image7 = atl::NIL;
	}
	
	avl::MergeDefault< avl::Image >( state.image7, TemplRef1.Get(), state.image8 );
	avl::MirrorImage( state.image8, avl::MirrorDirection::Both, outTempl );
}

void _X_CropBleeds( _X_CropBleedsState& state, const avl::Image& inTempl, avl::Image& outTempl )
{
	atl::Conditional< avl::Edge1D > edge1D1;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inTempl, state.image1 );
	avl::ScanSingleEdge_Direct( state.image1, g_constData1, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 5.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.0f, 5.0f, avl::EdgeTransition::Any), avl::Selection::First, atl::NIL, edge1D1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
	
	if (edge1D1 != atl::NIL)
	{
		atl::Conditional< avl::Edge1D > edge1D2;
		
		avl::ScanSingleEdge_Direct( state.image1, g_constData2, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 5.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.0f, 5.0f, avl::EdgeTransition::Any), avl::Selection::First, atl::NIL, edge1D2, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
		
		if (edge1D2 != atl::NIL)
		{
			int integer1;
			float real1;
			float real2;
			float real3;
			
			state.image2.AssignNonNil();
			
			integer1 = inTempl.Height();
			real1 = edge1D1.Get().Point().X();
			real2 = edge1D2.Get().Point().X();
			avl::SubtractReals( real2, real1, real3 );
			avl::Box box1 = avl::Box(static_cast<int>(real1), 0, static_cast<int>(real3), integer1);
			avl::CropImage( inTempl, box1, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), state.image2.Get() );
		}
		else
		{
			state.image2 = atl::NIL;
		}
	}
	else
	{
		state.image2 = atl::NIL;
	}
	
	avl::MergeDefault< avl::Image >( state.image2, inTempl, outTempl );
}

void _PrepareStripeModel( avl::GrayModel& outStripeModel, avl::GrayModel& outStripeModel_single_camera )
{
	// Create QI stripe GrayModel
	avl::CreateGrayModel( g_constData3, atl::NIL, atl::NIL, 0, atl::NIL, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, outStripeModel, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get() );
	
	outStripeModel_single_camera = outStripeModel;
}

void _CropTempl( _CropTemplState& state, const avl::Image& inTemplLab, const avl::Point2D& inPrescaler, int inMarginUp, int inMarginDown, const avl::GrayModel& inStripeModel, atl::Conditional< avl::Point2D >& outTemplStripeLoc, atl::Conditional< avl::Image >& outTemplLab )
{
	float real1;
	float real2;
	int integer1;
	int integer2;
	avl::Box box1;
	atl::Conditional< avl::Object2D > object2D1;
	
	avl::MirrorImage( inTemplLab, avl::MirrorDirection::Both, state.image1 );
	real1 = inPrescaler.X();
	real2 = inPrescaler.Y();
	avl::ResizeImage_Relative( state.image1, real1, real2, avl::ResizeMethod::Bilinear, state.image2 );
	integer1 = state.image2.Width();
	integer2 = state.image2.Height();
	box1 = avl::Box(0, inMarginUp, integer1, integer2 - inMarginUp - inMarginDown);
	avl::CropImage( state.image2, box1, avl::Pixel(255.0f, 255.0f, 255.0f, 0.0f), state.image3 );
	__ConvertLabToMono( state.___ConvertLabToMonoState1, state.image3, state.image4 );
	avl::LocateSingleObject_NCC( state.image4, atl::NIL, atl::NIL, inStripeModel, 1, atl::NIL, false, 0.7f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		outTemplStripeLoc.AssignNonNil();
		
		outTemplStripeLoc.Get() = object2D1.Get().Match().Origin();
	}
	else
	{
		outTemplStripeLoc = atl::NIL;
	}
	
	outTemplLab = state.image3;
}

void _PrepareLRTemplates( _PrepareLRTemplatesState& state, atl::Conditional< avl::Image >& outTempl_Left, atl::Conditional< avl::Image >& outTempl_Right )
{
	avl::Point2D point2D1;
	float real1;
	float real2;
	int integer1;
	int integer2;
	int integer3;
	int integer4;
	atl::Conditional< avl::Point2D > point2D2;
	
	avs::GlobalParameterRef<avl::Image> TemplRef1(Templ);
	point2D1 = TemplStripeLoc.load();
	real1 = point2D1.X();
	real2 = point2D1.Y();
	integer1 = TemplRef1.Get().Width();
	integer2 = TemplRef1.Get().Height();
	
	// Wyzcznenie ścieżki, wedłóg której ma być analizowany pasek w celu wykrycia punkut, który zostanie opisany jako punkt podziału. Zabieg stosowany w celu uniknięcia "dzielenia na sztywno" w poł obrazka. Pewnie docolowo linia podziału będzie znajdować się mniej więcej w połowie obrazu
	state.path1 = _avfml_path_ctor(_avfml_join_array<avl::Point2D>(avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(static_cast<double>(integer1) / 2.0) - 50)), static_cast<float>(static_cast<double>(static_cast<int>(static_cast<int>(real2) + 5)))), avl::Point2D(static_cast<float>(static_cast<double>(static_cast<int>(static_cast<double>(integer1) / 2.0) + 50)), static_cast<float>(static_cast<double>(static_cast<int>(static_cast<int>(real2) + 5))))));
	__ConvertLabToMono( state.___ConvertLabToMonoState1, TemplRef1.Get(), state.image1 );
	avl::ScanMultipleEdges_Direct( state.image1, state.path1, atl::NIL, 5, avl::SamplingParams(avl::InterpolationMethod::Bilinear, 1.0f, atl::NIL), avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.6f, 5.0f, avl::EdgeTransition::Any), 0.0f, atl::NIL, atl::NIL, state.edge1DArray1, state.gap1DArray1, atl::NIL, atl::Dummy<avl::Profile>().Get(), atl::Dummy<avl::Profile>().Get(), atl::Dummy< atl::Array< avl::Path > >().Get(), atl::Dummy<float>().Get() );
	
	state.point2DArray1.Resize(state.edge1DArray1.Size());
	
	for( int i = 0; i < state.edge1DArray1.Size(); ++i )
	{
		state.point2DArray1[i] = state.edge1DArray1[i].Point();
	}
	
	integer3 = state.point2DArray1.Size();
	integer4 = static_cast<int>(static_cast<double>(integer3) / 2.0);
	
	// AvsFilter_GetArrayElement_OrNil is intended for generated code only, consider use of built-in language features in regular programs.
	avs::AvsFilter_GetArrayElement_OrNil< avl::Point2D >( state.point2DArray1, integer4, false, point2D2 );
	
	if (point2D2 != atl::NIL)
	{
		float real3;
		avl::Box box1;
		avl::Box box2;
		avl::Vector2D vector2D1;
		int integer5;
		int integer6;
		float real4;
		avl::Box box3;
		avl::Box box4;
		avl::ShapeRegion shapeRegion1;
		atl::Conditional< avl::Object2D > object2D1;
		
		outTempl_Left.AssignNonNil();
		outTempl_Right.AssignNonNil();
		
		real3 = point2D2.Get().X();
		
		// Formuła uzupełniona
		box1 = avl::Box(0, 0, static_cast<int>(static_cast<int>(real3)), integer2);
		box2 = avl::Box(static_cast<int>(static_cast<int>(real3)), 0, static_cast<int>(integer1 - static_cast<int>(real3)), integer2);
		vector2D1 = avl::Vector2D(static_cast<float>(static_cast<double>(-static_cast<int>(real3))), 0.0f);
		avl::CropImage( TemplRef1.Get(), box1, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outTempl_Left.Get() );
		avl::CropImage( TemplRef1.Get(), box2, avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outTempl_Right.Get() );
		Templ_Left.SetValue(outTempl_Left.Get());
		Templ_Right.SetValue(outTempl_Right.Get());
		integer5 = outTempl_Right.Get().Width();
		integer6 = outTempl_Left.Get().Width();
		real4 = point2D2.Get().Y();
		
		// Creating BB for searching for the QE stripe in both left and rigth camera. The search for the BB should be done i the center off the image.
		box3 = avl::Box(0, static_cast<int>(static_cast<double>(static_cast<int>(real4)) - 40.0), 3500, 80);
		box4 = avl::Box(static_cast<int>(integer5 - 3500), static_cast<int>(static_cast<double>(static_cast<int>(real4)) - 40.0), 3500, 80);
		__ConvertLabToMono( state.___ConvertLabToMonoState2, outTempl_Left.Get(), state.image2 );
		avl::BoxToShapeRegion( box3, shapeRegion1 );
		__ConvertLabToMono( state.___ConvertLabToMonoState3, outTempl_Right.Get(), state.image3 );
		avs::GlobalParameterRef<avl::GrayModel> StripeModel_SingleCamRef1(StripeModel_SingleCam);
		avl::LocateSingleObject_NCC( state.image2, shapeRegion1, atl::NIL, StripeModel_SingleCamRef1.Get(), 1, atl::NIL, false, 0.5f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
		
		if (object2D1 != atl::NIL)
		{
			avl::ShapeRegion shapeRegion2;
			atl::Conditional< avl::Object2D > object2D2;
			
			avs::GlobalParameterRef<avl::GrayModel> StripeModel_SingleCamRef2(StripeModel_SingleCam);
			avl::BoxToShapeRegion( box4, shapeRegion2 );
			avl::LocateSingleObject_NCC( state.image3, shapeRegion2, atl::NIL, StripeModel_SingleCamRef2.Get(), 1, atl::NIL, false, 0.5f, atl::NIL, atl::NIL, object2D2, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
			
			if (object2D2 != atl::NIL)
			{
				avl::Point2D point2D3;
				avl::Point2D point2D4;
				
				point2D3 = object2D1.Get().Match().Origin();
				point2D4 = object2D2.Get().Match().Origin();
				TemplStripeLoc_Left.store(point2D3);
				TemplStripeLoc_Right.store(point2D4);
			}
		}
	}
	else
	{
		outTempl_Left = atl::NIL;
		outTempl_Right = atl::NIL;
	}
}

void _0_Init( _0_InitState& state, const avl::Image& inTempl )
{
	atl::Conditional< avl::Point2D > point2D1;
	
	_PrepareStripeModel( state.grayModel1, state.grayModel2 );
	StripeModel.SetValue(state.grayModel1);
	StripeModel_SingleCam.SetValue(state.grayModel2);
	_CropTempl( state.__CropTemplState1, inTempl, Prescaler, MarginUp, MarginDown, state.grayModel1, point2D1, state.image1 );
	
	if (state.image1 != atl::NIL)
	{
		__ConvertLabToMono( state.___ConvertLabToMonoState1, state.image1.Get(), state.image2 );
		avl::CropImage( state.image2, avl::Box(1405, 434, 621, 13), avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), state.image3 );
		
		if (point2D1 != atl::NIL)
		{
			Templ.SetValue(state.image1.Get());
			TemplStripeLoc.store(point2D1.Get());
		}
	}
	
	// Cutting Template for Left and Right Camera
	// 
	// (at the beginning and everytime the template is adjusted - _Main_3_Update).
	_PrepareLRTemplates( state.__PrepareLRTemplatesState1, state.image4, state.image5 );
	
	if (state.image4 != atl::NIL)
	{
		state.point2DArray1.AssignNonNil();
		
		__ConvertLabToMono( state.___ConvertLabToMonoState2, state.image4.Get(), state.image6 );
		_FindFeatures( state.__FindFeaturesState1, state.image6, state.point2DArray1.Get() );
	}
	else
	{
		state.point2DArray1 = atl::NIL;
	}
	
	if (state.image5 != atl::NIL)
	{
		__ConvertLabToMono( state.___ConvertLabToMonoState3, state.image5.Get(), state.image7 );
		
		if (state.point2DArray1 != atl::NIL)
		{
			_FindFeatures( state.__FindFeaturesState2, state.image7, state.point2DArray2 );
			FeatLoc_Left.SetValue(state.point2DArray1.Get());
			FeatLoc_Right.SetValue(state.point2DArray2);
		}
	}
	
	_PrepareLRSearchTiles( state.__PrepareLRSearchTilesState1 );
	ProcessIterator.store(0);
	SamplLeftReady.store(false);
	SamplRightReady.store(false);
}

void Main( void )
{
	atl::String file1;
	avl::Image image1;
	_X_CropBleedsState __X_CropBleedsState1;
	avl::Image image2;
	_0_InitState __0_InitState1;
	avl::EnumerateFilesState enumerateImagesState1;
	avl::Image image3;
	atl::String file2;
	atl::String string1;
	avl::EnumerateFilesState enumerateImagesState2;
	avl::Image image4;
	atl::String file3;
	atl::String string2;
	_1_UpdateState __1_UpdateState1;
	avl::Image image5;
	
	avl::CopyObject< atl::String >( g_constData4, file1 );
	avl::LoadImage( file1, false, image1 );
	_X_CropBleeds( __X_CropBleedsState1, image1, image2 );
	_0_Init( __0_InitState1, image1 );
	
	for(;;)
	{
		if (!avl::EnumerateImages( enumerateImagesState1, g_constData5, atl::NIL, avl::FileSortingOrder::Name, false, false, false, false, 0, image3, file2, string1, atl::NIL, atl::NIL ))
		{
			break;
		}
		if (!avl::EnumerateImages( enumerateImagesState2, g_constData6, atl::NIL, avl::FileSortingOrder::Name, false, false, false, false, 0, image4, file3, string2, atl::NIL, atl::NIL ))
		{
			break;
		}
		
		// Wykonywane na żądanie
		_1_Update( __1_UpdateState1, image2, image3, image4, image5 );
	}
}

void __CheckEntireSampl_Left( __CheckEntireSampl_LeftState& state, const avl::Image& inFrameLeft, bool& outHasEntireSampl, atl::Conditional< avl::Image >& outSampl )
{
	avl::Point2D point2D1;
	atl::Conditional< avl::Object2D > object2D1;
	atl::Conditional< bool > bool1;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inFrameLeft, state.image1 );
	avs::GlobalParameterRef<avl::GrayModel> StripeModelRef1(StripeModel);
	avs::GlobalParameterRef<avl::Image> Templ_LeftRef1(Templ_Left);
	point2D1 = TemplStripeLoc_Left.load();
	avl::LocateSingleObject_NCC( state.image1, atl::NIL, atl::NIL, StripeModelRef1.Get(), 1, atl::NIL, false, 0.1f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		atl::Conditional< int > integer1;
		int integer2;
		float real1;
		int integer3;
		int integer4;
		float real2;
		float real3;
		bool bool2;
		atl::Conditional< avl::Box > box1;
		avl::CoordinateSystem2D coordinateSystem2D1;
		avl::ShapeRegion shapeRegion1;
		int integer5;
		
		bool1.AssignNonNil();
		
		avl::ImageProjection( state.image1, atl::NIL, avl::ProjectionDirection::Vertical, avl::ProjectionMode::Average, state.profile1 );
		avl::SmoothProfile_Gauss( state.profile1, atl::NIL, 50.0f, 3.0f, false, state.profile2 );
		avl::DifferentiateProfile( state.profile2, false, avl::DifferentiationMethod::Central, state.profile3 );
		avl::ProfileEdges( state.profile3, atl::NIL, false, avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.0f, 0.005f, avl::EdgeTransition::DarkToBright), 100.0f, atl::NIL, atl::NIL, state.profileEdgeArray1, atl::NIL, atl::Dummy<avl::Profile>().Get() );
		
		state.integerArray1.Resize(state.profileEdgeArray1.Size());
		
		for( int i = 0; i < state.profileEdgeArray1.Size(); ++i )
		{
			float real4;
			
			real4 = state.profileEdgeArray1[i].Point();
			state.integerArray1[i] = static_cast<int>(real4);
		}
		
		// AvsFilter_GetArrayElement_OrNil is intended for generated code only, consider use of built-in language features in regular programs.
		avs::AvsFilter_GetArrayElement_OrNil< int >( state.integerArray1, 0, false, integer1 );
		integer2 = Templ_LeftRef1.Get().Height();
		real1 = point2D1.Y();
		integer3 = inFrameLeft.Width();
		integer4 = inFrameLeft.Height();
		real2 = object2D1.Get().Match().Origin().X();
		real3 = object2D1.Get().Match().Origin().Y();
		bool2 = static_cast<double>(real3) + 20.0 >= static_cast<double>(real1) && static_cast<double>(integer4) - static_cast<double>(real3) + 20.0 >= static_cast<double>(integer2) - static_cast<double>(real1);
		
		if (bool2)
		{
			if (integer1 != atl::NIL && integer1 != atl::NIL)
			{
				box1 = avl::Box(integer1.Get(), static_cast<int>(static_cast<double>(real3) - static_cast<double>(real1)), integer3 - integer1.Get(), integer2);
			}
			else
			{
				box1 = atl::NIL;
			}
		}
		else
		{
			box1 = atl::NIL;
		}
		
		if (box1 != atl::NIL)
		{
			outSampl.AssignNonNil();
			
			avl::CropImage( inFrameLeft, box1.Get(), avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outSampl.Get() );
		}
		else
		{
			outSampl = atl::NIL;
		}
		
		coordinateSystem2D1 = object2D1.Get().Alignment();
		avl::CreateRectangleRegion( avl::Rectangle2D(avl::Point2D(-3971.4707f, 2.842281f), 0.0f, 10258.6621f, 41.78479f), coordinateSystem2D1, integer3, integer4, state.region1, atl::NIL );
		avl::RegionComplement( state.region1, state.region2 );
		avl::RegionToShapeRegion( state.region2, shapeRegion1 );
		avl::LocateMultipleObjects_NCC( state.image1, shapeRegion1, atl::NIL, StripeModelRef1.Get(), 1, atl::NIL, false, 0.4f, 20.0f, atl::NIL, atl::NIL, state.object2DArray1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< atl::Array< float > > >().Get() );
		integer5 = state.object2DArray1.Size();
		bool1.Get() = bool2 && integer5 != 0;
	}
	else
	{
		bool1 = atl::NIL;
		outSampl = atl::NIL;
	}
	
	avl::MergeDefault< bool >( bool1, false, outHasEntireSampl );
}

void __CheckEntireSampl_Right( __CheckEntireSampl_RightState& state, const avl::Image& inFrameRight, bool& outHasEntireSampl, atl::Conditional< avl::Image >& outSampl )
{
	avl::Point2D point2D1;
	atl::Conditional< avl::Object2D > object2D1;
	atl::Conditional< bool > bool1;
	
	__ConvertLabToMono( state.___ConvertLabToMonoState1, inFrameRight, state.image1 );
	avs::GlobalParameterRef<avl::GrayModel> StripeModel_SingleCamRef1(StripeModel_SingleCam);
	point2D1 = TemplStripeLoc_Right.load();
	avs::GlobalParameterRef<avl::Image> Templ_RightRef1(Templ_Right);
	avl::LocateSingleObject_NCC( state.image1, atl::NIL, atl::NIL, StripeModel_SingleCamRef1.Get(), 1, atl::NIL, false, 0.2f, atl::NIL, atl::NIL, object2D1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Conditional< atl::Array< float > > >().Get() );
	
	if (object2D1 != atl::NIL)
	{
		atl::Conditional< int > integer1;
		float real1;
		int integer2;
		int integer3;
		int integer4;
		float real2;
		float real3;
		bool bool2;
		atl::Conditional< avl::Box > box1;
		avl::CoordinateSystem2D coordinateSystem2D1;
		avl::ShapeRegion shapeRegion1;
		int integer5;
		
		bool1.AssignNonNil();
		
		avl::ImageProjection( state.image1, atl::NIL, avl::ProjectionDirection::Vertical, avl::ProjectionMode::Average, state.profile1 );
		avl::SmoothProfile_Gauss( state.profile1, atl::NIL, 50.0f, 3.0f, false, state.profile2 );
		avl::DifferentiateProfile( state.profile2, false, avl::DifferentiationMethod::Central, state.profile3 );
		avl::ProfileEdges( state.profile3, atl::NIL, false, avl::EdgeScanParams(avl::ProfileInterpolationMethod::Quadratic4, 0.0f, 0.01f, avl::EdgeTransition::Any), 100.0f, atl::NIL, atl::NIL, state.profileEdgeArray1, atl::NIL, atl::Dummy<avl::Profile>().Get() );
		
		state.integerArray1.Resize(state.profileEdgeArray1.Size());
		
		for( int i = 0; i < state.profileEdgeArray1.Size(); ++i )
		{
			float real4;
			
			real4 = state.profileEdgeArray1[i].Point();
			state.integerArray1[i] = static_cast<int>(real4);
		}
		
		// AvsFilter_GetArrayElement_OrNil is intended for generated code only, consider use of built-in language features in regular programs.
		avs::AvsFilter_GetArrayElement_OrNil< int >( state.integerArray1, 0, true, integer1 );
		real1 = point2D1.Y();
		integer2 = Templ_RightRef1.Get().Height();
		integer3 = inFrameRight.Width();
		integer4 = inFrameRight.Height();
		real2 = object2D1.Get().Match().Origin().X();
		real3 = object2D1.Get().Match().Origin().Y();
		bool2 = static_cast<double>(real3) >= static_cast<double>(real1) && static_cast<double>(integer4) - static_cast<double>(real3) >= static_cast<double>(integer2) - static_cast<double>(real1);
		
		if (bool2)
		{
			if (integer1 != atl::NIL)
			{
				box1 = avl::Box(0, static_cast<int>(static_cast<double>(real3) - static_cast<double>(real1)), integer1.Get(), integer2);
			}
			else
			{
				box1 = atl::NIL;
			}
		}
		else
		{
			box1 = atl::NIL;
		}
		
		coordinateSystem2D1 = object2D1.Get().Alignment();
		avl::CreateRectangleRegion( avl::Rectangle2D(avl::Point2D(-3971.4707f, 2.842281f), 0.0f, 10258.6621f, 41.78479f), coordinateSystem2D1, integer3, integer4, state.region1, atl::NIL );
		avl::RegionComplement( state.region1, state.region2 );
		avl::RegionToShapeRegion( state.region2, shapeRegion1 );
		avl::LocateMultipleObjects_NCC( state.image1, shapeRegion1, atl::NIL, StripeModel_SingleCamRef1.Get(), 1, atl::NIL, false, 0.5f, 10.0f, atl::NIL, atl::NIL, state.object2DArray1, atl::NIL, atl::NIL, atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< avl::Image > >().Get(), atl::Dummy< atl::Array< atl::Array< float > > >().Get() );
		integer5 = state.object2DArray1.Size();
		bool1.Get() = bool2 && integer5 == 0;
		
		if (box1 != atl::NIL)
		{
			outSampl.AssignNonNil();
			
			avl::CropImage( inFrameRight, box1.Get(), avl::Pixel(0.0f, 0.0f, 0.0f, 0.0f), outSampl.Get() );
		}
		else
		{
			outSampl = atl::NIL;
		}
	}
	else
	{
		bool1 = atl::NIL;
		outSampl = atl::NIL;
	}
	
	avl::MergeDefault< bool >( bool1, false, outHasEntireSampl );
}

void _1_GetEntireSamplesPair( _1_GetEntireSamplesPairState& state, const avl::Image& inFrameLeft, const avl::Image& inFrameRight, bool& outPairReady, atl::Conditional< avl::Image >& outSamplLeft, atl::Conditional< avl::Image >& outSamplRight )
{
	bool bool1;
	bool bool2;
	bool bool3;
	bool bool4;
	atl::Conditional< bool > bool5;
	atl::Conditional< bool > bool6;
	
	__CheckEntireSampl_Left( state.___CheckEntireSampl_LeftState1, inFrameLeft, bool1, state.image1 );
	
	if (state.image1 != atl::NIL)
	{
		Sampl_Left.SetValue(state.image1.Get());
	}
	
	__CheckEntireSampl_Right( state.___CheckEntireSampl_RightState1, inFrameRight, bool2, state.image2 );
	
	if (state.image2 != atl::NIL)
	{
		Sampl_Right.SetValue(state.image2.Get());
	}
	
	bool3 = SamplLeftReady.load();
	bool4 = SamplRightReady.load();
	avs::GlobalParameterRef<avl::Image> Sampl_LeftRef1(Sampl_Left);
	avs::GlobalParameterRef<avl::Image> Sampl_RightRef1(Sampl_Right);
	outPairReady = (bool1 || bool3) && (bool2 || bool4);
	outSamplLeft = outPairReady ? atl::Conditional< avl::Image >(Sampl_LeftRef1.Get()) : atl::Conditional< avl::Image >(atl::NIL);
	outSamplRight = outPairReady ? atl::Conditional< avl::Image >(Sampl_RightRef1.Get()) : atl::Conditional< avl::Image >(atl::NIL);
	bool5 = outPairReady ? atl::Conditional< bool >(false) : bool3 ? atl::Conditional< bool >(atl::NIL) : atl::Conditional< bool >(bool1);
	bool6 = outPairReady ? atl::Conditional< bool >(false) : bool4 ? atl::Conditional< bool >(atl::NIL) : atl::Conditional< bool >(bool2);
	
	if (bool5 != atl::NIL && bool6 != atl::NIL)
	{
		SamplLeftReady.store(bool5.Get());
		SamplRightReady.store(bool6.Get());
	}
}

void Init( void )
{
	avl::InitLibrary();
	
	InitMainConsts();
}
