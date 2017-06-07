#pragma once

#include <utility>
#define panorama
//#define mini

#ifdef mini
const int WIDTH = 320;
const int HEIGHT = 180;
#else
const int WIDTH = 1280;
const int HEIGHT = 720;
#endif

#ifdef panorama
const int NUM_VIEWPORTS = 4;
const int SCREEN_HEIGHT = HEIGHT;

const int SCREEN_WIDTH =  WIDTH*NUM_VIEWPORTS;
const float ASPECT_RATIO = 1;

#else
const int NUM_VIEWPORTS = 1;
const int WIDTH = 1280;
const int SCREEN_WIDTH =  WIDTH/NUM_VIEWPORTS;
const float SCREEN_HEIGHT = HEIGHT;
const float ASPECT_RATIO = static_cast<float>(SCREEN_WIDTH)/static_cast<float>(SCREEN_HEIGHT);
#endif

const float FOV = 360 / NUM_VIEWPORTS;


// touch prompter
const float BLOB_SIZE = 10.0;
const int ABSENCE_TO_DEATH = 5;
const int BLOB_MATURITY_THRESH = 6;
const float TOUCH_ICON_VOFFSET = 200;
const float TOUCH_ICON_SIZE = 70;
const float DETECTION_PANEL_SIZE = 180;

const ofColor TOUCH_READY_COLOR = ofColor(170,170,255, 200);
const ofColor TOUCH_ACTIVE_COLOR = ofColor(255,170,170, 200);
const ofColor TOUCH_UNAVAILABLE_COLOR = ofColor(80,80,80, 200);

const std::string TOUCH_ICON_IMAGE_FILE = "touch.tiff";
const int NUMBER_OF_TOUCH_ICONS = 8;
const int TOUCH_ICON_DISTANCE = SCREEN_WIDTH / NUMBER_OF_TOUCH_ICONS;
const int TOUCH_ICON_OFFSET = TOUCH_ICON_DISTANCE / 2;

const std::string PD_PATCH = "pd/main.pd";
const int TICKS_PER_BUFFER = 8;


const int AREA_DIVISION = 50;
const int NUM_AREA = AREA_DIVISION * AREA_DIVISION;
const float MAP_SIZE = 10000.0;
const float HEIGHT_LIMIT = 1500;
const float HALF_MAP_SIZE = MAP_SIZE/2.0;
const float DIVIDER = MAP_SIZE / AREA_DIVISION;

//frustum-camera
const float CAMERA_HEIGHT = 250;
const float NEAR_CLIP = 1;
const float NEAR_H     = 2 * tan(FOV / 2.0) * -NEAR_CLIP;
const float NEAR_W     = NEAR_H * ASPECT_RATIO;
const float HALF_NEAR_H = NEAR_H/2;
const float HALF_NEAR_W = NEAR_W/2;

const float FAR_CLIP = 20000;
const float FAR_H      = 2 * tan(FOV / 2.0) * -FAR_CLIP;
const float FAR_W      = FAR_H * ASPECT_RATIO;
const float HALF_FAR_H = FAR_H/2;
const float HALF_FAR_W = FAR_W/2;

const float FAR_LABEL_CLIP = 1000;
const float FAR_LABEL_H      = 2 * tan(FOV / 2.0) * -FAR_CLIP;
const float FAR_LABEL_W      = FAR_H * ASPECT_RATIO;
const float HALF_FAR_LABEL_H = FAR_H/2;
const float HALF_FAR_LABEL_W = FAR_W/2;


// building
const float LEVEL_HEIGHT = 30;
const float HALF_LEVEL_HEIGHT = LEVEL_HEIGHT / 2;
const float LABEL_INDENT = 5;
const float BUILDING_THRESHOLD = 1000.0;
const float BUILDING_LABEL_THRESHOLD = 700.0;

// street
const float BULLET_SIZE = 1.5;
const float STREET_LABEL_THRESHOLD = 1500.0;

// font
const std::string FONT = "zurich.ttf";
const float FONT_SIZE = 9.5;


// tuio
const std::string TRACK_MASTER_IP = "224.0.0.1";
const int TRACK_MASTER_PORT = 64000;
const int MY_TUIO_PORT = 23456;
const int MAX_BLOBS = 96;

// syphon
const std::string SYPHON_IP = "224.0.0.1";
const int SYPHON_PORT = 8400;

inline std::pair<bool, int> getArea(const ofVec3f &pos){
    if(pos.x < -HALF_MAP_SIZE || HALF_MAP_SIZE < pos.x) return std::make_pair(false,-1);
    if(pos.z < -HALF_MAP_SIZE || HALF_MAP_SIZE < pos.z) return std::make_pair(false,-1);
    if(pos.y > HEIGHT_LIMIT) return std::make_pair(false,-1);
    int x = (pos.x + HALF_MAP_SIZE) / DIVIDER;
    int z = (pos.z + HALF_MAP_SIZE) / DIVIDER;
    int index = z * AREA_DIVISION + x;
    return std::make_pair(true, index);
}

inline std::tuple<bool, int, int> areaToXY(std::pair<bool,int> area){
    if(!area.first){
        return std::make_tuple(false, 0,0);
    }
    int x = area.second % AREA_DIVISION;
    int z = area.second / AREA_DIVISION;
    return std::make_tuple(true, x,z);
}

inline std::tuple<bool, int, int> getAreaXY(ofVec3f &pos){
    return areaToXY(getArea(pos));
}
