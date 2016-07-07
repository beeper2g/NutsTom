//
//  ShareMethod.h
//  TouchIsKey
//
//  Created by Fred on 14-7-12.
//
//

#ifndef __TouchIsKey__ShareMethod__
#define __TouchIsKey__ShareMethod__

class ShareMethod {
public:
    // Ads releated
    static void showInterstitial();
    static void showBanner(bool show);
    // Share related
    static void shareWithWeChat(const char* text);
    static void shareWithFacebook(const char* text);
    // GameCenter related
    static void showGameCenter();
    static void reportScore(int score);
};

#endif /* defined(__TouchIsKey__ShareMethod__) */
