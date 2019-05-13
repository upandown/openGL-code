
#include <gl/glut.h>
#include<vector>
#include <string>
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

GLuint myTex;

Mat myVide;
VideoCapture cap;
Mat frame;
int flags = 0;
long currentFrame = 0;
long totalFrameNumber = 0;


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int w = myVide.cols;
	int h = myVide.rows;

	glGenTextures(1, &myTex);
	glBindTexture(GL_TEXTURE_2D, myTex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	if (myVide.channels() == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, myVide.data);
	else if (myVide.channels() == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, myVide.data);
	else if (myVide.channels() == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, myVide.data);


	glEnable(GL_TEXTURE_2D);    // 启用纹理

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);    // Normal Pointing Away From Viewer

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);  // Point 2 (Back)
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);  // Point 3 (Back)
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);  // Point 4 (Back)
	glEnd();

	glPopAttrib();
	glDisable(GL_TEXTURE_2D);


	glFlush();
	glutSwapBuffers();
}

void stepDisplay() {

	if (flags == 0) {
		// 读取视频帧
		cap.read(frame);

		// 设置每n帧获取一次帧
		if (currentFrame % 1 == 0) {
			myVide = frame;

			if (currentFrame >= totalFrameNumber) {
				flags = 1;
			}
			currentFrame++;
		}

		display();
	}

}

int main(int argc, char* argv[])
{
	myVide = imread("timg.jpg");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutCreateWindow("example");
	glEnable(GL_TEXTURE_2D);    // 启用纹理

	cap.open("C:\\Users\\admin\\Videos\\myVideo.mp4");

	// 获取视频总帧数
	totalFrameNumber = cap.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "total frames: " << totalFrameNumber << endl;

	glutDisplayFunc(display);
	glutIdleFunc(stepDisplay);
	glutMainLoop();

	system("pause");
	return 0;
}


