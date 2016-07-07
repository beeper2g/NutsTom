/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.baidu.mobstat.StatService;
import com.beeper2g.nutstom.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.RelativeLayout;

import cn.domob.android.ads.AdEventListener;
import cn.domob.android.ads.AdView;
import cn.domob.android.ads.InterstitialAd;
import cn.domob.android.ads.InterstitialAdListener;
import cn.domob.android.ads.AdManager.ErrorCode;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.Platform.ShareParams;
import cn.sharesdk.onekeyshare.OnekeyShare;
import cn.sharesdk.onekeyshare.ShareContentCustomizeCallback;

public class AppActivity extends Cocos2dxActivity {
  private RelativeLayout rl_adContainer;
  private InterstitialAd mInterstitialAd;
  private AdView rl_ad;

  final static public String PUBLISHER_ID = "";
  final static public String InterstitialPPID = "";
  final static public String InlinePPID = "";

  private static AppActivity _appActiviy;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);

    _appActiviy = this;
    initInterstitialAd();
    initBannerAd();
  }

  void initInterstitialAd() {

    mInterstitialAd = new InterstitialAd(this, PUBLISHER_ID, InterstitialPPID);

    mInterstitialAd.setInterstitialAdListener(new InterstitialAdListener() {
      @Override
      public void onInterstitialAdReady() {
      }

      @Override
      public void onLandingPageOpen() {
      }

      @Override
      public void onLandingPageClose() {
      }

      @Override
      public void onInterstitialAdPresent() {
      }

      @Override
      public void onInterstitialAdDismiss() {
        mInterstitialAd.loadInterstitialAd();
      }

      @Override
      public void onInterstitialAdFailed(ErrorCode arg0) {
      }

      @Override
      public void onInterstitialAdLeaveApplication() {

      }

      @Override
      public void onInterstitialAdClicked(InterstitialAd arg0) {
      }
    });

    mInterstitialAd.loadInterstitialAd();
  }

  void initBannerAd() {
    rl_ad = new AdView(this, AppActivity.PUBLISHER_ID, AppActivity.InlinePPID);
    rl_ad.setAdEventListener(new AdEventListener() {
      @Override
      public void onAdOverlayPresented(AdView adView) {
      }

      @Override
      public void onAdOverlayDismissed(AdView adView) {
      }

      @Override
      public void onAdClicked(AdView arg0) {
      }

      @Override
      public void onLeaveApplication(AdView arg0) {
      }

      @Override
      public Context onAdRequiresCurrentContext() {
        return AppActivity.this;
      }

      @Override
      public void onAdFailed(AdView arg0, ErrorCode arg1) {
      }

      @Override
      public void onEventAdReturned(AdView arg0) {
      }
    });

    rl_adContainer = new RelativeLayout(this);
    RelativeLayout.LayoutParams parentLayputParams = new RelativeLayout.LayoutParams(
        RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT);
    RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
        RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
    layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM, RelativeLayout.TRUE);
    rl_adContainer.addView(rl_ad, layoutParams);
    addContentView(rl_adContainer, parentLayputParams);
  }

  @Override
  protected void onResume() {
    super.onResume();
    StatService.onResume(this);
  }

  @Override
  protected void onPause() {
    super.onPause();
    StatService.onPause(this);
  }

  public static void showBanner() {
    _appActiviy.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        if (_appActiviy.rl_ad == null) {
          _appActiviy.initBannerAd();
        } else {
          _appActiviy.rl_ad.setVisibility(View.VISIBLE);
        }
      }
    });
  }

  public static void hideBanner() {
    _appActiviy.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        if (_appActiviy.rl_ad != null) {
          _appActiviy.rl_ad.setVisibility(View.GONE);
        }
      }
    });
  }

  public static void showInterstitial() {
    _appActiviy.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        if (_appActiviy.mInterstitialAd.isInterstitialAdReady()) {
          _appActiviy.mInterstitialAd.showInterstitialAd(_appActiviy);
        } else {
          _appActiviy.mInterstitialAd.loadInterstitialAd();
        }
      }
    });
  }

  public static void shareWithWeChat(String text) {
    if (text.length() == 0) {
      text = "Nuts Tom，测试你的反应速度";
    } else {
      text = "万里长征，我走了" + text + "步，你来试试吧？";
    }
    
    final String textTmp = text;
    _appActiviy.runOnUiThread(new Runnable() {
      @Override
      public void run() {

        OnekeyShare oks = new OnekeyShare();
        // 关闭sso授权
        oks.disableSSOWhenAuthorize();

        // 分享时Notification的图标和文字
        oks.setNotification(R.drawable.icon, _appActiviy.getString(R.string.app_name));

        oks.setShareContentCustomizeCallback(new ShareContentCustomizeCallback() {
          @Override
          public void onShare(Platform platform, ShareParams paramsToShare) {
            paramsToShare.setShareType(Platform.SHARE_WEBPAGE);
            paramsToShare.setUrl("http://u.360.cn/detail.php?sid=201884136");
            paramsToShare.setTitle(_appActiviy.getString(R.string.app_name));
            paramsToShare.setText(textTmp);

            Drawable drawable = _appActiviy.getResources().getDrawable(R.drawable.icon);
            BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;
            Bitmap bitmap = bitmapDrawable.getBitmap();
            paramsToShare.setImageData(bitmap);
          }
        });

        // 启动分享GUI
        oks.show(_appActiviy);
      }
    });
  }

}
