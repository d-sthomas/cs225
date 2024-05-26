#include "Image.h"
//#include "RGB_HSL.h"

namespace cs225 {
    void Image::lighten() {
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).l += 0.1;
                if (getPixel(x,y).l > 1) {
                    getPixel(x,y).l = 1;
                }
            }
        }
    }
    void Image::lighten(double amount) {
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).l += amount;
                if (getPixel(x,y).l > 1) {
                    getPixel(x,y).l = 1;
                }
            }
        }
    }
    void Image::darken() {
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).l -= 0.1;
                if (getPixel(x,y).l < 0) {
                    getPixel(x,y).l = 0;
                }
            }
        }
    }
    void Image::darken(double amount){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).l -= amount;
                if (getPixel(x, y).l < 0) {
                    getPixel(x, y).l = 0;
                }
            }
        }
    }
    void Image::saturate(){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).s += 0.1;
                if (getPixel(x, y).s > 1) {
                    getPixel(x, y).s = 1;
                }
            }
        }
    }
    void Image::saturate(double amount){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).s += amount;
                if (getPixel(x, y).s > 1) {
                    getPixel(x, y).s = 1;
                }
            }
        }
    }
    void Image::desaturate(){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).s -= 0.1;
                if (getPixel(x, y).s < 0) {
                    getPixel(x, y).s = 0;
                }
            }
        }
    }
    void Image::desaturate(double amount){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).s -= amount;
                if (getPixel(x, y).s < 0) {
                    getPixel(x, y).s = 0;
                }
            }
        }
    }
    void Image::grayscale(){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).s = 0;
            }
        }
    }
    void Image::rotateColor(double degrees){
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                getPixel(x, y).h += degrees;
                if (getPixel(x, y).h > 360) {
                    getPixel(x, y).h -= 360;
                } else if (getPixel(x, y).h < 0) {
                    getPixel(x, y).h += 360;
                }
            }
        }
    }
    void Image::illinify(){
        int orange = 11;
        int blue = 216;
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                if (orange - getPixel(x, y).h > blue - getPixel(x,y).h) {
                    getPixel(x, y).h = orange;
                } else {
                    getPixel(x,y).h = blue;
                }
            }
        }
    }
    void Image::scale(double factor){
        unsigned int w = width() * factor;
        unsigned int h = height() * factor;
        if (factor > 1) {
            resize(w, h);
            scale_pixel(factor);
        } else {
            resize(w, h);
            scale_pixel(factor);
        }
    }

    void Image::scale(unsigned w, unsigned h){
        double og_w = width();
        double og_h = height();
        // checks width ratio
        double factor_w = w/og_w;
        double new_h = (w*og_h/og_w);
        // // checks height ration
        double factor_h = h/og_h;
        double new_w = (h*og_w/og_h);
        // // both scalings fit new dimensions, pick bigger one
        if ((w*new_h < w*h) && (h*new_w < w*h)) {
            if (w*new_h <= h*new_w) { // hxnew_w is bigger
                resize(new_w, h);
                scale_pixel(factor_h);
            } else { //wxnew_h is bigger
                resize(w, new_h);
                scale_pixel(factor_w);
            }
        } else if (w*new_h <= w*h) { // only w*new_h fits dimensions
            resize(w, new_h);
            scale_pixel(factor_w);
        } else if (h*new_w <= w*h) { // only h*new_w fits dimensions
            resize(new_w, h);
            scale_pixel(factor_h);
         }
    }

    //FIX THIS
    void Image::scale_pixel(double factor) {
        for (unsigned int x = 0; x < width(); ++x) {
            for (unsigned int y = 0; y < height(); ++y) {
                if (factor < 1) getPixel(x,y).h /= factor;
                else {
                    if (width() < height()) {
                        getPixel(x,y).h = (width() / factor / factor);
                    } else {
                        getPixel(x,y).h = (height() / factor / factor);
                    }
                }
            }
        }
    }
}