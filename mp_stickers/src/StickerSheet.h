/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
#include "Image.h"

struct Sticker {
        cs225::Image* to_stick;
        unsigned x;
        unsigned y;
};

class StickerSheet {
    public:
    StickerSheet(const cs225::Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(cs225::Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    cs225::Image* getSticker(unsigned index);
    cs225::Image render() const;
    private:
    cs225::Image base;
    std::vector<Sticker> stickers;
    unsigned max_stickers;
};

