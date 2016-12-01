#include "VDUIAnimation.h"

using namespace VideoDromm;

VDUIAnimation::VDUIAnimation(VDSettingsRef aVDSettings, VDSessionRef aVDSession) {
	mVDSettings = aVDSettings;
	mVDSession = aVDSession;
	// zoom
	minZoom = -3.0f;
	maxZoom = 3.0f;
	for (int c = 0; c < 128; c++)
	{
		localValues[c] = mVDSession->getControlValue(c);
	}
}
VDUIAnimation::~VDUIAnimation() {

}
float VDUIAnimation::getValue(unsigned int aCtrl) {
	return mVDSession->getControlValue(aCtrl);
}
void VDUIAnimation::setValue(unsigned int aCtrl, float aValue) {
	mVDSession->setControlValue(aCtrl, aValue);
}
bool VDUIAnimation::getBoolValue(unsigned int aCtrl) {
	return mVDSession->getBoolValue(aCtrl);
}
void VDUIAnimation::toggleValue(unsigned int aCtrl) {
	mVDSession->toggleValue(aCtrl);
}
void VDUIAnimation::toggleAuto(unsigned int aCtrl) {
	mVDSession->toggleAuto(aCtrl);
}
void VDUIAnimation::toggleTempo(unsigned int aCtrl) {
	mVDSession->toggleTempo(aCtrl);
}
void VDUIAnimation::resetAutoAnimation(unsigned int aCtrl) {
	mVDSession->resetAutoAnimation(aCtrl);
}
float VDUIAnimation::getMinUniformValueByIndex(unsigned int aIndex) {
	return mVDSession->getMinUniformValueByIndex(aIndex);
}
float VDUIAnimation::getMaxUniformValueByIndex(unsigned int aIndex) {
	return mVDSession->getMaxUniformValueByIndex(aIndex);
}
void VDUIAnimation::Run(const char* title) {

	ui::SetNextWindowSize(ImVec2(mVDSettings->uiLargeW, mVDSettings->uiLargeH), ImGuiSetCond_Once);
	ui::SetNextWindowPos(ImVec2(mVDSettings->uiMargin, mVDSettings->uiYPosRow2), ImGuiSetCond_Once);
	ui::Begin("Animation", NULL, ImVec2(0, 0), ui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
	{
		ui::PushItemWidth(mVDSettings->mPreviewFboWidth);
		if (ui::CollapsingHeader("Effects", NULL, true, true))
		{
			int hue = 0;

			/*(mVDSettings->iRepeat) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			mVDSettings->iRepeat ^= ui::Button("repeat");
			ui::PopStyleColor(3);
			hue++;
			ui::SameLine();*/

			ctrl = 45;
			(getBoolValue(ctrl)) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ui::Button("glitch")) {
				toggleValue(ctrl);
			}
			ui::PopStyleColor(3);
			hue++;
			ui::SameLine();

			ctrl = 46;
			(getBoolValue(ctrl)) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ui::Button("toggle")) {
				toggleValue(ctrl);
			}
			ui::PopStyleColor(3);
			hue++;
			ui::SameLine();

			ctrl = 47;
			(getBoolValue(ctrl)) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ui::Button("vignette")) {
				toggleValue(ctrl);
			}
			ui::PopStyleColor(3);
			hue++;

			ctrl = 48;
			(getBoolValue(ctrl)) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ui::Button("invert")) {
				toggleValue(ctrl);
			}
			ui::PopStyleColor(3);
			hue++;
			ui::SameLine();

			(mVDSettings->iGreyScale) ? ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ui::PushStyleColor(ImGuiCol_Button, ImColor::HSV(1.0f, 0.1f, 0.1f));
			ui::PushStyleColor(ImGuiCol_ButtonHovered, ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ui::PushStyleColor(ImGuiCol_ButtonActive, ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			mVDSettings->iGreyScale ^= ui::Button("greyscale");
			ui::PopStyleColor(3);
			hue++;
			ui::SameLine();

			if (ui::Button("blackout"))
			{
				setValue(1, 0.0);
				setValue(2, 0.0);
				setValue(3, 0.0);
				setValue(4, 0.0);
				setValue(5, 0.0);
				setValue(6, 0.0);
				setValue(7, 0.0);
				setValue(8, 0.0);
			}
		}
		if (ui::CollapsingHeader("Animation", NULL, true, true))
		{
			//ui::SliderInt("UI Zoom", &mVDSettings->mUIZoom, 1, 8);

			// iChromatic
			ctrl = 17;
			if (ui::Button("a##chromatic")) {
				toggleAuto(ctrl);
			}
			ui::SameLine();
			if (ui::Button("t##chromatic")) { toggleTempo(ctrl); }
			ui::SameLine();
			if (ui::Button("x##chromatic")) {
				resetAutoAnimation(ctrl);
			}
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::SliderFloat("chromatic/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				mVDSession->setControlValue(ctrl, localValues[ctrl]);
			}

			// ratio
			ctrl = 11;
			if (ui::Button("a##ratio")) { toggleAuto(ctrl); }
			ui::SameLine();
			if (ui::Button("t##ratio")) { toggleTempo(ctrl); }
			ui::SameLine();
			if (ui::Button("x##ratio")) { resetAutoAnimation(ctrl); }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::SliderFloat("ratio/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// exposure
			ctrl = 14;
			if (ui::Button("a##exposure")) { toggleAuto(ctrl); }
			ui::SameLine();
			if (ui::Button("t##exposure")) { toggleTempo(ctrl); }
			ui::SameLine();
			if (ui::Button("x##exposure")) { resetAutoAnimation(ctrl); }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::DragFloat("exposure", &localValues[ctrl], 0.1f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// zoom
			ctrl = 22;
			if (ui::Button("a##zoom"))
			{
				toggleAuto(ctrl);
			}
			ui::SameLine();
			if (ui::Button("t##zoom")) { toggleTempo(ctrl); }
			ui::SameLine();
			if (ui::Button("x##zoom")) { resetAutoAnimation(ctrl); }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::DragFloat("zoom", &localValues[ctrl], 0.1f, minZoom, maxZoom))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			ui::DragFloat("minzm", &minZoom, 0.1f, minZoom, maxZoom);
			ui::SameLine();
			ui::DragFloat("maxzm", &maxZoom, 0.1f, minZoom, maxZoom);

			// rotation speed 
			ctrl = 19;
			if (ui::Button("a##rotationspeed")) { toggleAuto(ctrl); }
			ui::SameLine();
			if (ui::Button("t##rotationspeed")) { toggleTempo(ctrl); }
			ui::SameLine();
			if (ui::Button("x##rotationspeed")) { resetAutoAnimation(ctrl); }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::DragFloat("rotationSpeed", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// badTv
			/*if (ui::Button("x##badtv")) { mVDSettings->iBadTv = 0.0f; }
			ui::SameLine();
			if (ui::SliderFloat("badTv/min/max", &mVDSettings->iBadTv, 0.0f, 5.0f))
			{
			}*/
			// param1
			if (ui::Button("x##param1")) { mVDSettings->iParam1 = 1.0f; }
			ui::SameLine();
			if (ui::SliderFloat("param1/min/max", &mVDSettings->iParam1, 0.01f, 100.0f))
			{
			}
			// param2
			if (ui::Button("x##param2")) { mVDSettings->iParam2 = 1.0f; }
			ui::SameLine();
			if (ui::SliderFloat("param2/min/max", &mVDSettings->iParam2, 0.01f, 100.0f))
			{
			}
			sprintf(buf, "XorY");
			mVDSettings->iXorY ^= ui::Button(buf);

			// steps
			ctrl = 20;
			if (ui::Button("x##steps")) { localValues[ctrl] = 16.0f; }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::SliderFloat("steps", &localValues[ctrl], 1.0f, 128.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// pixelate
			ctrl = 15;
			if (ui::Button("x##pixelate")) { localValues[ctrl] = 1.0f; }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::SliderFloat("pixelate", &localValues[ctrl], 0.01f, 1.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// trixels
			ctrl = 16;
			if (ui::Button("x##trixels")) { localValues[ctrl] = 0.0f; }
			ui::SameLine();
			localValues[ctrl] = mVDSession->getControlValue(ctrl);
			if (ui::SliderFloat("trixels", &localValues[ctrl], 0.00f, 1.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			ui::SliderFloat("ABP Bend", &mVDSettings->mBend, -20.0f, 20.0f);
		}
		// grid
		/*
		ctrl = 17;
		if (ui::Button("x##grid")) { localValues[ctrl] = 0.0f; }
		ui::SameLine();
		if (ui::SliderFloat("grid", &localValues[ctrl], 0.00f, 60.0f))
		{
			aParams << ",{\"name\" : " << ctrl << ",\"value\" : " << localValues[ctrl] << "}";
		}

	if (ui::CollapsingHeader("Camera", NULL, true, true))
	{
		ui::SliderFloat("Pos.x", &mVDSettings->mRenderPosXY.x, 0.0f, mVDSettings->mRenderWidth);
		ui::SliderFloat("Pos.y", &mVDSettings->mRenderPosXY.y, 0.0f, mVDSettings->mRenderHeight);
		float eyeZ = mVDSettings->mCamera.getEyePoint().z;
		if (ui::SliderFloat("Eye.z", &eyeZ, -500.0f, 1.0f))
		{
			vec3 eye = mVDSettings->mCamera.getEyePoint();
			eye.z = eyeZ;
			mVDSettings->mCamera.setEyePoint(eye);
		}

	}
		*/

		ui::PopItemWidth();
	}
	ui::End();
}
