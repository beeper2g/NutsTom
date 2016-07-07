#import <UIKit/UIKit.h>
#import "GoogleMobileAdsSdkiOS/GADBannerView.h"
#import "GoogleMobileAdsSdkiOS/GADInterstitial.h"

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate,
        UITextFieldDelegate,UIApplicationDelegate, GADBannerViewDelegate, GADInterstitialDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    GADBannerView* bannerView_;
    GADInterstitial *interstitial_;
}

@property(nonatomic, readonly) RootViewController* viewController;
@property(nonatomic, retain) GADInterstitial *interstitial;
@property(nonatomic, retain) GADBannerView *banner;

- (void)showInterstitial;

- (void)showBanner;
- (void)hideBanner;

@end

