#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "view/Suite.h"

#include "ViewTest.h"
#include "ScrollViewTest.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ViewTestsApp : public App {
  public:
	void setup() override;
	void resize() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	view::SuiteRef	mTestSuite;
};

void ViewTestsApp::setup()
{
	mTestSuite = make_shared<view::Suite>();

	mTestSuite->registerSuiteView<ViewTest>( "view" );
	mTestSuite->registerSuiteView<ScrollViewTest>( "scrollview" );

	mTestSuite->selectTest( 0 );
}

void ViewTestsApp::mouseDown( MouseEvent event )
{
}

void ViewTestsApp::resize()
{
}

void ViewTestsApp::update()
{
	mTestSuite->update();
}

void ViewTestsApp::draw()
{
	gl::clear();

	mTestSuite->draw();

	CI_CHECK_GL();
}

CINDER_APP( ViewTestsApp, RendererGl( RendererGl::Options().msaa( 8 ) ), []( App::Settings *settings ) {
	settings->setWindowPos( 0, 0 );
	settings->setWindowSize( 960, 565 );
} )
