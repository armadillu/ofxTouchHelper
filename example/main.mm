#include "ofMain.h"
#include "testApp.h"

int main(){

	ofAppiPhoneWindow * iOSWindow = new ofAppiPhoneWindow();

	//iOSWindow->enableDepthBuffer();
	iOSWindow->enableAntiAliasing(1);

	ofSetupOpenGL(iOSWindow, 480, 320, OF_FULLSCREEN);
	ofRunApp(new testApp);

}
