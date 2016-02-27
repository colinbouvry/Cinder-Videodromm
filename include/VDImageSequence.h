#pragma once

#include "cinder/Cinder.h"
#include "cinder/app/App.h"
#include "cinder/Rand.h"

// Settings
#include "VDSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm
{
	// stores the pointer to the VDImageSequence instance
	typedef std::shared_ptr<class VDImageSequence> VDImageSequenceRef;

	class VDImageSequence {
	public:
		VDImageSequence(VDSettingsRef aVDSettings, string aFilePath);

		static VDImageSequenceRef		create(VDSettingsRef aVDSettings, string aFilePath)
		{
			return shared_ptr<VDImageSequence>(new VDImageSequence(aVDSettings, aFilePath));
		}
		void						update();
		void						playSequence();
		void						stopSequence();
		void						pauseSequence();
		void						toggleLoadingFromDisk();
		void						stopLoading();
		int							getPlayheadPosition();
		void						setPlayheadPosition(int position);

		int							getSpeed();
		void						setSpeed(int speed);
		void						reverseSequence();
		bool						isLoadingFromDisk();
		bool						isValid(){ return mFramesLoaded > 0; };
		int							getMaxFrames();
		ci::gl::TextureRef			getCurrentSequenceTexture();

	private:
		// Settings
		VDSettingsRef				mVDSettings;

		int							playheadFrameInc;
		void						loadNextImageFromDisk();
		void						updateSequence();
		string						mFilePath;
		char						mFolder[32];
		string						mPrefix;
		string						mExt;
		int							mNumberOfDigits;
		int							mNextIndexFrameToTry;
		int							mCurrentLoadedFrame;
		int							mFramesLoaded;
		int							mPlayheadPosition;
		bool						mLoadingPaused;
		bool						mLoadingFilesComplete;
		bool						mPlaying;
		int							mSpeed;
		vector<ci::gl::TextureRef>	mSequenceTextures;

	};


}