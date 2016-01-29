#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"
// json
#include "cinder/json.h"
// Settings
#include "VDSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm {

	typedef std::shared_ptr<class VDSession> VDSessionRef;
	

	class VDSession
	{
	public:
		VDSession(VDSettingsRef aVDSettings);
		static VDSessionRef			create(VDSettingsRef aVDSettings);
		bool						save();
		bool						restore();
		void						reset();
		void						resetSomeParams();


		// fbo 
		bool						mFlipV;
		bool						mFlipH;

	private:
		// Settings
		VDSettingsRef				mVDSettings;
		const string				sessionFileName = "VDSession.json";
		fs::path					sessionPath;
	};

}
