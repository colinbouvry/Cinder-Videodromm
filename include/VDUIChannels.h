#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "VDSettings.h"
// Mix
#include "VDMix.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm
{
	// stores the pointer to the VDUIChannels instance
	typedef std::shared_ptr<class VDUIChannels> VDUIChannelsRef;

	class VDUIChannels
	{
	public:
		VDUIChannels(VDSettingsRef aVDSettings, VDMixRef aVDMix);
		static VDUIChannelsRef	create(VDSettingsRef aVDSettings, VDMixRef aVDMix)
		{
			return shared_ptr<VDUIChannels>(new VDUIChannels(aVDSettings, aVDMix));
		}
		~VDUIChannels();
		void    Run(const char* title);
	private:
		// Settings
		VDSettingsRef				mVDSettings;
		// Mix
		VDMixRef					mVDMix;
		// imgui
		float						f = 0.0f;
		char						buf[64];
	};
}