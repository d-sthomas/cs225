#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <vector>



StickerSheet::StickerSheet(const cs225::Image &picture, unsigned max) {
    base = picture;
    max_stickers = max;
}
StickerSheet::~StickerSheet() {
   stickers.clear();
}
StickerSheet::StickerSheet(const StickerSheet &other) {
    base = other.base;
    max_stickers = other.max_stickers;
    stickers.clear();
    for (auto sticker : other.stickers) {
        addSticker(*sticker.to_stick, sticker.x, sticker.y);
    }
}
const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
    base = other.base;
    max_stickers = other.max_stickers;
    stickers.clear();
    for (auto sticker : other.stickers) {
        addSticker(*sticker.to_stick, sticker.x, sticker.y);
    }
    return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    if (stickers.size() < max_stickers) {
        if (stickers.size() > max) {
            int idx = stickers.size() - max;
            stickers = {stickers.begin(), stickers.end() - idx};
        }
    }
    max_stickers = max;
}
int StickerSheet::addSticker(cs225::Image &sticker, unsigned x, unsigned y){ 
    if (x > base.width() || y > base.height()) return -1;
    Sticker add;
    add.to_stick = &sticker;
    add.x = x;
    add.y = y;
    stickers.push_back(add);
    return stickers.size();
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){ 
    if (index > stickers.size()) {
        return false;
    }
    stickers.at(index).x = x;
    stickers.at(index).y = y;
    return true;
 }
void StickerSheet::removeSticker(unsigned index){
    stickers.erase(stickers.begin() + index);
}
cs225::Image* StickerSheet::getSticker(unsigned index){
    if (index >= stickers.size()) return NULL;
    return stickers.at(index).to_stick;
}
cs225::Image StickerSheet::render() const{
    cs225::Image sheet = base;
    // do this for each sticker, so maybe triple loop??
    // lowkey i think the logic works, just need to figure out the const issue
    for (auto sticker : stickers) {
        unsigned sheet_x = sticker.x;
        unsigned sheet_y = sticker.y;
        for (unsigned x = 0; x < sticker.to_stick->width(); ++x) {
            for (unsigned y = 0; y < sticker.to_stick->height(); ++y) {
                cs225::HSLAPixel curr_pixel = sticker.to_stick->getPixel(x, y);
                if (curr_pixel.a == 1) {
                    sheet.getPixel(sheet_x, sheet_y) = curr_pixel;
                }
                sheet_y++;
            }
            sheet_y = sticker.y;
            sheet_x++;
        }
    }
    sheet.writeToFile("myImage.png");
    return sheet;
}