#include "VDFbo.h"

#include "cinder/gl/Texture.h"
#include "cinder/Xml.h"

using namespace ci;
using namespace ci::app;

namespace VideoDromm {
	VDFbo::VDFbo(VDSettingsRef aVDSettings, VDAnimationRef aVDAnimation, VDTextureList aTextureList)
		: mFilePathOrText("")
		, mFboName("fbo")
		, mWidth(1024)
		, mHeight(480)
	{
		CI_LOG_V("VDFbo constructor");
		mVDSettings = aVDSettings;
		mVDAnimation = aVDAnimation;
		mTextureList = aTextureList;
		mType = UNKNOWN;
		inputTextureIndex = 0;
		mPosX = mPosY = 0.0f;
		mZoom = 1.0f;

		// init the fbo whatever happens next
		gl::Fbo::Format format;
		mFbo = gl::Fbo::create(mWidth, mHeight, format.depthTexture()); 

		// init with passthru shader
		mShaderName = "fbotexture";
		
		// load passthru fragment shader
		try {
			fs::path fragFile = getAssetPath("") / "fbotexture.frag";
			if (fs::exists(fragFile)) {
				mFboTextureFragmentShaderString = loadString(loadAsset("fbotexture.frag"));
			}
			else {
				mError = "fbotexture.frag does not exist, should quit";
				CI_LOG_V(mError);
			}
			mFboTextureShader = gl::GlslProg::create(mPassthruVextexShaderString, mFboTextureFragmentShaderString);
			mFboTextureShader->setLabel(mShaderName);
			CI_LOG_V("fbotexture.frag loaded and compiled");
		}
		catch (gl::GlslProgCompileExc &exc) {
			mError = string(exc.what());
			CI_LOG_V("unable to load/compile fbotexture fragment shader:" + string(exc.what()));
		}
		catch (const std::exception &e) {
			mError = string(e.what());
			CI_LOG_V("unable to load fbotexture fragment shader:" + string(e.what()));
		}
	}
	VDFbo::~VDFbo(void) {
	}

	XmlTree	VDFbo::toXml() const
	{
		XmlTree		xml;
		xml.setTag("details");
		xml.setAttribute("path", mFilePathOrText);
		xml.setAttribute("width", mWidth);
		xml.setAttribute("height", mHeight);
		xml.setAttribute("shadername", mShaderName);

		return xml;
	}

	void VDFbo::fromXml(const XmlTree &xml)
	{
		mId = xml.getAttributeValue<string>("id", "");
		string mGlslPath = xml.getAttributeValue<string>("shadername", "0.glsl");
		mWidth = xml.getAttributeValue<int>("width", 1024);
		mHeight = xml.getAttributeValue<int>("height", 768);
		CI_LOG_V("fbo id " + mId + "fbo shadername " + mGlslPath);
		mShaderName = mGlslPath;
		mFboTextureShader->setLabel(mShaderName);
		/*if (mGlslPath.length() > 0) {
			fs::path fr = getAssetPath("") / mVDSettings->mAssetsPath / mGlslPath;
			if (fs::exists(fr)) {
				loadFragmentShader(fr.string());
				CI_LOG_V("successfully loaded " + mGlslPath);
			}
			else {
				CI_LOG_V("try upper level because file does not exist: " + mGlslPath);
				fr = getAssetPath("") / mGlslPath;
				if (fs::exists(fr)) {
					loadFragmentShader(fr.string());
					CI_LOG_V("successfully loaded " + mGlslPath);
				}
			}
		}*/
	}
	void VDFbo::setFragmentShader(string aFragmentShaderString) {
		mFboTextureFragmentShaderString = aFragmentShaderString;
		mFboTextureShader = gl::GlslProg::create(mPassthruVextexShaderString, mFboTextureFragmentShaderString);

	}

	std::string VDFbo::getLabel() {
		mFbo->setLabel(mId + " " + mFboTextureShader->getLabel());		
		return mFbo->getLabel();
	}

	void VDFbo::setPosition(int x, int y) {
		mPosX = ((float)x / (float)mWidth) - 0.5;
		mPosY = ((float)y / (float)mHeight) - 0.5;
	}
	void VDFbo::setZoom(float aZoom) {
		mZoom = aZoom;
	}
	int VDFbo::getTextureWidth() {
		return mWidth;
	};

	int VDFbo::getTextureHeight() {
		return mHeight;
	};

	ci::ivec2 VDFbo::getSize() {
		return mFbo->getSize();
	}

	ci::Area VDFbo::getBounds() {
		return mFbo->getBounds();
	}

	GLuint VDFbo::getId() {
		return mFbo->getId();
	}

	std::string VDFbo::getName(){
		return mFboName;
	}
	void VDFbo::setInputTexture(unsigned int aTextureIndex) {
		if (aTextureIndex > mTextureList.size() - 1) aTextureIndex = mTextureList.size() - 1;
		inputTextureIndex = aTextureIndex;
	}

	/*ci::gl::Texture2dRef VDFbo::getInputTexture(unsigned int aIndex) {
		if (aIndex > mTextureList.size() - 1) aIndex = mTextureList.size() - 1;
		return mTextureList[aIndex]->getTexture();
		}
		}*/
	ci::gl::Texture2dRef VDFbo::getTexture() {
		iChannelResolution0 = vec3(mPosX, mPosY, 0.5);
		gl::ScopedFramebuffer fbScp(mFbo);
		gl::clear(Color::black());
		// setup the viewport to match the dimensions of the FBO
		gl::ScopedViewport scpVp(ivec2(0), mFbo->getSize());
		gl::ScopedGlslProg shaderScp(mFboTextureShader);
		//mFboTextureShader = mShaderList[mShaderIndex]->getShader();
		//mShader->bind();
		mFboTextureShader->uniform("iGlobalTime", mVDSettings->iGlobalTime); //TODO
		mFboTextureShader->uniform("iResolution", vec3(mWidth, mHeight, 1.0));
		mFboTextureShader->uniform("iChannelResolution[0]", iChannelResolution0);
		mFboTextureShader->uniform("iChannel0", 0);
		mFboTextureShader->uniform("iZoom", mZoom);
		gl::ScopedTextureBind tex(mTextureList[inputTextureIndex]->getTexture());
		gl::drawSolidRect(Rectf(0, 0, mVDSettings->mRenderWidth, mVDSettings->mRenderHeight));
		return mFbo->getColorTexture();
	}
} // namespace VideoDromm
