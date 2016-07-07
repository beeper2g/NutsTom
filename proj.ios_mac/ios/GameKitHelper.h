//
//  GameKitHelper.h
//  NoZuoNoDie
//
//  Created by Fred Lee on 14-6-13.
//
//

#ifndef __NoZuoNoDie__GameKitHelper__
#define __NoZuoNoDie__GameKitHelper__

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface GameKitHelper :  NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate>{
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;

+ (GameKitHelper *)sharedGameKitHelper;
- (void) authenticateLocalUser;

- (void) showLeaderboard;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;

@end

#endif /* defined(__NoZuoNoDie__GameKitHelper__) */
