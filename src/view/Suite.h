/*
 Copyright (c) 2015, Richard Eakin - All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are permitted provided
 that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and
 the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "view/View.h"
#include "view/Button.h"
#include "view/Selector.h"
#include "view/Slider.h"

#include "mason/Factory.h"

#include "cinder/app/KeyEvent.h"

namespace view {

typedef std::shared_ptr<class Suite>		SuiteRef;
typedef std::shared_ptr<class SuiteView>	SuiteViewRef;

class SuiteView : public view::View {
public:
	void connectKeyDown( const std::function<void ( ci::app::KeyEvent& )> &callback );

private:
	ci::signals::ScopedConnection	mKeyDownConn;
};

class Suite {
public:
	Suite();

	void update();
	void draw();

	template<typename Y>
	void registerSuiteView( const std::string &key )
	{
		mFactory.registerBuilder<Y>( key );
		mSelector->getSegmentLabels().push_back( key );
		resize();
	}

	void selectTest( size_t index );
	size_t getCurrentTestIndex() const	{ return mSelector->getSelectedIndex(); }
	const std::string& getCurrentTestKey() const { return mCurrentTestKey; }

	void reloadCurrentTest();

private:
	void keyDown( ci::app::KeyEvent &event );
	void resize();
	void selectTest( const std::string &key );

	view::ViewRef		mRootView;
	SuiteViewRef		mCurrentSuiteView;
	view::VSelectorRef	mSelector;
	std::string			mCurrentTestKey;

	mason::Factory<SuiteView>	mFactory;
};

} // namespace view
