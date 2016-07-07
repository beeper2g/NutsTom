//
//  ShareMethod.cpp
//  TouchIsKey
//
//  Created by Fred on 14-7-12.
//
//

#include "../../Classes/sdk/ShareMethod.h"
#include "AppController.h"
#include "ShareSDK/shareSdk.h"
#include "GameKitHelper.h"

void ShareMethod::showInterstitial() {
    [(AppController*)[UIApplication sharedApplication].delegate showInterstitial];
}

void ShareMethod::showBanner(bool show) {

    AppController* app = (AppController*)[UIApplication sharedApplication].delegate;
    if (show) {
        [app showBanner];
    }
    else{        
        [app hideBanner];
    }
}

void ShareMethod::shareWithWeChat(const char* text)
{
    id<ISSContent> publishContent = [ShareSDK content:[[NSString alloc] initWithUTF8String:text]
                                       defaultContent:@"Nuts Tom很好玩"
                                                image:[ShareSDK pngImageWithImage:[UIImage imageNamed:@"Icon-57.png"]]
                                                title:[NSString stringWithFormat:@"#Nuts Tom#测试你的反应速度"]
                                                  url:@"https://itunes.apple.com/us/app/nuts-tom/id915824505"
                                          description:@"Nuts Tom"
                                            mediaType:SSPublishContentMediaTypeNews];
    
    [ShareSDK showShareViewWithType:ShareTypeWeixiTimeline
                          container:nil
                            content:publishContent
                      statusBarTips:NO
                        authOptions:nil
                       shareOptions:nil
                             result:^(ShareType type, SSResponseState state, id<ISSPlatformShareInfo> statusInfo, id<ICMErrorInfo> error, BOOL end)
     {
         
     }];
}

void ShareMethod::shareWithFacebook(const char* text)
{
    id<ISSContent> publishContent = [ShareSDK content:[[NSString alloc] initWithUTF8String:text]
                                       defaultContent:@"Nuts Tom is really funny"
                                                image:[ShareSDK pngImageWithImage:[UIImage imageNamed:@"Icon-57.png"]]
                                                title:[NSString stringWithFormat:@"#Nuts Tom#Test you action speed"]
                                                  url:@"https://itunes.apple.com/us/app/nuts-tom/id915824505"
                                          description:@"Nuts Tom"
                                            mediaType:SSPublishContentMediaTypeNews];
    
    [ShareSDK showShareViewWithType:ShareTypeFacebook
                          container:nil
                            content:publishContent
                      statusBarTips:NO
                        authOptions:nil
                       shareOptions:nil
                             result:^(ShareType type, SSResponseState state, id<ISSPlatformShareInfo> statusInfo, id<ICMErrorInfo> error, BOOL end)
     {
         
     }];
}

void ShareMethod::showGameCenter() {
    [[GameKitHelper sharedGameKitHelper] showLeaderboard];
}

void ShareMethod::reportScore(int score)
{
    GKScore *scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier:@"nutstom"];
    NSInteger s = (NSInteger)(score);
    scoreReporter.value = s;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error){
        if(error)
            NSLog(@"%@",error);
    }];
}
